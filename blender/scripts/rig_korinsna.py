"""Rig the Korinsna mesh onto the game's Hun skeleton.

Steps: load target skeleton, append the Korinsna mesh + its rig, align it to the
target rest pose, remap weights by semantic bone mapping, normalize/limit
influences, then export an FBX ready for UE import.

Usage:
  blender.exe -b --factory-startup --python rig_korinsna.py -- \
      <target_skeleton.blend> <korinsna.blend> <out.fbx> <out_blend>
"""
import bpy
import json
import math
import sys
from mathutils import Matrix, Quaternion, Vector

argv = sys.argv
argv = argv[argv.index("--") + 1:] if "--" in argv else []
target_blend, src_blend, out_fbx, out_blend = argv[0], argv[1], argv[2], argv[3]

# ---------------------------------------------------------------- bone mapping
CORE_MAP = {
    "Bip001-Pelvis": "pelvis",
    "Bip001-Spine": "spine_01",
    "Bip001-Spine1": "spine_02",
    "Bip001-Neck": "neck_01",
    "head_Bone001": "Head",
    "Chest_M": "spine_05",
    "Bn_l_breast_001": "spine_04",
    "Bn_r_breast_001": "spine_04",
}

SIDE_MAP = [
    # (source suffix, target suffix)
    ("Thigh", "thigh"),
    ("Calf", "calf"),
    ("Foot", "foot"),
    ("Toe0", "ball"),
    ("Clavicle", "clavicle"),
    ("UpperArm", "upperarm"),
    ("Forearm", "lowerarm"),
    ("Hand", "hand"),
]

FINGER_MAP = [
    ("Finger0", "thumb"),
    ("Finger1", "index"),
    ("Finger2", "middle"),
    ("Finger3", "ring"),
    ("Finger4", "pinky"),
]

TWIST_MAP = [
    ("Bone-{S}-Thigh-Twist", "thigh_twist_01_{s}"),
    ("Bone-{S}-Thigh-Twist1", "thigh_twist_02_{s}"),
    ("Bone-{S}-Calf-Twist", "calf_twist_01_{s}"),
    ("Bone-{S}-Calf-Twist1", "calf_twist_02_{s}"),
    ("Bone-{S}-UpperArm-Twist", "upperarm_twist_01_{s}"),
    ("Bone-{S}-UpperArm-Twist1", "upperarm_twist_02_{s}"),
    ("Bone-{S}-ForeArm-Twist", "lowerarm_twist_01_{s}"),
    ("Bone-{S}-ForeArm-Twist1", "lowerarm_twist_02_{s}"),
]

# everything hair / head accessory rides the head bone
HEAD_LIKE_PREFIXES = ("l_toushi", "r_toushi", "b_toushi", "liuhai", "qianfa",
                      "l_houfaA", "l_houfaB", "r_houfaA", "r_houfaB",
                      "l_erduo", "r_erduo", "erhuan", "head_Bone00")
# skirt-ish chains are remapped later by nearest skirt bone
SKIRT_PREFIXES = ("l_skirt", "r_skirt", "m_skirt", "b_skirt", "qunshi", "xiongshi")
FOOT_PREFIXES = ("l_jiaoshi", "r_jiaoshi", "Bn_l_kneePush", "Bn_r_kneePush",
                 "Bn_l_elbowPush", "Bn_r_elbowPush")


def build_mapping(source_names):
    mapping = {}
    for src, dst in CORE_MAP.items():
        mapping[src] = dst
    for side_src, side_dst in (("R", "r"), ("L", "l")):
        for src_suffix, dst_suffix in SIDE_MAP:
            mapping["Bip001-%s-%s" % (side_src, src_suffix)] = "%s_%s" % (dst_suffix, side_dst)
        for fs, fd in FINGER_MAP:
            for joint in ("", "1", "2"):
                src = "Bip001-%s-%s%s" % (side_src, fs, joint)
                idx = 1 + len(joint)
                mapping[src] = "%s_%02d_%s" % (fd, idx, side_dst)
        for tmpl, dst in TWIST_MAP:
            mapping[tmpl.format(S=side_src, s=side_dst)] = dst.format(s=side_dst)
    for name in source_names:
        if name in mapping:
            continue
        if name.startswith(HEAD_LIKE_PREFIXES):
            mapping[name] = "Head"
        elif name.startswith("Bn_l_kneePush") or name.startswith("Bn_l_elbowPush"):
            mapping[name] = "calf_l"
        elif name.startswith("Bn_r_kneePush") or name.startswith("Bn_r_elbowPush"):
            mapping[name] = "calf_r"
        elif name.startswith("l_jiaoshi"):
            mapping[name] = "foot_l"
        elif name.startswith("r_jiaoshi"):
            mapping[name] = "foot_r"
        elif name.startswith("xiongshi"):
            mapping[name] = "spine_05"
    return mapping


def log(msg):
    print("[RIG] %s" % msg)


# ---------------------------------------------------------------- load target
bpy.ops.wm.open_mainfile(filepath=target_blend)
target = next(o for o in bpy.data.objects if o.type == "ARMATURE")
target_bones = {b.name: b for b in target.data.bones}
log("target bones: %d" % len(target_bones))
# the armature node itself carries the game "Root" bone transform, so joint positions
# have to be read through the object matrix to land in component space
target_world = target.matrix_world.copy()


def tgt_head(name):
    return target_world @ target_bones[name].head_local


def tgt_tail(name):
    return target_world @ target_bones[name].tail_local

# ---------------------------------------------------------------- append source
with bpy.data.libraries.load(src_blend, link=False) as (data_from, data_to):
    data_to.objects = [n for n in data_from.objects]

src_objects = [o for o in data_to.objects if o is not None]
src_arm = next((o for o in src_objects if o.type == "ARMATURE"), None)
src_mesh = next((o for o in src_objects if o.type == "MESH"), None)
if src_arm is None or src_mesh is None:
    raise SystemExit("source armature/mesh not found")
for o in src_objects:
    bpy.context.collection.objects.link(o)
log("source mesh %s verts=%d groups=%d" % (src_mesh.name, len(src_mesh.data.vertices), len(src_mesh.vertex_groups)))

# ---------------------------------------------------------------- alignment
src_bones = {b.name: b for b in src_arm.data.bones}

pelvis_src = src_bones["Bip001-Pelvis"].head_local.copy()
head_src = src_bones["head_Bone001"].head_local.copy()
pelvis_dst = tgt_head("pelvis")
head_dst = tgt_head("Head")


def foot_frame(head_of, foot_l, foot_r, toe_l, toe_r):
    """Foot midpoint / horizontal forward direction of a rig."""
    fl, fr, tl, tr = head_of(foot_l), head_of(foot_r), head_of(toe_l), head_of(toe_r)
    mid = (fl + fr) * 0.5
    fwd = ((tl + tr) * 0.5) - mid
    fwd.z = 0.0
    if fwd.length < 1e-6:
        fwd = Vector((1.0, 0.0, 0.0))
    return mid, fwd.normalized()


foot_mid_src, forward_src = foot_frame(
    lambda n: src_bones[n].head_local, "Bip001-L-Foot", "Bip001-R-Foot",
    "Bip001-L-Toe0", "Bip001-R-Toe0")
foot_mid_dst, forward_dst = foot_frame(tgt_head, "foot_l", "foot_r", "ball_l", "ball_r")
log("source forward: %.3f %.3f | target forward: %.3f %.3f" % (
    forward_src.x, forward_src.y, forward_dst.x, forward_dst.y))

foot_src = min(
    src_bones["Bip001-L-Foot"].head_local.z,
    src_bones["Bip001-R-Foot"].head_local.z,
    src_bones["Bip001-L-Toe0"].head_local.z,
    src_bones["Bip001-R-Toe0"].head_local.z,
)

# rotate so the source faces the same way as the target rig, then match body height
angle = math.atan2(forward_dst.y, forward_dst.x) - math.atan2(forward_src.y, forward_src.x)
rot = Matrix.Rotation(angle, 4, "Z")

feet_dst = tgt_head("foot_l").z
scale = (head_dst.z - feet_dst) / (head_src.z - foot_src)
log("scale factor: %.5f (src height %.2f -> dst %.2f)" % (
    scale, head_src.z - foot_src, head_dst.z - feet_dst))

# anchor the foot joints on the target rig, then drop the whole mesh so the sole
# rests on the same ground plane the reference skeleton stands on
scaled_foot = rot @ foot_mid_src * scale
mat = Matrix.Scale(scale, 4) @ rot
mat.translation = Vector((foot_mid_dst.x - scaled_foot.x,
                          foot_mid_dst.y - scaled_foot.y,
                          0.0))

sole_dst = min(tgt_tail("ball_l").z, tgt_tail("ball_r").z)
lowest = min((mat @ v.co).z for v in src_mesh.data.vertices)
mat.translation.z += sole_dst - lowest
# animations drive the root bone at the origin, while the rest pose stores it ~96cm
# lower, so the mesh has to be authored in that grounded root space
mat.translation.z -= target_world.translation.z
log("root offset %.2f, sole now at %.2f" % (-target_world.translation.z, sole_dst - target_world.translation.z))

# bake the alignment into the mesh vertices (the source rig itself is discarded)
bake = src_mesh.matrix_world.inverted() @ mat @ src_mesh.matrix_world
src_mesh.data.transform(bake)
src_mesh.matrix_world = Matrix.Identity(4)

bpy.context.view_layer.update()
log("aligned: pelvis %.2f %.2f %.2f -> head %.2f %.2f %.2f (target %.2f %.2f %.2f)" % (
    *(mat @ pelvis_src), *(mat @ head_src), *head_dst))

# ---------------------------------------------------------------- remap weights
mapping = build_mapping([b.name for b in src_arm.data.bones])
unmapped = [b.name for b in src_arm.data.bones if b.name not in mapping]
log("unmapped source bones: %d (example: %s)" % (len(unmapped), unmapped[:6]))

src_group_names = {g.index: g.name for g in src_mesh.vertex_groups}
# snapshot weights before editing groups
weights = []
for v in src_mesh.data.vertices:
    entry = []
    for g in v.groups:
        gname = src_group_names.get(g.group)
        if gname is None:
            continue
        entry.append((gname, g.weight))
    weights.append(entry)

# skirt-ish chains map by nearest game skirt bone
skirt_targets = [n for n in target_bones if n.startswith("bns_skirt") or n.startswith("bns_frontSkirt")
                 or n.startswith("bns_ribbon") or n.startswith("bns_laterSkirt")]
log("skirt target bones: %d" % len(skirt_targets))


def nearest_skirt(src_bone_name):
    b = src_bones.get(src_bone_name)
    if b is None:
        return "pelvis"
    p = mat @ b.head_local
    best, best_d = None, 1e18
    for name in skirt_targets:
        tp = tgt_head(name)
        d = (tp - p).length
        if d < best_d:
            best, best_d = name, d
    return best or "pelvis"


for name in unmapped:
    if name.startswith(SKIRT_PREFIXES):
        mapping[name] = nearest_skirt(name)

for g in list(src_mesh.vertex_groups):
    src_mesh.vertex_groups.remove(g)

new_groups = {}
for gname in mapping.values():
    if gname not in target_bones:
        continue
    if gname not in new_groups:
        new_groups[gname] = src_mesh.vertex_groups.new(name=gname)

body_bones = [n for n in target_bones if n in
              ("pelvis", "spine_01", "spine_02", "spine_03", "spine_04", "spine_05",
               "neck_01", "neck_02", "Head", "clavicle_l", "clavicle_r", "upperarm_l",
               "upperarm_r", "lowerarm_l", "lowerarm_r", "hand_l", "hand_r", "thigh_l",
               "thigh_r", "calf_l", "calf_r", "foot_l", "foot_r", "ball_l", "ball_r")]


def nearest_body_bone(p):
    best, best_d = "pelvis", 1e18
    for name in body_bones:
        bp = tgt_head(name)
        d = (bp - p).length
        if d < best_d:
            best, best_d = name, d
    return best


filled = 0
for idx, entry in enumerate(weights):
    total = 0.0
    for gname, w in entry:
        target_name = mapping.get(gname)
        if target_name is None or target_name not in new_groups:
            continue
        # never let utility/twist-only bones dominate; keep as authored
        new_groups[target_name].add([idx], w, "REPLACE")
        total += w
    if total <= 1e-6:
        v = src_mesh.data.vertices[idx]
        world = src_mesh.matrix_world @ v.co
        bone = nearest_body_bone(world)
        if bone in new_groups:
            new_groups[bone].add([idx], 1.0, "REPLACE")
            filled += 1
log("vertices patched with nearest bone: %d" % filled)

# ---------------------------------------------------------------- modifiers
for m in list(src_mesh.modifiers):
    if m.type == "ARMATURE":
        src_mesh.modifiers.remove(m)
arm_mod = src_mesh.modifiers.new(name="Armature", type="ARMATURE")
arm_mod.object = target
src_mesh.parent = target
# the armature node carries the game Root transform, so move the mesh into armature
# space at the data level - relying on the parent inverse is not honoured consistently
# by the FBX exporter and leaves the imported bind pose shifted
src_mesh.data.transform(target.matrix_world.inverted())
src_mesh.matrix_parent_inverse = Matrix.Identity(4)

bpy.context.view_layer.objects.active = src_mesh
bpy.ops.object.select_all(action="DESELECT")
src_mesh.select_set(True)
bpy.ops.object.mode_set(mode="OBJECT")
bpy.ops.object.vertex_group_normalize_all(group_select_mode="ALL", lock_active=False)
bpy.ops.object.vertex_group_limit_total(group_select_mode="ALL", limit=8)
bpy.ops.object.vertex_group_clean(group_select_mode="ALL", limit=0.0005, keep_single=True)

# drop the leftover source rig
bpy.data.objects.remove(src_arm, do_unlink=True)

bpy.ops.wm.save_as_mainfile(filepath=out_blend)

# work in centimetres so UE (which treats FBX units as cm) receives the right size
bpy.context.scene.unit_settings.system = "METRIC"
bpy.context.scene.unit_settings.scale_length = 0.01
bpy.context.scene.unit_settings.length_unit = "CENTIMETERS"

bpy.ops.object.select_all(action="SELECT")
bpy.ops.export_scene.fbx(
    filepath=out_fbx,
    use_selection=True,
    object_types={"ARMATURE", "MESH"},
    add_leaf_bones=False,
    bake_anim=False,
    apply_scale_options="FBX_SCALE_NONE",
    axis_forward="-Z",
    axis_up="Y",
    path_mode="AUTO",
    mesh_smooth_type="FACE",
    use_mesh_modifiers=False,
)
log("exported %s" % out_fbx)
