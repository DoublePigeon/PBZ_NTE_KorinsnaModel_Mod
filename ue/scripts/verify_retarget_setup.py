"""Report what the authored retargeter and anim blueprint actually contain.

Writes extract/ue-retarget-verify.txt so the build can be sanity checked without opening the editor.
"""
import os

import unreal

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
OUT = os.path.join(ROOT, "extract", "ue-retarget-verify.txt")

RETARGETER = "/Game/Korinsna/RTG_HunToKorinsna"
ANIM_BP = "/Game/Korinsna/ABP_Korinsna_Retarget"

lines = []


def log(msg):
    lines.append(str(msg))


try:
    retargeter = unreal.EditorAssetLibrary.load_asset(RETARGETER)
    if retargeter is None:
        log("retargeter missing: " + RETARGETER)
    else:
        rtg = unreal.IKRetargeterController.get_controller(retargeter)
        log("retargeter %s ops=%d" % (RETARGETER, rtg.get_num_retarget_ops()))

        source_rig = rtg.get_ik_rig(unreal.RetargetSourceOrTarget.SOURCE)
        target_rig = rtg.get_ik_rig(unreal.RetargetSourceOrTarget.TARGET)
        log("source rig=%s" % (source_rig.get_path_name() if source_rig else "None"))
        log("target rig=%s" % (target_rig.get_path_name() if target_rig else "None"))
        log("retarget pose source=%s target=%s" % (
            rtg.get_current_retarget_pose_name(unreal.RetargetSourceOrTarget.SOURCE),
            rtg.get_current_retarget_pose_name(unreal.RetargetSourceOrTarget.TARGET)))

        if target_rig:
            tctl = unreal.IKRigController.get_controller(target_rig)
            log("target retarget root=%s" % tctl.get_retarget_root())
        if source_rig:
            sctl = unreal.IKRigController.get_controller(source_rig)
            log("source retarget root=%s" % sctl.get_retarget_root())

        mapping = []
        if target_rig:
            tctl = unreal.IKRigController.get_controller(target_rig)
            for chain in tctl.get_retarget_chains():
                name = str(chain.chain_name)
                mapping.append((name, str(rtg.get_source_chain(unreal.Name(name)))))

        for op_index in range(rtg.get_num_retarget_ops()):
            log("  op[%02d] %-24s enabled=%s" % (
                op_index, str(rtg.get_op_name(op_index)), rtg.get_retarget_op_enabled(op_index)))

        log("chain map (%d entries):" % len(mapping))
        for target_chain, source_chain in mapping:
            log("  %-16s <- %-16s" % (target_chain, source_chain))

    abp = unreal.EditorAssetLibrary.load_asset(ANIM_BP)
    if abp is None:
        log("anim blueprint missing: " + ANIM_BP)
    else:
        log("anim blueprint %s" % ANIM_BP)
        log("  target skeleton=%s" % abp.get_editor_property("target_skeleton").get_path_name())
        generated = abp.generated_class()
        log("  generated class=%s" % (generated.get_path_name() if generated else "None"))
        status = unreal.EditorAssetLibrary.find_asset_data(ANIM_BP)
        log("  asset class=%s" % status.asset_class_path.asset_name)
except Exception as exc:  # noqa: BLE001
    import traceback
    log("ERROR " + str(exc))
    log(traceback.format_exc())

with open(OUT, "w", encoding="utf-8") as fh:
    fh.write("\n".join(lines))
