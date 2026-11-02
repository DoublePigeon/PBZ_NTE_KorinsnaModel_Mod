"""Offline proof that the retarget chain is valid, without launching the game.

Everything here mirrors what the game does at runtime, so a failure here is the same failure the
"Retarget Pose From Mesh" node would hit - it just tells us why, instead of silently drawing an
unanimated A-pose.
"""
import os

import unreal

ROOT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod"
OUT = os.path.join(ROOT, "extract", "ue-retarget-check.txt")
EAL = unreal.EditorAssetLibrary

ANIM_BP = "/Game/Korinsna/ABP_Korinsna_Retarget"
RETARGETER = "/Game/Korinsna/RTG_HunToKorinsna"
CARRIER = "/HuaShira/Characters/Hero/Hero_Hun/SkinParts/Hun_Head_New"
SOURCE_MESH = "/HuaShira/Characters/Hero/Hero_Hun/SkinParts/Hun_Body_Simple"
STANDALONE = "/Game/Korinsna/SK_Korinsna"

lines = []


def log(msg):
    lines.append(str(msg))


def main():
    lib = getattr(unreal, "KorinsnaEditorLibrary", None)
    if lib is None:
        log("KorinsnaEditorLibrary is not exposed - was ProjectPBZEditor rebuilt?")
        return

    log("== anim blueprint")
    log(lib.inspect_retarget_anim_blueprint(ANIM_BP))

    log("== meshes")
    carrier = EAL.load_asset(CARRIER)
    standalone = EAL.load_asset(STANDALONE)
    for label, mesh in (("carrier", carrier), ("standalone", standalone)):
        if mesh is None:
            log("%s: MISSING" % label)
            continue
        skeleton = mesh.get_editor_property("skeleton")
        post = mesh.get_editor_property("post_process_anim_blueprint")
        log("%s %s skeleton=%s post_bp=%s slots=%d" % (
            label, mesh.get_path_name(),
            skeleton.get_path_name() if skeleton else "None",
            post.get_path_name() if post else "None",
            len(mesh.get_editor_property("materials"))))

    log("== retargeter processor, source = the game mesh the hero uses")
    log(lib.validate_retargeter(SOURCE_MESH, CARRIER, RETARGETER))

    log("== retargeter processor, source = our own copy of the game mesh")
    log(lib.validate_retargeter("/Game/Korinsna/Source/HunSkin", CARRIER, RETARGETER))


try:
    main()
finally:
    with open(OUT, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))
    print("\n".join(lines))
