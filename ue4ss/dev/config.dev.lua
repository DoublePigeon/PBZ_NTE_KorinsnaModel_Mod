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

    -- the level-wide searches are cheap enough to run often while developing, and they fill the caches
    -- immediately instead of after a few seconds
    target_rescan_scans = 1,
    copy_rescan_scans = 2,
    discover_every = 1,
}
