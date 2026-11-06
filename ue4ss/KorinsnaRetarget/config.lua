-- KorinsnaRetarget configuration.
--
-- Paths are object paths inside the mod's container (the container mounts as ../../../ProjectPBZ/,
-- so /Game/... resolves to ProjectPBZ/Content/...).
return {
    -- the game's own body component: the real game mesh with the real game animation. It keeps being
    -- animated (and refreshed) so its pose can be retargeted from; it is only hidden visually, and
    -- hiding it must never clear its visibility flag (that stops the pose from ticking).
    source_mesh_names = { "Hun_Body_Simple" },

    -- the hero part asset that ships the Korinsna mesh (see ue/scripts/build_carrier_mesh.py).
    -- The game loads it, the engine runs the mesh's post-process blueprint (the retarget graph) on
    -- it, and the script only has to stop it from following CharacterMesh0's pose.
    carrier_mesh_name = "Hun_Head_New",
    component_name = "KorinsnaBody",

    -- loaded as a dependency of the carrier mesh, so a plain lookup by name finds it
    anim_class_path = "/Game/Korinsna/ABP_Korinsna_Retarget.ABP_Korinsna_Retarget_C",

    -- everything of the original outfit that must be hidden; weapons stay
        hide_prefixes = { "Hun_" },
        -- The outfit is removed at ASSET level (blank skeletal meshes + empty Chaos Cloth assets), the
        -- same way the reference 2B mod does it. Runtime hiding is only a debugging tool: it fights the
        -- game's wardrobe system, and clearing the body's visibility also stops its pose from
        -- refreshing unless the tick option is forced. With that forced, hiding the body is safe and
        -- costs nothing: the real mesh keeps its sockets, physics and animation.
        hide_body_render_pass = false,
        hide_source_visibility = true,
        hide_only_source = false,
        hide_all_hun_parts = false,
        keep_visible = {
            "Weapon", "Blade", "Knife", "Scabbard", "Chakram", "Spear", "Sword", "HeiMoShang",
        },
        hide_parts = false,
        disable_uro = false,
        force_anim_refresh = true,
        hide_scabbards = true,
        carrier_cast_shadow = false,
        -- on: held weapon actors are re-parented onto the matching hand bone, so the blade follows the
        -- hand that is actually on screen instead of the hidden original one
        attach_weapons = true,
        -- hilt distance from the hand bone in cm (the game uses 9.5, which is Hun's hand; ours puts
        -- the hilt outside the fist). 0 = keep the game's distance.
        grip_distance = { r = 6.0, l = 6.0 },
        -- a weapon that is put away is carried over to Korinsna's own spine (torso), not the pelvis:
        -- the hips sway far more, which made it look like the weapon rode her backside.
        -- Bip001-Spine corresponds to Hun's spine_03 in the retarget chain
        -- (pelvis->spine_05 maps onto Bip001-Pelvis->Bip001-Spine1).
        sheathed_anchor = "Bip001-Spine",
        sheathed_source_bone = "spine_03",
        sheathed_push_cm = 2.0,
        -- a weapon anchor is derived from the hand bone, so it is skipped while the pose is obviously
        -- broken (hands more than a metre apart = reference pose)
        anchor_max_gap_cm = 100.0,
        -- diagnostic: log each weapon's full attach chain whenever it changes. Expensive (walks every
        -- skeletal component and builds strings), so it is off unless a weapon bug is being chased.
        report_weapon_chain = false,
        -- Hun's own waist knife + scabbard: anchored to Korinsna's pelvis and pushed out along the
        -- back of the skirt by `back_item_push_cm` so they no longer clip through it
        back_items = { "Hun_Knife", "Hun_Knife_Scabbard" },
        -- tuned on screen: 2 cm puts the hilt on the outside of the skirt without floating
        back_item_push_cm = 2.0,
        quiet_blank_parts = true,
        -- cutscene / preview copies of the hero render the one original mesh that is not replaced at
        -- asset level (the body, which is the retarget source), so the original outfit comes back
        -- with them. Hidden here; the young hero uses other meshes and keeps his outfit.
        hide_copy_bodies = true,
        hide_copy_body_meshes = { "Hun_Body_Simple" },
        -- Chaos Cloth garments (robe, cape, hair and the wardrobe's damaged variants) are components of
        -- their own, separate from the skeletal parts, so they are hidden separately
        hide_hero_cloth = true,
        -- everything else a copy owns (accessories, static-mesh cards, grooms) is hidden too
        hide_copy_outfit = true,
        -- the sweep that finds those components walks the whole level (five component classes), so it
        -- runs rarely: every `copy_rescan_scans`, the moment a hero-owned component spawns (the object
        -- listener sets `copy_dirty`), or when a cached one went away - never more often than
        -- `copy_rescan_min_scans`, because a cutscene spawns components continuously.
        copy_rescan_scans = 60,
        copy_rescan_min_scans = 4,
        -- re-arm the retarget when the game points the part component back at CharacterMesh0 (the
        -- model falling back to its reference pose after an interactive animation). See watch_pose():
        -- the leader pose pointer is read directly, so this reacts on the next scan.
        pose_watchdog = true,
        -- The bone-motion window is the slow backstop (it needs a window to be sure); the leader-pose
        -- read normally fires first. Kept on: 4 bone reads per scan, and it is the only thing that
        -- catches a stall neither of the two state checks explains.
        pose_bone_fallback = true,
        -- Each scan is classified as "stalled" when the game's body moved more than
        -- pose_step_move_cm while Korinsna moved less than pose_step_stuck_cm; the verdict is taken
        -- over a sliding window (pose_slip_window) because one bad read-out can otherwise look like
        -- motion and hide a stall. Only used when pose_bone_fallback is on.
        pose_step_move_cm = 0.5,
        pose_step_stuck_cm = 0.3,
        pose_slip_window = 12,
        pose_stuck_marks = 4,
        -- A single scan where the game's body moved more than this while ours did not move at all is a
        -- stall straight away (measured 98.8 cm in one scan the moment the pose was lost). Set it very
        -- high to disable the fast path and rely on the window above only.
        pose_big_jump_cm = 20.0,
        -- minimum scans between two rebuilds of the retarget graph (0.5 s each)
        pose_heal_cooldown = 6,
        -- scans to wait after a heal before the held weapons are anchored again (the hand bone has to
        -- be on a live pose first, or the wrong offset gets baked into the weapon)
        pose_weapon_wait = 2,
        -- diagnostic: print the watchdog counters every 5 scans
        report_pose_window = false,
        -- diagnostic: dump the KawaiiPhysics anim nodes the engine built for our graph, once per body
        -- (field names only; the game ships its own KawaiiPhysics fork, so this proves what survived
        -- the load). See docs/TECHNICAL-GUIDE.md 搂9.
        report_physics_nodes = false,
        report_physics_frames = false,
        live_physics_keys = false,
        -- diagnostic: pelvis/foot heights of the game's body vs ours (used to find the floating
        -- sit/lie bug, see §8.9). Turn on to measure, keep off: it logs a line per second.
        report_ground_every = 0,
        -- diagnostic: log which material instance each slot renders with, once per hero
        report_materials = false,
        -- the game's damage system replaces the *head part's* first material slot
        -- (Hun_Status/MI_ZeroHun_Head_Injured*); our mesh ships as that head part, so the dress slot
        -- must be put back or the dress renders with a pale skin shader
        material_guard = {
            [0] = "/Game/PBZContent/Characters/Hero/Hun_New_V2b/Material/MI_ZeroHun_Cloth_04_b.MI_ZeroHun_Cloth_04_b",
        },
        report_weapon_attachment = false,
        -- diagnostic run: measure the hand gap and each weapon's attach chain
        report_weapon_geometry = false,
        force_opaque = false,
        dump_census = false,

    -- extra yaw applied on top of the measured alignment, for fine tuning without a rebuild
    rotation_offset_yaw = 0.0,

    -- 0 = nothing written, 1 = problems only (release: a healthy session writes no log at all),
    -- 2 = everything (dev). Each line is a file write plus a console print; a chatty log is real work
    -- during a cutscene, which is why release keeps this at 1.
    log_level = 1,

    -- Scans between two level-wide searches for the components the per-scan work acts on (weapons,
    -- scabbards, Hun's waist knife). ONE search per scan replaces the three that the three jobs used to
    -- run separately; the hits are cached as names and the work then runs over those.
    target_rescan_scans = 1,
    -- scans between two attempts to find the hero while he is still unknown, and between two audit
    -- look-ups once he is known (the object listener normally makes both unnecessary)
    discover_every = 4,
    discover_audit_scans = 60,
    -- re-assert the blank-part shadow flags every N scans (the game's wardrobe pass turns parts back on)
    quiet_parts_every = 2,

    -- log a bone position of both rigs every N scans (0 disables): tells "frozen pose" apart from
    -- "wrong pose" without needing another build. Component space, so walking does not count as
    -- animation. Diagnostic: off in release.
    report_motion_every = 0,

    toggle_key = "F9",
    diagnostics_key = "F11",
    rescan_interval = 0.5,

    -- diagnostic switch: only report what is loaded, never change anything
    probe_only = false,
}
