SpaceYavin4Spawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceYavin4Spawner",

	spaceZone = "space_yavin4",

	shipSpawns = {
		{spawnName = "imperial_tie_hyper1_patrol4", spawnType = SHIP_SPAWN_SINGLE, x = 3686, z = 1552, y = 3339, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"imp_tie_fighter_tier3", "imp_tie_interceptor_tier3", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "imperial_tie_hyper1_patrol1", spawnType = SHIP_SPAWN_SINGLE, x = 3413, z = -92, y = 3462, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 50, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier3", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3"}
		},
		{spawnName = "imperial_supply_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 3490, z = 73, y = 3514, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_supply_route_1_00", "imperial_supply_route_1_01", "imperial_supply_route_1_02", "imperial_supply_route_1_03", "imperial_supply_route_1_04", "imperial_supply_route_1_05", "imperial_supply_route_1_06"},
			shipSpawns = {"imp_freighterlight_tier3", "imp_tie_fighter_tier3", "imp_freighterheavy_tier3", "imp_freightermedium_tier3"}
		},
		{spawnName = "hutt_asteroid_patrol2", spawnType = SHIP_SPAWN_SINGLE, x = 2829, z = -4794, y = 1393, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 350, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s02_tier2", "hutt_fighter_s01_tier2"}
		},
		{spawnName = "hutt_asteroid_patrol", spawnType = SHIP_SPAWN_SINGLE, x = 2428, z = -5996, y = 1259, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 200, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier2", "hutt_fighter_s01_tier2", "hutt_heavy_s01_tier3"}
		},
		{spawnName = "imperial_squad_1", spawnType = SHIP_SPAWN_SQUADRON, x = -6904, z = 4998, y = 6054, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 7200, maxRespawn = 10800, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_squad_1_00", "imperial_squad_1_01", "imperial_squad_1_02", "imperial_squad_1_03", "imperial_squad_1_04", "imperial_squad_1_05", "imperial_squad_1_06", "imperial_squad_1_07"},
			shipSpawns = {"squad_imperial_fleet"}
		},
		{spawnName = "rebel_defenders_4", spawnType = SHIP_SPAWN_SINGLE, x = -6331, z = 3387, y = 787, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 6,
			shipSpawns = {"rebel_raider_fast_attack_tier3", "reb_z95_tier3", "reb_ywing_tier3", "reb_bwing_tier3", "reb_awing_tier3", "reb_xwing_tier3"}
		},
		{spawnName = "nice_mining_path_a", spawnType = SHIP_SPAWN_SINGLE, x = -507, z = -5392, y = -6678, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"nice_mining_path_a_00", "nice_mining_path_a_01", "nice_mining_path_a_02", "nice_mining_path_a_03", "nice_mining_path_a_04"},
			shipSpawns = {"nebula_scientist_researcher_tier3", "junk_dealer_trader", "junk_dealer_collector"}
		},
		{spawnName = "rebel_gun_boat_1", spawnType = SHIP_SPAWN_SQUADRON, x = -5845, z = -1069, y = 840, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 3600, maxRespawn = 240, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_gun_boat_1_00", "rebel_gun_boat_1_01", "rebel_gun_boat_1_02", "rebel_gun_boat_1_03", "rebel_gun_boat_1_04", "rebel_gun_boat_1_05", "rebel_gun_boat_1_06", "rebel_gun_boat_1_07", "rebel_gun_boat_1_08", "rebel_gun_boat_1_09", "rebel_gun_boat_1_10", "rebel_gun_boat_1_11", "rebel_gun_boat_1_12", "rebel_gun_boat_1_13"},
			shipSpawns = {"squad_rebel_gunboat_tier3"}
		},
		{spawnName = "rebel_raider_captain_2", spawnType = SHIP_SPAWN_SINGLE, x = -6200, z = -5408, y = -781, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 500, maxRespawn = 1000, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 160, totalSpawns = 4,
			shipSpawns = {"rebel_raider_captain_tier3", "reb_z95_tier3", "reb_xwing_tier3", "reb_bwing_tier3", "reb_awing_tier3"}
		},
		{spawnName = "corellian_corvette_1", spawnType = SHIP_SPAWN_SQUADRON, x = -6209, z = -5296, y = -525, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 3600, maxRespawn = 5400, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"corellian_corvette_1_00", "corellian_corvette_1_01", "corellian_corvette_1_02", "corellian_corvette_1_03", "corellian_corvette_1_04", "corellian_corvette_1_05"},
			shipSpawns = {"squad_rebel_gunboat_tier3"}
		},
		{spawnName = "rebel_route_2", spawnType = SHIP_SPAWN_SINGLE, x = -2199, z = -5552, y = -4680, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 120, maxRespawn = 240, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_route_2_00", "rebel_route_2_01", "rebel_route_2_02", "rebel_route_2_03", "rebel_route_2_04", "rebel_route_2_05", "rebel_route_2_06"},
			shipSpawns = {"reb_awing_boss", "reb_awing_tier2", "reb_xwing_tier2", "reb_xwing_tier2", "reb_xwing_tier2", "reb_xwing_tier2", "reb_xwing_tier2", "reb_xwing_tier2", "reb_ywing_tier2", "reb_ywing_tier2", "reb_ywing_tier2", "reb_ywing_tier2", "reb_ywing_tier2"}
		},
		{spawnName = "hutt_patrol_two", spawnType = SHIP_SPAWN_SINGLE, x = -1767, z = -5975, y = 5177, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier2", "hutt_pirate_s01_tier2"}
		},
		{spawnName = "tier3_vylukh_rally_bravo", spawnType = SHIP_SPAWN_SINGLE, x = 1722, z = -3078, y = 2985, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 14, maxSpawnDistance = 48, minPatrol = 100, maxPatrol = 312, totalSpawns = 3,
			shipSpawns = {"vylukh_clan_elite_tier2", "vylukh_clan_transport_tier2", "vylukh_clan_soldier_tier2"}
		},
		{spawnName = "hutt_asteroid_1", spawnType = SHIP_SPAWN_SINGLE, x = -2279, z = -4901, y = 4912, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s02_tier2", "hutt_fighter_s02_tier2"}
		},
		{spawnName = "massassi_inspect_spawner_02", spawnType = SHIP_SPAWN_SINGLE, x = -332, z = -2348, y = 6768, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 45, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 350, totalSpawns = 1,
			shipSpawns = {"massassi_damaged_fighter_tier2"}
		},
		{spawnName = "imp_vs_smugglers_2", spawnType = SHIP_SPAWN_SINGLE, x = 1126, z = -3034, y = 4869, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier2", "imp_tie_fighter_tier3"}
		},
		{spawnName = "smugglers_vs_imperial_2", spawnType = SHIP_SPAWN_SINGLE, x = 1287, z = -2610, y = 4834, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"debris_smuggler_bomber_tier3", "debris_smuggler_fighter_tier3"}
		},
		{spawnName = "massassi_inspect_spawner_01", spawnType = SHIP_SPAWN_SINGLE, x = -6156, z = -4044, y = 3712, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 45, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 350, totalSpawns = 1,
			shipSpawns = {"massassi_damaged_fighter_tier2"}
		},
		{spawnName = "tatooine_imperial_tier2_inspect_rebagent", spawnType = SHIP_SPAWN_SINGLE, x = -3200, z = -3000, y = 6000, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 500, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier2", "rebel_agent_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_z95_tier3", "reb_bwing_tier3", "reb_awing_tier3"}
		},
		{spawnName = "imperial_station_lambda_patrol", spawnType = SHIP_SPAWN_SINGLE, x = -3686, z = -5547, y = 4127, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_station_lambda_patrol_00", "imperial_station_lambda_patrol_01", "imperial_station_lambda_patrol_02", "imperial_station_lambda_patrol_03", "imperial_station_lambda_patrol_04", "imperial_station_lambda_patrol_05", "imperial_station_lambda_patrol_06", "imperial_station_lambda_patrol_07", "imperial_station_lambda_patrol_08", "imperial_station_lambda_patrol_09", "imperial_station_lambda_patrol_10", "imperial_station_lambda_patrol_11", "imperial_station_lambda_patrol_12", "imperial_station_lambda_patrol_13"},
			shipSpawns = {"imp_lambda_shuttle_tier3", "imp_tie_bomber_tier2", "imp_tie_fighter_tier3"}
		},
		{spawnName = "corellia_imperial_tier3_officerinspect", spawnType = SHIP_SPAWN_SINGLE, x = -2000, z = -4500, y = 3000, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 25, maxSpawnDistance = 50, minPatrol = 200, maxPatrol = 400, totalSpawns = 1,
			shipSpawns = {"reb_yavinspy_tier4"}
		},
		{spawnName = "corellia_imperial_tier3_guard", spawnType = SHIP_SPAWN_SINGLE, x = -1933, z = -3975, y = 3055, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 25, maxSpawnDistance = 50, minPatrol = 200, maxPatrol = 400, totalSpawns = 3,
			shipSpawns = {"reb_awing_tier3", "reb_bwing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_ywing_tier3"}
		},
		{spawnName = "smuggler_debris_route_gaurd_2", spawnType = SHIP_SPAWN_SINGLE, x = 3438, z = 4640, y = 4017, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 80, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"debris_smuggler_fighter_tier3"}
		},
		{spawnName = "imperial_spies_1", spawnType = SHIP_SPAWN_SINGLE, x = 4224, z = 6624, y = 6928, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 50, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"imp_tie_advanced_tier3", "imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier3", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "smuggler_route_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = 4269, z = 6896, y = 5947, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 80, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"debris_smuggler_fighter_tier2"}
		},
		{spawnName = "smugglers_patrol_2", spawnType = SHIP_SPAWN_SINGLE, x = 3746, z = 5511, y = 3220, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"smugglers_patrol_2_00", "smugglers_patrol_2_01", "smugglers_patrol_2_02", "smugglers_patrol_2_03", "smugglers_patrol_2_04", "smugglers_patrol_2_05", "smugglers_patrol_2_06", "smugglers_patrol_2_07"},
			shipSpawns = {"debris_smuggler_bomber_tier3"}
		},
		{spawnName = "rebel_defenders_3", spawnType = SHIP_SPAWN_SINGLE, x = -5119, z = 4160, y = 353, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 350, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier2", "reb_z95_tier2", "reb_z95_tier3", "reb_ywing_tier3", "reb_xwing_tier3", "reb_bwing_tier3", "reb_awing_tier3"}
		},
		{spawnName = "rebel_defenders_2", spawnType = SHIP_SPAWN_SINGLE, x = -4749, z = 7136, y = 484, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 350, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier2", "reb_z95_tier2", "reb_xwing_tier3", "reb_z95_tier3", "reb_ywing_tier3", "reb_bwing_tier3", "reb_awing_tier3"}
		},
		{spawnName = "rebel_xwing_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = 2945, z = 4201, y = 5113, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier2", "reb_xwing_tier2", "reb_ywing_tier2", "reb_awing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_z95_tier3"}
		},
		{spawnName = "yavin_rebel_2_shuttle", spawnType = SHIP_SPAWN_SINGLE, x = 1405, z = 2111, y = 4328, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 10, maxRespawn = 60, minSpawnDistance = 30, maxSpawnDistance = 60, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"yavin_rebel_2_shuttle_00", "yavin_rebel_2_shuttle_01", "yavin_rebel_2_shuttle_02", "yavin_rebel_2_shuttle_03", "yavin_rebel_2_shuttle_04"},
			shipSpawns = {"yavin_mission_2_shuttle"}
		},
		{spawnName = "imperial_vs_smugglers_1", spawnType = SHIP_SPAWN_SINGLE, x = -283, z = -257, y = 4778, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 420, maxRespawn = 620, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_vs_smugglers_1_00", "imperial_vs_smugglers_1_01", "imperial_vs_smugglers_1_02", "imperial_vs_smugglers_1_03", "imperial_vs_smugglers_1_04", "imperial_vs_smugglers_1_05", "imperial_vs_smugglers_1_06", "imperial_vs_smugglers_1_07", "imperial_vs_smugglers_1_08", "imperial_vs_smugglers_1_09", "imperial_vs_smugglers_1_10", "imperial_vs_smugglers_1_11", "imperial_vs_smugglers_1_12", "imperial_vs_smugglers_1_13", "imperial_vs_smugglers_1_14", "imperial_vs_smugglers_1_15", "imperial_vs_smugglers_1_16", "imperial_vs_smugglers_1_17", "imperial_vs_smugglers_1_18", "imperial_vs_smugglers_1_19"},
			shipSpawns = {"imp_imperial_gunboat_tier3"}
		},
		{spawnName = "rebel_vs_imp_1", spawnType = SHIP_SPAWN_SINGLE, x = -847, z = 3766, y = 3922, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_z95_tier3"}
		},
		{spawnName = "imp_vs_rebel_1", spawnType = SHIP_SPAWN_SINGLE, x = -729, z = 3894, y = 4042, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"imp_tie_bomber_tier2", "imp_tie_fighter_tier3"}
		},
		{spawnName = "imp_gunboat_to_rebel_1", spawnType = SHIP_SPAWN_SINGLE, x = -425, z = 4930, y = 5028, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 30, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imp_gunboat_to_rebel_1_00", "imp_gunboat_to_rebel_1_01", "imp_gunboat_to_rebel_1_02", "imp_gunboat_to_rebel_1_03", "imp_gunboat_to_rebel_1_04", "imp_gunboat_to_rebel_1_05", "imp_gunboat_to_rebel_1_06", "imp_gunboat_to_rebel_1_07", "imp_gunboat_to_rebel_1_08", "imp_gunboat_to_rebel_1_09", "imp_gunboat_to_rebel_1_10", "imp_gunboat_to_rebel_1_11", "imp_gunboat_to_rebel_1_12", "imp_gunboat_to_rebel_1_13", "imp_gunboat_to_rebel_1_14", "imp_gunboat_to_rebel_1_15"},
			shipSpawns = {"imp_imperial_gunboat_tier2"}
		},
		{spawnName = "blockade_run_general_1", spawnType = SHIP_SPAWN_SINGLE, x = -2826, z = 4197, y = 750, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"blockade_run_general_1_00", "blockade_run_general_1_01", "blockade_run_general_1_02", "blockade_run_general_1_03", "blockade_run_general_1_04", "blockade_run_general_1_05", "blockade_run_general_1_06", "blockade_run_general_1_07", "blockade_run_general_1_08", "blockade_run_general_1_09", "blockade_run_general_1_10", "blockade_run_general_1_11", "blockade_run_general_1_12", "blockade_run_general_1_13", "blockade_run_general_1_14", "blockade_run_general_1_15", "blockade_run_general_1_16", "blockade_run_general_1_17", "blockade_run_general_1_18", "blockade_run_general_1_19", "blockade_run_general_1_20", "blockade_run_general_1_21", "blockade_run_general_1_22", "blockade_run_general_1_23", "blockade_run_general_1_24", "blockade_run_general_1_25"},
			shipSpawns = {"reb_bwing_tier2", "reb_freighterheavy_tier3", "reb_freighterlight_tier3", "reb_freighterlight_tier3", "reb_freightermedium_tier3", "reb_xwing_tier2", "reb_ywing_tier2", "reb_ykl37r_tier2", "reb_z95_tier2", "rebel_smuggler_tier3"}
		},
		{spawnName = "smugglers_run_1", spawnType = SHIP_SPAWN_SINGLE, x = 2261, z = 3918, y = -3860, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 6, maxSpawnDistance = 10, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"smugglers_run_1_00", "smugglers_run_1_01", "smugglers_run_1_02", "smugglers_run_1_03", "smugglers_run_1_04", "smugglers_run_1_05", "smugglers_run_1_06", "smugglers_run_1_07", "smugglers_run_1_08", "smugglers_run_1_09", "smugglers_run_1_10", "smugglers_run_1_11", "smugglers_run_1_12", "smugglers_run_1_13", "smugglers_run_1_14", "smugglers_run_1_15", "smugglers_run_1_16", "smugglers_run_1_17", "smugglers_run_1_18", "smugglers_run_1_19", "smugglers_run_1_20", "smugglers_run_1_21", "smugglers_run_1_22", "smugglers_run_1_23", "smugglers_run_1_24", "smugglers_run_1_25", "smugglers_run_1_26", "smugglers_run_1_27", "smugglers_run_1_28", "smugglers_run_1_29", "smugglers_run_1_30", "smugglers_run_1_31", "smugglers_run_1_32", "smugglers_run_1_33", "smugglers_run_1_34", "smugglers_run_1_35", "smugglers_run_1_36", "smugglers_run_1_37", "smugglers_run_1_38", "smugglers_run_1_39"},
			shipSpawns = {"blacksun_vehement_tier2", "blacksun_marauder_tier2", "hidden_daggers_nebula_stalker_tier2", "huttfighter_tier3", "hutt_fighter_s01_tier2", "hutt_bomber_s01_tier2", "nym_enforcer_tier2", "nym_gunship_tier2"}
		},
		{spawnName = "blockade_run_corvette_1", spawnType = SHIP_SPAWN_SINGLE, x = -2197, z = 5884, y = -3691, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 7200, maxRespawn = 10800, minSpawnDistance = 30, maxSpawnDistance = 200, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"blockade_run_corvette_1_00", "blockade_run_corvette_1_01", "blockade_run_corvette_1_02", "blockade_run_corvette_1_03", "blockade_run_corvette_1_04", "blockade_run_corvette_1_05", "blockade_run_corvette_1_06"},
			shipSpawns = {"reb_xwing_tier3", "reb_ykl37r_tier2", "reb_ywing_tier2"}
		},
		{spawnName = "rebel_raider_captain_1", spawnType = SHIP_SPAWN_SINGLE, x = -5129, z = -2267, y = -373, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 500, maxRespawn = 1000, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 80, maxPatrol = 160, totalSpawns = 6,
			shipSpawns = {"rebel_raider_captain_tier3", "reb_z95_tier3", "reb_ywing_tier3", "reb_xwing_tier3", "reb_awing_tier3", "reb_bwing_tier3"}
		},
		{spawnName = "corellia_imperial_tier3_leg_2_inspect", spawnType = SHIP_SPAWN_SINGLE, x = -3754, z = 325, y = -4456, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 45, maxSpawnDistance = 90, minPatrol = 200, maxPatrol = 260, totalSpawns = 1,
			shipSpawns = {"neutral_freighter"}
		},
		{spawnName = "rebel_defenders_1", spawnType = SHIP_SPAWN_SINGLE, x = -5536, z = 6083, y = 136, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 350, totalSpawns = 6,
			shipSpawns = {"rebel_raider_bomber_tier3", "reb_ywing_tier3", "reb_xwing_tier3", "reb_bwing_tier3", "reb_awing_tier3"}
		},
		{spawnName = "hutt_guards_2", spawnType = SHIP_SPAWN_SINGLE, x = 3581, z = -5979, y = -1756, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier2", "hutt_fighter_s01_tier2", "hutt_pirate_s01_tier2"}
		},
		{spawnName = "smuggler_to_debris_astroid_1", spawnType = SHIP_SPAWN_SINGLE, x = 7226, z = 5186, y = 3488, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"smuggler_to_debris_astroid_1_00", "smuggler_to_debris_astroid_1_01", "smuggler_to_debris_astroid_1_02", "smuggler_to_debris_astroid_1_03", "smuggler_to_debris_astroid_1_04", "smuggler_to_debris_astroid_1_05", "smuggler_to_debris_astroid_1_06", "smuggler_to_debris_astroid_1_07", "smuggler_to_debris_astroid_1_08", "smuggler_to_debris_astroid_1_09", "smuggler_to_debris_astroid_1_10", "smuggler_to_debris_astroid_1_11"},
			shipSpawns = {"debris_smuggler_collector_tier3"}
		},
		{spawnName = "smuggler_guards_3", spawnType = SHIP_SPAWN_SINGLE, x = 5115, z = 5598, y = 3353, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 3,
			shipSpawns = {"debris_smuggler_bomber_tier3", "debris_smuggler_fighter_tier2"}
		},
		{spawnName = "debris_collector", spawnType = SHIP_SPAWN_SINGLE, x = 5839, z = 5429, y = 3360, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"debris_collector_00", "debris_collector_01", "debris_collector_02", "debris_collector_03", "debris_collector_04", "debris_collector_05", "debris_collector_06", "debris_collector_07", "debris_collector_08", "debris_collector_09", "debris_collector_10", "debris_collector_11"},
			shipSpawns = {"debris_smuggler_collector_tier3", "debris_smuggler_fighter_tier3"}
		},
		{spawnName = "smuggler_base_1", spawnType = SHIP_SPAWN_SINGLE, x = 7238, z = 6647, y = 3462, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"smuggler_base_1_00", "smuggler_base_1_01", "smuggler_base_1_02", "smuggler_base_1_03", "smuggler_base_1_04", "smuggler_base_1_05", "smuggler_base_1_06", "smuggler_base_1_07", "smuggler_base_1_08", "smuggler_base_1_09", "smuggler_base_1_10"},
			shipSpawns = {"debris_smuggler_fighter_tier3"}
		},
		{spawnName = "imperial_tie_hyper1_patrol3", spawnType = SHIP_SPAWN_SINGLE, x = 3292, z = -787, y = 5141, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"imp_tie_bomber_tier2", "imp_tie_fighter_tier3", "imp_tie_interceptor_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "yavin4_to_station_1", spawnType = SHIP_SPAWN_SINGLE, x = -4852, z = -6144, y = -5023, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 400, maxRespawn = 850, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"yavin4_to_station_1_00", "yavin4_to_station_1_01", "yavin4_to_station_1_02"},
			shipSpawns = {"freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_tier3"}
		},
		{spawnName = "debris_communication_inspect_spawner_01", spawnType = SHIP_SPAWN_SINGLE, x = -5984, z = -496, y = 2880, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 45, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 350, totalSpawns = 1,
			shipSpawns = {"deathstar_debris_communication_tier2"}
		},
		{spawnName = "imperial_station_tie_three", spawnType = SHIP_SPAWN_SINGLE, x = -3600, z = 743, y = 4443, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 50, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"imp_tie_bomber_tier2", "imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "imperail_station_tie_spawner2", spawnType = SHIP_SPAWN_SINGLE, x = -3810, z = 2137, y = 4579, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 50, maxPatrol = 400, totalSpawns = 4,
			shipSpawns = {"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2"}
		},
		{spawnName = "imperial_station_salvage_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -3739, z = 1508, y = 4498, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_station_salvage_spawner_00", "imperial_station_salvage_spawner_01", "imperial_station_salvage_spawner_02", "imperial_station_salvage_spawner_03", "imperial_station_salvage_spawner_04", "imperial_station_salvage_spawner_05", "imperial_station_salvage_spawner_06", "imperial_station_salvage_spawner_07", "imperial_station_salvage_spawner_08", "imperial_station_salvage_spawner_09", "imperial_station_salvage_spawner_10", "imperial_station_salvage_spawner_11", "imperial_station_salvage_spawner_12", "imperial_station_salvage_spawner_13", "imperial_station_salvage_spawner_14", "imperial_station_salvage_spawner_15", "imperial_station_salvage_spawner_16", "imperial_station_salvage_spawner_17"},
			shipSpawns = {"imp_freighterlight_tier3"}
		},
		{spawnName = "imperial_station_tie_patrol", spawnType = SHIP_SPAWN_SINGLE, x = -4662, z = 1508, y = 4278, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_station_tie_patrol_00", "imperial_station_tie_patrol_01", "imperial_station_tie_patrol_02", "imperial_station_tie_patrol_03", "imperial_station_tie_patrol_04", "imperial_station_tie_patrol_05"},
			shipSpawns = {"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_oppressor_tier3", "imp_tie_interceptor_tier3"}
		},
		{spawnName = "imp_vs_reb_3", spawnType = SHIP_SPAWN_SINGLE, x = -2201, z = 1364, y = 3657, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier2", "imp_tie_fighter_tier3"}
		},
		{spawnName = "rebel_vs_imp_3", spawnType = SHIP_SPAWN_SINGLE, x = -2081, z = 1546, y = 3814, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_z95_tier3"}
		},
		{spawnName = "freighters_2", spawnType = SHIP_SPAWN_SINGLE, x = 240, z = -5299, y = -6160, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"freighters_2_00", "freighters_2_01", "freighters_2_02", "freighters_2_03", "freighters_2_04", "freighters_2_05"},
			shipSpawns = {"freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_tier3"}
		},
		{spawnName = "naboo_imperial_tier3_shinssyacht_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 3196, z = -6203, y = -5010, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 600, totalSpawns = 1,
			shipSpawns = {"shinss_yacht_tier3"}
		},
		{spawnName = "smuggler_astroid_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 7552, z = 3812, y = 2736, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 5, maxSpawnDistance = 15, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"smuggler_astroid_route_1_00", "smuggler_astroid_route_1_01", "smuggler_astroid_route_1_02", "smuggler_astroid_route_1_03", "smuggler_astroid_route_1_04", "smuggler_astroid_route_1_05", "smuggler_astroid_route_1_06", "smuggler_astroid_route_1_07", "smuggler_astroid_route_1_08", "smuggler_astroid_route_1_09", "smuggler_astroid_route_1_10", "smuggler_astroid_route_1_11", "smuggler_astroid_route_1_12", "smuggler_astroid_route_1_13", "smuggler_astroid_route_1_14", "smuggler_astroid_route_1_15"},
			shipSpawns = {"debris_smuggler_fighter_tier3"}
		},
		{spawnName = "smuggler_outpost_1", spawnType = SHIP_SPAWN_SINGLE, x = 6267, z = 1604, y = -3, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"smuggler_outpost_1_00", "smuggler_outpost_1_01", "smuggler_outpost_1_02", "smuggler_outpost_1_03", "smuggler_outpost_1_04", "smuggler_outpost_1_05", "smuggler_outpost_1_06", "smuggler_outpost_1_07", "smuggler_outpost_1_08"},
			shipSpawns = {"debris_smuggler_fighter_tier3", "debris_smuggler_boss", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3", "debris_smuggler_fighter_tier3"}
		},
		{spawnName = "smuggler_transport_1", spawnType = SHIP_SPAWN_SINGLE, x = 6096, z = 1635, y = 25, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 500, maxRespawn = 1000, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"smuggler_transport_1_00", "smuggler_transport_1_01", "smuggler_transport_1_02"},
			shipSpawns = {"debris_smuggler_transport_tier3"}
		},
		{spawnName = "rebel_xwing_hyper1_patrol1", spawnType = SHIP_SPAWN_SINGLE, x = 4239, z = -1265, y = 4275, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier2", "reb_awing_tier2", "reb_awing_tier2", "reb_bwing_tier3", "reb_xwing_tier2", "reb_ywing_tier2", "reb_awing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_z95_tier3"}
		},
		{spawnName = "imperial_tie_hyper1_patrol2", spawnType = SHIP_SPAWN_SINGLE, x = 4348, z = -572, y = 3857, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "naboo_imperial_tier3_inspect1_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 5000, z = -2300, y = 1020, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 400, totalSpawns = 1,
			shipSpawns = {"mercenary_spy_fighter_tier4"}
		},
		{spawnName = "smugglers_vs_imp_3", spawnType = SHIP_SPAWN_SINGLE, x = 4717, z = -4614, y = 2198, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"debris_smuggler_bomber_tier3", "debris_smuggler_fighter_tier3"}
		},
		{spawnName = "imp_vs_smugglers_3", spawnType = SHIP_SPAWN_SINGLE, x = 4356, z = -4966, y = 2507, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"imp_tie_bomber_tier2", "imp_tie_fighter_tier3"}
		},
		{spawnName = "nice_miners_guard_2", spawnType = SHIP_SPAWN_SINGLE, x = 4637, z = -349, y = -375, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"mercenary_guard_tier3", "mining_guard_ship_tier3", "nebula_scientist_bodyguard_tier3"}
		},
		{spawnName = "imperial_patrol_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 281, z = 1011, y = 1964, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 50, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_patrol_route_1_00", "imperial_patrol_route_1_01", "imperial_patrol_route_1_02", "imperial_patrol_route_1_03", "imperial_patrol_route_1_04", "imperial_patrol_route_1_05", "imperial_patrol_route_1_06", "imperial_patrol_route_1_07", "imperial_patrol_route_1_08", "imperial_patrol_route_1_09", "imperial_patrol_route_1_10", "imperial_patrol_route_1_11", "imperial_patrol_route_1_12", "imperial_patrol_route_1_13", "imperial_patrol_route_1_14", "imperial_patrol_route_1_15", "imperial_patrol_route_1_16", "imperial_patrol_route_1_17", "imperial_patrol_route_1_18", "imperial_patrol_route_1_19", "imperial_patrol_route_1_20", "imperial_patrol_route_1_21", "imperial_patrol_route_1_22", "imperial_patrol_route_1_23", "imperial_patrol_route_1_24", "imperial_patrol_route_1_25", "imperial_patrol_route_1_26", "imperial_patrol_route_1_27"},
			shipSpawns = {"imp_interceptor_boss", "imp_tie_advanced_tier3", "imp_tie_bomber_tier2", "imp_tie_fighter_tier3", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "tier3_vylukh_rally_alpha", spawnType = SHIP_SPAWN_SINGLE, x = 932, z = -2060, y = 1873, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 18, minSpawnDistance = 12, maxSpawnDistance = 48, minPatrol = 100, maxPatrol = 340, totalSpawns = 2,
			shipSpawns = {"vylukh_clan_elite_tier2", "vylukh_clan_soldier_tier2"}
		},
		{spawnName = "imperial_recovery_guard_loiter_1", spawnType = SHIP_SPAWN_SINGLE, x = -1640, z = 693, y = 760, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 30, maxSpawnDistance = 60, minPatrol = 50, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"imp_tie_bomber_tier2", "imp_tie_fighter_tier3", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "yavin_station_civi_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 630, z = -1704, y = 117, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 25, minPatrol = 300, maxPatrol = 500, totalSpawns = 2,
			shipSpawns = {"mercenary_guard_tier3"}
		},
		{spawnName = "rebel_spy_spawner_1", spawnType = SHIP_SPAWN_SINGLE, x = 1633, z = -2292, y = -2080, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_spy_spawner_1_00", "rebel_spy_spawner_1_01", "rebel_spy_spawner_1_02", "rebel_spy_spawner_1_03", "rebel_spy_spawner_1_04", "rebel_spy_spawner_1_05", "rebel_spy_spawner_1_06", "rebel_spy_spawner_1_07", "rebel_spy_spawner_1_08"},
			shipSpawns = {"rebel_spy_tier3"}
		},
		{spawnName = "imperial_patrol_route_2", spawnType = SHIP_SPAWN_SINGLE, x = -418, z = 1108, y = 12, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_patrol_route_2_00", "imperial_patrol_route_2_01", "imperial_patrol_route_2_02", "imperial_patrol_route_2_03", "imperial_patrol_route_2_04", "imperial_patrol_route_2_05", "imperial_patrol_route_2_06", "imperial_patrol_route_2_07", "imperial_patrol_route_2_08", "imperial_patrol_route_2_09", "imperial_patrol_route_2_10", "imperial_patrol_route_2_11", "imperial_patrol_route_2_12", "imperial_patrol_route_2_13", "imperial_patrol_route_2_14", "imperial_patrol_route_2_15", "imperial_patrol_route_2_16", "imperial_patrol_route_2_17", "imperial_patrol_route_2_18", "imperial_patrol_route_2_19", "imperial_patrol_route_2_20", "imperial_patrol_route_2_21", "imperial_patrol_route_2_22", "imperial_patrol_route_2_23", "imperial_patrol_route_2_24", "imperial_patrol_route_2_25", "imperial_patrol_route_2_26", "imperial_patrol_route_2_27", "imperial_patrol_route_2_28"},
			shipSpawns = {"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "yavin_imp_patrol_01", spawnType = SHIP_SPAWN_SQUADRON, x = 530, z = -277, y = -71, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 4, maxSpawnDistance = 32, minPatrol = 400, maxPatrol = 600, totalSpawns = 2,
			shipSpawns = {"squad_tie_mix_ace_average"}
		},
		{spawnName = "yavin_imp_base_transport_01", spawnType = SHIP_SPAWN_SINGLE, x = 492, z = -286, y = -26, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 4, maxSpawnDistance = 24, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"yavin_imp_base_transport_01_00", "yavin_imp_base_transport_01_01", "yavin_imp_base_transport_01_02", "yavin_imp_base_transport_01_03", "yavin_imp_base_transport_01_04", "yavin_imp_base_transport_01_05", "yavin_imp_base_transport_01_06", "yavin_imp_base_transport_01_07"},
			shipSpawns = {"freighterheavy_tier3"}
		},
		{spawnName = "nice_miners_2", spawnType = SHIP_SPAWN_SINGLE, x = 7187, z = -6529, y = -5283, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"nice_miners_2_00", "nice_miners_2_01", "nice_miners_2_02", "nice_miners_2_03", "nice_miners_2_04", "nice_miners_2_05", "nice_miners_2_06", "nice_miners_2_07", "nice_miners_2_08", "nice_miners_2_09", "nice_miners_2_10", "nice_miners_2_11", "nice_miners_2_12", "nice_miners_2_13", "nice_miners_2_14", "nice_miners_2_15", "nice_miners_2_16", "nice_miners_2_17", "nice_miners_2_18", "nice_miners_2_19", "nice_miners_2_20"},
			shipSpawns = {"mercenary_guard_tier3", "mining_guard_ship_tier3", "nebula_scientist_researcher_tier3"}
		},
		{spawnName = "hutt_to_imperial_1", spawnType = SHIP_SPAWN_SINGLE, x = 5409, z = -4825, y = -2351, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_to_imperial_1_00", "hutt_to_imperial_1_01", "hutt_to_imperial_1_02", "hutt_to_imperial_1_03", "hutt_to_imperial_1_04", "hutt_to_imperial_1_05", "hutt_to_imperial_1_06", "hutt_to_imperial_1_07", "hutt_to_imperial_1_08", "hutt_to_imperial_1_09", "hutt_to_imperial_1_10"},
			shipSpawns = {"hutt_fighter_s01_tier2", "hutt_pirate_s02_tier2"}
		},
		{spawnName = "hutt_debris_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = 6713, z = -4561, y = -2876, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_debris_patrol_1_00", "hutt_debris_patrol_1_01", "hutt_debris_patrol_1_02", "hutt_debris_patrol_1_03", "hutt_debris_patrol_1_04", "hutt_debris_patrol_1_05", "hutt_debris_patrol_1_06", "hutt_debris_patrol_1_07", "hutt_debris_patrol_1_08", "hutt_debris_patrol_1_09", "hutt_debris_patrol_1_10", "hutt_debris_patrol_1_11", "hutt_debris_patrol_1_12", "hutt_debris_patrol_1_13", "hutt_debris_patrol_1_14"},
			shipSpawns = {"hutt_fighter_boss", "hutt_pirate_s01_tier2", "hutt_pirate_s02_tier2", "hutt_pirate_s02_tier2", "hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "hutt_bomber_s02_tier3", "hutt_bomber_s02_tier3"}
		},
		{spawnName = "hutt_guards_1", spawnType = SHIP_SPAWN_SINGLE, x = 6533, z = -6048, y = -3113, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 80, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_fighter_s01_tier2", "hutt_fighter_s01_tier2", "hutt_fighter_s01_tier2", "hutt_pirate_s01_tier2", "hutt_pirate_s01_tier2", "hutt_pirate_s01_tier2", "hutt_pirate_s01_tier2", "huttbomber_tier3", "huttfighter_tier3"}
		},
		{spawnName = "nice_miners_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = 4926, z = -4565, y = -3549, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"mercenary_guard_tier3", "mining_guard_ship_tier3", "nebula_scientist_bodyguard_tier3"}
		},
		{spawnName = "nice_miners_guard_4", spawnType = SHIP_SPAWN_SINGLE, x = 5985, z = -3830, y = -3580, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"mercenary_guard_tier3", "mining_guard_ship_tier3", "nebula_scientist_bodyguard_tier3"}
		},
		{spawnName = "nice_miners_1", spawnType = SHIP_SPAWN_SINGLE, x = 5922, z = -6469, y = -6555, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"nice_miners_1_00", "nice_miners_1_01", "nice_miners_1_02", "nice_miners_1_03", "nice_miners_1_04", "nice_miners_1_05", "nice_miners_1_06", "nice_miners_1_07", "nice_miners_1_08"},
			shipSpawns = {"mining_guard_ship_tier3", "nebula_scientist_researcher_tier3"}
		},
	},
}

registerScreenPlay("SpaceYavin4Spawner", true)
