"""Author the IK Rigs, IK Retargeter and retarget AnimBlueprint for the Korinsna mod.

Nothing here touches the Korinsna skeleton: the mesh keeps its own Bip001 rig and the game keeps
its own Hun skeleton. The retargeter copies the game's runtime pose onto the Korinsna rig, and the
AnimBlueprint is a single "Retarget Pose From Mesh" node reading the parent skeletal mesh component.

Run order (see tools/build_all.ps1):
    import_korinsna_sk.py       -> /Game/Korinsna/SK_Korinsna (+ its own skeleton)
    build_mod_assets.py         -> textures, material slots
    import_hun_preview.py       -> /Game/Korinsna/Source/HunSkin (game bone names, editor only)
    build_retarget_assets.py    -> this file
    import_blank_parts.py       -> degenerate meshes over the hero's own parts
"""
import os

import unreal

AT = unreal.AssetToolsHelpers.get_asset_tools()
EAL = unreal.EditorAssetLibrary

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
RESULT = os.path.join(ROOT, "extract", "ue-retarget-result.txt")

DEST = "/Game/Korinsna"
TARGET_SKEL = DEST + "/SK_Korinsna_Skeleton"
TARGET_MESH = DEST + "/SK_Korinsna"
SOURCE_MESH = DEST + "/Source/HunSkin"

IKR_SOURCE = DEST + "/IKR_Hun"
IKR_TARGET = DEST + "/IKR_Korinsna"
RETARGETER = DEST + "/RTG_HunToKorinsna"
ANIM_BP = DEST + "/ABP_Korinsna_Retarget"

# Fingers are deliberately NOT retargeted.
#
# Every attempt to drive them produced visibly wrong fingers: they are small bones, so a constant
# reference-pose error of a few degrees is already enough to read as long and curled, and Korinsna's
# finger proportions differ from the hero's. Excluding them leaves them exactly at their bind pose,
# which is why the model is shipped with a clenched fist baked in
# (KorinsnaModel/npc_036_APOSE_clenched.blend -> the bind pose). Same principle the reference 2B mod
# uses for its facial bones: a bone that is never retargeted cannot be deformed.
#
# To bring finger animation back, the honest route is per-bone retarget-pose offsets plus a hand IK
# pass in the ABP - not simply re-adding the chain.
RETARGET_FINGERS = False
FINGER_CHAIN_PREFIXES = ("LeftHandThumb", "LeftHandIndex", "LeftHandMiddle", "LeftHandRing",
                         "LeftHandPinky", "RightHandThumb", "RightHandIndex", "RightHandMiddle",
                         "RightHandRing", "RightHandPinky")

# The dress chains are left out of the retarget.
#
# They were matched to the hero's robe chains geometrically, not by name, and the mapping does not hold
# up in motion: the skirt ends up swinging into the legs instead of hanging. Excluding them keeps the
# skirt at its modelled shape (the bind pose), which is rigid but never clips.
RETARGET_SKIRT = False
SKIRT_CHAIN_PREFIXES = ("LeftSkirt", "RightSkirt", "BackSkirt", "FrontSkirt")

# The head is excluded as well. Korinsna's face is skinned across `head_Bone001`/`head_Bone002`, whose
# pivots are not where the hero's single `Head` bone pivot is, so copying that rotation drags the face
# out of shape. Leaving the head out keeps it at its modelled shape - it still turns with the neck
# chain, exactly the trade-off the reference 2B mod makes for its facial bones.
RETARGET_HEAD = False
DROPPED_CHAINS = ("Head",)

# (chain name, source start, source end, target start, target end)
#
# Chain names are shared between the two rigs so the retargeter's chain map can be built by name.
# The game rig has five spine bones and 3ds-Max style fingers/cloth; Korinsna has two spine bones,
# Bip001 fingers (Finger0 = thumb ... Finger4 = pinky) and its own skirt chains.
CHAINS = [
    ("Root", "Root", "Root", "Root", "Root"),
    ("Spine", "pelvis", "spine_05", "Bip001-Pelvis", "Bip001-Spine1"),
    ("Neck", "neck_01", "neck_02", "Bip001-Neck", "Bip001-Neck"),
    ("Head", "Head", "Head", "head_Bone001", "head_Bone001"),

    ("LeftClavicle", "clavicle_l", "clavicle_l", "Bip001-L-Clavicle", "Bip001-L-Clavicle"),
    ("RightClavicle", "clavicle_r", "clavicle_r", "Bip001-R-Clavicle", "Bip001-R-Clavicle"),

    # One chain per limb segment group, spanning the twist bones in between.
    #
    # Splitting these into one-bone chains to keep the max-style twist bones
    # (Bip001-UpperArm -> Bone-UpperArm-Twist -> Bone-UpperArm-Twist1 -> Bip001-Forearm -> ...) out of
    # the retarget made the deformation clearly worse: with the twist bones frozen the skin they carry
    # (hundreds of weight units each) stops following the joint twist, and the limbs read as stretched.
    # The FK op's Interpolated rotation mode is designed for exactly this case and spreads the joint
    # rotation across the twist bones, so the continuous chain is kept.
    ("LeftArm", "upperarm_l", "hand_l", "Bip001-L-UpperArm", "Bip001-L-Hand"),
    ("RightArm", "upperarm_r", "hand_r", "Bip001-R-UpperArm", "Bip001-R-Hand"),
    ("LeftLeg", "thigh_l", "ball_l", "Bip001-L-Thigh", "Bip001-L-Toe0"),
    ("RightLeg", "thigh_r", "ball_r", "Bip001-R-Thigh", "Bip001-R-Toe0"),

    ("LeftHandThumb", "thumb_01_l", "thumb_03_l", "Bip001-L-Finger0", "Bip001-L-Finger02"),
    ("LeftHandIndex", "index_01_l", "index_03_l", "Bip001-L-Finger1", "Bip001-L-Finger12"),
    ("LeftHandMiddle", "middle_01_l", "middle_03_l", "Bip001-L-Finger2", "Bip001-L-Finger22"),
    ("LeftHandRing", "ring_01_l", "ring_03_l", "Bip001-L-Finger3", "Bip001-L-Finger32"),
    ("LeftHandPinky", "pinky_01_l", "pinky_03_l", "Bip001-L-Finger4", "Bip001-L-Finger42"),
    ("RightHandThumb", "thumb_01_r", "thumb_03_r", "Bip001-R-Finger0", "Bip001-R-Finger02"),
    ("RightHandIndex", "index_01_r", "index_03_r", "Bip001-R-Finger1", "Bip001-R-Finger12"),
    ("RightHandMiddle", "middle_01_r", "middle_03_r", "Bip001-R-Finger2", "Bip001-R-Finger22"),
    ("RightHandRing", "ring_01_r", "ring_03_r", "Bip001-R-Finger3", "Bip001-R-Finger32"),
    ("RightHandPinky", "pinky_01_r", "pinky_03_r", "Bip001-R-Finger4", "Bip001-R-Finger42"),

    # skirt: the game's robe chains and Korinsna's dress chains were matched geometrically
    # (tools/skirt_chain_map.py), not by name
    ("LeftSkirtA", "bns_skirt_0_01_l", "bns_skirt_0_05_l", "l_skirt_1", "l_skirt_5"),
    ("RightSkirtA", "bns_skirt_0_01_r", "bns_skirt_0_05_r", "r_skirt_1", "r_skirt_5"),
    ("LeftSkirtB", "bns_skirt_1_01_l", "bns_skirt_1_05_l", "l_skirt_7", "l_skirt_11"),
    ("RightSkirtB", "bns_skirt_1_01_r", "bns_skirt_1_05_r", "r_skirt_7", "r_skirt_11"),
    ("LeftSkirtC", "bns_skirt_2_01_l", "bns_skirt_2_05_l", "l_skirt_13", "l_skirt_17"),
    ("RightSkirtC", "bns_skirt_2_01_r", "bns_skirt_2_05_r", "r_skirt_13", "r_skirt_17"),
    ("BackSkirt", "bns_skirt_3_01", "bns_skirt_3_05", "b_skirt_1", "b_skirt_5"),
    ("FrontSkirt", "bns_frontSkirtArmorRibbon_01", "bns_frontSkirtArmorRibbon_05",
     "m_skirt_1", "m_skirt_5"),
]

lines = []


def log(msg):
    lines.append(str(msg))


STALE_DIR = "/Game/KorinsnaStale"


def cleanup_stale():
    """Assets that could not be deleted in an earlier run are parked here; clear them out."""
    if not EAL.does_directory_exist(STALE_DIR):
        return
    for path in EAL.list_assets(STALE_DIR):
        asset = EAL.load_asset(path)
        if asset is not None:
            EAL.delete_loaded_asset(asset)
    unreal.SystemLibrary.collect_garbage()
    log("stale assets left: %s" % list(EAL.list_assets(STALE_DIR)))


def wipe(path):
    """Delete an existing asset so it can be recreated in the same package."""
    if not EAL.does_asset_exist(path):
        return
    asset = EAL.load_asset(path)
    if asset is not None:
        EAL.delete_loaded_asset(asset)
        unreal.SystemLibrary.collect_garbage()
    if EAL.does_asset_exist(path):
        # something still holds a reference (an IK Rig controller, usually): park it outside
        # /Game/Korinsna instead, which is also outside the staged content
        base = path.rsplit("/", 1)[1]
        for attempt in range(100):
            stale = "%s/%s_%02d" % (STALE_DIR, base, attempt)
            if not EAL.does_asset_exist(stale):
                break
        log("could not delete %s, moving it to %s" % (path, stale))
        EAL.rename_asset(path, stale)
        if EAL.does_asset_exist(path):
            raise SystemExit("could not clear " + path)


def ensure_asset(path, asset_class, factory):
    wipe(path)
    folder, name = path.rsplit("/", 1)
    if not EAL.does_directory_exist(folder):
        EAL.make_directory(folder)
    asset = AT.create_asset(name, folder, asset_class, factory)
    if asset is None:
        raise SystemExit("asset creation failed: " + path)
    log("created %s -> %s" % (path, asset.get_path_name()))
    return asset


def build_rig(path, mesh):
    rig = ensure_asset(path, unreal.IKRigDefinition, unreal.IKRigDefinitionFactory())
    if rig is None:
        return None, None
    controller = unreal.IKRigController.get_controller(rig)
    if not controller.set_skeletal_mesh(mesh):
        log("  set_skeletal_mesh FAILED for %s" % path)
        return rig, None
    EAL.save_loaded_asset(rig, False)
    return rig, controller


def main():
    cleanup_stale()

    # probe assets from earlier experiments must not end up in the cooked mod
    for stale in ("/Game/Korinsna/ProbeIKR", "/Game/Korinsna/ProbeRTG"):
        if EAL.does_asset_exist(stale):
            wipe(stale)

    target_mesh = EAL.load_asset(TARGET_MESH)
    source_mesh = EAL.load_asset(SOURCE_MESH)
    if target_mesh is None:
        raise SystemExit("missing " + TARGET_MESH)
    if source_mesh is None:
        raise SystemExit("missing " + SOURCE_MESH)

    # ---------------------------------------------------------------- IK rigs
    rig_source, ctrl_source = build_rig(IKR_SOURCE, source_mesh)
    rig_target, ctrl_target = build_rig(IKR_TARGET, target_mesh)
    if not ctrl_source or not ctrl_target:
        raise SystemExit("IK rig creation failed")

    if not ctrl_source.set_retarget_root("pelvis"):
        log("source: set_retarget_root(pelvis) failed")
    if not ctrl_target.set_retarget_root("Bip001-Pelvis"):
        log("target: set_retarget_root(Bip001-Pelvis) failed")

    # Make the skeleton's reference pose match the mesh's bind pose before anything reads it. The
    # retargeter only transfers a rotation delta relative to the reference pose, so a mismatch becomes a
    # constant offset on every bone: invisible on big bones, but on fingers a few degrees already reads
    # as curled and deformed fingers. Same step as the reference 2B mod's sync_reference_pose().
    log("sync ref pose: " + str(
        unreal.KorinsnaEditorLibrary.sync_reference_pose(TARGET_MESH)))
    EAL.save_loaded_asset(EAL.load_asset(TARGET_SKEL), False)
    # the IK Rig caches the bone reference pose when the mesh is assigned, so re-assign it
    ctrl_target.set_skeletal_mesh(target_mesh)
    ctrl_source.set_skeletal_mesh(source_mesh)

    added_source = 0
    added_target = 0
    for name, s_start, s_end, t_start, t_end in CHAINS:
        if not RETARGET_FINGERS and name.startswith(FINGER_CHAIN_PREFIXES):
            continue
        if not RETARGET_SKIRT and name.startswith(SKIRT_CHAIN_PREFIXES):
            continue
        if not RETARGET_HEAD and name in DROPPED_CHAINS:
            continue
        if ctrl_source.add_retarget_chain(name, s_start, s_end, unreal.Name("None")):
            added_source += 1
        else:
            log("source chain failed: %s (%s..%s)" % (name, s_start, s_end))
        if ctrl_target.add_retarget_chain(name, t_start, t_end, unreal.Name("None")):
            added_target += 1
        else:
            log("target chain failed: %s (%s..%s)" % (name, t_start, t_end))
    log("chains: source=%d target=%d of %d" % (added_source, added_target, len(CHAINS)))

    EAL.save_loaded_asset(rig_source, False)
    EAL.save_loaded_asset(rig_target, False)

    # ---------------------------------------------------------------- retargeter
    retargeter = ensure_asset(RETARGETER, unreal.IKRetargeter, unreal.IKRetargetFactory())
    if retargeter is None:
        raise SystemExit("retargeter creation failed")

    rtg = unreal.IKRetargeterController.get_controller(retargeter)
    source_kind = unreal.RetargetSourceOrTarget.SOURCE
    target_kind = unreal.RetargetSourceOrTarget.TARGET
    rtg.set_ik_rig(source_kind, rig_source)
    rtg.set_ik_rig(target_kind, rig_target)
    rtg.set_preview_mesh(source_kind, source_mesh)
    rtg.set_preview_mesh(target_kind, target_mesh)
    log("ops after set_ik_rig: %d" % rtg.get_num_retarget_ops())
    rtg.assign_ik_rig_to_all_ops(source_kind, rig_source)
    rtg.assign_ik_rig_to_all_ops(target_kind, rig_target)
    log("ops after assign_ik_rig_to_all_ops: %d" % rtg.get_num_retarget_ops())
    rtg.auto_map_chains(unreal.AutoMapChainType.FUZZY, True)
    log("ops after auto_map_chains: %d" % rtg.get_num_retarget_ops())

    # Aligns the target retarget pose to the source's. Without it the per-bone rotation offsets are
    # computed against two different reference poses, which is what made the fingers come out long and
    # curled and produced the occasional stretched limb during animations.
    if hasattr(rtg, "auto_align_all_bones"):
        aligned = rtg.auto_align_all_bones(target_kind)
        log("auto_align_all_bones(target) = %s" % aligned)
        EAL.save_loaded_asset(rig_target, False)
    else:
        log("auto_align_all_bones is not exposed in this build")

    # The IK half of the default stack is dead weight here: it retargets IK goals, and the target IK
    # Rig has no goals or solvers, so those ops have nothing to solve. What is left is the pure FK
    # rotation copy plus pelvis/root motion, which is exactly a "same pose" retarget.
    disabled = []
    for index in range(rtg.get_num_retarget_ops()):
        name = str(rtg.get_op_name(index))
        if name in ("Retarget IK Goals", "Run IK Rig", "Remap Curves"):
            if rtg.set_retarget_op_enabled(index, False):
                disabled.append(name)
            else:
                log("could not disable op %s" % name)
    log("disabled ops: %s" % (disabled or "none"))
    for index in range(rtg.get_num_retarget_ops()):
        log("  op[%02d] %-22s enabled=%s" % (
            index, str(rtg.get_op_name(index)), rtg.get_retarget_op_enabled(index)))

    missing = []
    for name, _ss, _se, t_start, _te in CHAINS:
        mapped = rtg.get_source_chain(unreal.Name(name))
        if not str(mapped):
            missing.append(name)
    log("chains without a source mapping: %s" % (missing or "none"))
    EAL.save_loaded_asset(retargeter, False)

    # ---------------------------------------------------------------- anim blueprint
    skeleton = EAL.load_asset(TARGET_SKEL)
    if skeleton is None:
        raise SystemExit("missing " + TARGET_SKEL)

    ok = unreal.KorinsnaEditorLibrary.create_retarget_anim_blueprint(
        ANIM_BP, skeleton.get_path_name(), retargeter.get_path_name())
    log("anim blueprint created=%s" % ok)
    if EAL.does_asset_exist(ANIM_BP):
        abp = EAL.load_asset(ANIM_BP)
        log("  generated class=%s" % (
            abp.generated_class().get_path_name() if abp and abp.generated_class() else "None"))

    with open(RESULT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))


try:
    main()
finally:
    with open(RESULT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))
