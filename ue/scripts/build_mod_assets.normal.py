"""Build the Korinsna mod assets.

The host game only has shaders for its own materials, so the mod never ships
materials of its own: the mesh re-uses the host material instances for the hero
body and the host textures they sample are overridden with our own maps.

- imports the rigged FBX as Hun_Body_Simple on the host skeleton path
- assigns the host material instances to the imported mesh slots
"""
import unreal

AT = unreal.AssetToolsHelpers.get_asset_tools()
EAL = unreal.EditorAssetLibrary

FBX = "J:/VS_Projects/PBZ_KorinsnaSkinMod/blender/out/Korinsna_Body.fbx"
TEX_DIR = "J:/VS_Projects/PBZ_KorinsnaSkinMod/KorinsnaModel/textures"

SKEL_DIR = "/HuaShira/Characters/Hero/Hero_Hun"
DEST = SKEL_DIR + "/SkinParts"
MESH_NAME = "Hun_Body_Simple"
TARGET_SKEL = SKEL_DIR + "/Hun_Skin_Skeleton"

HOST_MI_DIR = "/Game/PBZContent/Characters/Hero/Hun_New_V2b/Material"
HOST_TEX_DIR = "/Game/PBZContent/Characters/Hero/Hun_New_V2b/Textures"
HOST_HEAD_MI_DIR = "/Game/PBZContent/Characters/Hero/Hun_New_V2b/Material/Hun_Status"
HOST_V2_MI_DIR = "/Game/PBZContent/Characters/Hero/Hun_New_V2/Material"

HOST_HEAD_TEX_DIR = HOST_TEX_DIR + "/HeadMerged"
HOST_EYE_TEX_DIR = "/Game/Test/Zero_LookDev/ZeroFile/Character/Hun/Head/Textures"
HOST_HUN_TEX_DIR = HOST_EYE_TEX_DIR

# slot -> host material instance path (the game rebuilds a dynamic instance from it)
SLOTS = [
    "%s/MI_ZeroHun_Cloth_01_b" % HOST_MI_DIR,
    "%s/MI_ZeroHun_Cloth_02_b" % HOST_MI_DIR,
    "%s/MI_ZeroHun_Cloth_03_b" % HOST_MI_DIR,
    "%s/MI_ZeroHun_Cloth_04_b" % HOST_MI_DIR,
    "%s/MI_ZeroHun_Cloth_05_b" % HOST_MI_DIR,
    "%s/MI_ZeroHun_Cap_01_b" % HOST_MI_DIR,
    "%s/MI_ZeroHun_Head_Injured30" % HOST_HEAD_MI_DIR,
    "%s/MI_ZeroHun_Eye_01" % HOST_V2_MI_DIR,
]

# (host texture folder, host texture name, our tga) - the host "Albedo" parameter of
# each material slot is replaced with the matching Korinsna map.
TEXTURES = [
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_01_BC", "T_NPC_036_01_d"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_02_BC", "T_NPC_036_02_d"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_03_BC", "T_NPC_036_hair_01_d"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_04_BC", "T_NPC_036_hair_02_d"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_05_BC", "T_NPC_036_face_d"),
    (HOST_TEX_DIR, "T_ZeroHun_Cap_V02_BC", "T_NPC_036_face_d"),
    (HOST_HEAD_TEX_DIR, "T_ZeroHun_Head_D", "T_NPC_036_face_d"),
    (HOST_EYE_TEX_DIR, "T_ZeroHun_Eye_D", "T_NPC_036_eyes_d"),
    # the host materials are masked by their Mix/Normal maps; Korinsna's UV layout does
    # not match the host maps, so neutral maps keep the geometry visible.
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_01_ARM", "T_Korinsna_ARM"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_02_ARM", "T_Korinsna_ARM"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_03_ARM", "T_Korinsna_ARM"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_04_ARM", "T_Korinsna_ARM"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_05_ARM", "T_Korinsna_ARM"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_01_N", "T_Korinsna_N"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_02_N", "T_Korinsna_N"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_03_N", "T_Korinsna_N"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_04_N", "T_Korinsna_N"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_05_N", "T_Korinsna_N"),
    (HOST_TEX_DIR, "T_ZeroHun_Cap_V02_N", "T_Korinsna_N"),
    (HOST_HEAD_TEX_DIR, "T_ZeroHun_Head_N", "T_Korinsna_N"),
    # grime / detail maps authored for the host body do not line up with our UVs
    (HOST_HEAD_TEX_DIR, "T_ZeroHun_Head_Detail_N", "T_Korinsna_N"),
    (HOST_HUN_TEX_DIR, "T_ZeroHun_Head_DirtMask", "T_Korinsna_Black"),
]

RESULT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod\extract\ue-buildassets-result.txt"


def log(msg):
    with open(RESULT, "a", encoding="utf-8") as fh:
        fh.write(str(msg) + "\n")


def ensure_dir(path):
    if not EAL.does_directory_exist(path):
        EAL.make_directory(path)


def delete_if_exists(path):
    if EAL.does_asset_exist(path):
        EAL.delete_asset(path)


open(RESULT, "w").close()

# ---------------------------------------------------------------- texture overrides
for tex_dir, tex_name, tga in TEXTURES:
    ensure_dir(tex_dir)
    dest = "%s/%s" % (tex_dir, tex_name)
    delete_if_exists(dest)
    task = unreal.AssetImportTask()
    task.set_editor_property("filename", "%s/%s.tga" % (TEX_DIR, tga))
    task.set_editor_property("destination_path", tex_dir)
    task.set_editor_property("destination_name", tex_name)
    task.set_editor_property("automated", True)
    task.set_editor_property("replace_existing", True)
    task.set_editor_property("save", True)
    AT.import_asset_tasks([task])
    tex = EAL.load_asset(dest)
    if tex is not None and tex_name.endswith("_BC"):
        # the host master materials sample the albedo as a virtual texture
        for prop, value in (("virtual_texture_streaming", True),):
            try:
                tex.set_editor_property(prop, value)
            except Exception as exc:
                log("  %s set failed: %s" % (prop, exc))
        EAL.save_loaded_asset(tex, False)
    log("texture override %s <- %s (%s)" % (dest, tga, "ok" if tex else "FAILED"))

# ---------------------------------------------------------------- slot placeholders
# The host material instances only exist inside the game packages. We create stand-in
# assets at the exact host paths so the mesh can reference them, then the pack step
# drops every placeholder so the game keeps its own (shader-compatible) materials.
mi_slots = []
for i, mi_path in enumerate(SLOTS):
    folder, name = mi_path.rsplit("/", 1)
    ensure_dir(folder)
    delete_if_exists(mi_path)
    mi = AT.create_asset(name, folder, unreal.MaterialInstanceConstant,
                         unreal.MaterialInstanceConstantFactoryNew())
    if mi is None:
        log("slot placeholder FAILED " + mi_path)
        mi_slots.append(None)
        continue
    EAL.save_loaded_asset(mi, False)
    mi_slots.append(mi_path)
    log("slot placeholder %s" % mi_path)

# ---------------------------------------------------------------- mesh
for path in [DEST + "/" + MESH_NAME, DEST + "/" + MESH_NAME + "_Skeleton", TARGET_SKEL]:
    delete_if_exists(path)

task = unreal.AssetImportTask()
task.set_editor_property("filename", FBX)
task.set_editor_property("destination_path", DEST)
task.set_editor_property("destination_name", MESH_NAME)
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
log("imported: %s" % [str(a) for a in task.get_editor_property("imported_object_paths")])

mesh = EAL.load_asset("%s/%s" % (DEST, MESH_NAME))
if mesh is None:
    raise SystemExit("mesh import failed")

skel = mesh.get_editor_property("skeleton")
skel_pkg = skel.get_path_name().split(".")[0] if skel else None
log("imported skeleton: %s" % skel_pkg)
if skel_pkg and skel_pkg != TARGET_SKEL:
    log("skeleton renamed: %s" % EAL.rename_asset(skel_pkg, TARGET_SKEL))

# ---------------------------------------------------------------- assign material slots
new_mats = []
for i, mi_path in enumerate(mi_slots):
    mi = EAL.load_asset(mi_path) if mi_path else None
    if mi is None:
        log("slot material missing: %s" % mi_path)
    entry = unreal.SkeletalMaterial()
    entry.set_editor_property("material_interface", mi)
    entry.set_editor_property("material_slot_name", "Korinsna_%02d" % i)
    new_mats.append(entry)
mesh.set_editor_property("materials", new_mats)
EAL.save_loaded_asset(mesh, False)

check = mesh.get_editor_property("materials")
log("assigned slots: %d" % len(check))
for i, m in enumerate(check):
    mi = m.get_editor_property("material_interface")
    log("  [%d] -> %s" % (i, mi.get_path_name() if mi else "None"))
log("done")