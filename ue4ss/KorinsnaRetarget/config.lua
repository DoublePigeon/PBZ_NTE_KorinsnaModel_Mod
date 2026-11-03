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
        -- the sweep that finds those components walks the whole level, so it runs rarely: event driven
        -- when a new hero copy component appears, plus this many scans as a safety net, and never more
        -- often than copy_rescan_min_scans (a cutscene spawns components continuously)
        copy_rescan_scans = 60,
        copy_rescan_min_scans = 4,
        -- re-arm the retarget when the game re-applies the leader pose (model stuck in its reference
        -- pose after an interactive animation / cutscene)
        pose_watchdog = true,
        -- Each scan is classified as "stalled" when the game's body moved more than
        -- pose_step_move_cm while Korinsna moved less than pose_step_stuck_cm. The verdict is taken
        -- over a sliding window (pose_slip_window) because one bad read-out can otherwise look like
        -- motion and hide a stall.
        pose_step_move_cm = 0.5,
        pose_step_stuck_cm = 0.3,
        pose_slip_window = 12,
        pose_stuck_marks = 4,
        -- minimum scans between two heals (0.5 s each), so an unrelated frozen pose cannot turn this
        -- into a re-init loop
        pose_heal_cooldown = 6,
        -- diagnostic: print the watchdog counters every 5 scans
        report_pose_window = false,
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

    -- log a bone position of both rigs every N scans (0 disables): tells "frozen pose" apart from
    -- "wrong pose" without needing another build. Component space, so walking does not count as
    -- animation.
    report_motion_every = 2,

    toggle_key = "F9",
    diagnostics_key = "F11",
    rescan_interval = 0.5,

    -- diagnostic switch: only report what is loaded, never change anything
    probe_only = false,
}
