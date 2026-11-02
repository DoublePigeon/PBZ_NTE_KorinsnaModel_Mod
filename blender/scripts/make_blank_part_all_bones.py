"""Build the blank part mesh so it keeps every bone of the game skeleton active.

Two constraints have to hold at the same time, and they pull in opposite directions:

  * the mesh must be invisible - it replaces all of the hero's outfit,
  * the mesh must stay a normal rendered primitive whose LOD references *every* bone.

Why the second one matters: the hero's body component is what the retargeter copies its pose from.
The engine only refreshes that component's bone transforms while it is being rendered, and the
transform array it fills is sized by the bones the current LOD uses (`ActiveBoneIndices`, derived from
skin weights). A single triangle weighted to one bone produces a bone list that is far too short, the
retarget node refuses to run, and the model freezes in its reference pose.

So: one tiny triangle per bone, placed at that bone's rest position and weighted 1.0 to it. Every bone
is used, the geometry stays sub-millimetre scale (each triangle is ~0.4 cm across and sits inside the
body part it belongs to), so nothing is visible while the animation keeps running.

Usage: blender.exe -b --python make_blank_part_all_bones.py
"""
import bpy

SRC = r"J:\VS_Projects\PBZ_KorinsnaSkinMod\blender\out\BlankPart.fbx"
OUT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod\blender\out\BlankPart.fbx"

SIZE = 0.4  # cm

bpy.ops.wm.read_factory_settings(use_empty=True)
bpy.ops.import_scene.fbx(filepath=SRC)

armatures = [ob for ob in bpy.data.objects if ob.type == "ARMATURE"]
if not armatures:
    raise SystemExit("no armature in %s" % SRC)
arm = armatures[0]
bones = list(arm.data.bones)
print("armature", arm.name, "bones", len(bones))

for ob in [o for o in bpy.data.objects if o.type == "MESH"]:
    bpy.data.objects.remove(ob, do_unlink=True)

mesh = bpy.data.meshes.new("BlankPart")
verts = []
faces = []
for index, bone in enumerate(bones):
    pivot = bone.head_local
    base = len(verts)
    verts.append((pivot.x, pivot.y, pivot.z))
    verts.append((pivot.x + SIZE, pivot.y, pivot.z))
    verts.append((pivot.x, pivot.y + SIZE, pivot.z))
    faces.append((base, base + 1, base + 2))

mesh.from_pydata(verts, [], faces)
mesh.update()

obj = bpy.data.objects.new("BlankPart", mesh)
bpy.context.collection.objects.link(obj)

group_by_bone = {}
for index, bone in enumerate(bones):
    group = group_by_bone.get(bone.name)
    if group is None:
        group = obj.vertex_groups.new(name=bone.name)
        group_by_bone[bone.name] = group
    group.add([index * 3, index * 3 + 1, index * 3 + 2], 1.0, "REPLACE")

mat = bpy.data.materials.new("BlankMat")
mat.use_nodes = True
obj.data.materials.append(mat)

mod = obj.modifiers.new(name="Armature", type="ARMATURE")
mod.object = arm
obj.parent = arm

# the skinned mesh sits in the armature's own space
obj.matrix_parent_inverse = arm.matrix_world.inverted()

bpy.context.scene.unit_settings.system = "METRIC"
bpy.context.scene.unit_settings.scale_length = 0.01
bpy.context.scene.unit_settings.length_unit = "CENTIMETERS"

bpy.ops.object.select_all(action="SELECT")
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
)
print("ALLBONESBLANK saved", OUT, "bones", len(bones), "verts", len(verts))
