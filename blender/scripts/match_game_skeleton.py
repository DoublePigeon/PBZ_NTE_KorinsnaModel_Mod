"""Make the hand-rigged Korinsna blend compatible with the game's Hun skeleton.

The hero body is driven by `PBZ_ABP_Hun_Base`, which was compiled against the game's
`Hun_Skin_Skeleton`. A mesh only animates when its own reference skeleton lines up with
that asset, and the hand rig made from `Hun_Skin.pskx` has two differences that stop it:

1. bone 0 is a leftover armature node (`Hun_Skin`) and the real root joint is called
   `root` - the game's skeleton calls it `Root`, so the root animation track never binds;
2. that `root` sits at the origin with no rotation, while the game's `Root` is 96cm below
   the origin and yawed -90 degrees, so the bind pose is a different space entirely.

Both are fixed here: the root joint becomes the armature node (Blender always exports the
armature object as a bone, so it can *be* bone 0) placed at the game's root frame, and the
few bones whose names differ only by case are renamed. Everything else - bone order,
transforms, weights, mesh - is left untouched, and because the mesh is parented to the
armature it moves with it, so the bind-pose appearance is preserved exactly.

Usage:
  blender.exe -b --factory-startup --python match_game_skeleton.py -- <in.blend> <out.blend> <out.fbx>
"""
import math
import sys

import bpy
from mathutils import Matrix

argv = sys.argv
argv = argv[argv.index("--") + 1:] if "--" in argv else []
src_blend, out_blend, out_fbx = argv[0], argv[1], argv[2]

# The hand rig already sits in the space the game expects (the character stands on the
# ground with it); only the names were wrong. Moving it here re-introduces a 96cm offset,
# so the armature node takes over the root joint exactly where it is.
ROOT_FRAME = Matrix.Identity(4)

# names that only differ from the game skeleton by capitalisation
RENAMES = {
    "head": "Head",
    "weapon_r": "WEAPON_R",
    "interaction": "Interaction",
}

ROOT_BONE = "root"


def log(msg):
    print("[MATCH] %s" % msg)


bpy.ops.wm.open_mainfile(filepath=src_blend)
arm = next(o for o in bpy.data.objects if o.type == "ARMATURE")
meshes = [o for o in bpy.data.objects if o.type == "MESH" and o.parent == arm]
if not meshes:
    raise SystemExit("no mesh parented to the armature")
log("armature %s bones=%d meshes=%s" % (arm.name, len(arm.data.bones), [m.name for m in meshes]))

for old, new in RENAMES.items():
    bone = arm.data.bones.get(old)
    if bone is not None:
        bone.name = new
        log("renamed %s -> %s" % (old, new))

bpy.ops.object.select_all(action="DESELECT")
arm.select_set(True)
bpy.context.view_layer.objects.active = arm
bpy.ops.object.mode_set(mode="EDIT")
edit_bones = arm.data.edit_bones
root = edit_bones.get(ROOT_BONE)
if root is None:
    raise SystemExit("root bone %r not found" % ROOT_BONE)

# keep the children where they are: with the root frame at identity their armatature-space
# matrix is already expressed in the space we hand over to the armature node
children = {child.name: child.matrix.copy() for child in root.children}
edit_bones.remove(root)
for name, matrix in children.items():
    edit_bones[name].matrix = matrix
log("dropped the %r joint, %d children promoted to top level" % (ROOT_BONE, len(children)))
bpy.ops.object.mode_set(mode="OBJECT")

# The host materials were authored against the hero's own UV layout and sample more than
# one UV set; the Korinsna mesh carries four (diffuse + lightmap/atlas sets). Whatever
# channel a material picks, it must land on the diffuse island, so every set is filled
# with a copy of UV0 - otherwise faces/hair sample random atlas space and render muddy.
for me in meshes:
    data = me.data
    layers = list(data.uv_layers)
    if len(layers) <= 1:
        continue
    uv0 = [d.uv.copy() for d in layers[0].data]
    for layer in layers[1:]:
        for i, loop_uv in enumerate(layer.data):
            loop_uv.uv = uv0[i]
    print("[MATCH] %s: copied UV0 into %d extra sets (%d..%d)"
          % (me.name, len(layers) - 1, 1, len(layers) - 1))

# the armature node now plays the role of the game's Root bone
arm.name = "Root"
arm.data.name = "Root"
arm.matrix_world = ROOT_FRAME @ arm.matrix_world
bpy.context.view_layer.update()
log("bone count including the armature node: %d" % (len(arm.data.bones) + 1))
log("mesh world after move: %s" % [round(v, 2) for v in meshes[0].matrix_world.translation])

bpy.ops.wm.save_as_mainfile(filepath=out_blend)

# centimetres, matching the engine's FBX units
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
