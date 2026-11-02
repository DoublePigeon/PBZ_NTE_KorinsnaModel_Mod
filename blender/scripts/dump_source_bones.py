import bpy, sys, json
argv = sys.argv
argv = argv[argv.index("--") + 1:] if "--" in argv else []
out = argv[0]
bpy.ops.wm.open_mainfile(filepath=r"J:\VS_Projects\PBZ_KorinsnaSkinMod\KorinsnaModel\npc_036.blend")
arm = None
mesh = None
for o in bpy.data.objects:
    if o.type == 'ARMATURE':
        arm = o
    if o.type == 'MESH' and 'skin' in o.name.lower():
        mesh = o
bones = []
for b in arm.data.bones:
    bones.append({"name": b.name, "parent": b.parent.name if b.parent else None,
                  "head": [round(v, 4) for v in b.head_local]})
data = {"bones": bones, "mesh": mesh.name, "vertex_groups": [g.name for g in mesh.vertex_groups]}
with open(out, "w", encoding="utf-8") as f:
    json.dump(data, f, ensure_ascii=False, indent=1)
print("WROTE", out, len(bones))