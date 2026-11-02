"""Suggest a geometric chain mapping for the cloth / skirt bone chains.

Both rigs have their own skirt chains (the hero's robe bones vs Korinsna's dress bones).
Retargeting them needs a start/end bone pair on each side; the chains are matched here by where
their roots sit in component space, because the naming conventions are unrelated.

Reads  extract/dump/refbones.txt            (game rig, component space)
       extract/ue-sk-korinsna-refpose.json  (Korinsna rig, component space)
Writes extract/skirt-chain-map.json
"""
import json
import os
import re

import numpy as np

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REFBONES = os.path.join(ROOT, "extract", "dump", "refbones.txt")
KOR_POSE = os.path.join(ROOT, "extract", "ue-sk-korinsna-refpose.json")
OUT = os.path.join(ROOT, "extract", "skirt-chain-map.json")


def hun_key(name):
    """name -> (chain key, sort index) for the game rig's cloth bones."""
    m = re.match(r"bns_skirt_(\d)_(\d+)_([lr])$", name)
    if m:
        return "skirt_%s_%s" % (m.group(1), m.group(3)), int(m.group(2))
    m = re.match(r"bns_sleeves_(\d)_(\d+)_([lr])$", name)
    if m:
        return "sleeves_%s_%s" % (m.group(1), m.group(3)), int(m.group(2))
    for prefix in ("bns_frontSkirtArmorRibbon_", "bns_ribbon_0_", "bns_cloak_"):
        if name.startswith(prefix):
            tail = name[len(prefix):]
            if tail.isdigit():
                return prefix.rstrip("_"), int(tail)
    return None, None


def kor_key(name):
    """name -> (chain key, sort index) for the Korinsna rig's cloth bones."""
    m = re.match(r"([lrmb])_skirt_(\d+)$", name)
    if m:
        return "skirt_%s" % m.group(1), int(m.group(2))
    m = re.match(r"(qunshi|xiongshi)_(\d+)$", name)
    if m:
        return m.group(1), int(m.group(2))
    return None, None


def load_hun():
    lines = open(REFBONES, encoding="utf-8", errors="replace").read().splitlines()
    start = next(i for i, line in enumerate(lines) if line.startswith("== after-reset nb=")) + 1
    bones = {}
    for line in lines[start:]:
        if not line or not line[:1].isdigit() or "|" not in line:
            break
        _, name, _parent, loc, _q, _s = line.split("|")
        bones[name] = np.array([float(v) for v in loc.split(",")])
    return bones


def chains(bones, key_fn):
    groups = {}
    for name, pos in bones.items():
        key, index = key_fn(name)
        if key is not None:
            groups.setdefault(key, []).append((index, name, pos))
    out = []
    for key, items in groups.items():
        if len(items) < 2:
            continue
        items.sort()
        out.append((key, items[0][1], items[-1][1], items[0][2], len(items)))
    return sorted(out, key=lambda c: c[1])


def main():
    hun = load_hun()
    kor = {name: np.array(pos) for name, pos in
           json.load(open(KOR_POSE, encoding="utf-8"))["refpose"].items()}

    hun_chains = chains(hun, hun_key)
    kor_chains = chains(kor, kor_key)

    print("game cloth chains (%d):" % len(hun_chains))
    for key, start, end, pos, count in hun_chains:
        print("  %-22s %-30s -> %-30s n=%d root=%s" % (
            key, start, end, count, np.round(pos, 1)))

    print("\nkorinsna cloth chains (%d):" % len(kor_chains))
    for key, start, end, pos, count in kor_chains:
        print("  %-22s %-14s -> %-14s n=%d root=%s" % (
            key, start, end, count, np.round(pos, 1)))

    suggestions = []
    used = set()
    for key, start, end, pos, count in hun_chains:
        best = None
        for kkey, kstart, kend, kpos, kcount in kor_chains:
            if kstart in used:
                continue
            d = float(np.linalg.norm(pos - kpos))
            if best is None or d < best[0]:
                best = (d, kkey, kstart, kend, kcount)
        if best:
            used.add(best[2])
            suggestions.append({
                "game_chain": [start, end],
                "korinsna_chain": [best[2], best[3]],
                "distance_cm": round(best[0], 2),
                "game_count": count,
                "korinsna_count": best[4],
            })

    print("\nsuggested mapping (greedy nearest root):")
    for s in suggestions:
        print("  %-34s -> %-14s d=%6.1f cm (%d vs %d bones)" % (
            "%s..%s" % tuple(s["game_chain"]), s["korinsna_chain"][0],
            s["distance_cm"], s["game_count"], s["korinsna_count"]))

    with open(OUT, "w", encoding="utf-8") as fh:
        json.dump(suggestions, fh, indent=1)


if __name__ == "__main__":
    main()
