"""Ship the Korinsna mesh as one of the hero's own part assets (the "carrier").

Why not a new asset path?
    Mod containers are mounted fine (texture overrides inside existing packages do apply), but
    UE4SS's only Lua loading entry point is LoadAsset, which resolves through the asset registry.
    The registry is built at cook time and never learns about packages that only exist in a mod
    container, so LoadAsset("/Game/Korinsna/SK_Korinsna") returns nil in the packaged game - and
    LoadObject / StaticLoadObject are not exposed to Lua at all.

    What does work is putting our mesh at a package path the game already asks for: the game then
    loads it, plus everything it references, as a normal dependency. So the mesh is shipped as
    SkinParts/Hun_Head_New (a part the runtime script takes over anyway) and the real head is
    simply hidden along with the rest of the original outfit.

How the retarget AnimBlueprint reaches the game
    The mesh carries it as PostProcessAnimBlueprint, which is a hard class reference, so cooking and
    loading the mesh pulls the AnimBlueprint - and through it the IK Retargeter and both IK Rigs -
    into memory. The runtime script then has a live class to point the component at.
"""
import json
import os

import unreal

AT = unreal.AssetToolsHelpers.get_asset_tools()
EAL = unreal.EditorAssetLibrary

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
FBX = os.path.join(ROOT, "blender", "out", "Korinsna_APose.fbx").replace("\\", "/")
RESULT = os.path.join(ROOT, "extract", "ue-carrier-result.txt")

DEST = "/HuaShira/Characters/Hero/Hero_Hun/SkinParts"
NAME = "Hun_Head_New"
SKELETON = "/Game/Korinsna/SK_Korinsna_Skeleton"
ANIM_BP = "/Game/Korinsna/ABP_Korinsna_Retarget"
TARGET_MESH = "/Game/Korinsna/SK_Korinsna"

lines = []


def log(msg):
    lines.append(str(msg))


def main():
    skeleton = EAL.load_asset(SKELETON)
    if skeleton is None:
        raise SystemExit("missing " + SKELETON + " (run import_korinsna_sk.py first)")
    anim_bp = EAL.load_asset(ANIM_BP)
    if anim_bp is None:
        raise SystemExit("missing " + ANIM_BP + " (run build_retarget_assets.py first)")

    path = DEST + "/" + NAME
    if EAL.does_asset_exist(path):
        existing = EAL.load_asset(path)
        if existing is not None:
            EAL.delete_loaded_asset(existing)
            unreal.SystemLibrary.collect_garbage()
    if EAL.does_asset_exist(path):
        raise SystemExit("could not clear " + path)

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
    # reuse the shared skeleton: Skeleton is read-only after import, and the retarget AnimBlueprint
    # is compiled against this exact skeleton asset
    options.set_editor_property("skeleton", skeleton)
    smid = unreal.FbxSkeletalMeshImportData()
    smid.set_editor_property("import_morph_targets", False)
    options.set_editor_property("skeletal_mesh_import_data", smid)
    task.set_editor_property("options", options)

    AT.import_asset_tasks([task])
    log("imported: %s" % [str(p) for p in task.get_editor_property("imported_object_paths")])

    mesh = EAL.load_asset(path)
    if mesh is None:
        raise SystemExit("carrier import failed")

    current = mesh.get_editor_property("skeleton")
    log("skeleton = %s" % (current.get_path_name() if current else "None"))
    if current is None or current.get_path_name() != skeleton.get_path_name():
        raise SystemExit("carrier mesh did not pick up %s" % skeleton.get_path_name())

    # the importer still writes a throwaway skeleton package next to the mesh
    for leftover in (DEST + "/" + NAME + "_Skeleton",):
        if EAL.does_asset_exist(leftover):
            asset = EAL.load_asset(leftover)
            if asset is not None:
                EAL.delete_loaded_asset(asset)
            unreal.SystemLibrary.collect_garbage()
            log("removed throwaway skeleton %s" % leftover)

    # the same material slots the standalone mesh uses
    donor = EAL.load_asset(TARGET_MESH)
    if donor is None:
        raise SystemExit("missing " + TARGET_MESH)
    slot_materials = []
    for entry in donor.get_editor_property("materials"):
        copied = unreal.SkeletalMaterial()
        copied.set_editor_property("material_interface", entry.get_editor_property("material_interface"))
        copied.set_editor_property("material_slot_name", entry.get_editor_property("material_slot_name"))
        slot_materials.append(copied)
    mesh.set_editor_property("materials", slot_materials)
    log("material slots copied: %d" % len(slot_materials))

    generated = anim_bp.generated_class()
    if generated is None:
        raise SystemExit("anim blueprint has no generated class")
    mesh.set_editor_property("post_process_anim_blueprint", generated)
    log("post process anim blueprint = %s" % generated.get_path_name())

    EAL.save_loaded_asset(mesh, False)

    result = {
        "asset": path,
        "mesh": mesh.get_path_name(),
        "skeleton": skeleton.get_path_name(),
        "anim_blueprint": generated.get_path_name(),
        "slots": len(slot_materials),
        "bones": None,
    }
    subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    actor = subsystem.spawn_actor_from_class(unreal.SkeletalMeshActor, unreal.Vector(0, 0, 0))
    comp = actor.skeletal_mesh_component
    comp.set_skeletal_mesh_asset(mesh)
    result["bones"] = comp.get_num_bones()
    subsystem.destroy_actor(actor)
    log("bones = %s" % result["bones"])

    with open(RESULT.replace(".txt", ".json"), "w", encoding="utf-8") as fh:
        json.dump(result, fh, indent=1)


try:
    main()
finally:
    with open(RESULT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))
