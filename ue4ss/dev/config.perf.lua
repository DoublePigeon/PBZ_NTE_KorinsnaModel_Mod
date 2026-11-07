-- Measurement overlay for the KorinsnaRetarget mod. `tools/install_lua.ps1 -Profile perf` installs it as
-- `config.dev.lua`, which main.lua merges over config.lua.
--
-- Why this exists: a freeze has to be measured with the mod behaving exactly like release. The dev
-- profile writes a line for many components and runs its probes on a fast cadence, so using it to time a
-- stall measures the logger. This overlay therefore keeps release behaviour (log_level = 1) and only
-- turns on the scan timer, which writes its `profile:` lines at level 1 so they survive a silent log.
--
-- Read the output like this:
--   profile: scan took 23.4ms (...)          -> this mod's own work was slow (look at drained/queue)
--   profile: 640ms stall before tick 813 ... -> the game thread was busy elsewhere; our last scan was fine
return {
    log_level = 1,

    -- the only thing this profile adds
    profile_scans = true,

    -- report a scan that takes longer than this, and a gap that is this many times the scan interval
    profile_slow_ms = 10,
    profile_gap_factor = 1.6,
}
