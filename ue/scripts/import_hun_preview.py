"""Import a mesh that carries the game's own 274-bone skeleton, for editor-side IK Rig authoring.

The IK Rigs and the IK Retargeter are authored against skeleton *names*; the runtime retarget
processor resolves those names against whatever mesh the game actually has on screen. That only
works if our authoring skeleton uses exactly the game's bone names, so this script imports the
mesh and verifies the names against the reference dump.

Writes extract/ue-hunpreview-result.txt.
"""
import json
import os

import unreal

AT = unreal.AssetToolsHelpers.get_asset_tools()
EAL = unreal.EditorAssetLibrary

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
FBX = os.path.join(ROOT, "blender", "out", "Korinsna_Body.fbx").replace("\\", "/")
DEST = "/Game/Korinsna/Source"
NAME = "HunSkin"
RESULT = os.path.join(ROOT, "extract", "ue-hunpreview-result.txt")
REFBONES = os.path.join(ROOT, "extract", "dump", "refbones.txt")


def game_bone_names():
    lines = open(REFBONES, encoding="utf-8", errors="replace").read().splitlines()
    start = next(i for i, line in enumerate(lines) if line.startswith("== after-reset nb=")) + 1
    names = []
    for line in lines[start:]:
        if not line or not line[:1].isdigit() or "|" not in line:
            break
        names.append(line.split("|")[1])
    return names


def main():
    if not EAL.does_directory_exist(DEST):
        EAL.make_directory(DEST)
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
    task.set_editor_property("options", options)
    AT.import_asset_tasks([task])

    mesh = EAL.load_asset(dest)
    lines = ["hun preview mesh import", "asset=%s" % dest]
    if mesh is None:
        lines.append("FAILED")
    else:
        subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
        actor = subsystem.spawn_actor_from_class(unreal.SkeletalMeshActor, unreal.Vector(0, 0, 0))
        comp = actor.skeletal_mesh_component
        comp.set_skeletal_mesh_asset(mesh)
        imported = [str(comp.get_bone_name(i)) for i in range(comp.get_num_bones())]
        subsystem.destroy_actor(actor)

        expected = game_bone_names()
        missing = [n for n in expected if n not in imported]
        extra = [n for n in imported if n not in expected]
        lines.append("imported bones=%d  game bones=%d" % (len(imported), len(expected)))
        lines.append("missing from import: %s" % (missing or "none"))
        lines.append("not in game rig: %s" % (extra or "none"))
        lines.append("skeleton=%s" % mesh.get_editor_property("skeleton").get_path_name())
        with open(os.path.join(ROOT, "extract", "ue-hunpreview-bones.json"), "w", encoding="utf-8") as fh:
            json.dump(imported, fh)

    with open(RESULT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))


main()
