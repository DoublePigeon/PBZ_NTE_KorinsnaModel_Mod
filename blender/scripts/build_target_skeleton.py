"""Build the game's Hun skin skeleton as a Blender armature from the UE4SS dump.

Usage:
    blender.exe -b --factory-startup --python build_target_skeleton.py -- <refbones.txt> <out.blend> <out.fbx>
"""
import bpy
import json
import math
import os
import sys
from mathutils import Matrix, Quaternion, Vector

argv = sys.argv
argv = argv[argv.index("--") + 1:] if "--" in argv else []
refbones_path, out_blend, out_fbx = argv[0], argv[1], argv[2]


def parse_bones(path):
    bones = []
    cur = None
    collecting = False
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.rstrip("\n")
            if line.startswith("== after-reset") and "nb=" in line:
                collecting = True
                continue
            if line == "== END ==":
                if collecting and bones:
                    break
                collecting = False
                continue
            if not collecting or "|" not in line:
                continue
            idx, name, parent, t, q, s = line.split("|")
            tx, ty, tz = [float(v) for v in t.split(",")]
            qx, qy, qz, qw = [float(v) for v in q.split(",")]
            bones.append({
                "i": int(idx),
                "name": name,
                "parent": parent,
                "loc": (tx, ty, tz),
                "quat": (qx, qy, qz, qw),
            })
    return bones


bones = parse_bones(refbones_path)
print("parsed bones:", len(bones))
if not bones:
    raise SystemExit("no bones parsed")

for ob in list(bpy.data.objects):
    bpy.data.objects.remove(ob, do_unlink=True)

arm_data = bpy.data.armatures.new("HunSkinSkeleton")
arm = bpy.data.objects.new("HunSkinSkeleton", arm_data)
bpy.context.collection.objects.link(arm)
bpy.context.view_layer.objects.active = arm
bpy.ops.object.mode_set(mode="EDIT")

# The Blender -> FBX -> UE pipe mirrors bone rotations across the XZ plane while
# keeping joint positions: a Blender bone frame R ends up as F*R*F in the engine.
# Conjugating by the same mirror here makes the exported rest pose come out exactly
# as the game's, otherwise the mesh renders rotated 90 degrees and sunk into the ground.
MIRROR = Matrix(((1.0, 0.0, 0.0), (0.0, -1.0, 0.0), (0.0, 0.0, 1.0)))

# absolute transforms in component space, exactly as dumped
abs_mat = {}
children = {}
for b in bones:
    q = Quaternion((b["quat"][3], b["quat"][0], b["quat"][1], b["quat"][2])).normalized()
    rot = (MIRROR @ q.to_matrix() @ MIRROR).to_4x4()
    rot.translation = Vector(b["loc"])
    abs_mat[b["name"]] = rot
    children.setdefault(b["parent"], []).append(b["name"])

# The "Root" bone becomes the armature node itself. Blender always emits an extra FBX
# node for the armature object, and Unreal turns it into an extra root joint - which
# left the imported mesh with 275 bones instead of the 274 the game skeleton has.
root_mat = abs_mat["Root"]
arm.name = "Root"
arm_data.name = "Root"
arm.matrix_world = root_mat
scaffold = [b for b in bones if b["name"] != "Root"]

edit_bones = {}
for b in scaffold:
    world = abs_mat[b["name"]]
    local = root_mat.inverted() @ world  # armature (== Root) space
    eb = arm_data.edit_bones.new(b["name"])
    eb.head = local.translation
    rotation = local.to_3x3()
    direction = (rotation @ Vector((0.0, 1.0, 0.0))).normalized()
    up = (rotation @ Vector((0.0, 0.0, 1.0))).normalized()
    kids = children.get(b["name"], [])
    if kids:
        child_world = abs_mat[kids[0]].translation
        length = (root_mat.inverted() @ child_world - eb.head).length
        if length < 1.0:
            length = 8.0
    else:
        length = 6.0
    eb.tail = eb.head + direction * length
    eb.align_roll(up)
    edit_bones[b["name"]] = eb

# second pass: parents (must exist first)
for b in scaffold:
    if b["parent"] in edit_bones:
        edit_bones[b["name"]].parent = edit_bones[b["parent"]]
        edit_bones[b["name"]].use_connect = False

bpy.ops.object.mode_set(mode="OBJECT")
arm_data.display_type = "STICK"

# verify: bone transforms relative to the armature node must equal Root-relative data
worst = 0.0
worst_name = None
for b in scaffold:
    got = root_mat @ arm_data.bones[b["name"]].matrix_local
    exp = abs_mat[b["name"]]
    drift = max((got.translation - exp.translation).length,
                max(abs(got.to_3x3()[r][c] - exp.to_3x3()[r][c]) for r in range(3) for c in range(3)) * 10.0)
    if drift > worst:
        worst, worst_name = drift, b["name"]
print("bone count:", len(arm_data.bones), "+ armature node =", len(arm_data.bones) + 1)
print("max bone matrix drift:", round(worst, 6), "at", worst_name)

bpy.ops.wm.save_as_mainfile(filepath=out_blend)

bpy.ops.object.select_all(action="SELECT")
bpy.ops.export_scene.fbx(
    filepath=out_fbx,
    use_selection=True,
    object_types={"ARMATURE"},
    add_leaf_bones=False,
    bake_anim=False,
    use_armature_deform_only=False,
    apply_scale_options="FBX_SCALE_NONE",
    axis_forward="-Z",
    axis_up="Y",
    path_mode="AUTO",
)
print("saved", out_blend, out_fbx)
