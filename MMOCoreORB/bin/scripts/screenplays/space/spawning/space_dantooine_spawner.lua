SpaceDantooineSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceDantooineSpawner",

	spaceZone = "space_dantooine",

	shipSpawns = {
		{"corellia_imperial_tier4_inspect2", -3934, -6968, 2011, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 50, 120, 1,
			{"velocity_merc_group_leader_tier5"}
		},
		{"pirate_beacon_defense", -3807, -6665, 1966, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 60, 320, 3,
			{"velocity_smuggler_tier3"}
		},
		{"rebel_base_defense_2", -3800, 6192, -4469, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 20, 50, 300, 6,
			{"reb_xwing_tier3", "reb_xwing_tier3_dantooine", "reb_ywing_tier3", "reb_ywing_tier3_dantooine", "reb_z95_tier2", "reb_z95_tier3", "reb_xwing_tier2", "reb_awing_tier2", "reb_awing_tier3", "reb_bwing_tier3", "reb_ywing_tier2"}
		},
		{"naboo_rebel_tier3_inspect_target", -3838, 5840, -3806, SHIP_AI_RANDOM_PATROL, 10, 30, 10, 20, 50, 120, 1,
			{"naboo_tier3_imperial_spy"}
		},
		{"rebel_base_defense_1", -2871, 5027, -3071, SHIP_AI_FIXED_PATROL, 180, 300, 10, 20, 6,
			5, {"rebel_base_defense_1_00", "rebel_base_defense_1_01", "rebel_base_defense_1_02", "rebel_base_defense_1_03", "rebel_base_defense_1_04", "rebel_base_defense_1_05", "rebel_base_defense_1_06", "rebel_base_defense_1_07", "rebel_base_defense_1_08", "rebel_base_defense_1_09", "rebel_base_defense_1_10", "rebel_base_defense_1_11", "rebel_base_defense_1_12", "rebel_base_defense_1_13", "rebel_base_defense_1_14", "rebel_base_defense_1_15"},
			{"reb_xwing_tier2", "reb_xwing_tier3_dantooine", "reb_ywing_tier2", "reb_ywing_tier3_dantooine", "reb_awing_tier2", "reb_bwing_tier2", "reb_z95_tier2"}
		},
		{"warrens_guards_1", -5921, 1303, -4991, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 370, 3,
			{"warrens_fighter"}
		},
		{"vortex_mission_4_shuttle", -3273, -3335, -3027, SHIP_AI_FIXED_PATROL, 10, 30, 10, 100, 1,
			5, {"vortex_mission_4_shuttle_00", "vortex_mission_4_shuttle_01", "vortex_mission_4_shuttle_02", "vortex_mission_4_shuttle_03", "vortex_mission_4_shuttle_04", "vortex_mission_4_shuttle_05", "vortex_mission_4_shuttle_06", "vortex_mission_4_shuttle_07", "vortex_mission_4_shuttle_08", "vortex_mission_4_shuttle_09", "vortex_mission_4_shuttle_10", "vortex_mission_4_shuttle_11", "vortex_mission_4_shuttle_12"},
			{"squad_vortex_mission_4"}
		},
		{"imperial_beacon_defense_3", -3592, -993, -3500, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 60, 320, 3,
			{"imp_tie_bomber_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3_dantooine", "imp_tie_interceptor_tier3_dantooine", "imp_tie_advanced_tier2", "imp_tie_aggressor_tier2", "imp_tie_interceptor_tier2", "imp_tie_oppressor_tier2"}
		},
		{"guardians_static_point_1", -5781, 1586, 5639, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 350, 3,
			{"anthropology_guardian", "junk_dealer_guardian"}
		},
		{"imperial_guard_1", -1894, 2834, 4783, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 30, 150, 500, 3,
			{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3_dantooine", "imp_tie_interceptor_tier3_dantooine"}
		},
		{"imperial_patrol_1", -2249, 3181, 6554, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 6,
			5, {"imperial_patrol_1_00", "imperial_patrol_1_01", "imperial_patrol_1_02", "imperial_patrol_1_03", "imperial_patrol_1_04", "imperial_patrol_1_05", "imperial_patrol_1_06", "imperial_patrol_1_07", "imperial_patrol_1_08", "imperial_patrol_1_09", "imperial_patrol_1_10", "imperial_patrol_1_11", "imperial_patrol_1_12", "imperial_patrol_1_13", "imperial_patrol_1_14", "imperial_patrol_1_15", "imperial_patrol_1_16", "imperial_patrol_1_17", "imperial_patrol_1_18"},
			{"imp_tie_fighter_tier2", "imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3_dantooine", "imp_tie_aggressor_tier2", "imp_tie_advanced_tier2", "imp_tie_bomber_tier2", "imp_tie_interceptor_tier2", "imp_tie_oppressor_tier2"}
		},
		{"naboo_rebel_tier3_pirate_leader_inspect", -711, -5678, 1064, SHIP_AI_FIXED_PATROL, 10, 20, 10, 150, 1,
			5, {"naboo_rebel_tier3_pirate_leader_inspect_00", "naboo_rebel_tier3_pirate_leader_inspect_01", "naboo_rebel_tier3_pirate_leader_inspect_02", "naboo_rebel_tier3_pirate_leader_inspect_03"},
			{"blacklight_pirate_fighter_quest"}
		},
		{"naboo_rebel_tier3_pirate_inspect", -733, -5435, 1328, SHIP_AI_FIXED_PATROL, 10, 30, 20, 50, 4,
			5, {"naboo_rebel_tier3_pirate_inspect_00", "naboo_rebel_tier3_pirate_inspect_01", "naboo_rebel_tier3_pirate_inspect_02", "naboo_rebel_tier3_pirate_inspect_03", "naboo_rebel_tier3_pirate_inspect_04", "naboo_rebel_tier3_pirate_inspect_05", "naboo_rebel_tier3_pirate_inspect_06", "naboo_rebel_tier3_pirate_inspect_07", "naboo_rebel_tier3_pirate_inspect_08", "naboo_rebel_tier3_pirate_inspect_09", "naboo_rebel_tier3_pirate_inspect_10", "naboo_rebel_tier3_pirate_inspect_11", "naboo_rebel_tier3_pirate_inspect_12", "naboo_rebel_tier3_pirate_inspect_13", "naboo_rebel_tier3_pirate_inspect_14", "naboo_rebel_tier3_pirate_inspect_15", "naboo_rebel_tier3_pirate_inspect_16", "naboo_rebel_tier3_pirate_inspect_17", "naboo_rebel_tier3_pirate_inspect_18", "naboo_rebel_tier3_pirate_inspect_19", "naboo_rebel_tier3_pirate_inspect_20", "naboo_rebel_tier3_pirate_inspect_21", "naboo_rebel_tier3_pirate_inspect_22", "naboo_rebel_tier3_pirate_inspect_23", "naboo_rebel_tier3_pirate_inspect_24", "naboo_rebel_tier3_pirate_inspect_25", "naboo_rebel_tier3_pirate_inspect_26", "naboo_rebel_tier3_pirate_inspect_27", "naboo_rebel_tier3_pirate_inspect_28", "naboo_rebel_tier3_pirate_inspect_29", "naboo_rebel_tier3_pirate_inspect_30", "naboo_rebel_tier3_pirate_inspect_31", "naboo_rebel_tier3_pirate_inspect_32", "naboo_rebel_tier3_pirate_inspect_33", "naboo_rebel_tier3_pirate_inspect_34", "naboo_rebel_tier3_pirate_inspect_35", "naboo_rebel_tier3_pirate_inspect_36", "naboo_rebel_tier3_pirate_inspect_37", "naboo_rebel_tier3_pirate_inspect_38", "naboo_rebel_tier3_pirate_inspect_39", "naboo_rebel_tier3_pirate_inspect_40", "naboo_rebel_tier3_pirate_inspect_41", "naboo_rebel_tier3_pirate_inspect_42", "naboo_rebel_tier3_pirate_inspect_43"},
			{"blacklight_assassin_tier3", "blacklight_bomber_tier3", "blacklight_fighter_tier3", "blacklight_leader_tier3"}
		},
		{"blacksun_harrassment_2", 344, -2611, -1632, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 360, 4,
			{"blacksun_marauder_tier3", "blacksun_vehement_tier3", "blacksun_bomber_ace_tier3_dantooine", "blacksun_bomber_ace_tier3_dantooine", "blacksun_bomber_ace_tier3_dantooine"}
		},
		{"force_assassins_1", 3310, -4356, -1257, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 390, 3,
			{"force_assassin", "force_assassin_tier3_dantooine", "force_assassin_tier3_dantooine", "force_assassin_tier3_dantooine"}
		},
		{"force_assassins_attack", 2778, -4811, -1751, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 4,
			5, {"force_assassins_attack_00", "force_assassins_attack_01", "force_assassins_attack_02", "force_assassins_attack_03", "force_assassins_attack_04", "force_assassins_attack_05", "force_assassins_attack_06", "force_assassins_attack_07", "force_assassins_attack_08", "force_assassins_attack_09", "force_assassins_attack_10", "force_assassins_attack_11", "force_assassins_attack_12", "force_assassins_attack_13", "force_assassins_attack_14", "force_assassins_attack_15", "force_assassins_attack_16", "force_assassins_attack_17", "force_assassins_attack_18", "force_assassins_attack_19", "force_assassins_attack_20", "force_assassins_attack_21", "force_assassins_attack_22", "force_assassins_attack_23", "force_assassins_attack_24", "force_assassins_attack_25", "force_assassins_attack_26", "force_assassins_attack_27", "force_assassins_attack_28", "force_assassins_attack_29", "force_assassins_attack_30", "force_assassins_attack_31", "force_assassins_attack_32", "force_assassins_attack_33", "force_assassins_attack_34", "force_assassins_attack_35", "force_assassins_attack_36", "force_assassins_attack_37", "force_assassins_attack_38", "force_assassins_attack_39", "force_assassins_attack_40", "force_assassins_attack_41", "force_assassins_attack_42", "force_assassins_attack_43", "force_assassins_attack_44", "force_assassins_attack_45", "force_assassins_attack_46", "force_assassins_attack_47", "force_assassins_attack_48"},
			{"force_assassin", "force_assassin", "force_assassin", "force_assassin", "force_bomber_boss", "force_assassin_tier3_dantooine", "force_assassin_tier3_dantooine", "force_assassin_tier3_dantooine", "force_assassin_tier3_dantooine", "force_assassin_tier3_dantooine", "force_assassin_tier3_dantooine"}
		},
		{"imperial_generator_defense_d", 3140, 4326, -7336, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 60, 320, 6,
			{"imp_tie_bomber_tier2", "imp_tie_bomber_tier3", "imp_tie_fighter_tier2", "imp_tie_fighter_tier3", "imp_tie_fighter_tier3_dantooine", "imp_tie_fighter_tier3_dantooine", "imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3_dantooine", "imp_tie_aggressor_tier2", "imp_tie_advanced_tier2", "imp_tie_advanced_tier4", "imp_tie_oppressor_tier2", "imp_tie_oppressor_tier3", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier3"}
		},
		{"slave_trader_out_2", 2299, -1583, 6678, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 3,
			5, {"slave_trader_out_2_00", "slave_trader_out_2_01", "slave_trader_out_2_02", "slave_trader_out_2_03", "slave_trader_out_2_04", "slave_trader_out_2_05", "slave_trader_out_2_06", "slave_trader_out_2_07", "slave_trader_out_2_08", "slave_trader_out_2_09", "slave_trader_out_2_10", "slave_trader_out_2_11", "slave_trader_out_2_12"},
			{"slave_trader_trader_tier3", "slave_trader_trader_tier3_dantooine", "slave_trader_trader_tier3_dantooine"}
		},
		{"slave_trader_out_1", 4999, -1574, 6617, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 3,
			5, {"slave_trader_out_1_00", "slave_trader_out_1_01", "slave_trader_out_1_02", "slave_trader_out_1_03", "slave_trader_out_1_04", "slave_trader_out_1_05", "slave_trader_out_1_06", "slave_trader_out_1_07", "slave_trader_out_1_08"},
			{"slave_trader_trader_tier3", "slave_trader_trader_tier3_dantooine", "slave_trader_trader_tier3_dantooine"}
		},
		{"imperial_inquisition_1", 5110, 5511, 754, SHIP_AI_FIXED_PATROL, 180, 300, 10, 20, 6,
			5, {"imperial_inquisition_1_00", "imperial_inquisition_1_01", "imperial_inquisition_1_02", "imperial_inquisition_1_03", "imperial_inquisition_1_04", "imperial_inquisition_1_05", "imperial_inquisition_1_06", "imperial_inquisition_1_07", "imperial_inquisition_1_08", "imperial_inquisition_1_09", "imperial_inquisition_1_10", "imperial_inquisition_1_11", "imperial_inquisition_1_12", "imperial_inquisition_1_13", "imperial_inquisition_1_14", "imperial_inquisition_1_15", "imperial_inquisition_1_16", "imperial_inquisition_1_17", "imperial_inquisition_1_18", "imperial_inquisition_1_19", "imperial_inquisition_1_20", "imperial_inquisition_1_21", "imperial_inquisition_1_22"},
			{"imp_tie_advanced_tier3", "imp_tie_fighter_tier3", "imp_tie_fighter_tier3_dantooine", "imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3_dantooine", "imp_tie_aggressor_tier3", "imp_tie_bomber_tier3"}
		},
		{"force_assassins_2", 4011, -3369, -2310, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 390, 3,
			{"force_assassin", "force_assassin_tier3_dantooine", "force_assassin_tier3_dantooine"}
		},
		{"blacksun_mining_harrassment_1", 4272, -1287, -1655, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 4,
			{"blacksun_aggressor_tier3", "blacksun_fighter_s02_tier3", "blacksun_fighter_s02_tier3_dantooine", "blacksun_fighter_s02_tier3_dantooine", "blacksun_fighter_s02_tier3_dantooine", "blacksun_fighter_s02_tier3_dantooine", "blacksun_gunship_tier3"}
		},
		{"corellia_imperial_tier4_generator", 6330, -955, -6802, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 60, 320, 3,
			{"tieadvanced_ace_tier4", "tieadvanced_ace_tier4", "tieadvanced_ace_tier4", "tieinterceptor_ace_tier4"}
		},
		{"tatooine_privateer_tier4_leg_3_inspect", 7456, -1625, 1458, SHIP_AI_RANDOM_PATROL, 180, 800, 40, 80, 80, 160, 3,
			{"valarian_bomber_tier3", "valarian_gunship_tier3", "valarian_gunship_inspect_tier4"}
		},
		{"anthro_astroid_route_1", -6804, -5672, 4660, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 4,
			5, {"anthro_astroid_route_1_00", "anthro_astroid_route_1_01", "anthro_astroid_route_1_02", "anthro_astroid_route_1_03", "anthro_astroid_route_1_04", "anthro_astroid_route_1_05", "anthro_astroid_route_1_06", "anthro_astroid_route_1_07", "anthro_astroid_route_1_08", "anthro_astroid_route_1_09", "anthro_astroid_route_1_10", "anthro_astroid_route_1_11", "anthro_astroid_route_1_12", "anthro_astroid_route_1_13", "anthro_astroid_route_1_14", "anthro_astroid_route_1_15", "anthro_astroid_route_1_16", "anthro_astroid_route_1_17", "anthro_astroid_route_1_18", "anthro_astroid_route_1_19", "anthro_astroid_route_1_20", "anthro_astroid_route_1_21", "anthro_astroid_route_1_22", "anthro_astroid_route_1_23", "anthro_astroid_route_1_24", "anthro_astroid_route_1_25", "anthro_astroid_route_1_26"},
			{"anthropology_collector", "anthropology_collector", "anthropology_guardian", "anthropology_scout", "anthropology_professor_boss", "anthropology_guardian", "anthropology_guardian", "anthropology_guardian", "anthropology_collector", "anthropology_collector", "anthropology_collector", "anthropology_collector", "anthropology_guardian", "anthropology_guardian", "anthropology_collector", "anthropology_collector"}
		},
		{"anthro_guardian_patrol_1", -6836, -3630, 3612, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 5,
			5, {"anthro_guardian_patrol_1_00", "anthro_guardian_patrol_1_01", "anthro_guardian_patrol_1_02", "anthro_guardian_patrol_1_03", "anthro_guardian_patrol_1_04", "anthro_guardian_patrol_1_05", "anthro_guardian_patrol_1_06", "anthro_guardian_patrol_1_07", "anthro_guardian_patrol_1_08", "anthro_guardian_patrol_1_09", "anthro_guardian_patrol_1_10", "anthro_guardian_patrol_1_11", "anthro_guardian_patrol_1_12", "anthro_guardian_patrol_1_13", "anthro_guardian_patrol_1_14", "anthro_guardian_patrol_1_15", "anthro_guardian_patrol_1_16", "anthro_guardian_patrol_1_17", "anthro_guardian_patrol_1_18", "anthro_guardian_patrol_1_19", "anthro_guardian_patrol_1_20", "anthro_guardian_patrol_1_21", "anthro_guardian_patrol_1_22", "anthro_guardian_patrol_1_23", "anthro_guardian_patrol_1_24", "anthro_guardian_patrol_1_25", "anthro_guardian_patrol_1_26", "anthro_guardian_patrol_1_27", "anthro_guardian_patrol_1_28", "anthro_guardian_patrol_1_29", "anthro_guardian_patrol_1_30", "anthro_guardian_patrol_1_31", "anthro_guardian_patrol_1_32", "anthro_guardian_patrol_1_33", "anthro_guardian_patrol_1_34", "anthro_guardian_patrol_1_35", "anthro_guardian_patrol_1_36", "anthro_guardian_patrol_1_37", "anthro_guardian_patrol_1_38", "anthro_guardian_patrol_1_39", "anthro_guardian_patrol_1_40", "anthro_guardian_patrol_1_41", "anthro_guardian_patrol_1_42", "anthro_guardian_patrol_1_43", "anthro_guardian_patrol_1_44"},
			{"anthropology_guardian", "anthropology_scout", "anthropology_guardian"}
		},
		{"anthro_guardians_1", -5794, -3929, 4621, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 300, 4,
			{"anthropology_guardian"}
		},
		{"antho_diplomat_route_1", -6321, -4294, 4733, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 4,
			5, {"antho_diplomat_route_1_00", "antho_diplomat_route_1_01", "antho_diplomat_route_1_02", "antho_diplomat_route_1_03", "antho_diplomat_route_1_04", "antho_diplomat_route_1_05", "antho_diplomat_route_1_06", "antho_diplomat_route_1_07", "antho_diplomat_route_1_08", "antho_diplomat_route_1_09", "antho_diplomat_route_1_10", "antho_diplomat_route_1_11", "antho_diplomat_route_1_12", "antho_diplomat_route_1_13", "antho_diplomat_route_1_14", "antho_diplomat_route_1_15", "antho_diplomat_route_1_16", "antho_diplomat_route_1_17", "antho_diplomat_route_1_18", "antho_diplomat_route_1_19", "antho_diplomat_route_1_20", "antho_diplomat_route_1_21", "antho_diplomat_route_1_22", "antho_diplomat_route_1_23", "antho_diplomat_route_1_24"},
			{"anthropology_diplomat", "anthropology_guardian", "anthropology_scout", "anthropology_guardian"}
		},
		{"collector_hyperspace_patrol", -5783, -5198, 3690, SHIP_AI_FIXED_PATROL, 180, 300, 40, 60, 3,
			5, {"collector_hyperspace_patrol_00", "collector_hyperspace_patrol_01", "collector_hyperspace_patrol_02", "collector_hyperspace_patrol_03", "collector_hyperspace_patrol_04", "collector_hyperspace_patrol_05", "collector_hyperspace_patrol_06", "collector_hyperspace_patrol_07", "collector_hyperspace_patrol_08", "collector_hyperspace_patrol_09", "collector_hyperspace_patrol_10", "collector_hyperspace_patrol_11", "collector_hyperspace_patrol_12", "collector_hyperspace_patrol_13", "collector_hyperspace_patrol_14", "collector_hyperspace_patrol_15", "collector_hyperspace_patrol_16", "collector_hyperspace_patrol_17", "collector_hyperspace_patrol_18", "collector_hyperspace_patrol_19", "collector_hyperspace_patrol_20", "collector_hyperspace_patrol_21"},
			{"anthropology_collector"}
		},
		{"rebel_generator_assassin_1", 6804, 4530, 1057, SHIP_AI_RANDOM_PATROL, 60, 420, 10, 30, 250, 520, 6,
			{"reb_awing_tier2", "reb_awing_tier3", "reb_bwing_tier2", "reb_bwing_tier3", "reb_xwing_tier2", "reb_xwing_tier3_dantooine", "reb_ywing_tier2", "reb_ywing_tier3", "reb_z95_tier2", "reb_z95_tier3"}
		},
		{"random_valarian_filler_2", 4366, 5653, 2519, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 390, 2,
			{"valarian_bomber_tier3"}
		},
		{"dantooine_rebel_spawner_1", 6089, 6831, 2528, SHIP_AI_FIXED_PATROL, 180, 300, 10, 20, 6,
			5, {"dantooine_rebel_spawner_1_00", "dantooine_rebel_spawner_1_01", "dantooine_rebel_spawner_1_02", "dantooine_rebel_spawner_1_03", "dantooine_rebel_spawner_1_04", "dantooine_rebel_spawner_1_05", "dantooine_rebel_spawner_1_06", "dantooine_rebel_spawner_1_07", "dantooine_rebel_spawner_1_08", "dantooine_rebel_spawner_1_09", "dantooine_rebel_spawner_1_10", "dantooine_rebel_spawner_1_11", "dantooine_rebel_spawner_1_12", "dantooine_rebel_spawner_1_13", "dantooine_rebel_spawner_1_14", "dantooine_rebel_spawner_1_15", "dantooine_rebel_spawner_1_16", "dantooine_rebel_spawner_1_17", "dantooine_rebel_spawner_1_18", "dantooine_rebel_spawner_1_19", "dantooine_rebel_spawner_1_20"},
			{"reb_awing_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_bwing_tier3", "reb_z95_tier3"}
		},
		{"valarian_guards_2", 7156, 5643, 5031, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 90, 380, 3,
			{"valarian_bomber_tier3", "valarian_gunship_tier3"}
		},
		{"valarian_guards_1", 6830, 6029, 3363, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 360, 3,
			{"valarian_bomber_tier2", "valarian_gunship_tier3"}
		},
		{"valarian_harrass_1", 7429, 5683, 3801, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 4,
			5, {"valarian_harrass_1_00", "valarian_harrass_1_01", "valarian_harrass_1_02", "valarian_harrass_1_03", "valarian_harrass_1_04", "valarian_harrass_1_05", "valarian_harrass_1_06", "valarian_harrass_1_07", "valarian_harrass_1_08", "valarian_harrass_1_09", "valarian_harrass_1_10", "valarian_harrass_1_11", "valarian_harrass_1_12", "valarian_harrass_1_13", "valarian_harrass_1_14", "valarian_harrass_1_15", "valarian_harrass_1_16", "valarian_harrass_1_17", "valarian_harrass_1_18", "valarian_harrass_1_19", "valarian_harrass_1_20", "valarian_harrass_1_21", "valarian_harrass_1_22", "valarian_harrass_1_23", "valarian_harrass_1_24", "valarian_harrass_1_25", "valarian_harrass_1_26", "valarian_harrass_1_27", "valarian_harrass_1_28", "valarian_harrass_1_29", "valarian_harrass_1_30", "valarian_harrass_1_31", "valarian_harrass_1_32", "valarian_harrass_1_33", "valarian_harrass_1_34", "valarian_harrass_1_35", "valarian_harrass_1_36", "valarian_harrass_1_37", "valarian_harrass_1_38", "valarian_harrass_1_39"},
			{"valarian_gunship_tier3", "valarian_bomber_tier3"}
		},
		{"random_valarian_filler_1", 7101, 5650, 3910, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 3,
			5, {"random_valarian_filler_1_00", "random_valarian_filler_1_01", "random_valarian_filler_1_02", "random_valarian_filler_1_03", "random_valarian_filler_1_04", "random_valarian_filler_1_05", "random_valarian_filler_1_06", "random_valarian_filler_1_07", "random_valarian_filler_1_08", "random_valarian_filler_1_09", "random_valarian_filler_1_10", "random_valarian_filler_1_11", "random_valarian_filler_1_12", "random_valarian_filler_1_13", "random_valarian_filler_1_14", "random_valarian_filler_1_15", "random_valarian_filler_1_16", "random_valarian_filler_1_17", "random_valarian_filler_1_18", "random_valarian_filler_1_19", "random_valarian_filler_1_20", "random_valarian_filler_1_21", "random_valarian_filler_1_22", "random_valarian_filler_1_23", "random_valarian_filler_1_24", "random_valarian_filler_1_25", "random_valarian_filler_1_26", "random_valarian_filler_1_27", "random_valarian_filler_1_28", "random_valarian_filler_1_29", "random_valarian_filler_1_30", "random_valarian_filler_1_31", "random_valarian_filler_1_32", "random_valarian_filler_1_33", "random_valarian_filler_1_34", "random_valarian_filler_1_35", "random_valarian_filler_1_36", "random_valarian_filler_1_37", "random_valarian_filler_1_38", "random_valarian_filler_1_39", "random_valarian_filler_1_40", "random_valarian_filler_1_41", "random_valarian_filler_1_42", "random_valarian_filler_1_43", "random_valarian_filler_1_44", "random_valarian_filler_1_45", "random_valarian_filler_1_46", "random_valarian_filler_1_47", "random_valarian_filler_1_48", "random_valarian_filler_1_49", "random_valarian_filler_1_50", "random_valarian_filler_1_51", "random_valarian_filler_1_52", "random_valarian_filler_1_53", "random_valarian_filler_1_54", "random_valarian_filler_1_55", "random_valarian_filler_1_56", "random_valarian_filler_1_57", "random_valarian_filler_1_58", "random_valarian_filler_1_59", "random_valarian_filler_1_60"},
			{"valarian_bomber_tier2", "valarian_fighter_boss", "valarian_bomber_tier2", "valarian_bomber_tier2", "valarian_bomber_tier2", "valarian_bomber_tier2", "valarian_bomber_tier2", "valarian_bomber_tier2", "valarian_bomber_tier2", "valarian_bomber_tier2"}
		},
		{"imperial_vs_valarian", -1930, 3142, 2653, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 4,
			5, {"imperial_vs_valarian_00", "imperial_vs_valarian_01", "imperial_vs_valarian_02", "imperial_vs_valarian_03", "imperial_vs_valarian_04", "imperial_vs_valarian_05", "imperial_vs_valarian_06", "imperial_vs_valarian_07", "imperial_vs_valarian_08", "imperial_vs_valarian_09", "imperial_vs_valarian_10", "imperial_vs_valarian_11", "imperial_vs_valarian_12", "imperial_vs_valarian_13", "imperial_vs_valarian_14", "imperial_vs_valarian_15", "imperial_vs_valarian_16", "imperial_vs_valarian_17", "imperial_vs_valarian_18", "imperial_vs_valarian_19", "imperial_vs_valarian_20", "imperial_vs_valarian_21", "imperial_vs_valarian_22", "imperial_vs_valarian_23", "imperial_vs_valarian_24", "imperial_vs_valarian_25", "imperial_vs_valarian_26", "imperial_vs_valarian_27", "imperial_vs_valarian_28"},
			{"imp_tie_bomber_tier3", "imp_tie_bomber_tier3_dantooine", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier3_dantooine", "imp_tie_oppressor_tier3"}
		},
		{"squad_imperial_destroyer", -2488, 3054, 2290, SHIP_AI_FIXED_PATROL, 10800, 14400, 10, 30, 1,
			5, {"squad_imperial_destroyer_00", "squad_imperial_destroyer_01", "squad_imperial_destroyer_02", "squad_imperial_destroyer_03", "squad_imperial_destroyer_04", "squad_imperial_destroyer_05", "squad_imperial_destroyer_06", "squad_imperial_destroyer_07", "squad_imperial_destroyer_08", "squad_imperial_destroyer_09", "squad_imperial_destroyer_10", "squad_imperial_destroyer_11", "squad_imperial_destroyer_12", "squad_imperial_destroyer_13", "squad_imperial_destroyer_14", "squad_imperial_destroyer_15", "squad_imperial_destroyer_16", "squad_imperial_destroyer_17", "squad_imperial_destroyer_18", "squad_imperial_destroyer_19", "squad_imperial_destroyer_20", "squad_imperial_destroyer_21", "squad_imperial_destroyer_22", "squad_imperial_destroyer_23", "squad_imperial_destroyer_24", "squad_imperial_destroyer_25", "squad_imperial_destroyer_26", "squad_imperial_destroyer_27", "squad_imperial_destroyer_28", "squad_imperial_destroyer_29", "squad_imperial_destroyer_30", "squad_imperial_destroyer_31", "squad_imperial_destroyer_32", "squad_imperial_destroyer_33", "squad_imperial_destroyer_34", "squad_imperial_destroyer_35", "squad_imperial_destroyer_36", "squad_imperial_destroyer_37", "squad_imperial_destroyer_38", "squad_imperial_destroyer_39", "squad_imperial_destroyer_40", "squad_imperial_destroyer_41", "squad_imperial_destroyer_42", "squad_imperial_destroyer_43", "squad_imperial_destroyer_44", "squad_imperial_destroyer_45", "squad_imperial_destroyer_46", "squad_imperial_destroyer_47", "squad_imperial_destroyer_48", "squad_imperial_destroyer_49", "squad_imperial_destroyer_50", "squad_imperial_destroyer_51", "squad_imperial_destroyer_52", "squad_imperial_destroyer_53", "squad_imperial_destroyer_54", "squad_imperial_destroyer_55", "squad_imperial_destroyer_56", "squad_imperial_destroyer_57", "squad_imperial_destroyer_58", "squad_imperial_destroyer_59", "squad_imperial_destroyer_60", "squad_imperial_destroyer_61", "squad_imperial_destroyer_62", "squad_imperial_destroyer_63", "squad_imperial_destroyer_64", "squad_imperial_destroyer_65", "squad_imperial_destroyer_66", "squad_imperial_destroyer_67"},
			{"squad_imperial_destroyer"}
		},
		{"imperial_debris_patrol", -2463, 3057, 2367, SHIP_AI_FIXED_PATROL, 180, 300, 10, 20, 7,
			5, {"imperial_debris_patrol_00", "imperial_debris_patrol_01", "imperial_debris_patrol_02", "imperial_debris_patrol_03", "imperial_debris_patrol_04", "imperial_debris_patrol_05", "imperial_debris_patrol_06", "imperial_debris_patrol_07", "imperial_debris_patrol_08", "imperial_debris_patrol_09", "imperial_debris_patrol_10", "imperial_debris_patrol_11", "imperial_debris_patrol_12", "imperial_debris_patrol_13", "imperial_debris_patrol_14", "imperial_debris_patrol_15", "imperial_debris_patrol_16", "imperial_debris_patrol_17", "imperial_debris_patrol_18", "imperial_debris_patrol_19", "imperial_debris_patrol_20", "imperial_debris_patrol_21", "imperial_debris_patrol_22", "imperial_debris_patrol_23", "imperial_debris_patrol_24", "imperial_debris_patrol_25", "imperial_debris_patrol_26", "imperial_debris_patrol_27", "imperial_debris_patrol_28", "imperial_debris_patrol_29", "imperial_debris_patrol_30", "imperial_debris_patrol_31", "imperial_debris_patrol_32", "imperial_debris_patrol_33", "imperial_debris_patrol_34", "imperial_debris_patrol_35", "imperial_debris_patrol_36", "imperial_debris_patrol_37", "imperial_debris_patrol_38", "imperial_debris_patrol_39", "imperial_debris_patrol_40", "imperial_debris_patrol_41", "imperial_debris_patrol_42", "imperial_debris_patrol_43", "imperial_debris_patrol_44", "imperial_debris_patrol_45", "imperial_debris_patrol_46", "imperial_debris_patrol_47", "imperial_debris_patrol_48", "imperial_debris_patrol_49", "imperial_debris_patrol_50", "imperial_debris_patrol_51", "imperial_debris_patrol_52", "imperial_debris_patrol_53", "imperial_debris_patrol_54", "imperial_debris_patrol_55", "imperial_debris_patrol_56", "imperial_debris_patrol_57", "imperial_debris_patrol_58", "imperial_debris_patrol_59", "imperial_debris_patrol_60", "imperial_debris_patrol_61", "imperial_debris_patrol_62", "imperial_debris_patrol_63", "imperial_debris_patrol_64", "imperial_debris_patrol_65", "imperial_debris_patrol_66", "imperial_debris_patrol_67", "imperial_debris_patrol_68"},
			{"imp_tie_bomber_tier3", "imp_tie_bomber_tier3_dantooine", "imp_tie_fighter_tier3", "imp_tie_fighter_tier3_dantooine", "imp_tie_oppressor_tier4", "imperial_lt_deathfire", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_oppressor_tier3", "imp_tie_interceptor_tier3"}
		},
		{"imperial_to_slavers_1", -2449, 2963, 2742, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 6,
			5, {"imperial_to_slavers_1_00", "imperial_to_slavers_1_01", "imperial_to_slavers_1_02", "imperial_to_slavers_1_03", "imperial_to_slavers_1_04", "imperial_to_slavers_1_05", "imperial_to_slavers_1_06", "imperial_to_slavers_1_07", "imperial_to_slavers_1_08", "imperial_to_slavers_1_09", "imperial_to_slavers_1_10", "imperial_to_slavers_1_11", "imperial_to_slavers_1_12", "imperial_to_slavers_1_13", "imperial_to_slavers_1_14", "imperial_to_slavers_1_15", "imperial_to_slavers_1_16", "imperial_to_slavers_1_17", "imperial_to_slavers_1_18", "imperial_to_slavers_1_19", "imperial_to_slavers_1_20", "imperial_to_slavers_1_21", "imperial_to_slavers_1_22", "imperial_to_slavers_1_23", "imperial_to_slavers_1_24", "imperial_to_slavers_1_25", "imperial_to_slavers_1_26", "imperial_to_slavers_1_27", "imperial_to_slavers_1_28", "imperial_to_slavers_1_29", "imperial_to_slavers_1_30", "imperial_to_slavers_1_31", "imperial_to_slavers_1_32", "imperial_to_slavers_1_33", "imperial_to_slavers_1_34", "imperial_to_slavers_1_35", "imperial_to_slavers_1_36", "imperial_to_slavers_1_37", "imperial_to_slavers_1_38", "imperial_to_slavers_1_39", "imperial_to_slavers_1_40", "imperial_to_slavers_1_41", "imperial_to_slavers_1_42", "imperial_to_slavers_1_43", "imperial_to_slavers_1_44", "imperial_to_slavers_1_45", "imperial_to_slavers_1_46", "imperial_to_slavers_1_47", "imperial_to_slavers_1_48", "imperial_to_slavers_1_49", "imperial_to_slavers_1_50", "imperial_to_slavers_1_51", "imperial_to_slavers_1_52", "imperial_to_slavers_1_53", "imperial_to_slavers_1_54", "imperial_to_slavers_1_55", "imperial_to_slavers_1_56", "imperial_to_slavers_1_57", "imperial_to_slavers_1_58", "imperial_to_slavers_1_59", "imperial_to_slavers_1_60", "imperial_to_slavers_1_61", "imperial_to_slavers_1_62", "imperial_to_slavers_1_63", "imperial_to_slavers_1_64", "imperial_to_slavers_1_65", "imperial_to_slavers_1_66", "imperial_to_slavers_1_67"},
			{"imp_tie_bomber_tier3", "imp_tie_bomber_tier3_dantooine", "imp_tie_fighter_tier3_dantooine", "imp_tie_fighter_tier3_dantooine", "imp_tie_interceptor_tier3", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"random_valarian_filler_4", 477, 3805, 3268, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 350, 2,
			{"valarian_bomber_tier3", "valarian_gunship_tier3"}
		},
		{"slavers_route_2", 3000, -338, 6228, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 2,
			5, {"slavers_route_2_00", "slavers_route_2_01", "slavers_route_2_02", "slavers_route_2_03", "slavers_route_2_04", "slavers_route_2_05", "slavers_route_2_06", "slavers_route_2_07", "slavers_route_2_08", "slavers_route_2_09", "slavers_route_2_10", "slavers_route_2_11"},
			{"slave_trader_transport_tier3", "slave_trader_transport_tier3_dantooine", "slave_trader_transport_tier3_dantooine"}
		},
		{"imperial_beacon_1", 2983, -77, 7483, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 60, 350, 6,
			{"imp_tie_advanced_tier2", "imp_tie_bomber_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier3_dantooine", "imp_tie_interceptor_tier3_dantooine", "imp_tie_aggressor_tier2", "imp_tie_oppressor_tier2"}
		},
		{"slavers_route_1", 4475, -408, 7154, SHIP_AI_FIXED_PATROL, 300, 420, 40, 80, 2,
			5, {"slavers_route_1_00", "slavers_route_1_01", "slavers_route_1_02", "slavers_route_1_03", "slavers_route_1_04", "slavers_route_1_05", "slavers_route_1_06", "slavers_route_1_07", "slavers_route_1_08", "slavers_route_1_09"},
			{"slave_trader_transport_tier3", "slave_trader_transport_tier3_dantooine", "slave_trader_transport_tier3_dantooine"}
		},
		{"slave_trader_guardian_1", 5257, -251, 5803, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 4,
			5, {"slave_trader_guardian_1_00", "slave_trader_guardian_1_01", "slave_trader_guardian_1_02", "slave_trader_guardian_1_03", "slave_trader_guardian_1_04", "slave_trader_guardian_1_05", "slave_trader_guardian_1_06", "slave_trader_guardian_1_07", "slave_trader_guardian_1_08", "slave_trader_guardian_1_09", "slave_trader_guardian_1_10", "slave_trader_guardian_1_11", "slave_trader_guardian_1_12", "slave_trader_guardian_1_13", "slave_trader_guardian_1_14", "slave_trader_guardian_1_15", "slave_trader_guardian_1_16", "slave_trader_guardian_1_17", "slave_trader_guardian_1_18", "slave_trader_guardian_1_19", "slave_trader_guardian_1_20", "slave_trader_guardian_1_21", "slave_trader_guardian_1_22", "slave_trader_guardian_1_23", "slave_trader_guardian_1_24", "slave_trader_guardian_1_25"},
			{"slave_trader_guardian_boss", "slave_trader_guardian_tier3", "slave_trader_guardian_tier3", "slave_trader_guardian_tier3", "slave_trader_guardian_tier3_dantooine", "slave_trader_guardian_tier3_dantooine", "slave_trader_guardian_tier3_dantooine", "slave_trader_guardian_tier3_dantooine", "slave_trader_guardian_tier3_dantooine", "slave_trader_guardian_tier3_dantooine"}
		},
		{"random_valarian_filler_3", 4111, 4625, 4486, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 390, 2,
			{"valarian_bomber_tier2"}
		},
		{"imperial_attack_base", 5937, 3394, 4492, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 50, 350, 6,
			{"imp_tie_fighter_tier3", "imp_tie_fighter_tier3_dantooine", "imp_tie_fighter_tier3_dantooine", "imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3_dantooine", "imp_tie_interceptor_tier3_dantooine", "imp_tie_oppressor_tier3", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3"}
		},
		{"rebel_base_defense_3", -1551, 3987, -3455, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 25, 50, 100, 6,
			{"reb_xwing_tier2", "reb_xwing_tier3_dantooine", "reb_z95_tier2", "reb_z95_tier3", "reb_ywing_tier2", "reb_ywing_tier3", "reb_bwing_tier2", "reb_bwing_tier3", "reb_awing_tier2", "reb_awing_tier3"}
		},
		{"warrens_dudes_1", -2499, 741, -6306, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 5,
			5, {"warrens_dudes_1_00", "warrens_dudes_1_01", "warrens_dudes_1_02", "warrens_dudes_1_03", "warrens_dudes_1_04", "warrens_dudes_1_05", "warrens_dudes_1_06", "warrens_dudes_1_07", "warrens_dudes_1_08", "warrens_dudes_1_09", "warrens_dudes_1_10", "warrens_dudes_1_11", "warrens_dudes_1_12", "warrens_dudes_1_13", "warrens_dudes_1_14", "warrens_dudes_1_15", "warrens_dudes_1_16", "warrens_dudes_1_17", "warrens_dudes_1_18", "warrens_dudes_1_19", "warrens_dudes_1_20", "warrens_dudes_1_21", "warrens_dudes_1_22", "warrens_dudes_1_23", "warrens_dudes_1_24", "warrens_dudes_1_25", "warrens_dudes_1_26", "warrens_dudes_1_27", "warrens_dudes_1_28", "warrens_dudes_1_29", "warrens_dudes_1_30", "warrens_dudes_1_31", "warrens_dudes_1_32", "warrens_dudes_1_33", "warrens_dudes_1_34", "warrens_dudes_1_35", "warrens_dudes_1_36", "warrens_dudes_1_37", "warrens_dudes_1_38", "warrens_dudes_1_39", "warrens_dudes_1_40", "warrens_dudes_1_41", "warrens_dudes_1_42", "warrens_dudes_1_43", "warrens_dudes_1_44", "warrens_dudes_1_45", "warrens_dudes_1_46", "warrens_dudes_1_47", "warrens_dudes_1_48", "warrens_dudes_1_49", "warrens_dudes_1_50", "warrens_dudes_1_51", "warrens_dudes_1_52", "warrens_dudes_1_53", "warrens_dudes_1_54", "warrens_dudes_1_55", "warrens_dudes_1_56", "warrens_dudes_1_57"},
			{"warrens_fighter", "warrens_scout", "warrens_fighter_boss", "warrens_fighter", "warrens_fighter", "warrens_fighter", "warrens_fighter", "warrens_fighter", "warrens_scout", "warrens_scout", "warrens_scout", "warrens_scout", "warrens_scout", "warrens_scout"}
		},
		{"warrens_guards_2", -1293, 146, -7137, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 390, 3,
			{"warrens_fighter"}
		},
		{"scavenger_guardians_1", 2404, 2251, -1462, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 300, 3,
			{"scavenger_guardian_tier3", "scavenger_guardian_tier3_dantooine", "scavenger_guardian_tier3_dantooine"}
		},
		{"tatooine_privateer_tier4_leg_3_destroy_two", 3519, 3264, 1160, SHIP_AI_RANDOM_PATROL, 180, 300, 60, 120, 80, 360, 3,
			{"valarian_gunship_tier3", "valarian_bomber_tier3"}
		},
		{"imperial_area_generator_defense_1", -1109, 4017, -1684, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 350, 8,
			{"imp_tie_fighter_tier3", "imp_tie_fighter_tier3_dantooine", "imp_tie_fighter_tier3_dantooine", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"scavenger_debris_route_1", 2250, 1543, -745, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 4,
			5, {"scavenger_debris_route_1_00", "scavenger_debris_route_1_01", "scavenger_debris_route_1_02", "scavenger_debris_route_1_03", "scavenger_debris_route_1_04", "scavenger_debris_route_1_05", "scavenger_debris_route_1_06", "scavenger_debris_route_1_07", "scavenger_debris_route_1_08", "scavenger_debris_route_1_09", "scavenger_debris_route_1_10", "scavenger_debris_route_1_11", "scavenger_debris_route_1_12", "scavenger_debris_route_1_13", "scavenger_debris_route_1_14", "scavenger_debris_route_1_15", "scavenger_debris_route_1_16", "scavenger_debris_route_1_17", "scavenger_debris_route_1_18", "scavenger_debris_route_1_19", "scavenger_debris_route_1_20", "scavenger_debris_route_1_21", "scavenger_debris_route_1_22", "scavenger_debris_route_1_23", "scavenger_debris_route_1_24", "scavenger_debris_route_1_25", "scavenger_debris_route_1_26", "scavenger_debris_route_1_27", "scavenger_debris_route_1_28", "scavenger_debris_route_1_29", "scavenger_debris_route_1_30", "scavenger_debris_route_1_31", "scavenger_debris_route_1_32", "scavenger_debris_route_1_33", "scavenger_debris_route_1_34", "scavenger_debris_route_1_35", "scavenger_debris_route_1_36", "scavenger_debris_route_1_37", "scavenger_debris_route_1_38", "scavenger_debris_route_1_39", "scavenger_debris_route_1_40", "scavenger_debris_route_1_41", "scavenger_debris_route_1_42", "scavenger_debris_route_1_43", "scavenger_debris_route_1_44", "scavenger_debris_route_1_45", "scavenger_debris_route_1_46", "scavenger_debris_route_1_47"},
			{"scavenger_collector_tier3", "scavenger_guardian_tier3", "scavenger_guardian_tier3", "scavenger_guardian_tier3", "scavenger_guardian_tier3", "scavenger_raider_boss", "scavenger_collector_tier3_dantooine", "scavenger_collector_tier3_dantooine", "scavenger_guardian_tier3_dantooine", "scavenger_guardian_tier3_dantooine", "scavenger_guardian_tier3_dantooine"}
		},
		{"scavenger_to_blacksun_1", 2274, 1515, -716, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 4,
			5, {"scavenger_to_blacksun_1_00", "scavenger_to_blacksun_1_01", "scavenger_to_blacksun_1_02", "scavenger_to_blacksun_1_03", "scavenger_to_blacksun_1_04", "scavenger_to_blacksun_1_05", "scavenger_to_blacksun_1_06", "scavenger_to_blacksun_1_07", "scavenger_to_blacksun_1_08", "scavenger_to_blacksun_1_09", "scavenger_to_blacksun_1_10", "scavenger_to_blacksun_1_11", "scavenger_to_blacksun_1_12", "scavenger_to_blacksun_1_13", "scavenger_to_blacksun_1_14", "scavenger_to_blacksun_1_15", "scavenger_to_blacksun_1_16", "scavenger_to_blacksun_1_17", "scavenger_to_blacksun_1_18", "scavenger_to_blacksun_1_19", "scavenger_to_blacksun_1_20", "scavenger_to_blacksun_1_21", "scavenger_to_blacksun_1_22", "scavenger_to_blacksun_1_23", "scavenger_to_blacksun_1_24", "scavenger_to_blacksun_1_25", "scavenger_to_blacksun_1_26", "scavenger_to_blacksun_1_27", "scavenger_to_blacksun_1_28", "scavenger_to_blacksun_1_29", "scavenger_to_blacksun_1_30", "scavenger_to_blacksun_1_31"},
			{"scavenger_collector_tier3_dantooine", "scavenger_guardian_tier3_dantooine"}
		},
		{"scavenger_guardian_4", 2567, 1685, -375, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 360, 3,
			{"scavenger_guardian_tier3_dantooine", "scavenger_guardian_tier3_dantooine", "scavenger_guardian_tier3_dantooine"}
		},
		{"scavenger_guardian_2", 1956, 2331, -1123, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 460, 2,
			{"scavenger_fanatic_tier3", "scavenger_guardian_tier2", "scavenger_guardian_tier3", "scavenger_fanatic_tier3_dantooine", "scavenger_fanatic_tier3_dantooine", "scavenger_guardian_tier3_dantooine", "scavenger_guardian_tier3_dantooine"}
		},
		{"scavenger_guardian_3", 1622, 2225, -464, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 360, 3,
			{"scavenger_guardian_tier3", "scavenger_guardian_tier3_dantooine", "scavenger_guardian_tier3_dantooine", "scavenger_guardian_tier3_dantooine"}
		},
		{"random_imperial_spawner_2", -4273, 3690, 1058, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 150, 350, 3,
			{"imp_tie_bomber_tier3", "imp_tie_interceptor_tier3"}
		},
		{"junk_dealer_traders_1", -7035, 660, -248, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 3,
			5, {"junk_dealer_traders_1_00", "junk_dealer_traders_1_01", "junk_dealer_traders_1_02", "junk_dealer_traders_1_03", "junk_dealer_traders_1_04", "junk_dealer_traders_1_05", "junk_dealer_traders_1_06", "junk_dealer_traders_1_07", "junk_dealer_traders_1_08", "junk_dealer_traders_1_09", "junk_dealer_traders_1_10", "junk_dealer_traders_1_11", "junk_dealer_traders_1_12", "junk_dealer_traders_1_13", "junk_dealer_traders_1_14", "junk_dealer_traders_1_15", "junk_dealer_traders_1_16", "junk_dealer_traders_1_17", "junk_dealer_traders_1_18", "junk_dealer_traders_1_19", "junk_dealer_traders_1_20"},
			{"junk_dealer_guardian", "junk_dealer_trader", "junk_dealer_trader", "junk_dealer_overseer", "junk_dealer_guardian", "junk_dealer_guardian", "junk_dealer_guardian", "junk_dealer_guardian", "junk_dealer_guardian", "junk_dealer_guardian"}
		},
		{"junk_dealers_route_1", -7312, 532, 24, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 3,
			5, {"junk_dealers_route_1_00", "junk_dealers_route_1_01", "junk_dealers_route_1_02", "junk_dealers_route_1_03", "junk_dealers_route_1_04", "junk_dealers_route_1_05", "junk_dealers_route_1_06", "junk_dealers_route_1_07", "junk_dealers_route_1_08", "junk_dealers_route_1_09", "junk_dealers_route_1_10", "junk_dealers_route_1_11", "junk_dealers_route_1_12", "junk_dealers_route_1_13", "junk_dealers_route_1_14", "junk_dealers_route_1_15", "junk_dealers_route_1_16", "junk_dealers_route_1_17", "junk_dealers_route_1_18", "junk_dealers_route_1_19", "junk_dealers_route_1_20", "junk_dealers_route_1_21", "junk_dealers_route_1_22", "junk_dealers_route_1_23", "junk_dealers_route_1_24", "junk_dealers_route_1_25", "junk_dealers_route_1_26", "junk_dealers_route_1_27", "junk_dealers_route_1_28", "junk_dealers_route_1_29", "junk_dealers_route_1_30", "junk_dealers_route_1_31", "junk_dealers_route_1_32", "junk_dealers_route_1_33", "junk_dealers_route_1_34", "junk_dealers_route_1_35", "junk_dealers_route_1_36", "junk_dealers_route_1_37", "junk_dealers_route_1_38", "junk_dealers_route_1_39", "junk_dealers_route_1_40"},
			{"junk_dealer_collector", "junk_dealer_guardian"}
		},
		{"junk_dealer_guardian_2", -6598, 2612, 1047, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 300, 2,
			{"junk_dealer_guardian"}
		},
		{"imperial_generator_defense_c", 4691, 4781, -6916, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 60, 320, 6,
			{"imp_tie_bomber_tier2", "imp_tie_bomber_tier3", "imp_tie_bomber_tier3_dantooine", "imp_tie_fighter_tier2", "imp_tie_fighter_tier3", "imp_tie_fighter_tier3_dantooine", "imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3_dantooine", "imp_tie_advanced_tier2", "imp_tie_aggressor_tier2", "imp_tie_aggressor_tier3"}
		},
		{"imperial_battle_1", 5836, 6225, -3897, SHIP_AI_RANDOM_PATROL, 180, 300, 30, 40, 50, 350, 6,
			{"imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_advanced_tier2", "imp_tie_bomber_tier2", "imp_tie_oppressor_tier2", "imp_tie_aggressor_tier2"}
		},
		{"velocity_battle_1", 5665, 6314, -3934, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 50, 300, 3,
			{"velocity_fighter_boss", "velocity_merc_heavy_fighter_tier3", "velocity_merc_heavy_fighter_tier3", "velocity_merc_heavy_fighter_tier3", "velocity_merc_heavy_fighter_tier3", "velocity_merc_heavy_fighter_tier3", "velocity_merc_heavy_fighter_tier3", "velocity_merc_heavy_fighter_tier3"}
		},
		{"imperial_battle_2", 6665, 5951, -4833, SHIP_AI_RANDOM_PATROL, 180, 300, 30, 40, 50, 350, 6,
			{"imp_tie_advanced_tier2", "imp_tie_aggressor_tier2", "imp_tie_bomber_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3_dantooine", "imp_tie_interceptor_tier3_dantooine", "imp_tie_oppressor_tier2"}
		},
		{"velocity_battle_3", 5826, 4836, -1980, SHIP_AI_RANDOM_PATROL, 180, 300, 30, 40, 50, 300, 3,
			{"velocity_smuggler_tier2"}
		},
		{"imperial_battle_3", 5951, 4862, -1932, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 50, 300, 6,
			{"imp_tie_bomber_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier3_dantooine", "imp_tie_interceptor_tier3_dantooine", "imp_tie_aggressor_tier2", "imp_tie_advanced_tier2", "imp_tie_oppressor_tier2"}
		},
		{"corellia_imperial_tier4_inspect1", 3133, 6113, -3618, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 60, 420, 1,
			{"velocity_merc_captain_tier4"}
		},
		{"hutt_gunships", -1252, -618, 1543, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 5,
			5, {"hutt_gunships_00", "hutt_gunships_01", "hutt_gunships_02", "hutt_gunships_03", "hutt_gunships_04", "hutt_gunships_05", "hutt_gunships_06", "hutt_gunships_07"},
			{"huttskiff_tier3", "hutt_pirate_s01_tier2"}
		},
		{"imperial_area_generator_defense_2", -1366, 3537, -1804, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 350, 8,
			{"imp_tie_bomber_tier3_dantooine", "imp_tie_bomber_tier3_dantooine", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_interceptor_tier3", "imp_tie_fighter_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"smuggle_route_1", -3158, 2978, -2521, SHIP_AI_FIXED_PATROL, 300, 420, 20, 40, 3,
			5, {"smuggle_route_1_00", "smuggle_route_1_01", "smuggle_route_1_02", "smuggle_route_1_03", "smuggle_route_1_04", "smuggle_route_1_05", "smuggle_route_1_06", "smuggle_route_1_07", "smuggle_route_1_08", "smuggle_route_1_09", "smuggle_route_1_10", "smuggle_route_1_11", "smuggle_route_1_12"},
			{"nym_smuggle_vessel", "nym_smuggle_vessel", "nym_smuggle_vessel", "nym_enforcer_tier3"}
		},
		{"smuggle_loiter_1", -3097, 2592, -2355, SHIP_AI_RANDOM_PATROL, 180, 300, 30, 60, 100, 400, 3,
			{"nym_bomber_tier3", "nym_enforcer_tier3", "nym_enforcer_tier2", "nym_bomber_tier2"}
		},
		{"mining_guard_1", 3311, -329, -1814, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 360, 2,
			{"mining_guard_ship_tier3", "mining_guard_ship_tier3_dantooine", "mining_guard_ship_tier3_dantooine"}
		},
		{"mining_guard_2", 243, 214, -2237, SHIP_AI_RANDOM_PATROL, 180, 300, 50, 100, 80, 360, 2,
			{"mining_guard_ship_tier3", "mining_guard_ship_tier3_dantooine", "mining_guard_ship_tier3_dantooine"}
		},
		{"trade_route_1", 1348, -753, -2321, SHIP_AI_FIXED_PATROL, 300, 420, 3, 6, 3,
			5, {"trade_route_1_00", "trade_route_1_01", "trade_route_1_02", "trade_route_1_03", "trade_route_1_04", "trade_route_1_05", "trade_route_1_06", "trade_route_1_07", "trade_route_1_08", "trade_route_1_09", "trade_route_1_10"},
			{"freighterheavy", "freighterlight", "freightermedium", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterheavy_tier3_story"}
		},
		{"mining_guard_patrol_1", 1626, -844, -2165, SHIP_AI_FIXED_PATROL, 180, 300, 10, 20, 3,
			5, {"mining_guard_patrol_1_00", "mining_guard_patrol_1_01", "mining_guard_patrol_1_02", "mining_guard_patrol_1_03", "mining_guard_patrol_1_04", "mining_guard_patrol_1_05", "mining_guard_patrol_1_06", "mining_guard_patrol_1_07"},
			{"mining_guard_ship_boss", "mining_guard_ship_tier3", "mining_guard_ship_tier3", "mining_guard_ship_tier3", "mining_guard_ship_tier3_dantooine", "mining_guard_ship_tier3_dantooine", "mining_guard_ship_tier3_dantooine", "mining_guard_ship_tier3_dantooine", "mining_guard_ship_tier3_dantooine", "mining_guard_ship_tier3_dantooine", "mining_guard_ship_tier3_dantooine", "mining_guard_ship_tier3_dantooine"}
		},
		{"mining_route_1", 2041, -354, -1242, SHIP_AI_FIXED_PATROL, 300, 420, 30, 50, 3,
			5, {"mining_route_1_00", "mining_route_1_01", "mining_route_1_02", "mining_route_1_03", "mining_route_1_04", "mining_route_1_05", "mining_route_1_06", "mining_route_1_07", "mining_route_1_08", "mining_route_1_09"},
			{"freighterheavy_mining", "freighterlight_mining", "freightermedium_mining"}
		},
		{"mining_spawner_1", 2000, -400, -1300, SHIP_AI_RANDOM_PATROL, 180, 300, 30, 50, 100, 400, 3,
			{"mining_guard_ship_tier3", "mining_guard_ship_tier3_dantooine", "mining_guard_ship_tier3_dantooine"}
		},
	},
}

registerScreenPlay("SpaceDantooineSpawner", true)

function SpaceDantooineSpawner:start()
	if (not isZoneEnabled(self.spaceZone)) then
		return
	end

	self:populateSpawns()
end
