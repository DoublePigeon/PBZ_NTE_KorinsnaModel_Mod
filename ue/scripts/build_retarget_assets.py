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
import re

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

# Which bone chains take part in the retarget, and with which modes, is DATA: ue/retarget_config.json.
#
# This used to be a set of name-prefix tests here (`name.startswith(FINGER_CHAIN_PREFIXES)` etc.), which
# is the kind of string matching that silently mis-handles a chain that is added or renamed later.
# Every chain now carries its own `retarget` flag plus its rotation/translation modes, and the reasons
# are recorded next to it in the file's `note` fields.
CONFIG_PATH = os.path.join(ROOT, "ue", "retarget_config.json")

# Hair / skirt physics. Both authoring inputs are data, never code:
#   * ue/rigidbody_config.json - the active path: the engine's own RigidBody node + a physics asset
#     generated from this file (component-space simulation, so world movement never enters the solver);
#   * ue/kawaii_config.json - the previous KawaiiPhysics path, kept as a reference/fallback (its "mode"
#     key decides which one the C++ authoring step builds).
PHYSICS_CONFIG = os.path.join(ROOT, "ue", "kawaii_config.json")


def load_config():
    import json

    with open(CONFIG_PATH, encoding="utf-8") as handle:
        return json.load(handle)


def enum_value(enum_type, name):
    """`GloballyScaled` / `OneToOne` -> the unreal enum member, with a clear error if it is unknown."""
    snake = re.sub(r"(?<!^)(?=[A-Z])", "_", str(name)).upper()
    value = getattr(enum_type, snake, None)
    if value is None:
        raise SystemExit("unknown %s value: %s (expected e.g. %s)" % (
            enum_type, name, ", ".join(n for n in dir(enum_type) if n.isupper())))
    return value


def merged_settings(chain, defaults):
    """Config entry + defaults -> values written into the FK Chains op."""
    merged = dict(defaults)
    merged.update({key: value for key, value in chain.items()
                   if key not in ("name", "retarget", "source", "target", "note")})
    return merged


lines = []
if os.path.exists(RESULT):
    os.remove(RESULT)


def log(msg):
    """Write through, line by line: a failed build can die inside the engine (an assert in the IK
    retargeter kills the process), and the log is the only evidence of how far it got."""
    text = str(msg)
    lines.append(text)
    with open(RESULT, "a", encoding="utf-8") as handle:
        handle.write(text + "\n")


STALE_DIR = "/Game/KorinsnaStale"


def bone_parents(mesh_path):
    """{bone: parent} of a mesh, read from a throwaway component. The IK Rig controller does not expose
    chain bone lists to Python and a chain is "every bone on the hierarchy path start -> end", so the
    only way to know which bones a chain covers is to walk the skeleton."""
    mesh = EAL.load_asset(mesh_path)
    if mesh is None:
        raise SystemExit("missing " + mesh_path)
    subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    actor = subsystem.spawn_actor_from_class(unreal.SkeletalMeshActor, unreal.Vector(0, 0, 0))
    component = actor.skeletal_mesh_component
    component.set_skeletal_mesh_asset(mesh)
    parents = {}
    try:
        for index in range(component.get_num_bones()):
            name = str(component.get_bone_name(index))
            parents[name] = str(component.get_parent_bone(unreal.Name(name)))
    finally:
        subsystem.destroy_actor(actor)
    return parents


def chain_bones(parents, start, end):
    """Bones on the path from `start` down to `end`, inclusive; empty if `end` is not below `start`."""
    if start not in parents or end not in parents:
        return []
    path = [end]
    current = end
    for _ in range(256):
        if current == start:
            return list(reversed(path))
        parent = parents.get(current)
        if parent in (None, "None", ""):
            return []
        path.append(parent)
        current = parent
    return []


def _op_chain_names(rtg, index):
    """Chain names an op holds settings for. A chain with no settings in any op cannot be mapped."""
    try:
        controller = rtg.get_op_controller(index)
        entries = controller.get_settings().get_editor_property("chains_to_retarget")
    except Exception as error:                      # ops without chain settings (pelvis/root motion)
        return "n/a"
    return "[%s]" % ",".join(str(e.get_editor_property("target_chain_name")) for e in entries)


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

    config = load_config()
    defaults = config.get("defaults", {})
    chains = config["chains"]
    participating = [c for c in chains if c.get("retarget")]

    added_source = 0
    added_target = 0
    for chain in chains:
        if not chain.get("retarget"):
            continue
        name = chain["name"]
        s_start, s_end = chain["source"]
        t_start, t_end = chain["target"]
        if ctrl_source.add_retarget_chain(name, s_start, s_end, unreal.Name("None")):
            added_source += 1
        else:
            log("source chain failed: %s (%s..%s)" % (name, s_start, s_end))
        if ctrl_target.add_retarget_chain(name, t_start, t_end, unreal.Name("None")):
            added_target += 1
        else:
            log("target chain failed: %s (%s..%s)" % (name, t_start, t_end))
    log("chains: source=%d target=%d of %d (%d not retargeted)" % (
        added_source, added_target, len(chains), len(chains) - len(participating)))

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
    # Chain mapping is explicit, from the config: both IK rigs use the same chain names, so every
    # target chain maps to the source chain of the same name. Fuzzy auto-mapping was removed: with the
    # limbs split per joint it mapped some chains by name similarity, which left a target chain
    # unmapped while its bones were still marked retargetable - that trips an editor assert
    # ("Bone should never be retargeted and not in a mapped chain") inside auto_align_all_bones.
    mapped_chains = 0
    for chain in participating:
        name = unreal.Name(chain["name"])
        if rtg.set_source_chain(name, name):
            mapped_chains += 1
        else:
            log("could not map chain %s" % chain["name"])
    log("chains mapped explicitly: %d of %d" % (mapped_chains, len(participating)))
    log("ops after chain mapping: %d" % rtg.get_num_retarget_ops())

    # The retargeter looks the mapping up by bone -> chain -> mapped chain, so a target chain that ends
    # up without a source chain makes it assert ("Bone should never be retargeted and not in a mapped
    # chain") inside auto_align_all_bones and takes the whole editor down. Verify before aligning and
    # skip the align instead of crashing: an unaligned pose is a visible defect, a crash is a lost build.
    unmapped = [c["name"] for c in participating
                if not str(rtg.get_source_chain(unreal.Name(c["name"])))]
    for index in range(rtg.get_num_retarget_ops()):
        log("  op[%02d] %-22s chains=%s" % (
            index, str(rtg.get_op_name(index)), _op_chain_names(rtg, index)))
    if unmapped:
        log("ALIGN SKIPPED - chains without a source mapping: %s" % unmapped)

    # Aligns the target retarget pose to the source's. Without it the per-bone rotation offsets are
    # computed against two different reference poses, which is what made the fingers come out long and
    # curled and produced the occasional stretched limb during animations.
    #
    # `auto_align_all_bones` is NOT used: it walks every bone it considers retargetable, and the engine
    # asserts ("Bone should never be retargeted and not in a mapped chain") as soon as one of them is in
    # no mapped chain - which kills the editor process mid-build. Aligning the bones of our own mapped
    # chains through `auto_align_bones` is the same alignment, one chain at a time, and it keeps the log
    # showing how far it got.
    if not hasattr(rtg, "auto_align_bones"):
        log("auto_align_bones is not exposed in this build")
    elif unmapped:
        log("alignment skipped: unmapped chains")
    else:
        parents = bone_parents(TARGET_MESH)
        method = unreal.RetargetAutoAlignMethod.CHAIN_TO_CHAIN
        aligned = 0
        for chain in participating:
            bones = [unreal.Name(b) for b in chain_bones(
                parents, chain["target"][0], chain["target"][1])]
            if not bones:
                log("  align %-14s no bones on the path %s..%s" % (
                    chain["name"], chain["target"][0], chain["target"][1]))
                continue
            rtg.auto_align_bones(bones, method, target_kind)
            aligned += 1
            log("  align %-14s %d bone(s): %s" % (chain["name"], len(bones), ", ".join(
                str(b) for b in bones)))
        log("aligned %d chain(s), retarget pose saved" % aligned)
        EAL.save_loaded_asset(rig_target, False)

    # Op enable flags come from the config too. The IK half of the default stack must stay off: it
    # retargets IK goals, and the target IK Rig has no goals or solvers, so enabling it crashes the
    # game (TECHNICAL-GUIDE §6.12). What is left is the pure FK rotation copy plus pelvis/root motion.
    wanted_ops = config.get("ops", {})
    for index in range(rtg.get_num_retarget_ops()):
        name = str(rtg.get_op_name(index))
        if name in wanted_ops:
            enabled = bool(wanted_ops[name])
            if not rtg.set_retarget_op_enabled(index, enabled):
                log("could not set op %s enabled=%s" % (name, enabled))
    for index in range(rtg.get_num_retarget_ops()):
        log("  op[%02d] %-22s enabled=%s" % (
            index, str(rtg.get_op_name(index)), rtg.get_retarget_op_enabled(index)))

    # Per-chain modes, straight from the config: rotation mode/alpha, translation mode/alpha, enable.
    # `set_settings` takes the whole struct, so it is read, edited per chain and written back once.
    fk_index = rtg.get_index_of_op_by_name(unreal.Name("FK Chains"))
    if fk_index < 0:
        log("FK Chains op not found - chain settings not applied")
    else:
        controller = rtg.get_op_controller(fk_index)
        settings = controller.get_settings()
        by_name = {c["name"]: merged_settings(c, defaults) for c in participating}
        op_chains = settings.get_editor_property("chains_to_retarget")
        for chain in op_chains:
            name = str(chain.get_editor_property("target_chain_name"))
            values = by_name.get(name)
            if values is None:
                log("  chain in op but not in config: %s (left at defaults)" % name)
                continue
            chain.set_editor_property("enable_fk", bool(values.get("enable_fk", True)))
            chain.set_editor_property("rotation_mode", enum_value(
                unreal.FKChainRotationMode, values.get("rotation_mode", "Interpolated")))
            chain.set_editor_property("rotation_alpha", float(values.get("rotation_alpha", 1.0)))
            chain.set_editor_property("translation_mode", enum_value(
                unreal.FKChainTranslationMode, values.get("translation_mode", "None")))
            chain.set_editor_property("translation_alpha",
                                      float(values.get("translation_alpha", 1.0)))
            log("  %-16s enableFK=%-5s rot=%-13s rotA=%.2f trans=%-15s transA=%.2f" % (
                name, chain.get_editor_property("enable_fk"),
                str(chain.get_editor_property("rotation_mode")).rsplit(".", 1)[-1],
                chain.get_editor_property("rotation_alpha"),
                str(chain.get_editor_property("translation_mode")).rsplit(".", 1)[-1],
                chain.get_editor_property("translation_alpha")))
        settings.set_editor_property("chains_to_retarget", op_chains)
        controller.set_settings(settings)
        log("FK chain settings applied to %d chain(s)" % len(op_chains))
    EAL.save_loaded_asset(retargeter, False)

    missing = []
    for chain in participating:
        mapped = rtg.get_source_chain(unreal.Name(chain["name"]))
        if not str(mapped):
            missing.append(chain["name"])
    log("chains without a source mapping: %s" % (missing or "none"))

    # ---------------------------------------------------------------- anim blueprint
    skeleton = EAL.load_asset(TARGET_SKEL)
    if skeleton is None:
        raise SystemExit("missing " + TARGET_SKEL)

    # Hair / skirt physics: rigged in ue/rigidbody_config.json (the same data-driven rule as
    # ue/retarget_config.json). The C++ authoring step generates the physics asset named there and adds a
    # single RigidBody node after the retarget node.
    ok = unreal.KorinsnaEditorLibrary.create_retarget_anim_blueprint(
        ANIM_BP, skeleton.get_path_name(), retargeter.get_path_name(), PHYSICS_CONFIG.replace("\\", "/"))
    log("anim blueprint created=%s (physics config %s)" % (ok, PHYSICS_CONFIG))
    if EAL.does_asset_exist(ANIM_BP):
        abp = EAL.load_asset(ANIM_BP)
        log("  generated class=%s" % (
            abp.generated_class().get_path_name() if abp and abp.generated_class() else "None"))
        # Prove what was authored: the runtime log cannot show a node whose root bone or collider set
        # did not resolve. Reports "no kawaii nodes" when the rigid-body path is active.
        for line in str(unreal.KorinsnaEditorLibrary.describe_kawaii_physics(ANIM_BP)).splitlines():
            log("  " + line)

    with open(RESULT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))


try:
    main()
finally:
    with open(RESULT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))
