SpaceNabooSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceNabooSpawner",

	spaceZone = "space_naboo",

	shipSpawns = {
		{"rogue_droid_generator", -7133, 1932, -977, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 5,
			5, {"rogue_droid_generator_00", "rogue_droid_generator_01", "rogue_droid_generator_02", "rogue_droid_generator_03", "rogue_droid_generator_04", "rogue_droid_generator_05", "rogue_droid_generator_06", "rogue_droid_generator_07", "rogue_droid_generator_08", "rogue_droid_generator_09", "rogue_droid_generator_10", "rogue_droid_generator_11", "rogue_droid_generator_12", "rogue_droid_generator_13", "rogue_droid_generator_14", "rogue_droid_generator_15", "rogue_droid_generator_16", "rogue_droid_generator_17", "rogue_droid_generator_18"},
			{"rogue_droid_bomber", "rogue_droid_defender_tier1", "rogue_droid_defender_tier1_naboo", "rogue_droid_fighter_tier1", "rogue_droid_fighter_tier1_naboo", "rogue_droid_scrapper_tier1_naboo"}
		},
		{"rogue_droid_boss", -7118, 1949, -1078, SHIP_AI_FIXED_PATROL, 7200, 10800, 5, 15, 1,
			5, {"rogue_droid_boss_00", "rogue_droid_boss_01", "rogue_droid_boss_02", "rogue_droid_boss_03", "rogue_droid_boss_04", "rogue_droid_boss_05", "rogue_droid_boss_06", "rogue_droid_boss_07", "rogue_droid_boss_08", "rogue_droid_boss_09", "rogue_droid_boss_10", "rogue_droid_boss_11", "rogue_droid_boss_12", "rogue_droid_boss_13", "rogue_droid_boss_14", "rogue_droid_boss_15", "rogue_droid_boss_16", "rogue_droid_boss_17", "rogue_droid_boss_18", "rogue_droid_boss_19", "rogue_droid_boss_20", "rogue_droid_boss_21", "rogue_droid_boss_22", "rogue_droid_boss_23", "rogue_droid_boss_24", "rogue_droid_boss_25", "rogue_droid_boss_26", "rogue_droid_boss_27", "rogue_droid_boss_28", "rogue_droid_boss_29", "rogue_droid_boss_30", "rogue_droid_boss_31", "rogue_droid_boss_32", "rogue_droid_boss_33", "rogue_droid_boss_34", "rogue_droid_boss_35", "rogue_droid_boss_36", "rogue_droid_boss_37", "rogue_droid_boss_38", "rogue_droid_boss_39", "rogue_droid_boss_40", "rogue_droid_boss_41", "rogue_droid_boss_42", "rogue_droid_boss_43", "rogue_droid_boss_44", "rogue_droid_boss_45", "rogue_droid_boss_46", "rogue_droid_boss_47"},
			{"rogue_droid_boss"}
		},
		{"rogue_droid_scrapper_route", -7167, 1933, -1052, SHIP_AI_FIXED_PATROL, 60, 120, 10, 30, 5,
			5, {"rogue_droid_scrapper_route_00", "rogue_droid_scrapper_route_01", "rogue_droid_scrapper_route_02", "rogue_droid_scrapper_route_03", "rogue_droid_scrapper_route_04", "rogue_droid_scrapper_route_05", "rogue_droid_scrapper_route_06", "rogue_droid_scrapper_route_07", "rogue_droid_scrapper_route_08", "rogue_droid_scrapper_route_09", "rogue_droid_scrapper_route_10"},
			{"rogue_droid_scrapper_tier1", "rogue_droid_scrapper_tier1_naboo"}
		},
		{"borvo_static_patrol_three", -2389, -5285, -810, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 50, 300, 4,
			{"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1_naboo", "borvo_fighter_tier1", "borvo_fighter_tier1_naboo"}
		},
		{"borvo_static_patrol_four", -3672, -7131, 2145, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 50, 300, 4,
			{"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1_naboo"}
		},
		{"borvo_boss", -3654, -5367, 2378, SHIP_AI_FIXED_PATROL, 7200, 10800, 10, 20, 1,
			5, {"borvo_boss_00", "borvo_boss_01", "borvo_boss_02", "borvo_boss_03", "borvo_boss_04", "borvo_boss_05", "borvo_boss_06", "borvo_boss_07", "borvo_boss_08", "borvo_boss_09", "borvo_boss_10", "borvo_boss_11", "borvo_boss_12", "borvo_boss_13", "borvo_boss_14", "borvo_boss_15", "borvo_boss_16", "borvo_boss_17", "borvo_boss_18", "borvo_boss_19", "borvo_boss_20", "borvo_boss_21", "borvo_boss_22", "borvo_boss_23", "borvo_boss_24", "borvo_boss_25", "borvo_boss_26", "borvo_boss_27", "borvo_boss_28", "borvo_boss_29", "borvo_boss_30", "borvo_boss_31", "borvo_boss_32", "borvo_boss_33", "borvo_boss_34", "borvo_boss_35", "borvo_boss_36", "borvo_boss_37", "borvo_boss_38", "borvo_boss_39", "borvo_boss_40", "borvo_boss_41", "borvo_boss_42", "borvo_boss_43", "borvo_boss_44", "borvo_boss_45", "borvo_boss_46", "borvo_boss_47", "borvo_boss_48", "borvo_boss_49", "borvo_boss_50", "borvo_boss_51", "borvo_boss_52"},
			{"borvo_boss_tier3"}
		},
		{"borvos_boys_route_base", -3637, -5422, 2523, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 5,
			5, {"borvos_boys_route_base_00", "borvos_boys_route_base_01", "borvos_boys_route_base_02", "borvos_boys_route_base_03", "borvos_boys_route_base_04", "borvos_boys_route_base_05", "borvos_boys_route_base_06", "borvos_boys_route_base_07", "borvos_boys_route_base_08", "borvos_boys_route_base_09", "borvos_boys_route_base_10", "borvos_boys_route_base_11", "borvos_boys_route_base_12", "borvos_boys_route_base_13", "borvos_boys_route_base_14", "borvos_boys_route_base_15", "borvos_boys_route_base_16", "borvos_boys_route_base_17", "borvos_boys_route_base_18", "borvos_boys_route_base_19", "borvos_boys_route_base_20", "borvos_boys_route_base_21", "borvos_boys_route_base_22", "borvos_boys_route_base_23", "borvos_boys_route_base_24", "borvos_boys_route_base_25", "borvos_boys_route_base_26", "borvos_boys_route_base_27", "borvos_boys_route_base_28", "borvos_boys_route_base_29", "borvos_boys_route_base_30", "borvos_boys_route_base_31", "borvos_boys_route_base_32", "borvos_boys_route_base_33", "borvos_boys_route_base_34", "borvos_boys_route_base_35", "borvos_boys_route_base_36", "borvos_boys_route_base_37", "borvos_boys_route_base_38", "borvos_boys_route_base_39", "borvos_boys_route_base_40", "borvos_boys_route_base_41", "borvos_boys_route_base_42", "borvos_boys_route_base_43", "borvos_boys_route_base_44", "borvos_boys_route_base_45", "borvos_boys_route_base_46", "borvos_boys_route_base_47", "borvos_boys_route_base_48", "borvos_boys_route_base_49", "borvos_boys_route_base_50", "borvos_boys_route_base_51", "borvos_boys_route_base_52", "borvos_boys_route_base_53"},
			{"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_fighter_tier1_naboo"}
		},
		{"borvo_vs_rsf_2", -4653, -4807, 2728, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 3,
			{"borvo_bomber_tier1", "borvo_fighter_tier1"}
		},
		{"rsf_vs_borvo_2", -4449, -4780, 2470, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 4,
			{"rsf_rawl_tier1_naboo", "rsf_stinger_tier1"}
		},
		{"borvo_static_patrol_six", -4704, -3760, 460, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 50, 300, 3,
			{"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1_naboo", "borvo_fighter_tier1", "borvo_fighter_tier1_naboo"}
		},
		{"borvo_vs_rsf_1", -4668, -2815, 551, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 3,
			{"borvo_bomber_tier1", "borvo_fighter_tier1_naboo"}
		},
		{"rsf_vs_borvo_1", -4706, -2816, 448, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 4,
			{"rsf_ace_tier1", "rsf_stinger_tier1"}
		},
		{"imperial_poi_asteroid", 3909, 3396, 7512, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 5,
			5, {"imperial_poi_asteroid_00", "imperial_poi_asteroid_01", "imperial_poi_asteroid_02", "imperial_poi_asteroid_03", "imperial_poi_asteroid_04"},
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{"tradefed_guardians_2", 3218, -5734, -5191, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 100, 300, 3,
			{"trade_fed_guardian"}
		},
		{"naboo_miner_stationary_patrol", 6006, 6494, 6770, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 50, 100, 4,
			{"naboo_miner_fighter"}
		},
		{"rsf_patrol_3", -1504, 4713, -5453, SHIP_AI_RANDOM_PATROL, 60, 120, 15, 45, 50, 300, 3,
			{"rsf_ace_tier1", "rsf_hunter_tier1", "rsf_hunter_tier1_naboo", "rsf_scanner_tier1", "rsf_stinger_tier1_naboo"}
		},
		{"rse_patrol", -388, 5529, -6249, SHIP_AI_FIXED_PATROL, 120, 240, 20, 35, 7,
			5, {"rse_patrol_00", "rse_patrol_01", "rse_patrol_02", "rse_patrol_03", "rse_patrol_04", "rse_patrol_05", "rse_patrol_06", "rse_patrol_07", "rse_patrol_08", "rse_patrol_09", "rse_patrol_10", "rse_patrol_11", "rse_patrol_12", "rse_patrol_13", "rse_patrol_14", "rse_patrol_15", "rse_patrol_16", "rse_patrol_17", "rse_patrol_18", "rse_patrol_19", "rse_patrol_20", "rse_patrol_21", "rse_patrol_22", "rse_patrol_23", "rse_patrol_24", "rse_patrol_25"},
			{"rsf_ace_tier1", "rsf_hunter_tier1", "rsf_hunter_tier1_naboo", "rsf_hunter_tier1_naboo", "rsf_rawl_tier1", "rsf_rawl_tier1_naboo"}
		},
		{"rsf_boss", -343, 5522, -6205, SHIP_AI_FIXED_PATROL, 7200, 10800, 10, 20, 1,
			5, {"rsf_boss_00", "rsf_boss_01", "rsf_boss_02", "rsf_boss_03", "rsf_boss_04", "rsf_boss_05", "rsf_boss_06", "rsf_boss_07", "rsf_boss_08", "rsf_boss_09", "rsf_boss_10", "rsf_boss_11", "rsf_boss_12", "rsf_boss_13", "rsf_boss_14", "rsf_boss_15", "rsf_boss_16", "rsf_boss_17", "rsf_boss_18", "rsf_boss_19", "rsf_boss_20", "rsf_boss_21", "rsf_boss_22", "rsf_boss_23", "rsf_boss_24", "rsf_boss_25", "rsf_boss_26", "rsf_boss_27", "rsf_boss_28", "rsf_boss_29", "rsf_boss_30", "rsf_boss_31", "rsf_boss_32", "rsf_boss_33", "rsf_boss_34", "rsf_boss_35", "rsf_boss_36", "rsf_boss_37", "rsf_boss_38", "rsf_boss_39", "rsf_boss_40", "rsf_boss_41", "rsf_boss_42", "rsf_boss_43", "rsf_boss_44", "rsf_boss_45", "rsf_boss_46", "rsf_boss_47", "rsf_boss_48", "rsf_boss_49", "rsf_boss_50", "rsf_boss_51", "rsf_boss_52", "rsf_boss_53", "rsf_boss_54", "rsf_boss_55", "rsf_boss_56", "rsf_boss_57", "rsf_boss_58", "rsf_boss_59", "rsf_boss_60", "rsf_boss_61", "rsf_boss_62", "rsf_boss_63"},
			{"rsf_boss"}
		},
		{"naboo_miner_fighters", 4895, 6528, 6078, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 3,
			5, {"naboo_miner_fighters_00", "naboo_miner_fighters_01", "naboo_miner_fighters_02", "naboo_miner_fighters_03", "naboo_miner_fighters_04", "naboo_miner_fighters_05", "naboo_miner_fighters_06", "naboo_miner_fighters_07", "naboo_miner_fighters_08", "naboo_miner_fighters_09", "naboo_miner_fighters_10", "naboo_miner_fighters_11", "naboo_miner_fighters_12", "naboo_miner_fighters_13", "naboo_miner_fighters_14", "naboo_miner_fighters_15", "naboo_miner_fighters_16", "naboo_miner_fighters_17", "naboo_miner_fighters_18", "naboo_miner_fighters_19", "naboo_miner_fighters_20", "naboo_miner_fighters_21", "naboo_miner_fighters_22", "naboo_miner_fighters_23", "naboo_miner_fighters_24", "naboo_miner_fighters_25", "naboo_miner_fighters_26", "naboo_miner_fighters_27", "naboo_miner_fighters_28", "naboo_miner_fighters_29", "naboo_miner_fighters_30", "naboo_miner_fighters_31", "naboo_miner_fighters_32", "naboo_miner_fighters_33", "naboo_miner_fighters_34", "naboo_miner_fighters_35", "naboo_miner_fighters_36", "naboo_miner_fighters_37", "naboo_miner_fighters_38", "naboo_miner_fighters_39", "naboo_miner_fighters_40", "naboo_miner_fighters_41", "naboo_miner_fighters_42", "naboo_miner_fighters_43", "naboo_miner_fighters_44", "naboo_miner_fighters_45", "naboo_miner_fighters_46", "naboo_miner_fighters_47", "naboo_miner_fighters_48", "naboo_miner_fighters_49", "naboo_miner_fighters_50", "naboo_miner_fighters_51", "naboo_miner_fighters_52", "naboo_miner_fighters_53", "naboo_miner_fighters_54", "naboo_miner_fighters_55"},
			{"naboo_miner_defender", "naboo_miner_fighter", "naboo_miner_hunter"}
		},
		{"naboo_miners_planetoid", 2736, 6039, 5438, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 1,
			5, {"naboo_miners_planetoid_00", "naboo_miners_planetoid_01", "naboo_miners_planetoid_02", "naboo_miners_planetoid_03", "naboo_miners_planetoid_04", "naboo_miners_planetoid_05", "naboo_miners_planetoid_06", "naboo_miners_planetoid_07", "naboo_miners_planetoid_08", "naboo_miners_planetoid_09", "naboo_miners_planetoid_10", "naboo_miners_planetoid_11", "naboo_miners_planetoid_12", "naboo_miners_planetoid_13", "naboo_miners_planetoid_14"},
			{"naboo_miner_transport"}
		},
		{"ot_violator_squad", -2535, 5374, 3629, SHIP_AI_FIXED_PATROL, 259200, 295200, 10, 20, 1,
			5, {"ot_violator_squad_00", "ot_violator_squad_01", "ot_violator_squad_02", "ot_violator_squad_03", "ot_violator_squad_04", "ot_violator_squad_05", "ot_violator_squad_06", "ot_violator_squad_07", "ot_violator_squad_08", "ot_violator_squad_09", "ot_violator_squad_10", "ot_violator_squad_11", "ot_violator_squad_12", "ot_violator_squad_13", "ot_violator_squad_14", "ot_violator_squad_15", "ot_violator_squad_16", "ot_violator_squad_17", "ot_violator_squad_18", "ot_violator_squad_19", "ot_violator_squad_20", "ot_violator_squad_21", "ot_violator_squad_22"},
			{"squad_naboo_boss"}
		},
		{"naboo_privateer_13", 3168, -1441, -1209, SHIP_AI_RANDOM_PATROL, 60, 120, 24, 64, 116, 320, 3,
			{"aynat_enforcer_tier1", "aynat_ghost_tier1", "aynat_intimidator_tier1", "aynat_outlaw_tier1", "aynat_vaporizer_tier1"}
		},
		{"rsf_station_guards_2", -1058, 36, -6779, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"rsf_rawl_tier1", "rsf_stinger_tier1"}
		},
		{"rsf_station_guards_3", 595, -91, -4744, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"rsf_rawl_tier1", "rsf_rawl_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier1_naboo"}
		},
		{"imperial_generic_1", 1036, -506, -1295, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 64, 55, 380, 3,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{"black_sun_route_1", -21, -289, -960, SHIP_AI_FIXED_PATROL, 60, 120, 8, 32, 3,
			5, {"black_sun_route_1_00", "black_sun_route_1_01", "black_sun_route_1_02", "black_sun_route_1_03"},
			{"blacksun_ace_s04_tier1", "blacksun_bomber_ace_s04_tier1", "blacksun_fighter_s01_tier1", "blacksun_fighter_s02_tier1", "blacksun_fighter_s02_tier1", "blacksun_fighter_s02_tier1", "blacksun_fighter_s02_tier1"}
		},
		{"rebel_attack_1", -476, 1137, -971, SHIP_AI_RANDOM_PATROL, 10, 20, 8, 64, 80, 180, 3,
			{"imp_freightermedium_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1"}
		},
		{"hutt_generic_1", -16, 942, -1260, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 32, 100, 400, 3,
			{"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s02_tier1"}
		},
		{"rsf_to_station_2", -3125, 551, -4589, SHIP_AI_FIXED_PATROL, 60, 120, 10, 50, 7,
			5, {"rsf_to_station_2_00", "rsf_to_station_2_01", "rsf_to_station_2_02"},
			{"rsf_rawl_tier1", "rsf_rawl_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier1_naboo"}
		},
		{"rsf_vs_droids_4", -6139, -1178, -3891, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 200, 3,
			{"rsf_rawl_tier1_naboo", "rsf_stinger_tier1"}
		},
		{"droid_vs_rsf_4", -6117, -772, -3763, SHIP_AI_RANDOM_PATROL, 10, 60, 10, 30, 150, 300, 10,
			{"rogue_droid_defender_tier1", "rogue_droid_fighter_tier1", "rogue_droid_alpha_tier1", "rogue_droid_alpha_tier1_naboo", "rogue_droid_defender", "rogue_droid_defender_tier1", "rogue_droid_defender_tier1_naboo", "rogue_droid_fighter", "rogue_droid_fighter_tier1", "rogue_droid_scrapper", "rogue_droid_scrapper_tier1", "rogue_droid_scrapper_tier1_naboo"}
		},
		{"rebel_cadet_1", -6416, -2568, -4512, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 64, 50, 380, 3,
			{"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1"}
		},
		{"comm_ship_twinstar_shipping_01", -5000, -3200, -5000, SHIP_AI_RANDOM_PATROL, 4, 120, 32, 128, 100, 400, 3,
			{"blacksun_fighter_s02_tier1", "blacksun_marauder_tier1"}
		},
		{"stn_dantooine_shiftyprince_inspect_01", -6032, -2176, -5816, SHIP_AI_RANDOM_PATROL, 15, 45, 32, 128, 100, 400, 1,
			{"shifty_prince_tier3"}
		},
		{"naboo_imperial_2", -1915, -2006, -1455, SHIP_AI_RANDOM_PATROL, 60, 14, 8, 120, 100, 300, 3,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{"imperial_fluff_spawns_3", -2024, -3820, -3131, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 100, 300, 3,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{"rebel_defense_3", -5233, 6658, 6405, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 50, 300, 3,
			{"reb_xwing_cadet_tier1"}
		},
		{"rebel_defense_4", -4892, 6147, 6901, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 50, 300, 4,
			{"reb_xwing_tier1", "reb_xwing_tier1", "reb_ywing_tier2", "reb_ywing_tier2", "rebel_raider_captain"}
		},
		{"imperial_fluff_spawns_4", -5221, 5646, 5880, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{"rebel_boss", -5569, 5792, 6386, SHIP_AI_FIXED_PATROL, 7200, 10800, 10, 20, 1,
			5, {"rebel_boss_00", "rebel_boss_01", "rebel_boss_02", "rebel_boss_03", "rebel_boss_04", "rebel_boss_05", "rebel_boss_06", "rebel_boss_07", "rebel_boss_08", "rebel_boss_09", "rebel_boss_10", "rebel_boss_11", "rebel_boss_12", "rebel_boss_13", "rebel_boss_14", "rebel_boss_15", "rebel_boss_16", "rebel_boss_17", "rebel_boss_18", "rebel_boss_19", "rebel_boss_20"},
			{"rebel_boss"}
		},
		{"rebel_defense_2", -5998, 5792, 6563, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 50, 300, 4,
			{"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_tier1", "reb_ywing_tier1", "reb_z95_tier1"}
		},
		{"imperial_naboo_squad_3", -6004, 5601, 5836, SHIP_AI_FIXED_PATROL, 300, 420, 10, 20, 1,
			5, {"imperial_naboo_squad_3_00", "imperial_naboo_squad_3_01", "imperial_naboo_squad_3_02", "imperial_naboo_squad_3_03", "imperial_naboo_squad_3_04", "imperial_naboo_squad_3_05"},
			{"squad_imperial_naboo_3"}
		},
		{"rebel_base_defense_1", -5667, 6271, 6288, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 3,
			5, {"rebel_base_defense_1_00", "rebel_base_defense_1_01", "rebel_base_defense_1_02", "rebel_base_defense_1_03", "rebel_base_defense_1_04", "rebel_base_defense_1_05", "rebel_base_defense_1_06", "rebel_base_defense_1_07", "rebel_base_defense_1_08", "rebel_base_defense_1_09", "rebel_base_defense_1_10", "rebel_base_defense_1_11", "rebel_base_defense_1_12", "rebel_base_defense_1_13", "rebel_base_defense_1_14", "rebel_base_defense_1_15", "rebel_base_defense_1_16", "rebel_base_defense_1_17", "rebel_base_defense_1_18", "rebel_base_defense_1_19", "rebel_base_defense_1_20"},
			{"reb_z95_tier1", "reb_xwing_tier1"}
		},
		{"rsf_station_guards_6", 4741, -6195, 2118, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"rsf_rawl_tier1", "rsf_rawl_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier2_naboo"}
		},
		{"droid_vs_rsf_2", -5456, 2169, -1279, SHIP_AI_RANDOM_PATROL, 10, 60, 10, 30, 150, 300, 10,
			{"rogue_droid_defender_tier1", "rogue_droid_fighter_tier1_naboo", "rogue_droid_alpha_tier1", "rogue_droid_alpha_tier1_naboo", "rogue_droid_defender", "rogue_droid_defender_tier1", "rogue_droid_defender_tier1_naboo", "rogue_droid_fighter", "rogue_droid_fighter_tier1", "rogue_droid_scrapper", "rogue_droid_scrapper_tier1", "rogue_droid_scrapper_tier1_naboo"}
		},
		{"rsf_vs_droids_2", -5187, 2236, -1313, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 4,
			{"rsf_rawl_tier1_naboo", "rsf_stinger_tier1"}
		},
		{"rsf_patrol_2", -6302, 2023, -2391, SHIP_AI_RANDOM_PATROL, 60, 120, 20, 35, 50, 300, 3,
			{"rsf_rawl_tier1", "rsf_rawl_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier1_naboo"}
		},
		{"rogue_droid_scrapper_patrol", -7060, 1785, -1125, SHIP_AI_FIXED_PATROL, 60, 120, 15, 30, 5,
			5, {"rogue_droid_scrapper_patrol_00", "rogue_droid_scrapper_patrol_01", "rogue_droid_scrapper_patrol_02", "rogue_droid_scrapper_patrol_03", "rogue_droid_scrapper_patrol_04", "rogue_droid_scrapper_patrol_05", "rogue_droid_scrapper_patrol_06", "rogue_droid_scrapper_patrol_07", "rogue_droid_scrapper_patrol_08", "rogue_droid_scrapper_patrol_09", "rogue_droid_scrapper_patrol_10", "rogue_droid_scrapper_patrol_11", "rogue_droid_scrapper_patrol_12", "rogue_droid_scrapper_patrol_13", "rogue_droid_scrapper_patrol_14", "rogue_droid_scrapper_patrol_15", "rogue_droid_scrapper_patrol_16", "rogue_droid_scrapper_patrol_17", "rogue_droid_scrapper_patrol_18", "rogue_droid_scrapper_patrol_19", "rogue_droid_scrapper_patrol_20", "rogue_droid_scrapper_patrol_21", "rogue_droid_scrapper_patrol_22", "rogue_droid_scrapper_patrol_23"},
			{"rogue_droid_defender_tier1", "rogue_droid_defender_tier1_naboo", "rogue_droid_fighter_tier1", "rogue_droid_fighter_tier1_naboo"}
		},
		{"black_sun_generic_1", -2302, 1093, -1291, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 64, 300, 600, 3,
			{"blacksun_ace_s04_tier2", "blacksun_aggressor_tier2", "blacksun_bomber_ace_s04_tier2", "blacksun_fighter_s01_tier2", "blacksun_marauder_tier2", "blacksun_vehement_tier2"}
		},
		{"imperial_fluff_spawns_5", -5968, -1847, 386, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{"rsf_vs_droids_1", -4700, -1052, -419, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 4,
			{"rsf_rawl_tier1", "rsf_stinger_tier1"}
		},
		{"droid_vs_rsf_1", -4765, -502, -531, SHIP_AI_RANDOM_PATROL, 10, 60, 10, 30, 150, 300, 10,
			{"rogue_droid_alpha_tier1", "rogue_droid_alpha_tier1_naboo", "rogue_droid_fighter", "rogue_droid_fighter_tier1", "rogue_droid_fighter_tier1_naboo", "rogue_droid_defender", "rogue_droid_defender_tier1", "rogue_droid_defender_tier1_naboo", "rogue_droid_scrapper", "rogue_droid_scrapper_tier1_naboo"}
		},
		{"naboo_imperial_4", -3738, 2869, -2174, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 32, 50, 300, 3,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{"imperial_poi_2", -2986, 2039, -22, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 350, 3,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_interceptor_tier1"}
		},
		{"imperial_poi_spawner", -3007, 1805, -3, SHIP_AI_FIXED_PATROL, 300, 430, 10, 20, 1,
			5, {"imperial_poi_spawner_00", "imperial_poi_spawner_01", "imperial_poi_spawner_02", "imperial_poi_spawner_03", "imperial_poi_spawner_04", "imperial_poi_spawner_05", "imperial_poi_spawner_06", "imperial_poi_spawner_07"},
			{"squad_imperial_naboo_2"}
		},
		{"rsf_patrol_5", -4572, 1876, 2862, SHIP_AI_RANDOM_PATROL, 60, 120, 20, 50, 70, 310, 3,
			{"rsf_ace_tier1", "rsf_hunter_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier1_naboo"}
		},
		{"naboo_privateer_2", 2958, 941, -1002, SHIP_AI_RANDOM_PATROL, 4, 120, 32, 128, 100, 400, 3,
			{"blacksun_fighter_s02_tier1", "blacksun_marauder_tier1"}
		},
		{"imperial_boss", 2682, 1603, 869, SHIP_AI_FIXED_PATROL, 7200, 10800, 10, 20, 1,
			5, {"imperial_boss_00", "imperial_boss_01", "imperial_boss_02", "imperial_boss_03", "imperial_boss_04", "imperial_boss_05", "imperial_boss_06", "imperial_boss_07", "imperial_boss_08", "imperial_boss_09", "imperial_boss_10", "imperial_boss_11", "imperial_boss_12", "imperial_boss_13", "imperial_boss_14", "imperial_boss_15", "imperial_boss_16", "imperial_boss_17", "imperial_boss_18", "imperial_boss_19", "imperial_boss_20", "imperial_boss_21", "imperial_boss_22", "imperial_boss_23", "imperial_boss_24", "imperial_boss_25", "imperial_boss_26", "imperial_boss_27", "imperial_boss_28", "imperial_boss_29", "imperial_boss_30", "imperial_boss_31", "imperial_boss_32", "imperial_boss_33", "imperial_boss_34", "imperial_boss_35", "imperial_boss_36", "imperial_boss_37", "imperial_boss_38", "imperial_boss_39", "imperial_boss_40", "imperial_boss_41", "imperial_boss_42", "imperial_boss_43", "imperial_boss_44", "imperial_boss_45", "imperial_boss_46", "imperial_boss_47", "imperial_boss_48", "imperial_boss_49", "imperial_boss_50", "imperial_boss_51", "imperial_boss_52", "imperial_boss_53", "imperial_boss_54", "imperial_boss_55", "imperial_boss_56", "imperial_boss_57", "imperial_boss_58", "imperial_boss_59", "imperial_boss_60", "imperial_boss_61"},
			{"imperial_boss"}
		},
		{"imperial_base_patrol_2", 2840, 1573, 930, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 4,
			5, {"imperial_base_patrol_2_00", "imperial_base_patrol_2_01", "imperial_base_patrol_2_02", "imperial_base_patrol_2_03", "imperial_base_patrol_2_04", "imperial_base_patrol_2_05", "imperial_base_patrol_2_06", "imperial_base_patrol_2_07", "imperial_base_patrol_2_08", "imperial_base_patrol_2_09", "imperial_base_patrol_2_10", "imperial_base_patrol_2_11", "imperial_base_patrol_2_12", "imperial_base_patrol_2_13", "imperial_base_patrol_2_14", "imperial_base_patrol_2_15", "imperial_base_patrol_2_16", "imperial_base_patrol_2_17", "imperial_base_patrol_2_18", "imperial_base_patrol_2_19", "imperial_base_patrol_2_20", "imperial_base_patrol_2_21"},
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_interceptor_tier1"}
		},
		{"imperial_base_patrol", 2954, 1642, 916, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 4,
			5, {"imperial_base_patrol_00", "imperial_base_patrol_01", "imperial_base_patrol_02", "imperial_base_patrol_03", "imperial_base_patrol_04", "imperial_base_patrol_05", "imperial_base_patrol_06", "imperial_base_patrol_07", "imperial_base_patrol_08", "imperial_base_patrol_09", "imperial_base_patrol_10", "imperial_base_patrol_11", "imperial_base_patrol_12", "imperial_base_patrol_13", "imperial_base_patrol_14", "imperial_base_patrol_15", "imperial_base_patrol_16", "imperial_base_patrol_17", "imperial_base_patrol_18", "imperial_base_patrol_19", "imperial_base_patrol_20", "imperial_base_patrol_21", "imperial_base_patrol_22"},
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{"imperial_gunboat_woot_1", 3166, 1238, 1103, SHIP_AI_FIXED_PATROL, 3600, 4200, 10, 20, 2,
			5, {"imperial_gunboat_woot_1_00", "imperial_gunboat_woot_1_01", "imperial_gunboat_woot_1_02", "imperial_gunboat_woot_1_03", "imperial_gunboat_woot_1_04", "imperial_gunboat_woot_1_05", "imperial_gunboat_woot_1_06", "imperial_gunboat_woot_1_07", "imperial_gunboat_woot_1_08", "imperial_gunboat_woot_1_09", "imperial_gunboat_woot_1_10", "imperial_gunboat_woot_1_11", "imperial_gunboat_woot_1_12", "imperial_gunboat_woot_1_13", "imperial_gunboat_woot_1_14", "imperial_gunboat_woot_1_15", "imperial_gunboat_woot_1_16", "imperial_gunboat_woot_1_17", "imperial_gunboat_woot_1_18", "imperial_gunboat_woot_1_19", "imperial_gunboat_woot_1_20"},
			{"imp_imperial_gunboat_tier1"}
		},
		{"rebel_cadet_3", 5492, 64, 2804, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 64, 50, 380, 3,
			{"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1"}
		},
		{"rsf_patrol_4", 1297, 4803, -4375, SHIP_AI_RANDOM_PATROL, 60, 120, 30, 50, 70, 310, 3,
			{"rsf_ace_tier1", "rsf_hunter_tier1"}
		},
		{"naboo_rori_transport_route", 3211, 2687, -2756, SHIP_AI_FIXED_PATROL, 60, 120, 50, 70, 5,
			5, {"naboo_rori_transport_route_00", "naboo_rori_transport_route_01", "naboo_rori_transport_route_02", "naboo_rori_transport_route_03", "naboo_rori_transport_route_04", "naboo_rori_transport_route_05", "naboo_rori_transport_route_06", "naboo_rori_transport_route_07", "naboo_rori_transport_route_08", "naboo_rori_transport_route_09", "naboo_rori_transport_route_10", "naboo_rori_transport_route_11", "naboo_rori_transport_route_12", "naboo_rori_transport_route_13", "naboo_rori_transport_route_14", "naboo_rori_transport_route_15", "naboo_rori_transport_route_16"},
			{"freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_tier1", "freightermedium_tier1", "rsf_ace_tier1", "rsf_ace_tier1", "rsf_ace_tier1", "rsf_ace_tier1", "rsf_ace_tier1", "rsf_defender", "rsf_fighter"}
		},
		{"rsf_forces_station", 2837, 2687, -2682, SHIP_AI_RANDOM_PATROL, 60, 120, 50, 70, 100, 300, 3,
			{"rsf_ace_tier1", "rsf_hunter_tier1"}
		},
		{"black_sun_attack_1", 1091, 733, -2295, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 64, 200, 400, 6,
			{"blacksun_bomber_ace_s04_tier2", "blacksun_ace_s04_tier2", "blacksun_aggressor_tier2", "blacksun_fighter_s01_tier2", "blacksun_vehement_tier2", "blacksun_marauder_tier2"}
		},
		{"imperial_naboo_squad_1", 2358, 3786, -3554, SHIP_AI_FIXED_PATROL, 300, 420, 10, 20, 1,
			5, {"imperial_naboo_squad_1_00", "imperial_naboo_squad_1_01", "imperial_naboo_squad_1_02", "imperial_naboo_squad_1_03", "imperial_naboo_squad_1_04", "imperial_naboo_squad_1_05"},
			{"squad_imperial_naboo_1"}
		},
		{"tradefed_guardians_1", 1326, -5493, -5868, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 100, 300, 3,
			{"trade_fed_guardian"}
		},
		{"tradefed_wide_patrol", 2500, -5542, -5469, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 4,
			5, {"tradefed_wide_patrol_00", "tradefed_wide_patrol_01", "tradefed_wide_patrol_02", "tradefed_wide_patrol_03", "tradefed_wide_patrol_04", "tradefed_wide_patrol_05", "tradefed_wide_patrol_06", "tradefed_wide_patrol_07", "tradefed_wide_patrol_08"},
			{"trade_fed_fighter", "trade_fed_heavy_fighter", "trade_fed_bomber"}
		},
		{"tradefed_patrol_1", 2043, -5830, -6988, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 4,
			5, {"tradefed_patrol_1_00", "tradefed_patrol_1_01", "tradefed_patrol_1_02", "tradefed_patrol_1_03", "tradefed_patrol_1_04", "tradefed_patrol_1_05"},
			{"trade_fed_fighter", "trade_fed_bomber"}
		},
		{"federation_poi_patrol", 2171, -5573, -4644, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 5,
			5, {"federation_poi_patrol_00", "federation_poi_patrol_01", "federation_poi_patrol_02", "federation_poi_patrol_03", "federation_poi_patrol_04", "federation_poi_patrol_05", "federation_poi_patrol_06", "federation_poi_patrol_07", "federation_poi_patrol_08", "federation_poi_patrol_09", "federation_poi_patrol_10", "federation_poi_patrol_11"},
			{"trade_fed_fighter", "trade_fed_bomber"}
		},
		{"rsf_patrol_spawner", -5397, 2779, -3508, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 45, 60, 300, 3,
			{"rsf_ace_tier1", "rsf_hunter_tier1"}
		},
		{"rsf_patrol_2", -3525, 3169, -5274, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 50, 300, 3,
			{"rsf_ace_tier1", "rsf_hunter_tier1"}
		},
		{"rsf_station_guards_1", -3059, 1760, -7465, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"rsf_rawl_tier1", "rsf_rawl_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier1_naboo"}
		},
		{"naboo_privateer_4", 2147, -1509, 3415, SHIP_AI_RANDOM_PATROL, 60, 120, 32, 64, 50, 290, 3,
			{"blacksun_marauder_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{"borvo_static_patrol", -3324, -4588, 2821, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"borvo_defender_tier1", "borvo_defender_tier1_naboo", "borvo_fighter_tier1", "borvo_fighter_tier1_naboo"}
		},
		{"borvo_civ_route_assault", -2997, -3003, 2790, SHIP_AI_FIXED_PATROL, 60, 120, 10, 30, 4,
			5, {"borvo_civ_route_assault_00", "borvo_civ_route_assault_01", "borvo_civ_route_assault_02", "borvo_civ_route_assault_03", "borvo_civ_route_assault_04", "borvo_civ_route_assault_05", "borvo_civ_route_assault_06", "borvo_civ_route_assault_07", "borvo_civ_route_assault_08", "borvo_civ_route_assault_09", "borvo_civ_route_assault_10", "borvo_civ_route_assault_11", "borvo_civ_route_assault_12", "borvo_civ_route_assault_13", "borvo_civ_route_assault_14", "borvo_civ_route_assault_15", "borvo_civ_route_assault_16", "borvo_civ_route_assault_17", "borvo_civ_route_assault_18", "borvo_civ_route_assault_19", "borvo_civ_route_assault_20", "borvo_civ_route_assault_21", "borvo_civ_route_assault_22", "borvo_civ_route_assault_23", "borvo_civ_route_assault_24", "borvo_civ_route_assault_25", "borvo_civ_route_assault_26", "borvo_civ_route_assault_27", "borvo_civ_route_assault_28", "borvo_civ_route_assault_29", "borvo_civ_route_assault_30", "borvo_civ_route_assault_31", "borvo_civ_route_assault_32", "borvo_civ_route_assault_33", "borvo_civ_route_assault_34", "borvo_civ_route_assault_35", "borvo_civ_route_assault_36", "borvo_civ_route_assault_37"},
			{"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1_naboo", "borvo_fighter_tier1", "borvo_fighter_tier1_naboo"}
		},
		{"rebel_cadet_2", 4480, -4132, -6180, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 64, 50, 380, 3,
			{"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1"}
		},
		{"rsf_station_patrol_1", 6928, -4258, -320, SHIP_AI_FIXED_PATROL, 60, 120, 10, 50, 7,
			5, {"rsf_station_patrol_1_00", "rsf_station_patrol_1_01", "rsf_station_patrol_1_02", "rsf_station_patrol_1_03", "rsf_station_patrol_1_04", "rsf_station_patrol_1_05"},
			{"rsf_rawl_tier1", "rsf_stinger_tier1"}
		},
		{"freighters_station_1", 7423, -4059, -443, SHIP_AI_FIXED_PATROL, 300, 420, 10, 50, 3,
			5, {"freighters_station_1_00", "freighters_station_1_01", "freighters_station_1_02", "freighters_station_1_03", "freighters_station_1_04"},
			{"freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterheavy_tier1", "freighterlight_tier1", "freighterlight_tier1"}
		},
		{"rsf_station_guards_5", 6137, -2967, -2084, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"rsf_rawl_tier1", "rsf_stinger_tier1"}
		},
		{"naboo_miners_2", 2244, 5805, 4430, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 1,
			5, {"naboo_miners_2_00", "naboo_miners_2_01", "naboo_miners_2_02", "naboo_miners_2_03", "naboo_miners_2_04", "naboo_miners_2_05", "naboo_miners_2_06", "naboo_miners_2_07", "naboo_miners_2_08", "naboo_miners_2_09", "naboo_miners_2_10", "naboo_miners_2_11", "naboo_miners_2_12", "naboo_miners_2_13", "naboo_miners_2_14", "naboo_miners_2_15", "naboo_miners_2_16", "naboo_miners_2_17", "naboo_miners_2_18", "naboo_miners_2_19", "naboo_miners_2_20", "naboo_miners_2_21", "naboo_miners_2_22", "naboo_miners_2_23", "naboo_miners_2_24"},
			{"naboo_miner_transport"}
		},
		{"naboo_privateer_tier3_leg_3_inspect", 3151, 3183, 4026, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 15, 10, 300, 1,
			{"naboo_diplomatic_corps_bad_tier3"}
		},
		{"naboo_privateer_tier_3_leg_2_destroy", 3361, 3224, 3815, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 10, 300, 4,
			{"aynat_intimidator_tier1"}
		},
		{"miner_boss", 3503, 5583, 4003, SHIP_AI_FIXED_PATROL, 7200, 10800, 10, 20, 1,
			5, {"miner_boss_00", "miner_boss_01", "miner_boss_02", "miner_boss_03", "miner_boss_04", "miner_boss_05", "miner_boss_06", "miner_boss_07", "miner_boss_08", "miner_boss_09", "miner_boss_10", "miner_boss_11", "miner_boss_12", "miner_boss_13", "miner_boss_14", "miner_boss_15", "miner_boss_16", "miner_boss_17"},
			{"naboo_miner_boss"}
		},
		{"borvo_static_patrol_five", -5949, -4106, 3627, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 100, 300, 4,
			{"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1_naboo", "borvo_fighter_tier1", "borvo_fighter_tier1_naboo"}
		},
		{"naboo_miners_3", 4686, 6442, 4474, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 1,
			5, {"naboo_miners_3_00", "naboo_miners_3_01", "naboo_miners_3_02", "naboo_miners_3_03", "naboo_miners_3_04", "naboo_miners_3_05", "naboo_miners_3_06", "naboo_miners_3_07", "naboo_miners_3_08", "naboo_miners_3_09", "naboo_miners_3_10", "naboo_miners_3_11", "naboo_miners_3_12", "naboo_miners_3_13", "naboo_miners_3_14", "naboo_miners_3_15", "naboo_miners_3_16", "naboo_miners_3_17", "naboo_miners_3_18", "naboo_miners_3_19", "naboo_miners_3_20", "naboo_miners_3_21", "naboo_miners_3_22", "naboo_miners_3_23", "naboo_miners_3_24", "naboo_miners_3_25", "naboo_miners_3_26", "naboo_miners_3_27", "naboo_miners_3_28", "naboo_miners_3_29", "naboo_miners_3_30", "naboo_miners_3_31", "naboo_miners_3_32", "naboo_miners_3_33"},
			{"naboo_miner_transport"}
		},
		{"naboo_miner_outer_patrol", 5411, 7287, 3928, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 50, 401, 4,
			{"naboo_miner_fighter"}
		},
		{"borvo_static_patrol_two", -923, -5511, 913, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 50, 300, 4,
			{"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1", "borvo_defender_tier1_naboo"}
		},
		{"rebel_generic_1", -172, -2813, -425, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 64, 50, 380, 3,
			{"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1"}
		},
		{"naboo_privateer_12", 3142, -3591, -492, SHIP_AI_RANDOM_PATROL, 60, 120, 16, 64, 140, 612, 3,
			{"aynat_enforcer_tier1", "aynat_ghost_tier1", "aynat_intimidator_tier1"}
		},
		{"naboo_miner_patrol_two", 1378, 4209, 6187, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 40, 300, 4,
			{"naboo_miner_fighter"}
		},
		{"imperial_naboo_squad_2", 1732, 5597, 5168, SHIP_AI_FIXED_PATROL, 300, 420, 10, 20, 1,
			5, {"imperial_naboo_squad_2_00", "imperial_naboo_squad_2_01", "imperial_naboo_squad_2_02", "imperial_naboo_squad_2_03", "imperial_naboo_squad_2_04", "imperial_naboo_squad_2_05"},
			{"squad_imperial_naboo_2"}
		},
		{"imperial_fluff_spawns_1", 386, 3917, 3129, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{"rsf_civ_route_defenders", -2052, -931, 3368, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 30, 300, 4,
			{"rsf_hunter_tier1", "rsf_hunter_tier1_naboo", "rsf_rawl_tier1_naboo"}
		},
		{"imperial_fluff_spawns_2", -1837, -174, -162, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_interceptor_tier1"}
		},
		{"naboo_imperial_tier2_inspect1_spawner", -1500, 1000, 3200, SHIP_AI_RANDOM_PATROL, 60, 120, 25, 50, 100, 300, 1,
			{"mercenary_courier_tier2"}
		},
		{"imperial_patrol_1", 263, 2203, 1703, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 70, 310, 3,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_interceptor_tier1"}
		},
		{"hutt_attack_1", 689, -286, 803, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 64, 80, 380, 3,
			{"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s02_tier1"}
		},
		{"tie_veteran_guard", -2126, 349, 3670, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 10, 100, 400, 3,
			{"imp_tie_bomber_tier1", "imp_tie_fighter_tier1", "imp_tie_interceptor_tier1"}
		},
		{"naboo_rebel_2", -1297, 298, -607, SHIP_AI_RANDOM_PATROL, 60, 120, 64, 128, 100, 450, 3,
			{"imp_tie_bomber_tier1", "imp_tie_fighter_tier1"}
		},
		{"imperial_squad_naboo_4", -85, 2896, 3434, SHIP_AI_FIXED_PATROL, 300, 420, 10, 20, 1,
			5, {"imperial_squad_naboo_4_00", "imperial_squad_naboo_4_01", "imperial_squad_naboo_4_02", "imperial_squad_naboo_4_03", "imperial_squad_naboo_4_04", "imperial_squad_naboo_4_05"},
			{"squad_imperial_naboo_4"}
		},
		{"civ_route_stations", -3102, 1794, 3032, SHIP_AI_FIXED_PATROL, 300, 420, 10, 40, 5,
			5, {"civ_route_stations_00", "civ_route_stations_01", "civ_route_stations_02", "civ_route_stations_03", "civ_route_stations_04", "civ_route_stations_05", "civ_route_stations_06", "civ_route_stations_07", "civ_route_stations_08", "civ_route_stations_09", "civ_route_stations_10", "civ_route_stations_11", "civ_route_stations_12", "civ_route_stations_13", "civ_route_stations_14", "civ_route_stations_15", "civ_route_stations_16", "civ_route_stations_17", "civ_route_stations_18", "civ_route_stations_19", "civ_route_stations_20", "civ_route_stations_21", "civ_route_stations_22", "civ_route_stations_23", "civ_route_stations_24", "civ_route_stations_25", "civ_route_stations_26", "civ_route_stations_27", "civ_route_stations_28", "civ_route_stations_29", "civ_route_stations_30", "civ_route_stations_31", "civ_route_stations_32", "civ_route_stations_33", "civ_route_stations_34", "civ_route_stations_35", "civ_route_stations_36", "civ_route_stations_37", "civ_route_stations_38", "civ_route_stations_39", "civ_route_stations_40"},
			{"civspeeder_naboo", "civspeeder_naboo", "freighterlight_smuggler", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterheavy_tier3_story"}
		},
		{"commerce_route_1", -688, 776, -393, SHIP_AI_FIXED_PATROL, 300, 420, 8, 64, 3,
			5, {"commerce_route_1_00", "commerce_route_1_01", "commerce_route_1_02", "commerce_route_1_03", "commerce_route_1_04"},
			{"freightermedium_tier1", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_tier1", "imp_freighterlight_tier1", "freightermedium_tier1", "imp_freightermedium_tier1", "freighterlight_tier1", "freighterlight_tier1", "freightermedium_tier1"}
		},
	},
}

registerScreenPlay("SpaceNabooSpawner", true)

function SpaceNabooSpawner:start()
	if (not isZoneEnabled(self.spaceZone)) then
		return
	end

	self:populateSpawns()
end
