"""Rewrite BlankPart.fbx with a tiny triangle instead of a zero-area one.

The mesh has to stay an ordinary rendered primitive (see make_blank_part.py for why), so the geometry
is a small triangle placed inside the character's pelvis. The existing FBX is reused as the source of
the armature, because the .blend it was originally exported from is no longer in the repo.

Usage: blender.exe -b --python make_tiny_blank.py
"""
import bpy

SRC = r"J:\VS_Projects\PBZ_KorinsnaSkinMod\blender\out\BlankPart.fbx"
OUT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod\blender\out\BlankPart.fbx"

SIZE = 0.6      # cm
HEIGHT = 95.0   # pelvis height in the hero skeleton's units (cm)

bpy.ops.wm.read_factory_settings(use_empty=True)
bpy.ops.import_scene.fbx(filepath=SRC)

meshes = [ob for ob in bpy.data.objects if ob.type == "MESH"]
if not meshes:
    raise SystemExit("no mesh in %s" % SRC)
obj = meshes[0]
print("reusing mesh object", obj.name, "verts", len(obj.data.vertices))

obj.data.vertices[0].co = (0.0, 0.0, HEIGHT)
obj.data.vertices[1].co = (SIZE, 0.0, HEIGHT)
obj.data.vertices[2].co = (0.0, SIZE, HEIGHT)
obj.data.update()

armatures = [ob for ob in bpy.data.objects if ob.type == "ARMATURE"]
print("armatures", [(a.name, len(a.data.bones)) for a in armatures])
print("vertex groups", [g.name for g in obj.vertex_groups])

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
print("TINYBLANK saved", OUT)
