"""Render the rigged mesh with one flat colour per material slot so the palette render
from the game can be matched back to actual body regions."""
import math

import bpy
from mathutils import Vector

bpy.ops.wm.open_mainfile(filepath=r"J:\VS_Projects\PBZ_KorinsnaSkinMod\blender\out\Korinsna_Rigged_source.blend")

COLORS = [
    ("0 red", (1.0, 0.0, 0.0)),
    ("1 green", (0.0, 1.0, 0.0)),
    ("2 blue", (0.0, 0.0, 1.0)),
    ("3 yellow", (1.0, 1.0, 0.0)),
    ("4 magenta", (1.0, 0.0, 1.0)),
    ("5 cyan", (0.0, 1.0, 1.0)),
    ("6 orange", (1.0, 0.45, 0.0)),
    ("7 purple", (0.5, 0.0, 1.0)),
]

mesh = next(o for o in bpy.data.objects if o.type == "MESH")
for index, (name, rgb) in enumerate(COLORS):
    mat = bpy.data.materials.new("SLOT_%d" % index)
    mat.use_nodes = True
    nodes = mat.node_tree.nodes
    bsdf = next((n for n in nodes if n.type == "BSDF_PRINCIPLED"), None)
    if bsdf is None:
        bsdf = nodes.new("ShaderNodeBsdfPrincipled")
        out_node = next((n for n in nodes if n.type == "OUTPUT_MATERIAL"), None)
        if out_node is None:
            out_node = nodes.new("ShaderNodeOutputMaterial")
        mat.node_tree.links.new(bsdf.outputs[0], out_node.inputs["Surface"])
    bsdf.inputs["Base Color"].default_value = (rgb[0], rgb[1], rgb[2], 1.0)
    bsdf.inputs["Roughness"].default_value = 1.0
    if index < len(mesh.data.materials):
        mesh.data.materials[index] = mat
    else:
        mesh.data.materials.append(mat)

scene = bpy.context.scene
scene.render.engine = "BLENDER_EEVEE"
scene.render.resolution_x = 700
scene.render.resolution_y = 900
scene.world = bpy.data.worlds.new("W")
scene.world.use_nodes = True
bg = next((n for n in scene.world.node_tree.nodes if n.type == "BACKGROUND"), None)
if bg is not None:
    bg.inputs[0].default_value = (0.05, 0.05, 0.06, 1.0)

ws = [mesh.matrix_world @ v.co for v in mesh.data.vertices]
cx = (min(v.x for v in ws) + max(v.x for v in ws)) / 2
cy = (min(v.y for v in ws) + max(v.y for v in ws)) / 2
zmin, zmax = min(v.z for v in ws), max(v.z for v in ws)
height = zmax - zmin

cam_data = bpy.data.cameras.new("C")
cam_data.lens = 55
cam = bpy.data.objects.new("C", cam_data)
bpy.context.collection.objects.link(cam)
scene.camera = cam
for tag, angle in (("front", 0.0), ("back", 180.0)):
    a = math.radians(angle)
    dist = height * 1.4
    cam.location = Vector((cx + dist * math.sin(a), cy - dist * math.cos(a), (zmin + zmax) / 2))
    cam.rotation_euler = (math.radians(90), 0, a)
    light_data = bpy.data.lights.new("L", type="SUN")
    light_data.energy = 4.0
    light = bpy.data.objects.new("L", light_data)
    bpy.context.collection.objects.link(light)
    light.rotation_euler = (math.radians(60), 0, a + math.radians(25))
    scene.render.filepath = r"J:\VS_Projects\PBZ_KorinsnaSkinMod\extract\slots-%s.png" % tag
    bpy.ops.render.render(write_still=True)
    bpy.data.objects.remove(light, do_unlink=True)
print("slot render done")
