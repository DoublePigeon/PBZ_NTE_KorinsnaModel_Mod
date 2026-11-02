"""Temporary diagnostic: override the host hero albedo textures with solid red."""
import unreal

AT = unreal.AssetToolsHelpers.get_asset_tools()
EAL = unreal.EditorAssetLibrary

TEX_DIR = "J:/VS_Projects/PBZ_KorinsnaSkinMod/extract/testtex"
HOST_TEX_DIR = "/Game/PBZContent/Characters/Hero/Hun_New_V2b/Textures"
NAMES = ["T_ZeroHun_Cloth_01_BC", "T_ZeroHun_Cloth_02_BC", "T_ZeroHun_Cloth_03_BC",
         "T_ZeroHun_Cloth_04_BC", "T_ZeroHun_Cloth_05_BC", "T_ZeroHun_Cap_V02_BC"]

for name in NAMES:
    dest = "%s/%s" % (HOST_TEX_DIR, name)
    if EAL.does_asset_exist(dest):
        EAL.delete_asset(dest)
    task = unreal.AssetImportTask()
    task.set_editor_property("filename", "%s/%s.tga" % (TEX_DIR, name))
    task.set_editor_property("destination_path", HOST_TEX_DIR)
    task.set_editor_property("destination_name", name)
    task.set_editor_property("automated", True)
    task.set_editor_property("replace_existing", True)
    task.set_editor_property("save", True)
    AT.import_asset_tasks([task])
    tex = EAL.load_asset(dest)
    unreal.log("REDTEST %s -> %s" % (dest, "ok" if tex else "fail"))
