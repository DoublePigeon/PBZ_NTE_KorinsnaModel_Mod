"""Smoke-test the UE4SS Lua mod without the game.

Loads `ue4ss/KorinsnaRetarget/scripts/main.lua` in an embedded Lua runtime with a stubbed engine and a
fake hero, runs the top level plus a few scans, and checks what the mod did. It cannot prove the mod
works in game, but it catches the failure class that otherwise costs a full play-test round: a name
that is nil at run time (forward reference, typo in a config key, a helper removed by a refactor).

Two worlds are exercised:
  * empty - nothing has spawned yet, which is the state right after boot;
  * hero  - a player pawn with the game's body component, the carrier and a weapon attached to it, so
            the per-scan work (hero tree, weapon/scabbard caches, pose watchdog, material guard) runs.

Both install flavours are checked as well: release must register no object listener (it has no
devtools.lua), dev must register both.

Needs `lupa` (the same package tools/luacheck.py uses):  pip install lupa
"""
import shutil
import sys
import tempfile
from pathlib import Path

import lupa

ROOT = Path(__file__).resolve().parent.parent
MAIN = ROOT / "ue4ss" / "KorinsnaRetarget" / "scripts" / "main.lua"
CONFIG = ROOT / "ue4ss" / "KorinsnaRetarget" / "config.lua"
DEV_CONFIG = ROOT / "ue4ss" / "dev" / "config.dev.lua"

# --------------------------------------------------------------------------------------------- stubs
#
# Every proxy answers unknown engine calls with nil, which is what the script expects from a component
# whose mesh, materials and bones are not interesting. Only the calls the code branches on are real.
STUBS = r"""
local scans = 0
local loop_callback = nil
function print(...) end
listeners = 0

local world = { objects = {}, by_class = {} }

local function class_object(class_name)
    return { GetFullName = function() return "/Script/Engine." .. class_name end }
end

local function proxy(name, class_name)
    -- Every field the script reads has to exist here, and `false` (not nil) is used for "unset":
    -- a nil field is simply absent from the table, and the fallback metatable below would then answer
    -- that read with a *function* instead.
    local object = {
        __name = name, __class = class_name or "Object", __children = {},
        __owner = false, __root = false, __parent = false, __socket = false, __mesh = false,
        __post = false, __leader = false, __materials = false, __pawn = false,
        __components = false, __bones = false,
    }
    object.GetFullName = function() return name end
    object.IsValid = function() return true end
    object.GetClass = function() return class_object(object.__class) end
    object.GetOwner = function() return object.__owner or nil end
    object.GetRootComponent = function() return object.__root or nil end
    object.GetAttachParent = function() return object.__parent or nil end
    object.GetAttachSocketName = function() return object.__socket or nil end
    object.GetSkeletalMeshAsset = function() return object.__mesh or nil end
    object.GetStaticMesh = function() return nil end
    object.GetNumBones = function() return object.__bones or 0 end
    object.GetChildrenComponents = function(_, recurse, out)
        for _, child in ipairs(object.__children) do out[#out + 1] = child end
        return true
    end
    object.K2_GetComponentsByClass = function() return object.__components or {} end
    object.GetPostProcessInstance = function() return object.__post or nil end
    object.GetMaterial = function(_, index)
        return object.__materials and object.__materials[index] or nil
    end
    object.GetNumMaterials = function() return 0 end
    object.K2_GetPawn = function() return object.__pawn or nil end
    object.GetControlledPawn = function() return object.__pawn or nil end
    object.GetPawn = function() return object.__pawn or nil end
    object.GetSocketLocation = function() return nil end
    object.K2_GetActorLocation = function() return { X = 0, Y = 0, Z = 0 } end
    object.GetActorLocation = function() return { X = 0, Y = 0, Z = 0 } end
    object.GetRelativeLocation = function() return { X = 0, Y = 0, Z = 0 } end
    setmetatable(object, { __index = function() return function() return nil end end })
    return object
end

function proxy_object(name, class_name) return proxy(name, class_name) end

local function fname(text)
    return { ToString = function() return text end }
end

local function register(class_name, object)
    world.by_class[class_name] = world.by_class[class_name] or {}
    table.insert(world.by_class[class_name], object)
    table.insert(world.objects, object)
    return object
end

function FindAllOf(class_name) return world.by_class[class_name] or {} end

function StaticFindObject(path)
    -- class lookups: the script resolves the SkeletalMeshComponent class by its /Script path
    local script_class = path:match("^/Script/Engine%.(%w+)$")
    if script_class then return class_object(script_class) end
    for _, object in ipairs(world.objects) do
        if object.__name == path then return object end
    end
    return nil
end

function IsValid(obj) return obj ~= nil end
function ExecuteInGameThread(fn) fn() end
function NotifyOnNewObject(path, callback) listeners = listeners + 1 end
function LoopInGameThreadWithDelay(delay, callback) loop_callback = callback end
function RegisterKeyBind(key, callback) end
Key = { F9 = 1, F11 = 2 }

function SmokeScan(count)
    for _ = 1, (count or 1) do
        if loop_callback == nil then return "no loop" end
        loop_callback()
        scans = scans + 1
    end
    return scans
end

-- A player pawn shaped like the one the mod expects: the game's body component (pose source), the
-- carrier part that ships the Korinsna mesh, one outfit part, and a weapon actor hanging off the body.
function SmokeHero()
    local map = "/Game/Maps/B03/X.PBZ_Fujizhilin_WP:PersistentLevel."

    local skin = proxy(map .. "Hun_Head_New_1", "SkeletalMesh")
    skin.GetFullName = function() return "/Game/Hun/SkinParts/Hun_Head_New.Hun_Head_New" end
    local hero_mesh = proxy(map .. "Hun_Body_Simple_1", "SkeletalMesh")
    hero_mesh.GetFullName = function() return "/Game/Hun/Hun_Body_Simple.Hun_Body_Simple" end
    local weapon_mesh = proxy(map .. "Hun_ChiZheZuiJian_1", "SkeletalMesh")
    weapon_mesh.GetFullName =
        function() return "/Game/Weapons/Hun_ChiZheZuiJian.Hun_ChiZheZuiJian" end
    local cloth_mesh = proxy(map .. "CA_Hun_Robe_1", "SkeletalMesh")
    cloth_mesh.GetFullName = function() return "/Game/Hun/CA_Hun_Robe.CA_Hun_Robe" end
    local upcloth_mesh = proxy(map .. "Hun_UpCloth_1", "SkeletalMesh")
    upcloth_mesh.GetFullName = function() return "/Game/Hun/SkinParts/Hun_UpCloth.Hun_UpCloth" end

    local actor = proxy(map .. "BP_Hun_C_1", "BP_Hun_C")
    local root = proxy(map .. "BP_Hun_C_1.DefaultSceneRoot", "SceneComponent")
    root.__owner, actor.__root = actor, root

    local source = proxy(map .. "BP_Hun_C_1.CharacterMesh0", "SkeletalMeshComponent")
    source.__owner, source.__mesh, source.__bones, source.__parent = actor, hero_mesh, 1171, root
    local carrier = proxy(map .. "BP_Hun_C_1.meshhead", "SkeletalMeshComponent")
    carrier.__owner, carrier.__mesh, carrier.__bones, carrier.__parent = actor, skin, 369, root
    local cloth = proxy(map .. "BP_Hun_C_1.meshUpCloth", "SkeletalMeshComponent")
    cloth.__owner, cloth.__mesh, cloth.__bones, cloth.__parent = actor, upcloth_mesh, 369, root

    local weapon_root = proxy(map .. "BP_Weapon_Hun_ChiZheZuiJian_C_1", "SceneComponent")
    weapon_root.__parent, weapon_root.__socket = source, fname("WEAPON_R")
    local weapon = proxy(map .. "BP_Weapon_Hun_ChiZheZuiJian_C_1.Weapon Mesh",
        "SkeletalMeshComponent")
    weapon.__owner, weapon.__mesh, weapon.__parent = weapon_root, weapon_mesh, weapon_root

    local robe = proxy(map .. "BP_Hun_C_1.ClothRobe", "ChaosClothComponent")
    robe.__owner, robe.__parent = actor, root

    local garment = proxy(map .. "BP_Hun_C_1.ClothRobe_SK", "ChaosClothComponent")
    garment.GetClothAsset = function() return cloth_mesh end

    source.__components = { source }
    actor.__components = { source, carrier, cloth }
    root.__children = { source, carrier, cloth, robe }
    source.__children = { weapon_root }

    local controller = proxy(map .. "PlayerController_1", "PlayerController")
    controller.__pawn = actor

    register("PlayerController", controller)
    register("SkeletalMeshComponent", source)
    register("SkeletalMeshComponent", carrier)
    register("SkeletalMeshComponent", cloth)
    register("SkeletalMeshComponent", weapon)
    register("ChaosClothComponent", robe)
    return actor
end
"""


def run(profile, world, scans=10):
    """Install one profile into a temp folder, run it, return (log text, listeners, scans).

    `world` is "empty" (nothing spawned), "hero" (pawn present from the start) or "late" (the pawn
    appears only after a few scans - the real sequence at level load, and the case that broke when the
    hero was discovered by polling: the counter never advanced, so the one attempt made before the
    level spawned him blocked every later one).
    """
    work = Path(tempfile.mkdtemp(prefix="korinsna-smoke-"))
    mod = work / "KorinsnaRetarget"
    (mod / "scripts").mkdir(parents=True)
    shutil.copy2(MAIN, mod / "scripts" / "main.lua")
    shutil.copy2(CONFIG, mod / "config.lua")
    if profile == "dev":
        shutil.copy2(DEV_CONFIG, mod / "config.dev.lua")

    runtime = lupa.LuaRuntime(unpack_returned_tuples=True)
    runtime.execute(STUBS)
    if world == "hero":
        runtime.eval("SmokeHero()")
    loader = runtime.eval("loadfile")(str(mod / "scripts" / "main.lua").replace("\\", "/"))
    if loader is None:
        raise SystemExit("main.lua did not load")
    loader()

    ran = 0
    if world == "late":
        ran += runtime.eval("SmokeScan(%d)" % max(1, scans // 2))
        runtime.eval("SmokeHero()")
    ran += runtime.eval("SmokeScan(%d)" % scans)
    listeners = runtime.eval("listeners or 0")
    log_path = mod / "KorinsnaRetarget.log"
    text = log_path.read_text(encoding="utf-8", errors="replace") if log_path.exists() else ""
    shutil.rmtree(work, ignore_errors=True)
    return text, listeners, ran


def check(profile, world):
    label = "%s/%s" % (profile, world)
    text, listeners, scans = run(profile, world)
    problems = []
    hero = world in ("hero", "late")

    # The listeners are what make the copy/garment caches event driven, so BOTH profiles must register
    # them. Exactly two: the rare cloth and groom classes. The engine mesh classes are deliberately not
    # registered - they fire for the whole level and their dispatch cost is what stalled the game.
    if listeners != 2:
        problems.append("%s: expected 2 object listeners, got %s" % (label, listeners))
    if "scan error" in text:
        problems.append("%s: a scan raised: %s" % (
            label, text.split("scan error:", 1)[1].splitlines()[0]))
    if "FAILED " in text:
        problems.append("%s: an engine call failed: %s" % (
            label, text.split("FAILED ", 1)[1].splitlines()[0]))

    if profile == "dev":
        # The dev profile logs everything, so the run itself can be inspected.
        if "boot" not in text:
            problems.append("%s: the script never started" % label)
        if "periodic loop registered" not in text:
            problems.append("%s: the scan loop was not registered" % label)
        if hero:
            for needed in ("hero body:", "carrier:"):
                if needed not in text:
                    problems.append("%s: never found %r" % (label, needed))
    elif text.strip():
        # release is silent by design: a healthy session writes no log file at all
        problems.append("%s: release must stay silent, wrote: %r" % (label, text[:200]))

    print("%-14s scans=%-2s listeners=%s log_lines=%d" % (
        label, scans, listeners, len(text.splitlines())))
    for problem in problems:
        print("FAIL " + problem)
    if not problems:
        print("ok   %s" % label)
    return 1 if problems else 0


def main():
    failed = 0
    for profile in ("release", "dev"):
        for world in ("empty", "hero", "late"):
            failed += check(profile, world)
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
