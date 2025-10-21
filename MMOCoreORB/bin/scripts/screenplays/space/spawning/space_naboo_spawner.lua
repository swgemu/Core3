SpaceNabooSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceNabooSpawner",

	spaceZone = "space_naboo",

	shipSpawns = {
		{spawnName = "rogue_droid_generator", spawnType = SHIP_SPAWN_SINGLE, x = -7133, z = 1932, y = -977, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"rogue_droid_generator_00", "rogue_droid_generator_01", "rogue_droid_generator_02", "rogue_droid_generator_03", "rogue_droid_generator_04", "rogue_droid_generator_05", "rogue_droid_generator_06", "rogue_droid_generator_07", "rogue_droid_generator_08", "rogue_droid_generator_09", "rogue_droid_generator_10", "rogue_droid_generator_11", "rogue_droid_generator_12", "rogue_droid_generator_13", "rogue_droid_generator_14", "rogue_droid_generator_15", "rogue_droid_generator_16", "rogue_droid_generator_17", "rogue_droid_generator_18"},
			shipSpawns = {"rogue_droid_bomber", "rogue_droid_defender_tier1", "rogue_droid_defender_tier1_naboo", "rogue_droid_fighter_tier1", "rogue_droid_fighter_tier1_naboo", "rogue_droid_scrapper_tier1_naboo"}
		},
		{spawnName = "rogue_droid_boss", spawnType = SHIP_SPAWN_SINGLE, x = -7118, z = 1949, y = -1078, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 7200, maxRespawn = 10800, minSpawnDistance = 5, maxSpawnDistance = 15, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rogue_droid_boss_00", "rogue_droid_boss_01", "rogue_droid_boss_02", "rogue_droid_boss_03", "rogue_droid_boss_04", "rogue_droid_boss_05", "rogue_droid_boss_06", "rogue_droid_boss_07", "rogue_droid_boss_08", "rogue_droid_boss_09", "rogue_droid_boss_10", "rogue_droid_boss_11", "rogue_droid_boss_12", "rogue_droid_boss_13", "rogue_droid_boss_14", "rogue_droid_boss_15", "rogue_droid_boss_16", "rogue_droid_boss_17", "rogue_droid_boss_18", "rogue_droid_boss_19", "rogue_droid_boss_20", "rogue_droid_boss_21", "rogue_droid_boss_22", "rogue_droid_boss_23", "rogue_droid_boss_24", "rogue_droid_boss_25", "rogue_droid_boss_26", "rogue_droid_boss_27", "rogue_droid_boss_28", "rogue_droid_boss_29", "rogue_droid_boss_30", "rogue_droid_boss_31", "rogue_droid_boss_32", "rogue_droid_boss_33", "rogue_droid_boss_34", "rogue_droid_boss_35", "rogue_droid_boss_36", "rogue_droid_boss_37", "rogue_droid_boss_38", "rogue_droid_boss_39", "rogue_droid_boss_40", "rogue_droid_boss_41", "rogue_droid_boss_42", "rogue_droid_boss_43", "rogue_droid_boss_44", "rogue_droid_boss_45", "rogue_droid_boss_46", "rogue_droid_boss_47"},
			shipSpawns = {"rogue_droid_boss"}
		},
		{spawnName = "rogue_droid_scrapper_route", spawnType = SHIP_SPAWN_SINGLE, x = -7167, z = 1933, y = -1052, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"rogue_droid_scrapper_route_00", "rogue_droid_scrapper_route_01", "rogue_droid_scrapper_route_02", "rogue_droid_scrapper_route_03", "rogue_droid_scrapper_route_04", "rogue_droid_scrapper_route_05", "rogue_droid_scrapper_route_06", "rogue_droid_scrapper_route_07", "rogue_droid_scrapper_route_08", "rogue_droid_scrapper_route_09", "rogue_droid_scrapper_route_10"},
			shipSpawns = {"rogue_droid_scrapper_tier1", "rogue_droid_scrapper_tier1_naboo"}
		},
		{spawnName = "borvo_static_patrol_three", spawnType = SHIP_SPAWN_SINGLE, x = -2389, z = -5285, y = -810, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1_naboo", "borvo_fighter_tier1", "borvo_fighter_tier1_naboo"}
		},
		{spawnName = "borvo_static_patrol_four", spawnType = SHIP_SPAWN_SINGLE, x = -3672, z = -7131, y = 2145, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1_naboo"}
		},
		{spawnName = "borvo_boss", spawnType = SHIP_SPAWN_SINGLE, x = -3654, z = -5367, y = 2378, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 7200, maxRespawn = 10800, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"borvo_boss_00", "borvo_boss_01", "borvo_boss_02", "borvo_boss_03", "borvo_boss_04", "borvo_boss_05", "borvo_boss_06", "borvo_boss_07", "borvo_boss_08", "borvo_boss_09", "borvo_boss_10", "borvo_boss_11", "borvo_boss_12", "borvo_boss_13", "borvo_boss_14", "borvo_boss_15", "borvo_boss_16", "borvo_boss_17", "borvo_boss_18", "borvo_boss_19", "borvo_boss_20", "borvo_boss_21", "borvo_boss_22", "borvo_boss_23", "borvo_boss_24", "borvo_boss_25", "borvo_boss_26", "borvo_boss_27", "borvo_boss_28", "borvo_boss_29", "borvo_boss_30", "borvo_boss_31", "borvo_boss_32", "borvo_boss_33", "borvo_boss_34", "borvo_boss_35", "borvo_boss_36", "borvo_boss_37", "borvo_boss_38", "borvo_boss_39", "borvo_boss_40", "borvo_boss_41", "borvo_boss_42", "borvo_boss_43", "borvo_boss_44", "borvo_boss_45", "borvo_boss_46", "borvo_boss_47", "borvo_boss_48", "borvo_boss_49", "borvo_boss_50", "borvo_boss_51", "borvo_boss_52"},
			shipSpawns = {"borvo_boss_tier3"}
		},
		{spawnName = "borvos_boys_route_base", spawnType = SHIP_SPAWN_SINGLE, x = -3637, z = -5422, y = 2523, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"borvos_boys_route_base_00", "borvos_boys_route_base_01", "borvos_boys_route_base_02", "borvos_boys_route_base_03", "borvos_boys_route_base_04", "borvos_boys_route_base_05", "borvos_boys_route_base_06", "borvos_boys_route_base_07", "borvos_boys_route_base_08", "borvos_boys_route_base_09", "borvos_boys_route_base_10", "borvos_boys_route_base_11", "borvos_boys_route_base_12", "borvos_boys_route_base_13", "borvos_boys_route_base_14", "borvos_boys_route_base_15", "borvos_boys_route_base_16", "borvos_boys_route_base_17", "borvos_boys_route_base_18", "borvos_boys_route_base_19", "borvos_boys_route_base_20", "borvos_boys_route_base_21", "borvos_boys_route_base_22", "borvos_boys_route_base_23", "borvos_boys_route_base_24", "borvos_boys_route_base_25", "borvos_boys_route_base_26", "borvos_boys_route_base_27", "borvos_boys_route_base_28", "borvos_boys_route_base_29", "borvos_boys_route_base_30", "borvos_boys_route_base_31", "borvos_boys_route_base_32", "borvos_boys_route_base_33", "borvos_boys_route_base_34", "borvos_boys_route_base_35", "borvos_boys_route_base_36", "borvos_boys_route_base_37", "borvos_boys_route_base_38", "borvos_boys_route_base_39", "borvos_boys_route_base_40", "borvos_boys_route_base_41", "borvos_boys_route_base_42", "borvos_boys_route_base_43", "borvos_boys_route_base_44", "borvos_boys_route_base_45", "borvos_boys_route_base_46", "borvos_boys_route_base_47", "borvos_boys_route_base_48", "borvos_boys_route_base_49", "borvos_boys_route_base_50", "borvos_boys_route_base_51", "borvos_boys_route_base_52", "borvos_boys_route_base_53"},
			shipSpawns = {"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_fighter_tier1_naboo"}
		},
		{spawnName = "borvo_vs_rsf_2", spawnType = SHIP_SPAWN_SINGLE, x = -4653, z = -4807, y = 2728, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"borvo_bomber_tier1", "borvo_fighter_tier1"}
		},
		{spawnName = "rsf_vs_borvo_2", spawnType = SHIP_SPAWN_SINGLE, x = -4449, z = -4780, y = 2470, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"rsf_rawl_tier1_naboo", "rsf_stinger_tier1"}
		},
		{spawnName = "borvo_static_patrol_six", spawnType = SHIP_SPAWN_SINGLE, x = -4704, z = -3760, y = 460, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1_naboo", "borvo_fighter_tier1", "borvo_fighter_tier1_naboo"}
		},
		{spawnName = "borvo_vs_rsf_1", spawnType = SHIP_SPAWN_SINGLE, x = -4668, z = -2815, y = 551, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"borvo_bomber_tier1", "borvo_fighter_tier1_naboo"}
		},
		{spawnName = "rsf_vs_borvo_1", spawnType = SHIP_SPAWN_SINGLE, x = -4706, z = -2816, y = 448, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"rsf_ace_tier1", "rsf_stinger_tier1"}
		},
		{spawnName = "imperial_poi_asteroid", spawnType = SHIP_SPAWN_SINGLE, x = 3909, z = 3396, y = 7512, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_poi_asteroid_00", "imperial_poi_asteroid_01", "imperial_poi_asteroid_02", "imperial_poi_asteroid_03", "imperial_poi_asteroid_04"},
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{spawnName = "tradefed_guardians_2", spawnType = SHIP_SPAWN_SINGLE, x = 3218, z = -5734, y = -5191, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"trade_fed_guardian"}
		},
		{spawnName = "naboo_miner_stationary_patrol", spawnType = SHIP_SPAWN_SINGLE, x = 6006, z = 6494, y = 6770, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 50, maxPatrol = 100, totalSpawns = 4,
			shipSpawns = {"naboo_miner_fighter"}
		},
		{spawnName = "rsf_patrol_3", spawnType = SHIP_SPAWN_SINGLE, x = -1504, z = 4713, y = -5453, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 15, maxSpawnDistance = 45, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"rsf_ace_tier1", "rsf_hunter_tier1", "rsf_hunter_tier1_naboo", "rsf_scanner_tier1", "rsf_stinger_tier1_naboo"}
		},
		{spawnName = "rse_patrol", spawnType = SHIP_SPAWN_SINGLE, x = -388, z = 5529, y = -6249, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 120, maxRespawn = 240, minSpawnDistance = 20, maxSpawnDistance = 35, totalSpawns = 7,
			patrolsToAssign = 5, fixedPatrolPoints = {"rse_patrol_00", "rse_patrol_01", "rse_patrol_02", "rse_patrol_03", "rse_patrol_04", "rse_patrol_05", "rse_patrol_06", "rse_patrol_07", "rse_patrol_08", "rse_patrol_09", "rse_patrol_10", "rse_patrol_11", "rse_patrol_12", "rse_patrol_13", "rse_patrol_14", "rse_patrol_15", "rse_patrol_16", "rse_patrol_17", "rse_patrol_18", "rse_patrol_19", "rse_patrol_20", "rse_patrol_21", "rse_patrol_22", "rse_patrol_23", "rse_patrol_24", "rse_patrol_25"},
			shipSpawns = {"rsf_ace_tier1", "rsf_hunter_tier1", "rsf_hunter_tier1_naboo", "rsf_hunter_tier1_naboo", "rsf_rawl_tier1", "rsf_rawl_tier1_naboo"}
		},
		{spawnName = "rsf_boss", spawnType = SHIP_SPAWN_SINGLE, x = -343, z = 5522, y = -6205, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 7200, maxRespawn = 10800, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rsf_boss_00", "rsf_boss_01", "rsf_boss_02", "rsf_boss_03", "rsf_boss_04", "rsf_boss_05", "rsf_boss_06", "rsf_boss_07", "rsf_boss_08", "rsf_boss_09", "rsf_boss_10", "rsf_boss_11", "rsf_boss_12", "rsf_boss_13", "rsf_boss_14", "rsf_boss_15", "rsf_boss_16", "rsf_boss_17", "rsf_boss_18", "rsf_boss_19", "rsf_boss_20", "rsf_boss_21", "rsf_boss_22", "rsf_boss_23", "rsf_boss_24", "rsf_boss_25", "rsf_boss_26", "rsf_boss_27", "rsf_boss_28", "rsf_boss_29", "rsf_boss_30", "rsf_boss_31", "rsf_boss_32", "rsf_boss_33", "rsf_boss_34", "rsf_boss_35", "rsf_boss_36", "rsf_boss_37", "rsf_boss_38", "rsf_boss_39", "rsf_boss_40", "rsf_boss_41", "rsf_boss_42", "rsf_boss_43", "rsf_boss_44", "rsf_boss_45", "rsf_boss_46", "rsf_boss_47", "rsf_boss_48", "rsf_boss_49", "rsf_boss_50", "rsf_boss_51", "rsf_boss_52", "rsf_boss_53", "rsf_boss_54", "rsf_boss_55", "rsf_boss_56", "rsf_boss_57", "rsf_boss_58", "rsf_boss_59", "rsf_boss_60", "rsf_boss_61", "rsf_boss_62", "rsf_boss_63"},
			shipSpawns = {"rsf_boss"}
		},
		{spawnName = "naboo_miner_fighters", spawnType = SHIP_SPAWN_SINGLE, x = 4895, z = 6528, y = 6078, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"naboo_miner_fighters_00", "naboo_miner_fighters_01", "naboo_miner_fighters_02", "naboo_miner_fighters_03", "naboo_miner_fighters_04", "naboo_miner_fighters_05", "naboo_miner_fighters_06", "naboo_miner_fighters_07", "naboo_miner_fighters_08", "naboo_miner_fighters_09", "naboo_miner_fighters_10", "naboo_miner_fighters_11", "naboo_miner_fighters_12", "naboo_miner_fighters_13", "naboo_miner_fighters_14", "naboo_miner_fighters_15", "naboo_miner_fighters_16", "naboo_miner_fighters_17", "naboo_miner_fighters_18", "naboo_miner_fighters_19", "naboo_miner_fighters_20", "naboo_miner_fighters_21", "naboo_miner_fighters_22", "naboo_miner_fighters_23", "naboo_miner_fighters_24", "naboo_miner_fighters_25", "naboo_miner_fighters_26", "naboo_miner_fighters_27", "naboo_miner_fighters_28", "naboo_miner_fighters_29", "naboo_miner_fighters_30", "naboo_miner_fighters_31", "naboo_miner_fighters_32", "naboo_miner_fighters_33", "naboo_miner_fighters_34", "naboo_miner_fighters_35", "naboo_miner_fighters_36", "naboo_miner_fighters_37", "naboo_miner_fighters_38", "naboo_miner_fighters_39", "naboo_miner_fighters_40", "naboo_miner_fighters_41", "naboo_miner_fighters_42", "naboo_miner_fighters_43", "naboo_miner_fighters_44", "naboo_miner_fighters_45", "naboo_miner_fighters_46", "naboo_miner_fighters_47", "naboo_miner_fighters_48", "naboo_miner_fighters_49", "naboo_miner_fighters_50", "naboo_miner_fighters_51", "naboo_miner_fighters_52", "naboo_miner_fighters_53", "naboo_miner_fighters_54", "naboo_miner_fighters_55"},
			shipSpawns = {"naboo_miner_defender", "naboo_miner_fighter", "naboo_miner_hunter"}
		},
		{spawnName = "naboo_miners_planetoid", spawnType = SHIP_SPAWN_SINGLE, x = 2736, z = 6039, y = 5438, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"naboo_miners_planetoid_00", "naboo_miners_planetoid_01", "naboo_miners_planetoid_02", "naboo_miners_planetoid_03", "naboo_miners_planetoid_04", "naboo_miners_planetoid_05", "naboo_miners_planetoid_06", "naboo_miners_planetoid_07", "naboo_miners_planetoid_08", "naboo_miners_planetoid_09", "naboo_miners_planetoid_10", "naboo_miners_planetoid_11", "naboo_miners_planetoid_12", "naboo_miners_planetoid_13", "naboo_miners_planetoid_14"},
			shipSpawns = {"naboo_miner_transport"}
		},
		{spawnName = "ot_violator_squad", spawnType = SHIP_SPAWN_SQUADRON, x = -2535, z = 5374, y = 3629, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 259200, maxRespawn = 295200, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"ot_violator_squad_00", "ot_violator_squad_01", "ot_violator_squad_02", "ot_violator_squad_03", "ot_violator_squad_04", "ot_violator_squad_05", "ot_violator_squad_06", "ot_violator_squad_07", "ot_violator_squad_08", "ot_violator_squad_09", "ot_violator_squad_10", "ot_violator_squad_11", "ot_violator_squad_12", "ot_violator_squad_13", "ot_violator_squad_14", "ot_violator_squad_15", "ot_violator_squad_16", "ot_violator_squad_17", "ot_violator_squad_18", "ot_violator_squad_19", "ot_violator_squad_20", "ot_violator_squad_21", "ot_violator_squad_22"},
			shipSpawns = {"squad_naboo_boss"}
		},
		{spawnName = "naboo_privateer_13", spawnType = SHIP_SPAWN_SINGLE, x = 3168, z = -1441, y = -1209, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 24, maxSpawnDistance = 64, minPatrol = 116, maxPatrol = 320, totalSpawns = 3,
			shipSpawns = {"aynat_enforcer_tier1", "aynat_ghost_tier1", "aynat_intimidator_tier1", "aynat_outlaw_tier1", "aynat_vaporizer_tier1"}
		},
		{spawnName = "rsf_station_guards_2", spawnType = SHIP_SPAWN_SINGLE, x = -1058, z = 36, y = -6779, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"rsf_rawl_tier1", "rsf_stinger_tier1"}
		},
		{spawnName = "rsf_station_guards_3", spawnType = SHIP_SPAWN_SINGLE, x = 595, z = -91, y = -4744, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"rsf_rawl_tier1", "rsf_rawl_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier1_naboo"}
		},
		{spawnName = "imperial_generic_1", spawnType = SHIP_SPAWN_SINGLE, x = 1036, z = -506, y = -1295, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 64, minPatrol = 55, maxPatrol = 380, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{spawnName = "black_sun_route_1", spawnType = SHIP_SPAWN_SINGLE, x = -21, z = -289, y = -960, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 32, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"black_sun_route_1_00", "black_sun_route_1_01", "black_sun_route_1_02", "black_sun_route_1_03"},
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_bomber_ace_s04_tier1", "blacksun_fighter_s01_tier1", "blacksun_fighter_s02_tier1", "blacksun_fighter_s02_tier1", "blacksun_fighter_s02_tier1", "blacksun_fighter_s02_tier1"}
		},
		{spawnName = "rebel_attack_1", spawnType = SHIP_SPAWN_SINGLE, x = -476, z = 1137, y = -971, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 10, maxRespawn = 20, minSpawnDistance = 8, maxSpawnDistance = 64, minPatrol = 80, maxPatrol = 180, totalSpawns = 3,
			shipSpawns = {"imp_freightermedium_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1"}
		},
		{spawnName = "hutt_generic_1", spawnType = SHIP_SPAWN_SINGLE, x = -16, z = 942, y = -1260, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 32, minPatrol = 100, maxPatrol = 400, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s02_tier1"}
		},
		{spawnName = "rsf_to_station_2", spawnType = SHIP_SPAWN_SINGLE, x = -3125, z = 551, y = -4589, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 7,
			patrolsToAssign = 5, fixedPatrolPoints = {"rsf_to_station_2_00", "rsf_to_station_2_01", "rsf_to_station_2_02"},
			shipSpawns = {"rsf_rawl_tier1", "rsf_rawl_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier1_naboo"}
		},
		{spawnName = "rsf_vs_droids_4", spawnType = SHIP_SPAWN_SINGLE, x = -6139, z = -1178, y = -3891, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"rsf_rawl_tier1_naboo", "rsf_stinger_tier1"}
		},
		{spawnName = "droid_vs_rsf_4", spawnType = SHIP_SPAWN_SINGLE, x = -6117, z = -772, y = -3763, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 10, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 10,
			shipSpawns = {"rogue_droid_defender_tier1", "rogue_droid_fighter_tier1", "rogue_droid_alpha_tier1", "rogue_droid_alpha_tier1_naboo", "rogue_droid_defender", "rogue_droid_defender_tier1", "rogue_droid_defender_tier1_naboo", "rogue_droid_fighter", "rogue_droid_fighter_tier1", "rogue_droid_scrapper", "rogue_droid_scrapper_tier1", "rogue_droid_scrapper_tier1_naboo"}
		},
		{spawnName = "rebel_cadet_1", spawnType = SHIP_SPAWN_SINGLE, x = -6416, z = -2568, y = -4512, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 64, minPatrol = 50, maxPatrol = 380, totalSpawns = 3,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1"}
		},
		{spawnName = "comm_ship_twinstar_shipping_01", spawnType = SHIP_SPAWN_SINGLE, x = -5000, z = -3200, y = -5000, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 4, maxRespawn = 120, minSpawnDistance = 32, maxSpawnDistance = 128, minPatrol = 100, maxPatrol = 400, totalSpawns = 3,
			shipSpawns = {"blacksun_fighter_s02_tier1", "blacksun_marauder_tier1"}
		},
		{spawnName = "stn_dantooine_shiftyprince_inspect_01", spawnType = SHIP_SPAWN_SINGLE, x = -6032, z = -2176, y = -5816, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 15, maxRespawn = 45, minSpawnDistance = 32, maxSpawnDistance = 128, minPatrol = 100, maxPatrol = 400, totalSpawns = 1,
			shipSpawns = {"shifty_prince_tier3"}
		},
		{spawnName = "naboo_imperial_2", spawnType = SHIP_SPAWN_SINGLE, x = -1915, z = -2006, y = -1455, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 14, minSpawnDistance = 8, maxSpawnDistance = 120, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{spawnName = "imperial_fluff_spawns_3", spawnType = SHIP_SPAWN_SINGLE, x = -2024, z = -3820, y = -3131, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{spawnName = "rebel_defense_3", spawnType = SHIP_SPAWN_SINGLE, x = -5233, z = 6658, y = 6405, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"reb_xwing_cadet_tier1"}
		},
		{spawnName = "rebel_defense_4", spawnType = SHIP_SPAWN_SINGLE, x = -4892, z = 6147, y = 6901, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 50, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"reb_xwing_tier1", "reb_xwing_tier1", "reb_ywing_tier2", "reb_ywing_tier2", "rebel_raider_captain"}
		},
		{spawnName = "imperial_fluff_spawns_4", spawnType = SHIP_SPAWN_SINGLE, x = -5221, z = 5646, y = 5880, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{spawnName = "rebel_boss", spawnType = SHIP_SPAWN_SINGLE, x = -5569, z = 5792, y = 6386, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 7200, maxRespawn = 10800, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_boss_00", "rebel_boss_01", "rebel_boss_02", "rebel_boss_03", "rebel_boss_04", "rebel_boss_05", "rebel_boss_06", "rebel_boss_07", "rebel_boss_08", "rebel_boss_09", "rebel_boss_10", "rebel_boss_11", "rebel_boss_12", "rebel_boss_13", "rebel_boss_14", "rebel_boss_15", "rebel_boss_16", "rebel_boss_17", "rebel_boss_18", "rebel_boss_19", "rebel_boss_20"},
			shipSpawns = {"rebel_boss"}
		},
		{spawnName = "rebel_defense_2", spawnType = SHIP_SPAWN_SINGLE, x = -5998, z = 5792, y = 6563, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 50, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_tier1", "reb_ywing_tier1", "reb_z95_tier1"}
		},
		{spawnName = "imperial_naboo_squad_3", spawnType = SHIP_SPAWN_SQUADRON, x = -6004, z = 5601, y = 5836, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_naboo_squad_3_00", "imperial_naboo_squad_3_01", "imperial_naboo_squad_3_02", "imperial_naboo_squad_3_03", "imperial_naboo_squad_3_04", "imperial_naboo_squad_3_05"},
			shipSpawns = {"squad_imperial_naboo_3"}
		},
		{spawnName = "rebel_base_defense_1", spawnType = SHIP_SPAWN_SINGLE, x = -5667, z = 6271, y = 6288, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_base_defense_1_00", "rebel_base_defense_1_01", "rebel_base_defense_1_02", "rebel_base_defense_1_03", "rebel_base_defense_1_04", "rebel_base_defense_1_05", "rebel_base_defense_1_06", "rebel_base_defense_1_07", "rebel_base_defense_1_08", "rebel_base_defense_1_09", "rebel_base_defense_1_10", "rebel_base_defense_1_11", "rebel_base_defense_1_12", "rebel_base_defense_1_13", "rebel_base_defense_1_14", "rebel_base_defense_1_15", "rebel_base_defense_1_16", "rebel_base_defense_1_17", "rebel_base_defense_1_18", "rebel_base_defense_1_19", "rebel_base_defense_1_20"},
			shipSpawns = {"reb_z95_tier1", "reb_xwing_tier1"}
		},
		{spawnName = "rsf_station_guards_6", spawnType = SHIP_SPAWN_SINGLE, x = 4741, z = -6195, y = 2118, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"rsf_rawl_tier1", "rsf_rawl_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier2_naboo"}
		},
		{spawnName = "droid_vs_rsf_2", spawnType = SHIP_SPAWN_SINGLE, x = -5456, z = 2169, y = -1279, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 10, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 10,
			shipSpawns = {"rogue_droid_defender_tier1", "rogue_droid_fighter_tier1_naboo", "rogue_droid_alpha_tier1", "rogue_droid_alpha_tier1_naboo", "rogue_droid_defender", "rogue_droid_defender_tier1", "rogue_droid_defender_tier1_naboo", "rogue_droid_fighter", "rogue_droid_fighter_tier1", "rogue_droid_scrapper", "rogue_droid_scrapper_tier1", "rogue_droid_scrapper_tier1_naboo"}
		},
		{spawnName = "rsf_vs_droids_2", spawnType = SHIP_SPAWN_SINGLE, x = -5187, z = 2236, y = -1313, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"rsf_rawl_tier1_naboo", "rsf_stinger_tier1"}
		},
		{spawnName = "rsf_patrol_2", spawnType = SHIP_SPAWN_SINGLE, x = -6302, z = 2023, y = -2391, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 35, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"rsf_rawl_tier1", "rsf_rawl_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier1_naboo"}
		},
		{spawnName = "rogue_droid_scrapper_patrol", spawnType = SHIP_SPAWN_SINGLE, x = -7060, z = 1785, y = -1125, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 15, maxSpawnDistance = 30, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"rogue_droid_scrapper_patrol_00", "rogue_droid_scrapper_patrol_01", "rogue_droid_scrapper_patrol_02", "rogue_droid_scrapper_patrol_03", "rogue_droid_scrapper_patrol_04", "rogue_droid_scrapper_patrol_05", "rogue_droid_scrapper_patrol_06", "rogue_droid_scrapper_patrol_07", "rogue_droid_scrapper_patrol_08", "rogue_droid_scrapper_patrol_09", "rogue_droid_scrapper_patrol_10", "rogue_droid_scrapper_patrol_11", "rogue_droid_scrapper_patrol_12", "rogue_droid_scrapper_patrol_13", "rogue_droid_scrapper_patrol_14", "rogue_droid_scrapper_patrol_15", "rogue_droid_scrapper_patrol_16", "rogue_droid_scrapper_patrol_17", "rogue_droid_scrapper_patrol_18", "rogue_droid_scrapper_patrol_19", "rogue_droid_scrapper_patrol_20", "rogue_droid_scrapper_patrol_21", "rogue_droid_scrapper_patrol_22", "rogue_droid_scrapper_patrol_23"},
			shipSpawns = {"rogue_droid_defender_tier1", "rogue_droid_defender_tier1_naboo", "rogue_droid_fighter_tier1", "rogue_droid_fighter_tier1_naboo"}
		},
		{spawnName = "black_sun_generic_1", spawnType = SHIP_SPAWN_SINGLE, x = -2302, z = 1093, y = -1291, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 64, minPatrol = 300, maxPatrol = 600, totalSpawns = 3,
			shipSpawns = {"blacksun_ace_s04_tier2", "blacksun_aggressor_tier2", "blacksun_bomber_ace_s04_tier2", "blacksun_fighter_s01_tier2", "blacksun_marauder_tier2", "blacksun_vehement_tier2"}
		},
		{spawnName = "imperial_fluff_spawns_5", spawnType = SHIP_SPAWN_SINGLE, x = -5968, z = -1847, y = 386, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{spawnName = "rsf_vs_droids_1", spawnType = SHIP_SPAWN_SINGLE, x = -4700, z = -1052, y = -419, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"rsf_rawl_tier1", "rsf_stinger_tier1"}
		},
		{spawnName = "droid_vs_rsf_1", spawnType = SHIP_SPAWN_SINGLE, x = -4765, z = -502, y = -531, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 10, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 10,
			shipSpawns = {"rogue_droid_alpha_tier1", "rogue_droid_alpha_tier1_naboo", "rogue_droid_fighter", "rogue_droid_fighter_tier1", "rogue_droid_fighter_tier1_naboo", "rogue_droid_defender", "rogue_droid_defender_tier1", "rogue_droid_defender_tier1_naboo", "rogue_droid_scrapper", "rogue_droid_scrapper_tier1_naboo"}
		},
		{spawnName = "naboo_imperial_4", spawnType = SHIP_SPAWN_SINGLE, x = -3738, z = 2869, y = -2174, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 32, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{spawnName = "imperial_poi_2", spawnType = SHIP_SPAWN_SINGLE, x = -2986, z = 2039, y = -22, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 350, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_interceptor_tier1"}
		},
		{spawnName = "imperial_poi_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -3007, z = 1805, y = -3, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 430, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_poi_spawner_00", "imperial_poi_spawner_01", "imperial_poi_spawner_02", "imperial_poi_spawner_03", "imperial_poi_spawner_04", "imperial_poi_spawner_05", "imperial_poi_spawner_06", "imperial_poi_spawner_07"},
			shipSpawns = {"squad_imperial_naboo_2"}
		},
		{spawnName = "rsf_patrol_5", spawnType = SHIP_SPAWN_SINGLE, x = -4572, z = 1876, y = 2862, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 50, minPatrol = 70, maxPatrol = 310, totalSpawns = 3,
			shipSpawns = {"rsf_ace_tier1", "rsf_hunter_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier1_naboo"}
		},
		{spawnName = "naboo_privateer_2", spawnType = SHIP_SPAWN_SINGLE, x = 2958, z = 941, y = -1002, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 4, maxRespawn = 120, minSpawnDistance = 32, maxSpawnDistance = 128, minPatrol = 100, maxPatrol = 400, totalSpawns = 3,
			shipSpawns = {"blacksun_fighter_s02_tier1", "blacksun_marauder_tier1"}
		},
		{spawnName = "imperial_boss", spawnType = SHIP_SPAWN_SINGLE, x = 2682, z = 1603, y = 869, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 7200, maxRespawn = 10800, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_boss_00", "imperial_boss_01", "imperial_boss_02", "imperial_boss_03", "imperial_boss_04", "imperial_boss_05", "imperial_boss_06", "imperial_boss_07", "imperial_boss_08", "imperial_boss_09", "imperial_boss_10", "imperial_boss_11", "imperial_boss_12", "imperial_boss_13", "imperial_boss_14", "imperial_boss_15", "imperial_boss_16", "imperial_boss_17", "imperial_boss_18", "imperial_boss_19", "imperial_boss_20", "imperial_boss_21", "imperial_boss_22", "imperial_boss_23", "imperial_boss_24", "imperial_boss_25", "imperial_boss_26", "imperial_boss_27", "imperial_boss_28", "imperial_boss_29", "imperial_boss_30", "imperial_boss_31", "imperial_boss_32", "imperial_boss_33", "imperial_boss_34", "imperial_boss_35", "imperial_boss_36", "imperial_boss_37", "imperial_boss_38", "imperial_boss_39", "imperial_boss_40", "imperial_boss_41", "imperial_boss_42", "imperial_boss_43", "imperial_boss_44", "imperial_boss_45", "imperial_boss_46", "imperial_boss_47", "imperial_boss_48", "imperial_boss_49", "imperial_boss_50", "imperial_boss_51", "imperial_boss_52", "imperial_boss_53", "imperial_boss_54", "imperial_boss_55", "imperial_boss_56", "imperial_boss_57", "imperial_boss_58", "imperial_boss_59", "imperial_boss_60", "imperial_boss_61"},
			shipSpawns = {"imperial_boss"}
		},
		{spawnName = "imperial_base_patrol_2", spawnType = SHIP_SPAWN_SINGLE, x = 2840, z = 1573, y = 930, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_base_patrol_2_00", "imperial_base_patrol_2_01", "imperial_base_patrol_2_02", "imperial_base_patrol_2_03", "imperial_base_patrol_2_04", "imperial_base_patrol_2_05", "imperial_base_patrol_2_06", "imperial_base_patrol_2_07", "imperial_base_patrol_2_08", "imperial_base_patrol_2_09", "imperial_base_patrol_2_10", "imperial_base_patrol_2_11", "imperial_base_patrol_2_12", "imperial_base_patrol_2_13", "imperial_base_patrol_2_14", "imperial_base_patrol_2_15", "imperial_base_patrol_2_16", "imperial_base_patrol_2_17", "imperial_base_patrol_2_18", "imperial_base_patrol_2_19", "imperial_base_patrol_2_20", "imperial_base_patrol_2_21"},
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_interceptor_tier1"}
		},
		{spawnName = "imperial_base_patrol", spawnType = SHIP_SPAWN_SINGLE, x = 2954, z = 1642, y = 916, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_base_patrol_00", "imperial_base_patrol_01", "imperial_base_patrol_02", "imperial_base_patrol_03", "imperial_base_patrol_04", "imperial_base_patrol_05", "imperial_base_patrol_06", "imperial_base_patrol_07", "imperial_base_patrol_08", "imperial_base_patrol_09", "imperial_base_patrol_10", "imperial_base_patrol_11", "imperial_base_patrol_12", "imperial_base_patrol_13", "imperial_base_patrol_14", "imperial_base_patrol_15", "imperial_base_patrol_16", "imperial_base_patrol_17", "imperial_base_patrol_18", "imperial_base_patrol_19", "imperial_base_patrol_20", "imperial_base_patrol_21", "imperial_base_patrol_22"},
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{spawnName = "imperial_gunboat_woot_1", spawnType = SHIP_SPAWN_SINGLE, x = 3166, z = 1238, y = 1103, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 3600, maxRespawn = 4200, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_gunboat_woot_1_00", "imperial_gunboat_woot_1_01", "imperial_gunboat_woot_1_02", "imperial_gunboat_woot_1_03", "imperial_gunboat_woot_1_04", "imperial_gunboat_woot_1_05", "imperial_gunboat_woot_1_06", "imperial_gunboat_woot_1_07", "imperial_gunboat_woot_1_08", "imperial_gunboat_woot_1_09", "imperial_gunboat_woot_1_10", "imperial_gunboat_woot_1_11", "imperial_gunboat_woot_1_12", "imperial_gunboat_woot_1_13", "imperial_gunboat_woot_1_14", "imperial_gunboat_woot_1_15", "imperial_gunboat_woot_1_16", "imperial_gunboat_woot_1_17", "imperial_gunboat_woot_1_18", "imperial_gunboat_woot_1_19", "imperial_gunboat_woot_1_20"},
			shipSpawns = {"imp_imperial_gunboat_tier1"}
		},
		{spawnName = "rebel_cadet_3", spawnType = SHIP_SPAWN_SINGLE, x = 5492, z = 64, y = 2804, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 64, minPatrol = 50, maxPatrol = 380, totalSpawns = 3,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1"}
		},
		{spawnName = "rsf_patrol_4", spawnType = SHIP_SPAWN_SINGLE, x = 1297, z = 4803, y = -4375, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 30, maxSpawnDistance = 50, minPatrol = 70, maxPatrol = 310, totalSpawns = 3,
			shipSpawns = {"rsf_ace_tier1", "rsf_hunter_tier1"}
		},
		{spawnName = "naboo_rori_transport_route", spawnType = SHIP_SPAWN_SINGLE, x = 3211, z = 2687, y = -2756, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 50, maxSpawnDistance = 70, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"naboo_rori_transport_route_00", "naboo_rori_transport_route_01", "naboo_rori_transport_route_02", "naboo_rori_transport_route_03", "naboo_rori_transport_route_04", "naboo_rori_transport_route_05", "naboo_rori_transport_route_06", "naboo_rori_transport_route_07", "naboo_rori_transport_route_08", "naboo_rori_transport_route_09", "naboo_rori_transport_route_10", "naboo_rori_transport_route_11", "naboo_rori_transport_route_12", "naboo_rori_transport_route_13", "naboo_rori_transport_route_14", "naboo_rori_transport_route_15", "naboo_rori_transport_route_16"},
			shipSpawns = {"freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_tier1", "freightermedium_tier1", "rsf_ace_tier1", "rsf_ace_tier1", "rsf_ace_tier1", "rsf_ace_tier1", "rsf_ace_tier1", "rsf_defender", "rsf_fighter"}
		},
		{spawnName = "rsf_forces_station", spawnType = SHIP_SPAWN_SINGLE, x = 2837, z = 2687, y = -2682, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 50, maxSpawnDistance = 70, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"rsf_ace_tier1", "rsf_hunter_tier1"}
		},
		{spawnName = "black_sun_attack_1", spawnType = SHIP_SPAWN_SINGLE, x = 1091, z = 733, y = -2295, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 64, minPatrol = 200, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"blacksun_bomber_ace_s04_tier2", "blacksun_ace_s04_tier2", "blacksun_aggressor_tier2", "blacksun_fighter_s01_tier2", "blacksun_vehement_tier2", "blacksun_marauder_tier2"}
		},
		{spawnName = "imperial_naboo_squad_1", spawnType = SHIP_SPAWN_SQUADRON, x = 2358, z = 3786, y = -3554, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_naboo_squad_1_00", "imperial_naboo_squad_1_01", "imperial_naboo_squad_1_02", "imperial_naboo_squad_1_03", "imperial_naboo_squad_1_04", "imperial_naboo_squad_1_05"},
			shipSpawns = {"squad_imperial_naboo_1"}
		},
		{spawnName = "tradefed_guardians_1", spawnType = SHIP_SPAWN_SINGLE, x = 1326, z = -5493, y = -5868, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"trade_fed_guardian"}
		},
		{spawnName = "tradefed_wide_patrol", spawnType = SHIP_SPAWN_SINGLE, x = 2500, z = -5542, y = -5469, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"tradefed_wide_patrol_00", "tradefed_wide_patrol_01", "tradefed_wide_patrol_02", "tradefed_wide_patrol_03", "tradefed_wide_patrol_04", "tradefed_wide_patrol_05", "tradefed_wide_patrol_06", "tradefed_wide_patrol_07", "tradefed_wide_patrol_08"},
			shipSpawns = {"trade_fed_fighter", "trade_fed_heavy_fighter", "trade_fed_bomber"}
		},
		{spawnName = "tradefed_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = 2043, z = -5830, y = -6988, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"tradefed_patrol_1_00", "tradefed_patrol_1_01", "tradefed_patrol_1_02", "tradefed_patrol_1_03", "tradefed_patrol_1_04", "tradefed_patrol_1_05"},
			shipSpawns = {"trade_fed_fighter", "trade_fed_bomber"}
		},
		{spawnName = "federation_poi_patrol", spawnType = SHIP_SPAWN_SINGLE, x = 2171, z = -5573, y = -4644, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"federation_poi_patrol_00", "federation_poi_patrol_01", "federation_poi_patrol_02", "federation_poi_patrol_03", "federation_poi_patrol_04", "federation_poi_patrol_05", "federation_poi_patrol_06", "federation_poi_patrol_07", "federation_poi_patrol_08", "federation_poi_patrol_09", "federation_poi_patrol_10", "federation_poi_patrol_11"},
			shipSpawns = {"trade_fed_fighter", "trade_fed_bomber"}
		},
		{spawnName = "rsf_patrol_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -5397, z = 2779, y = -3508, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 45, minPatrol = 60, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"rsf_ace_tier1", "rsf_hunter_tier1"}
		},
		{spawnName = "rsf_patrol_2", spawnType = SHIP_SPAWN_SINGLE, x = -3525, z = 3169, y = -5274, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"rsf_ace_tier1", "rsf_hunter_tier1"}
		},
		{spawnName = "rsf_station_guards_1", spawnType = SHIP_SPAWN_SINGLE, x = -3059, z = 1760, y = -7465, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"rsf_rawl_tier1", "rsf_rawl_tier1_naboo", "rsf_stinger_tier1", "rsf_stinger_tier1_naboo"}
		},
		{spawnName = "naboo_privateer_4", spawnType = SHIP_SPAWN_SINGLE, x = 2147, z = -1509, y = 3415, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 32, maxSpawnDistance = 64, minPatrol = 50, maxPatrol = 290, totalSpawns = 3,
			shipSpawns = {"blacksun_marauder_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "borvo_static_patrol", spawnType = SHIP_SPAWN_SINGLE, x = -3324, z = -4588, y = 2821, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"borvo_defender_tier1", "borvo_defender_tier1_naboo", "borvo_fighter_tier1", "borvo_fighter_tier1_naboo"}
		},
		{spawnName = "borvo_civ_route_assault", spawnType = SHIP_SPAWN_SINGLE, x = -2997, z = -3003, y = 2790, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"borvo_civ_route_assault_00", "borvo_civ_route_assault_01", "borvo_civ_route_assault_02", "borvo_civ_route_assault_03", "borvo_civ_route_assault_04", "borvo_civ_route_assault_05", "borvo_civ_route_assault_06", "borvo_civ_route_assault_07", "borvo_civ_route_assault_08", "borvo_civ_route_assault_09", "borvo_civ_route_assault_10", "borvo_civ_route_assault_11", "borvo_civ_route_assault_12", "borvo_civ_route_assault_13", "borvo_civ_route_assault_14", "borvo_civ_route_assault_15", "borvo_civ_route_assault_16", "borvo_civ_route_assault_17", "borvo_civ_route_assault_18", "borvo_civ_route_assault_19", "borvo_civ_route_assault_20", "borvo_civ_route_assault_21", "borvo_civ_route_assault_22", "borvo_civ_route_assault_23", "borvo_civ_route_assault_24", "borvo_civ_route_assault_25", "borvo_civ_route_assault_26", "borvo_civ_route_assault_27", "borvo_civ_route_assault_28", "borvo_civ_route_assault_29", "borvo_civ_route_assault_30", "borvo_civ_route_assault_31", "borvo_civ_route_assault_32", "borvo_civ_route_assault_33", "borvo_civ_route_assault_34", "borvo_civ_route_assault_35", "borvo_civ_route_assault_36", "borvo_civ_route_assault_37"},
			shipSpawns = {"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1_naboo", "borvo_fighter_tier1", "borvo_fighter_tier1_naboo"}
		},
		{spawnName = "rebel_cadet_2", spawnType = SHIP_SPAWN_SINGLE, x = 4480, z = -4132, y = -6180, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 64, minPatrol = 50, maxPatrol = 380, totalSpawns = 3,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1"}
		},
		{spawnName = "rsf_station_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = 6928, z = -4258, y = -320, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 7,
			patrolsToAssign = 5, fixedPatrolPoints = {"rsf_station_patrol_1_00", "rsf_station_patrol_1_01", "rsf_station_patrol_1_02", "rsf_station_patrol_1_03", "rsf_station_patrol_1_04", "rsf_station_patrol_1_05"},
			shipSpawns = {"rsf_rawl_tier1", "rsf_stinger_tier1"}
		},
		{spawnName = "freighters_station_1", spawnType = SHIP_SPAWN_SINGLE, x = 7423, z = -4059, y = -443, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"freighters_station_1_00", "freighters_station_1_01", "freighters_station_1_02", "freighters_station_1_03", "freighters_station_1_04"},
			shipSpawns = {"freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterheavy_tier1", "freighterlight_tier1", "freighterlight_tier1"}
		},
		{spawnName = "rsf_station_guards_5", spawnType = SHIP_SPAWN_SINGLE, x = 6137, z = -2967, y = -2084, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"rsf_rawl_tier1", "rsf_stinger_tier1"}
		},
		{spawnName = "naboo_miners_2", spawnType = SHIP_SPAWN_SINGLE, x = 2244, z = 5805, y = 4430, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"naboo_miners_2_00", "naboo_miners_2_01", "naboo_miners_2_02", "naboo_miners_2_03", "naboo_miners_2_04", "naboo_miners_2_05", "naboo_miners_2_06", "naboo_miners_2_07", "naboo_miners_2_08", "naboo_miners_2_09", "naboo_miners_2_10", "naboo_miners_2_11", "naboo_miners_2_12", "naboo_miners_2_13", "naboo_miners_2_14", "naboo_miners_2_15", "naboo_miners_2_16", "naboo_miners_2_17", "naboo_miners_2_18", "naboo_miners_2_19", "naboo_miners_2_20", "naboo_miners_2_21", "naboo_miners_2_22", "naboo_miners_2_23", "naboo_miners_2_24"},
			shipSpawns = {"naboo_miner_transport"}
		},
		{spawnName = "naboo_privateer_tier3_leg_3_inspect", spawnType = SHIP_SPAWN_SINGLE, x = 3151, z = 3183, y = 4026, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 15, minPatrol = 10, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"naboo_diplomatic_corps_bad_tier3"}
		},
		{spawnName = "naboo_privateer_tier_3_leg_2_destroy", spawnType = SHIP_SPAWN_SINGLE, x = 3361, z = 3224, y = 3815, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 10, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"aynat_intimidator_tier1"}
		},
		{spawnName = "miner_boss", spawnType = SHIP_SPAWN_SINGLE, x = 3503, z = 5583, y = 4003, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 7200, maxRespawn = 10800, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"miner_boss_00", "miner_boss_01", "miner_boss_02", "miner_boss_03", "miner_boss_04", "miner_boss_05", "miner_boss_06", "miner_boss_07", "miner_boss_08", "miner_boss_09", "miner_boss_10", "miner_boss_11", "miner_boss_12", "miner_boss_13", "miner_boss_14", "miner_boss_15", "miner_boss_16", "miner_boss_17"},
			shipSpawns = {"naboo_miner_boss"}
		},
		{spawnName = "borvo_static_patrol_five", spawnType = SHIP_SPAWN_SINGLE, x = -5949, z = -4106, y = 3627, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 100, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1_naboo", "borvo_fighter_tier1", "borvo_fighter_tier1_naboo"}
		},
		{spawnName = "naboo_miners_3", spawnType = SHIP_SPAWN_SINGLE, x = 4686, z = 6442, y = 4474, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"naboo_miners_3_00", "naboo_miners_3_01", "naboo_miners_3_02", "naboo_miners_3_03", "naboo_miners_3_04", "naboo_miners_3_05", "naboo_miners_3_06", "naboo_miners_3_07", "naboo_miners_3_08", "naboo_miners_3_09", "naboo_miners_3_10", "naboo_miners_3_11", "naboo_miners_3_12", "naboo_miners_3_13", "naboo_miners_3_14", "naboo_miners_3_15", "naboo_miners_3_16", "naboo_miners_3_17", "naboo_miners_3_18", "naboo_miners_3_19", "naboo_miners_3_20", "naboo_miners_3_21", "naboo_miners_3_22", "naboo_miners_3_23", "naboo_miners_3_24", "naboo_miners_3_25", "naboo_miners_3_26", "naboo_miners_3_27", "naboo_miners_3_28", "naboo_miners_3_29", "naboo_miners_3_30", "naboo_miners_3_31", "naboo_miners_3_32", "naboo_miners_3_33"},
			shipSpawns = {"naboo_miner_transport"}
		},
		{spawnName = "naboo_miner_outer_patrol", spawnType = SHIP_SPAWN_SINGLE, x = 5411, z = 7287, y = 3928, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 401, totalSpawns = 4,
			shipSpawns = {"naboo_miner_fighter"}
		},
		{spawnName = "borvo_static_patrol_two", spawnType = SHIP_SPAWN_SINGLE, x = -923, z = -5511, y = 913, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"borvo_bomber_tier1", "borvo_bomber_tier1_naboo", "borvo_defender_tier1", "borvo_defender_tier1", "borvo_defender_tier1_naboo"}
		},
		{spawnName = "rebel_generic_1", spawnType = SHIP_SPAWN_SINGLE, x = -172, z = -2813, y = -425, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 64, minPatrol = 50, maxPatrol = 380, totalSpawns = 3,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1"}
		},
		{spawnName = "naboo_privateer_12", spawnType = SHIP_SPAWN_SINGLE, x = 3142, z = -3591, y = -492, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 16, maxSpawnDistance = 64, minPatrol = 140, maxPatrol = 612, totalSpawns = 3,
			shipSpawns = {"aynat_enforcer_tier1", "aynat_ghost_tier1", "aynat_intimidator_tier1"}
		},
		{spawnName = "naboo_miner_patrol_two", spawnType = SHIP_SPAWN_SINGLE, x = 1378, z = 4209, y = 6187, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 40, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"naboo_miner_fighter"}
		},
		{spawnName = "imperial_naboo_squad_2", spawnType = SHIP_SPAWN_SQUADRON, x = 1732, z = 5597, y = 5168, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_naboo_squad_2_00", "imperial_naboo_squad_2_01", "imperial_naboo_squad_2_02", "imperial_naboo_squad_2_03", "imperial_naboo_squad_2_04", "imperial_naboo_squad_2_05"},
			shipSpawns = {"squad_imperial_naboo_2"}
		},
		{spawnName = "imperial_fluff_spawns_1", spawnType = SHIP_SPAWN_SINGLE, x = 386, z = 3917, y = 3129, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo"}
		},
		{spawnName = "rsf_civ_route_defenders", spawnType = SHIP_SPAWN_SINGLE, x = -2052, z = -931, y = 3368, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 30, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"rsf_hunter_tier1", "rsf_hunter_tier1_naboo", "rsf_rawl_tier1_naboo"}
		},
		{spawnName = "imperial_fluff_spawns_2", spawnType = SHIP_SPAWN_SINGLE, x = -1837, z = -174, y = -162, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_interceptor_tier1"}
		},
		{spawnName = "naboo_imperial_tier2_inspect1_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -1500, z = 1000, y = 3200, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 25, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"mercenary_courier_tier2"}
		},
		{spawnName = "imperial_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = 263, z = 2203, y = 1703, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 70, maxPatrol = 310, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_naboo", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_naboo", "imp_tie_interceptor_tier1"}
		},
		{spawnName = "hutt_attack_1", spawnType = SHIP_SPAWN_SINGLE, x = 689, z = -286, y = 803, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 64, minPatrol = 80, maxPatrol = 380, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s02_tier1"}
		},
		{spawnName = "tie_veteran_guard", spawnType = SHIP_SPAWN_SINGLE, x = -2126, z = 349, y = 3670, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 10, minPatrol = 100, maxPatrol = 400, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_fighter_tier1", "imp_tie_interceptor_tier1"}
		},
		{spawnName = "naboo_rebel_2", spawnType = SHIP_SPAWN_SINGLE, x = -1297, z = 298, y = -607, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 64, maxSpawnDistance = 128, minPatrol = 100, maxPatrol = 450, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_fighter_tier1"}
		},
		{spawnName = "imperial_squad_naboo_4", spawnType = SHIP_SPAWN_SQUADRON, x = -85, z = 2896, y = 3434, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_squad_naboo_4_00", "imperial_squad_naboo_4_01", "imperial_squad_naboo_4_02", "imperial_squad_naboo_4_03", "imperial_squad_naboo_4_04", "imperial_squad_naboo_4_05"},
			shipSpawns = {"squad_imperial_naboo_4"}
		},
		{spawnName = "civ_route_stations", spawnType = SHIP_SPAWN_SINGLE, x = -3102, z = 1794, y = 3032, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 40, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"civ_route_stations_00", "civ_route_stations_01", "civ_route_stations_02", "civ_route_stations_03", "civ_route_stations_04", "civ_route_stations_05", "civ_route_stations_06", "civ_route_stations_07", "civ_route_stations_08", "civ_route_stations_09", "civ_route_stations_10", "civ_route_stations_11", "civ_route_stations_12", "civ_route_stations_13", "civ_route_stations_14", "civ_route_stations_15", "civ_route_stations_16", "civ_route_stations_17", "civ_route_stations_18", "civ_route_stations_19", "civ_route_stations_20", "civ_route_stations_21", "civ_route_stations_22", "civ_route_stations_23", "civ_route_stations_24", "civ_route_stations_25", "civ_route_stations_26", "civ_route_stations_27", "civ_route_stations_28", "civ_route_stations_29", "civ_route_stations_30", "civ_route_stations_31", "civ_route_stations_32", "civ_route_stations_33", "civ_route_stations_34", "civ_route_stations_35", "civ_route_stations_36", "civ_route_stations_37", "civ_route_stations_38", "civ_route_stations_39", "civ_route_stations_40"},
			shipSpawns = {"civspeeder_naboo", "civspeeder_naboo", "freighterlight_smuggler", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterheavy_tier3_story"}
		},
		{spawnName = "commerce_route_1", spawnType = SHIP_SPAWN_SINGLE, x = -688, z = 776, y = -393, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 8, maxSpawnDistance = 64, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"commerce_route_1_00", "commerce_route_1_01", "commerce_route_1_02", "commerce_route_1_03", "commerce_route_1_04"},
			shipSpawns = {"freightermedium_tier1", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_tier1", "imp_freighterlight_tier1", "freightermedium_tier1", "imp_freightermedium_tier1", "freighterlight_tier1", "freighterlight_tier1", "freightermedium_tier1"}
		},
	},
}

registerScreenPlay("SpaceNabooSpawner", true)
