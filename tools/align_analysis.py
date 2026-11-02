"""Compare the Korinsna APOSE pose with the game skeleton's reference pose.

Prints how far the two skeletons agree under a best-fit similarity transform and
which Blender -> UE axis convention explains the numbers, so the FBX export can
be aligned in one shot instead of by trial and error.

Usage: python tools/align_analysis.py
"""
import json
import os
import re

import numpy as np

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REFBONES = os.path.join(ROOT, "extract", "dump", "refbones.txt")
APOSE = os.path.join(ROOT, "extract", "apose-dump.json")

# Hun bone -> Korinsna bone correspondences that exist on both rigs
PAIRS = [
    ("pelvis", "Bip001-Pelvis"),
    ("spine_01", "Bip001-Spine"),
    ("spine_05", "Bip001-Spine1"),
    ("neck_01", "Bip001-Neck"),
    ("Head", "head_Bone001"),
    ("clavicle_l", "Bip001-L-Clavicle"),
    ("upperarm_l", "Bip001-L-UpperArm"),
    ("lowerarm_l", "Bip001-L-Forearm"),
    ("hand_l", "Bip001-L-Hand"),
    ("clavicle_r", "Bip001-R-Clavicle"),
    ("upperarm_r", "Bip001-R-UpperArm"),
    ("lowerarm_r", "Bip001-R-Forearm"),
    ("hand_r", "Bip001-R-Hand"),
    ("thigh_l", "Bip001-L-Thigh"),
    ("calf_l", "Bip001-L-Calf"),
    ("foot_l", "Bip001-L-Foot"),
    ("ball_l", "Bip001-L-Toe0"),
    ("thigh_r", "Bip001-R-Thigh"),
    ("calf_r", "Bip001-R-Calf"),
    ("foot_r", "Bip001-R-Foot"),
    ("ball_r", "Bip001-R-Toe0"),
]

# the eight axis conventions a Blender -> UE conversion can plausibly use
AXIS_VARIANTS = {
    "(-y, x, z)": lambda p: np.stack([-p[:, 1], p[:, 0], p[:, 2]], axis=1),
    "( y,-x, z)": lambda p: np.stack([p[:, 1], -p[:, 0], p[:, 2]], axis=1),
    "(-y,-x, z)": lambda p: np.stack([-p[:, 1], -p[:, 0], p[:, 2]], axis=1),
    "( y, x, z)": lambda p: np.stack([p[:, 1], p[:, 0], p[:, 2]], axis=1),
    "(-x,-y, z)": lambda p: np.stack([-p[:, 0], -p[:, 1], p[:, 2]], axis=1),
    "( x, y, z)": lambda p: np.stack([p[:, 0], p[:, 1], p[:, 2]], axis=1),
    "(-x, y, z)": lambda p: np.stack([-p[:, 0], p[:, 1], p[:, 2]], axis=1),
    "( x,-y, z)": lambda p: np.stack([p[:, 0], -p[:, 1], p[:, 2]], axis=1),
}


def load_hun_refpose():
    lines = open(REFBONES, encoding="utf-8", errors="replace").read().splitlines()
    start = next(i for i, line in enumerate(lines) if line.startswith("== after-reset nb=")) + 1
    bones = {}
    for line in lines[start:]:
        if not line or not re.match(r"^\d+\|", line):
            break
        idx, name, parent, loc, quat, scale = line.split("|")
        bones[name] = {
            "parent": None if parent == "None" else parent,
            "loc": [float(v) for v in loc.split(",")],
            "quat": [float(v) for v in quat.split(",")],
        }
    return bones


def umeyama(src, dst):
    """Least-squares uniform scale + rotation + translation mapping src onto dst."""
    mu_s, mu_d = src.mean(0), dst.mean(0)
    sc, dc = src - mu_s, dst - mu_d
    sigma = dc.T @ sc / len(src)
    u, d, vt = np.linalg.svd(sigma)
    s = np.eye(3)
    if np.linalg.det(u) * np.linalg.det(vt) < 0:
        s[2, 2] = -1.0
    rot = u @ s @ vt
    var_s = (sc ** 2).sum() / len(src)
    scale = float(np.trace(np.diag(d) @ s) / var_s)
    trans = mu_d - scale * rot @ mu_s
    return scale, rot, trans


def euler_zyx(rot):
    """Report a rotation as yaw/pitch/roll in degrees (UE-ish order)."""
    import math
    sy = -rot[2, 0]
    sy = max(-1.0, min(1.0, sy))
    pitch = math.asin(sy)
    if abs(sy) < 0.999999:
        yaw = math.atan2(rot[1, 0], rot[0, 0])
        roll = math.atan2(rot[2, 1], rot[2, 2])
    else:
        yaw = math.atan2(-rot[0, 1], rot[1, 1])
        roll = 0.0
    return [round(math.degrees(v), 2) for v in (yaw, pitch, roll)]


def main():
    hun = load_hun_refpose()
    apose = json.load(open(APOSE, encoding="utf-8"))
    kor_pose = apose["armature"]["pose"]
    kor_rest = apose["armature"]["rest"]

    hun_xyz = np.array([b["loc"] for b in hun.values()], dtype=float)
    print("Hun reference pose (component space, cm)")
    print("  bones=%d  z range %.2f .. %.2f" % (len(hun), hun_xyz[:, 2].min(), hun_xyz[:, 2].max()))
    for name in ("Root", "pelvis", "Head", "hand_l", "hand_r", "foot_l", "foot_r", "ball_l", "ball_r"):
        if name in hun:
            print("  %-10s %s" % (name, np.round(hun[name]["loc"], 2)))

    kor_xyz = np.array([v["head"] for v in kor_pose.values()], dtype=float)
    print("\nKorinsna APOSE pose (Blender world)")
    print("  bones=%d  z range %.2f .. %.2f  x %.2f..%.2f  y %.2f..%.2f" % (
        len(kor_pose), kor_xyz[:, 2].min(), kor_xyz[:, 2].max(),
        kor_xyz[:, 0].min(), kor_xyz[:, 0].max(), kor_xyz[:, 1].min(), kor_xyz[:, 1].max()))
    rest_delta = max(
        max(abs(kor_rest[n]["head"][i] - kor_pose[n]["head"][i]) for i in range(3))
        for n in kor_rest)
    print("  rest vs pose max delta: %.3f" % rest_delta)

    names_h = [p[0] for p in PAIRS if p[0] in hun and p[1] in kor_pose]
    names_k = [p[1] for p in PAIRS if p[0] in hun and p[1] in kor_pose]
    print("  correspondences used: %d" % len(names_h))

    dst = np.array([hun[n]["loc"] for n in names_h], dtype=float)

    results = []
    for label, fn in AXIS_VARIANTS.items():
        src_world = np.array([kor_pose[n]["head"] for n in names_k], dtype=float)
        src = fn(src_world)
        scale, rot, trans = umeyama(src, dst)
        fitted = (scale * (rot @ src.T).T) + trans
        err = np.linalg.norm(fitted - dst, axis=1)
        results.append((float(err.mean()), float(err.max()), label, scale, rot, trans, err))

    results.sort()
    print("\nbest-fit similarity per axis convention (mean / max error in cm)")
    for mean_err, max_err, label, scale, rot, trans, _ in results:
        print("  %-12s mean %6.2f  max %6.2f  scale %.4f  yaw/pitch/roll %s" % (
            label, mean_err, max_err, scale, euler_zyx(rot)))

    mean_err, max_err, label, scale, rot, trans, err = results[0]
    print("\nchosen: %s" % label)
    print("  scale = %.6f" % scale)
    print("  rotation (yaw,pitch,roll deg) = %s" % euler_zyx(rot))
    print("  rotation matrix = %s" % np.round(rot, 5).tolist())
    print("  translation = %s" % np.round(trans, 3).tolist())
    print("  per bone error:")
    for name, e in zip(names_h, err):
        print("    %-12s %6.2f cm" % (name, e))

    # the mesh is 173.7 cm tall in world space; what scale does the fit want?
    print("\nmesh bounds (Blender world): %s .. %s" % (
        apose["objects"][0]["bounds_min"] if False else "", ""))
    for obj in apose["objects"]:
        if obj["type"] == "MESH":
            print("  %s  z %.2f .. %.2f  height %.2f  armature scale %s" % (
                obj["name"], obj["bounds_min"][2], obj["bounds_max"][2],
                obj["bounds_max"][2] - obj["bounds_min"][2],
                [o["scale"] for o in apose["objects"] if o["type"] == "ARMATURE"]))


if __name__ == "__main__":
    main()
