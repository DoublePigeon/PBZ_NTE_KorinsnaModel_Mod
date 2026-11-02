import bpy
bpy.ops.wm.open_mainfile(filepath=r"J:\VS_Projects\PBZ_KorinsnaSkinMod\blender\out\Korinsna_Rigged.blend")
for o in bpy.data.objects:
    if o.type == 'MESH':
        print("MESH", o.name, "dims", tuple(round(v,2) for v in o.dimensions), "loc", tuple(round(v,2) for v in o.location))
        zs = [ (o.matrix_world @ v.co).z for v in o.data.vertices ]
        print("Z range %.2f .. %.2f" % (min(zs), max(zs)))
        print("groups", len(o.vertex_groups), "modifiers", [m.type for m in o.modifiers])
        print("parent", o.parent.name if o.parent else None, "matrix_world", [round(v,2) for v in o.matrix_world.to_translation()])