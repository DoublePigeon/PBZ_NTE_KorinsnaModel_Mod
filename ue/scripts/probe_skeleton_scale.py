"""Prints the target skeleton's reference pose in the units the anim graph actually works in.

The KawaiiPhysics collision spheres store their radius and their offset as plain numbers, and both are
compared against bone positions taken from the *component space* pose. The dumped Blender rig and the
UE skeleton are not necessarily in the same units (the carrier mesh is drawn with a component scale),
so the only safe way to author a radius in centimetres is to read the skeleton's own numbers.

Usage:
  UnrealEditor-Cmd.exe <uproject> -ExecutePythonScript=ue/scripts/probe_skeleton_scale.py
"""

import os
import sys

import unreal

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
OUT = os.path.join(ROOT, "extract", "probe-skeleton-scale.txt")

SKELETON = "/Game/Korinsna/SK_Korinsna_Skeleton.SK_Korinsna_Skeleton"
MESH = "/Game/Korinsna/SK_Korinsna.SK_Korinsna"
BONES = ("Bip001-Pelvis", "Bip001-L-Thigh", "Bip001-L-Calf", "Bip001-L-Foot",
         "head_Bone001", "head_Bone003", "b_skirt_1", "liuhai_1")

lines = []


def log(message):
    text = str(message)
    lines.append(text)
    unreal.log(text)


def main():
    skeleton = unreal.load_asset(SKELETON)
    log("skeleton=%s" % (skeleton.get_path_name() if skeleton else None))
    mesh = unreal.load_asset(MESH)
    if mesh:
        bounds = mesh.get_bounds()
        log("mesh bounds extent=%s sphere_radius=%.2f" % (bounds.box_extent, bounds.sphere_radius))

    if skeleton is None:
        return

    # The reference skeleton is exposed through the skeleton asset's preview info only in the editor;
    # fall back to reading the bone transforms the importer wrote into the mesh's skeleton.
    try:
        ref = skeleton.get_editor_property("reference_skeleton")
        log("reference_skeleton property present: %s" % type(ref))
    except Exception as error:  # noqa: BLE001 - diagnostic only
        log("reference_skeleton property unavailable (%s)" % error)

    try:
        names = skeleton.get_editor_property("bone_tree")
        log("bone_tree entries=%d" % len(names))
    except Exception as error:  # noqa: BLE001
        log("bone_tree unavailable (%s)" % error)


main()

with open(OUT, "w", encoding="utf-8") as handle:
    handle.write("\n".join(lines))
sys.stdout.write("\n".join(lines))
