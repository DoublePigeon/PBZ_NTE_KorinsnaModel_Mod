"""Create the game skeleton asset inside the project, at the game's own asset path.

The hero's own body parts are replaced with degenerate meshes (import_blank_parts.py) and those
meshes must reference `/HuaShira/.../Hun_Skin_Skeleton`. In the packaged mod that asset is *not*
shipped (overwriting the real skeleton crashes the game), so the reference simply resolves to the
game's own copy - but the editor still needs a local skeleton to import against.

`blender/out/Korinsna_Body.fbx` is already rigged to a skeleton that carries every bone name the
game uses, so it doubles as a donor: import it, take its skeleton, rename that to the game path,
and leave the mesh behind as the blank-part source.
"""
import os

import unreal

AT = unreal.AssetToolsHelpers.get_asset_tools()
EAL = unreal.EditorAssetLibrary

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
RESULT = os.path.join(ROOT, "extract", "ue-hunskeleton-result.txt")

GAME_DIR = "/HuaShira/Characters/Hero/Hero_Hun"
GAME_SKEL = GAME_DIR + "/Hun_Skin_Skeleton"
DONOR_FBX = os.path.join(ROOT, "blender", "out", "Korinsna_Body.fbx")
DONOR_NAME = "HunSkeletonDonor"

lines = []


def log(msg):
    lines.append(str(msg))


def asset_class(path):
    try:
        return str(EAL.find_asset_data(path).asset_class_path.asset_name)
    except Exception:  # noqa: BLE001
        return "?"


def discard(path):
    if EAL.does_asset_exist(path):
        asset = EAL.load_asset(path)
        if asset is not None:
            EAL.delete_loaded_asset(asset)
        unreal.SystemLibrary.collect_garbage()
    return not EAL.does_asset_exist(path)


def move_aside(path):
    if not EAL.does_asset_exist(path):
        return
    log("removing %s (%s)" % (path, asset_class(path)))
    if discard(path):
        return
    counter = 0
    while EAL.does_asset_exist("%s_stale%d" % (path, counter)):
        counter += 1
    moved = "%s_stale%d" % (path, counter)
    EAL.rename_asset(path, moved)
    log("  moved to %s" % moved)


def main():
    if not EAL.does_directory_exist(GAME_DIR):
        EAL.make_directory(GAME_DIR)

    for path in (GAME_SKEL, GAME_DIR + "/" + DONOR_NAME, GAME_DIR + "/" + DONOR_NAME + "_Skeleton"):
        move_aside(path)

    task = unreal.AssetImportTask()
    task.set_editor_property("filename", DONOR_FBX.replace("\\", "/"))
    task.set_editor_property("destination_path", GAME_DIR)
    task.set_editor_property("destination_name", DONOR_NAME)
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
    log("imported: %s" % [str(p) for p in task.get_editor_property("imported_object_paths")])

    donor = EAL.load_asset(GAME_DIR + "/" + DONOR_NAME)
    if donor is None:
        raise SystemExit("donor import failed")
    skeleton = donor.get_editor_property("skeleton")
    if skeleton is None:
        raise SystemExit("donor has no skeleton")
    skeleton_path = skeleton.get_path_name().split(".")[0]
    log("donor skeleton: %s" % skeleton_path)

    if skeleton_path != GAME_SKEL:
        log("rename %s -> %s : %s" % (skeleton_path, GAME_SKEL,
                                      EAL.rename_asset(skeleton_path, GAME_SKEL)))

    # the donor mesh is only a bone-name carrier: don't leave it in the plugin folder, everything
    # under /HuaShira is staged into the shipped container
    for path in list(EAL.list_assets(GAME_DIR, recursive=False)):
        name = path.rsplit("/", 1)[1].split(".")[0]
        if name.startswith(DONOR_NAME) or name.startswith("Hun_Skin_Skeleton_"):
            log("discarding leftover %s (%s)" % (path, asset_class(path)))
            if not discard(path):
                EAL.rename_asset(path, "/Game/KorinsnaStale/" + name)

    log("game skeleton class: %s" % asset_class(GAME_SKEL))
    log("skeleton asset present: %s" % EAL.does_asset_exist(GAME_SKEL))
    log("folder now: %s" % sorted(EAL.list_assets(GAME_DIR, recursive=False)))


try:
    main()
finally:
    with open(RESULT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))
