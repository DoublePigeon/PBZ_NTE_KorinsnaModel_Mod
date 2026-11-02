"""Create a tiny skinned test mesh on the Hun skeleton for pipeline validation."""
import bpy
import sys
from mathutils import Vector

argv = sys.argv
argv = argv[argv.index("--") + 1:] if "--" in argv else []
skeleton_blend, out_fbx = argv[0], argv[1]

bpy.ops.wm.open_mainfile(filepath=skeleton_blend)
arm = bpy.data.objects["HunSkinSkeleton"]

# place a sphere at the chest so it is easy to spot in game
bpy.ops.object.select_all(action="DESELECT")
bpy.ops.mesh.primitive_uv_sphere_add(segments=16, ring_count=8, radius=12.0, location=(0.0, 0.0, 0.0))
sphere = bpy.context.active_object
sphere.name = "TestSphere"

bone = arm.data.bones["spine_03"]
head = arm.matrix_world @ bone.head_local
sphere.location = head
bpy.ops.object.transform_apply(location=True, rotation=True, scale=True)

vg = sphere.vertex_groups.new(name="spine_03")
vg.add(list(range(len(sphere.data.vertices))), 1.0, "REPLACE")

mat = bpy.data.materials.new("TestMagenta")
mat.use_nodes = True
bsdf = mat.node_tree.nodes.get("Principled BSDF")
bsdf.inputs["Base Color"].default_value = (1.0, 0.0, 1.0, 1.0)
bsdf.inputs["Emission Color"].default_value = (1.0, 0.0, 1.0, 1.0)
bsdf.inputs["Emission Strength"].default_value = 3.0
sphere.data.materials.append(mat)

mod = sphere.modifiers.new(name="Armature", type="ARMATURE")
mod.object = arm
sphere.parent = arm

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
)
print("TESTFBX saved", out_fbx)
