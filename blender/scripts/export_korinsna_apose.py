"""Export the APOSE Korinsna model as a self-contained FBX for the retarget pipeline.

The mesh keeps its own `Bip001-*` skeleton: nothing is rebound onto the game rig.
What this script fixes is only what the FBX/UE round trip would otherwise mangle:

* bakes the armature object transform (the APOSE file carries a x2.4797 scale on the
  armature object, which UE would turn into a scale on the root bone),
* clears the pose so the exported bind pose is the rest pose,
* names the armature object `Root` (Blender always exports it as a node, and UE turns
  that node into bone 0 - matching what the game skeleton has),
* exports in centimetres with the same axis/unit settings the previous working
  pipeline used (`rig_korinsna.py`).

Usage:
  blender -b --python export_korinsna_apose.py [-- <in.blend> <out.fbx> <scale>]
"""
import os
import sys

import bpy

argv = sys.argv
argv = argv[argv.index("--") + 1:] if "--" in argv else []
SRC = argv[0] if len(argv) > 0 else r"J:\VS_Projects\PBZ_KorinsnaSkinMod\KorinsnaModel\npc_036_APOSE.blend"
OUT = argv[1] if len(argv) > 1 else r"J:\VS_Projects\PBZ_KorinsnaSkinMod\blender\out\Korinsna_APose.fbx"
SCALE = float(argv[2]) if len(argv) > 2 else 1.0
# No extra yaw: the model is authored facing the direction the game expects. An earlier build added
# +90 degrees here, which showed up in game as a 90 degree counter-clockwise error.
ROT_Z = float(argv[3]) if len(argv) > 3 else 0.0
# the game skeleton's Root bone sits at -96 cm; the runtime script aligns the mesh to the hero by
# measuring feet positions instead of relying on a baked offset
OFFSET = (0.0, 0.0, 0.0)

bpy.ops.wm.open_mainfile(filepath=SRC)

arm = next(o for o in bpy.data.objects if o.type == "ARMATURE")
mesh = next(o for o in bpy.data.objects if o.type == "MESH" and "skin" in o.name.lower())

print("source armature %s scale %s  mesh %s" % (
    arm.name, tuple(round(v, 4) for v in arm.matrix_world.to_scale()), mesh.name))

# The APOSE file only changes the pose; what we want shipped is that pose as the *bind* pose, so
# the retargeter compares motion against the same reference the game uses.
#
# Two steps are required, and getting only one of them is what made the hands come out open and the
# limbs stretch:
#
#   1. bake the posed deformation into the MESH VERTICES (apply the armature modifier while the rest
#      pose is still the original one), then
#   2. make that pose the rest pose of the ARMATURE (armature_apply).
#
# With only step 2 the bones sit in the new pose while the vertices stay at the old shape, so the mesh
# is bound to a skeleton it does not match: the engine renders the un-posed silhouette and every
# animation deforms from an inconsistent bind pose.
bpy.context.view_layer.objects.active = arm
if bpy.context.mode != "OBJECT":
    bpy.ops.object.mode_set(mode="OBJECT")
arm.data.pose_position = "POSE"

bpy.ops.object.select_all(action="DESELECT")
bpy.context.view_layer.objects.active = mesh
mesh.select_set(True)

# Blender refuses to apply an armature modifier to a mesh with shape keys. The mod never ships morph
# targets (the UE import runs with morph targets off), so the keys are only in the way here.
if mesh.data.shape_keys is not None:
    mesh.shape_key_clear()
    print("removed shape keys (morph targets are not shipped)")

baked = []
for modifier in list(mesh.modifiers):
    if modifier.type != "ARMATURE":
        continue
    # the name has to be read before applying: afterwards the reference is dangling
    modifier_name = str(modifier.name)
    try:
        bpy.ops.object.modifier_apply(modifier=modifier_name)
        baked.append(modifier_name)
    except RuntimeError as exc:
        print("could not bake modifier: %s" % exc)
bpy.ops.object.select_all(action="DESELECT")
print("baked the current pose into the mesh vertices: %s" % (baked or "nothing"))

bpy.context.view_layer.objects.active = arm
arm.select_set(True)
bpy.ops.object.mode_set(mode="POSE")
bpy.ops.pose.select_all(action="SELECT")
bpy.ops.pose.armature_apply(selected=False)
bpy.ops.object.mode_set(mode="OBJECT")
print("baked the current pose as the rest pose")

# the modifier is gone after applying it; put it back so the file stays usable in Blender
if not any(m.type == "ARMATURE" for m in mesh.modifiers):
    restored = mesh.modifiers.new(name="Armature", type="ARMATURE")
    restored.object = arm

# optional uniform scale on top of the model's own size
if SCALE != 1.0:
    arm.scale = [v * SCALE for v in arm.scale]
    mesh.scale = [v * SCALE for v in mesh.scale]

if ROT_Z:
    import math
    arm.rotation_euler.z += math.radians(ROT_Z)

arm.location.x += OFFSET[0]
arm.location.y += OFFSET[1]
arm.location.z += OFFSET[2]

# bake object transforms into the data; the armature scale must not survive as a bone scale
for obj in bpy.data.objects:
    obj.select_set(obj.type in {"ARMATURE", "MESH"})
bpy.context.view_layer.objects.active = arm
if bpy.context.mode != "OBJECT":
    bpy.ops.object.mode_set(mode="OBJECT")
bpy.ops.object.parent_clear(type="CLEAR_KEEP_TRANSFORM")
bpy.ops.object.transform_apply(location=True, rotation=True, scale=True)

mesh.parent = arm
mesh.matrix_parent_inverse.identity()

arm.name = "Root"
arm.data.name = "Root"

bpy.context.scene.unit_settings.system = "METRIC"
bpy.context.scene.unit_settings.scale_length = 0.01
bpy.context.scene.unit_settings.length_unit = "CENTIMETERS"

os.makedirs(os.path.dirname(OUT), exist_ok=True)
bpy.ops.object.select_all(action="DESELECT")
arm.select_set(True)
mesh.select_set(True)
bpy.context.view_layer.objects.active = arm
bpy.ops.export_scene.fbx(
    filepath=OUT,
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

world = [mesh.matrix_world @ v.co for v in mesh.data.vertices]
print("###EXPORT###")
print("fbx=%s" % OUT)
print("armature=%s bones=%d scale=%s" % (
    arm.name, len(arm.data.bones), [round(v, 5) for v in arm.matrix_world.to_scale()]))
print("mesh=%s verts=%d vgroups=%d bounds z %.2f..%.2f x %.2f..%.2f y %.2f..%.2f" % (
    mesh.name, len(mesh.data.vertices), len(mesh.vertex_groups),
    min(p.z for p in world), max(p.z for p in world),
    min(p.x for p in world), max(p.x for p in world),
    min(p.y for p in world), max(p.y for p in world)))
print("###END###")
