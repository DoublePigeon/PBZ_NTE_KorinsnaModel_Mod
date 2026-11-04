"""Dump the retargeter's actual per-chain settings (read-only; no assets are modified).

Writes extract/ue-retarget-settings.txt so the numbers can be compared against docs/IK_check.md.
"""
import os

import unreal

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
OUT = os.path.join(ROOT, "extract", "ue-retarget-settings.txt")
RETARGETER = "/Game/Korinsna/RTG_HunToKorinsna"

lines = []


def log(msg):
    lines.append(str(msg))


def read_op_settings(rtg, op_name):
    index = rtg.get_index_of_op_by_name(unreal.Name(op_name))
    if index < 0:
        log("%s: op not found" % op_name)
        return None
    controller = rtg.get_op_controller(index)
    if controller is None or not hasattr(controller, "get_settings"):
        log("%s: controller %s has no get_settings" % (op_name, type(controller).__name__))
        return None
    return controller.get_settings()


def main():
    rtg_asset = unreal.EditorAssetLibrary.load_asset(RETARGETER)
    if rtg_asset is None:
        raise SystemExit("missing " + RETARGETER)
    rtg = unreal.IKRetargeterController.get_controller(rtg_asset)

    count = rtg.get_num_retarget_ops()
    log("ops: %d" % count)
    for index in range(count):
        controller = rtg.get_op_controller(index)
        log("op[%02d] %-24s enabled=%-5s controller=%s" % (
            index, str(rtg.get_op_name(index)), rtg.get_retarget_op_enabled(index),
            type(controller).__name__))

    settings = read_op_settings(rtg, "FK Chains")
    if settings is not None:
        chains = settings.get_editor_property("chains_to_retarget")
        log("chains in op: %d" % len(chains))
        for chain in chains:
            log("  %-16s enableFK=%-5s rot=%-13s rotA=%.2f trans=%-15s transA=%.2f" % (
                str(chain.get_editor_property("target_chain_name")),
                chain.get_editor_property("enable_fk"),
                chain.get_editor_property("rotation_mode"),
                chain.get_editor_property("rotation_alpha"),
                chain.get_editor_property("translation_mode"),
                chain.get_editor_property("translation_alpha")))

    for op_name in ("Pelvis Motion", "Root Motion"):
        op_settings = read_op_settings(rtg, op_name)
        if op_settings is None:
            continue
        log("%s: %s" % (op_name, op_settings))
        for prop in ("rotation_alpha", "translation_alpha", "enable_translation",
                     "enable_rotation", "translation_alpha_x", "translation_alpha_y",
                     "translation_alpha_z", "scale_horizontal", "scale_vertical"):
            try:
                log("   %-22s = %s" % (prop, op_settings.get_editor_property(prop)))
            except Exception:  # noqa: BLE001
                pass


try:
    main()
finally:
    with open(OUT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines) + "\n")
