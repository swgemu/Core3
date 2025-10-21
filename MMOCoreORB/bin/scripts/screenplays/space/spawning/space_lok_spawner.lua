SpaceLokSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceLokSpawner",

	spaceZone = "space_lok",

	shipSpawns = {
		{spawnName = "nym_gunboat_to_imp", spawnType = SHIP_SPAWN_SINGLE, x = 6427, z = -6877, y = -5763, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"nym_gunboat_to_imp_00", "nym_gunboat_to_imp_01", "nym_gunboat_to_imp_02", "nym_gunboat_to_imp_03", "nym_gunboat_to_imp_04", "nym_gunboat_to_imp_05", "nym_gunboat_to_imp_06", "nym_gunboat_to_imp_07", "nym_gunboat_to_imp_08", "nym_gunboat_to_imp_09", "nym_gunboat_to_imp_10", "nym_gunboat_to_imp_11", "nym_gunboat_to_imp_12", "nym_gunboat_to_imp_13", "nym_gunboat_to_imp_14", "nym_gunboat_to_imp_15", "nym_gunboat_to_imp_16"},
			shipSpawns = {"nym_gunship_tier3"}
		},
		{spawnName = "nym_fodder_2", spawnType = SHIP_SPAWN_SINGLE, x = 6959, z = -5822, y = -6004, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"nym_bomber_tier3"}
		},
		{spawnName = "nym_asteroid_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = 5820, z = -6045, y = -6201, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"nym_asteroid_patrol_1_00", "nym_asteroid_patrol_1_01", "nym_asteroid_patrol_1_02", "nym_asteroid_patrol_1_03", "nym_asteroid_patrol_1_04", "nym_asteroid_patrol_1_05", "nym_asteroid_patrol_1_06", "nym_asteroid_patrol_1_07", "nym_asteroid_patrol_1_08", "nym_asteroid_patrol_1_09", "nym_asteroid_patrol_1_10", "nym_asteroid_patrol_1_11", "nym_asteroid_patrol_1_12", "nym_asteroid_patrol_1_13", "nym_asteroid_patrol_1_14", "nym_asteroid_patrol_1_15", "nym_asteroid_patrol_1_16", "nym_asteroid_patrol_1_17", "nym_asteroid_patrol_1_18", "nym_asteroid_patrol_1_19", "nym_asteroid_patrol_1_20", "nym_asteroid_patrol_1_21", "nym_asteroid_patrol_1_22", "nym_asteroid_patrol_1_23", "nym_asteroid_patrol_1_24", "nym_asteroid_patrol_1_25", "nym_asteroid_patrol_1_26", "nym_asteroid_patrol_1_27", "nym_asteroid_patrol_1_28", "nym_asteroid_patrol_1_29"},
			shipSpawns = {"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{spawnName = "debris_rebel_1", spawnType = SHIP_SPAWN_SQUADRON, x = 491, z = -3947, y = -17, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 10, minPatrol = 50, maxPatrol = 400, totalSpawns = 1,
			shipSpawns = {"squad_xwing_small_average"}
		},
		{spawnName = "nym_lieutenant_1", spawnType = SHIP_SPAWN_SINGLE, x = -3100, z = 642, y = 3067, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 50, maxPatrol = 400, totalSpawns = 1,
			shipSpawns = {"nym_lieutenant_tier2"}
		},
		{spawnName = "nyms_rebel_run_1", spawnType = SHIP_SPAWN_SINGLE, x = -3216, z = 955, y = 3084, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 1, maxSpawnDistance = 8, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"nyms_rebel_run_1_00", "nyms_rebel_run_1_01", "nyms_rebel_run_1_02", "nyms_rebel_run_1_03", "nyms_rebel_run_1_04", "nyms_rebel_run_1_05", "nyms_rebel_run_1_06", "nyms_rebel_run_1_07", "nyms_rebel_run_1_08", "nyms_rebel_run_1_09", "nyms_rebel_run_1_10", "nyms_rebel_run_1_11", "nyms_rebel_run_1_12", "nyms_rebel_run_1_13", "nyms_rebel_run_1_14", "nyms_rebel_run_1_15", "nyms_rebel_run_1_16", "nyms_rebel_run_1_17", "nyms_rebel_run_1_18", "nyms_rebel_run_1_19", "nyms_rebel_run_1_20", "nyms_rebel_run_1_21", "nyms_rebel_run_1_22", "nyms_rebel_run_1_23", "nyms_rebel_run_1_24", "nyms_rebel_run_1_25"},
			shipSpawns = {"nym_cannon_ship_tier2", "nym_enforcer_tier2", "nym_enforcer_tier3", "nym_fighter_tier2", "nym_star_kimogila_boss", "nym_enforcer_tier3", "nym_enforcer_tier3", "nym_enforcer_tier3", "nym_enforcer_tier3", "nym_enforcer_tier3", "nym_enforcer_tier2", "nym_enforcer_tier2", "nym_enforcer_tier2", "nym_enforcer_tier2", "nym_enforcer_tier2"}
		},
		{spawnName = "lok_base_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = -3170, z = 842, y = 3067, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 20, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 50, maxPatrol = 400, totalSpawns = 2,
			shipSpawns = {"nym_cannon_ship_tier2", "nym_enforcer_tier3", "nym_fighter_tier2", "nym_fighter_tier2", "nym_fighter_tier2", "nym_fighter_tier3"}
		},
		{spawnName = "bloodrazor_static_watch_3", spawnType = SHIP_SPAWN_SINGLE, x = -5254, z = 5479, y = 2273, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_destroyer_tier3"}
		},
		{spawnName = "bloozrazor_static_spine_2", spawnType = SHIP_SPAWN_SINGLE, x = -1280, z = 1958, y = 3786, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_destroyer_tier3", "bloodrazor_cutthroat_tier3"}
		},
		{spawnName = "bloodrazor_vs_kimogila_5", spawnType = SHIP_SPAWN_SINGLE, x = 587, z = 1468, y = 5966, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_cutthroat_tier2", "bloodrazor_berzerker_tier2", "bloodrazor_destroyer_tier3"}
		},
		{spawnName = "kimogila_vs_bloodrazor_5", spawnType = SHIP_SPAWN_SINGLE, x = 533, z = 1390, y = 6273, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"kimogila_scrapper_tier2", "kimogila_inciter_tier2", "kimogila_champion_tier3"}
		},
		{spawnName = "corsair_static_base_5", spawnType = SHIP_SPAWN_SINGLE, x = -240, z = 3688, y = 4669, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"corsair_sloop_tier3"}
		},
		{spawnName = "kimogila_vs_bloodrazor_1", spawnType = SHIP_SPAWN_SINGLE, x = 305, z = 5182, y = 5808, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"kimogila_scrapper_tier2", "kimogila_inciter_tier2", "kimogila_champion_tier3"}
		},
		{spawnName = "bloodrazor_static_watch_2", spawnType = SHIP_SPAWN_SINGLE, x = -2474, z = -1852, y = 5003, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_berzerker_tier2"}
		},
		{spawnName = "bloodrazor_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = -5649, z = -1837, y = 5976, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"bloodrazor_patrol_1_00", "bloodrazor_patrol_1_01", "bloodrazor_patrol_1_02", "bloodrazor_patrol_1_03", "bloodrazor_patrol_1_04", "bloodrazor_patrol_1_05", "bloodrazor_patrol_1_06", "bloodrazor_patrol_1_07", "bloodrazor_patrol_1_08", "bloodrazor_patrol_1_09", "bloodrazor_patrol_1_10", "bloodrazor_patrol_1_11", "bloodrazor_patrol_1_12", "bloodrazor_patrol_1_13", "bloodrazor_patrol_1_14"},
			shipSpawns = {"bloodrazor_berzerker_tier3", "bloodrazor_cutthroat_tier3"}
		},
		{spawnName = "bloodrazor_static_3", spawnType = SHIP_SPAWN_SINGLE, x = -4421, z = 441, y = 6868, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_destroyer_tier2", "bloodrazor_cutthroat_tier2"}
		},
		{spawnName = "bloodrazor_boss", spawnType = SHIP_SPAWN_SINGLE, x = -4737, z = 5755, y = 5372, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_captain_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_cutthroat_tier3"}
		},
		{spawnName = "bloodrazor_static_watch_4", spawnType = SHIP_SPAWN_SINGLE, x = -6845, z = 5015, y = 3354, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_cutthroat_tier2", "bloodrazor_berzerker_tier2", "bloodrazor_destroyer_tier3"}
		},
		{spawnName = "bloodrazor_static_watch_1", spawnType = SHIP_SPAWN_SINGLE, x = -5832, z = 6823, y = 4644, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_cutthroat_tier2"}
		},
		{spawnName = "bloodrazor_patrol_2", spawnType = SHIP_SPAWN_SINGLE, x = -6522, z = 4280, y = 6263, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"bloodrazor_patrol_2_00", "bloodrazor_patrol_2_01", "bloodrazor_patrol_2_02", "bloodrazor_patrol_2_03", "bloodrazor_patrol_2_04", "bloodrazor_patrol_2_05", "bloodrazor_patrol_2_06", "bloodrazor_patrol_2_07", "bloodrazor_patrol_2_08"},
			shipSpawns = {"bloodrazor_destroyer_tier3", "bloodrazor_cutthroat_tier3", "bloodrazor_berzerker_tier2"}
		},
		{spawnName = "corsair_static_base_2", spawnType = SHIP_SPAWN_SINGLE, x = 2461, z = -3943, y = 6131, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"corsair_raider_tier3"}
		},
		{spawnName = "kimogila_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = 5349, z = 7498, y = 6604, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"kimogila_patrol_1_00", "kimogila_patrol_1_01", "kimogila_patrol_1_02", "kimogila_patrol_1_03", "kimogila_patrol_1_04", "kimogila_patrol_1_05", "kimogila_patrol_1_06", "kimogila_patrol_1_07", "kimogila_patrol_1_08", "kimogila_patrol_1_09", "kimogila_patrol_1_10", "kimogila_patrol_1_11", "kimogila_patrol_1_12", "kimogila_patrol_1_13", "kimogila_patrol_1_14", "kimogila_patrol_1_15", "kimogila_patrol_1_16"},
			shipSpawns = {"kimogila_scrapper_tier2", "kimogila_inciter_tier3"}
		},
		{spawnName = "kimogila_battlelord", spawnType = SHIP_SPAWN_SINGLE, x = 6543, z = 7012, y = 5471, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"kimogila_battlelord_tier3", "kimogila_champion_tier2", "kimogila_champion_tier2", "kimogila_champion_tier2", "kimogila_champion_tier2", "kimogila_inciter_tier2", "kimogila_inciter_tier2", "kimogila_inciter_tier2", "kimogila_inciter_tier2", "kimogila_scrapper_tier2", "kimogila_scrapper_tier2", "kimogila_scrapper_tier2"}
		},
		{spawnName = "kimogila_static_3", spawnType = SHIP_SPAWN_SINGLE, x = 3657, z = 5032, y = 7486, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"kimogila_scrapper_tier3", "kimogila_champion_tier3"}
		},
		{spawnName = "corsair_base_static_1", spawnType = SHIP_SPAWN_SINGLE, x = 1677, z = 4097, y = 4410, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"corsair_manowar_tier3"}
		},
		{spawnName = "naboo_privateer_tier3_leg_3_destroy", spawnType = SHIP_SPAWN_SINGLE, x = -2352, z = 1808, y = -3496, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 45, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"blacksun_marauder_tier2", "blacksun_marauder_tier3"}
		},
		{spawnName = "kimogila_static_watch_2", spawnType = SHIP_SPAWN_SINGLE, x = 6531, z = 576, y = 926, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"kimogila_scrapper_tier2"}
		},
		{spawnName = "bloozrazor_static_spine_1", spawnType = SHIP_SPAWN_SINGLE, x = 167, z = 885, y = 5542, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"bloodrazor_destroyer_tier3", "bloodrazor_cutthroat_tier3"}
		},
		{spawnName = "trade_fed_base_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = 2820, z = 252, y = 2804, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 32, minPatrol = 50, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"imp_tie_fighter_tier2", "imp_tie_fighter_tier3"}
		},
		{spawnName = "trade_fed_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 3058, z = 249, y = 3156, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 2, maxSpawnDistance = 4, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"trade_fed_route_1_00", "trade_fed_route_1_01", "trade_fed_route_1_02", "trade_fed_route_1_03", "trade_fed_route_1_04", "trade_fed_route_1_05", "trade_fed_route_1_06", "trade_fed_route_1_07", "trade_fed_route_1_08", "trade_fed_route_1_09", "trade_fed_route_1_10", "trade_fed_route_1_11", "trade_fed_route_1_12", "trade_fed_route_1_13", "trade_fed_route_1_14", "trade_fed_route_1_15", "trade_fed_route_1_16", "trade_fed_route_1_17", "trade_fed_route_1_18", "trade_fed_route_1_19", "trade_fed_route_1_20"},
			shipSpawns = {"freighterlight_tier3", "freighterlight_tier3", "freighterlight_tier3", "freighterheavy_tier3", "freighterheavy_tier3", "freightermedium_tier3", "freightermedium_tier3", "freightermedium_tier3"}
		},
		{spawnName = "trade_fed_route_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = 3071, z = 246, y = 3151, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 4, maxSpawnDistance = 6, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"trade_fed_route_guard_1_00", "trade_fed_route_guard_1_01", "trade_fed_route_guard_1_02", "trade_fed_route_guard_1_03", "trade_fed_route_guard_1_04", "trade_fed_route_guard_1_05", "trade_fed_route_guard_1_06", "trade_fed_route_guard_1_07", "trade_fed_route_guard_1_08", "trade_fed_route_guard_1_09", "trade_fed_route_guard_1_10", "trade_fed_route_guard_1_11", "trade_fed_route_guard_1_12", "trade_fed_route_guard_1_13", "trade_fed_route_guard_1_14", "trade_fed_route_guard_1_15", "trade_fed_route_guard_1_16", "trade_fed_route_guard_1_17", "trade_fed_route_guard_1_18", "trade_fed_route_guard_1_19", "trade_fed_route_guard_1_20", "trade_fed_route_guard_1_21", "trade_fed_route_guard_1_22"},
			shipSpawns = {"imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier3"}
		},
		{spawnName = "yavin_rebel_mission_3", spawnType = SHIP_SPAWN_SQUADRON, x = -5150, z = 2430, y = 586, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 10, maxRespawn = 30, minSpawnDistance = 30, maxSpawnDistance = 60, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"yavin_rebel_mission_3_00", "yavin_rebel_mission_3_01", "yavin_rebel_mission_3_02", "yavin_rebel_mission_3_03", "yavin_rebel_mission_3_04"},
			shipSpawns = {"squad_yavin_rebel_3", "yavin_mission_3_shuttle"}
		},
		{spawnName = "imp_guard_hyperspace", spawnType = SHIP_SPAWN_SINGLE, x = -5332, z = -1477, y = -6866, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"imp_tie_fighter_tier3", "imp_tie_bomber_tier3", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "static_to_station_1", spawnType = SHIP_SPAWN_SINGLE, x = -6130, z = -1486, y = -6667, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"static_to_station_1_00", "static_to_station_1_01", "static_to_station_1_02", "static_to_station_1_03", "static_to_station_1_04", "static_to_station_1_05", "static_to_station_1_06"},
			shipSpawns = {"freighterheavy_tier3_story", "nebula_scientist_researcher_tier3", "smuggler_freighterlight_tier3"}
		},
		{spawnName = "corsair_nebula_4", spawnType = SHIP_SPAWN_SINGLE, x = 2996, z = 2032, y = -2178, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 18, minSpawnDistance = 8, maxSpawnDistance = 32, minPatrol = 50, maxPatrol = 350, totalSpawns = 3,
			shipSpawns = {"corsair_behemoth_tier2", "corsair_raider_tier2"}
		},
		{spawnName = "corsair_nebula_2", spawnType = SHIP_SPAWN_SINGLE, x = 2049, z = 3681, y = -1914, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 32, minPatrol = 50, maxPatrol = 350, totalSpawns = 3,
			shipSpawns = {"corsair_raider_tier2", "corsair_sloop_tier2"}
		},
		{spawnName = "rebel_testing_droid_attack_1", spawnType = SHIP_SPAWN_SQUADRON, x = 3063, z = 4594, y = -1337, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 7200, maxRespawn = 10800, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_testing_droid_attack_1_00", "rebel_testing_droid_attack_1_01", "rebel_testing_droid_attack_1_02", "rebel_testing_droid_attack_1_03", "rebel_testing_droid_attack_1_04"},
			shipSpawns = {"squad_rebel_testing_droids"}
		},
		{spawnName = "rebel_testing_squad_1", spawnType = SHIP_SPAWN_SQUADRON, x = 3016, z = 2978, y = -1305, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 1, maxSpawnDistance = 150, minPatrol = 50, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_bwing_standard_ace"}
		},
		{spawnName = "kimogila_static_watch_4", spawnType = SHIP_SPAWN_SINGLE, x = 5096, z = 3, y = 2093, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"kimogila_champion_tier3"}
		},
		{spawnName = "nym_fighters_1", spawnType = SHIP_SPAWN_SINGLE, x = 5436, z = -1865, y = 1555, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 5, maxSpawnDistance = 20, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"nym_fighters_1_00", "nym_fighters_1_01", "nym_fighters_1_02", "nym_fighters_1_03", "nym_fighters_1_04"},
			shipSpawns = {"nym_cannon_ship_tier2", "nym_cannon_ship_tier2", "nym_enforcer_tier2", "nym_enforcer_tier2", "nym_lieutenant_tier2"}
		},
		{spawnName = "imp_vs_nym_2", spawnType = SHIP_SPAWN_SINGLE, x = 6726, z = -4385, y = 1371, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"imp_tie_bomber_tier2", "imp_tie_fighter_tier2", "imp_tie_advanced_tier3", "imp_tie_aggressor_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "nym_vs_imp_2", spawnType = SHIP_SPAWN_SINGLE, x = 6436, z = -4417, y = 1427, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{spawnName = "tie_debris_nym_route", spawnType = SHIP_SPAWN_SQUADRON, x = 522, z = -3937, y = -462, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 300, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"tie_debris_nym_route_00", "tie_debris_nym_route_01", "tie_debris_nym_route_02", "tie_debris_nym_route_03", "tie_debris_nym_route_04", "tie_debris_nym_route_05", "tie_debris_nym_route_06"},
			shipSpawns = {"squad_nym_fighter_wing"}
		},
		{spawnName = "nym_mining_field_route_1", spawnType = SHIP_SPAWN_SQUADRON, x = 2190, z = -7120, y = -1538, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"nym_mining_field_route_1_00", "nym_mining_field_route_1_01", "nym_mining_field_route_1_02", "nym_mining_field_route_1_03", "nym_mining_field_route_1_04", "nym_mining_field_route_1_05"},
			shipSpawns = {"squad_mining_freighter_nym"}
		},
		{spawnName = "imp_gunboat_to_nym", spawnType = SHIP_SPAWN_SINGLE, x = 6328, z = 5949, y = -214, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imp_gunboat_to_nym_00", "imp_gunboat_to_nym_01", "imp_gunboat_to_nym_02", "imp_gunboat_to_nym_03", "imp_gunboat_to_nym_04", "imp_gunboat_to_nym_05", "imp_gunboat_to_nym_06", "imp_gunboat_to_nym_07", "imp_gunboat_to_nym_08", "imp_gunboat_to_nym_09", "imp_gunboat_to_nym_10", "imp_gunboat_to_nym_11", "imp_gunboat_to_nym_12", "imp_gunboat_to_nym_13", "imp_gunboat_to_nym_14", "imp_gunboat_to_nym_15", "imp_gunboat_to_nym_16", "imp_gunboat_to_nym_17", "imp_gunboat_to_nym_18", "imp_gunboat_to_nym_19"},
			shipSpawns = {"imp_imperial_gunboat_tier3"}
		},
		{spawnName = "nym_mining_freighters_1", spawnType = SHIP_SPAWN_SINGLE, x = 2153, z = -3725, y = -1491, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 40, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 50, maxPatrol = 400, totalSpawns = 3,
			shipSpawns = {"nym_bomber_tier2", "nym_enforcer_tier2"}
		},
		{spawnName = "nym_mining_field_guard", spawnType = SHIP_SPAWN_SINGLE, x = 2131, z = -3707, y = -1471, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"nym_bomber_tier2", "nym_fighter_tier2"}
		},
		{spawnName = "nym_gunboat_run_1", spawnType = SHIP_SPAWN_SINGLE, x = 5133, z = -1559, y = -5413, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"nym_gunboat_run_1_00", "nym_gunboat_run_1_01", "nym_gunboat_run_1_02", "nym_gunboat_run_1_03", "nym_gunboat_run_1_04", "nym_gunboat_run_1_05", "nym_gunboat_run_1_06", "nym_gunboat_run_1_07", "nym_gunboat_run_1_08", "nym_gunboat_run_1_09", "nym_gunboat_run_1_10", "nym_gunboat_run_1_11", "nym_gunboat_run_1_12", "nym_gunboat_run_1_13", "nym_gunboat_run_1_14", "nym_gunboat_run_1_15", "nym_gunboat_run_1_16", "nym_gunboat_run_1_17", "nym_gunboat_run_1_18", "nym_gunboat_run_1_19", "nym_gunboat_run_1_20", "nym_gunboat_run_1_21", "nym_gunboat_run_1_22", "nym_gunboat_run_1_23", "nym_gunboat_run_1_24", "nym_gunboat_run_1_25", "nym_gunboat_run_1_26", "nym_gunboat_run_1_27", "nym_gunboat_run_1_28", "nym_gunboat_run_1_29"},
			shipSpawns = {"nym_gunship_tier3"}
		},
		{spawnName = "rebel_guard_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 3670, z = -2555, y = -3934, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 4, maxSpawnDistance = 42, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_guard_route_1_00", "rebel_guard_route_1_01", "rebel_guard_route_1_02", "rebel_guard_route_1_03", "rebel_guard_route_1_04", "rebel_guard_route_1_05", "rebel_guard_route_1_06", "rebel_guard_route_1_07", "rebel_guard_route_1_08", "rebel_guard_route_1_09"},
			shipSpawns = {"reb_z95_tier3", "reb_xwing_tier3"}
		},
		{spawnName = "nebulon_rebel_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 3931, z = -411, y = -3770, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 32, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"nebulon_rebel_route_1_00", "nebulon_rebel_route_1_01", "nebulon_rebel_route_1_02", "nebulon_rebel_route_1_03", "nebulon_rebel_route_1_04", "nebulon_rebel_route_1_05", "nebulon_rebel_route_1_06", "nebulon_rebel_route_1_07", "nebulon_rebel_route_1_08", "nebulon_rebel_route_1_09"},
			shipSpawns = {"reb_awing_tier3", "reb_bwing_tier3", "reb_xwing_tier3", "reb_ywing_tier3", "reb_z95_tier3"}
		},
		{spawnName = "rebel_equipment_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 2033, z = -2311, y = -3680, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 2, maxSpawnDistance = 4, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_equipment_route_1_00", "rebel_equipment_route_1_01", "rebel_equipment_route_1_02", "rebel_equipment_route_1_03", "rebel_equipment_route_1_04", "rebel_equipment_route_1_05", "rebel_equipment_route_1_06", "rebel_equipment_route_1_07", "rebel_equipment_route_1_08", "rebel_equipment_route_1_09", "rebel_equipment_route_1_10", "rebel_equipment_route_1_11", "rebel_equipment_route_1_12", "rebel_equipment_route_1_13", "rebel_equipment_route_1_14", "rebel_equipment_route_1_15", "rebel_equipment_route_1_16", "rebel_equipment_route_1_17", "rebel_equipment_route_1_18", "rebel_equipment_route_1_19", "rebel_equipment_route_1_20"},
			shipSpawns = {"reb_xwing_tier2", "reb_ywing_tier2", "reb_ywing_tier3", "reb_freightermedium_tier3", "reb_freighterlight_tier3", "reb_freighterlight_tier3", "reb_freighterheavy_tier3"}
		},
		{spawnName = "rebel_outpost_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = 1811, z = -2167, y = -3456, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"reb_z95_tier2", "reb_z95_tier3"}
		},
		{spawnName = "corsair_nebula_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = 3078, z = -645, y = -2264, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 64, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"corsair_nebula_patrol_1_00", "corsair_nebula_patrol_1_01", "corsair_nebula_patrol_1_02", "corsair_nebula_patrol_1_03", "corsair_nebula_patrol_1_04", "corsair_nebula_patrol_1_05", "corsair_nebula_patrol_1_06", "corsair_nebula_patrol_1_07"},
			shipSpawns = {"corsair_behemoth_tier3"}
		},
		{spawnName = "nyms_boys", spawnType = SHIP_SPAWN_SINGLE, x = 3719, z = -2284, y = -1151, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 30, maxSpawnDistance = 45, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"nyms_boys_00", "nyms_boys_01", "nyms_boys_02", "nyms_boys_03", "nyms_boys_04", "nyms_boys_05", "nyms_boys_06"},
			shipSpawns = {"nym_cannon_ship_tier2", "nym_enforcer_tier3"}
		},
		{spawnName = "kimogila_vs_bloodrazor_4", spawnType = SHIP_SPAWN_SINGLE, x = -3095, z = 3631, y = 3774, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"kimogila_scrapper_tier2", "kimogila_inciter_tier2", "kimogila_champion_tier3"}
		},
		{spawnName = "bloodrazor_static_4", spawnType = SHIP_SPAWN_SINGLE, x = -1839, z = 6481, y = 3316, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_berzerker_tier3", "bloodrazor_destroyer_tier3"}
		},
		{spawnName = "bloodrazor_vs_kimogila_2", spawnType = SHIP_SPAWN_SINGLE, x = -562, z = 6191, y = 1836, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_cutthroat_tier2", "bloodrazor_berzerker_tier3", "bloodrazor_destroyer_tier2"}
		},
		{spawnName = "erkon_the_vile", spawnType = SHIP_SPAWN_SINGLE, x = 3047, z = 7029, y = 1403, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 86400, maxRespawn = 172800, minSpawnDistance = 1, maxSpawnDistance = 30, minPatrol = 400, maxPatrol = 3000, totalSpawns = 1,
			shipSpawns = {"erkon_the_vile"}
		},
		{spawnName = "kimogila_static_1", spawnType = SHIP_SPAWN_SINGLE, x = 4380, z = 4967, y = 5546, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"kimogila_champion_tier3", "kimogila_scrapper_tier2", "kimogila_inciter_tier2"}
		},
		{spawnName = "kimogila_static_watch_1", spawnType = SHIP_SPAWN_SINGLE, x = 5655, z = 2680, y = 3481, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"kimogila_champion_tier3"}
		},
		{spawnName = "bloodrazor_vs_kimogila_4", spawnType = SHIP_SPAWN_SINGLE, x = -3253, z = -1988, y = 3894, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bloodrazor_cutthroat_tier2", "bloodrazor_berzerker_tier2", "bloodrazor_destroyer_tier3"}
		},
		{spawnName = "vortex_mission_1_shuttle", spawnType = SHIP_SPAWN_SINGLE, x = -3745, z = -3124, y = -658, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 10, maxRespawn = 30, minSpawnDistance = 30, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"vortex_mission_1_shuttle_00", "vortex_mission_1_shuttle_01", "vortex_mission_1_shuttle_02", "vortex_mission_1_shuttle_03", "vortex_mission_1_shuttle_04", "vortex_mission_1_shuttle_05", "vortex_mission_1_shuttle_06", "vortex_mission_1_shuttle_07"},
			shipSpawns = {"vortex_mission_1_shuttle"}
		},
		{spawnName = "nym_lieutenant_lokstation_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -6364, z = -5296, y = 1432, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 30, maxRespawn = 45, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"nym_lieutenant_lokstation_spawner_00", "nym_lieutenant_lokstation_spawner_01", "nym_lieutenant_lokstation_spawner_02", "nym_lieutenant_lokstation_spawner_03"},
			shipSpawns = {"nym_lieutenant_tier2"}
		},
		{spawnName = "nym_fodder_1", spawnType = SHIP_SPAWN_SINGLE, x = 7016, z = -5554, y = -4957, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"nym_bomber_tier3", "nym_enforcer_tier3"}
		},
		{spawnName = "imp_vs_nym_3", spawnType = SHIP_SPAWN_SINGLE, x = 6016, z = -5694, y = -2817, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 350, totalSpawns = 6,
			shipSpawns = {"imp_tie_fighter_tier2", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "nym_vs_imp_3", spawnType = SHIP_SPAWN_SINGLE, x = 6107, z = -5789, y = -3058, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 350, totalSpawns = 4,
			shipSpawns = {"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{spawnName = "imp_vs_nym_4", spawnType = SHIP_SPAWN_SINGLE, x = 5948, z = -6901, y = 224, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"imp_tie_fighter_tier2", "imp_tie_bomber_tier2", "imp_tie_advanced_tier2", "imp_tie_aggressor_tier2", "imp_tie_interceptor_tier2", "imp_tie_oppressor_tier2"}
		},
		{spawnName = "nym_vs_imp_4", spawnType = SHIP_SPAWN_SINGLE, x = 5764, z = -7026, y = -231, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"nym_enforcer_tier2"}
		},
		{spawnName = "nym_vs_imperial_1", spawnType = SHIP_SPAWN_SINGLE, x = 4999, z = -4746, y = -556, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{spawnName = "imp_vs_nym_1", spawnType = SHIP_SPAWN_SINGLE, x = 4940, z = -4509, y = -205, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"imp_tie_fighter_tier3", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3", "imp_tie_advanced_tier3", "imp_tie_interceptor_tier3", "imp_tie_oppressor_tier3"}
		},
		{spawnName = "nym_static_beacon_1", spawnType = SHIP_SPAWN_SINGLE, x = 2560, z = -4878, y = -4120, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{spawnName = "nym_trade_attack_1", spawnType = SHIP_SPAWN_SINGLE, x = 711, z = -4072, y = 2409, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 40, maxSpawnDistance = 80, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"nym_trade_attack_1_00", "nym_trade_attack_1_01", "nym_trade_attack_1_02", "nym_trade_attack_1_03", "nym_trade_attack_1_04", "nym_trade_attack_1_05", "nym_trade_attack_1_06"},
			shipSpawns = {"nym_bomber_tier2", "nym_fighter_tier2", "nym_fighter_tier2", "nym_fighter_tier2", "nym_fighter_tier2", "nym_fighter_tier2"}
		},
		{spawnName = "kimogila_vs_bloodrazor_2", spawnType = SHIP_SPAWN_SINGLE, x = -233, z = 1695, y = 1799, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"kimogila_scrapper_tier2", "kimogila_inciter_tier2", "kimogila_champion_tier3"}
		},
		{spawnName = "nym_lieutenant_2", spawnType = SHIP_SPAWN_SINGLE, x = 729, z = -843, y = 2438, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 30, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"nym_lieutenant_2_00", "nym_lieutenant_2_01", "nym_lieutenant_2_02", "nym_lieutenant_2_03", "nym_lieutenant_2_04", "nym_lieutenant_2_05"},
			shipSpawns = {"nym_lieutenant_tier2"}
		},
		{spawnName = "nym_static_beacon_2", spawnType = SHIP_SPAWN_SINGLE, x = -77, z = -2347, y = -1573, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"nym_bomber_tier2", "nym_enforcer_tier3"}
		},
		{spawnName = "imperial_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = -1531, z = 3202, y = 325, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_patrol_1_00", "imperial_patrol_1_01", "imperial_patrol_1_02", "imperial_patrol_1_03", "imperial_patrol_1_04", "imperial_patrol_1_05", "imperial_patrol_1_06", "imperial_patrol_1_07", "imperial_patrol_1_08", "imperial_patrol_1_09", "imperial_patrol_1_10", "imperial_patrol_1_11", "imperial_patrol_1_12", "imperial_patrol_1_13"},
			shipSpawns = {"imp_tie_fighter_tier3", "imp_tie_bomber_tier3", "imp_tie_aggressor_tier3"}
		},
		{spawnName = "imperial_outpost_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = -1553, z = 2866, y = 206, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier2", "imp_tie_advanced_tier2", "imp_tie_aggressor_tier2", "imp_tie_oppressor_tier2"}
		},
		{spawnName = "tie_investigation_route_1", spawnType = SHIP_SPAWN_SQUADRON, x = -1486, z = 2057, y = 360, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 150, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"tie_investigation_route_1_00", "tie_investigation_route_1_01", "tie_investigation_route_1_02", "tie_investigation_route_1_03", "tie_investigation_route_1_04", "tie_investigation_route_1_05"},
			shipSpawns = {"squad_tie_standard_average"}
		},
		{spawnName = "viopa_rebel_1_shuttle", spawnType = SHIP_SPAWN_SQUADRON, x = 2102, z = 1022, y = 2191, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 10, maxRespawn = 30, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"viopa_rebel_1_shuttle_00", "viopa_rebel_1_shuttle_01", "viopa_rebel_1_shuttle_02", "viopa_rebel_1_shuttle_03"},
			shipSpawns = {"squad_viopa_rebel_1"}
		},
		{spawnName = "rebel_vs_corsair_1", spawnType = SHIP_SPAWN_SINGLE, x = 1782, z = -205, y = 2312, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"reb_xwing_tier3", "reb_xwing_tier3", "reb_ywing_tier2", "reb_z95_tier2"}
		},
		{spawnName = "corsair_vs_rebel_1", spawnType = SHIP_SPAWN_SINGLE, x = 1932, z = -231, y = 2208, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"corsair_raider_tier3", "corsair_manowar_tier3"}
		},
		{spawnName = "rebel_testing_droid_squad_2", spawnType = SHIP_SPAWN_SQUADRON, x = 3008, z = 1166, y = -1275, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 7200, maxRespawn = 10800, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_testing_droid_squad_2_00", "rebel_testing_droid_squad_2_01", "rebel_testing_droid_squad_2_02", "rebel_testing_droid_squad_2_03", "rebel_testing_droid_squad_2_04"},
			shipSpawns = {"squad_rebel_testing_droids", "rebel_droid_training_boss"}
		},
		{spawnName = "nym_lieutenant_3", spawnType = SHIP_SPAWN_SINGLE, x = 39, z = -134, y = -2666, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 30, maxSpawnDistance = 80, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"nym_lieutenant_3_00", "nym_lieutenant_3_01", "nym_lieutenant_3_02", "nym_lieutenant_3_03", "nym_lieutenant_3_04"},
			shipSpawns = {"nym_lieutenant_tier2"}
		},
		{spawnName = "nym_corsair_attack_1", spawnType = SHIP_SPAWN_SINGLE, x = 65, z = -86, y = -2637, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 50, maxSpawnDistance = 80, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"nym_corsair_attack_1_00", "nym_corsair_attack_1_01", "nym_corsair_attack_1_02", "nym_corsair_attack_1_03", "nym_corsair_attack_1_04"},
			shipSpawns = {"nym_bomber_tier2", "nym_enforcer_tier2", "nym_enforcer_tier3"}
		},
		{spawnName = "corsair_nebula_1", spawnType = SHIP_SPAWN_SINGLE, x = 1777, z = -34, y = -2495, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 32, minPatrol = 50, maxPatrol = 350, totalSpawns = 3,
			shipSpawns = {"corsair_sloop_tier3"}
		},
		{spawnName = "corsair_nebula_3", spawnType = SHIP_SPAWN_SINGLE, x = 2476, z = 2016, y = -1465, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 32, minPatrol = 50, maxPatrol = 350, totalSpawns = 4,
			shipSpawns = {"corsair_manowar_tier2", "corsair_raider_tier2", "corsair_shadowstalker", "corsair_manowar_tier2", "corsair_manowar_tier2", "corsair_manowar_tier2", "corsair_manowar_tier2", "corsair_raider_tier2", "corsair_raider_tier2", "corsair_raider_tier2"}
		},
		{spawnName = "trade_fed_research_static_1", spawnType = SHIP_SPAWN_SINGLE, x = -1110, z = -4204, y = -2888, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"trade_fed_fighter", "trade_fed_bomber"}
		},
		{spawnName = "trade_fed_static_base", spawnType = SHIP_SPAWN_SINGLE, x = -636, z = -4091, y = -6175, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"trade_fed_fighter", "trade_fed_bomber"}
		},
		{spawnName = "trade_fed_research_static_2", spawnType = SHIP_SPAWN_SINGLE, x = 335, z = -4091, y = -3621, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"trade_fed_fighter", "trade_fed_bomber"}
		},
		{spawnName = "trade_fed_research_freighters", spawnType = SHIP_SPAWN_SINGLE, x = -1714, z = -4228, y = -5813, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 420, maxRespawn = 520, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"trade_fed_research_freighters_00", "trade_fed_research_freighters_01", "trade_fed_research_freighters_02", "trade_fed_research_freighters_03", "trade_fed_research_freighters_04", "trade_fed_research_freighters_05", "trade_fed_research_freighters_06", "trade_fed_research_freighters_07", "trade_fed_research_freighters_08", "trade_fed_research_freighters_09", "trade_fed_research_freighters_10", "trade_fed_research_freighters_11", "trade_fed_research_freighters_12", "trade_fed_research_freighters_13", "trade_fed_research_freighters_14", "trade_fed_research_freighters_15", "trade_fed_research_freighters_16"},
			shipSpawns = {"naboo_miner_transport", "nebula_scientist_researcher_tier3"}
		},
		{spawnName = "trade_fed_station_patrol", spawnType = SHIP_SPAWN_SINGLE, x = -1756, z = -4207, y = -5108, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"trade_fed_station_patrol_00", "trade_fed_station_patrol_01", "trade_fed_station_patrol_02", "trade_fed_station_patrol_03", "trade_fed_station_patrol_04", "trade_fed_station_patrol_05", "trade_fed_station_patrol_06", "trade_fed_station_patrol_07", "trade_fed_station_patrol_08", "trade_fed_station_patrol_09", "trade_fed_station_patrol_10", "trade_fed_station_patrol_11", "trade_fed_station_patrol_12", "trade_fed_station_patrol_13", "trade_fed_station_patrol_14"},
			shipSpawns = {"trade_fed_fighter", "trade_fed_bomber"}
		},
	},
}

registerScreenPlay("SpaceLokSpawner", true)
