"""Dump everything needed to align the Korinsna model with the game skeleton.

Usage:
  blender -b --python inspect_apose.py -- <in.blend> <out.json>

Writes rest-pose and posed world-space joint positions for every bone so two
blends can be diffed (is the game pose baked into the rest pose?), plus the
mesh bounds that decide scale / offset.
"""
import bpy
import json
import sys

argv = sys.argv
argv = argv[argv.index("--") + 1:] if "--" in argv else []
src, out = argv[0], argv[1]

bpy.ops.wm.open_mainfile(filepath=src)

result = {
    "file": src,
    "blender": bpy.app.version_string,
    "units": {
        "system": bpy.context.scene.unit_settings.system,
        "scale_length": bpy.context.scene.unit_settings.scale_length,
        "length_unit": bpy.context.scene.unit_settings.length_unit,
    },
    "objects": [],
}

arm_obj = None
for obj in bpy.data.objects:
    entry = {
        "name": obj.name,
        "type": obj.type,
        "parent": obj.parent.name if obj.parent else None,
        "parent_type": obj.parent_type if obj.parent else None,
        "loc": [round(v, 4) for v in obj.matrix_world.to_translation()],
        "rot_euler": [round(v, 4) for v in obj.matrix_world.to_euler()],
        "scale": [round(v, 4) for v in obj.matrix_world.to_scale()],
    }
    if obj.type == "MESH":
        world = [obj.matrix_world @ v.co for v in obj.data.vertices]
        entry.update({
            "verts": len(obj.data.vertices),
            "polys": len(obj.data.polygons),
            "uv_layers": [uv.name for uv in obj.data.uv_layers],
            "materials": [m.name if m else None for m in obj.data.materials],
            "vgroups": len(obj.vertex_groups),
            "modifiers": [(m.type, getattr(m, "object", None).name if getattr(m, "object", None) else None)
                          for m in obj.modifiers],
            "bounds_min": [round(min(p[i] for p in world), 3) for i in range(3)],
            "bounds_max": [round(max(p[i] for p in world), 3) for i in range(3)],
        })
    if obj.type == "ARMATURE":
        arm_obj = obj
        entry.update({
            "pose_position": obj.data.pose_position,
            "bones": len(obj.data.bones),
        })
    result["objects"].append(entry)

if arm_obj is not None:
    mat = arm_obj.matrix_world
    rest = {}
    pose = {}
    parents = {}
    for bone in arm_obj.data.bones:
        rest[bone.name] = {
            "head": [round(v, 4) for v in (mat @ bone.head_local)],
            "tail": [round(v, 4) for v in (mat @ bone.tail_local)],
        }
        parents[bone.name] = bone.parent.name if bone.parent else None
    for pbone in arm_obj.pose.bones:
        pose[pbone.name] = {
            "head": [round(v, 4) for v in (mat @ pbone.head)],
            "tail": [round(v, 4) for v in (mat @ pbone.tail)],
        }
    result["armature"] = {
        "object": arm_obj.name,
        "parents": parents,
        "rest": rest,
        "pose": pose,
    }

if arm_obj is not None:
    worst = 0.0
    worst_bone = None
    for name, r in result["armature"]["rest"].items():
        p = result["armature"]["pose"][name]
        d = max(abs(r["head"][i] - p["head"][i]) for i in range(3))
        if d > worst:
            worst, worst_bone = d, name
    result["rest_vs_pose_max_delta"] = round(worst, 4)
    result["rest_vs_pose_worst_bone"] = worst_bone

with open(out, "w", encoding="utf-8") as fh:
    json.dump(result, fh, ensure_ascii=False, indent=1)

print("###SUMMARY###")
print(json.dumps({
    "file": src,
    "units": result["units"],
    "armature": [
        (o["name"], o.get("bones"), o.get("pose_position"), o["loc"], o["rot_euler"], o["scale"])
        for o in result["objects"] if o["type"] == "ARMATURE"
    ],
    "mesh": [
        (o["name"], o.get("verts"), o.get("bounds_min"), o.get("bounds_max"))
        for o in result["objects"] if o["type"] == "MESH"
    ],
    "rest_vs_pose_max_delta": result.get("rest_vs_pose_max_delta"),
    "rest_vs_pose_worst_bone": result.get("rest_vs_pose_worst_bone"),
}, ensure_ascii=False))
print("###END###")
