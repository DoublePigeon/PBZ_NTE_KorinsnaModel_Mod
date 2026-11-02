import bpy
bpy.ops.wm.open_mainfile(filepath=r"J:\VS_Projects\PBZ_KorinsnaSkinMod\KorinsnaModel\npc_036.blend")
for o in bpy.data.objects:
    if o.type == 'MESH':
        for i, uv in enumerate(o.data.uv_layers):
            us = [d.uv[0] for d in uv.data]
            vs = [d.uv[1] for d in uv.data]
            print("UV%d %s: u %.3f..%.3f v %.3f..%.3f" % (i, uv.name, min(us), max(us), min(vs), max(vs)))