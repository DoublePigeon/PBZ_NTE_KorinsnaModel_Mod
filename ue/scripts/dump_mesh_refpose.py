"""Dump a skeletal mesh's reference pose in component space, for offline alignment checks.

Spawns a throwaway SkeletalMeshActor (the only way the Python API exposes a skeletal mesh
component) and writes every bone's component-space translation plus the mesh bounds.

Usage: UnrealEditor-Cmd.exe <project> -ExecutePythonScript="dump_mesh_refpose.py <objectPath> <outJson>"
"""
import json
import os
import sys

import unreal

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
argv = []
try:
    argv = [a for a in sys.argv if a and not a.startswith("-")]
except Exception:  # noqa: BLE001
    argv = []

asset_path = "/Game/Korinsna/SK_Korinsna"
out_path = os.path.join(ROOT, "extract", "ue-mesh-refpose.json")
for index, value in enumerate(argv):
    if value.startswith("/Game/"):
        asset_path = value
        if index + 1 < len(argv) and argv[index + 1].lower().endswith(".json"):
            out_path = argv[index + 1]


def main():
    mesh = unreal.EditorAssetLibrary.load_asset(asset_path)
    if mesh is None:
        raise SystemExit("missing " + asset_path)

    subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    actor = subsystem.spawn_actor_from_class(unreal.SkeletalMeshActor, unreal.Vector(0, 0, 0))
    comp = actor.skeletal_mesh_component
    comp.set_skeletal_mesh_asset(mesh)

    pose = {}
    for i in range(comp.get_num_bones()):
        name = str(comp.get_bone_name(i))
        tr = comp.get_bone_transform(name, unreal.RelativeTransformSpace.RTS_COMPONENT)
        t = tr.translation
        pose[name] = [round(t.x, 4), round(t.y, 4), round(t.z, 4)]
    subsystem.destroy_actor(actor)

    bounds = mesh.get_bounds()
    o, e = bounds.origin, bounds.box_extent
    with open(out_path, "w", encoding="utf-8") as fh:
        json.dump({
            "asset": mesh.get_path_name(),
            "bones": len(pose),
            "bounds_min": [o.x - e.x, o.y - e.y, o.z - e.z],
            "bounds_max": [o.x + e.x, o.y + e.y, o.z + e.z],
            "refpose": pose,
        }, fh, indent=1)


main()
