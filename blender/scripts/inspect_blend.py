import bpy, json, sys, os

out = {}
out["blender_version"] = bpy.app.version_string
out["file"] = bpy.data.filepath
out["objects"] = []
for o in bpy.data.objects:
    entry = {
        "name": o.name,
        "type": o.type,
        "parent": o.parent.name if o.parent else None,
        "loc": [round(v, 4) for v in o.location],
        "scale": [round(v, 4) for v in o.scale],
        "dims": [round(v, 4) for v in o.dimensions],
    }
    if o.type == 'MESH':
        entry["verts"] = len(o.data.vertices)
        entry["polys"] = len(o.data.polygons)
        entry["uv_layers"] = [uv.name for uv in o.data.uv_layers]
        entry["materials"] = [m.name if m else None for m in o.data.materials]
        entry["vgroups"] = len(o.vertex_groups)
        entry["shade_smooth"] = bool(o.data.polygons[0].use_smooth) if len(o.data.polygons) else None
        entry["modifiers"] = [m.type for m in o.modifiers]
    if o.type == 'ARMATURE':
        arm = o.data
        entry["bones"] = len(arm.bones)
        entry["bone_names"] = [b.name for b in arm.bones][:40]
        entry["pose_position"] = arm.pose_position
        entry["axes"] = [round(v, 4) for v in o.matrix_world.to_euler()]
    out["objects"].append(entry)

out["materials"] = []
for m in bpy.data.materials:
    mi = {"name": m.name, "use_nodes": m.use_nodes, "nodes": []}
    if m.use_nodes:
        for n in m.node_tree.nodes:
            node = {"type": n.type, "name": n.name}
            if n.type == 'TEX_IMAGE' and n.image:
                node["image"] = n.image.name
                node["size"] = list(n.image.size)
            if n.type == 'BSDF_PRINCIPLED':
                node["base_color"] = [round(v, 3) for v in n.inputs["Base Color"].default_value]
            mi["nodes"].append(node)
    out["materials"].append(mi)

out["images"] = [{"name": i.name, "size": list(i.size)} for i in bpy.data.images]

print("###JSON_START###")
print(json.dumps(out, ensure_ascii=False))
print("###JSON_END###")
