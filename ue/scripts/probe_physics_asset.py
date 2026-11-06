"""Prints what the generated cloth physics asset actually contains.

Written after a game test where hair stretched to the floor and the skirt vanished: at that point the
asset was hand-built and its constraints had no joint frames. This probe exists so the question
"does the asset hold the cloth bones at all?" is answered from the asset, not from a guess.

Usage:
  UnrealEditor-Cmd.exe <uproject> -ExecutePythonScript=ue/scripts/probe_physics_asset.py
"""

import os
import sys

import unreal

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
OUT = os.path.join(ROOT, "extract", "probe-physics-asset.txt")

ASSET = "/Game/Korinsna/PA_Korinsna_Cloth.PA_Korinsna_Cloth"
CLOTH_SAMPLES = ("l_skirt_1", "l_skirt_5", "b_skirt_1", "m_skirt_1",
                 "liuhai_1", "qianfa_1", "qianfa_39", "l_houfaA_1")
KINEMATIC_SAMPLES = ("Bip001-Pelvis", "Bip001-L-Thigh", "Bip001-L-Calf")

lines = []


def log(message):
    text = str(message)
    lines.append(text)
    unreal.log(text)


def main():
    asset = unreal.load_asset(ASSET)
    if asset is None:
        log("missing asset %s" % ASSET)
        return
    log("api: " + ", ".join(m for m in dir(asset) if not m.startswith("_")))
    try:
        bodies = asset.get_editor_property("skeletal_body_setups")
        constraints = asset.get_editor_property("constraint_setup")
        log("asset=%s bodies=%d constraints=%d" % (ASSET, len(bodies), len(constraints)))
    except Exception as error:  # noqa: BLE001 - diagnostic only
        log("editor-property read failed: %s" % error)
        return

    cloth_bodies, kinematic_bodies, other = 0, 0, 0
    names = []
    for body in bodies:
        if body is None:
            continue
        name = str(body.get_editor_property("bone_name"))
        names.append(name)
        physics_type = body.get_editor_property("physics_type")
        if str(physics_type) == "EPhysicsType.PHYS_TYPE_SIMULATED":
            cloth_bodies += 1
        elif str(physics_type) == "EPhysicsType.PHYS_TYPE_KINEMATIC":
            kinematic_bodies += 1
        else:
            other += 1
    log("simulated=%d kinematic=%d default=%d" % (cloth_bodies, kinematic_bodies, other))

    for sample in CLOTH_SAMPLES + KINEMATIC_SAMPLES:
        log("  %-18s body=%s" % (sample, "yes" if sample in names else "NO"))

    # constraint frames are the thing that was missing when the hair fell to the floor
    for index in range(min(len(constraints), 3)):
        template = constraints[index]
        instance = template.get_editor_property("default_instance")
        log("  constraint[%d] %s -> %s pos1=%s pri1=%s" % (
            index,
            instance.get_editor_property("constraint_bone_1"),
            instance.get_editor_property("constraint_bone_2"),
            instance.get_editor_property("pos1"),
            instance.get_editor_property("pri_axis1")))


main()

with open(OUT, "w", encoding="utf-8") as handle:
    handle.write("\n".join(lines))
sys.stdout.write("\n".join(lines))
