"""Build the Korinsna mod assets.

The host game only ships shaders for its own materials, so the mod never creates
materials: the imported mesh points at the hero's own material instances and the
textures those instances sample are replaced with Korinsna's maps.

Every parameter on the hero's master materials (`MA_Character`, `MAI_*`) is sampled
through a **virtual texture**. A plain texture bound to a VT sampler silently falls back
to the placeholder map, which is what made the face black and the cloth muddy, so every
override below is imported as a VT (and the small helper maps are generated at 256px,
one full VT tile).
"""
import unreal

AT = unreal.AssetToolsHelpers.get_asset_tools()
EAL = unreal.EditorAssetLibrary

TEX_DIR = "J:/VS_Projects/PBZ_KorinsnaSkinMod/KorinsnaModel/textures"

HOST_MI_DIR = "/Game/PBZContent/Characters/Hero/Hun_New_V2b/Material"
HOST_TEX_DIR = "/Game/PBZContent/Characters/Hero/Hun_New_V2b/Textures"
HOST_HEAD_TEX_DIR = HOST_TEX_DIR + "/HeadMerged"
HOST_HEAD_MI_DIR = HOST_MI_DIR + "/Hun_Status"
HOST_V2_MI_DIR = "/Game/PBZContent/Characters/Hero/Hun_New_V2/Material"
HOST_HUN_TEX_DIR = "/Game/Test/Zero_LookDev/ZeroFile/Character/Hun/Head/Textures"

# slot order follows the mesh's own material order:
#   0 dress, 1 body/trims, 2 front hair, 3 back hair, 4 face, 5 eyebrow, 6 eyes, 7 highlight
# Hair and face avoid MAI_Cloth (fabric weave detail) and MAI_Skin (subsurface colour map);
# those two only land on small trims where they do not read.
SLOTS = [
    "%s/MI_ZeroHun_Cloth_02_b" % HOST_MI_DIR,           # dress      (MAI_Cloth)
    "%s/MI_ZeroHun_Cloth_04_b" % HOST_MI_DIR,           # body       (MAI_Cloth)
    "%s/MI_ZeroHun_Cloth_03_b" % HOST_MI_DIR,           # front hair (MAI_Equipment)
    "%s/MI_ZeroHun_Cloth_01_b" % HOST_MI_DIR,           # back hair  (MAI_Equipment_Mask)
    "%s/MI_ZeroHun_Cap_01_b" % HOST_MI_DIR,             # face       (MAI_Equipment_Mask)
    "%s/MI_ZeroHun_Head_Injured30" % HOST_HEAD_MI_DIR,  # eyebrow    (MAI_Skin)
    "%s/MI_ZeroHun_Eye_01" % HOST_V2_MI_DIR,            # eyes       (MA_EyeRefractive)
    "%s/MI_ZeroHun_Cloth_05_b" % HOST_MI_DIR,           # highlight  (MAI_Cloth)
]

# (folder, texture name, our tga, kind) - kind drives the sampler settings
TEXTURES = [
    # albedo: one distinct host texture per slot
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_01_BC", "T_NPC_036_hair_02_d", "albedo"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_02_BC", "T_NPC_036_01_d", "albedo"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_03_BC", "T_NPC_036_hair_01_d", "albedo"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_04_BC", "T_NPC_036_02_d", "albedo"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_05_BC", "T_Korinsna_White", "albedo"),
    (HOST_TEX_DIR, "T_ZeroHun_Cap_V02_BC", "T_NPC_036_face_d", "albedo"),
    (HOST_HEAD_TEX_DIR, "T_ZeroHun_Head_D", "T_NPC_036_face_d", "albedo"),
    (HOST_HUN_TEX_DIR, "T_ZeroHun_Eye_D", "T_NPC_036_eyes_d", "albedo"),
    # neutral shading inputs so nothing tints, dirties or glosses the albedo
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_01_ARM", "T_Korinsna_ARM", "mask"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_02_ARM", "T_Korinsna_ARM", "mask"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_03_ARM", "T_Korinsna_ARM", "mask"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_04_ARM", "T_Korinsna_ARM", "mask"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_05_ARM", "T_Korinsna_ARM", "mask"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_01_N", "T_Korinsna_N", "normal"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_02_N", "T_Korinsna_N", "normal"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_03_N", "T_Korinsna_N", "normal"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_04_N", "T_Korinsna_N", "normal"),
    (HOST_TEX_DIR, "T_ZeroHun_Cloth_05_N", "T_Korinsna_N", "normal"),
    (HOST_TEX_DIR, "T_ZeroHun_Cap_V02_N", "T_Korinsna_N", "normal"),
    (HOST_HEAD_TEX_DIR, "T_ZeroHun_Head_N", "T_Korinsna_N", "normal"),
    (HOST_TEX_DIR, "T_ZeroHun_Head_Detail_N", "T_Korinsna_N", "normal"),
    (HOST_TEX_DIR, "T_ZeroHun_Head_V02_SCMT", "T_Korinsna_White", "mask"),
    (HOST_HUN_TEX_DIR, "T_ZeroHun_Head_DirtMask", "T_Korinsna_Black", "mask"),
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


def configure(tex, kind):
    """Match the way the host material samples this channel."""
    settings = {
        "albedo": (True, unreal.TextureCompressionSettings.TC_DEFAULT),
        "normal": (False, unreal.TextureCompressionSettings.TC_NORMALMAP),
        "mask": (False, unreal.TextureCompressionSettings.TC_DEFAULT),
    }[kind]
    tex.set_editor_property("srgb", settings[0])
    tex.set_editor_property("compression_settings", settings[1])
    tex.set_editor_property("virtual_texture_streaming", True)
    tex.set_editor_property("mip_gen_settings", unreal.TextureMipGenSettings.TMGS_SIMPLE_AVERAGE)


open(RESULT, "w").close()

# ---------------------------------------------------------------- texture overrides
for folder, name, tga, kind in TEXTURES:
    ensure_dir(folder)
    dest = "%s/%s" % (folder, name)
    delete_if_exists(dest)
    task = unreal.AssetImportTask()
    task.set_editor_property("filename", "%s/%s.tga" % (TEX_DIR, tga))
    task.set_editor_property("destination_path", folder)
    task.set_editor_property("destination_name", name)
    task.set_editor_property("automated", True)
    task.set_editor_property("replace_existing", True)
    task.set_editor_property("save", True)
    AT.import_asset_tasks([task])
    tex = EAL.load_asset(dest)
    if tex is None:
        log("texture FAILED %s <- %s" % (dest, tga))
        continue
    configure(tex, kind)
    EAL.save_loaded_asset(tex, False)
    log("texture %-7s %s <- %s" % (kind, dest, tga))

# ---------------------------------------------------------------- slot placeholders
# The host material instances live inside the game packages; stand-ins at the same paths let the mesh
# reference them, and the packing step drops every placeholder again - so at runtime the reference
# resolves to the game's own instance and the game's shader is used unchanged.
#
# The one thing that cannot be fixed this way is the Masked cutout: the host material reads an
# `OpacityMask` texture whose inherited default is a non-VT engine example map, which the virtual
# texture samplers fall back to the VT placeholder for (a dither pattern - the speckled, see-through
# look). Assets cannot be patched without a real parent, so the runtime script overrides that
# parameter through a dynamic material instance instead; see `force_opaque` in the UE4SS mod.
mi_slots = []
for mi_path in SLOTS:
    folder, name = mi_path.rsplit("/", 1)
    ensure_dir(folder)
    delete_if_exists(mi_path)
    mi = AT.create_asset(name, folder, unreal.MaterialInstanceConstant,
                         unreal.MaterialInstanceConstantFactoryNew())
    if mi is None:
        log("slot placeholder FAILED %s" % mi_path)
        mi_slots.append(None)
        continue
    EAL.save_loaded_asset(mi, False)
    mi_slots.append(mi_path)
log("slot placeholders: %d" % len([m for m in mi_slots if m]))

# ---------------------------------------------------------------- slot instances (disabled)
# Kept as a record of a dead end: a child instance whose parent is the placeholder renders as a flat
# untextured material in game, because the parent that the placeholder path resolves to at runtime does
# not hand over its texture parameters the way a real parent instance does. The mesh therefore points
# at the placeholder paths directly, which is the arrangement that renders correctly.
# The Masked cutout (`OpacityMask`) is left alone for now; see docs/TECHNICAL-GUIDE.md.

# ---------------------------------------------------------------- mesh
# The Korinsna body is a standalone asset with its own skeleton (built by
# ue/scripts/import_korinsna_sk.py); the hero's own Hun_Body_Simple is replaced by a degenerate
# mesh instead, so the game keeps animating its original skeleton and we retarget from it.
MESH = "/Game/Korinsna/SK_Korinsna"
mesh = EAL.load_asset(MESH)
if mesh is None:
    raise SystemExit("missing %s - run import_korinsna_sk.py first" % MESH)

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
