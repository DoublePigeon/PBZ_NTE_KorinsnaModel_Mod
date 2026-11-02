"""Smoke test: import a skinned test mesh at the Hun body asset path and wire up assets."""
import unreal

AT = unreal.AssetToolsHelpers.get_asset_tools()
EAL = unreal.EditorAssetLibrary
MEL = unreal.MaterialEditingLibrary


def log(msg):
    unreal.log("KORINSNA: " + str(msg))


FBX = "J:/VS_Projects/PBZ_KorinsnaSkinMod/blender/out/TestSphere.fbx"
DEST = "/HuaShira/Characters/Hero/Hero_Hun/SkinParts"
SKEL_DIR = "/HuaShira/Characters/Hero/Hero_Hun"
MESH_NAME = "Hun_Body_Simple"
TARGET_SKEL = SKEL_DIR + "/Hun_Skin_Skeleton"

# 0. clean previous attempts
for path in [DEST + "/" + MESH_NAME, DEST + "/" + MESH_NAME + "_Skeleton", TARGET_SKEL]:
    if EAL.does_asset_exist(path):
        EAL.delete_asset(path)
        log("deleted " + path)

# 1. import mesh + its skeleton
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
options.set_editor_property("create_physics_asset", True)
task.set_editor_property("options", options)

AT.import_asset_tasks([task])
log("imported: %s" % [str(a) for a in task.get_editor_property("imported_object_paths")])

mesh = EAL.load_asset("%s/%s" % (DEST, MESH_NAME))
if mesh is None:
    raise SystemExit("mesh import failed")

skel = mesh.get_editor_property("skeleton")
skel_pkg = skel.get_path_name().split(".")[0]
log("imported skeleton pkg = %s" % skel_pkg)

if skel_pkg != TARGET_SKEL:
    ok = EAL.rename_asset(skel_pkg, TARGET_SKEL)
    log("rename ok = %s" % ok)

skel = mesh.get_editor_property("skeleton")
log("mesh skeleton now = %s" % skel.get_path_name())

# 2. test material (unlit magenta) in our own namespace
mat_dir = "/Game/Korinsna/Materials"
if not EAL.does_directory_exist(mat_dir):
    EAL.make_directory(mat_dir)
mat_path = mat_dir + "/M_Korinsna_Test"
if EAL.does_asset_exist(mat_path):
    EAL.delete_asset(mat_path)
mat = AT.create_asset("M_Korinsna_Test", mat_dir, unreal.Material, unreal.MaterialFactoryNew())
mat.set_editor_property("shading_model", unreal.MaterialShadingModel.MSM_UNLIT)
expr = MEL.create_material_expression(mat, unreal.MaterialExpressionVectorParameter, -350, 0)
expr.set_editor_property("parameter_name", "TestColor")
expr.set_editor_property("default_value", unreal.LinearColor(1.0, 0.0, 1.0, 1.0))
MEL.connect_material_property(expr, "", unreal.MaterialProperty.MP_EMISSIVE_COLOR)
MEL.recompile_material(mat)
EAL.save_loaded_asset(mat, False)
log("material = %s" % mat.get_path_name())

mats = mesh.get_editor_property("materials")
log("material slots = %d" % len(mats))
if len(mats) > 0:
    mats[0].set_editor_property("material_interface", mat)
    mesh.set_editor_property("materials", mats)
    log("assigned test material")

EAL.save_loaded_asset(mesh, False)
EAL.save_directory("/HuaShira", only_if_is_dirty=False, recursive=True)
EAL.save_directory("/Game/Korinsna", only_if_is_dirty=False, recursive=True)
log("done")
