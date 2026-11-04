"""Read-only probe: dump the chain set on both IK rigs, the retargeter chain mappings and the FK Chains
op's per-chain settings. Used to find out why auto_align_all_bones asserts after the limbs were split
into per-joint chains ("Bone should never be retargeted and not in a mapped chain").

Writes extract/ue-probe-chains.txt.
"""
import os

import unreal

EAL = unreal.EditorAssetLibrary
ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
RESULT = os.path.join(ROOT, "extract", "ue-probe-chains.txt")

IKR_SOURCE = "/Game/Korinsna/IKR_Hun"
IKR_TARGET = "/Game/Korinsna/IKR_Korinsna"
RETARGETER = "/Game/Korinsna/RTG_HunToKorinsna"

lines = []


def log(msg):
    lines.append(str(msg))


def dump_rig(path):
    log("=== " + path)
    if not EAL.does_asset_exist(path):
        log("  missing")
        return
    rig = EAL.load_asset(path)
    controller = unreal.IKRigController.get_controller(rig)
    chains = controller.get_retarget_chains()
    log("  chain count: %d" % len(chains))
    for chain in chains:
        name = chain.get_editor_property("chain_name")
        start = chain.get_editor_property("start_bone")
        end = chain.get_editor_property("end_bone")
        log("    %-22s %s .. %s" % (str(name), str(start), str(end)))


def main():
    dump_rig(IKR_SOURCE)
    dump_rig(IKR_TARGET)

    log("=== " + RETARGETER)
    if not EAL.does_asset_exist(RETARGETER):
        log("  missing")
    else:
        rtg_asset = EAL.load_asset(RETARGETER)
        rtg = unreal.IKRetargeterController.get_controller(rtg_asset)
        log("  ops: %d" % rtg.get_num_retarget_ops())
        for index in range(rtg.get_num_retarget_ops()):
            log("  op[%02d] %s" % (index, str(rtg.get_op_name(index))))

        rig = EAL.load_asset(IKR_TARGET)
        controller = unreal.IKRigController.get_controller(rig)
        for chain in controller.get_retarget_chains():
            name = unreal.Name(str(chain.get_editor_property("chain_name")))
            log("  map %-22s -> %s" % (str(name), str(rtg.get_source_chain(name))))

        fk_index = rtg.get_index_of_op_by_name(unreal.Name("FK Chains"))
        log("  FK Chains op index: %d" % fk_index)
        if fk_index >= 0:
            controller_op = rtg.get_op_controller(fk_index)
            settings = controller_op.get_settings()
            chain_settings = settings.get_editor_property("chains_to_retarget")
            log("  FK op chain settings: %d" % len(chain_settings))
            for entry in chain_settings:
                log("    %-22s fk=%s rot=%s trans=%s" % (
                    str(entry.get_editor_property("target_chain_name")),
                    entry.get_editor_property("enable_fk"),
                    entry.get_editor_property("rotation_mode"),
                    entry.get_editor_property("translation_mode")))

    with open(RESULT, "w", encoding="utf-8") as handle:
        handle.write("\n".join(lines))


main()
