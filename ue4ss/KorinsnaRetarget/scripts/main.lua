-- KorinsnaRetarget: shows Korinsna on the protagonist without touching either skeleton.
--
-- How the pieces fit together, and why it is built this way:
--
--   1. The pak ships Korinsna's mesh (own Bip001 skeleton, unchanged) as the hero's own
--      SkinParts/Hun_Head_New package. New package paths cannot be loaded from Lua in a packaged
--      build (LoadAsset goes through the asset registry, which never learns about mod containers,
--      and LoadObject/StaticLoadObject are not exposed), but a package path the game already asks
--      for always resolves - so the game loads our mesh, and everything it references, for us.
--   2. The mesh carries ABP_Korinsna_Retarget as its PostProcessAnimBlueprint. That is a hard class
--      reference, so loading the mesh also loads the AnimBlueprint, the IK Retargeter and both IK
--      Rigs - which is how the script gets a live class to point the component at.
--   3. The game keeps animating CharacterMesh0 (the hero's real body component, untouched, with the
--      real Hun skeleton). The script hides it but keeps it posing, and the retarget anim graph - a
--      single "Retarget Pose From Mesh" node reading its parent component - copies that pose onto
--      Korinsna's rig.
--
-- Nothing is rebound: no bone is renamed and no weight is copied between skeletons.

local DEFAULTS = {
    -- the hero's body component: real game mesh + real game animation, hidden but still ticking
    source_mesh_names = { "Hun_Body_Simple" },
    -- the part asset that carries our mesh (see ue/scripts/build_carrier_mesh.py)
    carrier_mesh_name = "Hun_Head_New",
    anim_class_path = "/Game/Korinsna/ABP_Korinsna_Retarget.ABP_Korinsna_Retarget_C",
    -- The game's own part component already runs the retarget blueprint: the mesh's
    -- PostProcessAnimBlueprint is instantiated by the engine for it. So there is nothing to create;
    -- only the leader pose has to be cleared, because a follower component never evaluates its own
    -- animation. Set this to true only to experiment with a component of our own (note that
    -- RegisterComponent is not BlueprintCallable, so a component built with StaticConstructObject
    -- cannot be registered from Lua and never animates).
    create_own_component = false,

    hide_prefixes = { "Hun_" },
    -- The whole outfit is handled at ASSET level (blank meshes + empty Chaos Cloth assets), the same
    -- way the reference 2B mod does it. Runtime hiding is kept only as a debugging tool: it fights
    -- the game's wardrobe system and, if it ever clears the body's visibility, it also stops the pose
    -- from refreshing unless the tick option is forced.
    hide_source_visibility = true,
    hide_body_render_pass = false,
    hide_all_hun_parts = false,
    hide_only_source = false,
    keep_visible = { "Weapon", "Blade", "Knife", "Scabbard", "Chakram", "Spear", "Sword" },
    hide_parts = false,
    -- hidden body + this = the pose keeps updating (see force_anim_refresh)
    force_anim_refresh = true,
    -- scabbards ride Hun's own sockets and fly around once the visible body is Korinsna's
    hide_scabbards = true,
    -- off: the retargeted pose casts a shadow that does not match the visible mesh and shows up as
    -- black patches near the character
    carrier_cast_shadow = false,
    -- on: a held weapon actor is re-parented onto the hand bone it is drawn from (see
    -- anchor_held_weapons). The game attaches it once, so nothing fights the change.
    attach_weapons = true,
    -- How far from the hand bone the hilt should sit, in cm. The game uses 9.5 (Hun's hand), which on
    -- Korinsna's shorter hand bone puts the hilt on the outside of the fist; the fist's own grip is
    -- ~6 cm out (measured: proximal finger joints are 6.0-6.5 cm from the hand bone head).
    -- 0 or nil leaves the game's distance alone.
    grip_distance = { r = 6.0, l = 6.0 },
    -- A weapon that is put away is carried over to Korinsna's own body: the game hangs it on a socket
    -- on HUN's back (wide shoulders, thick robe), where it floats behind her or cuts through the
    -- dress. It is anchored to the middle of her spine so it follows the torso - on the pelvis it
    -- visibly rode her backside, because the hips sway far more than the chest. `sheathed_source_bone`
    -- is the Hun bone it corresponds to in the retarget chain (pelvis->spine_05 maps onto
    -- Bip001-Pelvis->Bip001-Spine1, so Korinsna's middle spine is Hun's spine_03).
    sheathed_anchor = "Bip001-Spine",
    sheathed_source_bone = "spine_03",
    sheathed_push_cm = 2.0,
    -- never derive a weapon anchor from a pose whose hands are more than this far apart: that is a
    -- reference pose, not a real one, and anchoring from it bakes a wrong offset into the weapon
    anchor_max_gap_cm = 100.0,
    -- diagnostic: log each weapon's full attach chain whenever it changes (draw / sheathe / swap)
    report_weapon_chain = false,
    -- The hero's own waist knife and its scabbard: carried onto Korinsna's pelvis (so they stop
    -- riding Hun's sockets) and pushed out along the back of the dress by this many cm so they sit on
    -- the outside of the skirt instead of through it. Empty list disables the feature.
    back_items = { "Hun_Knife", "Hun_Knife_Scabbard" },
    back_item_push_cm = 2.0,
    -- keep the blanked part meshes out of the shadow and main pass: degenerate triangles make the
    -- shadow pass flicker. Only the hero's own components are touched.
    quiet_blank_parts = true,
    -- Meshes that only exist on the original hero body: the cutscene / preview copies of the hero
    -- render them again (the player's own copy is hidden separately), so they are hidden here too.
    -- The young hero uses different meshes and must keep his outfit.
    hide_copy_bodies = true,
    hide_copy_body_meshes = { "Hun_Body_Simple" },
    -- Chaos Cloth garments are components of their own (the robe/cape/hair, plus the wardrobe's
    -- damaged variants) and are hidden separately from the skeletal parts.
    hide_hero_cloth = true,
    -- Everything else a cutscene / preview copy of the hero owns (accessories, static-mesh cards,
    -- grooms) is hidden too: those copies only need the Korinsna mesh and weapons.
    hide_copy_outfit = true,
    -- The sweep that finds those components walks the whole level, so it runs rarely: when a new hero
    -- copy component appeared (event driven) or every this many scans (a safety net). Re-applying the
    -- hiding from the cached list still happens every scan, which is what keeps it off screen.
    copy_rescan_scans = 60,
    -- Even when a rescan is "due", never run it more often than this: a cutscene spawns components
    -- continuously, which would otherwise mean a full level sweep every scan.
    copy_rescan_min_scans = 4,
    -- re-arm the retarget when the game re-applies the part components' leader pose (the model falling
    -- back to its reference pose after an interactive animation). See watch_pose().
    pose_watchdog = true,
    -- Each scan is classified as "stalled" when the game's body moved more than pose_step_move_cm
    -- while Korinsna moved less than pose_step_stuck_cm; the verdict is taken over a sliding window
    -- (pose_slip_window), because one bad read-out can otherwise look like motion and hide a stall.
    pose_step_move_cm = 0.5,
    pose_step_stuck_cm = 0.3,
    pose_slip_window = 12,
    -- 4 stalled scans (~2 s) is already a stall: the marks only become true when the game's body moves
    -- while ours does not, so they do not fire on scattered bad read-outs
    pose_stuck_marks = 4,
    -- minimum scans between two heals (0.5 s each), so an unrelated frozen pose cannot turn this
    -- into a re-init loop
    pose_heal_cooldown = 6,
    -- diagnostic: print the watchdog counters every 5 scans
    report_pose_window = false,
    -- diagnostic: log which material instance each slot renders with, once per hero
    report_materials = false,
    -- Slots the game overwrites at runtime, mapped to the instance they must have. The hero's damage
    -- system replaces the head part's first slot with Hun_Status/MI_ZeroHun_Head_Injured*, and our
    -- mesh is that part, so the dress slot has to be put back (it otherwise renders as pale skin).
    material_guard = {},
    -- diagnostic only: logs how each weapon is attached (parent + socket) at two moments
    report_weapon_attachment = false,
    -- diagnostic only: measures the gap between the hero's hands and ours, and prints each weapon's
    -- full attach chain + owner, to decide how the weapons can be made to follow Korinsna's hands
    report_weapon_geometry = false,
    -- push a white map into the host materials' OpacityMask parameter: the placeholder mask makes the
    -- mesh look speckled and semi-transparent
    -- off: CreateDynamicMaterialInstance is not callable from Lua in this build, so the cutout fix is
    -- done at asset level instead (ue/scripts/build_mod_assets.py authors a per-slot instance)
    force_opaque = false,

    -- one-shot census of every skeletal mesh component in the level (mesh name, visibility, owner,
    -- position). This is how a component that still draws part of the original outfit is identified.
    dump_census = false,

    toggle_key = "F9",
    diagnostics_key = "F11",
    rescan_interval = 0.5,

    -- diagnostic switch: only report what is loaded, never change anything
    probe_only = false,
}

local function merge(base, extra)
    for k, v in pairs(extra) do base[k] = v end
    return base
end

local config = merge(DEFAULTS, {})
local config_source = "built-in defaults"

local MOD = "KorinsnaRetarget"
local script_path = debug.getinfo(1, "S").source:gsub("^@", "")
local mod_dir = script_path:match("^(.*)[/\\][Ss]cripts[/\\]main%.lua$")
    or script_path:match("^(.*)[/\\]") or "."
local LOG_PATH = mod_dir .. "/" .. MOD .. ".log"

-- Read config.lua by path instead of require(): the module search path does not reliably include
-- the mod root, and a silently ignored config file is very hard to notice.
local function apply_config_file(mod_root)
    for _, path in ipairs({ mod_root .. "/config.lua", mod_root .. "/Scripts/config.lua" }) do
        local handle = io.open(path, "r")
        if handle then
            local source = handle:read("*a")
            handle:close()
            local chunk = load(source, "@" .. path)
            if chunk then
                local ok, table_value = pcall(chunk)
                if ok and type(table_value) == "table" then
                    merge(config, table_value)
                    return path
                end
            end
        end
    end
    return nil
end

local applied = apply_config_file(mod_dir)
if applied then config_source = applied end

local log_lines = {}
local state = {
    enabled = true,
    show_ours = true,
    probed = false,
    tick = 0,
    aligned = false,
    source = nil,      -- the hero's body component (pose source)
    carrier = nil,     -- the game's part component that carries our mesh asset
    body = nil,        -- the component we create and drive
    actor = nil,       -- the hero actor that owns them
    actor_name = nil,  -- its object name, kept as a string so staleness never needs the object
    hidden = {},
    hidden_names = {}, -- name-keyed twin of `hidden`, for logging once per component
    fixed = {},
    refreshed = {},
    weapon_attached = {},
}

local function log(msg)
    local line = string.format("[%s] %s", tostring(os.date("%H:%M:%S")), tostring(msg))
    table.insert(log_lines, line)
    if #log_lines > 800 then table.remove(log_lines, 1) end
    print("[" .. MOD .. "] " .. tostring(msg))
end

-- Appended one line at a time so an engine crash can never lose the line just produced.
local function trace(msg)
    log(msg)
    local f = io.open(LOG_PATH, "a")
    if not f then return end
    f:write(log_lines[#log_lines] .. "\n")
    f:close()
end

-- Strict on purpose: an object whose validity cannot be read is treated as gone. The old fallback
-- ("unknown means valid") made the script dereference the hero's destroyed components after the game
-- re-created him on a map change, which crashed the game (see docs/TECHNICAL-GUIDE.md 6.12).
local function valid(obj)
    if not obj then return false end
    local ok, v = pcall(function() return obj:IsValid() end)
    if ok and type(v) == "boolean" then return v end
    return false
end

-- UE4SS returns a truthy wrapper around a null pointer for objects it could not find, so an object
-- only counts as usable if a call on it succeeds.
local function usable(obj)
    if obj == nil then return nil end
    local ok, name = pcall(function() return obj:GetFullName() end)
    if not ok or name == nil or name == "" then return nil end
    return obj
end

local function full_name(obj)
    local name = nil
    pcall(function() name = obj:GetFullName() end)
    return name
end

local function short_name(name)
    if not name then return nil end
    return name:match("([^%./]+)$")
end

-- Forward declarations: the helpers below are defined before these, but they call them.local vec_of
local try
local fmt_vec

-- Every engine call goes through pcall: one failing call must never take the whole scan down. But a
-- silently swallowed error is what makes debugging this mod so hard, so the label and the error are
-- logged instead of thrown away.
try = function(label, fn)
    local ok, result = pcall(fn)
    if not ok then
        trace("FAILED " .. label .. ": " .. tostring(result))
        return nil
    end
    return result
end

-- A blueprint's class default object is named '<Package>.<Class>_C:Component', not 'Default__...',
-- and touching one of its components crashes the game. Live components sit in a level, so their
-- name carries 'PersistentLevel'.
local function is_cdo(obj)
    local name = full_name(obj)
    if name == nil then return true end
    if name:find("Default__", 1, true) then return true end
    if not name:find("PersistentLevel", 1, true) and name:find("%.[%w_]+_C:", 1) then
        return true
    end
    return false
end

local function mesh_of(component)
    local mesh = nil
    pcall(function() mesh = component:GetSkeletalMeshAsset() end)
    return usable(mesh)
end

local function mesh_name(component)
    local mesh = mesh_of(component)
    return mesh and short_name(full_name(mesh)) or nil
end

-- Some of the hero's accessories are static meshes, not skeletal ones.
local function part_mesh_name(component)
    local name = mesh_name(component)
    if name then return name end
    -- Only a static mesh component has GetStaticMesh: asking anything else throws, and asking it for
    -- every component on every scan filled the log with failures (Chaos Cloth garments are skeletal
    -- mesh components too, so "not skeletal" was not a good enough guard).
    local class = usable(try("GetClass", function() return component:GetClass() end))
    local class_name = class and short_name(full_name(class)) or nil
    if class_name == nil or not class_name:find("Static", 1, true) then return nil end
    local mesh = try("GetStaticMesh", function() return component:GetStaticMesh() end)
    return usable(mesh) and short_name(full_name(mesh)) or nil
end

local function bone_count(component)
    local count = nil
    pcall(function() count = component:GetNumBones() end)
    return count
end

local function anim_instance_name(component)
    local instance = nil
    pcall(function() instance = component:GetAnimInstance() end)
    if not usable(instance) then return "nil" end
    local class = nil
    pcall(function() class = instance:GetClass() end)
    return usable(class) and short_name(full_name(class)) or "?"
end

-- Every engine call goes through pcall: one failing call must never take the whole scan down. But a
-- silently swallowed error is what makes debugging this mod so hard, so the label and the error are
-- logged instead of thrown away.
local vec_of -- defined further down, but the helpers below need it

local function class_name_of(obj)
    if not usable(obj) then return "nil" end
    local class = try("GetClass", function() return obj:GetClass() end)
    return usable(class) and short_name(full_name(class)) or "?"
end

local function object_name(obj)
    if not usable(obj) then return "nil" end
    return short_name(full_name(obj)) or "?"
end

local function post_instance_name(component)
    local instance = try("GetPostProcessInstance", function() return component:GetPostProcessInstance() end)
    if not usable(instance) then return "nil" end
    return object_name(instance)
end

local function anim_class_name(component)
    local class = try("GetAnimClass", function() return component:GetAnimClass() end)
    if not usable(class) then return "nil" end
    return object_name(class)
end

local function component_location(component)
    local value = try("K2_GetComponentLocation", function() return component:K2_GetComponentLocation() end)
    return vec_of(value)
end

local function relative_location(component)
    local value = try("GetRelativeLocation", function() return component:GetRelativeLocation() end)
    return vec_of(value)
end

local function is_our_body(obj)
    local name = full_name(obj)
    return name ~= nil and name:find(config.component_name, 1, true) ~= nil
end

local function contains_any(value, list)
    if not value then return false end
    for _, candidate in ipairs(list) do
        if value:find(candidate, 1, true) then return true end
    end
    return false
end

local function matches_any(value, list)
    if not value then return false end
    for _, candidate in ipairs(list) do
        if value == candidate then return true end
    end
    return false
end

local function actor_of(component)
    local actor = nil
    pcall(function() actor = component:GetOwner() end)
    if actor ~= nil then return actor end
    pcall(function() actor = component:GetAttachmentRootActor() end)
    return actor
end

-- True when the component is still owned by the hero actor we set up for. Owner keys are compared as
-- strings, so this never touches an object that may already be destroyed.
local function belongs_to_actor(component, actor_name)
    if component == nil or actor_name == nil then return false end
    local owner = try("GetOwner", function() return component:GetOwner() end)
    local owner_key = usable(owner) and full_name(owner) or nil
    return owner_key ~= nil and owner_key == actor_name
end

-- True when the component is part of the hero's own scene graph (a part, or something a weapon actor
-- hangs onto the hero's body). Used instead of "any component whose mesh name matches": the level is
-- full of other characters carrying meshes with the same naming convention.
local function attached_to_hero(component)
    local node = component
    for _ = 1, 8 do
        local parent = try("GetAttachParent", function() return node:GetAttachParent() end)
        if not usable(parent) then return false end
        local key = full_name(parent)
        if key ~= nil and (key == state.source_name or key == state.carrier_name) then
            return true
        end
        if belongs_to_actor(parent, state.actor_name) then return true end
        node = parent
    end
    return false
end

-- Everything below hangs off one specific hero actor. The game destroys that actor and builds a new
-- one on every map change / teleport, so all of it has to be dropped when the actor changes - a stale
-- component reference is exactly what crashed during teleport. `actor_name` is a plain string, so the
-- decision never requires reading from the dead object.
local RESET_KEYS = {
    "actor", "actor_name",
    "source", "carrier", "body", "source_name", "carrier_name",
    "aligned", "carrier_ready_tick", "align_attempts",
    "hidden_list", "quiet_parts", "quiet_parts_actor", "quiet_parts_tick", "quiet_reported",
    "hide_collected", "hide_targets", "hide_index", "spawned_parts",
    "leader_cleared", "opaque_done", "hidden_shadow_cleared", "materials_reported",
    "pose_prev", "pose_stuck", "pose_heals", "pose_samples", "pose_heal_tick",
    "pose_window", "pose_fail_streak", "pose_last_ours", "pose_identical",
    "attach_checks", "geo_checks", "census_steps", "dumped_everything",
    "reported_sockets", "weapon_attached", "weapon_prev", "mids", "hidden_shadow_cleared",
    "weapon_sockets", "weapon_reanchor", "weapon_reanchor_ready",
    "copy_hidden", "copy_leader", "copy_reported", "cloth_seen", "cloth_reported",
    "copy_seen", "copy_outfit_reported", "copy_list", "copy_carriers", "cloth_list",
    "copy_dirty", "copy_scan_tick",
}

local function reset_actor_state(reason)
    for _, key in ipairs(RESET_KEYS) do
        state[key] = nil
    end
    state.hidden = {}
    state.fixed = {}
    state.refreshed = {}
    state.leader_cleared = {}
    state.hidden_names = {}
    trace("state: reset (" .. tostring(reason) .. ")")
end

-- Object path -> live object, but only for objects that already exist in memory. This works for
-- package paths inside a mod container as long as something else already loaded them.
local function find_loaded(path)
    local found = nil
    pcall(function() found = StaticFindObject(path) end)
    found = usable(found)
    if found then trace("find_loaded: hit " .. path) end
    return found
end

-- The anim blueprint class: already in memory because the carrier mesh references it, so a plain
-- lookup by name is enough (LoadAsset cannot see new packages, see the header comment).
local function anim_class()
    local direct = find_loaded(config.anim_class_path)
    if direct then return direct end
    local mesh = state.carrier and mesh_of(state.carrier)
    if mesh then
        local ok, value = pcall(function() return mesh.PostProcessAnimBlueprint end)
        if ok then
            local resolved = usable(value)
            if resolved then
                trace("anim class taken from the carrier's post-process blueprint")
                return resolved
            end
        end
    end
    return nil
end

-- A component only advances its pose while it is relevant for rendering, so keep it always
-- relevant. Native UFUNCTIONs only: writing VisibilityBasedAnimTickOption by reflection is not safe
-- (UE4SS stores a 4-byte int in a 1-byte enum and corrupts the neighbours, which crashes later).
local function keep_ticking(component, label)
    local failures = {}
    local function call(name, fn)
        local good = pcall(fn)
        if not good then failures[#failures + 1] = name end
    end
    call("SetCullDistance", function() component:SetCullDistance(0.0) end)
    -- A huge bounds scale was used while the component was still being placed; it also inflates the
    -- shadow bounds, which showed up as flickering black patches at all distances. The component is
    -- correctly placed now, so a sane scale is enough (and keeps it from being culled).
    call("SetBoundsScale", function() component:SetBoundsScale(2.0) end)
    call("SetComponentTickEnabled", function() component:SetComponentTickEnabled(true) end)
    -- The retargeted pose produces a shadow that does not match the visible mesh (the depth pass uses
    -- a different bound/space than the main pass here), which shows up as black patches near the
    -- character. Nothing is lost by turning it off on the carrier.
    if config.carrier_cast_shadow == false then
        call("SetCastShadow", function() component:SetCastShadow(false) end)
    end
    trace(label .. ": always-relevant" ..
        (#failures > 0 and (", failed: " .. table.concat(failures, ",")) or ""))
end

local function hide_part(component, label)
    if state.hidden[component] then return end
    pcall(function() component:SetRenderInMainPass(false) end)
    pcall(function() component:SetCastShadow(false) end)
    state.hidden[component] = label
    trace("hidden " .. label)
end

local function show_part(component)
    if not valid(component) then return end
    pcall(function() component:SetRenderInMainPass(true) end)
    pcall(function() component:SetCastShadow(true) end)
    pcall(function() component:SetHiddenInGame(false, true) end)
    pcall(function() component:SetVisibility(true, true) end)
end

local function component_list(actor)
    local class = try("SkeletalMeshComponent class",
        function() return StaticFindObject("/Script/Engine.SkeletalMeshComponent") end)
    if class == nil then return nil end
    return try("K2_GetComponentsByClass", function() return actor:K2_GetComponentsByClass(class) end)
end

-- The TArray UE4SS hands back is not indexable the obvious way: list[i] yields a wrapper that is
-- truthy but null. Try the plausible accessors until one returns a real object.
local function nth(list, index)
    local value = try("index", function() return list[index] end)
    if usable(value) then return value end
    value = try("Get", function() return list:Get(index) end)
    if usable(value) then return value end
    value = try("Get", function() return list:Get(index - 1) end)
    if usable(value) then return value end
    return nil
end

-- True when this component draws Korinsna: the carrier must never be hidden.
local function is_carrier_mesh(name)
    return name ~= nil and name == config.carrier_mesh_name
end

-- Collects every scene component below a root by walking children, which returns its result through a
-- TArray out-parameter. That array is a plain Lua table here, so it can actually be read - unlike the
-- TArray that K2_GetComponentsByClass returns, whose elements come back as null wrappers.
local function children_of(component, out)
    if not valid(component) then return out end
    local collected = {}
    local ok = try("GetChildrenComponents",
        function() component:GetChildrenComponents(true, collected) end)
    if ok ~= nil or #collected > 0 then
        for index = 1, #collected do
            local child = collected[index]
            if usable(child) then
                out[#out + 1] = child
            end
        end
    end
    return out
end

local function enumerate_parts(actor)
    local found = {}
    local seen = {}

    -- FindAllOf takes a SHORT class name; passing the /Script/Engine path silently returns nothing,
    -- which is what made an earlier version of this script give up on enumeration entirely.
    for _, class_name in ipairs({ "SkeletalMeshComponent", "StaticMeshComponent" }) do
        local objects = try("FindAllOf " .. class_name, function() return FindAllOf(class_name) end)
        local count = 0
        if type(objects) == "table" then
            for key, obj in pairs(objects) do
                count = count + 1
                if usable(obj) and actor_of(obj) == actor then
                    local full = full_name(obj)
                    if full and not seen[full] then
                        seen[full] = true
                        found[#found + 1] = obj
                    end
                end
            end
        end
        trace("hide: FindAllOf(" .. class_name .. ") -> " .. count)
    end
    for _, component in ipairs(children_of(try("GetRootComponent",
        function() return actor:GetRootComponent() end), {})) do
        local full = full_name(component)
        if full and not seen[full] then
            seen[full] = true
            found[#found + 1] = component
        end
    end
    trace("hide: enumerator found " .. #found .. " components of our actor")
    return found
end

-- Hide everything of the hero's original outfit except weapons.
--
-- The components are collected once and then hidden one per scan, each one logged before the call:
-- hiding the whole outfit at once crashed the game during level load, and this way a component that
-- cannot be touched names itself in the log instead of taking the process down silently.
local function collect_hide_targets(actor, keep)
    local targets = {}
    if config.hide_only_source then
        -- diagnostic mode: only the old body, so a crash names the component responsible
        if valid(state.source) then targets[1] = state.source end
        trace("hide: only the source body is queued")
        return targets
    end

    local list = component_list(actor)
    if list == nil then
        trace("hide: component list unavailable")
    else
        local count = try("component count", function() return #list end) or 0
        for index = 1, count do
            local component = nth(list, index)
            if component ~= nil then targets[#targets + 1] = component end
        end
        trace("hide: " .. count .. " components from the actor list, " ..
            #targets .. " readable")
    end

    -- walk the scene graph as well: it returns its result through an out-parameter, which is a real
    -- Lua table, so this finds the parts the actor list could not hand over
    local seen = {}
    for _, component in ipairs(targets) do
        local key = full_name(component)
        if key then seen[key] = true end
    end
    for _, component in ipairs(enumerate_parts(actor)) do
        local key = full_name(component)
        if key and not seen[key] then
            seen[key] = true
            targets[#targets + 1] = component
        end
    end
    trace("hide: " .. #targets .. " candidates total")
    return targets
end

-- The hero's own components, listed as they are right now. Called several times, because the game's
-- wardrobe system assigns the outfit meshes to those components over the first seconds - a single
-- early census shows "mesh=nil" and hides the culprit.
local function census_hero(tag)
    local objects = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    local count = 0
    if type(objects) == "table" then
        for _, obj in pairs(objects) do
            if usable(obj) and actor_of(obj) == state.actor then
                count = count + 1
                trace(string.format("census[%s]: %-24s mesh=%-24s vis=%s",
                    tag, tostring(short_name(full_name(obj))), tostring(part_mesh_name(obj)),
                    tostring(try("IsVisible", function() return obj:IsVisible() end))))
            end
        end
    end
    trace(string.format("census[%s]: %d components on the hero", tag, count))
end

-- One-shot census of everything that draws near the hero: every skeletal mesh component in the level
-- (there are only a few dozen) and every static mesh component within a radius. Filtering by asset
-- name was not enough - the part that still shows uses an asset whose name mentions nothing about the
-- hero, so position is the reliable criterion.
local function dump_everything()
    local hero_at = component_location(state.source)
    trace("census: source visible=" ..
        tostring(try("IsVisible", function() return state.source:IsVisible() end)) ..
        " at=" .. fmt_vec(hero_at))

    local function distance_to(obj)
        local at = component_location(obj)
        if not at or not hero_at then return nil end
        local dx, dy, dz = at.X - hero_at.X, at.Y - hero_at.Y, at.Z - hero_at.Z
        return math.sqrt(dx * dx + dy * dy + dz * dz)
    end

    for _, class_name in ipairs({ "SkeletalMeshComponent", "StaticMeshComponent" }) do
        local objects = try("FindAllOf " .. class_name, function() return FindAllOf(class_name) end)
        local scanned, reported = 0, 0
        if type(objects) == "table" then
            for _, obj in pairs(objects) do
                if usable(obj) then
                    scanned = scanned + 1
                    local mesh = part_mesh_name(obj)
                    local distance = distance_to(obj)
                    local near = distance ~= nil and distance < 400
                    -- skeletal components are few: list them all, static ones only when close
                    if mesh ~= nil and (class_name == "SkeletalMeshComponent" or near) then
                        reported = reported + 1
                        local owner = try("GetOwner", function() return obj:GetOwner() end)
                        trace(string.format(
                            "census: %-8s %-24s mesh=%-26s vis=%-5s d=%-7s owner=%s",
                            class_name:gsub("MeshComponent", ""),
                            tostring(short_name(full_name(obj))), tostring(mesh),
                            tostring(try("IsVisible", function() return obj:IsVisible() end)),
                            distance and string.format("%.0f", distance) or "?",
                            tostring(owner and short_name(full_name(owner)) or "?")))
                    end
                end
            end
        end
        trace(string.format("census: %s scanned=%d reported=%d", class_name, scanned, reported))
    end
end

-- Hides one component. The hero's parts are SkeletalMeshComponentBudgeted and ignore
-- SetRenderInMainPass (the body went away, the hat and clothes stayed), so visibility is cleared too.
-- The body is handled separately: it carries the clothes, but it is also the pose source.
local function apply_hide(component)
    local key = full_name(component)
    if key ~= nil and key == state.source_name then
        -- The body carries the clothes in this game, so it has to disappear completely; it must keep
        -- posing though, which is why the animation tick option is logged at start-up.
        try("SetRenderInMainPass", function() component:SetRenderInMainPass(false) end)
        try("SetCastShadow", function() component:SetCastShadow(false) end)
        if config.hide_source_visibility then
            -- bPropagateToChildren must stay false: our carrier component hangs under this one
            try("SetVisibility", function() component:SetVisibility(false, false) end)
            try("SetHiddenInGame", function() component:SetHiddenInGame(true, false) end)
        end
        return
    end
    try("SetVisibility", function() component:SetVisibility(false, false) end)
    try("SetHiddenInGame", function() component:SetHiddenInGame(true, false) end)
    try("SetRenderInMainPass", function() component:SetRenderInMainPass(false) end)
    try("SetCastShadow", function() component:SetCastShadow(false) end)
end

-- The game re-applies its wardrobe continuously, so the hidden parts are re-hidden on every scan.
local function reapply_hidden()
    local list = state.hidden_list
    if list == nil then return end
    for index = 1, #list do
        local component = list[index]
        if valid(component) then apply_hide(component) end
    end
end

local function remember_hidden(component, label)
    local key = full_name(component)
    if key ~= nil and key == state.carrier_name then
        trace("hide: refusing to hide the carrier " .. tostring(label))
        return
    end
    state.hidden_list = state.hidden_list or {}
    state.hidden_list[#state.hidden_list + 1] = component
    state.hidden[component] = label
    apply_hide(component)
end

local function hide_next()
    -- Parts seen spawning are hidden first (that path never needs to enumerate components); anything
    -- the enumeration did find is hidden afterwards.
    local queue = state.spawned_parts
    if queue ~= nil then
        for key, component in pairs(queue) do
            queue[key] = nil
            if not valid(component) then
                trace("hide: skip stale " .. tostring(key))
            elseif key == state.carrier_name then
                trace("hide: skip our own carrier " .. tostring(key))
            elseif actor_of(component) ~= state.actor then
                -- not the hero's component (weapons ride on their own actors, sequences have copies)
                trace("hide: skip other actor " .. tostring(key))
            else
                local part = part_mesh_name(component)
                local name_ok = part ~= nil and contains_any(part, config.hide_prefixes)
                    and not contains_any(part, config.keep_visible)
                if not name_ok then
                    trace("hide: skip " .. tostring(short_name(key)) ..
                        " mesh=" .. tostring(part))
                else
                    local label = tostring(part) ..
                        " (" .. tostring(short_name(key)) .. ")"
                    trace("hide: hiding " .. label)
                    remember_hidden(component, label)
                    trace("hide: hidden " .. label)
                    return true
                end
            end
        end
    end

    local targets = state.hide_targets
    if targets == nil then return false end
    local index = (state.hide_index or 0) + 1
    local component = targets[index]
    state.hide_index = index
    if component == nil then return false end
    local label = tostring(part_mesh_name(component)) ..
        " (" .. tostring(short_name(full_name(component))) .. ")"
    if not valid(component) then
        trace("hide: skip stale " .. label)
        return true
    end
    local component_key = full_name(component)
    if component_key ~= nil and component_key == state.carrier_name then return true end
    if actor_of(component) ~= state.actor then return true end
    trace("hide: hiding " .. label)
    remember_hidden(component, label)
    trace("hide: hidden " .. label)
    return true
end

local function attach_to(component, parent)
    for _, attempt in ipairs({
        function() return component:AttachToComponent(parent, FName(""), 2, 2, 2, false) end,
        function() return component:K2_AttachToComponent(parent, FName(""), 2, 2, 2, false) end,
    }) do
        local ok, result = pcall(attempt)
        if ok and result ~= false then
            pcall(function()
                component:K2_SetRelativeLocationAndRotation({ X = 0.0, Y = 0.0, Z = 0.0 },
                    { Pitch = 0.0, Yaw = 0.0, Roll = 0.0 }, false, {}, false)
            end)
            return true
        end
    end
    return false
end

-- Move the carrier component under the body component so the retarget node (which finds its source
-- through GetAttachParent) sees it, and so both share the same placement in the actor.
local function anchor_carrier(carrier, source)
    local attached = attach_to(carrier, source)
    trace("anchor_carrier: attached=" .. tostring(attached))
    return attached
end

local function drive_carrier(carrier)
    -- The game points these part components at CharacterMesh0 as their leader-pose source. A follower
    -- component does not evaluate its own animation at all, so the retarget graph (reached through the
    -- mesh's post-process blueprint) would never run.
    --
    -- This is done ONCE per component: SetLeaderPoseComponent re-runs the follower setup, and calling
    -- it on every scan kept re-initialising the pose, so the model stood frozen in its first frame.
    local key = full_name(carrier) or "?"
    state.leader_cleared = state.leader_cleared or {}
    if not state.leader_cleared[key] then
        state.leader_cleared[key] = true
        local cleared = try("SetLeaderPoseComponent/clear",
            function() carrier:SetLeaderPoseComponent(nil, true, true) end)
        trace("carrier: leader pose cleared (" .. tostring(cleared) .. ")")
    end
    try("SetEnableAnimation", function() carrier:SetEnableAnimation(true) end)
    try("SetDisablePostProcessBlueprint",
        function() carrier:SetDisablePostProcessBlueprint(false) end)

    -- Only a component of our own needs its anim class replaced. On the game's own component the
    -- retarget graph runs as the post-process instance; setting the main class would tear that down.
    if not config.create_own_component then
        return
    end

    local class = anim_class()
    if class then
        local current = try("GetAnimInstance", function() return carrier:GetAnimInstance() end)
        local current_class = nil
        if usable(current) then
            current_class = try("GetClass", function() return current:GetClass() end)
        end
        -- recreate the anim instance only when it is missing or not ours: replacing it every scan
        -- would reset the pose and churn objects
        if current_class == nil or full_name(current_class) ~= full_name(class) then
            try("SetAnimInstanceClass", function() carrier:SetAnimInstanceClass(class) end)
            trace("carrier: anim class set -> "
                .. anim_instance_name(carrier) .. " (animclass=" .. anim_class_name(carrier) ..
                ", post=" .. post_instance_name(carrier) .. ")")
        end
    else
        trace("carrier: NO anim class available (blueprint did not load)")
    end
end

-- FVector from UE4SS arrives as a table with either upper- or lower-case keys depending on build
vec_of = function(value)
    if value == nil then return nil end
    local x = value.X or value.x
    local y = value.Y or value.y
    local z = value.Z or value.z
    if x == nil or y == nil or z == nil then return nil end
    return { X = tonumber(x), Y = tonumber(y), Z = tonumber(z) }
end

local function bone_world(component, name)
    local value = nil
    pcall(function() value = component:GetSocketLocation(FName(name)) end)
    return vec_of(value)
end

-- Component-space bone offset between two bones. World positions move when the actor walks, so they
-- cannot tell "frozen pose" from "moving character"; a bone-to-bone offset can.
local function bone_component(component, name)
    local transform = nil
    pcall(function() transform = component:GetBoneTransform(FName(name), 1) end)
    if transform ~= nil then
        local t = transform.Translation or transform.translation
        local v = vec_of(t)
        if v then return v end
    end
    -- fall back to world space: caller compares two bones, so a translation cancels out
    return bone_world(component, name)
end

local function sub(a, b)
    if not a or not b then return nil end
    return { X = a.X - b.X, Y = a.Y - b.Y, Z = a.Z - b.Z }
end

fmt_vec = function(v)
    if not v then return "?" end
    return string.format("(%.1f, %.1f, %.1f)", v.X, v.Y, v.Z)
end

-- Lua 5.4 (which UE4SS embeds) removed math.atan2 and math.degrees; math.atan takes (y, x)
local function atan2(y, x)
    if math.atan2 then return math.atan2(y, x) end
    return math.atan(y, x)
end

local function degrees(radians)
    return radians * 180.0 / math.pi
end

local function hand_axis_yaw(left, right)
    if not left or not right then return nil end
    return degrees(atan2(right.Y - left.Y, right.X - left.X))
end

-- Movement of the carrier component. Only Blueprint-callable setters work from Lua here, and the
-- K2_* variants take an out FHitResult, so several call shapes are tried until one sticks.
local function place(component, location, yaw)
    local rotator = { Pitch = 0.0, Yaw = yaw, Roll = 0.0 }
    local attempts = {
        { "K2_SetRelativeLocationAndRotation/5", function()
            component:K2_SetRelativeLocationAndRotation(location, rotator, false, {}, false)
        end },
        { "K2_SetRelativeLocationAndRotation/3", function()
            component:K2_SetRelativeLocationAndRotation(location, rotator, false)
        end },
        { "K2_SetRelativeRotation/4", function()
            component:K2_SetRelativeRotation(rotator, false, {}, false)
        end },
        { "K2_SetRelativeRotation/2", function()
            component:K2_SetRelativeRotation(rotator, false)
        end },
        { "K2_SetRelativeLocation/4", function()
            component:K2_SetRelativeLocation(location, false, {}, false)
        end },
        { "K2_SetRelativeLocation/2", function()
            component:K2_SetRelativeLocation(location, false)
        end },
    }
    for _, attempt in ipairs(attempts) do
        local ok = pcall(attempt[2])
        if ok then
            trace("place: " .. attempt[1] .. " ok")
            return true
        end
    end
    trace("place: every setter failed")
    return false
end

-- Turn and place the carrier so its shoulder axis and feet line up with the hero's. Measuring beats
-- a hard-coded rotation: it also cancels whatever transform the component inherited from the bone it
-- used to hang from.
local function align_carrier(carrier, source)
    local source_yaw = hand_axis_yaw(bone_world(source, "hand_l"), bone_world(source, "hand_r"))
    local carrier_yaw = hand_axis_yaw(bone_world(carrier, "Bip001-L-Hand"),
        bone_world(carrier, "Bip001-R-Hand"))
    if not source_yaw or not carrier_yaw then
        trace("align: hand bones unavailable")
        return false
    end

    -- a component that was registered before its mesh was assigned reports every bone at the world
    -- origin; aligning against that produces astronomically wrong offsets
    local source_pelvis = bone_world(source, "pelvis") or bone_world(source, "Pelvis")
    local carrier_pelvis = bone_world(carrier, "Bip001-Pelvis")
    if source_pelvis and carrier_pelvis then
        local dx = math.abs(source_pelvis.X - carrier_pelvis.X)
        local dy = math.abs(source_pelvis.Y - carrier_pelvis.Y)
        local dz = math.abs(source_pelvis.Z - carrier_pelvis.Z)
        if math.max(dx, dy, dz) > 10000 then
            trace(string.format("align: refusing, carrier pelvis %s is nowhere near source %s",
                fmt_vec(carrier_pelvis), fmt_vec(source_pelvis)))
            return false
        end
    end

    local yaw = source_yaw - carrier_yaw
    while yaw > 180 do yaw = yaw - 360 end
    while yaw < -180 do yaw = yaw + 360 end
    yaw = yaw + (config.rotation_offset_yaw or 0)
    trace(string.format("align: source yaw %.1f carrier yaw %.1f -> yaw offset %.1f",
        source_yaw, carrier_yaw, yaw))

    local location = { X = 0.0, Y = 0.0, Z = 0.0 }
    local current = nil
    pcall(function() current = vec_of(carrier:GetRelativeLocation()) end)
    if current then location = current end

    local applied = place(carrier, location, yaw)
    trace("align: first pass applied=" .. tostring(applied))

    -- re-measure after the turn: rotating about the origin moves the feet
    local source_foot = bone_world(source, "ball_l") or bone_world(source, "foot_l")
    local carrier_foot = bone_world(carrier, "Bip001-L-Toe0") or bone_world(carrier, "Bip001-L-Foot")
    trace("align: source foot " .. fmt_vec(source_foot) .. " carrier foot " .. fmt_vec(carrier_foot))
    if source_foot and carrier_foot then
        local shifted = {
            X = location.X + (source_foot.X - carrier_foot.X),
            Y = location.Y + (source_foot.Y - carrier_foot.Y),
            Z = location.Z + (source_foot.Z - carrier_foot.Z),
        }
        trace("align: shifting to relative " .. fmt_vec(shifted))
        applied = place(carrier, shifted, yaw)
    end

    local after_yaw = hand_axis_yaw(bone_world(carrier, "Bip001-L-Hand"),
        bone_world(carrier, "Bip001-R-Hand"))
    local after_foot = bone_world(carrier, "Bip001-L-Toe0") or bone_world(carrier, "Bip001-L-Foot")
    trace(string.format("align: done applied=%s yaw now %.1f foot now %s",
        tostring(applied), after_yaw or -999, fmt_vec(after_foot)))
    return applied
end

-- ------------------------------------------------------------------ pose watchdog
--
-- The game re-establishes the part components' leader pose whenever it rebuilds the hero (an
-- interactive animation, a cutscene, a mode switch). A leader-pose follower never evaluates its own
-- animation, so the retarget graph stops running and the mesh falls back to its reference pose - the
-- "model turned into the default pose until the game is restarted" bug. Clearing the leader pose is
-- therefore done once per component (repeating it every scan re-initialises the pose), plus again
-- here, but only when the pose is demonstrably stuck.

local distance -- defined further down, the watchdog below needs it

-- The watchdog needs a vector that only reflects the POSE, not where the character is or which way it
-- faces. World space is out: during the very interaction that breaks the retarget the character turns
-- to face its partner, and a frozen pose then looks like a fast-moving one (measured: the vector's Z
-- stayed at 5.6 while X/Y swung around a circle of ~45 cm radius). Component space is rotation
-- invariant, so that is what is used - `GetBoneTransform` occasionally answers with a zeroed transform
-- in this build, which is filtered out as "no information" by the caller.
local function hand_vector(component, hand_bone, pelvis_bone)
    local hand = bone_component(component, hand_bone)
    local pelvis = bone_component(component, pelvis_bone)
    if not hand or not pelvis then return nil end
    return sub(hand, pelvis)
end

local function rearm_pose(target, source_moved, ours_moved, escalate)
    state.pose_heals = (state.pose_heals or 0) + 1
    trace(string.format(
        "pose: stalled (source moved %.2f, ours moved %.2f) - re-arming the retarget #%d%s" ..
        " (anim=%s animclass=%s post=%s)",
        source_moved or -1, ours_moved or -1, state.pose_heals,
        escalate and " [escalated]" or "",
        anim_instance_name(target), anim_class_name(target), post_instance_name(target)))
    -- the leader pose is the usual culprit: a follower component does not evaluate its animation
    try("watchdog SetLeaderPoseComponent",
        function() target:SetLeaderPoseComponent(nil, true, true) end)
    try("watchdog SetEnableAnimation", function() target:SetEnableAnimation(true) end)
    try("watchdog SetDisablePostProcessBlueprint",
        function() target:SetDisablePostProcessBlueprint(false) end)
    try("watchdog SetComponentTickEnabled", function() target:SetComponentTickEnabled(true) end)
    try("watchdog SetBoundsScale", function() target:SetBoundsScale(2.0) end)
    if escalate then
        -- Second failure in a row: force the post-process instance to be built again. Toggling the
        -- flag is the only thing available from Lua that makes the component re-create its
        -- PostProcessInstance, and it is what recovers the pose when clearing the leader pose alone
        -- does not.
        try("watchdog post-process off",
            function() target:SetDisablePostProcessBlueprint(true) end)
        try("watchdog keep ticking", function() target:SetComponentTickEnabled(true) end)
        try("watchdog post-process on",
            function() target:SetDisablePostProcessBlueprint(false) end)
        try("watchdog mark dirty", function() target:MarkRenderStateDirty() end)
    end
    trace("pose: re-armed (post=" .. post_instance_name(target) .. ")")
    -- the pose the weapons were anchored against may have been the broken one: re-anchor them
    state.weapon_reanchor = true
end

-- Consecutive counters are useless here: the read-out occasionally returns a stale/zero transform for
-- one scan (measured: a frozen pose reported 3.0,-38.8,5.1 in the middle of a run of 9.7,-37.7,5.1),
-- and a single outlier reset the counters, so a pose frozen for 17 s only healed at the end. Instead
-- every scan is classified, and the verdict is taken over a sliding window, so a few outliers cannot
-- hide a stall.
local function count_marks(marks)
    local count = 0
    for index = 1, #marks do
        if marks[index] then count = count + 1 end
    end
    return count
end

local function watch_pose(target)
    if not config.pose_watchdog then return end
    if not valid(target) or not valid(state.source) then return end

    -- Fast, unambiguous signal: while the retarget graph exists the component always has a
    -- post-process instance. When the game tears it down (which is what happens around interactive
    -- animations), the pose is already lost - do not wait for the window.
    local post = try("GetPostProcessInstance",
        function() return target:GetPostProcessInstance() end)
    if not usable(post) then
        if state.pose_heal_tick == nil or state.tick - state.pose_heal_tick
            >= (config.pose_heal_cooldown or 6) then
            state.pose_heal_tick = state.tick
            state.pose_fail_streak = (state.pose_fail_streak or 0) + 1
            trace("pose: post-process instance is gone - rebuilding the retarget")
            rearm_pose(target, -1, -1, true)
        end
        return
    end

    local now = {
        source = hand_vector(state.source, "hand_r", "pelvis"),
        ours = hand_vector(target, "Bip001-R-Hand", "Bip001-Pelvis"),
    }
    local previous = state.pose_prev
    state.pose_prev = now

    -- A zero/garbage read means "no information", not "the pose moved": drop it and keep the last
    -- good sample, otherwise an outlier looks like motion.
    local function plausible(vector)
        if vector == nil then return nil end
        local length = math.sqrt(vector.X * vector.X + vector.Y * vector.Y + vector.Z * vector.Z)
        if length < 5.0 or length > 200.0 then return nil end
        return vector
    end
    now.source = plausible(now.source)
    now.ours = plausible(now.ours)

    local window = config.pose_slip_window or 12
    local marks = state.pose_marks or {}
    local src_move = (previous and previous.source and now.source)
        and distance(now.source, previous.source) or 0.0
    local ours_move = (previous and previous.ours and now.ours)
        and distance(now.ours, previous.ours) or 0.0
    -- when either read-out is missing the scan says nothing either way; skip it instead of counting it
    -- as "the pose moved" (which would dilute the window)
    if now.source == nil or now.ours == nil then
        if config.report_pose_window and state.tick % 5 == 0 then
            trace(string.format("pose window: no read-out (src %s, ours %s)",
                fmt_vec(now.source), fmt_vec(now.ours)))
        end
        return
    end
    local stalled_now = src_move > (config.pose_step_move_cm or 0.5)
        and ours_move < (config.pose_step_stuck_cm or 0.3)
    marks[#marks + 1] = stalled_now
    while #marks > window do table.remove(marks, 1) end
    state.pose_marks = marks

    local stalled = count_marks(marks)
    if config.report_pose_window and state.tick % 5 == 0 then
        trace(string.format(
            "pose window: %d/%d stalled (this scan=%s) | src %s move %.2f | ours %s move %.2f",
            stalled, #marks, tostring(stalled_now), fmt_vec(now.source), src_move,
            fmt_vec(now.ours), ours_move))
    end
    -- the pose is animating again, so a weapon waiting to be re-anchored can be handed back to the
    -- game's socket now (see anchor_held_weapons)
    if state.weapon_reanchor and ours_move > 0.5 then
        state.weapon_reanchor_ready = true
    end
    if stalled < (config.pose_stuck_marks or 4) then
        if stalled == 0 then state.pose_fail_streak = 0 end
        return
    end
    if state.pose_heal_tick ~= nil
        and state.tick - state.pose_heal_tick < (config.pose_heal_cooldown or 6) then
        return
    end
    state.pose_heal_tick = state.tick
    state.pose_marks = {}
    state.pose_fail_streak = (state.pose_fail_streak or 0) + 1
    rearm_pose(target, src_move, ours_move, state.pose_fail_streak >= 2)
end
local function dump_component(component, tag)
    if not valid(component) then
        trace(string.format("%s: <stale>", tag))
        return
    end
    local parent = try("GetAttachParent", function() return component:GetAttachParent() end)
    trace(string.format("%s %-14s mesh=%-14s bones=%-4s registered=%s",
        tag, object_name(component), tostring(mesh_name(component)), tostring(bone_count(component)),
        tostring(try("IsRegistered", function() return component:IsRegistered() end))))
    trace(string.format("%s   anim=%-26s animclass=%-26s post=%-26s",
        tag, anim_instance_name(component), anim_class_name(component), post_instance_name(component)))
    trace(string.format("%s   parent=%-16s at=(%s) rel=(%s) parent_at=(%s) leader=%s",
        tag, object_name(parent), fmt_vec(component_location(component)),
        fmt_vec(relative_location(component)),
        fmt_vec(parent and component_location(parent) or nil),
        object_name(try("GetMasterPoseComponent", function() return component:GetMasterPoseComponent() end))))
end

local function dump_all()
    trace("dump: source")
    dump_component(state.source, "  src")
    trace("dump: carrier (game part)")
    dump_component(state.carrier, "  carrier")
    trace("dump: our body")
    dump_component(state.body, "  body")
    trace("dump: anim class " .. tostring(anim_class() and "found" or "MISSING"))
    if valid(state.source) then
        trace("dump: source world head " .. fmt_vec(bone_world(state.source, "Head")) ..
            " hand_l " .. fmt_vec(bone_world(state.source, "hand_l")))
    end
    if valid(state.body or state.carrier) then
        local body = state.body or state.carrier
        trace("dump: ours world head " .. fmt_vec(bone_world(body, "head_Bone001")) ..
            " hand_l " .. fmt_vec(bone_world(body, "Bip001-L-Hand")))
    end
end

-- Enumerate the actor's own components. FindAllOf("/Script/Engine.SkeletalMeshComponent") returns
-- nothing in this build, so the actor's component list is the only way to reach the other parts -
-- this is also exactly how the previous version of this mod found them.
local function refresh_from_actor(actor)
    local list = component_list(actor)
    if list == nil then return end
    local count = try("component count", function() return #list end) or 0
    local ok = pcall(function()
        for index = 1, count do
            local component = list[index]
            if valid(component) then
                local name = mesh_name(component)
                if matches_any(name, config.source_mesh_names) then
                    state.source = component
                elseif name == config.carrier_mesh_name and bone_count(component) ~= 274
                    and not is_our_body(component) then
                    -- the bone count separates our mesh (Bip001, 369 bones) from the game's own
                    -- Hun_Head_New, which shares the asset name but uses the hero skeleton
                    state.carrier = component
                end
            end
        end
    end)
    if not ok then trace("refresh_from_actor: component walk failed") end
end

-- Creates our own SkeletalMeshComponent instead of re-using the game's part component. The game's
-- component is driven by its own "copy pose" anim graph and has its own animation flags, which
-- silently kept the retarget output from ever being evaluated. A component we create has none of
-- that baggage; the mesh asset and the anim blueprint are already in memory (the game loaded them
-- through the carrier part), so nothing has to be loaded by name.
local function create_own_body(actor, mesh, class, source)
    local component_class = nil
    pcall(function() component_class = StaticFindObject("/Script/Engine.SkeletalMeshComponent") end)
    if component_class == nil then
        trace("own body: SkeletalMeshComponent class not found")
        return nil
    end

    local component = nil
    for _, attempt in ipairs({
        function() return StaticConstructObject(component_class, actor, FName(config.component_name), 0, nil) end,
        function() return StaticConstructObject(component_class, actor, FName(config.component_name), 0) end,
        function() return StaticConstructObject(component_class, actor, FName(config.component_name)) end,
    }) do
        local ok, created = pcall(attempt)
        if ok and created ~= nil then
            component = created
            break
        end
    end
    if component == nil then
        trace("own body: StaticConstructObject failed")
        return nil
    end
    trace("own body: object " .. tostring(full_name(component)))

    -- Order matters. Registering before the mesh is assigned leaves the component with no bones at
    -- all (every bone query answers 0 and it draws black), and the parent has to be in place before
    -- the anim class: the retarget node looks its source component up once, when the anim instance is
    -- created, and a missing parent at that moment means it never retargets anything.
    try("SetSkeletalMeshAsset", function() component:SetSkeletalMeshAsset(mesh) end)
    trace("own body: mesh=" .. tostring(mesh_name(component)) ..
        " bones=" .. tostring(bone_count(component)))
    try("SetCollisionEnabled", function() component:SetCollisionEnabled(0) end)
    try("SetVisibility", function() component:SetVisibility(true, true) end)
    try("SetHiddenInGame", function() component:SetHiddenInGame(false, true) end)
    try("SetGenerateOverlapEvents", function() component:SetGenerateOverlapEvents(false) end)
    trace("own body: RegisterComponent -> " ..
        tostring(try("RegisterComponent", function() return component:RegisterComponent() end)) ..
        " registered=" .. tostring(try("IsRegistered", function() return component:IsRegistered() end)))

    local attached = attach_to(component, source)
    trace("own body: attached=" .. tostring(attached) ..
        " at=" .. fmt_vec(component_location(component)))

    -- 0 == EAnimationMode::AnimationBlueprint; without it the anim instance is created but ignored
    try("SetAnimationMode", function() component:SetAnimationMode(0) end)
    -- InitAnim() returns early when this is off, and then no instance is ever spawned
    try("SetEnableAnimation", function() component:SetEnableAnimation(true) end)
    try("SetDisablePostProcessBlueprint", function() component:SetDisablePostProcessBlueprint(false) end)
    try("SetAnimInstanceClass", function() component:SetAnimInstanceClass(class) end)
    trace("own body: animclass now=" .. anim_class_name(component) ..
        " anim=" .. anim_instance_name(component) ..
        " post=" .. post_instance_name(component))
    try("MarkRenderStateDirty", function() component:MarkRenderStateDirty() end)
    return component
end

-- Disables the engine's animation update-rate optimization. That optimization stops evaluating a
-- mesh which is not being rendered, and this mod hides the hero's body while still retargeting from
-- its pose - so with the optimization on, the pose freezes. APawn/APlayerController::ConsoleCommand
-- is BlueprintCallable, which is why a console command is used instead of a property write.
local function disable_uro()
    local found = try("FindAllOf PlayerController", function() return FindAllOf("PlayerController") end)
    if type(found) == "table" then
        for _, controller in pairs(found) do
            if usable(controller) then
                local output = try("ConsoleCommand",
                    function() return controller:ConsoleCommand("a.URO.Enable 0") end)
                trace("uro: a.URO.Enable 0 -> " .. tostring(output))
                return true
            end
        end
    end
    trace("uro: no player controller found yet")
    return false
end

-- Writes a property through UE4SS's reflection API. ImportText is what the engine itself uses to
-- parse property text, so it handles enums and bitfields correctly - writing the value directly from
-- Lua does not (a 4-byte write into a 1-byte enum corrupted the neighbours and crashed the game).
local function set_property(obj, property_name, text)
    local ok, err = pcall(function()
        local reflection = obj:Reflection()
        if reflection == nil then error("no reflection") end
        local property = reflection:GetProperty(property_name)
        if property == nil then error("property not found") end
        if not property:IsValid() then error("property invalid") end
        property:ImportText(text, property:ContainerPtrToValuePtr(obj), 0, obj)
    end)
    if ok then
        trace(string.format("set_property: %s = %s", property_name, text))
        return true
    end
    trace(string.format("set_property FAILED: %s = %s (%s)", property_name, text, tostring(err)))
    return false
end

-- Makes a component keep refreshing its bone transforms even while it is not being rendered, which is
-- what the retarget needs from a hidden pose source:
--   * AlwaysTickPoseAndRefreshBones disables the update-rate path that throttles unrendered meshes,
--   * bEnableUpdateRateOptimizations turns that optimization off for this component altogether.
local function force_anim_refresh(component)
    set_property(component, "VisibilityBasedAnimTickOption", "AlwaysTickPoseAndRefreshBones")
    set_property(component, "bEnableUpdateRateOptimizations", "False")
    try("SetComponentTickEnabled", function() component:SetComponentTickEnabled(true) end)
end

-- Hides every mesh component that belongs to any "Hun" actor: the hero, but also the copies the game
-- keeps around for sequences and the character UI. Those copies render the same outfit, which is why
-- hiding only the hero's own component left the robe and the top visible.
local function hide_all_hun_parts()
    local objects = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    if type(objects) ~= "table" then return 0 end
    local hidden = 0
    for _, obj in pairs(objects) do
        if usable(obj) and not is_cdo(obj) then
            local key = full_name(obj)
            local owner = try("GetOwner", function() return obj:GetOwner() end)
            local owner_key = owner ~= nil and full_name(owner) or nil
            local mesh = part_mesh_name(obj)
            local belongs_to_hun = (owner_key ~= nil and owner_key:find("Hun", 1, true) ~= nil)
                or (key ~= nil and key:find("Hun", 1, true) ~= nil)
            local keep = key ~= nil and (key == state.carrier_name or key == state.source_name)
            local weapon = mesh ~= nil and contains_any(mesh, config.keep_visible)
            if belongs_to_hun and not keep and not weapon and mesh ~= nil then
                local already = state.hidden[obj] ~= nil
                try("SetVisibility", function() obj:SetVisibility(false, false) end)
                try("SetHiddenInGame", function() obj:SetHiddenInGame(true, false) end)
                if not already then
                    state.hidden[obj] = mesh
                    trace("hide: " .. mesh .. " (" .. tostring(short_name(key)) .. ")")
                    hidden = hidden + 1
                end
            end
        end
    end
    return hidden
end

-- Logs the socket each weapon component hangs from and whether the (possibly blanked) body mesh still
-- provides it. Weapons are attached by socket name, so replacing the body mesh can silently make them
-- disappear - this says exactly which names have to be recreated on the replacement mesh.
local function report_weapon_sockets()
    local objects = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    if type(objects) ~= "table" then return end
    for _, obj in pairs(objects) do
        if usable(obj) then
            local mesh = part_mesh_name(obj)
            if mesh ~= nil and contains_any(mesh, config.keep_visible) then
                local socket = try("GetAttachSocketName", function() return obj:GetAttachSocketName() end)
                local socket_name = tostring(socket)
                local exists = try("DoesSocketExist",
                    function() return state.source:DoesSocketExist(FName(socket_name)) end)
                trace(string.format("socket: %-24s mesh=%-22s socket=%-18s on source=%s",
                    tostring(short_name(full_name(obj))), mesh, socket_name, tostring(exists)))
            end
        end
    end
end

-- Scabbards are separate little meshes that ride on their own sockets. Their sockets belong to the
-- Hun skeleton, so once the visible body is Korinsna's they fly around on their own. Matched by mesh
-- name because every weapon variant has its own scabbard asset (and some weapons have none).
-- `back_items` are exempt: those are anchored onto Korinsna's own back (see anchor_back_items).
local function hide_scabbards()
    if state.actor_name == nil then return end
    local objects = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    if type(objects) ~= "table" then return end
    for _, obj in pairs(objects) do
        if usable(obj) then
            local mesh = part_mesh_name(obj)
            -- Only ours: every NPC carries a scabbard too, and hiding those stripped the enemies of
            -- their weapons' sheaths (and of any part that happened to be named like one).
            if mesh ~= nil and mesh:lower():find("scab", 1, true)
                and not matches_any(mesh, config.back_items or {})
                and (belongs_to_actor(obj, state.actor_name)
                    or attached_to_hero(obj)) then
                local key = full_name(obj) or mesh
                try("SetVisibility", function() obj:SetVisibility(false, false) end)
                try("SetHiddenInGame", function() obj:SetHiddenInGame(true, false) end)
                try("SetRenderInMainPass", function() obj:SetRenderInMainPass(false) end)
                try("SetCastShadow", function() obj:SetCastShadow(false) end)
                if not state.hidden_names[key] then
                    state.hidden_names[key] = true
                    state.hidden[obj] = mesh
                    trace("hide: scabbard " .. mesh)
                end
            end
        end
    end
end

-- The host materials are Masked and read their cutout from an `OpacityMask` texture. Its inherited
-- default is a non-VT engine example map, so the virtual texture samplers fall back to the VT
-- placeholder - a dither pattern, which is the speckled, see-through look and the reason the model
-- read as dark and unclear in shadow. Overriding that parameter with our own white VT map makes the
-- mask fully opaque.
--
-- A per-slot dynamic material instance is the only way to do this from Lua in this build: the mesh
-- component exposes Scalar/Vector/Color parameter setters but no texture one.
local function force_opaque(component)
    if not usable(component) then return false end
    -- Slot 5's albedo is our own pure white VT map, so the asset is already shipped and loaded. It has
    -- to be a VT map: the host samplers are virtual textures, and a plain texture there falls back to
    -- the VT placeholder (the dither pattern this is fixing).
    local white = find_loaded(
        "/Game/PBZContent/Characters/Hero/Hun_New_V2b/Textures/" ..
        "T_ZeroHun_Cloth_05_BC.T_ZeroHun_Cloth_05_BC")
    if white == nil then
        trace("opaque: the white VT texture is not loaded, skipping")
        return false
    end

    local count = try("GetNumMaterials", function() return component:GetNumMaterials() end) or 0
    local done = 0
    for index = 0, count - 1 do
        local mid = try("CreateDynamicMaterialInstance",
            function() return component:CreateDynamicMaterialInstance(index) end)
        if usable(mid) then
            -- the cutout parameter is named differently per host material family
            for _, param in ipairs({ "OpacityMask", "MaskTex", "Opacity" }) do
                try("SetTextureParameterValue " .. param,
                    function() mid:SetTextureParameterValue(FName(param), white) end)
            end
            done = done + 1
        end
    end
    trace(string.format("opaque: %d of %d material slots patched", done, count))
    return done > 0
end

-- Weapons are separate ACTORS whose root component the game attaches, once, to one of Hun's hand
-- mount sockets (`WEAPON_R`, `weapon_l`) - and to the `Pt_*_Back_Socket` family when sheathed. That
-- is why a held weapon sits at a constant 9.5-10.4 cm from Hun's hand bone while Korinsna's hand is
-- anywhere from 7 to 52 cm away from it: nothing re-writes the weapon per frame, only the attach
-- decides where it hangs. Redirecting that attach is therefore enough, and it has to be the ACTOR
-- ROOT that is re-parented - re-parenting the mesh child (what this script used to do) leaves the
-- root behind and produces two drivers, which is what made the blades fly around.
--
-- The correction after the re-parent is a single translation. Both hands come out of the retarget
-- with the same world orientation up to one constant per hand (measured over seven samples: left
-- -20.2/97.3/-4.5, right 8.3/-83.0/5.0, stable to 0.1 degrees), so the visually correct placement is
-- "keep the weapon's world rotation, move it by the vector from Hun's hand to ours". After that one
-- shift the weapon's transform relative to our hand bone is constant - exactly like it is relative to
-- Hun's hand bone - so no per-frame correction is needed.
--
-- Hand IK was the other candidate and is not viable: with correct proportions the gap between the two
-- hands grows to 40 cm in some poses, which no unstretched arm can reach.
local function is_weapon_mesh(name)
    if name == nil then return false end
    local lowered = name:lower()
    return lowered:find("blade", 1, true) ~= nil
        or lowered:find("weapon", 1, true) ~= nil
        or lowered:find("knife", 1, true) ~= nil
        or lowered:find("sword", 1, true) ~= nil
        or lowered:find("spear", 1, true) ~= nil
        or lowered:find("axe", 1, true) ~= nil
        or lowered:find("hook", 1, true) ~= nil
        or lowered:find("heimoshang", 1, true) ~= nil
end

distance = function(a, b)
    if not a or not b then return math.huge end
    local dx, dy, dz = a.X - b.X, a.Y - b.Y, a.Z - b.Z
    return math.sqrt(dx * dx + dy * dy + dz * dz)
end

local function unit(v)
    if not v then return nil end
    local length = math.sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z)
    if length < 0.001 then return nil end
    return { X = v.X / length, Y = v.Y / length, Z = v.Z / length }
end

-- "Behind the body" for this rig: the back skirt bones hang down the back of the dress, so their
-- offset from the pelvis is a direction the model itself guarantees to point away from the front.
-- Flattened to the horizontal plane, because a dress flares outwards, not upwards.
local function back_direction(carrier, pelvis)
    for _, name in ipairs({ "b_skirt_1", "b_skirt_2", "b_skirt_3", "b_skirt_4", "b_skirt_5" }) do
        local skirt = bone_world(carrier, name)
        if skirt then
            local v = sub(skirt, pelvis)
            local flat = unit({ X = v.X, Y = v.Y, Z = 0.0 })
            if flat then return flat end
        end
    end
    return nil
end

local function socket_text_of(component)
    local socket = try("GetAttachSocketName",
        function() return component:GetAttachSocketName() end)
    if socket == nil then return "?" end
    -- FName arrives as userdata; tell UE4SS to render it
    return tostring(try("ToString", function() return socket:ToString() end) or socket)
end

-- Which hand a mount socket belongs to. Sheathed weapons use the back sockets and must stay there,
-- so anything with "back" in the name is refused. The side has to come from the SOCKET, not from the
-- weapon's name: `HookMan_Hook_L` is held in the right hand.
local function mount_side(socket_name)
    if socket_name == nil then return nil end
    local lowered = socket_name:lower()
    if lowered:find("back", 1, true) then return nil end
    if not (lowered:find("weapon", 1, true) or lowered:find("hand", 1, true)) then return nil end
    if lowered:find("_r", 1, true) then return "r" end
    if lowered:find("_l", 1, true) then return "l" end
    return nil
end

local HANDS = {
    r = { game = "hand_r", ours = "Bip001-R-Hand" },
    l = { game = "hand_l", ours = "Bip001-L-Hand" },
}

-- The attach frame of a weapon actor is its own root component. `AActor:GetRootComponent` is not
-- callable from this UE4SS build, so walk up the attach chain instead and stop at the first parent
-- that belongs to another actor: that last component is the actor's root.
local function actor_root_of(component)
    local owner_name = full_name(try("GetOwner", function() return component:GetOwner() end))
    local node = component
    for _ = 1, 8 do
        local parent = try("GetAttachParent", function() return node:GetAttachParent() end)
        if not usable(parent) then break end
        local parent_owner = full_name(try("GetOwner", function() return parent:GetOwner() end))
        if parent_owner ~= owner_name then break end
        node = parent
    end
    return node
end

local function set_world_location(component, target)
    local attempts = {
        { "K2_SetWorldLocation/4", function()
            component:K2_SetWorldLocation(target, false, {}, false)
        end },
        { "K2_SetWorldLocation/2", function()
            component:K2_SetWorldLocation(target, false)
        end },
    }
    for _, attempt in ipairs(attempts) do
        if pcall(attempt[2]) then
            trace("place: " .. attempt[1] .. " ok")
            return true
        end
    end
    trace("place: every world setter failed")
    return false
end

local function shift_world(component, delta)
    local at = component_location(component)
    if not at then return false end
    return set_world_location(component, {
        X = at.X + delta.X, Y = at.Y + delta.Y, Z = at.Z + delta.Z })
end

-- The game puts the weapon 9.5 cm from Hun's hand bone, which is where HIS grip is. Korinsna's hand
-- bone is much closer to the knuckles (4.4 cm long, fingers start 6.0 cm away), so the same distance
-- puts the hilt on the outside of the fist at the first finger joint. Keep the direction the game
-- chose and only rescale the distance to our own grip: `grip_distance` in config.lua.
local function pull_to_grip(component, origin, target_length)
    if not target_length or target_length <= 0 then return nil end
    local at = component_location(component)
    if not at then return nil end
    local v = sub(at, origin)
    local length = math.sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z)
    if length < 0.5 then return nil end
    local k = target_length / length
    local target = { X = origin.X + v.X * k, Y = origin.Y + v.Y * k, Z = origin.Z + v.Z * k }
    if not set_world_location(component, target) then return nil end
    return target_length
end

local function push_log_once(key, message)
    state.log_once = state.log_once or {}
    if state.log_once[key] then return end
    state.log_once[key] = true
    trace(message)
end

-- A holstered weapon hangs from a socket on the hero's body. The socket itself is fine - the hidden
-- body is still animated and the retargeted pose follows the same animation - but the socket sits on
-- HUN's back: wide shoulders, thick robe. Korinsna is smaller and her skirt is rigid, so a weapon left
-- on that socket floats behind her or cuts through the dress (the same reason the waist knife is
-- anchored to her pelvis, see anchor_back_items).
--
-- So a weapon that is put away is carried over to Korinsna's own body: pelvis to pelvis (which keeps
-- its left/right and up/down placement on the back), keeping the game's world rotation, plus the same
-- outward push along the back of the dress that the waist knife uses. Once attached to her pelvis it
-- simply follows her animation, and nothing has to be corrected per frame.
local function anchor_sheathed_weapon(root, source, socket, mesh)
    local carrier = state.body or state.carrier
    if not valid(carrier) or not valid(source) then return end
    local carrier_name = full_name(carrier)
    local socket_world = try("GetSocketLocation",
        function() return source:GetSocketLocation(FName(socket)) end)
    local gap = distance(component_location(root), socket_world)
    local key = full_name(root) or tostring(mesh)

    local our_spine = bone_world(carrier, config.sheathed_anchor or "Bip001-Spine")
    local hun_spine = bone_world(source, config.sheathed_source_bone or "spine_03")
    if not our_spine or not hun_spine then
        -- fall back to the pelvis pair, which is always present
        our_spine = bone_world(carrier, "Bip001-Pelvis")
        hun_spine = bone_world(source, "pelvis")
    end
    if not socket_world or not our_spine or not hun_spine then return end

    -- keep the weapon's placement on the back, but expressed on OUR torso: pelvis-to-spine would put
    -- it where the hips are, and the hips sway a lot during locomotion, which looked like the weapon
    -- riding the character's backside. Same idea as the hand anchor (our bone - the game's bone).
    local delta = sub(our_spine, hun_spine)
    local back = back_direction(carrier, our_spine)
    local push = config.sheathed_push_cm or 0.0
    if back and push ~= 0 then
        delta = { X = delta.X + back.X * push, Y = delta.Y + back.Y * push, Z = delta.Z }
    end

    push_log_once("holster|" .. key, string.format(
        "weapon: %s holstered on '%s' (socket gap %.1f cm) -> %s", tostring(mesh),
        tostring(socket), gap, config.sheathed_anchor or "Bip001-Spine"))

    local bone = config.sheathed_anchor or "Bip001-Spine"
    try("attach sheathed weapon", function()
        return root:K2_AttachToComponent(carrier, FName(bone), 1, 1, 1, false)
    end)
    if full_name(try("GetAttachParent", function() return root:GetAttachParent() end))
        ~= carrier_name then
        trace("weapon: could not carry " .. tostring(mesh) .. " over to " .. bone)
        return
    end
    shift_world(root, delta)
    -- Deliberately no visibility change here: the weapon actor's ROOT is not the weapon mesh (the mesh
    -- is a child called "Weapon Mesh"), and forcing the root visible/renderable made the game's hidden
    -- helper geometry show up as a translucent box with an arrow. The game keeps the weapon itself
    -- visible; carrying the root is all that is needed.
    state.weapon_carried = state.weapon_carried or {}
    if not state.weapon_carried[key] then
        state.weapon_carried[key] = true
        trace(string.format("weapon: %s carried to %s, moved %s, pushed %.1f cm along %s",
            tostring(mesh), bone, fmt_vec(delta), push, fmt_vec(back)))
    end
end

local function anchor_held_weapons()
    local carrier = state.body or state.carrier
    local source = state.source
    if not valid(carrier) or not valid(source) then return end
    local carrier_name = full_name(carrier)
    local source_name = full_name(source)

    -- After a pose heal the weapon keeps the relative transform it was given while the hand bone was
    -- still in its (wrong) reference pose, which shows up as a wrong blade orientation until the
    -- weapon is swapped. Put such a weapon back on the game's own socket; the normal anchoring below
    -- re-derives the offset from a correct pose on the next scan.
    if state.weapon_reanchor then
        -- Wait until the pose is demonstrably alive again: re-anchoring in the same scan as the heal
        -- bakes the broken pose into the weapon again (measured: a 182 cm hand gap, i.e. the hand was
        -- still at the reference pose).
        if not state.weapon_reanchor_ready then
            return
        end
        state.weapon_reanchor_ready = false
        local objects = try("FindAllOf SkeletalMeshComponent",
            function() return FindAllOf("SkeletalMeshComponent") end)
        if type(objects) == "table" then
            local seen = {}
            for _, obj in pairs(objects) do
                if usable(obj) and not is_cdo(obj) then
                    local mesh = part_mesh_name(obj)
                    if mesh ~= nil and is_weapon_mesh(mesh) then
                        local root = actor_root_of(obj)
                        local key = usable(root) and full_name(root) or nil
                        local socket = key and (state.weapon_sockets or {})[key] or nil
                        if key and socket and not seen[key]
                            and full_name(try("GetAttachParent",
                                function() return root:GetAttachParent() end)) == carrier_name then
                            seen[key] = true
                            try("reanchor weapon", function()
                                return root:K2_AttachToComponent(source, FName(socket), 2, 2, 2, false)
                            end)
                            trace("weapon: " .. tostring(mesh) ..
                                " returned to '" .. tostring(socket) .. "' for a fresh anchor")
                        end
                    end
                end
            end
        end
        state.weapon_reanchor = false
    end

    local hands = {}
    for side, names in pairs(HANDS) do
        hands[side] = {
            bone = names.ours,
            game = bone_world(source, names.game),
            ours = bone_world(carrier, names.ours),
        }
    end

    -- The weapon anchor is derived from the hand bone, so never anchor while the pose is obviously
    -- broken (the hands more than a metre apart cannot be a real pose): wait for the next scan.
    local gap_now = distance(hands.r.game, hands.r.ours)
    if gap_now > (config.anchor_max_gap_cm or 100.0) then
        push_log_once("gap|" .. string.format("%.0f", gap_now),
            string.format("weapon: holding off, the pose looks broken (hand gap %.1f cm)", gap_now))
    end

    local objects = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    if type(objects) ~= "table" then return end

    local seen = {}
    for _, obj in pairs(objects) do
        if usable(obj) and not is_cdo(obj) then
            local mesh = part_mesh_name(obj)
            if mesh ~= nil and is_weapon_mesh(mesh) then
                local owner = try("GetOwner", function() return obj:GetOwner() end)
                -- the hero's own knives and scabbards are part components of the hero actor; they
                -- already ride sockets on the hidden body and are in the right place
                if usable(owner) and full_name(owner) ~= full_name(state.actor) then
                    local root = actor_root_of(obj)
                    local key = usable(root) and full_name(root) or nil
                    if key and not seen[key] then
                        seen[key] = true
                        local parent_name = full_name(try("GetAttachParent",
                            function() return root:GetAttachParent() end))
                        -- Anything the game hangs elsewhere (a back socket, the chest, the world) keeps
                        -- the game's anchor - but see anchor_sheathed_weapon.
                        if parent_name ~= carrier_name and parent_name == source_name then
                            local socket = socket_text_of(root)
                            local side = mount_side(socket)
                            local hand = side and hands[side] or nil
                            if hand and hand.game and hand.ours then
                                -- A hand mount is only anchored from a plausible pose; leaving it on
                                -- the game's socket for one more scan is invisible, anchoring from a
                                -- reference pose bakes a wrong offset into the weapon.
                                if gap_now > (config.anchor_max_gap_cm or 100.0) then
                                    -- nothing to do this scan
                                else
                                local before = distance(component_location(root), hand.game)
                                try("attach weapon " .. tostring(mesh), function()
                                    return root:K2_AttachToComponent(carrier, FName(hand.bone),
                                        1, 1, 1, false)
                                end)
                                local now = full_name(try("GetAttachParent",
                                    function() return root:GetAttachParent() end))
                                if now == carrier_name then
                                    local delta = sub(hand.ours, hand.game)
                                    shift_world(root, delta)
                                    local grip = pull_to_grip(root, hand.ours,
                                        (config.grip_distance or {})[side])
                                    -- remembered so a re-anchor after a pose heal can put the weapon
                                    -- back where the game had it (see anchor_held_weapons)
                                    state.weapon_sockets = state.weapon_sockets or {}
                                    state.weapon_sockets[key] = socket

                                    -- "was" is how far the weapon sat from Hun's hand; it is also the
                                    -- offset we reproduce, and "now" is after the grip rescale
                                    trace(string.format(
                                        "weapon: %s on %s -> %s | hand gap %.1f cm | offset %.1f -> %s cm",
                                        tostring(mesh), socket, hand.bone,
                                        distance(hand.game, hand.ours), before,
                                        grip and string.format("%.1f", grip) or "unchanged"))
                                else
                                    trace("weapon: could not attach " .. tostring(mesh))
                                end
                                end
                            else
                                anchor_sheathed_weapon(root, source, socket, mesh)
                            end
                        end
                    end
                end
            end
        end
    end
end

-- The hero's own waist knife and its scabbard ride a socket on Hun's lower back. That spot is right
-- for HIS body, but Korinsna is narrower and her skirt is rigid, so the blade ends up inside the
-- skirt with only the tip poking out. Both parts are carried over with the body (pelvis to pelvis,
-- keeping the game's world rotation) and then pushed out along the back of the dress, so they sit on
-- the outside of the skirt like a sheathed knife should.
local function anchor_back_items()
    local items = config.back_items or {}
    if #items == 0 then return end
    local carrier = state.body or state.carrier
    local source = state.source
    if not valid(carrier) or not valid(source) then return end
    local carrier_name = full_name(carrier)
    local source_name = full_name(source)
    local our_pelvis = bone_world(carrier, "Bip001-Pelvis")
    local hun_pelvis = bone_world(source, "pelvis")
    if not our_pelvis or not hun_pelvis then return end

    local delta = sub(our_pelvis, hun_pelvis)
    local back = back_direction(carrier, our_pelvis)
    local push = config.back_item_push_cm or 0.0
    if back and push ~= 0 then
        delta = { X = delta.X + back.X * push, Y = delta.Y + back.Y * push, Z = delta.Z }
    end

    local objects = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    if type(objects) ~= "table" then return end
    for _, obj in pairs(objects) do
        if usable(obj) and not is_cdo(obj) then
            local mesh = part_mesh_name(obj)
            if mesh ~= nil and matches_any(mesh, items) then
                local parent_name = full_name(try("GetAttachParent",
                    function() return obj:GetAttachParent() end))
                if parent_name == carrier_name then
                    -- anchored already; the game's wardrobe pass hides it again every so often
                    show_part(obj)
                elseif parent_name == source_name then
                    try("attach back item " .. tostring(mesh), function()
                        return obj:K2_AttachToComponent(carrier, FName("Bip001-Pelvis"),
                            1, 1, 1, false)
                    end)
                    if full_name(try("GetAttachParent",
                        function() return obj:GetAttachParent() end)) == carrier_name then
                        shift_world(obj, delta)
                        show_part(obj)
                        trace(string.format(
                            "back: %s -> Bip001-Pelvis, moved %s, pushed out %.1f cm along %s",
                            tostring(mesh), fmt_vec(delta), push, fmt_vec(back)))
                    else
                        trace("back: could not attach " .. tostring(mesh))
                    end
                end
            end
        end
    end
end

-- True when the actor is the pawn the player actually controls. Cutscene / preview copies of the hero
-- exist as extra actors with the same part assets; those must never take over the retarget, and they
-- are exactly the actors whose leftover outfit has to be hidden.
local player_pawn_cache = { tick = -1, name = nil, logged = false }

local function player_pawn_name()
    if player_pawn_cache.tick == state.tick then return player_pawn_cache.name end
    local found = nil
    local count = 0
    local controllers = try("FindAllOf PlayerController",
        function() return FindAllOf("PlayerController") end)
    if type(controllers) == "table" then
        for _, controller in pairs(controllers) do
            if usable(controller) then
                count = count + 1
                local pawn = try("K2_GetPawn", function() return controller:K2_GetPawn() end)
                if not usable(pawn) then
                    pawn = try("GetControlledPawn",
                        function() return controller:GetControlledPawn() end)
                end
                if not usable(pawn) then
                    pawn = try("GetPawn", function() return controller:GetPawn() end)
                end
                if usable(pawn) then
                    found = full_name(pawn)
                    break
                end
            end
        end
    end
    if not player_pawn_cache.logged or player_pawn_cache.name ~= found then
        player_pawn_cache.logged = true
        player_pawn_cache.name = found
        trace(string.format("pawn: %s (%d controller(s) seen)",
            found and short_name(found) or "unresolved", count))
    end
    player_pawn_cache.tick = state.tick
    player_pawn_cache.name = found
    return found
end

local function is_player_pawn(actor_name)
    if actor_name == nil then return false end
    return player_pawn_name() == actor_name
end

-- Names the game gives the hero actors it spawns for playback instead of gameplay: a level sequence
-- copy (`BP_Seq_Hun_C`, `BP_Seq_Hun_Climax_C`) and the wardrobe's appearance preview. This is the one
-- discriminator that does not depend on the pawn lookup working, so it is used both for "do not adopt
-- this actor" and for "clean this actor's leftover outfit up".
local COPY_NAME_MARKERS = { "BP_Seq_", "Preview" }

local function looks_like_copy(owner_name)
    if owner_name == nil then return false end
    for _, marker in ipairs(COPY_NAME_MARKERS) do
        if owner_name:find(marker, 1, true) then return true end
    end
    return false
end

-- The young hero's meshes are different (`Hun_Young_*`) and must keep their outfit, so anything whose
-- owner mentions "Young" is out of scope for every cleanup below.
local function hero_owned(owner_name)
    if owner_name == nil then return false end
    if owner_name:find("Young", 1, true) then return false end
    return owner_name:find("Hun", 1, true) ~= nil
end

-- A hero actor that is NOT the player: the cutscene copies (`BP_Seq_Hun_C`, `BP_Seq_Hun_Climax_C`),
-- the appearance preview, and anything else the game spawns with the hero's part assets. Deciding this
-- by "is the player pawn" rather than by our own state matters: on the prologue map the player is the
-- YOUNG hero, so the mod has no carrier of its own there - and yet the adult copies in the cutscene
-- still render the original outfit and must be cleaned up.
local function is_hero_copy(owner_name)
    if not hero_owned(owner_name) then return false end
    if owner_name == state.actor_name then return false end
    -- a sequence / preview actor is always a copy
    if looks_like_copy(owner_name) then return true end
    -- any other hero-looking actor is a copy when the pawn can be resolved and it is not the pawn
    -- (a cutscene can reuse a gameplay-looking hero class, e.g. `BP_Renewal_Hun_Climax_C`)
    local pawn = player_pawn_name()
    return pawn ~= nil and pawn ~= owner_name
end

-- Object path -> live object, cached. Only objects that already exist in memory resolve, which is
-- fine here: every material instance we name is referenced by the mesh itself, so it is loaded.
local function resolve_material(path)
    if state.material_cache == nil then state.material_cache = {} end
    local cached = state.material_cache[path]
    if usable(cached) then return cached end
    local found = find_loaded(path)
    if found then
        state.material_cache[path] = found
    end
    return found
end

-- The game's status system swaps the first material slot of the *head part* when the hero is hurt
-- (`Hun_Status/MI_ZeroHun_Head_Injured*`, seen in the log as
-- `material[0] MID_MI_ZeroHun_Head_Injured30_...`). Our mesh ships as that head part, so the dress
-- slot ended up rendering with a pale skin shader instead of its albedo - the "faded dress" bug.
-- Whatever the game puts in a guarded slot is replaced with the intended instance again.
local function guard_materials(component, label)
    local guard = config.material_guard
    if type(guard) ~= "table" then return end
    local prefix = label or "material"
    for index, path in pairs(guard) do
        local want = resolve_material(path)
        if want == nil then
            if not state.guard_missing then
                state.guard_missing = true
                trace(prefix .. ": cannot resolve " .. tostring(path))
            end
        else
            local have = try("GetMaterial", function() return component:GetMaterial(index) end)
            local have_name = usable(have) and full_name(have) or "<none>"
            if have_name ~= full_name(want) then
                local ok = pcall(function() component:SetMaterial(index, want) end)
                trace(string.format("%s: slot %d was %s -> restored %s (%s)", prefix, index,
                    tostring(short_name(have_name)), tostring(short_name(path)),
                    ok and "ok" or "FAILED"))
            end
        end
    end
end

-- Re-resolve a cached component by its object name.
--
-- A cached UObject wrapper outlives the object: the cutscene copies are created and destroyed
-- continuously, and calling an engine function on a freed pointer crashes inside the game itself
-- (0xc0000005 in PBZ.exe, the same signature as the teleport crash that §6.16 fixed). Resolving the
-- name again proves the object is still alive before anything is touched, and costs a hash lookup.
local function resolve_component(key)
    if key == nil then return nil end
    local found = nil
    pcall(function() found = StaticFindObject(key) end)
    found = usable(found)
    if found == nil then return nil end
    -- the same name must still denote the same object (a recycled name is not our component)
    if full_name(found) ~= key then return nil end
    return found
end

-- The hero exists more than once: the player actor, plus the copies the game spawns for cutscenes
-- (`BP_Seq_Hun_C`, `BP_Seq_Hun_Climax_C`) and for the appearance preview. `Hun_Body_Simple` is the one
-- original-outfit mesh this mod does NOT replace at asset level (the real body is the retarget pose
-- source, so it is hidden at runtime only, see `hide_source_visibility`) - which means every copy
-- renders the original outfit again, together with whatever else it carries (accessory static meshes,
-- Chaos Cloth garments, grooms).
--
-- The copies only need OUR mesh, so everything else they own is hidden. Two properties matter for the
-- implementation:
--   * the sweep must not run over the whole level every scan. `FindAllOf("StaticMeshComponent")` on a
--     real map walks thousands of components, and doing that twice a second visibly stuttered the
--     game. The component list is therefore collected rarely (when something new appeared, or every
--     `copy_rescan_scans`) and re-applied from the cache every scan.
--   * the copy's body keeps ticking and its Korinsna mesh gets its leader pose cleared once, so the
--     retarget graph still runs inside the cutscene instead of showing the reference pose.
--
-- The young hero uses different meshes (`Hun_Young_*`), is never a copy of the adult hero, and keeps
-- his outfit.
local COPY_CLASSES = {
    "SkeletalMeshComponent", "StaticMeshComponent", "ChaosClothComponent",
    "GroomComponent", "SkeletalMeshComponentBudgeted",
}

local function copy_component_entry(obj, class_name)
    local is_mesh_class = class_name == "SkeletalMeshComponent"
        or class_name == "StaticMeshComponent"
        or class_name == "SkeletalMeshComponentBudgeted"
    local mesh = is_mesh_class and part_mesh_name(obj) or nil
    local asset = mesh
    if asset == nil and class_name == "ChaosClothComponent" then
        asset = object_name(try("GetClothAsset", function() return obj:GetClothAsset() end))
    end
    -- only the name is cached, never the object itself (see resolve_component)
    return { key = full_name(obj), class = class_name, mesh = mesh, asset = asset }
end

-- Rare, expensive: rebuild the list of components that belong to hero copies and must be hidden.
local function collect_copy_components()
    state.copy_seen = state.copy_seen or {}
    state.copy_list = {}
    for _, class_name in ipairs(COPY_CLASSES) do
        local objects = try("FindAllOf " .. class_name, function() return FindAllOf(class_name) end)
        if type(objects) == "table" then
            for _, obj in pairs(objects) do
                if usable(obj) and not is_cdo(obj) then
                    local owner_name = full_name(try("GetOwner", function() return obj:GetOwner() end))
                    if is_hero_copy(owner_name) then
                        local key = full_name(obj)
                        if key ~= nil and key ~= state.carrier_name then
                            local entry = copy_component_entry(obj, class_name)
                            -- the carrier is our own mesh and weapons are supposed to stay visible
                            local keep = entry.mesh ~= nil and (entry.mesh == config.carrier_mesh_name
                                or is_weapon_mesh(entry.mesh))
                            if not keep then
                                state.copy_list[#state.copy_list + 1] = entry
                                local tag = class_name .. "|" .. tostring(entry.asset)
                                if not state.copy_seen[tag] then
                                    state.copy_seen[tag] = true
                                    trace(string.format("copy part: %-30s %-26s (%s)",
                                        class_name, tostring(entry.asset), tostring(short_name(key))))
                                end
                            end
                        end
                    end
                end
            end
        end
    end
    trace("copy part: " .. #state.copy_list .. " component(s) to keep hidden on hero copies")
    return state.copy_list
end

-- Cheap: re-apply the hiding to the cached list (the game's wardrobe / sequence pass turns parts back
-- on), and set up the pieces that need a one-off call. Every entry is re-resolved by name first: the
-- cutscene copies come and go constantly, and touching one that has been destroyed crashes the game.
local function apply_copy_hiding()
    local list = state.copy_list
    if list == nil then return end
    state.copy_hidden = state.copy_hidden or {}
    state.copy_leader = state.copy_leader or {}
    local dropped = 0
    for index = 1, #list do
        local entry = list[index]
        -- never hide our own mesh, whatever the classification said
        if entry.mesh ~= config.carrier_mesh_name then
            local obj = resolve_component(entry.key)
            if obj == nil then
                dropped = dropped + 1
            else
                local key = entry.key
                if entry.mesh ~= nil and not state.copy_hidden[key] then
                    state.copy_hidden[key] = true
                    -- the pose has to keep updating even though the mesh is no longer drawn: the
                    -- copy's own Korinsna mesh is a leader-pose follower of it and retargets from it
                    force_anim_refresh(obj)
                end
                try("copy part SetVisibility", function() obj:SetVisibility(false, false) end)
                try("copy part SetHiddenInGame", function() obj:SetHiddenInGame(true, false) end)
                try("copy part SetRenderInMainPass", function() obj:SetRenderInMainPass(false) end)
                try("copy part SetCastShadow", function() obj:SetCastShadow(false) end)
            end
        end
    end
    if dropped > 0 then
        -- the list contains dead components; rebuild it soon instead of touching them again
        state.copy_dirty = true
    end

    -- the copies' own Korinsna mesh: clear the leader pose once so it evaluates the retarget graph, and
    -- keep its material slots guarded - the game swaps the head part's first slot (the dress) on these
    -- copies too, which is why the dress looked faded during cutscenes (§6.21).
    local carriers = state.copy_carriers
    if carriers == nil then return end
    for index = 1, #carriers do
        local obj = resolve_component(carriers[index])
        if obj ~= nil then
            local key = carriers[index]
            if key ~= state.carrier_name and not state.copy_leader[key] then
                state.copy_leader[key] = true
                try("copy leader pose clear",
                    function() obj:SetLeaderPoseComponent(nil, true, true) end)
                try("copy SetEnableAnimation", function() obj:SetEnableAnimation(true) end)
                try("copy SetDisablePostProcessBlueprint",
                    function() obj:SetDisablePostProcessBlueprint(false) end)
                try("copy keep ticking", function() obj:SetComponentTickEnabled(true) end)
                trace("copy: made " .. tostring(short_name(key)) .. " evaluate the retarget")
            end
            guard_materials(obj, "copy material")
        else
            state.copy_dirty = true
        end
    end
end

-- Rare, expensive: the copies' own Korinsna meshes (which must keep running) and the Chaos Cloth
-- garments on any hero (the wardrobe has variants whose assets are not blanked at design time).
local function collect_hero_garments()
    state.copy_carriers = {}
    state.cloth_list = {}
    state.cloth_seen = state.cloth_seen or {}

    local meshes = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    if type(meshes) == "table" then
        for _, obj in pairs(meshes) do
            if usable(obj) and not is_cdo(obj) then
                local owner_name = full_name(try("GetOwner", function() return obj:GetOwner() end))
                if is_hero_copy(owner_name) and part_mesh_name(obj) == config.carrier_mesh_name then
                    -- names only: a copy can be destroyed before the next scan (see resolve_component)
                    local key = full_name(obj)
                    if key ~= nil then
                        state.copy_carriers[#state.copy_carriers + 1] = key
                    end
                end
            end
        end
    end

    local cloths = try("FindAllOf ChaosClothComponent",
        function() return FindAllOf("ChaosClothComponent") end)
    if type(cloths) == "table" then
        for _, obj in pairs(cloths) do
            if usable(obj) and not is_cdo(obj) then
                local owner_name = full_name(try("GetOwner", function() return obj:GetOwner() end))
                if hero_owned(owner_name) then
                    local asset_name = object_name(try("GetClothAsset",
                        function() return obj:GetClothAsset() end))
                    local key = full_name(obj)
                    if key ~= nil then
                        state.cloth_list[#state.cloth_list + 1] = key
                        if not state.cloth_seen[key] then
                            state.cloth_seen[key] = true
                            trace(string.format("cloth: hiding %s owner=%s", asset_name,
                                tostring(short_name(owner_name))))
                        end
                    end
                end
            end
        end
    end
    trace(string.format("cloth: %d garment(s), %d copy carrier(s)", #state.cloth_list,
        #state.copy_carriers))
end

local function apply_cloth_hiding()
    local list = state.cloth_list
    if list == nil then return end
    local dropped = 0
    for index = 1, #list do
        local obj = resolve_component(list[index])
        if obj == nil then
            dropped = dropped + 1
        else
            try("cloth SetVisibility", function() obj:SetVisibility(false, false) end)
            try("cloth SetHiddenInGame", function() obj:SetHiddenInGame(true, false) end)
            try("cloth SetRenderInMainPass", function() obj:SetRenderInMainPass(false) end)
            try("cloth SetCastShadow", function() obj:SetCastShadow(false) end)
        end
    end
    if dropped > 0 then state.copy_dirty = true end
end

-- Runs whether or not the retarget is set up: on the prologue map the player IS the young hero (a
-- different mesh, not replaced), so the mod idles there, while the adult copies in that map's
-- cutscenes still render the original outfit.
local function sweep_other_heroes()
    -- The rescan walks every skeletal / static mesh in the level, so it must not be triggered by every
    -- single component the game spawns: during a cutscene that would be a full sweep per scan.
    -- `copy_dirty` is still honoured, but not more often than `copy_rescan_min_scans`.
    local since_last = state.tick - (state.copy_scan_tick or -100000)
    local due = state.copy_list == nil
        or ((state.copy_dirty or since_last >= (config.copy_rescan_scans or 60))
            and since_last >= (config.copy_rescan_min_scans or 4))
    if due then
        state.copy_dirty = false
        state.copy_scan_tick = state.tick
        if config.hide_copy_outfit or config.hide_copy_bodies then
            collect_copy_components()
        end
        if config.hide_hero_cloth or config.hide_copy_bodies then
            collect_hero_garments()
        end
    end
    if config.hide_copy_outfit or config.hide_copy_bodies then
        apply_copy_hiding()
    end
    if config.hide_hero_cloth then
        apply_cloth_hiding()
    end
end

-- The hero's blanked part meshes are sub-centimetre degenerate triangles. They are invisible, but a
-- shadow pass over near-zero-area geometry is a classic source of flickering black specks, which is
-- what kept appearing around the character. Keeping them out of both the shadow and the main pass
-- costs nothing: nothing about their skeleton or weights is needed at render time.
--
-- ONLY the hero's own components may be touched here. This used to run over every skeletal mesh in
-- the level, which took every NPC and every bell save point out of the base pass - they are skeletal
-- meshes too, so they went black or lost limbs. The list is collected once per hero actor.
local function hero_part_components()
    local refresh = state.quiet_parts ~= nil and state.quiet_parts_actor == state.actor_name
        and (state.tick - (state.quiet_parts_tick or 0)) < 20
    if refresh then
        return state.quiet_parts
    end
    local list = {}
    local objects = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    if type(objects) == "table" then
        for _, obj in pairs(objects) do
            if usable(obj) and not is_cdo(obj) and belongs_to_actor(obj, state.actor_name) then
                local key = full_name(obj)
                local mesh = part_mesh_name(obj)
                if mesh ~= nil and key ~= state.carrier_name and key ~= state.source_name
                    and not is_weapon_mesh(mesh) then
                    -- names, not objects: the wardrobe can destroy a part while the map keeps running
                    list[#list + 1] = key
                end
            end
        end
    end
    state.quiet_parts = list
    state.quiet_parts_actor = state.actor_name
    state.quiet_parts_tick = state.tick
    trace("shadow: " .. #list .. " part meshes on the hero")
    return list
end

local function quiet_blank_parts()
    if state.actor_name == nil then return end
    local list = hero_part_components()
    for index = 1, #list do
        local obj = resolve_component(list[index])
        if obj ~= nil then
            try("part SetCastShadow", function() obj:SetCastShadow(false) end)
            try("part SetRenderInMainPass", function() obj:SetRenderInMainPass(false) end)
        end
    end
    if not state.quiet_reported and #list > 0 then
        state.quiet_reported = true
        trace("shadow: silenced " .. #list .. " hero part meshes")
    end
end

-- Reports how each weapon is attached: parent component, socket name, and whether that changes between
-- scans. This decides whether the weapons can be re-parented onto Korinsna's hands at all - if the
-- game re-attaches them every frame, any re-parenting is undone immediately and the two drivers fight.
local function report_weapon_attachment(tag)
    local objects = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    if type(objects) ~= "table" then return end
    for _, obj in pairs(objects) do
        if usable(obj) then
            local mesh = part_mesh_name(obj)
            if mesh ~= nil and is_weapon_mesh(mesh) then
                local parent = try("GetAttachParent", function() return obj:GetAttachParent() end)
                local socket = try("GetAttachSocketName",
                    function() return obj:GetAttachSocketName() end)
                local socket_text = "?"
                if socket ~= nil then
                    -- FName arrives as userdata; tell UE4SS to render it
                    socket_text = tostring(try("ToString", function() return socket:ToString() end)
                        or socket)
                end
                trace(string.format("attach[%s]: %-26s parent=%-20s socket=%s", tag,
                    tostring(mesh), tostring(short_name(full_name(parent))), socket_text))
            end
        end
    end
end

-- ---------------------------------------------------------------------------------------------
-- Weapon geometry census
--
-- The weapons are drawn where Hun's hand is, and Korinsna's arm is shorter, so the question that
-- has to be answered with numbers is: how far apart are the two hands, and what is each weapon
-- actually parented to (its own actor's Root, or the hero's body component)? The attach chain is
-- printed in full because a weapon mesh hanging from `Root` of its OWN actor means the actor - not
-- the component - is what has to be re-parented.
-- ---------------------------------------------------------------------------------------------

local function attach_chain(component, depth)
    local parts = { object_name(component) .. "/" .. socket_text_of(component) }
    local node = component
    for _ = 1, (depth or 5) - 1 do
        local parent = try("GetAttachParent", function() return node:GetAttachParent() end)
        if not usable(parent) then break end
        parts[#parts + 1] = object_name(parent) .. "/" .. socket_text_of(parent)
        node = parent
    end
    return table.concat(parts, " <- ")
end

-- A weapon that is put away must end up exactly where the game's back socket puts it. The only way to
-- know what the game does at that moment is to record the whole attach chain whenever it changes
-- (which component is attached to what, with which socket), so the fix works from facts.
local function watch_weapon_chain()
    if not config.report_weapon_chain then return end
    local source = state.source
    if not valid(source) then return end
    local carrier = state.body or state.carrier
    local carrier_name = valid(carrier) and full_name(carrier) or "<none>"
    local objects = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    if type(objects) ~= "table" then return end
    state.weapon_chain = state.weapon_chain or {}
    local seen = {}
    for _, obj in pairs(objects) do
        if usable(obj) and not is_cdo(obj) then
            local mesh = part_mesh_name(obj)
            if mesh ~= nil and is_weapon_mesh(mesh) then
                local owner = try("GetOwner", function() return obj:GetOwner() end)
                if usable(owner) and full_name(owner) ~= state.actor_name then
                    local root = actor_root_of(obj)
                    local key = usable(root) and full_name(root) or tostring(mesh)
                    if not seen[key] then
                        seen[key] = true
                        -- only the hero's own weapons: every NPC carries one too, and those would
                        -- only add noise
                        local parent_name = full_name(try("GetAttachParent",
                            function() return root:GetAttachParent() end))
                        if parent_name == state.source_name or parent_name == carrier_name then
                            local chain = attach_chain(obj, 4)
                            if state.weapon_chain[key] ~= chain then
                                state.weapon_chain[key] = chain
                                local socket = socket_text_of(root)
                                local socket_world = try("GetSocketLocation",
                                    function() return source:GetSocketLocation(FName(socket)) end)
                                local gap = distance(component_location(root), socket_world)
                                trace(string.format(
                                    "weapon chain: %-22s %s | root gap to socket %s", tostring(mesh),
                                    chain, gap < math.huge and string.format("%.1f cm", gap) or "?"))
                            end
                        end
                    end
                end
            end
        end
    end
end


local function bone_world_rot(component, name)
    local rotator = nil
    pcall(function() rotator = component:GetSocketRotation(FName(name)) end)
    if rotator == nil then return nil end
    local pitch = rotator.Pitch or rotator.pitch
    local yaw = rotator.Yaw or rotator.yaw
    local roll = rotator.Roll or rotator.roll
    if pitch == nil then return nil end
    return { Pitch = tonumber(pitch), Yaw = tonumber(yaw), Roll = tonumber(roll) }
end

local function fmt_rot(rotator)
    if not rotator then return "?" end
    return string.format("p%.1f/y%.1f/r%.1f", rotator.Pitch, rotator.Yaw, rotator.Roll)
end

-- Sockets are how the hero's own weapons are attached, so knowing which ones exist decides whether
-- Korinsna's skeleton needs a matching socket or whether the weapon hangs from a bone.
local function log_sockets(component, tag)
    local mesh = mesh_of(component)
    if not mesh then return end
    local skeleton = try("GetSkeleton", function() return mesh:GetSkeleton() end)
    for _, holder in ipairs({ { "mesh", mesh }, { "skel", skeleton } }) do
        if usable(holder[2]) then
            local ok, list = pcall(function() return holder[2].Sockets end)
            if ok and list ~= nil then
                local names, count = {}, 0
                pcall(function() count = list:GetArrayNum() end)
                if count == 0 then pcall(function() count = #list end) end
                for index = 1, math.min(tonumber(count) or 0, 80) do
                    local socket = nil
                    pcall(function() socket = list[index] end)
                    local name = nil
                    if socket ~= nil then
                        pcall(function() name = socket.SocketName end)
                        if name == nil then
                            pcall(function() name = socket:GetPropertyValue("SocketName") end)
                        end
                    end
                    if name ~= nil then
                        names[#names + 1] = tostring(
                            try("ToString", function() return name:ToString() end) or name)
                    end
                end
                trace(string.format("%s sockets[%s] n=%s: %s", tag, holder[1], tostring(count),
                    table.concat(names, " ")))
            end
        end
    end
end

local function report_weapon_geometry(tag, with_tree)
    local source = state.source
    local carrier = state.body or state.carrier
    if not valid(source) or not valid(carrier) then return end

    local game_l = bone_world(source, "hand_l")
    local game_r = bone_world(source, "hand_r")
    local our_l = bone_world(carrier, "Bip001-L-Hand")
    local our_r = bone_world(carrier, "Bip001-R-Hand")
    trace(string.format("geo[%s] hands game L%s R%s | ours L%s R%s | apart L=%.1f R=%.1f",
        tag, fmt_vec(game_l), fmt_vec(game_r), fmt_vec(our_l), fmt_vec(our_r),
        distance(game_l, our_l), distance(game_r, our_r)))
    trace(string.format("geo[%s] hand rot game L %s R %s | ours L %s R %s", tag,
        fmt_rot(bone_world_rot(source, "hand_l")), fmt_rot(bone_world_rot(source, "hand_r")),
        fmt_rot(bone_world_rot(carrier, "Bip001-L-Hand")),
        fmt_rot(bone_world_rot(carrier, "Bip001-R-Hand"))))
    trace(string.format("geo[%s] source=%s carrier=%s actor=%s", tag, object_name(source),
        object_name(carrier), object_name(state.actor)))
    log_sockets(source, "geo[" .. tag .. "]")
    log_sockets(carrier, "geo[" .. tag .. "]")

    state.weapon_prev = state.weapon_prev or {}
    local objects = try("FindAllOf SkeletalMeshComponent",
        function() return FindAllOf("SkeletalMeshComponent") end)
    if type(objects) == "table" then
        for _, obj in pairs(objects) do
            if usable(obj) and not is_cdo(obj) then
                local mesh = part_mesh_name(obj)
                if mesh ~= nil and is_weapon_mesh(mesh) then
                    local at = component_location(obj)
                    local owner = try("GetOwner", function() return obj:GetOwner() end)
                    local key = full_name(obj) or mesh
                    local previous = state.weapon_prev[key]
                    state.weapon_prev[key] = at
                    trace(string.format("geo[%s] %-26s owner=%s", tag, tostring(mesh),
                        object_name(owner)))
                    trace(string.format("geo[%s]   chain %s", tag, attach_chain(obj, 6)))
                    trace(string.format(
                        "geo[%s]   world%s moved=%s toGameL=%.1f toGameR=%.1f toOurL=%.1f toOurR=%.1f",
                        tag, fmt_vec(at),
                        previous and string.format("%.1f", distance(previous, at)) or "n/a",
                        distance(at, game_l), distance(at, game_r),
                        distance(at, our_l), distance(at, our_r)))
                end
            end
        end
    end

    -- the hero's own component tree, so a weapon parented to a sibling of the body is visible
    if with_tree then
        local root = actor_root_of(source)
        for _, component in ipairs(children_of(root, {})) do
            trace(string.format("geo[%s] tree %s mesh=%s parent=%s/%s", tag, object_name(component),
                tostring(part_mesh_name(component)),
                object_name(try("GetAttachParent", function() return component:GetAttachParent() end)),
                socket_text_of(component)))
        end
    end
end

-- ------------------------------------------------------------------- materials
--
-- The 8 slots reuse the game's own material instances, so the textures they sample are the only thing
-- this mod changes. Their *parameters* still carry the hero's settings, and one of them dominated the
-- colour: `MI_ZeroHun_Cloth_02_b` (the dress slot) enables the hero's fabric overlay layer
-- (`Overlay` = true, `DetailColor` = T_Fabric_C, `ColorTiling` = 40) at `BaseColor Intensity` = 0.5,
-- i.e. the albedo is blended 1:1 with a grey fabric noise - which is what made the red dress look
-- faded and hid its pattern. The fix is at asset level: the dress borrows `MI_ZeroHun_Cloth_05_b`
-- instead, which is the same material family without the overlay (see ue/scripts/build_mod_assets.py).
--
-- Parameters were meant to be corrected at runtime through a dynamic material instance, but
-- `CreateAndSetMaterialInstanceDynamic` reached through Lua produced an instance of the *wrong*
-- parent material (log: `MID_MI_ZeroHun_Head_Injured30_...` on the dress slot) and its
-- `Get/SetScalarParameterValue` never read back, so that route is a dead end. What is left is a
-- read-only probe: which material each slot actually renders with.

local function report_materials(component)
    local count = try("GetNumMaterials", function() return component:GetNumMaterials() end) or 0
    trace("material: " .. count .. " slots on " .. tostring(short_name(full_name(component))))
    for index = 0, count - 1 do
        local material = try("GetMaterial", function() return component:GetMaterial(index) end)
        trace(string.format("material[%d] %s", index, object_name(material)))
    end
end


local function setup()
    if state.actor_name == nil then return end
    -- Stale-state gate: after a map change the hero actor is destroyed before the new one is built, so
    -- everything we hold can point at freed memory. Compare identities by name and drop the state
    -- instead of poking the old components (that is what crashed the game on teleport).
    if not valid(state.actor) then
        reset_actor_state("the hero actor is gone")
        return
    end
    if is_cdo(state.actor) then
        reset_actor_state("the hero actor is a class default object")
        return
    end
    if state.source_name ~= nil and not belongs_to_actor(state.source, state.actor_name) then
        reset_actor_state("the pose source no longer belongs to the hero actor")
        return
    end
    if state.carrier_name ~= nil and not belongs_to_actor(state.carrier, state.actor_name) then
        reset_actor_state("the carrier no longer belongs to the hero actor")
        return
    end
    refresh_from_actor(state.actor)

    if config.disable_uro and not state.uro_disabled then
        state.uro_disabled = disable_uro()
    end

    -- the hidden body has to keep producing fresh bone transforms (see force_anim_refresh)
    if config.force_anim_refresh and valid(state.source) and not state.refreshed[state.source] then
        state.refreshed[state.source] = true
        force_anim_refresh(state.source)
    end

    if not valid(state.source) then
        trace("setup: hero body component is gone")
        return
    end
    if not state.fixed[state.source] then
        state.fixed[state.source] = true
        trace("hero body: " .. tostring(full_name(state.source)))
        keep_ticking(state.source, "source")
    end

    if not valid(state.carrier) then
        if not state.reported_missing_carrier then
            state.reported_missing_carrier = true
            trace("setup: no component with mesh " .. tostring(config.carrier_mesh_name) ..
                " and a non-hero skeleton yet")
        end
        return
    end

    if not state.fixed[state.carrier] then
        state.fixed[state.carrier] = true
        trace("carrier: " .. tostring(full_name(state.carrier)))
        dump_component(state.carrier, "  carrier-in")

        local mesh = mesh_of(state.carrier)
        local class = anim_class()
        if mesh then
            trace("carrier: mesh skeleton = " .. object_name(
                try("GetSkeleton", function() return mesh:GetSkeleton() end)))
            trace("carrier: mesh post-process bp = " .. object_name(
                try("PostProcessAnimBlueprint", function() return mesh.PostProcessAnimBlueprint end)))
            trace("source: VisibilityBasedAnimTickOption = " ..
                tostring(try("read anim tick option",
                    function() return state.source.VisibilityBasedAnimTickOption end)))
        end

        if config.create_own_component and mesh and class then
            local own = create_own_body(state.actor, mesh, class, state.source)
            if own then
                state.body = own
                keep_ticking(own, "own body")
                show_part(own)
                dump_all()
            end
        end

        if not state.body then
            -- The game's own part component is registered, placed and - through the mesh's
            -- post-process blueprint - already running the retarget graph. All that is needed is to
            -- make it stop following CharacterMesh0's pose, because a follower component never
            -- evaluates its own animation.
            state.body = state.carrier
            state.carrier_name = full_name(state.carrier)
            state.source_name = full_name(state.source)
            trace("hide: carrier=" .. tostring(state.carrier_name) ..
                " source=" .. tostring(state.source_name))
            try("SetLeaderPoseComponent", function() state.carrier:SetLeaderPoseComponent(nil, true, true) end)
            keep_ticking(state.carrier, "carrier")
            show_part(state.carrier)
            -- the source body appeared before the actor was known, so it never went through the
            -- spawn queue; queue it by hand
            if config.hide_parts and valid(state.source) then
                state.spawned_parts = state.spawned_parts or {}
                local key = full_name(state.source)
                if key and not state.spawned_parts[key] then
                    state.spawned_parts[key] = state.source
                    trace("hide: queued the source body")
                end
            end
            dump_all()
        end
    end

    local target = state.body or state.carrier
    -- every scan: the game may re-apply a leader pose, which would silently stop our anim instance
    drive_carrier(target)

    -- The game re-arms the leader pose after interactive animations / cutscenes; the pose then drops
    -- back to the reference pose. Only re-clear when the pose is demonstrably stuck (see watch_pose).
    watch_pose(target)

    if config.report_materials and state.aligned and not state.materials_reported and valid(target) then
        state.materials_reported = true
        report_materials(target)
    end

    -- Every scan: the game re-applies its damage/status material on the part we ship, which silently
    -- replaced the dress material (see guard_materials).
    if valid(target) then
        guard_materials(target)
    end

    if config.force_opaque and not state.opaque_done and valid(target) then
        state.opaque_done = force_opaque(target)
    end

    -- Re-applied every scan: the mask/visibility flags are also touched by the game's own wardrobe
    -- system, and a re-enabled shadow on the retargeted mesh is what shows up as flickering black
    -- patches near the character.
    if config.carrier_cast_shadow == false and valid(target) then
        try("carrier SetCastShadow", function() target:SetCastShadow(false) end)
    end

    if state.aligned and not state.dumped_everything and config.dump_census then
        state.dumped_everything = true
        dump_everything()
    end

    if config.hide_scabbards then
        hide_scabbards()
    end

    if config.quiet_blank_parts then
        quiet_blank_parts()
    end

    sweep_other_heroes()

    -- one-off census of how each weapon is attached, kept for future debugging of the anchoring
    if config.report_weapon_attachment and state.aligned then
        state.attach_checks = state.attach_checks or 0
        local marks = { 3, 9 }
        local mark = marks[state.attach_checks + 1]
        if mark ~= nil and state.tick >= state.carrier_ready_tick + mark then
            state.attach_checks = state.attach_checks + 1
            report_weapon_attachment("t+" .. mark)
        end
    end

    -- Every scan: the game re-attaches a weapon when it is drawn, sheathed or swapped, so the check
    -- has to be repeated - anchoring is only done while the weapon actually hangs from a hand socket.
    if config.attach_weapons and state.aligned then
        anchor_held_weapons()
    end

    -- Logs the full attach chain whenever it changes (draw / sheathe / swap), with the gap between the
    -- weapon's root and the socket it names.
    watch_weapon_chain()

    if state.aligned then
        anchor_back_items()
    end

    -- Spread over a minute of play so the samples also cover the weapons being drawn and swung:
    -- a weapon that sits at a fixed offset from the hand shows up as a constant toGame distance.
    if config.report_weapon_geometry and state.aligned then
        state.geo_checks = state.geo_checks or 0
        local marks = { 2, 6, 10, 20, 40, 80, 120 }
        local mark = marks[state.geo_checks + 1]
        if mark ~= nil and state.tick >= state.carrier_ready_tick + mark then
            state.geo_checks = state.geo_checks + 1
            local ok, err = pcall(report_weapon_geometry, "t+" .. mark, state.geo_checks == 1)
            if not ok then trace("geo error: " .. tostring(err)) end
        end
    end

    if config.hide_all_hun_parts and state.aligned then
        hide_all_hun_parts()
    end

    if state.aligned and not state.reported_sockets then
        state.reported_sockets = true
        report_weapon_sockets()
    end

    -- repeat the hero census a few times so wardrobe assignments made after start-up are caught
    if state.aligned and config.dump_census then
        state.census_steps = state.census_steps or 0
        local marks = { 3, 12, 30, 60 }
        local mark = marks[state.census_steps + 1]
        if mark ~= nil and state.tick >= state.carrier_ready_tick + mark then
            state.census_steps = state.census_steps + 1
            census_hero("t+" .. mark)
        end
    end

    -- Keep the hero's own body invisible. SetVisibility alone would stop the engine refreshing its
    -- bone transforms (see `force_anim_refresh`), so the pose would freeze and the retarget would copy
    -- stale data. bPropagateToChildren must stay false: our carrier hangs under this component.
    -- Shadow casting is cleared too: the hidden body has no business casting a shadow, and its shadow
    -- is what showed up as flickering black patches while playing attack animations.
    if config.hide_source_visibility and valid(state.source) then
        try("source SetVisibility", function() state.source:SetVisibility(false, false) end)
        try("source SetHiddenInGame", function() state.source:SetHiddenInGame(true, false) end)
        try("source SetCastShadow", function() state.source:SetCastShadow(false) end)
        -- Reflection writes are expensive and one is enough; the flag only has to be set once per
        -- hero (it is also what spammed the log with a line every scan).
        if not state.hidden_shadow_cleared then
            state.hidden_shadow_cleared = set_property(state.source, "bCastHiddenShadow", "False")
        end
    end
    if config.hide_body_render_pass and valid(state.source) then
        try("source SetRenderInMainPass",
            function() state.source:SetRenderInMainPass(false) end)
        try("source SetCastShadow", function() state.source:SetCastShadow(false) end)
    end

    -- The alignment and the outfit hiding are done on later scans rather than with ExecuteWithDelay:
    -- that function does not exist in this UE4SS build (the call silently did nothing), and by the
    -- time the periodic scan fires, all the parts are registered and safe to touch.
    if not state.carrier_ready_tick then
        state.carrier_ready_tick = state.tick
    elseif not state.aligned and state.tick > state.carrier_ready_tick then
        if state.body == state.carrier then
            -- the game's own component already sits exactly where the hero's body sits
            state.aligned = true
        else
            state.align_attempts = (state.align_attempts or 0) + 1
            if align_carrier(state.body or state.carrier, state.source) or state.align_attempts >= 5 then
                state.aligned = true
            end
        end
        dump_all()
    end

    if config.hide_parts and state.aligned then
        if not state.hide_collected then
            state.hide_collected = true
            state.hide_targets = collect_hide_targets(state.actor, state.body) or {}
        end
        local more = hide_next()
        if state.hidden_list then reapply_hidden() end
        -- once nothing is left to hide, take a census of what is still drawn
        if not more and not state.dumped_everything then
            state.dumped_everything = true
            dump_everything()
        end
    end

    -- The game's own copy of the carrier mesh sits under the same actor; it is hidden on a later
    -- tick, because hiding components while their owner is still spawning them crashed the game.
    if state.aligned and state.body and state.body ~= state.carrier and valid(state.carrier) then
        hide_part(state.carrier, "carrier(" .. tostring(mesh_name(state.carrier)) .. ")")
    end

    -- Animation probe. Comparing component-space pelvis->hand vectors: world positions also change
    -- when the actor walks, so they cannot tell "frozen pose" from "moving character".
    state.tick = state.tick + 1
    if config.report_motion_every > 0 and state.tick % config.report_motion_every == 0 then
        local body = state.body or state.carrier
        if valid(state.source) and valid(body) then
            local source_arm = sub(bone_component(state.source, "hand_l"),
                bone_component(state.source, "pelvis"))
            local body_arm = sub(bone_component(body, "Bip001-L-Hand"),
                bone_component(body, "Bip001-Pelvis"))
            trace(string.format(
                "motion: source pelvis->hand %s | ours pelvis->hand %s",
                fmt_vec(source_arm), fmt_vec(body_arm)))
        end
    end
end


local function consider(obj)
    if obj == nil or not valid(obj) or is_cdo(obj) or is_our_body(obj) then return end
    local name = mesh_name(obj)
    local is_source = matches_any(name, config.source_mesh_names)
    local is_carrier = (name == config.carrier_mesh_name and bone_count(obj) ~= 274)
    if not (is_source or is_carrier) then return end

    local actor = actor_of(obj)
    if actor == nil or is_cdo(actor) then return end

    -- A level-sequence / preview actor never drives the mod: it carries the same part assets (so the
    -- asset override makes it show Korinsna's mesh) but its animation belongs to the sequence.
    local actor_key = full_name(actor)
    if looks_like_copy(actor_key) then
        push_log_once("seq|" .. tostring(actor_key),
            "state: not adopting " .. tostring(short_name(actor_key)) .. " (sequence/preview actor)")
        return
    end

    -- A different hero actor usually means the game travelled / re-created him: every component we
    -- remember belongs to an object that is being destroyed, and using one of them crashed the game.
    -- The actor we already hold wins unless the new one is demonstrably the player's pawn.
    if state.actor_name ~= nil and actor_key ~= state.actor_name then
        if valid(state.actor) and not is_player_pawn(actor_key) then
            push_log_once("other|" .. tostring(actor_key),
                "state: keeping the current hero actor, ignoring " ..
                tostring(short_name(actor_key)))
            return
        end
        reset_actor_state("the hero actor was re-created: " ..
            tostring(short_name(state.actor_name)) .. " -> " .. tostring(short_name(actor_key)))
    end
    state.actor = actor
    state.actor_name = actor_key

    if is_source then
        state.source = obj
        trace("hero body: " .. tostring(full_name(obj)) .. " actor=" .. tostring(full_name(actor)))
    else
        state.carrier = obj
        trace("carrier: " .. tostring(full_name(obj)) .. " actor=" .. tostring(full_name(actor)))
    end
    setup()
end

local function scan()
    if not state.enabled then return end
    if config.probe_only then
        if not state.probed then
            state.probed = true
            trace("probe: carrier mesh found = " ..
                tostring(find_loaded("/HuaShira/Characters/Hero/Hero_Hun/SkinParts/Hun_Head_New.Hun_Head_New") ~= nil))
            trace("probe: anim class = " .. tostring(anim_class() and "found" or "MISSING"))
        end
        return
    end
    setup()
    -- Runs whether or not the retarget is set up (see sweep_other_heroes): the prologue map plays as
    -- the young hero, where the mod has no carrier of its own, but its cutscene copies still need this.
    sweep_other_heroes()
end

-- Logs what the game is creating, then hands anything interesting to consider(). The log line is
-- what tells us which actor really owns the Korinsna mesh, because the hero's parts are not all on
-- the actor that owns CharacterMesh0.
local function inspect_new(obj)
    if obj == nil or not valid(obj) or is_cdo(obj) then return end
    local name = mesh_name(obj)
    local actor_name = nil
    local owner = nil
    pcall(function() owner = obj:GetOwner() end)
    if usable(owner) then actor_name = full_name(owner) end

    -- Queue anything that could be one of the hero's part components. The mesh asset often is not
    -- assigned yet while the object is still being constructed, so the mesh name is not reliable
    -- here: the hero's parts are components called "mesh..." (meshhead, meshHair, meshUpCloth, ...)
    -- plus CharacterMesh0, and they are filtered properly when they are hidden.
    local component_name = short_name(full_name(obj))
    local queue_by_name = component_name ~= nil
        and (component_name:sub(1, 4) == "mesh" or component_name:sub(1, 9) == "Character")    local queue_by_mesh = contains_any(name, config.hide_prefixes)
        and not contains_any(name, config.keep_visible)
        and not is_carrier_mesh(name)
    if config.hide_parts and (queue_by_name or queue_by_mesh) then
        state.spawned_parts = state.spawned_parts or {}
        local key = full_name(obj)
        if key and not state.spawned_parts[key] then
            state.spawned_parts[key] = obj
            trace("hide: queued " .. tostring(component_name) .. " mesh=" .. tostring(name) ..
                " owner=" .. tostring(actor_name))
        end
    end

    -- A hero copy spawned: the (rare, level-wide) sweep that lists its components has to run again.
    -- Detecting it here keeps the sweep event driven instead of running every scan, which stuttered.
    if hero_owned(actor_name) then
        state.copy_dirty = true
    end

    -- only report components that actually draw something: the level creates thousands during load
    if name == nil then return end
    trace(string.format("new component: %-20s bones=%-5s mesh=%-22s owner=%s",
        tostring(short_name(full_name(obj))), tostring(bone_count(obj)), tostring(name),
        tostring(actor_name)))
    consider(obj)
end

local function on_new_object(obj)
    if obj == nil or config.probe_only then return end
    -- the notification fires while the object is still being constructed, so touch nothing here and
    -- let the object settle on the game thread first (this is what the previous mod did, and it is
    -- the only reliable way in this build: FindAllOf returns nothing)
    local function handle()
        if type(ExecuteInGameThread) == "function" then
            -- two hops: the first lets the engine finish constructing the object, the second reads it
            ExecuteInGameThread(function()
                ExecuteInGameThread(function() inspect_new(obj) end)
            end)
        else
            inspect_new(obj)
        end
    end
    handle()
end

local function toggle_ours()
    state.show_ours = not state.show_ours
    if valid(state.carrier) then
        pcall(function() state.carrier:SetVisibility(state.show_ours, true) end)
    end
    trace("carrier visible=" .. tostring(state.show_ours))
end

local function boot()
    trace("boot, mod_dir=" .. tostring(mod_dir))
    trace("config from " .. tostring(config_source) ..
        " probe_only=" .. tostring(config.probe_only) ..
        " hide_parts=" .. tostring(config.hide_parts) ..
        " carrier=" .. tostring(config.carrier_mesh_name))

    local ok = pcall(function()
        NotifyOnNewObject("/Script/Engine.SkeletalMeshComponent", on_new_object)
        -- some of the hero's accessories are static meshes
        NotifyOnNewObject("/Script/Engine.StaticMeshComponent", on_new_object)
    end)
    trace("NotifyOnNewObject ok=" .. tostring(ok))

    if type(RegisterKeyBind) == "function" and Key then
        if Key[config.toggle_key] then
            pcall(RegisterKeyBind, Key[config.toggle_key], toggle_ours)
        end
        if Key[config.diagnostics_key] then
            pcall(RegisterKeyBind, Key[config.diagnostics_key], function()
                if type(ExecuteInGameThread) == "function" then
                    ExecuteInGameThread(dump_all)
                else
                    dump_all()
                end
            end)
        end
    end

    if type(LoopInGameThreadWithDelay) == "function" then
        -- one Lua error inside the callback would otherwise stop the loop for good (that is what
        -- silently disabled every later scan), so the body is wrapped and errors are logged
        pcall(LoopInGameThreadWithDelay, math.floor(config.rescan_interval * 1000), function()
            local ok, err = pcall(scan)
            if not ok then trace("scan error: " .. tostring(err)) end
        end)
        trace("periodic loop registered")
    end
end

boot()
