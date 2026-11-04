"""Print the bones each configured retarget chain actually contains (read-only).

A UE retarget chain is "every bone on the hierarchy path from start to end", so this is the only way to
know whether twist bones sit inside a limb chain. Writes extract/ue-chain-bones.txt.
"""
import json
import os

import unreal

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
CONFIG = os.path.join(ROOT, "ue", "retarget_config.json")
OUT = os.path.join(ROOT, "extract", "ue-chain-bones.txt")

TARGET_MESH = "/Game/Korinsna/SK_Korinsna"
SOURCE_MESH = "/Game/Korinsna/Source/HunSkin"

lines = []


def log(msg):
    lines.append(str(msg))


def spawn_component(mesh_path):
    mesh = unreal.EditorAssetLibrary.load_asset(mesh_path)
    if mesh is None:
        raise SystemExit("missing " + mesh_path)
    subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    actor = subsystem.spawn_actor_from_class(unreal.SkeletalMeshActor, unreal.Vector(0, 0, 0))
    component = actor.skeletal_mesh_component
    component.set_skeletal_mesh_asset(mesh)
    return subsystem, actor, component


def bone_path(component, start, end):
    """Bones from `start` down to `end` following the child chain, or [] if `end` is not below `start`."""
    count = component.get_num_bones()
    for index in range(count):
        name = str(component.get_bone_name(index))
        if name != end:
            continue
        path = [name]
        current = name
        for _ in range(64):
            parent = str(component.get_parent_bone(unreal.Name(current)))
            if parent in ("None", ""):
                return []
            path.append(parent)
            current = parent
            if parent == start:
                return list(reversed(path))
        return []
    return []


def main():
    with open(CONFIG, encoding="utf-8") as handle:
        config = json.load(handle)

    sub_t, actor_t, comp_t = spawn_component(TARGET_MESH)
    sub_s, actor_s, comp_s = spawn_component(SOURCE_MESH)
    try:
        log("target bones=%d source bones=%d" % (
            comp_t.get_num_bones(), comp_s.get_num_bones()))
        for chain in config["chains"]:
            if not chain.get("retarget"):
                continue
            s_start, s_end = chain["source"]
            t_start, t_end = chain["target"]
            source_bones = bone_path(comp_s, s_start, s_end)
            target_bones = bone_path(comp_t, t_start, t_end)
            log("")
            log("%s  retarget=%s  rot=%s trans=%s" % (
                chain["name"], chain.get("retarget"),
                chain.get("rotation_mode", "default"),
                chain.get("translation_mode", "default")))
            log("  source %s..%s  (%d bones)" % (s_start, s_end, len(source_bones)))
            log("    " + " -> ".join(source_bones))
            log("  target %s..%s  (%d bones)" % (t_start, t_end, len(target_bones)))
            log("    " + " -> ".join(target_bones))
            likely_twist = [b for b in target_bones
                            if "twist" in b.lower() or "roll" in b.lower()]
            if likely_twist:
                log("  twist-like bones inside the target chain: %s" % ", ".join(likely_twist))
    finally:
        sub_t.destroy_actor(actor_t)
        sub_s.destroy_actor(actor_s)


try:
    main()
finally:
    with open(OUT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines) + "\n")
