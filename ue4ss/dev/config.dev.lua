-- Dev overlay for the KorinsnaRetarget mod. `tools/install_lua.ps1 -Profile dev` copies it into the mod
-- folder as `config.dev.lua`, and main.lua merges it over `config.lua`.
--
-- Only the log and the diagnostics differ. The behaviour is exactly the release behaviour - that is the
-- point of having one code base: anything seen in the dev profile is also what the game does in release.
return {
    -- 2 = every line (file write + console print). Release is 1: problems only.
    log_level = 2,

    -- the bone-motion watchdog window: the counters tell whether the leader-pose check ever failed and
    -- the slow path had to take over
    report_pose_window = true,
    report_motion_every = 2,

    -- per-weapon attach chains, the one-off censuses, and the material slot dump
    report_weapon_chain = true,
    report_weapon_attachment = true,
    report_weapon_geometry = true,
    report_materials = true,

    -- the KawaiiPhysics field layout the game's own engine created for our graph: the plug-in fork the
    -- game ships differs from the version the nodes were authored with, and a dropped property means a
    -- node that simulates nothing
    report_physics_nodes = true,

    -- per-frame recorder on F10 (see main.lua): press it, then hammer WASD for 5 seconds
    report_physics_frames = true,

    -- F6 = rigid (physics off), F7 = baked values: bisect without a cook
    live_physics_keys = true,

    -- the level-wide searches are cheap enough to run often while developing, and they fill the caches
    -- immediately instead of after a few seconds
    target_rescan_scans = 20,
    copy_rescan_scans = 2,
    discover_every = 1,

    -- The attach-chain log walks the whole UObject array on every scan, which is a hitch of its own; it
    -- is off by default and turned on only while a weapon-attachment question is being investigated.
    report_weapon_chain = false,

    -- times each scan and reports a stall (the game thread was busy before our callback ran) separately
    -- from a slow scan, because those two have completely different causes
    profile_scans = true,

    -- which classes actually reach the object listener, and whether owner/mesh are readable at that
    -- moment. This decides whether the hiding caches can be filled from events instead of the
    -- level-wide searches (a class the listener never reports cannot be found that way).
    report_listener_classes = true,
}
