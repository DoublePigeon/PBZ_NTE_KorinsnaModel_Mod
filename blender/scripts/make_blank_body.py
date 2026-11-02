"""Build the blank hero body from the game's own bone hierarchy.

Why not just import a skeleton
    The glTF export of `Hun_Body_Simple` contains the game's bone hierarchy as parented empties (no
    skin), so Blender does not create an armature. This script rebuilds an armature from that
    hierarchy - same names, same parents, same rest positions - which is what makes the resulting blank
    mesh keep exactly the game mesh's bone list.

Why the bone list has to match
    The engine only creates the hero's AnimBP instance when
    `AnimSkeleton->IsCompatibleMesh(Mesh)` holds. A blank body imported from a re-built 285-bone
    armature was rejected, so the component had no anim instance at all: the retargeter then copied a
    reference pose (frozen model) and weapons lost the sockets they hang from (274 bones expected).

The geometry is a 0.1 micrometre triangle bound 100% to `pelvis`: far below one pixel, but enough to
keep the mesh an ordinary rendered primitive with LODs and a material slot. Same technique as the
reference 2B mod.

Usage:
    blender.exe -b --python make_blank_body.py -- <Hun_Body_Simple.glb> <BlankBody.fbx>
"""
import sys
from pathlib import Path

import bpy
from mathutils import Matrix, Vector

argv = sys.argv
argv = argv[argv.index("--") + 1:] if "--" in argv else []
SOURCE_GLB = Path(argv[0])
OUT_FBX = Path(argv[1])

TRIANGLE_SIZE = 0.0001  # cm
WEIGHT_BONE = "pelvis"


def collect_hierarchy():
    """All empties, depth first, parents before children (the order UE assigns bone indices in)."""
    objects = list(bpy.context.scene.objects)
    roots = [ob for ob in objects if ob.parent is None and ob.type == "EMPTY"]
    ordered = []
    stack = list(reversed(roots))
    while stack:
        empty = stack.pop()
        ordered.append(empty)
        children = [c for c in objects if c.parent == empty and c.type == "EMPTY"]
        stack.extend(reversed(children))
    return ordered


def main() -> None:
    if not SOURCE_GLB.exists():
        raise SystemExit("missing %s" % SOURCE_GLB)

    bpy.ops.wm.read_factory_settings(use_empty=True)
    bpy.ops.import_scene.gltf(filepath=str(SOURCE_GLB))

    empties = collect_hierarchy()
    if not empties:
        raise SystemExit("no bone hierarchy in %s" % SOURCE_GLB)
    print("hierarchy nodes:", len(empties))
    print("first:", [e.name for e in empties[:6]])

    armature_data = bpy.data.armatures.new("HunSkinSkeleton")
    arm = bpy.data.objects.new("HunSkinSkeleton", armature_data)
    bpy.context.scene.collection.objects.link(arm)

    bpy.context.view_layer.objects.active = arm
    bpy.ops.object.mode_set(mode="EDIT")

    created = {}
    positions = {empty.name: empty.matrix_world.translation.copy() for empty in empties}
    first_child = {}
    for empty in empties:
        first_child.setdefault(empty.parent.name if empty.parent else None, empty)

    for empty in empties:
        bone = armature_data.edit_bones.new(empty.name)
        head = positions[empty.name]
        bone.head = head
        child = first_child.get(empty.name)
        tail = positions[child.name] if child is not None else head + Vector((0.0, 0.0, 10.0))
        bone.tail = tail if (tail - head).length > 1e-4 else head + Vector((0.0, 0.0, 10.0))
        created[empty.name] = bone

    for empty in empties:
        parent = empty.parent
        if parent is not None and parent.name in created:
            created[empty.name].parent = created[parent.name]

    bpy.ops.object.mode_set(mode="OBJECT")
    print("bones:", len(armature_data.bones))
    if WEIGHT_BONE not in armature_data.bones:
        raise SystemExit("bone %s missing" % WEIGHT_BONE)

    pivot = armature_data.bones[WEIGHT_BONE].head_local.copy()
    verts = [
        pivot,
        pivot + Vector((TRIANGLE_SIZE, 0.0, 0.0)),
        pivot + Vector((0.0, 0.0, TRIANGLE_SIZE)),
    ]
    mesh = bpy.data.meshes.new("BlankBody")
    mesh.from_pydata(verts, [], [(0, 1, 2)])
    mesh.update()

    obj = bpy.data.objects.new("BlankBody", mesh)
    bpy.context.scene.collection.objects.link(obj)
    obj.parent = arm
    obj.matrix_world = Matrix.Identity(4)

    group = obj.vertex_groups.new(name=WEIGHT_BONE)
    group.add([0, 1, 2], 1.0, "REPLACE")

    material = bpy.data.materials.new("BlankMat")
    material.use_nodes = True
    obj.data.materials.append(material)

    modifier = obj.modifiers.new("Rig", type="ARMATURE")
    modifier.object = arm

    bpy.context.scene.unit_settings.system = "METRIC"
    bpy.context.scene.unit_settings.scale_length = 0.01
    bpy.context.scene.unit_settings.length_unit = "CENTIMETERS"

    bpy.ops.object.select_all(action="SELECT")
    bpy.ops.export_scene.fbx(
        filepath=str(OUT_FBX),
        use_selection=True,
        object_types={"ARMATURE", "MESH"},
        add_leaf_bones=False,
        bake_anim=False,
        apply_scale_options="FBX_SCALE_NONE",
        axis_forward="-Z",
        axis_up="Y",
        path_mode="AUTO",
    )
    print("BLANKBODY saved", OUT_FBX, "bones", len(armature_data.bones))


main()
