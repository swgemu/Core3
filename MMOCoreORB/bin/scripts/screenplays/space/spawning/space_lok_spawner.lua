SpaceLokSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceLokSpawner",

	spaceZone = "space_lok",

	shipSpawns = {
		{"nym_gunboat_to_imp", 6427, -6877, -5763, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 1,
			5, {"nym_gunboat_to_imp_00", "nym_gunboat_to_imp_01", "nym_gunboat_to_imp_02", "nym_gunboat_to_imp_03", "nym_gunboat_to_imp_04", "nym_gunboat_to_imp_05", "nym_gunboat_to_imp_06", "nym_gunboat_to_imp_07", "nym_gunboat_to_imp_08", "nym_gunboat_to_imp_09", "nym_gunboat_to_imp_10", "nym_gunboat_to_imp_11", "nym_gunboat_to_imp_12", "nym_gunboat_to_imp_13", "nym_gunboat_to_imp_14", "nym_gunboat_to_imp_15", "nym_gunboat_to_imp_16"},
			{"nym_gunship_tier3"}
		},
		{"nym_fodder_2", 6959, -5822, -6004, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 2,
			{"nym_bomber_tier3"}
		},
		{"nym_asteroid_patrol_1", 5820, -6045, -6201, SHIP_AI_FIXED_PATROL, 30, 60, 10, 30, 3,
			5, {"nym_asteroid_patrol_1_00", "nym_asteroid_patrol_1_01", "nym_asteroid_patrol_1_02", "nym_asteroid_patrol_1_03", "nym_asteroid_patrol_1_04", "nym_asteroid_patrol_1_05", "nym_asteroid_patrol_1_06", "nym_asteroid_patrol_1_07", "nym_asteroid_patrol_1_08", "nym_asteroid_patrol_1_09", "nym_asteroid_patrol_1_10", "nym_asteroid_patrol_1_11", "nym_asteroid_patrol_1_12", "nym_asteroid_patrol_1_13", "nym_asteroid_patrol_1_14", "nym_asteroid_patrol_1_15", "nym_asteroid_patrol_1_16", "nym_asteroid_patrol_1_17", "nym_asteroid_patrol_1_18", "nym_asteroid_patrol_1_19", "nym_asteroid_patrol_1_20", "nym_asteroid_patrol_1_21", "nym_asteroid_patrol_1_22", "nym_asteroid_patrol_1_23", "nym_asteroid_patrol_1_24", "nym_asteroid_patrol_1_25", "nym_asteroid_patrol_1_26", "nym_asteroid_patrol_1_27", "nym_asteroid_patrol_1_28", "nym_asteroid_patrol_1_29"},
			{"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{"debris_rebel_1", 491, -3947, -17, SHIP_AI_RANDOM_PATROL, 300, 420, 10, 10, 50, 400, 1,
			{"squad_xwing_small_average"}
		},
		{"nym_lieutenant_1", -3100, 642, 3067, SHIP_AI_RANDOM_PATROL, 60, 120, 20, 40, 50, 400, 1,
			{"nym_lieutenant_tier2"}
		},
		{"nyms_rebel_run_1", -3216, 955, 3084, SHIP_AI_FIXED_PATROL, 60, 120, 1, 8, 3,
			5, {"nyms_rebel_run_1_00", "nyms_rebel_run_1_01", "nyms_rebel_run_1_02", "nyms_rebel_run_1_03", "nyms_rebel_run_1_04", "nyms_rebel_run_1_05", "nyms_rebel_run_1_06", "nyms_rebel_run_1_07", "nyms_rebel_run_1_08", "nyms_rebel_run_1_09", "nyms_rebel_run_1_10", "nyms_rebel_run_1_11", "nyms_rebel_run_1_12", "nyms_rebel_run_1_13", "nyms_rebel_run_1_14", "nyms_rebel_run_1_15", "nyms_rebel_run_1_16", "nyms_rebel_run_1_17", "nyms_rebel_run_1_18", "nyms_rebel_run_1_19", "nyms_rebel_run_1_20", "nyms_rebel_run_1_21", "nyms_rebel_run_1_22", "nyms_rebel_run_1_23", "nyms_rebel_run_1_24", "nyms_rebel_run_1_25"},
			{"nym_cannon_ship_tier2", "nym_enforcer_tier2", "nym_enforcer_tier3", "nym_fighter_tier2", "nym_star_kimogila_boss", "nym_enforcer_tier3", "nym_enforcer_tier3", "nym_enforcer_tier3", "nym_enforcer_tier3", "nym_enforcer_tier3", "nym_enforcer_tier2", "nym_enforcer_tier2", "nym_enforcer_tier2", "nym_enforcer_tier2", "nym_enforcer_tier2"}
		},
		{"lok_base_guard_1", -3170, 842, 3067, SHIP_AI_RANDOM_PATROL, 60, 20, 20, 40, 50, 400, 2,
			{"nym_cannon_ship_tier2", "nym_enforcer_tier3", "nym_fighter_tier2", "nym_fighter_tier2", "nym_fighter_tier2", "nym_fighter_tier3"}
		},
		{"bloodrazor_static_watch_3", -5254, 5479, 2273, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"bloodrazor_destroyer_tier3"}
		},
		{"bloozrazor_static_spine_2", -1280, 1958, 3786, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"bloodrazor_destroyer_tier3", "bloodrazor_cutthroat_tier3"}
		},
		{"bloodrazor_vs_kimogila_5", 587, 1468, 5966, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"bloodrazor_cutthroat_tier2", "bloodrazor_berzerker_tier2", "bloodrazor_destroyer_tier3"}
		},
		{"kimogila_vs_bloodrazor_5", 533, 1390, 6273, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 2,
			{"kimogila_scrapper_tier2", "kimogila_inciter_tier2", "kimogila_champion_tier3"}
		},
		{"corsair_static_base_5", -240, 3688, 4669, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"corsair_sloop_tier3"}
		},
		{"kimogila_vs_bloodrazor_1", 305, 5182, 5808, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"kimogila_scrapper_tier2", "kimogila_inciter_tier2", "kimogila_champion_tier3"}
		},
		{"bloodrazor_static_watch_2", -2474, -1852, 5003, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"bloodrazor_berzerker_tier2"}
		},
		{"bloodrazor_patrol_1", -5649, -1837, 5976, SHIP_AI_FIXED_PATROL, 30, 60, 10, 20, 3,
			5, {"bloodrazor_patrol_1_00", "bloodrazor_patrol_1_01", "bloodrazor_patrol_1_02", "bloodrazor_patrol_1_03", "bloodrazor_patrol_1_04", "bloodrazor_patrol_1_05", "bloodrazor_patrol_1_06", "bloodrazor_patrol_1_07", "bloodrazor_patrol_1_08", "bloodrazor_patrol_1_09", "bloodrazor_patrol_1_10", "bloodrazor_patrol_1_11", "bloodrazor_patrol_1_12", "bloodrazor_patrol_1_13", "bloodrazor_patrol_1_14"},
			{"bloodrazor_berzerker_tier3", "bloodrazor_cutthroat_tier3"}
		},
		{"bloodrazor_static_3", -4421, 441, 6868, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"bloodrazor_destroyer_tier2", "bloodrazor_cutthroat_tier2"}
		},
		{"bloodrazor_boss", -4737, 5755, 5372, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 3,
			{"bloodrazor_captain_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3"}
		},
		{"bloodrazor_static_watch_4", -6845, 5015, 3354, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"bloodrazor_cutthroat_tier2", "bloodrazor_berzerker_tier2", "bloodrazor_destroyer_tier3"}
		},
		{"bloodrazor_static_watch_1", -5832, 6823, 4644, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"bloodrazor_cutthroat_tier2"}
		},
		{"bloodrazor_patrol_2", -6522, 4280, 6263, SHIP_AI_FIXED_PATROL, 30, 60, 10, 30, 2,
			5, {"bloodrazor_patrol_2_00", "bloodrazor_patrol_2_01", "bloodrazor_patrol_2_02", "bloodrazor_patrol_2_03", "bloodrazor_patrol_2_04", "bloodrazor_patrol_2_05", "bloodrazor_patrol_2_06", "bloodrazor_patrol_2_07", "bloodrazor_patrol_2_08"},
			{"bloodrazor_destroyer_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_berzerker_tier2"}
		},
		{"corsair_static_base_2", 2461, -3943, 6131, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"corsair_raider_tier3"}
		},
		{"kimogila_patrol_1", 5349, 7498, 6604, SHIP_AI_FIXED_PATROL, 30, 60, 10, 30, 4,
			5, {"kimogila_patrol_1_00", "kimogila_patrol_1_01", "kimogila_patrol_1_02", "kimogila_patrol_1_03", "kimogila_patrol_1_04", "kimogila_patrol_1_05", "kimogila_patrol_1_06", "kimogila_patrol_1_07", "kimogila_patrol_1_08", "kimogila_patrol_1_09", "kimogila_patrol_1_10", "kimogila_patrol_1_11", "kimogila_patrol_1_12", "kimogila_patrol_1_13", "kimogila_patrol_1_14", "kimogila_patrol_1_15", "kimogila_patrol_1_16"},
			{"kimogila_scrapper_tier2", "kimogila_inciter_tier3"}
		},
		{"kimogila_battlelord", 6543, 7012, 5471, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"kimogila_battlelord_tier3", "kimogila_champion_tier2", "kimogila_champion_tier2", "kimogila_champion_tier2", "kimogila_champion_tier2", "kimogila_inciter_tier2", "kimogila_inciter_tier2", "kimogila_inciter_tier2", "kimogila_inciter_tier2", "kimogila_scrapper_tier2", "kimogila_scrapper_tier2", "kimogila_scrapper_tier2"}
		},
		{"kimogila_static_3", 3657, 5032, 7486, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"kimogila_scrapper_tier3", "kimogila_champion_tier3"}
		},
		{"corsair_base_static_1", 1677, 4097, 4410, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"corsair_manowar_tier3"}
		},
		{"naboo_privateer_tier3_leg_3_destroy", -2352, 1808, -3496, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 100, 45, 300, 4,
			{"blacksun_marauder_tier2", "blacksun_marauder_tier3"}
		},
		{"kimogila_static_watch_2", 6531, 576, 926, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"kimogila_scrapper_tier2"}
		},
		{"bloozrazor_static_spine_1", 167, 885, 5542, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 2,
			{"bloodrazor_destroyer_tier3", "bloodrazor_cutthroat_tier3"}
		},
		{"trade_fed_base_guard_1", 2820, 252, 2804, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 32, 50, 300, 4,
			{"imp_tie_fighter_tier2", "imp_tie_fighter_tier3"}
		},
		{"trade_fed_route_1", 3058, 249, 3156, SHIP_AI_FIXED_PATROL, 300, 420, 2, 4, 3,
			5, {"trade_fed_route_1_00", "trade_fed_route_1_01", "trade_fed_route_1_02", "trade_fed_route_1_03", "trade_fed_route_1_04", "trade_fed_route_1_05", "trade_fed_route_1_06", "trade_fed_route_1_07", "trade_fed_route_1_08", "trade_fed_route_1_09", "trade_fed_route_1_10", "trade_fed_route_1_11", "trade_fed_route_1_12", "trade_fed_route_1_13", "trade_fed_route_1_14", "trade_fed_route_1_15", "trade_fed_route_1_16", "trade_fed_route_1_17", "trade_fed_route_1_18", "trade_fed_route_1_19", "trade_fed_route_1_20"},
			{"freighterlight_tier3", "freighterlight_tier3", "freighterlight_tier3", "freighterheavy_tier3", "freighterheavy_tier3", "freightermedium_tier3", "freightermedium_tier3", "freightermedium_tier3"}
		},
		{"trade_fed_route_guard_1", 3071, 246, 3151, SHIP_AI_FIXED_PATROL, 60, 120, 4, 6, 3,
			5, {"trade_fed_route_guard_1_00", "trade_fed_route_guard_1_01", "trade_fed_route_guard_1_02", "trade_fed_route_guard_1_03", "trade_fed_route_guard_1_04", "trade_fed_route_guard_1_05", "trade_fed_route_guard_1_06", "trade_fed_route_guard_1_07", "trade_fed_route_guard_1_08", "trade_fed_route_guard_1_09", "trade_fed_route_guard_1_10", "trade_fed_route_guard_1_11", "trade_fed_route_guard_1_12", "trade_fed_route_guard_1_13", "trade_fed_route_guard_1_14", "trade_fed_route_guard_1_15", "trade_fed_route_guard_1_16", "trade_fed_route_guard_1_17", "trade_fed_route_guard_1_18", "trade_fed_route_guard_1_19", "trade_fed_route_guard_1_20", "trade_fed_route_guard_1_21", "trade_fed_route_guard_1_22"},
			{"imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier3"}
		},
		{"yavin_rebel_mission_3", -5150, 2430, 586, SHIP_AI_FIXED_PATROL, 10, 30, 30, 60, 1,
			5, {"yavin_rebel_mission_3_00", "yavin_rebel_mission_3_01", "yavin_rebel_mission_3_02", "yavin_rebel_mission_3_03", "yavin_rebel_mission_3_04"},
			{"squad_yavin_rebel_3", "yavin_mission_3_shuttle"}
		},
		{"imp_guard_hyperspace", -5332, -1477, -6866, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 20, 150, 300, 6,
			{"imp_tie_fighter_tier3", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"static_to_station_1", -6130, -1486, -6667, SHIP_AI_FIXED_PATROL, 300, 420, 10, 20, 3,
			5, {"static_to_station_1_00", "static_to_station_1_01", "static_to_station_1_02", "static_to_station_1_03", "static_to_station_1_04", "static_to_station_1_05", "static_to_station_1_06"},
			{"freighterheavy_tier3_story", "nebula_scientist_researcher_tier3", "smuggler_freighterlight_tier3"}
		},
		{"corsair_nebula_4", 2996, 2032, -2178, SHIP_AI_RANDOM_PATROL, 60, 18, 8, 32, 50, 350, 3,
			{"corsair_behemoth_tier2", "corsair_raider_tier2"}
		},
		{"corsair_nebula_2", 2049, 3681, -1914, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 32, 50, 350, 3,
			{"corsair_raider_tier2", "corsair_sloop_tier2"}
		},
		{"rebel_testing_droid_attack_1", 3063, 4594, -1337, SHIP_AI_FIXED_PATROL, 7200, 10800, 10, 100, 1,
			5, {"rebel_testing_droid_attack_1_00", "rebel_testing_droid_attack_1_01", "rebel_testing_droid_attack_1_02", "rebel_testing_droid_attack_1_03", "rebel_testing_droid_attack_1_04"},
			{"squad_rebel_testing_droids"}
		},
		{"rebel_testing_squad_1", 3016, 2978, -1305, SHIP_AI_RANDOM_PATROL, 300, 420, 1, 150, 50, 300, 1,
			{"squad_bwing_standard_ace"}
		},
		{"kimogila_static_watch_4", 5096, 3, 2093, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"kimogila_champion_tier3"}
		},
		{"nym_fighters_1", 5436, -1865, 1555, SHIP_AI_FIXED_PATROL, 60, 120, 5, 20, 2,
			5, {"nym_fighters_1_00", "nym_fighters_1_01", "nym_fighters_1_02", "nym_fighters_1_03", "nym_fighters_1_04"},
			{"nym_cannon_ship_tier2", "nym_cannon_ship_tier2", "nym_enforcer_tier2", "nym_enforcer_tier2", "nym_lieutenant_tier2"}
		},
		{"imp_vs_nym_2", 6726, -4385, 1371, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 6,
			{"imp_tie_bomber_tier2", "imp_tie_fighter_tier2", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"nym_vs_imp_2", 6436, -4417, 1427, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{"tie_debris_nym_route", 522, -3937, -462, SHIP_AI_FIXED_PATROL, 300, 420, 10, 300, 1,
			5, {"tie_debris_nym_route_00", "tie_debris_nym_route_01", "tie_debris_nym_route_02", "tie_debris_nym_route_03", "tie_debris_nym_route_04", "tie_debris_nym_route_05", "tie_debris_nym_route_06"},
			{"squad_nym_fighter_wing"}
		},
		{"nym_mining_field_route_1", 2190, -7120, -1538, SHIP_AI_FIXED_PATROL, 60, 120, 10, 100, 1,
			5, {"nym_mining_field_route_1_00", "nym_mining_field_route_1_01", "nym_mining_field_route_1_02", "nym_mining_field_route_1_03", "nym_mining_field_route_1_04", "nym_mining_field_route_1_05"},
			{"squad_mining_freighter_nym"}
		},
		{"imp_gunboat_to_nym", 6328, 5949, -214, SHIP_AI_FIXED_PATROL, 60, 120, 10, 30, 1,
			5, {"imp_gunboat_to_nym_00", "imp_gunboat_to_nym_01", "imp_gunboat_to_nym_02", "imp_gunboat_to_nym_03", "imp_gunboat_to_nym_04", "imp_gunboat_to_nym_05", "imp_gunboat_to_nym_06", "imp_gunboat_to_nym_07", "imp_gunboat_to_nym_08", "imp_gunboat_to_nym_09", "imp_gunboat_to_nym_10", "imp_gunboat_to_nym_11", "imp_gunboat_to_nym_12", "imp_gunboat_to_nym_13", "imp_gunboat_to_nym_14", "imp_gunboat_to_nym_15", "imp_gunboat_to_nym_16", "imp_gunboat_to_nym_17", "imp_gunboat_to_nym_18", "imp_gunboat_to_nym_19"},
			{"imp_imperial_gunboat_tier3"}
		},
		{"nym_mining_freighters_1", 2153, -3725, -1491, SHIP_AI_RANDOM_PATROL, 60, 40, 10, 100, 50, 400, 3,
			{"nym_bomber_tier2", "nym_enforcer_tier2"}
		},
		{"nym_mining_field_guard", 2131, -3707, -1471, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 100, 50, 300, 3,
			{"nym_bomber_tier2", "nym_fighter_tier2"}
		},
		{"nym_gunboat_run_1", 5133, -1559, -5413, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 1,
			5, {"nym_gunboat_run_1_00", "nym_gunboat_run_1_01", "nym_gunboat_run_1_02", "nym_gunboat_run_1_03", "nym_gunboat_run_1_04", "nym_gunboat_run_1_05", "nym_gunboat_run_1_06", "nym_gunboat_run_1_07", "nym_gunboat_run_1_08", "nym_gunboat_run_1_09", "nym_gunboat_run_1_10", "nym_gunboat_run_1_11", "nym_gunboat_run_1_12", "nym_gunboat_run_1_13", "nym_gunboat_run_1_14", "nym_gunboat_run_1_15", "nym_gunboat_run_1_16", "nym_gunboat_run_1_17", "nym_gunboat_run_1_18", "nym_gunboat_run_1_19", "nym_gunboat_run_1_20", "nym_gunboat_run_1_21", "nym_gunboat_run_1_22", "nym_gunboat_run_1_23", "nym_gunboat_run_1_24", "nym_gunboat_run_1_25", "nym_gunboat_run_1_26", "nym_gunboat_run_1_27", "nym_gunboat_run_1_28", "nym_gunboat_run_1_29"},
			{"nym_gunship_tier3"}
		},
		{"rebel_guard_route_1", 3670, -2555, -3934, SHIP_AI_FIXED_PATROL, 60, 120, 4, 42, 3,
			5, {"rebel_guard_route_1_00", "rebel_guard_route_1_01", "rebel_guard_route_1_02", "rebel_guard_route_1_03", "rebel_guard_route_1_04", "rebel_guard_route_1_05", "rebel_guard_route_1_06", "rebel_guard_route_1_07", "rebel_guard_route_1_08", "rebel_guard_route_1_09"},
			{"reb_z95_tier3", "reb_xwing_tier3"}
		},
		{"nebulon_rebel_route_1", 3931, -411, -3770, SHIP_AI_FIXED_PATROL, 60, 120, 8, 32, 6,
			5, {"nebulon_rebel_route_1_00", "nebulon_rebel_route_1_01", "nebulon_rebel_route_1_02", "nebulon_rebel_route_1_03", "nebulon_rebel_route_1_04", "nebulon_rebel_route_1_05", "nebulon_rebel_route_1_06", "nebulon_rebel_route_1_07", "nebulon_rebel_route_1_08", "nebulon_rebel_route_1_09"},
			{"reb_awing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_z95_tier3"}
		},
		{"rebel_equipment_route_1", 2033, -2311, -3680, SHIP_AI_FIXED_PATROL, 300, 420, 2, 4, 3,
			5, {"rebel_equipment_route_1_00", "rebel_equipment_route_1_01", "rebel_equipment_route_1_02", "rebel_equipment_route_1_03", "rebel_equipment_route_1_04", "rebel_equipment_route_1_05", "rebel_equipment_route_1_06", "rebel_equipment_route_1_07", "rebel_equipment_route_1_08", "rebel_equipment_route_1_09", "rebel_equipment_route_1_10", "rebel_equipment_route_1_11", "rebel_equipment_route_1_12", "rebel_equipment_route_1_13", "rebel_equipment_route_1_14", "rebel_equipment_route_1_15", "rebel_equipment_route_1_16", "rebel_equipment_route_1_17", "rebel_equipment_route_1_18", "rebel_equipment_route_1_19", "rebel_equipment_route_1_20"},
			{"reb_xwing_tier2", "reb_ywing_tier2", "reb_ywing_tier3", "reb_freightermedium_tier3", "reb_freighterlight_tier3", "reb_freighterlight_tier3", "reb_freighterheavy_tier3"}
		},
		{"rebel_outpost_guard_1", 1811, -2167, -3456, SHIP_AI_RANDOM_PATROL, 60, 120, 20, 40, 50, 300, 3,
			{"reb_z95_tier2", "reb_z95_tier3"}
		},
		{"corsair_nebula_patrol_1", 3078, -645, -2264, SHIP_AI_FIXED_PATROL, 60, 120, 8, 64, 2,
			5, {"corsair_nebula_patrol_1_00", "corsair_nebula_patrol_1_01", "corsair_nebula_patrol_1_02", "corsair_nebula_patrol_1_03", "corsair_nebula_patrol_1_04", "corsair_nebula_patrol_1_05", "corsair_nebula_patrol_1_06", "corsair_nebula_patrol_1_07"},
			{"corsair_behemoth_tier3"}
		},
		{"nyms_boys", 3719, -2284, -1151, SHIP_AI_FIXED_PATROL, 60, 120, 30, 45, 3,
			5, {"nyms_boys_00", "nyms_boys_01", "nyms_boys_02", "nyms_boys_03", "nyms_boys_04", "nyms_boys_05", "nyms_boys_06"},
			{"nym_cannon_ship_tier2", "nym_enforcer_tier3"}
		},
		{"kimogila_vs_bloodrazor_4", -3095, 3631, 3774, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 2,
			{"kimogila_scrapper_tier2", "kimogila_inciter_tier2", "kimogila_champion_tier3"}
		},
		{"bloodrazor_static_4", -1839, 6481, 3316, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"bloodrazor_berzerker_tier3", "bloodrazor_destroyer_tier3"}
		},
		{"bloodrazor_vs_kimogila_2", -562, 6191, 1836, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"bloodrazor_cutthroat_tier2", "bloodrazor_berzerker_tier3", "bloodrazor_destroyer_tier2"}
		},
		{"erkon_the_vile", 3047, 7029, 1403, SHIP_AI_RANDOM_PATROL, 86400, 172800, 1, 30, 400, 3000, 1,
			{"erkon_the_vile"}
		},
		{"kimogila_static_1", 4380, 4967, 5546, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"kimogila_champion_tier3", "kimogila_scrapper_tier2", "kimogila_inciter_tier2"}
		},
		{"kimogila_static_watch_1", 5655, 2680, 3481, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"kimogila_champion_tier3"}
		},
		{"bloodrazor_vs_kimogila_4", -3253, -1988, 3894, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"bloodrazor_cutthroat_tier2", "bloodrazor_berzerker_tier2", "bloodrazor_destroyer_tier3"}
		},
		{"vortex_mission_1_shuttle", -3745, -3124, -658, SHIP_AI_FIXED_PATROL, 10, 30, 30, 50, 1,
			5, {"vortex_mission_1_shuttle_00", "vortex_mission_1_shuttle_01", "vortex_mission_1_shuttle_02", "vortex_mission_1_shuttle_03", "vortex_mission_1_shuttle_04", "vortex_mission_1_shuttle_05", "vortex_mission_1_shuttle_06", "vortex_mission_1_shuttle_07"},
			{"vortex_mission_1_shuttle"}
		},
		{"nym_lieutenant_lokstation_spawner", -6364, -5296, 1432, SHIP_AI_FIXED_PATROL, 30, 45, 10, 15, 1,
			5, {"nym_lieutenant_lokstation_spawner_00", "nym_lieutenant_lokstation_spawner_01", "nym_lieutenant_lokstation_spawner_02", "nym_lieutenant_lokstation_spawner_03"},
			{"nym_lieutenant_tier2"}
		},
		{"nym_fodder_1", 7016, -5554, -4957, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 20, 150, 300, 2,
			{"nym_bomber_tier3", "nym_enforcer_tier3"}
		},
		{"imp_vs_nym_3", 6016, -5694, -2817, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 350, 6,
			{"imp_tie_fighter_tier2", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"nym_vs_imp_3", 6107, -5789, -3058, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 350, 4,
			{"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{"imp_vs_nym_4", 5948, -6901, 224, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 6,
			{"imp_tie_fighter_tier2", "imp_tie_bomber_tier2", "imp_tie_advanced_tier2", "imp_tie_aggressor_tier2", "imp_tie_interceptor_tier2", "imp_tie_oppressor_tier2"}
		},
		{"nym_vs_imp_4", 5764, -7026, -231, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 20, 150, 300, 2,
			{"nym_enforcer_tier2"}
		},
		{"nym_vs_imperial_1", 4999, -4746, -556, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{"imp_vs_nym_1", 4940, -4509, -205, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 6,
			{"imp_tie_fighter_tier3", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"nym_static_beacon_1", 2560, -4878, -4120, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{"nym_trade_attack_1", 711, -4072, 2409, SHIP_AI_FIXED_PATROL, 60, 120, 40, 80, 3,
			5, {"nym_trade_attack_1_00", "nym_trade_attack_1_01", "nym_trade_attack_1_02", "nym_trade_attack_1_03", "nym_trade_attack_1_04", "nym_trade_attack_1_05", "nym_trade_attack_1_06"},
			{"nym_bomber_tier2", "nym_fighter_tier2", "nym_fighter_tier2", "nym_fighter_tier2", "nym_fighter_tier2", "nym_fighter_tier2"}
		},
		{"kimogila_vs_bloodrazor_2", -233, 1695, 1799, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"kimogila_scrapper_tier2", "kimogila_inciter_tier2", "kimogila_champion_tier3"}
		},
		{"nym_lieutenant_2", 729, -843, 2438, SHIP_AI_FIXED_PATROL, 60, 120, 30, 50, 1,
			5, {"nym_lieutenant_2_00", "nym_lieutenant_2_01", "nym_lieutenant_2_02", "nym_lieutenant_2_03", "nym_lieutenant_2_04", "nym_lieutenant_2_05"},
			{"nym_lieutenant_tier2"}
		},
		{"nym_static_beacon_2", -77, -2347, -1573, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{"imperial_patrol_1", -1531, 3202, 325, SHIP_AI_FIXED_PATROL, 60, 120, 20, 40, 3,
			5, {"imperial_patrol_1_00", "imperial_patrol_1_01", "imperial_patrol_1_02", "imperial_patrol_1_03", "imperial_patrol_1_04", "imperial_patrol_1_05", "imperial_patrol_1_06", "imperial_patrol_1_07", "imperial_patrol_1_08", "imperial_patrol_1_09", "imperial_patrol_1_10", "imperial_patrol_1_11", "imperial_patrol_1_12", "imperial_patrol_1_13"},
			{"imp_tie_fighter_tier3", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3"}
		},
		{"imperial_outpost_guard_1", -1553, 2866, 206, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 40, 100, 400, 6,
			{"imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier2", "imp_tie_advanced_tier2", "imp_tie_aggressor_tier2", "imp_tie_oppressor_tier2"}
		},
		{"tie_investigation_route_1", -1486, 2057, 360, SHIP_AI_FIXED_PATROL, 300, 420, 10, 150, 2,
			5, {"tie_investigation_route_1_00", "tie_investigation_route_1_01", "tie_investigation_route_1_02", "tie_investigation_route_1_03", "tie_investigation_route_1_04", "tie_investigation_route_1_05"},
			{"squad_tie_standard_average"}
		},
		{"viopa_rebel_1_shuttle", 2102, 1022, 2191, SHIP_AI_FIXED_PATROL, 10, 30, 10, 100, 1,
			5, {"viopa_rebel_1_shuttle_00", "viopa_rebel_1_shuttle_01", "viopa_rebel_1_shuttle_02", "viopa_rebel_1_shuttle_03"},
			{"squad_viopa_rebel_1"}
		},
		{"rebel_vs_corsair_1", 1782, -205, 2312, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 4,
			{"reb_xwing_tier3", "reb_xwing_tier3", "reb_ywing_tier2", "reb_z95_tier2"}
		},
		{"corsair_vs_rebel_1", 1932, -231, 2208, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 2,
			{"corsair_raider_tier3", "corsair_manowar_tier3"}
		},
		{"rebel_testing_droid_squad_2", 3008, 1166, -1275, SHIP_AI_FIXED_PATROL, 7200, 10800, 10, 100, 1,
			5, {"rebel_testing_droid_squad_2_00", "rebel_testing_droid_squad_2_01", "rebel_testing_droid_squad_2_02", "rebel_testing_droid_squad_2_03", "rebel_testing_droid_squad_2_04"},
			{"squad_rebel_testing_droids", "rebel_droid_training_boss"}
		},
		{"nym_lieutenant_3", 39, -134, -2666, SHIP_AI_FIXED_PATROL, 60, 120, 30, 80, 1,
			5, {"nym_lieutenant_3_00", "nym_lieutenant_3_01", "nym_lieutenant_3_02", "nym_lieutenant_3_03", "nym_lieutenant_3_04"},
			{"nym_lieutenant_tier2"}
		},
		{"nym_corsair_attack_1", 65, -86, -2637, SHIP_AI_FIXED_PATROL, 60, 120, 50, 80, 3,
			5, {"nym_corsair_attack_1_00", "nym_corsair_attack_1_01", "nym_corsair_attack_1_02", "nym_corsair_attack_1_03", "nym_corsair_attack_1_04"},
			{"nym_bomber_tier2", "nym_enforcer_tier2", "nym_enforcer_tier3"}
		},
		{"corsair_nebula_1", 1777, -34, -2495, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 32, 50, 350, 3,
			{"corsair_sloop_tier3"}
		},
		{"corsair_nebula_3", 2476, 2016, -1465, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 32, 50, 350, 4,
			{"corsair_manowar_tier2", "corsair_raider_tier2", "corsair_shadowstalker", "corsair_manowar_tier2", "corsair_manowar_tier2", "corsair_manowar_tier2", "corsair_manowar_tier2", "corsair_raider_tier2", "corsair_raider_tier2", "corsair_raider_tier2"}
		},
		{"trade_fed_research_static_1", -1110, -4204, -2888, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 4,
			{"trade_fed_fighter", "trade_fed_bomber"}
		},
		{"trade_fed_static_base", -636, -4091, -6175, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"trade_fed_fighter", "trade_fed_bomber"}
		},
		{"trade_fed_research_static_2", 335, -4091, -3621, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 3,
			{"trade_fed_fighter", "trade_fed_bomber"}
		},
		{"trade_fed_research_freighters", -1714, -4228, -5813, SHIP_AI_FIXED_PATROL, 420, 520, 10, 15, 4,
			5, {"trade_fed_research_freighters_00", "trade_fed_research_freighters_01", "trade_fed_research_freighters_02", "trade_fed_research_freighters_03", "trade_fed_research_freighters_04", "trade_fed_research_freighters_05", "trade_fed_research_freighters_06", "trade_fed_research_freighters_07", "trade_fed_research_freighters_08", "trade_fed_research_freighters_09", "trade_fed_research_freighters_10", "trade_fed_research_freighters_11", "trade_fed_research_freighters_12", "trade_fed_research_freighters_13", "trade_fed_research_freighters_14", "trade_fed_research_freighters_15", "trade_fed_research_freighters_16"},
			{"naboo_miner_transport", "nebula_scientist_researcher_tier3"}
		},
		{"trade_fed_station_patrol", -1756, -4207, -5108, SHIP_AI_FIXED_PATROL, 30, 60, 10, 30, 3,
			5, {"trade_fed_station_patrol_00", "trade_fed_station_patrol_01", "trade_fed_station_patrol_02", "trade_fed_station_patrol_03", "trade_fed_station_patrol_04", "trade_fed_station_patrol_05", "trade_fed_station_patrol_06", "trade_fed_station_patrol_07", "trade_fed_station_patrol_08", "trade_fed_station_patrol_09", "trade_fed_station_patrol_10", "trade_fed_station_patrol_11", "trade_fed_station_patrol_12", "trade_fed_station_patrol_13", "trade_fed_station_patrol_14"},
			{"trade_fed_fighter", "trade_fed_bomber"}
		},
	},
}

registerScreenPlay("SpaceLokSpawner", true)

function SpaceLokSpawner:start()
	if (not isZoneEnabled(self.spaceZone)) then
		return
	end

	self:populateSpawns()
end
