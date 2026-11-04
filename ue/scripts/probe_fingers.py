"""List the finger bone paths of both rigs (read-only).

Per-joint retarget chains must never share a bone and must end on the last bone *before* the joint, so
the exact parent chain of every phalanx matters. Writes extract/ue-finger-bones.txt.
"""
import os

import unreal

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
OUT = os.path.join(ROOT, "extract", "ue-finger-bones.txt")

TARGET_MESH = "/Game/Korinsna/SK_Korinsna"
SOURCE_MESH = "/Game/Korinsna/Source/HunSkin"

lines = []


def log(msg):
    lines.append(str(msg))


def spawn(mesh_path):
    mesh = unreal.EditorAssetLibrary.load_asset(mesh_path)
    if mesh is None:
        raise SystemExit("missing " + mesh_path)
    subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    actor = subsystem.spawn_actor_from_class(unreal.SkeletalMeshActor, unreal.Vector(0, 0, 0))
    component = actor.skeletal_mesh_component
    component.set_skeletal_mesh_asset(mesh)
    return subsystem, actor, component


def dump(label, mesh_path, keywords):
    subsystem, actor, component = spawn(mesh_path)
    try:
        log("=== %s (%d bones)" % (label, component.get_num_bones()))
        parents = {}
        order = []
        for index in range(component.get_num_bones()):
            name = str(component.get_bone_name(index))
            parents[name] = str(component.get_parent_bone(unreal.Name(name)))
            order.append(name)
        for name in order:
            lowered = name.lower()
            if not any(key in lowered for key in keywords):
                continue
            parent = parents[name]
            log("  %-26s parent=%s" % (name, parent))
    finally:
        subsystem.destroy_actor(actor)


try:
    dump("target / Korinsna", TARGET_MESH,
         ("finger", "thumb", "index", "middle", "ring", "pinky", "hand"))
    dump("source / Hun", SOURCE_MESH,
         ("thumb_", "index_", "middle_", "ring_", "pinky_", "hand_"))
finally:
    with open(OUT, "w", encoding="utf-8") as handle:
        handle.write("\n".join(lines) + "\n")
