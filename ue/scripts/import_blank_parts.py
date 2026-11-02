"""Overwrite the hero's own part meshes with a degenerate (zero-area) mesh.

Why at asset level instead of at runtime
    The runtime script cannot reliably hide the hero's parts: the body component also carries the
    robe and the hair, and it has to stay animating because it is the retarget pose source, so it can
    never be hidden outright. Blanking the *meshes* sidesteps the problem entirely - there is nothing
    left to render, whatever actor loads them.

Why this does not break the animation
    Every blank mesh keeps the game's own skeleton (`/HuaShira/.../Hun_Skin_Skeleton`), so the hero's
    AnimBP still runs on the body component exactly as before: the pose the retargeter copies from is
    unchanged. Only the geometry is gone.

Why the skeleton is only referenced, never shipped
    `tools/stage_iostore.ps1` drops `Hun_Skin_Skeleton` from the container. The reference inside each
    blank mesh therefore resolves to the copy that is already in the game - the one the hero's
    AnimBP was compiled against.

Weapons are deliberately not blanked.
"""
import os

import unreal

AT = unreal.AssetToolsHelpers.get_asset_tools()
EAL = unreal.EditorAssetLibrary

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
BLANK_FBX = os.path.join(ROOT, "blender", "out", "BlankPart.fbx").replace("\\", "/")
# the body needs its own blank mesh: one built from the game's own bone hierarchy, so its bone list
# matches the real body exactly (see the note on BLANKED)
BLANK_BODY_FBX = os.path.join(ROOT, "blender", "out", "BlankBody.fbx").replace("\\", "/")
# the shipped body mesh resolves to 274 bones at runtime (265 real + 9 virtual from the skeleton)
EXPECTED_BODY_BONES = 274
RESULT = os.path.join(ROOT, "extract", "ue-blank-result.txt")

HERO = "/HuaShira/Characters/Hero/Hero_Hun"
SKELETON = HERO + "/Hun_Skin_Skeleton"

# Everything the hero's outfit is made of. Hun_Head_New is absent on purpose: it is the carrier that
# ships the Korinsna model. Weapons (Weapon/...) are never touched.
#
# Hun_Body_Simple is NOT blanked. Replacing it with a rebuilt blank mesh made the hero's AnimBP
# incompatible (bone list differed), which costs both the pose and the weapon sockets; and building a
# blank mesh whose bone list matches exactly is fragile. It is hidden at runtime instead
# (`hide_source_visibility` + `force_anim_refresh` in the UE4SS mod), which keeps the real mesh - and
# therefore its animation, sockets and physics - intact.
BLANKED = [
    (HERO + "/SkinParts", "Hun_Body"),
    (HERO + "/SkinParts", "Hun_Cloth"),
    (HERO + "/SkinParts", "Hun_Hair"),
    (HERO + "/SkinParts", "Hun_Rope01"),
    (HERO + "/SkinParts", "Hun_Scarf_Climax"),
    (HERO + "/SkinParts", "Hun_BrowLashCardMoQu"),
    (HERO + "/SkinParts", "Hun_Head"),
    (HERO + "/SkinParts", "Hun_UpBody"),
    (HERO + "/SkinParts", "Hun_DownBody"),
    (HERO + "/SkinParts", "Hun_Waistless"),
    (HERO + "/SkinParts", "Hun_FrontBelt"),
    (HERO + "/SkinParts", "Hun_UpCloth"),
    (HERO + "/SkinParts", "Hun_DownCloth"),
    (HERO + "/SkinParts", "Hun_FrontCloth"),
    (HERO + "/SkinParts", "Hun_Cape"),
    (HERO + "/SkinParts", "Hun_Scarf"),
    (HERO + "/SkinParts", "Hun_Hair_Band"),
    (HERO + "/SkinParts", "Hun_BrowLashCard"),
    (HERO + "/SkinParts", "Hun_Hat"),
    (HERO + "/Hats", "Hun_Hat_00"),
]

lines = []


def log(msg):
    lines.append(str(msg))


def discard(path):
    if EAL.does_asset_exist(path):
        asset = EAL.load_asset(path)
        if asset is not None:
            EAL.delete_loaded_asset(asset)
        unreal.SystemLibrary.collect_garbage()
    return not EAL.does_asset_exist(path)


def blank(folder, name, fbx):
    path = folder + "/" + name
    if not discard(path):
        log("FAILED   could not clear %s" % path)
        return False
    if not EAL.does_directory_exist(folder):
        EAL.make_directory(folder)

    task = unreal.AssetImportTask()
    task.set_editor_property("filename", fbx)
    task.set_editor_property("destination_path", folder)
    task.set_editor_property("destination_name", name)
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
    # the game's own skeleton: the hero's AnimBP is compiled against this exact asset
    options.set_editor_property("skeleton", skeleton)
    options.set_editor_property("skeletal_mesh_import_data",
                                unreal.FbxSkeletalMeshImportData())
    task.set_editor_property("options", options)

    AT.import_asset_tasks([task])

    mesh = EAL.load_asset(path)
    if mesh is None:
        log("FAILED   import produced nothing at %s" % path)
        return False

    actual = mesh.get_editor_property("skeleton")
    actual_path = actual.get_path_name().split(".")[0] if actual else "None"
    if actual_path != SKELETON:
        log("FAILED   %s got skeleton %s" % (path, actual_path))
        return False

    # a zero-area triangle still needs a material slot or the component may refuse to draw it at all
    slots = mesh.get_editor_property("materials")
    bones = None
    subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    actor = subsystem.spawn_actor_from_class(unreal.SkeletalMeshActor, unreal.Vector(0, 0, 0))
    try:
        component = actor.skeletal_mesh_component
        component.set_skeletal_mesh_asset(mesh)
        bones = component.get_num_bones()
    except Exception as exc:  # noqa: BLE001
        log("    bone count failed: %s" % exc)
    finally:
        subsystem.destroy_actor(actor)

    log("blanked  %s (slots=%d, bones=%s, skeleton=%s)"
        % (path, len(slots), bones, actual_path))

    # the importer drops a throwaway skeleton package next to the mesh
    for leftover in (folder + "/" + name + "_Skeleton",):
        if EAL.does_asset_exist(leftover):
            discard(leftover)
    return True


def main():
    global skeleton
    skeleton = EAL.load_asset(SKELETON)
    if skeleton is None:
        raise SystemExit(
            "missing %s - run ue/scripts/import_hun_skeleton.py first" % SKELETON)
    log("skeleton = %s" % skeleton.get_path_name())

    # Hun_Body_Simple stays the real game mesh (see the note on BLANKED)
    restored = HERO + "/SkinParts/Hun_Body_Simple"
    if EAL.does_asset_exist(restored):
        if discard(restored):
            log("restored %s (override deleted)" % restored)
        else:
            log("FAILED   could not delete %s" % restored)

    ok = 0
    for folder, name in BLANKED:
        fbx = BLANK_BODY_FBX if name == "Hun_Body_Simple" else BLANK_FBX
        if blank(folder, name, fbx):
            ok += 1
    log("blanked %d of %d" % (ok, len(BLANKED)))

    EAL.save_directory(HERO, only_if_is_dirty=False, recursive=True)
    log("saved %s" % HERO)


try:
    main()
finally:
    with open(RESULT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))
    print("\n".join(lines))
