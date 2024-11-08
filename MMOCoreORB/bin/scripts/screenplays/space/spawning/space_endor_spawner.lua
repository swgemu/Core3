SpaceEndorSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceEndorSpawner",

	spaceZone = "space_endor",

	shipSpawns = {
		{"freighter_mission_dudes_1", 3569, -482, -2421, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 90, 380, 3,
			{"mining_guard_ship_tier3", "mining_guard_ship_tier3"}
		},
		{"freighter_mission_dudes_1_inspect", 3571, -480, -2419, SHIP_AI_RANDOM_PATROL, 45, 90, 40, 80, 90, 380, 1,
			{"freighterheavy_tier4_inspect"}
		},
		{"corellia_imperial_tier3_leg_4_destroy_xwing", 4200, -1200, -1200, SHIP_AI_RANDOM_PATROL, 180, 300, 25, 50, 100, 300, 3,
			{"reb_xwing_tier4"}
		},
		{"artisan_peacekeeper_1", -6914, -6495, 214, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 300, 3,
			{"endor_artisan_peacekeeper_tier4", "endor_artisan_peacekeeper_tier4_endor"}
		},
		{"artisan_to_trader_1", -6986, -6675, 271, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 3,
			5, {"artisan_to_trader_1_00", "artisan_to_trader_1_01", "artisan_to_trader_1_02", "artisan_to_trader_1_03"},
			{"endor_artisan_diplomat_boss", "endor_artisan_diplomat_tier4", "endor_artisan_diplomat_tier4", "endor_artisan_diplomat_tier4", "endor_artisan_diplomat_tier4_endor", "endor_artisan_diplomat_tier4_endor", "endor_artisan_diplomat_tier4_endor", "endor_artisan_diplomat_tier4_endor", "endor_artisan_diplomat_tier4_endor"}
		},
		{"artisan_to_station_1", -7035, -6614, 495, SHIP_AI_FIXED_PATROL, 300, 420, 20, 40, 3,
			5, {"artisan_to_station_1_00", "artisan_to_station_1_01", "artisan_to_station_1_02", "artisan_to_station_1_03", "artisan_to_station_1_04", "artisan_to_station_1_05"},
			{"endor_artisan_freighter_tier4", "endor_artisan_freighter_tier4_endor", "freighterheavy_tier3_story", "freighterheavy_tier3_story"}
		},
		{"imperial_secret_station_guard_3", 6425, -6352, 6847, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 100, 300, 600, 1,
			{"squad_tie_aggressor_ace"}
		},
		{"imperial_secret_station_guard_2", 5640, -7076, 7041, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 100, 300, 600, 2,
			{"squad_tie_mix_ace"}
		},
		{"imperial_secret_station_guard_1", 6109, -5905, 6350, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 100, 300, 600, 2,
			{"squad_tie_mix_ace"}
		},
		{"imperial_death_squad", 5957, -6209, 6618, SHIP_AI_FIXED_PATROL, 3600, 7200, 20, 40, 1,
			5, {"imperial_death_squad_00", "imperial_death_squad_01", "imperial_death_squad_02", "imperial_death_squad_03", "imperial_death_squad_04", "imperial_death_squad_05", "imperial_death_squad_06", "imperial_death_squad_07", "imperial_death_squad_08", "imperial_death_squad_09", "imperial_death_squad_10", "imperial_death_squad_11", "imperial_death_squad_12", "imperial_death_squad_13", "imperial_death_squad_14", "imperial_death_squad_15", "imperial_death_squad_16", "imperial_death_squad_17", "imperial_death_squad_18", "imperial_death_squad_19", "imperial_death_squad_20", "imperial_death_squad_21", "imperial_death_squad_22", "imperial_death_squad_23"},
			{"squad_imperial_fleet"}
		},
		{"droid_guards_route_1", -5354, 1575, -1107, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 3,
			{"junk_droid_fighter"}
		},
		{"droid_engineer_1", -4619, 2631, -2037, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 4,
			5, {"droid_engineer_1_00", "droid_engineer_1_01", "droid_engineer_1_02", "droid_engineer_1_03", "droid_engineer_1_04", "droid_engineer_1_05"},
			{"junk_droid_engineer"}
		},
		{"hutt_smuggler_02", 4730, -2531, -3607, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 200, 200, 600, 5,
			{"hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "hutt_pirate_s02_tier3", "huttsmuggler", "huttsmuggler", "huttsmuggler"}
		},
		{"tatooine_imperial_tier3_rebscout_spawner", -2450, -3052, 1234, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 50, 100, 600, 1,
			{"rebel_scout_fighter_tier3"}
		},
		{"generator_imperial_defense_a", 6253, 7311, -6096, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 60, 320, 3,
			{"imp_tie_aggressor_tier4", "imp_tie_advanced_tier4", "imp_tie_aggressor_tier4"}
		},
		{"hutt_smuggler_01", 4249, 2899, 3799, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 200, 200, 700, 5,
			{"hutt_bomber_s02_tier3", "hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "huttsmuggler", "huttsmuggler", "huttsmuggler"}
		},
		{"rebel_generator_defense_3", 1501, 6494, 4192, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 50, 300, 3,
			{"reb_bwing_boss", "reb_xwing_tier4", "reb_xwing_tier4", "reb_xwing_tier4", "reb_xwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4", "reb_ywing_tier4", "reb_ywing_tier4", "reb_ywing_tier4", "reb_ywing_tier4"}
		},
		{"tatooine_imperial_tier3_destroy2_spawner", 1207, 4306, 3989, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 50, 100, 300, 6,
			{"reb_awing_tier4", "reb_bwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4", "rebel_raider_bomber_tier3", "rebel_raider_captain_tier3", "rebel_raider_fast_attack_tier3"}
		},
		{"tatooine_imperial_tier3_inspect4escort", 1897, 6480, 1174, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 50, 100, 300, 6,
			{"reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4", "reb_z95_tier4", "reb_z95_tier4", "reb_z95_tier4"}
		},
		{"tatooine_imperial_tier3_inspect4_spawner", 2000, 6500, 1200, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 50, 100, 400, 1,
			{"rebel_command_shuttle_tier4"}
		},
		{"naboo_imperial_tier3_inspect3escort", 6102, -6988, -1069, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 400, 5,
			{"reb_xwing_tier3", "reb_z95_tier3", "reb_ywing_tier3"}
		},
		{"tatooine_imperial_tier3_inspect3_spawner", 6009, -7001, -1095, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 50, 100, 400, 1,
			{"rebel_scout_shuttle_tier3"}
		},
		{"spice_pirates_defend_1", 4620, -6158, -447, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 4,
			{"spice_pirate_fighter_tier4"}
		},
		{"blacklight_base_defense", 5740, -3589, 1121, SHIP_AI_FIXED_PATROL, 180, 300, 20, 30, 4,
			5, {"blacklight_base_defense_00", "blacklight_base_defense_01", "blacklight_base_defense_02", "blacklight_base_defense_03", "blacklight_base_defense_04", "blacklight_base_defense_05", "blacklight_base_defense_06", "blacklight_base_defense_07", "blacklight_base_defense_08", "blacklight_base_defense_09", "blacklight_base_defense_10", "blacklight_base_defense_11", "blacklight_base_defense_12", "blacklight_base_defense_13", "blacklight_base_defense_14", "blacklight_base_defense_15", "blacklight_base_defense_16", "blacklight_base_defense_17", "blacklight_base_defense_18", "blacklight_base_defense_19", "blacklight_base_defense_20", "blacklight_base_defense_21"},
			{"blacklight_assassin_tier4", "blacklight_assassin_tier4", "blacklight_assassin_tier4", "blacklight_bomber_tier4", "blacklight_bomber_tier4", "blacklight_bomber_tier4", "blacklight_fighter_tier4", "blacklight_fighter_tier4", "blacklight_fighter_tier4", "blacklight_leader_tier5"}
		},
		{"spice_pirate_astroid_route_1", 6435, -7024, -2, SHIP_AI_FIXED_PATROL, 300, 420, 40, 80, 4,
			5, {"spice_pirate_astroid_route_1_00", "spice_pirate_astroid_route_1_01", "spice_pirate_astroid_route_1_02", "spice_pirate_astroid_route_1_03", "spice_pirate_astroid_route_1_04", "spice_pirate_astroid_route_1_05", "spice_pirate_astroid_route_1_06", "spice_pirate_astroid_route_1_07", "spice_pirate_astroid_route_1_08", "spice_pirate_astroid_route_1_09", "spice_pirate_astroid_route_1_10", "spice_pirate_astroid_route_1_11", "spice_pirate_astroid_route_1_12", "spice_pirate_astroid_route_1_13", "spice_pirate_astroid_route_1_14", "spice_pirate_astroid_route_1_15", "spice_pirate_astroid_route_1_16"},
			{"spice_pirate_fighter_tier4", "spice_pirate_transport_tier4", "spice_pirate_boss", "spice_pirate_fighter_tier4", "spice_pirate_fighter_tier4", "spice_pirate_fighter_tier4", "spice_pirate_fighter_tier4", "spice_pirate_fighter_tier4", "spice_pirate_transport_tier4", "spice_pirate_transport_tier4", "spice_pirate_transport_tier4", "spice_pirate_transport_tier4"}
		},
		{"spice_to_generator_1", 6356, -7061, 2, SHIP_AI_FIXED_PATROL, 300, 420, 40, 80, 5,
			5, {"spice_to_generator_1_00", "spice_to_generator_1_01", "spice_to_generator_1_02", "spice_to_generator_1_03", "spice_to_generator_1_04", "spice_to_generator_1_05", "spice_to_generator_1_06", "spice_to_generator_1_07", "spice_to_generator_1_08", "spice_to_generator_1_09"},
			{"spice_pirate_spy_tier4", "spice_pirate_transport_tier4"}
		},
		{"scientist_lookout_2", 4861, -2763, 6701, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 90, 300, 4,
			{"nebula_scientist_bodyguard_tier4", "nebula_scientist_lookout_tier4"}
		},
		{"scientist_lookout_1", 538, -1108, 4026, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 90, 300, 4,
			{"nebula_scientist_bodyguard_tier4", "nebula_scientist_lookout_tier4"}
		},
		{"scientist_operation_4", 1275, -2910, 6983, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 3,
			5, {"scientist_operation_4_00", "scientist_operation_4_01", "scientist_operation_4_02", "scientist_operation_4_03"},
			{"nebula_scientist_analyst_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_bodyguard_boss", "nebula_scientist_bodyguard_tier4", "nebula_scientist_bodyguard_tier4", "nebula_scientist_bodyguard_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_analyst_tier4", "nebula_scientist_analyst_tier4", "nebula_scientist_analyst_tier4", "nebula_scientist_analyst_tier4", "nebula_scientist_analyst_tier4", "nebula_scientist_analyst_tier4"}
		},
		{"generator_imperial_defense_b", 6138, 6738, -6077, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 60, 320, 3,
			{"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4"}
		},
		{"rebel_spies_1", -7378, -1321, 6649, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 160, 6,
			{"reb_bwing_tier4", "reb_xwing_tier4", "reb_z95_tier4", "reb_ywing_tier4", "reb_awing_tier4"}
		},
		{"rebel_spy_nebulon_guard", -6624, -1310, 7333, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 160, 4,
			{"reb_bwing_tier4", "reb_xwing_tier4", "reb_awing_tier4", "reb_z95_tier4", "reb_ywing_tier4"}
		},
		{"rebel_generator_defense_2", -3581, 2443, 4804, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 50, 300, 4,
			{"reb_awing_tier4", "reb_bwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4"}
		},
		{"rebel_generator_defense_1", -3506, 2756, 4747, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 50, 300, 6,
			{"reb_awing_tier4", "reb_bwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4"}
		},
		{"tatooine_imperial_tier3_inspect2escort", -5003, 4079, 6079, SHIP_AI_RANDOM_PATROL, 180, 300, 25, 50, 100, 300, 6,
			{"reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4", "reb_z95_tier4", "reb_z95_tier4"}
		},
		{"tatooine_imperial_tier3_inspect2_spawner", -5009, 4104, 6001, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 100, 400, 6,
			{"rebel_scout_fighter_tier3"}
		},
		{"traders_station_route_1", 5802, -1527, -4659, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 3,
			5, {"traders_station_route_1_00", "traders_station_route_1_01", "traders_station_route_1_02", "traders_station_route_1_03", "traders_station_route_1_04", "traders_station_route_1_05", "traders_station_route_1_06", "traders_station_route_1_07", "traders_station_route_1_08"},
			{"endor_trader_bodyguard_hire"}
		},
		{"imperial_base_defense_1", -5395, -661, -5101, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 70, 340, 6,
			{"imp_tie_advanced_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_aggressor_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_base_defense_3", -5848, -4070, -6499, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 70, 340, 6,
			{"imp_tie_aggressor_tier4", "imp_tie_fighter_tier4", "imp_tie_oppressor_tier4", "imp_tie_advanced_tier4", "imp_tie_bomber_tier4", "imp_tie_interceptor_tier4"}
		},
		{"imperial_base_defense_2", -4681, -1795, -6620, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 70, 340, 6,
			{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_base_patrol_1", -5321, -1892, -5100, SHIP_AI_FIXED_PATROL, 180, 300, 10, 30, 7,
			5, {"imperial_base_patrol_1_00", "imperial_base_patrol_1_01", "imperial_base_patrol_1_02", "imperial_base_patrol_1_03", "imperial_base_patrol_1_04", "imperial_base_patrol_1_05", "imperial_base_patrol_1_06", "imperial_base_patrol_1_07", "imperial_base_patrol_1_08", "imperial_base_patrol_1_09", "imperial_base_patrol_1_10", "imperial_base_patrol_1_11", "imperial_base_patrol_1_12", "imperial_base_patrol_1_13", "imperial_base_patrol_1_14", "imperial_base_patrol_1_15", "imperial_base_patrol_1_16", "imperial_base_patrol_1_17", "imperial_base_patrol_1_18", "imperial_base_patrol_1_19", "imperial_base_patrol_1_20", "imperial_base_patrol_1_21", "imperial_base_patrol_1_22", "imperial_base_patrol_1_23", "imperial_base_patrol_1_24", "imperial_base_patrol_1_25", "imperial_base_patrol_1_26", "imperial_base_patrol_1_27", "imperial_base_patrol_1_28", "imperial_base_patrol_1_29", "imperial_base_patrol_1_30", "imperial_base_patrol_1_31", "imperial_base_patrol_1_32", "imperial_base_patrol_1_33", "imperial_base_patrol_1_34", "imperial_base_patrol_1_35", "imperial_base_patrol_1_36", "imperial_base_patrol_1_37", "imperial_base_patrol_1_38", "imperial_base_patrol_1_39", "imperial_base_patrol_1_40", "imperial_base_patrol_1_41"},
			{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"}
		},
		{"imperial_to_scientist_route", -5453, -2115, -5079, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 7,
			5, {"imperial_to_scientist_route_00", "imperial_to_scientist_route_01", "imperial_to_scientist_route_02", "imperial_to_scientist_route_03", "imperial_to_scientist_route_04", "imperial_to_scientist_route_05", "imperial_to_scientist_route_06", "imperial_to_scientist_route_07", "imperial_to_scientist_route_08", "imperial_to_scientist_route_09", "imperial_to_scientist_route_10", "imperial_to_scientist_route_11", "imperial_to_scientist_route_12"},
			{"imperial_scout", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_base_to_generator", -4779, -1875, -5083, SHIP_AI_FIXED_PATROL, 600, 720, 20, 40, 5,
			5, {"imperial_base_to_generator_00", "imperial_base_to_generator_01", "imperial_base_to_generator_02", "imperial_base_to_generator_03", "imperial_base_to_generator_04", "imperial_base_to_generator_05", "imperial_base_to_generator_06", "imperial_base_to_generator_07", "imperial_base_to_generator_08", "imperial_base_to_generator_09", "imperial_base_to_generator_10", "imperial_base_to_generator_11", "imperial_base_to_generator_12", "imperial_base_to_generator_13", "imperial_base_to_generator_14", "imperial_base_to_generator_15", "imperial_base_to_generator_16", "imperial_base_to_generator_17", "imperial_base_to_generator_18", "imperial_base_to_generator_19", "imperial_base_to_generator_20", "imperial_base_to_generator_21", "imperial_base_to_generator_22", "imperial_base_to_generator_23"},
			{"imp_decimator_tier4", "imp_imperial_gunboat_tier4", "imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_base_defense_4", -7532, -2631, -4793, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 70, 340, 6,
			{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4", "imp_tie_bomber_tier4", "imp_tie_advanced_tier4", "imp_tie_aggressor_tier4"}
		},
		{"trade_to_station_1", -2520, -5051, 280, SHIP_AI_FIXED_PATROL, 300, 420, 20, 40, 3,
			5, {"trade_to_station_1_00", "trade_to_station_1_01", "trade_to_station_1_02", "trade_to_station_1_03", "trade_to_station_1_04", "trade_to_station_1_05", "trade_to_station_1_06", "trade_to_station_1_07"},
			{"endor_trader_freighter"}
		},
		{"tatooine_imperial_tier3_destroy1_spawner", -3250, -4500, -1200, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 60, 100, 300, 6,
			{"reb_awing_tier4", "reb_bwing_tier4", "rebel_raider_bomber_tier3", "rebel_raider_captain_tier3", "reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4"}
		},
		{"trader_mercenaries_1", -2927, -5157, 411, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 4,
			5, {"trader_mercenaries_1_00", "trader_mercenaries_1_01", "trader_mercenaries_1_02", "trader_mercenaries_1_03", "trader_mercenaries_1_04", "trader_mercenaries_1_05", "trader_mercenaries_1_06", "trader_mercenaries_1_07", "trader_mercenaries_1_08", "trader_mercenaries_1_09", "trader_mercenaries_1_10", "trader_mercenaries_1_11", "trader_mercenaries_1_12", "trader_mercenaries_1_13"},
			{"endor_trader_mercenary", "endor_trader_bodyguard_boss", "endor_trader_bodyguard_hire", "endor_trader_bodyguard_hire", "endor_trader_bodyguard_hire", "endor_trader_bodyguard_hire", "endor_trader_mercenary", "endor_trader_mercenary", "endor_trader_mercenary", "endor_trader_mercenary", "endor_trader_bodyguard_hire"}
		},
		{"trader_guards_2", -2933, -5459, 590, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 300, 3,
			{"endor_trader_bodyguard_hire"}
		},
		{"trader_to_artisan_1", -3032, -5318, 717, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 3,
			5, {"trader_to_artisan_1_00", "trader_to_artisan_1_01", "trader_to_artisan_1_02", "trader_to_artisan_1_03", "trader_to_artisan_1_04"},
			{"endor_trader_collector"}
		},
		{"death_watch_patrol_2", 1751, -6843, -6369, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 300, 3,
			{"death_watch_assassin_tier4", "death_watch_eradicator_tier4"}
		},
		{"death_watch_patrol_1", 2639, -6807, -5925, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 4,
			5, {"death_watch_patrol_1_00", "death_watch_patrol_1_01", "death_watch_patrol_1_02", "death_watch_patrol_1_03", "death_watch_patrol_1_04", "death_watch_patrol_1_05", "death_watch_patrol_1_06", "death_watch_patrol_1_07", "death_watch_patrol_1_08", "death_watch_patrol_1_09", "death_watch_patrol_1_10", "death_watch_patrol_1_11", "death_watch_patrol_1_12", "death_watch_patrol_1_13", "death_watch_patrol_1_14", "death_watch_patrol_1_15", "death_watch_patrol_1_16"},
			{"death_watch_assassin_tier4", "death_watch_eradicator_tier4", "death_watch_prowler_tier4", "death_watch_boss", "death_watch_prowler_tier4", "death_watch_prowler_tier4", "death_watch_prowler_tier4", "death_watch_prowler_tier4", "death_watch_eradicator_tier4", "death_watch_eradicator_tier4", "death_watch_eradicator_tier4", "death_watch_eradicator_tier4", "death_watch_assassin_tier4", "death_watch_assassin_tier4", "death_watch_assassin_tier4", "death_watch_assassin_tier4"}
		},
		{"death_watch_guards_1", 2343, -7485, -7246, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 100, 350, 3,
			{"death_watch_prowler_tier4", "death_watch_eradicator_tier4", "death_watch_assassin_tier4"}
		},
		{"corellia_imperial_tier3_leg_3_destroy_aces", -5313, -5183, 2462, SHIP_AI_RANDOM_PATROL, 180, 300, 25, 50, 100, 300, 6,
			{"reb_awing_tier4", "reb_bwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4"}
		},
		{"droid_guards_2", -6063, 276, -553, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 3,
			{"junk_droid_fighter"}
		},
		{"droid_guards_1", -6929, 278, 26, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 4,
			{"junk_droid_fighter"}
		},
		{"droid_to_junk_1", -6444, 259, -279, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 3,
			5, {"droid_to_junk_1_00", "droid_to_junk_1_01", "droid_to_junk_1_02", "droid_to_junk_1_03", "droid_to_junk_1_04", "droid_to_junk_1_05", "droid_to_junk_1_06", "droid_to_junk_1_07", "droid_to_junk_1_08"},
			{"junk_droid_scavenger", "junk_droid_fighter_boss", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger"}
		},
		{"endor_smuggler_transport_1", -798, 3814, -812, SHIP_AI_FIXED_PATROL, 350, 650, 20, 40, 3,
			5, {"endor_smuggler_transport_1_00", "endor_smuggler_transport_1_01", "endor_smuggler_transport_1_02", "endor_smuggler_transport_1_03", "endor_smuggler_transport_1_04", "endor_smuggler_transport_1_05", "endor_smuggler_transport_1_06", "endor_smuggler_transport_1_07", "endor_smuggler_transport_1_08", "endor_smuggler_transport_1_09", "endor_smuggler_transport_1_10"},
			{"endor_smuggler_transport"}
		},
		{"smuggler_guards_1", -818, 3863, -913, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 300, 3,
			{"endor_smuggler_fighter"}
		},
		{"corellia_imperial_tier3_leg_3_destroy_bwing", -1500, 5000, -2430, SHIP_AI_RANDOM_PATROL, 180, 300, 25, 50, 100, 300, 6,
			{"reb_bwing_tier4"}
		},
		{"smuggler_fighter_guards_1", -1905, 3818, -1292, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 80, 300, 3,
			{"endor_smuggler_fighter"}
		},
		{"hutt_smuggler_route", -4266, 3939, -3918, SHIP_AI_FIXED_PATROL, 30, 60, 10, 100, 3,
			5, {"hutt_smuggler_route_00", "hutt_smuggler_route_01", "hutt_smuggler_route_02", "hutt_smuggler_route_03", "hutt_smuggler_route_04", "hutt_smuggler_route_05", "hutt_smuggler_route_06", "hutt_smuggler_route_07"},
			{"hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "hutt_pirate_s02_tier3", "huttsmuggler", "huttsmuggler", "huttsmuggler", "huttsmuggler"}
		},
		{"hutt_smuggler_guard", -3934, 3798, -3808, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 100, 100, 300, 2,
			{"hutt_pirate_s02_tier3", "hutt_pirate_s02_tier3", "hutt_bomber_s02_tier3"}
		},
		{"blacksun_mission_dudes_1", -728, -1862, -5638, SHIP_AI_RANDOM_PATROL, 180, 300, 50, 100, 90, 380, 6,
			{"blacksun_ace_s04_tier4", "blacksun_aggressor_tier4", "blacksun_bomber_s03_tier4", "blacksun_fighter_s03_tier4", "blacksun_marauder_tier4", "blacksun_vehement_tier4"}
		},
		{"imperial_satellite_defense", -3432, -2837, -3695, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 50, 300, 3,
			{"imp_tie_bomber_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"tatooine_imperial_tier4_endscout1", -3606, -2695, -3771, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 100, 50, 400, 1,
			{"rebel_endscout_tier4"}
		},
		{"imperial_star_defender_5", -6453, 7433, 4018, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 4,
			{"imp_tie_aggressor_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_astroid_destroy_1", -5612, 7359, 4175, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 20, 80, 360, 1,
			{"imperial_demolition"}
		},
		{"imperial_astroid_demo_1", -7445, 6821, 3689, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 20, 80, 360, 1,
			{"imperial_demolition"}
		},
		{"imperial_star_defender_3", -4109, 7131, 3757, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 4,
			{"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_cargo_to_junk", -5019, 6550, 2419, SHIP_AI_FIXED_PATROL, 180, 350, 10, 15, 3,
			5, {"imperial_cargo_to_junk_00", "imperial_cargo_to_junk_01", "imperial_cargo_to_junk_02", "imperial_cargo_to_junk_03", "imperial_cargo_to_junk_04", "imperial_cargo_to_junk_05", "imperial_cargo_to_junk_06", "imperial_cargo_to_junk_07", "imperial_cargo_to_junk_08", "imperial_cargo_to_junk_09", "imperial_cargo_to_junk_10", "imperial_cargo_to_junk_11"},
			{"imperial_cargo_tower"}
		},
		{"imperial_collector_n_engineer_1", -5141, 6454, 2274, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 4,
			5, {"imperial_collector_n_engineer_1_00", "imperial_collector_n_engineer_1_01", "imperial_collector_n_engineer_1_02", "imperial_collector_n_engineer_1_03", "imperial_collector_n_engineer_1_04", "imperial_collector_n_engineer_1_05", "imperial_collector_n_engineer_1_06", "imperial_collector_n_engineer_1_07", "imperial_collector_n_engineer_1_08", "imperial_collector_n_engineer_1_09", "imperial_collector_n_engineer_1_10", "imperial_collector_n_engineer_1_11", "imperial_collector_n_engineer_1_12", "imperial_collector_n_engineer_1_13", "imperial_collector_n_engineer_1_14", "imperial_collector_n_engineer_1_15", "imperial_collector_n_engineer_1_16"},
			{"imperial_debris_collector", "imperial_engineer"}
		},
		{"imperial_astroid_demo_2", -6618, 7359, 2054, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 20, 80, 360, 1,
			{"imperial_demolition"}
		},
		{"imperial_demolition_1", -5199, 6548, 2453, SHIP_AI_FIXED_PATROL, 180, 300, 20, 40, 3,
			5, {"imperial_demolition_1_00", "imperial_demolition_1_01", "imperial_demolition_1_02", "imperial_demolition_1_03", "imperial_demolition_1_04", "imperial_demolition_1_05", "imperial_demolition_1_06", "imperial_demolition_1_07", "imperial_demolition_1_08", "imperial_demolition_1_09", "imperial_demolition_1_10", "imperial_demolition_1_11"},
			{"imperial_demolition"}
		},
		{"imperial_debris_collector_1", -5195, 6642, 2287, SHIP_AI_FIXED_PATROL, 300, 420, 20, 40, 4,
			5, {"imperial_debris_collector_1_00", "imperial_debris_collector_1_01", "imperial_debris_collector_1_02", "imperial_debris_collector_1_03", "imperial_debris_collector_1_04", "imperial_debris_collector_1_05", "imperial_debris_collector_1_06", "imperial_debris_collector_1_07", "imperial_debris_collector_1_08", "imperial_debris_collector_1_09", "imperial_debris_collector_1_10", "imperial_debris_collector_1_11", "imperial_debris_collector_1_12", "imperial_debris_collector_1_13", "imperial_debris_collector_1_14", "imperial_debris_collector_1_15", "imperial_debris_collector_1_16"},
			{"imperial_debris_collector", "imp_decimator_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_star_defender_6", -6179, 6889, 2161, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 4,
			{"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_star_defender_2", -1978, 7153, 2331, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 4,
			{"imp_tie_aggressor_tier4", "imp_tie_fighter_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_star_guards_1", -3205, 6234, 957, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 4,
			{"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_junk_guard_1", -4832, 4513, -602, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 3,
			{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_junk_guard_2", -5518, 4725, -537, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 3,
			{"imp_tie_advanced_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4"}
		},
		{"spice_pirates_defend_3", 1990, -5150, 2922, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 4,
			{"spice_pirate_fighter_tier4"}
		},
		{"imperial_trade_route_gaurd_1", -421, -5113, 2145, SHIP_AI_FIXED_PATROL, 300, 420, 20, 40, 4,
			5, {"imperial_trade_route_gaurd_1_00", "imperial_trade_route_gaurd_1_01", "imperial_trade_route_gaurd_1_02", "imperial_trade_route_gaurd_1_03", "imperial_trade_route_gaurd_1_04", "imperial_trade_route_gaurd_1_05", "imperial_trade_route_gaurd_1_06", "imperial_trade_route_gaurd_1_07", "imperial_trade_route_gaurd_1_08", "imperial_trade_route_gaurd_1_09", "imperial_trade_route_gaurd_1_10", "imperial_trade_route_gaurd_1_11", "imperial_trade_route_gaurd_1_12", "imperial_trade_route_gaurd_1_13", "imperial_trade_route_gaurd_1_14", "imperial_trade_route_gaurd_1_15"},
			{"imp_decimator_tier4", "imp_tie_advanced_tier4", "imp_tie_oppressor_tier4"}
		},
		{"trader_fighter_guards_1", -2062, -5676, 567, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 300, 3,
			{"endor_trader_bodyguard_hire"}
		},
		{"spice_pirates_defend_2", 1062, -4727, -953, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 80, 360, 4,
			{"spice_pirate_fighter_tier4"}
		},
		{"spice_defenders_1", 2084, -5135, 481, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 100, 300, 4,
			{"spice_pirate_fighter_tier4"}
		},
		{"generator_to_spice_base_1", 2067, -5512, 462, SHIP_AI_FIXED_PATROL, 300, 420, 20, 40, 3,
			5, {"generator_to_spice_base_1_00", "generator_to_spice_base_1_01", "generator_to_spice_base_1_02", "generator_to_spice_base_1_03", "generator_to_spice_base_1_04"},
			{"spice_pirate_transport_tier4"}
		},
		{"scientist_lookout_4", -1029, 989, 278, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 90, 300, 4,
			{"nebula_scientist_bodyguard_tier4", "nebula_scientist_lookout_tier4"}
		},
		{"scientist_lookout_3", 635, 2847, 601, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 90, 300, 4,
			{"nebula_scientist_bodyguard_tier4", "nebula_scientist_lookout_tier4"}
		},
		{"corellia_privateer_tier3_inspect_spawner", 1317, -455, -2876, SHIP_AI_FIXED_PATROL, 10, 20, 10, 100, 3,
			5, {"corellia_privateer_tier3_inspect_spawner_00", "corellia_privateer_tier3_inspect_spawner_01"},
			{"evil_raider_tyrant_tier3"}
		},
		{"stn_endor_spynet_inspect_1", 251, 6, -1973, SHIP_AI_GUARD_PATROL, 45, 90, 150, 200, 300, 750, 1,
			{"spynet_watcher_tier3"}
		},
		{"imperial_generator_defense_2", -655, -2005, -202, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 50, 300, 4,
			{"imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"}
		},
		{"imperial_generator_defense_1", -791, -2202, -96, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 30, 50, 300, 4,
			{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"scientist_operation_2", 563, 989, 1179, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 3,
			5, {"scientist_operation_2_00", "scientist_operation_2_01", "scientist_operation_2_02", "scientist_operation_2_03"},
			{"nebula_scientist_analyst_tier4", "nebula_scientist_researcher_tier4"}
		},
		{"scientist_operation_guard_1", 400, 1020, 1160, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 90, 300, 4,
			{"nebula_scientist_bodyguard_tier4"}
		},
		{"scientist_operation_guard_2", -630, 1120, 1370, SHIP_AI_RANDOM_PATROL, 180, 300, 40, 80, 90, 300, 4,
			{"nebula_scientist_bodyguard_tier4"}
		},
		{"scientist_operation_1", -1147, 1105, 1493, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 3,
			5, {"scientist_operation_1_00", "scientist_operation_1_01", "scientist_operation_1_02", "scientist_operation_1_03", "scientist_operation_1_04", "scientist_operation_1_05", "scientist_operation_1_06", "scientist_operation_1_07", "scientist_operation_1_08"},
			{"nebula_scientist_analyst_tier4", "nebula_scientist_researcher_tier4"}
		},
		{"scientists_route_1", 608, -423, 2569, SHIP_AI_FIXED_PATROL, 180, 300, 40, 80, 6,
			5, {"scientists_route_1_00", "scientists_route_1_01", "scientists_route_1_02", "scientists_route_1_03", "scientists_route_1_04", "scientists_route_1_05", "scientists_route_1_06", "scientists_route_1_07", "scientists_route_1_08", "scientists_route_1_09", "scientists_route_1_10", "scientists_route_1_11", "scientists_route_1_12", "scientists_route_1_13", "scientists_route_1_14", "scientists_route_1_15", "scientists_route_1_16", "scientists_route_1_17", "scientists_route_1_18", "scientists_route_1_19", "scientists_route_1_20", "scientists_route_1_21", "scientists_route_1_22"},
			{"nebula_scientist_analyst_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_bodyguard_tier4"}
		},
	},
}

registerScreenPlay("SpaceEndorSpawner", true)

function SpaceEndorSpawner:start()
	if (not isZoneEnabled(self.spaceZone)) then
		return
	end

	self:populateSpawns()
end