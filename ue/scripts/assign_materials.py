"""Assign material interfaces to a skeletal mesh's material slots by index.

Usage:
  UnrealEditor-Cmd.exe <uproject> -ExecutePythonScript="assign_materials.py" --
    <mesh_package_path> <mi_path_0> [mi_path_1 ...]
"""
import sys
import unreal

EAL = unreal.EditorAssetLibrary
AT = unreal.AssetToolsHelpers.get_asset_tools()

argv = sys.argv
argv = argv[argv.index("--") + 1:] if "--" in argv else []
mesh_path = argv[0]
mi_paths = argv[1:]


def log(msg):
    unreal.log("KORINSNA: " + str(msg))


mesh = EAL.load_asset(mesh_path)
if mesh is None:
    raise SystemExit("mesh not found: " + mesh_path)

mats = mesh.get_editor_property("materials")
log("existing slots: %d" % len(mats))

new_mats = []
for i, mi_path in enumerate(mi_paths):
    mi = EAL.load_asset(mi_path)
    if mi is None:
        log("WARNING: missing material %s" % mi_path)
    slot_name = "Korinsna_%02d" % i
    entry = unreal.SkeletalMaterial()
    entry.set_editor_property("material_interface", mi)
    entry.set_editor_property("material_slot_name", slot_name)
    entry.set_editor_property("imported_material_slot_name", slot_name)
    new_mats.append(entry)

mesh.set_editor_property("materials", new_mats)
EAL.save_loaded_asset(mesh, False)

check = mesh.get_editor_property("materials")
log("new slots: %d" % len(check))
for i, m in enumerate(check):
    mi = m.get_editor_property("material_interface")
    log("  [%d] %s -> %s" % (i, m.get_editor_property("material_slot_name"),
                             mi.get_path_name() if mi else "None"))
log("done")
