"""Assign the Korinsna material instances to Hun_Body_Simple's slots (hardcoded)."""
import unreal

EAL = unreal.EditorAssetLibrary

MESH = "/HuaShira/Characters/Hero/Hero_Hun/SkinParts/Hun_Body_Simple"
MIS = [
    "/Game/Korinsna/Materials/MI_Korinsna_Cloth01",
    "/Game/Korinsna/Materials/MI_Korinsna_Cloth02",
    "/Game/Korinsna/Materials/MI_Korinsna_Hair01",
    "/Game/Korinsna/Materials/MI_Korinsna_Hair02",
    "/Game/Korinsna/Materials/MI_Korinsna_Face",
    "/Game/Korinsna/Materials/MI_Korinsna_Eyebrow",
    "/Game/Korinsna/Materials/MI_Korinsna_Eye",
    "/Game/Korinsna/Materials/MI_Korinsna_Emit",
]


def log(msg):
    unreal.log("KORINSNA: " + str(msg))
    try:
        with open(r"J:\VS_Projects\PBZ_KorinsnaSkinMod\extract\ue-assign-result.txt", "a", encoding="utf-8") as fh:
            fh.write(str(msg) + "\n")
    except Exception:
        pass


mesh = EAL.load_asset(MESH)
if mesh is None:
    raise SystemExit("mesh not found: " + MESH)

old = mesh.get_editor_property("materials")
log("existing slots: %d (%s)" % (len(old), [str(m.get_editor_property("material_slot_name")) for m in old]))

new_mats = []
for i, path in enumerate(MIS):
    mi = EAL.load_asset(path)
    if mi is None:
        log("WARNING missing " + path)
    entry = unreal.SkeletalMaterial()
    slot_name = "Korinsna_%02d" % i
    entry.set_editor_property("material_interface", mi)
    entry.set_editor_property("material_slot_name", slot_name)
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
