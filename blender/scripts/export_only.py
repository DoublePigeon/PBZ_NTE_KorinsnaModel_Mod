"""Re-export `blender/out/Korinsna_Rigged.blend` to FBX after manual weight edits.

Run with:  blender.exe -b blender/out/Korinsna_Rigged.blend --python blender/scripts/export_only.py
"""
import bpy

out_fbx = r"J:\VS_Projects\PBZ_KorinsnaSkinMod\blender\out\Korinsna_Body.fbx"

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
print("exported", out_fbx)
