SpaceYavin4Spawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceYavin4Spawner",

	spaceZone = "space_yavin4",

	shipSpawns = {
		{"imperial_tie_hyper1_patrol4", 3686, 1552, 3339, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 400, 6,
			{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier3", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"imperial_tie_hyper1_patrol1", 3413, -92, 3462, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 50, 400, 6,
			{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier3", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3"}
		},
		{"imperial_supply_route_1", 3490, 73, 3514, SHIP_AI_FIXED_PATROL, 60, 120, 10, 15, 2,
			5, {"imperial_supply_route_1_00", "imperial_supply_route_1_01", "imperial_supply_route_1_02", "imperial_supply_route_1_03", "imperial_supply_route_1_04", "imperial_supply_route_1_05", "imperial_supply_route_1_06"},
			{"imp_freighterlight_tier3", "imp_tie_fighter_tier3", "imp_freighterheavy_tier3", "imp_freightermedium_tier3"}
		},
		{"hutt_asteroid_patrol2", 2829, -4794, 1393, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 350, 3,
			{"hutt_bomber_s02_tier2", "hutt_fighter_s01_tier2"}
		},
		{"hutt_asteroid_patrol", 2428, -5996, 1259, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 200, 300, 3,
			{"hutt_bomber_s01_tier2", "hutt_fighter_s01_tier2", "hutt_heavy_s01_tier3"}
		},
		{"imperial_squad_1", -6904, 4998, 6054, SHIP_AI_FIXED_PATROL, 7200, 10800, 5, 10, 1,
			5, {"imperial_squad_1_00", "imperial_squad_1_01", "imperial_squad_1_02", "imperial_squad_1_03", "imperial_squad_1_04", "imperial_squad_1_05", "imperial_squad_1_06", "imperial_squad_1_07"},
			{"squad_imperial_fleet"}
		},
		{"rebel_defenders_4", -6331, 3387, 787, SHIP_AI_RANDOM_PATROL, 60, 120, 20, 40, 80, 360, 6,
			{"rebel_raider_fast_attack_tier3", "reb_z95_tier3", "reb_ywing_tier3", "reb_bwing_tier3", "reb_awing_tier3", "reb_xwing_tier3"}
		},
		{"nice_mining_path_a", -507, -5392, -6678, SHIP_AI_FIXED_PATROL, 60, 120, 10, 30, 5,
			5, {"nice_mining_path_a_00", "nice_mining_path_a_01", "nice_mining_path_a_02", "nice_mining_path_a_03", "nice_mining_path_a_04"},
			{"nebula_scientist_researcher_tier3", "junk_dealer_trader", "junk_dealer_collector"}
		},
		{"rebel_gun_boat_1", -5845, -1069, 840, SHIP_AI_FIXED_PATROL, 3600, 240, 5, 10, 1,
			5, {"rebel_gun_boat_1_00", "rebel_gun_boat_1_01", "rebel_gun_boat_1_02", "rebel_gun_boat_1_03", "rebel_gun_boat_1_04", "rebel_gun_boat_1_05", "rebel_gun_boat_1_06", "rebel_gun_boat_1_07", "rebel_gun_boat_1_08", "rebel_gun_boat_1_09", "rebel_gun_boat_1_10", "rebel_gun_boat_1_11", "rebel_gun_boat_1_12", "rebel_gun_boat_1_13"},
			{"squad_rebel_gunboat_tier3"}
		},
		{"rebel_raider_captain_2", -6200, -5408, -781, SHIP_AI_RANDOM_PATROL, 500, 1000, 20, 40, 80, 160, 4,
			{"rebel_raider_captain_tier3", "reb_z95_tier3", "reb_xwing_tier3", "reb_bwing_tier3", "reb_awing_tier3"}
		},
		{"corellian_corvette_1", -6209, -5296, -525, SHIP_AI_FIXED_PATROL, 3600, 5400, 10, 20, 1,
			5, {"corellian_corvette_1_00", "corellian_corvette_1_01", "corellian_corvette_1_02", "corellian_corvette_1_03", "corellian_corvette_1_04", "corellian_corvette_1_05"},
			{"squad_rebel_gunboat_tier3"}
		},
		{"rebel_route_2", -2199, -5552, -4680, SHIP_AI_FIXED_PATROL, 120, 240, 10, 15, 5,
			5, {"rebel_route_2_00", "rebel_route_2_01", "rebel_route_2_02", "rebel_route_2_03", "rebel_route_2_04", "rebel_route_2_05", "rebel_route_2_06"},
			{"reb_awing_boss", "reb_awing_tier2", "reb_xwing_tier2", "reb_xwing_tier2", "reb_xwing_tier2", "reb_xwing_tier2", "reb_xwing_tier2", "reb_xwing_tier2", "reb_ywing_tier2", "reb_ywing_tier2", "reb_ywing_tier2", "reb_ywing_tier2", "reb_ywing_tier2"}
		},
		{"hutt_patrol_two", -1767, -5975, 5177, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 50, 300, 3,
			{"hutt_bomber_s01_tier2", "hutt_pirate_s01_tier2"}
		},
		{"tier3_vylukh_rally_bravo", 1722, -3078, 2985, SHIP_AI_GUARD_PATROL, 60, 120, 14, 48, 100, 312, 3,
			{"vylukh_clan_elite_tier2", "vylukh_clan_transport_tier2", "vylukh_clan_soldier_tier2"}
		},
		{"hutt_asteroid_1", -2279, -4901, 4912, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 300, 3,
			{"hutt_bomber_s02_tier2", "hutt_fighter_s02_tier2"}
		},
		{"massassi_inspect_spawner_02", -332, -2348, 6768, SHIP_AI_RANDOM_PATROL, 30, 45, 10, 50, 100, 350, 1,
			{"massassi_damaged_fighter_tier2"}
		},
		{"imp_vs_smugglers_2", 1126, -3034, 4869, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 3,
			{"imp_tie_bomber_tier2", "imp_tie_fighter_tier3"}
		},
		{"smugglers_vs_imperial_2", 1287, -2610, 4834, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 3,
			{"debris_smuggler_bomber_tier3", "debris_smuggler_fighter_tier3"}
		},
		{"massassi_inspect_spawner_01", -6156, -4044, 3712, SHIP_AI_RANDOM_PATROL, 30, 45, 10, 50, 100, 350, 1,
			{"massassi_damaged_fighter_tier2"}
		},
		{"tatooine_imperial_tier2_inspect_rebagent", -3200, -3000, 6000, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 500, 6,
			{"reb_xwing_tier2", "rebel_agent_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_z95_tier3", "reb_bwing_tier3", "reb_awing_tier3"}
		},
		{"imperial_station_lambda_patrol", -3686, -5547, 4127, SHIP_AI_FIXED_PATROL, 60, 120, 10, 15, 3,
			5, {"imperial_station_lambda_patrol_00", "imperial_station_lambda_patrol_01", "imperial_station_lambda_patrol_02", "imperial_station_lambda_patrol_03", "imperial_station_lambda_patrol_04", "imperial_station_lambda_patrol_05", "imperial_station_lambda_patrol_06", "imperial_station_lambda_patrol_07", "imperial_station_lambda_patrol_08", "imperial_station_lambda_patrol_09", "imperial_station_lambda_patrol_10", "imperial_station_lambda_patrol_11", "imperial_station_lambda_patrol_12", "imperial_station_lambda_patrol_13"},
			{"imp_lambda_shuttle_tier3", "imp_tie_bomber_tier2", "imp_tie_fighter_tier3"}
		},
		{"corellia_imperial_tier3_officerinspect", -2000, -4500, 3000, SHIP_AI_RANDOM_PATROL, 30, 60, 25, 50, 200, 400, 1,
			{"reb_yavinspy_tier4"}
		},
		{"corellia_imperial_tier3_guard", -1933, -3975, 3055, SHIP_AI_RANDOM_PATROL, 60, 120, 25, 50, 200, 400, 3,
			{"reb_awing_tier3", "reb_bwing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_ywing_tier3"}
		},
		{"smuggler_debris_route_gaurd_2", 3438, 4640, 4017, SHIP_AI_RANDOM_PATROL, 60, 120, 5, 10, 80, 300, 2,
			{"debris_smuggler_fighter_tier3"}
		},
		{"imperial_spies_1", 4224, 6624, 6928, SHIP_AI_RANDOM_PATROL, 60, 120, 5, 10, 50, 300, 6,
			{"imp_tie_advanced_tier3", "imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier3", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"smuggler_route_guard_1", 4269, 6896, 5947, SHIP_AI_RANDOM_PATROL, 60, 120, 5, 10, 80, 300, 3,
			{"debris_smuggler_fighter_tier2"}
		},
		{"smugglers_patrol_2", 3746, 5511, 3220, SHIP_AI_FIXED_PATROL, 60, 120, 20, 40, 2,
			5, {"smugglers_patrol_2_00", "smugglers_patrol_2_01", "smugglers_patrol_2_02", "smugglers_patrol_2_03", "smugglers_patrol_2_04", "smugglers_patrol_2_05", "smugglers_patrol_2_06", "smugglers_patrol_2_07"},
			{"debris_smuggler_bomber_tier3"}
		},
		{"rebel_defenders_3", -5119, 4160, 353, SHIP_AI_RANDOM_PATROL, 60, 120, 20, 40, 100, 350, 6,
			{"reb_xwing_tier2", "reb_z95_tier2", "reb_z95_tier3", "reb_ywing_tier3", "reb_xwing_tier3", "reb_bwing_tier3", "reb_awing_tier3"}
		},
		{"rebel_defenders_2", -4749, 7136, 484, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 100, 350, 6,
			{"reb_xwing_tier2", "reb_z95_tier2", "reb_xwing_tier3", "reb_z95_tier3", "reb_ywing_tier3", "reb_bwing_tier3", "reb_awing_tier3"}
		},
		{"rebel_xwing_guard_1", 2945, 4201, 5113, SHIP_AI_GUARD_PATROL, 60, 120, 10, 50, 100, 400, 6,
			{"reb_awing_tier2", "reb_xwing_tier2", "reb_ywing_tier2", "reb_awing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_z95_tier3"}
		},
		{"yavin_rebel_2_shuttle", 1405, 2111, 4328, SHIP_AI_FIXED_PATROL, 10, 60, 30, 60, 1,
			5, {"yavin_rebel_2_shuttle_00", "yavin_rebel_2_shuttle_01", "yavin_rebel_2_shuttle_02", "yavin_rebel_2_shuttle_03", "yavin_rebel_2_shuttle_04"},
			{"yavin_mission_2_shuttle"}
		},
		{"imperial_vs_smugglers_1", -283, -257, 4778, SHIP_AI_FIXED_PATROL, 420, 620, 10, 20, 4,
			5, {"imperial_vs_smugglers_1_00", "imperial_vs_smugglers_1_01", "imperial_vs_smugglers_1_02", "imperial_vs_smugglers_1_03", "imperial_vs_smugglers_1_04", "imperial_vs_smugglers_1_05", "imperial_vs_smugglers_1_06", "imperial_vs_smugglers_1_07", "imperial_vs_smugglers_1_08", "imperial_vs_smugglers_1_09", "imperial_vs_smugglers_1_10", "imperial_vs_smugglers_1_11", "imperial_vs_smugglers_1_12", "imperial_vs_smugglers_1_13", "imperial_vs_smugglers_1_14", "imperial_vs_smugglers_1_15", "imperial_vs_smugglers_1_16", "imperial_vs_smugglers_1_17", "imperial_vs_smugglers_1_18", "imperial_vs_smugglers_1_19"},
			{"imp_imperial_gunboat_tier3"}
		},
		{"rebel_vs_imp_1", -847, 3766, 3922, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 6,
			{"reb_awing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_z95_tier3"}
		},
		{"imp_vs_rebel_1", -729, 3894, 4042, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 4,
			{"imp_tie_bomber_tier2", "imp_tie_fighter_tier3"}
		},
		{"imp_gunboat_to_rebel_1", -425, 4930, 5028, SHIP_AI_FIXED_PATROL, 30, 120, 10, 30, 1,
			5, {"imp_gunboat_to_rebel_1_00", "imp_gunboat_to_rebel_1_01", "imp_gunboat_to_rebel_1_02", "imp_gunboat_to_rebel_1_03", "imp_gunboat_to_rebel_1_04", "imp_gunboat_to_rebel_1_05", "imp_gunboat_to_rebel_1_06", "imp_gunboat_to_rebel_1_07", "imp_gunboat_to_rebel_1_08", "imp_gunboat_to_rebel_1_09", "imp_gunboat_to_rebel_1_10", "imp_gunboat_to_rebel_1_11", "imp_gunboat_to_rebel_1_12", "imp_gunboat_to_rebel_1_13", "imp_gunboat_to_rebel_1_14", "imp_gunboat_to_rebel_1_15"},
			{"imp_imperial_gunboat_tier2"}
		},
		{"blockade_run_general_1", -2826, 4197, 750, SHIP_AI_FIXED_PATROL, 300, 420, 20, 40, 3,
			5, {"blockade_run_general_1_00", "blockade_run_general_1_01", "blockade_run_general_1_02", "blockade_run_general_1_03", "blockade_run_general_1_04", "blockade_run_general_1_05", "blockade_run_general_1_06", "blockade_run_general_1_07", "blockade_run_general_1_08", "blockade_run_general_1_09", "blockade_run_general_1_10", "blockade_run_general_1_11", "blockade_run_general_1_12", "blockade_run_general_1_13", "blockade_run_general_1_14", "blockade_run_general_1_15", "blockade_run_general_1_16", "blockade_run_general_1_17", "blockade_run_general_1_18", "blockade_run_general_1_19", "blockade_run_general_1_20", "blockade_run_general_1_21", "blockade_run_general_1_22", "blockade_run_general_1_23", "blockade_run_general_1_24", "blockade_run_general_1_25"},
			{"reb_bwing_tier2", "reb_freighterheavy_tier3", "reb_freighterlight_tier3", "reb_freighterlight_tier3", "reb_freightermedium_tier3", "reb_xwing_tier2", "reb_ywing_tier2", "reb_ykl37r_tier2", "reb_z95_tier2", "rebel_smuggler_tier3"}
		},
		{"smugglers_run_1", 2261, 3918, -3860, SHIP_AI_FIXED_PATROL, 60, 120, 6, 10, 6,
			5, {"smugglers_run_1_00", "smugglers_run_1_01", "smugglers_run_1_02", "smugglers_run_1_03", "smugglers_run_1_04", "smugglers_run_1_05", "smugglers_run_1_06", "smugglers_run_1_07", "smugglers_run_1_08", "smugglers_run_1_09", "smugglers_run_1_10", "smugglers_run_1_11", "smugglers_run_1_12", "smugglers_run_1_13", "smugglers_run_1_14", "smugglers_run_1_15", "smugglers_run_1_16", "smugglers_run_1_17", "smugglers_run_1_18", "smugglers_run_1_19", "smugglers_run_1_20", "smugglers_run_1_21", "smugglers_run_1_22", "smugglers_run_1_23", "smugglers_run_1_24", "smugglers_run_1_25", "smugglers_run_1_26", "smugglers_run_1_27", "smugglers_run_1_28", "smugglers_run_1_29", "smugglers_run_1_30", "smugglers_run_1_31", "smugglers_run_1_32", "smugglers_run_1_33", "smugglers_run_1_34", "smugglers_run_1_35", "smugglers_run_1_36", "smugglers_run_1_37", "smugglers_run_1_38", "smugglers_run_1_39"},
			{"blacksun_vehement_tier2", "blacksun_marauder_tier2", "hidden_daggers_nebula_stalker_tier2", "huttfighter_tier3", "hutt_fighter_s01_tier2", "hutt_bomber_s01_tier2", "nym_enforcer_tier2", "nym_gunship_tier2"}
		},
		{"blockade_run_corvette_1", -2197, 5884, -3691, SHIP_AI_FIXED_PATROL, 7200, 10800, 30, 200, 1,
			5, {"blockade_run_corvette_1_00", "blockade_run_corvette_1_01", "blockade_run_corvette_1_02", "blockade_run_corvette_1_03", "blockade_run_corvette_1_04", "blockade_run_corvette_1_05", "blockade_run_corvette_1_06"},
			{"reb_xwing_tier3", "reb_ykl37r_tier2", "reb_ywing_tier2"}
		},
		{"rebel_raider_captain_1", -5129, -2267, -373, SHIP_AI_RANDOM_PATROL, 500, 1000, 10, 20, 80, 160, 6,
			{"rebel_raider_captain_tier3", "reb_z95_tier3", "reb_ywing_tier3", "reb_xwing_tier3", "reb_awing_tier3", "reb_bwing_tier3"}
		},
		{"corellia_imperial_tier3_leg_2_inspect", -3754, 325, -4456, SHIP_AI_RANDOM_PATROL, 60, 120, 45, 90, 200, 260, 1,
			{"neutral_freighter"}
		},
		{"rebel_defenders_1", -5536, 6083, 136, SHIP_AI_RANDOM_PATROL, 60, 120, 20, 40, 100, 350, 6,
			{"rebel_raider_bomber_tier3", "reb_ywing_tier3", "reb_xwing_tier3", "reb_bwing_tier3", "reb_awing_tier3"}
		},
		{"hutt_guards_2", 3581, -5979, -1756, SHIP_AI_RANDOM_PATROL, 60, 120, 20, 40, 80, 300, 3,
			{"hutt_bomber_s01_tier2", "hutt_fighter_s01_tier2", "hutt_pirate_s01_tier2"}
		},
		{"smuggler_to_debris_astroid_1", 7226, 5186, 3488, SHIP_AI_FIXED_PATROL, 60, 120, 5, 10, 2,
			5, {"smuggler_to_debris_astroid_1_00", "smuggler_to_debris_astroid_1_01", "smuggler_to_debris_astroid_1_02", "smuggler_to_debris_astroid_1_03", "smuggler_to_debris_astroid_1_04", "smuggler_to_debris_astroid_1_05", "smuggler_to_debris_astroid_1_06", "smuggler_to_debris_astroid_1_07", "smuggler_to_debris_astroid_1_08", "smuggler_to_debris_astroid_1_09", "smuggler_to_debris_astroid_1_10", "smuggler_to_debris_astroid_1_11"},
			{"debris_smuggler_collector_tier3"}
		},
		{"smuggler_guards_3", 5115, 5598, 3353, SHIP_AI_RANDOM_PATROL, 60, 120, 20, 40, 80, 360, 3,
			{"debris_smuggler_bomber_tier3", "debris_smuggler_fighter_tier2"}
		},
		{"debris_collector", 5839, 5429, 3360, SHIP_AI_FIXED_PATROL, 60, 120, 20, 40, 4,
			5, {"debris_collector_00", "debris_collector_01", "debris_collector_02", "debris_collector_03", "debris_collector_04", "debris_collector_05", "debris_collector_06", "debris_collector_07", "debris_collector_08", "debris_collector_09", "debris_collector_10", "debris_collector_11"},
			{"debris_smuggler_collector_tier3", "debris_smuggler_fighter_tier3"}
		},
		{"smuggler_base_1", 7238, 6647, 3462, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 4,
			5, {"smuggler_base_1_00", "smuggler_base_1_01", "smuggler_base_1_02", "smuggler_base_1_03", "smuggler_base_1_04", "smuggler_base_1_05", "smuggler_base_1_06", "smuggler_base_1_07", "smuggler_base_1_08", "smuggler_base_1_09", "smuggler_base_1_10"},
			{"debris_smuggler_fighter_tier3"}
		},
		{"imperial_tie_hyper1_patrol3", 3292, -787, 5141, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 400, 6,
			{"imp_tie_bomber_tier2", "imp_tie_fighter_tier3", "imp_tie_interceptor_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"yavin4_to_station_1", -4852, -6144, -5023, SHIP_AI_FIXED_PATROL, 400, 850, 10, 20, 2,
			5, {"yavin4_to_station_1_00", "yavin4_to_station_1_01", "yavin4_to_station_1_02"},
			{"freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_tier3"}
		},
		{"debris_communication_inspect_spawner_01", -5984, -496, 2880, SHIP_AI_RANDOM_PATROL, 30, 45, 10, 50, 100, 350, 1,
			{"deathstar_debris_communication_tier2"}
		},
		{"imperial_station_tie_three", -3600, 743, 4443, SHIP_AI_GUARD_PATROL, 60, 120, 10, 50, 50, 400, 6,
			{"imp_tie_bomber_tier2", "imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"imperail_station_tie_spawner2", -3810, 2137, 4579, SHIP_AI_GUARD_PATROL, 60, 120, 10, 50, 50, 400, 4,
			{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2"}
		},
		{"imperial_station_salvage_spawner", -3739, 1508, 4498, SHIP_AI_FIXED_PATROL, 60, 120, 10, 15, 2,
			5, {"imperial_station_salvage_spawner_00", "imperial_station_salvage_spawner_01", "imperial_station_salvage_spawner_02", "imperial_station_salvage_spawner_03", "imperial_station_salvage_spawner_04", "imperial_station_salvage_spawner_05", "imperial_station_salvage_spawner_06", "imperial_station_salvage_spawner_07", "imperial_station_salvage_spawner_08", "imperial_station_salvage_spawner_09", "imperial_station_salvage_spawner_10", "imperial_station_salvage_spawner_11", "imperial_station_salvage_spawner_12", "imperial_station_salvage_spawner_13", "imperial_station_salvage_spawner_14", "imperial_station_salvage_spawner_15", "imperial_station_salvage_spawner_16", "imperial_station_salvage_spawner_17"},
			{"imp_freighterlight_tier3"}
		},
		{"imperial_station_tie_patrol", -4662, 1508, 4278, SHIP_AI_FIXED_PATROL, 60, 120, 10, 25, 6,
			5, {"imperial_station_tie_patrol_00", "imperial_station_tie_patrol_01", "imperial_station_tie_patrol_02", "imperial_station_tie_patrol_03", "imperial_station_tie_patrol_04", "imperial_station_tie_patrol_05"},
			{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_oppressor_tier3", "imp_tie_interceptor_tier3"}
		},
		{"imp_vs_reb_3", -2201, 1364, 3657, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 3,
			{"imp_tie_bomber_tier2", "imp_tie_fighter_tier3"}
		},
		{"rebel_vs_imp_3", -2081, 1546, 3814, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 6,
			{"reb_awing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_z95_tier3"}
		},
		{"freighters_2", 240, -5299, -6160, SHIP_AI_FIXED_PATROL, 300, 420, 10, 20, 2,
			5, {"freighters_2_00", "freighters_2_01", "freighters_2_02", "freighters_2_03", "freighters_2_04", "freighters_2_05"},
			{"freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_tier3"}
		},
		{"naboo_imperial_tier3_shinssyacht_spawner", 3196, -6203, -5010, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 50, 100, 600, 1,
			{"shinss_yacht_tier3"}
		},
		{"smuggler_astroid_route_1", 7552, 3812, 2736, SHIP_AI_FIXED_PATROL, 60, 120, 5, 15, 4,
			5, {"smuggler_astroid_route_1_00", "smuggler_astroid_route_1_01", "smuggler_astroid_route_1_02", "smuggler_astroid_route_1_03", "smuggler_astroid_route_1_04", "smuggler_astroid_route_1_05", "smuggler_astroid_route_1_06", "smuggler_astroid_route_1_07", "smuggler_astroid_route_1_08", "smuggler_astroid_route_1_09", "smuggler_astroid_route_1_10", "smuggler_astroid_route_1_11", "smuggler_astroid_route_1_12", "smuggler_astroid_route_1_13", "smuggler_astroid_route_1_14", "smuggler_astroid_route_1_15"},
			{"debris_smuggler_fighter_tier3"}
		},
		{"smuggler_outpost_1", 6267, 1604, -3, SHIP_AI_FIXED_PATROL, 60, 120, 20, 40, 4,
			5, {"smuggler_outpost_1_00", "smuggler_outpost_1_01", "smuggler_outpost_1_02", "smuggler_outpost_1_03", "smuggler_outpost_1_04", "smuggler_outpost_1_05", "smuggler_outpost_1_06", "smuggler_outpost_1_07", "smuggler_outpost_1_08"},
			{"debris_smuggler_fighter_tier3", "debris_smuggler_boss", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3"}
		},
		{"smuggler_transport_1", 6096, 1635, 25, SHIP_AI_FIXED_PATROL, 500, 1000, 10, 15, 2,
			5, {"smuggler_transport_1_00", "smuggler_transport_1_01", "smuggler_transport_1_02"},
			{"debris_smuggler_transport_tier3"}
		},
		{"rebel_xwing_hyper1_patrol1", 4239, -1265, 4275, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 400, 6,
			{"reb_awing_tier2", "reb_awing_tier2", "reb_awing_tier2", "reb_bwing_tier3", "reb_xwing_tier2", "reb_ywing_tier2", "reb_awing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_z95_tier3"}
		},
		{"imperial_tie_hyper1_patrol2", 4348, -572, 3857, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 400, 6,
			{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"naboo_imperial_tier3_inspect1_spawner", 5000, -2300, 1020, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 50, 100, 400, 1,
			{"mercenary_spy_fighter_tier4"}
		},
		{"smugglers_vs_imp_3", 4717, -4614, 2198, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 4,
			{"debris_smuggler_bomber_tier3", "debris_smuggler_fighter_tier3"}
		},
		{"imp_vs_smugglers_3", 4356, -4966, 2507, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 4,
			{"imp_tie_bomber_tier2", "imp_tie_fighter_tier3"}
		},
		{"nice_miners_guard_2", 4637, -349, -375, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 4,
			{"mercenary_guard_tier3", "mining_guard_ship_tier3", "nebula_scientist_bodyguard_tier3"}
		},
		{"imperial_patrol_route_1", 281, 1011, 1964, SHIP_AI_FIXED_PATROL, 60, 120, 20, 50, 6,
			5, {"imperial_patrol_route_1_00", "imperial_patrol_route_1_01", "imperial_patrol_route_1_02", "imperial_patrol_route_1_03", "imperial_patrol_route_1_04", "imperial_patrol_route_1_05", "imperial_patrol_route_1_06", "imperial_patrol_route_1_07", "imperial_patrol_route_1_08", "imperial_patrol_route_1_09", "imperial_patrol_route_1_10", "imperial_patrol_route_1_11", "imperial_patrol_route_1_12", "imperial_patrol_route_1_13", "imperial_patrol_route_1_14", "imperial_patrol_route_1_15", "imperial_patrol_route_1_16", "imperial_patrol_route_1_17", "imperial_patrol_route_1_18", "imperial_patrol_route_1_19", "imperial_patrol_route_1_20", "imperial_patrol_route_1_21", "imperial_patrol_route_1_22", "imperial_patrol_route_1_23", "imperial_patrol_route_1_24", "imperial_patrol_route_1_25", "imperial_patrol_route_1_26", "imperial_patrol_route_1_27"},
			{"imp_interceptor_boss", "imp_tie_advanced_tier3", "imp_tie_bomber_tier2", "imp_tie_fighter_tier3", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"tier3_vylukh_rally_alpha", 932, -2060, 1873, SHIP_AI_RANDOM_PATROL, 60, 18, 12, 48, 100, 340, 2,
			{"vylukh_clan_elite_tier2", "vylukh_clan_soldier_tier2"}
		},
		{"imperial_recovery_guard_loiter_1", -1640, 693, 760, SHIP_AI_RANDOM_PATROL, 60, 120, 30, 60, 50, 400, 6,
			{"imp_tie_bomber_tier2", "imp_tie_fighter_tier3", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"yavin_station_civi_spawner", 630, -1704, 117, SHIP_AI_RANDOM_PATROL, 300, 420, 10, 25, 300, 500, 2,
			{"mercenary_guard_tier3"}
		},
		{"rebel_spy_spawner_1", 1633, -2292, -2080, SHIP_AI_FIXED_PATROL, 60, 120, 20, 40, 2,
			5, {"rebel_spy_spawner_1_00", "rebel_spy_spawner_1_01", "rebel_spy_spawner_1_02", "rebel_spy_spawner_1_03", "rebel_spy_spawner_1_04", "rebel_spy_spawner_1_05", "rebel_spy_spawner_1_06", "rebel_spy_spawner_1_07", "rebel_spy_spawner_1_08"},
			{"rebel_spy_tier3"}
		},
		{"imperial_patrol_route_2", -418, 1108, 12, SHIP_AI_FIXED_PATROL, 60, 120, 20, 40, 6,
			5, {"imperial_patrol_route_2_00", "imperial_patrol_route_2_01", "imperial_patrol_route_2_02", "imperial_patrol_route_2_03", "imperial_patrol_route_2_04", "imperial_patrol_route_2_05", "imperial_patrol_route_2_06", "imperial_patrol_route_2_07", "imperial_patrol_route_2_08", "imperial_patrol_route_2_09", "imperial_patrol_route_2_10", "imperial_patrol_route_2_11", "imperial_patrol_route_2_12", "imperial_patrol_route_2_13", "imperial_patrol_route_2_14", "imperial_patrol_route_2_15", "imperial_patrol_route_2_16", "imperial_patrol_route_2_17", "imperial_patrol_route_2_18", "imperial_patrol_route_2_19", "imperial_patrol_route_2_20", "imperial_patrol_route_2_21", "imperial_patrol_route_2_22", "imperial_patrol_route_2_23", "imperial_patrol_route_2_24", "imperial_patrol_route_2_25", "imperial_patrol_route_2_26", "imperial_patrol_route_2_27", "imperial_patrol_route_2_28"},
			{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{"yavin_imp_patrol_01", 530, -277, -71, SHIP_AI_RANDOM_PATROL, 300, 420, 4, 32, 400, 600, 2,
			{"squad_tie_mix_average", "squad_tie_mix_ace"}
		},
		{"yavin_imp_base_transport_01", 492, -286, -26, SHIP_AI_FIXED_PATROL, 300, 420, 4, 24, 2,
			5, {"yavin_imp_base_transport_01_00", "yavin_imp_base_transport_01_01", "yavin_imp_base_transport_01_02", "yavin_imp_base_transport_01_03", "yavin_imp_base_transport_01_04", "yavin_imp_base_transport_01_05", "yavin_imp_base_transport_01_06", "yavin_imp_base_transport_01_07"},
			{"freighterheavy_tier3"}
		},
		{"nice_miners_2", 7187, -6529, -5283, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 3,
			5, {"nice_miners_2_00", "nice_miners_2_01", "nice_miners_2_02", "nice_miners_2_03", "nice_miners_2_04", "nice_miners_2_05", "nice_miners_2_06", "nice_miners_2_07", "nice_miners_2_08", "nice_miners_2_09", "nice_miners_2_10", "nice_miners_2_11", "nice_miners_2_12", "nice_miners_2_13", "nice_miners_2_14", "nice_miners_2_15", "nice_miners_2_16", "nice_miners_2_17", "nice_miners_2_18", "nice_miners_2_19", "nice_miners_2_20"},
			{"mercenary_guard_tier3", "mining_guard_ship_tier3", "nebula_scientist_researcher_tier3"}
		},
		{"hutt_to_imperial_1", 5409, -4825, -2351, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 3,
			5, {"hutt_to_imperial_1_00", "hutt_to_imperial_1_01", "hutt_to_imperial_1_02", "hutt_to_imperial_1_03", "hutt_to_imperial_1_04", "hutt_to_imperial_1_05", "hutt_to_imperial_1_06", "hutt_to_imperial_1_07", "hutt_to_imperial_1_08", "hutt_to_imperial_1_09", "hutt_to_imperial_1_10"},
			{"hutt_fighter_s01_tier2", "hutt_pirate_s02_tier2"}
		},
		{"hutt_debris_patrol_1", 6713, -4561, -2876, SHIP_AI_FIXED_PATROL, 60, 120, 10, 15, 4,
			5, {"hutt_debris_patrol_1_00", "hutt_debris_patrol_1_01", "hutt_debris_patrol_1_02", "hutt_debris_patrol_1_03", "hutt_debris_patrol_1_04", "hutt_debris_patrol_1_05", "hutt_debris_patrol_1_06", "hutt_debris_patrol_1_07", "hutt_debris_patrol_1_08", "hutt_debris_patrol_1_09", "hutt_debris_patrol_1_10", "hutt_debris_patrol_1_11", "hutt_debris_patrol_1_12", "hutt_debris_patrol_1_13", "hutt_debris_patrol_1_14"},
			{"hutt_fighter_boss", "hutt_pirate_s01_tier2", "hutt_pirate_s02_tier2", "hutt_pirate_s02_tier2", "hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "hutt_bomber_s02_tier3", "hutt_bomber_s02_tier3"}
		},
		{"hutt_guards_1", 6533, -6048, -3113, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 80, 300, 3,
			{"hutt_fighter_s01_tier2", "hutt_fighter_s01_tier2", "hutt_fighter_s01_tier2", "hutt_pirate_s01_tier2", "hutt_pirate_s01_tier2", "hutt_pirate_s01_tier2", "hutt_pirate_s01_tier2", "huttbomber_tier3", "huttfighter_tier3"}
		},
		{"nice_miners_guard_1", 4926, -4565, -3549, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 4,
			{"mercenary_guard_tier3", "mining_guard_ship_tier3", "nebula_scientist_bodyguard_tier3"}
		},
		{"nice_miners_guard_4", 5985, -3830, -3580, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 150, 300, 4,
			{"mercenary_guard_tier3", "mining_guard_ship_tier3", "nebula_scientist_bodyguard_tier3"}
		},
		{"nice_miners_1", 5922, -6469, -6555, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 6,
			5, {"nice_miners_1_00", "nice_miners_1_01", "nice_miners_1_02", "nice_miners_1_03", "nice_miners_1_04", "nice_miners_1_05", "nice_miners_1_06", "nice_miners_1_07", "nice_miners_1_08"},
			{"mining_guard_ship_tier3", "nebula_scientist_researcher_tier3"}
		},
	},
}

registerScreenPlay("SpaceYavin4Spawner", true)

function SpaceYavin4Spawner:start()
	if (not isZoneEnabled(self.spaceZone)) then
		return
	end

	self:populateSpawns()
end
