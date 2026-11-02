"""Import the APOSE Korinsna FBX as a standalone skeletal mesh and dump its reference pose.

The mesh keeps its own `Bip001-*` skeleton: the game rig is never touched, animation comes
from the runtime IK retargeter instead.

Writes:
  extract/ue-sk-korinsna-refpose.json  bone name -> component-space translation
  extract/ue-skimport-result.txt       summary (bounds, skeleton, materials, key joints)
"""
import json
import os

import unreal

AT = unreal.AssetToolsHelpers.get_asset_tools()
EAL = unreal.EditorAssetLibrary

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
FBX = os.path.join(ROOT, "blender", "out", "Korinsna_APose.fbx").replace("\\", "/")
DEST = "/Game/Korinsna"
NAME = "SK_Korinsna"
RESULT = os.path.join(ROOT, "extract", "ue-skimport-result.txt")
POSE_OUT = os.path.join(ROOT, "extract", "ue-sk-korinsna-refpose.json")

INTERESTING = ("Root", "Bip001-Pelvis", "Bip001-Spine", "Bip001-Spine1", "Bip001-Neck",
               "head_Bone001", "Bip001-L-Hand", "Bip001-R-Hand", "Bip001-L-Foot",
               "Bip001-R-Foot", "Bip001-L-Toe0")


def main():
    dest = DEST + "/" + NAME
    if EAL.does_asset_exist(dest):
        EAL.delete_asset(dest)

    task = unreal.AssetImportTask()
    task.set_editor_property("filename", FBX)
    task.set_editor_property("destination_path", DEST)
    task.set_editor_property("destination_name", NAME)
    task.set_editor_property("automated", True)
    task.set_editor_property("replace_existing", True)
    task.set_editor_property("save", True)

    options = unreal.FbxImportUI()
    options.set_editor_property("import_mesh", True)
    options.set_editor_property("import_as_skeletal", True)
    options.set_editor_property("import_animations", False)
    options.set_editor_property("import_materials", False)
    options.set_editor_property("import_textures", False)
    options.set_editor_property("mesh_type_to_import", unreal.FBXImportType.FBXIT_SKELETAL_MESH)
    options.set_editor_property("create_physics_asset", False)
    smid = unreal.FbxSkeletalMeshImportData()
    smid.set_editor_property("import_morph_targets", False)
    options.set_editor_property("skeletal_mesh_import_data", smid)
    task.set_editor_property("options", options)

    AT.import_asset_tasks([task])

    mesh = EAL.load_asset(dest)
    if mesh is None:
        raise SystemExit("mesh import failed: " + dest)

    bounds = mesh.get_bounds()
    origin, extent = bounds.origin, bounds.box_extent
    skel = mesh.get_editor_property("skeleton")

    subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    actor = subsystem.spawn_actor_from_class(unreal.SkeletalMeshActor, unreal.Vector(0, 0, 0))
    comp = actor.skeletal_mesh_component
    comp.set_skeletal_mesh_asset(mesh)

    count = comp.get_num_bones()
    pose = {}
    for i in range(count):
        name = str(comp.get_bone_name(i))
        tr = comp.get_bone_transform(name, unreal.RelativeTransformSpace.RTS_COMPONENT)
        t = tr.translation
        pose[name] = [round(t.x, 4), round(t.y, 4), round(t.z, 4)]
    subsystem.destroy_actor(actor)

    with open(POSE_OUT, "w", encoding="utf-8") as fh:
        json.dump({"asset": dest, "bones": count, "refpose": pose}, fh, indent=1)

    lines = [
        "korinsna skeletal mesh import",
        "asset=%s" % dest,
        "skeleton=%s" % (skel.get_path_name() if skel else "None"),
        "bones=%d" % count,
        "materials=%d" % len(mesh.get_editor_property("materials")),
        "bounds origin (%.2f, %.2f, %.2f) extent (%.2f, %.2f, %.2f)" % (
            origin.x, origin.y, origin.z, extent.x, extent.y, extent.z),
        "bounds min z = %.2f  max z = %.2f" % (origin.z - extent.z, origin.z + extent.z),
    ]
    for name in INTERESTING:
        if name in pose:
            lines.append("  %-18s %s" % (name, pose[name]))
    with open(RESULT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))


main()
