SpaceEndorSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceEndorSpawner",

	spaceZone = "space_endor",

	shipSpawns = {
		{spawnName = "freighter_mission_dudes_1", spawnType = SHIP_SPAWN_SINGLE, x = 3569, z = -482, y = -2421, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, minPatrol = 90, maxPatrol = 380, totalSpawns = 3,
			shipSpawns = {"mining_guard_ship_tier3", "mining_guard_ship_tier3"}
		},
		{spawnName = "freighter_mission_dudes_1_inspect", spawnType = SHIP_SPAWN_SINGLE, x = 3571, z = -480, y = -2419, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 45, maxRespawn = 90, minSpawnDistance = 40, maxSpawnDistance = 80, minPatrol = 90, maxPatrol = 380, totalSpawns = 1,
			shipSpawns = {"freighterheavy_tier4_inspect"}
		},
		{spawnName = "corellia_imperial_tier3_leg_4_destroy_xwing", spawnType = SHIP_SPAWN_SINGLE, x = 4200, z = -1200, y = -1200, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 25, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"reb_xwing_tier4"}
		},
		{spawnName = "artisan_peacekeeper_1", spawnType = SHIP_SPAWN_SINGLE, x = -6914, z = -6495, y = 214, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"endor_artisan_peacekeeper_tier4", "endor_artisan_peacekeeper_tier4_endor"}
		},
		{spawnName = "artisan_to_trader_1", spawnType = SHIP_SPAWN_SINGLE, x = -6986, z = -6675, y = 271, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"artisan_to_trader_1_00", "artisan_to_trader_1_01", "artisan_to_trader_1_02", "artisan_to_trader_1_03"},
			shipSpawns = {"endor_artisan_diplomat_boss", "endor_artisan_diplomat_tier4", "endor_artisan_diplomat_tier4", "endor_artisan_diplomat_tier4", "endor_artisan_diplomat_tier4_endor", "endor_artisan_diplomat_tier4_endor", "endor_artisan_diplomat_tier4_endor", "endor_artisan_diplomat_tier4_endor", "endor_artisan_diplomat_tier4_endor"}
		},
		{spawnName = "artisan_to_station_1", spawnType = SHIP_SPAWN_SINGLE, x = -7035, z = -6614, y = 495, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"artisan_to_station_1_00", "artisan_to_station_1_01", "artisan_to_station_1_02", "artisan_to_station_1_03", "artisan_to_station_1_04", "artisan_to_station_1_05"},
			shipSpawns = {"endor_artisan_freighter_tier4", "endor_artisan_freighter_tier4_endor", "freighterheavy_tier3_story", "freighterheavy_tier3_story"}
		},
		{spawnName = "imperial_secret_station_guard_3", spawnType = SHIP_SPAWN_SQUADRON, x = 6425, z = -6352, y = 6847, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 300, maxPatrol = 600, totalSpawns = 1,
			shipSpawns = {"squad_tie_aggressor_ace"}
		},
		{spawnName = "imperial_secret_station_guard_2", spawnType = SHIP_SPAWN_SQUADRON, x = 5640, z = -7076, y = 7041, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 300, maxPatrol = 600, totalSpawns = 2,
			shipSpawns = {"squad_tie_mix_ace"}
		},
		{spawnName = "imperial_secret_station_guard_1", spawnType = SHIP_SPAWN_SQUADRON, x = 6109, z = -5905, y = 6350, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 300, maxPatrol = 600, totalSpawns = 2,
			shipSpawns = {"squad_tie_mix_ace"}
		},
		{spawnName = "imperial_death_squad", spawnType = SHIP_SPAWN_SQUADRON, x = 5957, z = -6209, y = 6618, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 3600, maxRespawn = 7200, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_death_squad_00", "imperial_death_squad_01", "imperial_death_squad_02", "imperial_death_squad_03", "imperial_death_squad_04", "imperial_death_squad_05", "imperial_death_squad_06", "imperial_death_squad_07", "imperial_death_squad_08", "imperial_death_squad_09", "imperial_death_squad_10", "imperial_death_squad_11", "imperial_death_squad_12", "imperial_death_squad_13", "imperial_death_squad_14", "imperial_death_squad_15", "imperial_death_squad_16", "imperial_death_squad_17", "imperial_death_squad_18", "imperial_death_squad_19", "imperial_death_squad_20", "imperial_death_squad_21", "imperial_death_squad_22", "imperial_death_squad_23"},
			shipSpawns = {"squad_imperial_fleet"}
		},
		{spawnName = "droid_guards_route_1", spawnType = SHIP_SPAWN_SINGLE, x = -5354, z = 1575, y = -1107, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 3,
			shipSpawns = {"junk_droid_fighter"}
		},
		{spawnName = "droid_engineer_1", spawnType = SHIP_SPAWN_SINGLE, x = -4619, z = 2631, y = -2037, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"droid_engineer_1_00", "droid_engineer_1_01", "droid_engineer_1_02", "droid_engineer_1_03", "droid_engineer_1_04", "droid_engineer_1_05"},
			shipSpawns = {"junk_droid_engineer"}
		},
		{spawnName = "hutt_smuggler_02", spawnType = SHIP_SPAWN_SINGLE, x = 4730, z = -2531, y = -3607, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 200, minPatrol = 200, maxPatrol = 600, totalSpawns = 5,
			shipSpawns = {"hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "hutt_pirate_s02_tier3", "huttsmuggler", "huttsmuggler", "huttsmuggler"}
		},
		{spawnName = "tatooine_imperial_tier3_rebscout_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -2450, z = -3052, y = 1234, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 600, totalSpawns = 1,
			shipSpawns = {"rebel_scout_fighter_tier3"}
		},
		{spawnName = "generator_imperial_defense_a", spawnType = SHIP_SPAWN_SINGLE, x = 6253, z = 7311, y = -6096, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 60, maxPatrol = 320, totalSpawns = 3,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_advanced_tier4", "imp_tie_aggressor_tier4"}
		},
		{spawnName = "hutt_smuggler_01", spawnType = SHIP_SPAWN_SINGLE, x = 4249, z = 2899, y = 3799, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 200, minPatrol = 200, maxPatrol = 700, totalSpawns = 5,
			shipSpawns = {"hutt_bomber_s02_tier3", "hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "huttsmuggler", "huttsmuggler", "huttsmuggler"}
		},
		{spawnName = "rebel_generator_defense_3", spawnType = SHIP_SPAWN_SINGLE, x = 1501, z = 6494, y = 4192, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"reb_bwing_boss", "reb_xwing_tier4", "reb_xwing_tier4", "reb_xwing_tier4", "reb_xwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4", "reb_ywing_tier4", "reb_ywing_tier4", "reb_ywing_tier4", "reb_ywing_tier4"}
		},
		{spawnName = "tatooine_imperial_tier3_destroy2_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 1207, z = 4306, y = 3989, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier4", "reb_bwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4", "rebel_raider_bomber_tier3", "rebel_raider_captain_tier3", "rebel_raider_fast_attack_tier3"}
		},
		{spawnName = "tatooine_imperial_tier3_inspect4escort", spawnType = SHIP_SPAWN_SINGLE, x = 1897, z = 6480, y = 1174, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4", "reb_z95_tier4", "reb_z95_tier4", "reb_z95_tier4"}
		},
		{spawnName = "tatooine_imperial_tier3_inspect4_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 2000, z = 6500, y = 1200, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 400, totalSpawns = 1,
			shipSpawns = {"rebel_command_shuttle_tier4"}
		},
		{spawnName = "naboo_imperial_tier3_inspect3escort", spawnType = SHIP_SPAWN_SINGLE, x = 6102, z = -6988, y = -1069, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 400, totalSpawns = 5,
			shipSpawns = {"reb_xwing_tier3", "reb_z95_tier3", "reb_ywing_tier3"}
		},
		{spawnName = "tatooine_imperial_tier3_inspect3_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 6009, z = -7001, y = -1095, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 400, totalSpawns = 1,
			shipSpawns = {"rebel_scout_shuttle_tier3"}
		},
		{spawnName = "spice_pirates_defend_1", spawnType = SHIP_SPAWN_SINGLE, x = 4620, z = -6158, y = -447, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 4,
			shipSpawns = {"spice_pirate_fighter_tier4"}
		},
		{spawnName = "blacklight_base_defense", spawnType = SHIP_SPAWN_SINGLE, x = 5740, z = -3589, y = 1121, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 30, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"blacklight_base_defense_00", "blacklight_base_defense_01", "blacklight_base_defense_02", "blacklight_base_defense_03", "blacklight_base_defense_04", "blacklight_base_defense_05", "blacklight_base_defense_06", "blacklight_base_defense_07", "blacklight_base_defense_08", "blacklight_base_defense_09", "blacklight_base_defense_10", "blacklight_base_defense_11", "blacklight_base_defense_12", "blacklight_base_defense_13", "blacklight_base_defense_14", "blacklight_base_defense_15", "blacklight_base_defense_16", "blacklight_base_defense_17", "blacklight_base_defense_18", "blacklight_base_defense_19", "blacklight_base_defense_20", "blacklight_base_defense_21"},
			shipSpawns = {"blacklight_assassin_tier4", "blacklight_assassin_tier4", "blacklight_assassin_tier4", "blacklight_bomber_tier4", "blacklight_bomber_tier4", "blacklight_bomber_tier4", "blacklight_fighter_tier4", "blacklight_fighter_tier4", "blacklight_fighter_tier4", "blacklight_leader_tier5"}
		},
		{spawnName = "spice_pirate_astroid_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 6435, z = -7024, y = -2, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 40, maxSpawnDistance = 80, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"spice_pirate_astroid_route_1_00", "spice_pirate_astroid_route_1_01", "spice_pirate_astroid_route_1_02", "spice_pirate_astroid_route_1_03", "spice_pirate_astroid_route_1_04", "spice_pirate_astroid_route_1_05", "spice_pirate_astroid_route_1_06", "spice_pirate_astroid_route_1_07", "spice_pirate_astroid_route_1_08", "spice_pirate_astroid_route_1_09", "spice_pirate_astroid_route_1_10", "spice_pirate_astroid_route_1_11", "spice_pirate_astroid_route_1_12", "spice_pirate_astroid_route_1_13", "spice_pirate_astroid_route_1_14", "spice_pirate_astroid_route_1_15", "spice_pirate_astroid_route_1_16"},
			shipSpawns = {"spice_pirate_fighter_tier4", "spice_pirate_transport_tier4", "spice_pirate_boss", "spice_pirate_fighter_tier4", "spice_pirate_fighter_tier4", "spice_pirate_fighter_tier4", "spice_pirate_fighter_tier4", "spice_pirate_fighter_tier4", "spice_pirate_transport_tier4", "spice_pirate_transport_tier4", "spice_pirate_transport_tier4", "spice_pirate_transport_tier4"}
		},
		{spawnName = "spice_to_generator_1", spawnType = SHIP_SPAWN_SINGLE, x = 6356, z = -7061, y = 2, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 40, maxSpawnDistance = 80, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"spice_to_generator_1_00", "spice_to_generator_1_01", "spice_to_generator_1_02", "spice_to_generator_1_03", "spice_to_generator_1_04", "spice_to_generator_1_05", "spice_to_generator_1_06", "spice_to_generator_1_07", "spice_to_generator_1_08", "spice_to_generator_1_09"},
			shipSpawns = {"spice_pirate_spy_tier4", "spice_pirate_transport_tier4"}
		},
		{spawnName = "scientist_lookout_2", spawnType = SHIP_SPAWN_SINGLE, x = 4861, z = -2763, y = 6701, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, minPatrol = 90, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"nebula_scientist_bodyguard_tier4", "nebula_scientist_lookout_tier4"}
		},
		{spawnName = "scientist_lookout_1", spawnType = SHIP_SPAWN_SINGLE, x = 538, z = -1108, y = 4026, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, minPatrol = 90, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"nebula_scientist_bodyguard_tier4", "nebula_scientist_lookout_tier4"}
		},
		{spawnName = "scientist_operation_4", spawnType = SHIP_SPAWN_SINGLE, x = 1275, z = -2910, y = 6983, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"scientist_operation_4_00", "scientist_operation_4_01", "scientist_operation_4_02", "scientist_operation_4_03"},
			shipSpawns = {"nebula_scientist_analyst_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_bodyguard_boss", "nebula_scientist_bodyguard_tier4", "nebula_scientist_bodyguard_tier4", "nebula_scientist_bodyguard_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_analyst_tier4", "nebula_scientist_analyst_tier4", "nebula_scientist_analyst_tier4", "nebula_scientist_analyst_tier4", "nebula_scientist_analyst_tier4", "nebula_scientist_analyst_tier4"}
		},
		{spawnName = "generator_imperial_defense_b", spawnType = SHIP_SPAWN_SINGLE, x = 6138, z = 6738, y = -6077, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 60, maxPatrol = 320, totalSpawns = 3,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4"}
		},
		{spawnName = "rebel_spies_1", spawnType = SHIP_SPAWN_SINGLE, x = -7378, z = -1321, y = 6649, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 160, totalSpawns = 6,
			shipSpawns = {"reb_bwing_tier4", "reb_xwing_tier4", "reb_z95_tier4", "reb_ywing_tier4", "reb_awing_tier4"}
		},
		{spawnName = "rebel_spy_nebulon_guard", spawnType = SHIP_SPAWN_SINGLE, x = -6624, z = -1310, y = 7333, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 160, totalSpawns = 4,
			shipSpawns = {"reb_bwing_tier4", "reb_xwing_tier4", "reb_awing_tier4", "reb_z95_tier4", "reb_ywing_tier4"}
		},
		{spawnName = "rebel_generator_defense_2", spawnType = SHIP_SPAWN_SINGLE, x = -3581, z = 2443, y = 4804, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"reb_awing_tier4", "reb_bwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4"}
		},
		{spawnName = "rebel_generator_defense_1", spawnType = SHIP_SPAWN_SINGLE, x = -3506, z = 2756, y = 4747, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier4", "reb_bwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4"}
		},
		{spawnName = "tatooine_imperial_tier3_inspect2escort", spawnType = SHIP_SPAWN_SINGLE, x = -5003, z = 4079, y = 6079, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 25, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4", "reb_z95_tier4", "reb_z95_tier4"}
		},
		{spawnName = "tatooine_imperial_tier3_inspect2_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -5009, z = 4104, y = 6001, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"rebel_scout_fighter_tier3"}
		},
		{spawnName = "traders_station_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 5802, z = -1527, y = -4659, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"traders_station_route_1_00", "traders_station_route_1_01", "traders_station_route_1_02", "traders_station_route_1_03", "traders_station_route_1_04", "traders_station_route_1_05", "traders_station_route_1_06", "traders_station_route_1_07", "traders_station_route_1_08"},
			shipSpawns = {"endor_trader_bodyguard_hire"}
		},
		{spawnName = "imperial_base_defense_1", spawnType = SHIP_SPAWN_SINGLE, x = -5395, z = -661, y = -5101, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 70, maxPatrol = 340, totalSpawns = 6,
			shipSpawns = {"imp_tie_advanced_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_aggressor_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_base_defense_3", spawnType = SHIP_SPAWN_SINGLE, x = -5848, z = -4070, y = -6499, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 70, maxPatrol = 340, totalSpawns = 6,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_fighter_tier4", "imp_tie_oppressor_tier4", "imp_tie_advanced_tier4", "imp_tie_bomber_tier4", "imp_tie_interceptor_tier4"}
		},
		{spawnName = "imperial_base_defense_2", spawnType = SHIP_SPAWN_SINGLE, x = -4681, z = -1795, y = -6620, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 70, maxPatrol = 340, totalSpawns = 6,
			shipSpawns = {"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_base_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = -5321, z = -1892, y = -5100, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 7,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_base_patrol_1_00", "imperial_base_patrol_1_01", "imperial_base_patrol_1_02", "imperial_base_patrol_1_03", "imperial_base_patrol_1_04", "imperial_base_patrol_1_05", "imperial_base_patrol_1_06", "imperial_base_patrol_1_07", "imperial_base_patrol_1_08", "imperial_base_patrol_1_09", "imperial_base_patrol_1_10", "imperial_base_patrol_1_11", "imperial_base_patrol_1_12", "imperial_base_patrol_1_13", "imperial_base_patrol_1_14", "imperial_base_patrol_1_15", "imperial_base_patrol_1_16", "imperial_base_patrol_1_17", "imperial_base_patrol_1_18", "imperial_base_patrol_1_19", "imperial_base_patrol_1_20", "imperial_base_patrol_1_21", "imperial_base_patrol_1_22", "imperial_base_patrol_1_23", "imperial_base_patrol_1_24", "imperial_base_patrol_1_25", "imperial_base_patrol_1_26", "imperial_base_patrol_1_27", "imperial_base_patrol_1_28", "imperial_base_patrol_1_29", "imperial_base_patrol_1_30", "imperial_base_patrol_1_31", "imperial_base_patrol_1_32", "imperial_base_patrol_1_33", "imperial_base_patrol_1_34", "imperial_base_patrol_1_35", "imperial_base_patrol_1_36", "imperial_base_patrol_1_37", "imperial_base_patrol_1_38", "imperial_base_patrol_1_39", "imperial_base_patrol_1_40", "imperial_base_patrol_1_41"},
			shipSpawns = {"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"}
		},
		{spawnName = "imperial_to_scientist_route", spawnType = SHIP_SPAWN_SINGLE, x = -5453, z = -2115, y = -5079, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, totalSpawns = 7,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_to_scientist_route_00", "imperial_to_scientist_route_01", "imperial_to_scientist_route_02", "imperial_to_scientist_route_03", "imperial_to_scientist_route_04", "imperial_to_scientist_route_05", "imperial_to_scientist_route_06", "imperial_to_scientist_route_07", "imperial_to_scientist_route_08", "imperial_to_scientist_route_09", "imperial_to_scientist_route_10", "imperial_to_scientist_route_11", "imperial_to_scientist_route_12"},
			shipSpawns = {"imperial_scout", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_base_to_generator", spawnType = SHIP_SPAWN_SINGLE, x = -4779, z = -1875, y = -5083, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 600, maxRespawn = 720, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_base_to_generator_00", "imperial_base_to_generator_01", "imperial_base_to_generator_02", "imperial_base_to_generator_03", "imperial_base_to_generator_04", "imperial_base_to_generator_05", "imperial_base_to_generator_06", "imperial_base_to_generator_07", "imperial_base_to_generator_08", "imperial_base_to_generator_09", "imperial_base_to_generator_10", "imperial_base_to_generator_11", "imperial_base_to_generator_12", "imperial_base_to_generator_13", "imperial_base_to_generator_14", "imperial_base_to_generator_15", "imperial_base_to_generator_16", "imperial_base_to_generator_17", "imperial_base_to_generator_18", "imperial_base_to_generator_19", "imperial_base_to_generator_20", "imperial_base_to_generator_21", "imperial_base_to_generator_22", "imperial_base_to_generator_23"},
			shipSpawns = {"imp_decimator_tier4", "imp_imperial_gunboat_tier4", "imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_base_defense_4", spawnType = SHIP_SPAWN_SINGLE, x = -7532, z = -2631, y = -4793, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 70, maxPatrol = 340, totalSpawns = 6,
			shipSpawns = {"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4", "imp_tie_bomber_tier4", "imp_tie_advanced_tier4", "imp_tie_aggressor_tier4"}
		},
		{spawnName = "trade_to_station_1", spawnType = SHIP_SPAWN_SINGLE, x = -2520, z = -5051, y = 280, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"trade_to_station_1_00", "trade_to_station_1_01", "trade_to_station_1_02", "trade_to_station_1_03", "trade_to_station_1_04", "trade_to_station_1_05", "trade_to_station_1_06", "trade_to_station_1_07"},
			shipSpawns = {"endor_trader_freighter"}
		},
		{spawnName = "tatooine_imperial_tier3_destroy1_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -3250, z = -4500, y = -1200, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 60, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier4", "reb_bwing_tier4", "rebel_raider_bomber_tier3", "rebel_raider_captain_tier3", "reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4"}
		},
		{spawnName = "trader_mercenaries_1", spawnType = SHIP_SPAWN_SINGLE, x = -2927, z = -5157, y = 411, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"trader_mercenaries_1_00", "trader_mercenaries_1_01", "trader_mercenaries_1_02", "trader_mercenaries_1_03", "trader_mercenaries_1_04", "trader_mercenaries_1_05", "trader_mercenaries_1_06", "trader_mercenaries_1_07", "trader_mercenaries_1_08", "trader_mercenaries_1_09", "trader_mercenaries_1_10", "trader_mercenaries_1_11", "trader_mercenaries_1_12", "trader_mercenaries_1_13"},
			shipSpawns = {"endor_trader_mercenary", "endor_trader_bodyguard_boss", "endor_trader_bodyguard_hire", "endor_trader_bodyguard_hire", "endor_trader_bodyguard_hire", "endor_trader_bodyguard_hire", "endor_trader_mercenary", "endor_trader_mercenary", "endor_trader_mercenary", "endor_trader_mercenary", "endor_trader_bodyguard_hire"}
		},
		{spawnName = "trader_guards_2", spawnType = SHIP_SPAWN_SINGLE, x = -2933, z = -5459, y = 590, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"endor_trader_bodyguard_hire"}
		},
		{spawnName = "trader_to_artisan_1", spawnType = SHIP_SPAWN_SINGLE, x = -3032, z = -5318, y = 717, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"trader_to_artisan_1_00", "trader_to_artisan_1_01", "trader_to_artisan_1_02", "trader_to_artisan_1_03", "trader_to_artisan_1_04"},
			shipSpawns = {"endor_trader_collector"}
		},
		{spawnName = "death_watch_patrol_2", spawnType = SHIP_SPAWN_SINGLE, x = 1751, z = -6843, y = -6369, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"death_watch_assassin_tier4", "death_watch_eradicator_tier4"}
		},
		{spawnName = "death_watch_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = 2639, z = -6807, y = -5925, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"death_watch_patrol_1_00", "death_watch_patrol_1_01", "death_watch_patrol_1_02", "death_watch_patrol_1_03", "death_watch_patrol_1_04", "death_watch_patrol_1_05", "death_watch_patrol_1_06", "death_watch_patrol_1_07", "death_watch_patrol_1_08", "death_watch_patrol_1_09", "death_watch_patrol_1_10", "death_watch_patrol_1_11", "death_watch_patrol_1_12", "death_watch_patrol_1_13", "death_watch_patrol_1_14", "death_watch_patrol_1_15", "death_watch_patrol_1_16"},
			shipSpawns = {"death_watch_assassin_tier4", "death_watch_eradicator_tier4", "death_watch_prowler_tier4", "death_watch_boss", "death_watch_prowler_tier4", "death_watch_prowler_tier4", "death_watch_prowler_tier4", "death_watch_prowler_tier4", "death_watch_eradicator_tier4", "death_watch_eradicator_tier4", "death_watch_eradicator_tier4", "death_watch_eradicator_tier4", "death_watch_assassin_tier4", "death_watch_assassin_tier4", "death_watch_assassin_tier4", "death_watch_assassin_tier4"}
		},
		{spawnName = "death_watch_guards_1", spawnType = SHIP_SPAWN_SINGLE, x = 2343, z = -7485, y = -7246, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 350, totalSpawns = 3,
			shipSpawns = {"death_watch_prowler_tier4", "death_watch_eradicator_tier4", "death_watch_assassin_tier4"}
		},
		{spawnName = "corellia_imperial_tier3_leg_3_destroy_aces", spawnType = SHIP_SPAWN_SINGLE, x = -5313, z = -5183, y = 2462, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 25, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier4", "reb_bwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4", "reb_z95_tier4"}
		},
		{spawnName = "droid_guards_2", spawnType = SHIP_SPAWN_SINGLE, x = -6063, z = 276, y = -553, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 3,
			shipSpawns = {"junk_droid_fighter"}
		},
		{spawnName = "droid_guards_1", spawnType = SHIP_SPAWN_SINGLE, x = -6929, z = 278, y = 26, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 4,
			shipSpawns = {"junk_droid_fighter"}
		},
		{spawnName = "droid_to_junk_1", spawnType = SHIP_SPAWN_SINGLE, x = -6444, z = 259, y = -279, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"droid_to_junk_1_00", "droid_to_junk_1_01", "droid_to_junk_1_02", "droid_to_junk_1_03", "droid_to_junk_1_04", "droid_to_junk_1_05", "droid_to_junk_1_06", "droid_to_junk_1_07", "droid_to_junk_1_08"},
			shipSpawns = {"junk_droid_scavenger", "junk_droid_fighter_boss", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger", "junk_droid_scavenger"}
		},
		{spawnName = "endor_smuggler_transport_1", spawnType = SHIP_SPAWN_SINGLE, x = -798, z = 3814, y = -812, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 350, maxRespawn = 650, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"endor_smuggler_transport_1_00", "endor_smuggler_transport_1_01", "endor_smuggler_transport_1_02", "endor_smuggler_transport_1_03", "endor_smuggler_transport_1_04", "endor_smuggler_transport_1_05", "endor_smuggler_transport_1_06", "endor_smuggler_transport_1_07", "endor_smuggler_transport_1_08", "endor_smuggler_transport_1_09", "endor_smuggler_transport_1_10"},
			shipSpawns = {"endor_smuggler_transport"}
		},
		{spawnName = "smuggler_guards_1", spawnType = SHIP_SPAWN_SINGLE, x = -818, z = 3863, y = -913, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"endor_smuggler_fighter"}
		},
		{spawnName = "corellia_imperial_tier3_leg_3_destroy_bwing", spawnType = SHIP_SPAWN_SINGLE, x = -1500, z = 5000, y = -2430, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 25, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_bwing_tier4"}
		},
		{spawnName = "smuggler_fighter_guards_1", spawnType = SHIP_SPAWN_SINGLE, x = -1905, z = 3818, y = -1292, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, minPatrol = 80, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"endor_smuggler_fighter"}
		},
		{spawnName = "hutt_smuggler_route", spawnType = SHIP_SPAWN_SINGLE, x = -4266, z = 3939, y = -3918, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_smuggler_route_00", "hutt_smuggler_route_01", "hutt_smuggler_route_02", "hutt_smuggler_route_03", "hutt_smuggler_route_04", "hutt_smuggler_route_05", "hutt_smuggler_route_06", "hutt_smuggler_route_07"},
			shipSpawns = {"hutt_fighter_s02_tier3", "hutt_fighter_s02_tier3", "hutt_pirate_s02_tier3", "huttsmuggler", "huttsmuggler", "huttsmuggler", "huttsmuggler"}
		},
		{spawnName = "hutt_smuggler_guard", spawnType = SHIP_SPAWN_SINGLE, x = -3934, z = 3798, y = -3808, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"hutt_pirate_s02_tier3", "hutt_pirate_s02_tier3", "hutt_bomber_s02_tier3"}
		},
		{spawnName = "blacksun_mission_dudes_1", spawnType = SHIP_SPAWN_SINGLE, x = -728, z = -1862, y = -5638, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 50, maxSpawnDistance = 100, minPatrol = 90, maxPatrol = 380, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier4", "blacksun_aggressor_tier4", "blacksun_bomber_s03_tier4", "blacksun_fighter_s03_tier4", "blacksun_marauder_tier4", "blacksun_vehement_tier4"}
		},
		{spawnName = "imperial_satellite_defense", spawnType = SHIP_SPAWN_SINGLE, x = -3432, z = -2837, y = -3695, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "tatooine_imperial_tier4_endscout1", spawnType = SHIP_SPAWN_SINGLE, x = -3606, z = -2695, y = -3771, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 50, maxPatrol = 400, totalSpawns = 1,
			shipSpawns = {"rebel_endscout_tier4"}
		},
		{spawnName = "imperial_star_defender_5", spawnType = SHIP_SPAWN_SINGLE, x = -6453, z = 7433, y = 4018, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 4,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_astroid_destroy_1", spawnType = SHIP_SPAWN_SINGLE, x = -5612, z = 7359, y = 4175, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 80, maxPatrol = 360, totalSpawns = 1,
			shipSpawns = {"imperial_demolition"}
		},
		{spawnName = "imperial_astroid_demo_1", spawnType = SHIP_SPAWN_SINGLE, x = -7445, z = 6821, y = 3689, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 80, maxPatrol = 360, totalSpawns = 1,
			shipSpawns = {"imperial_demolition"}
		},
		{spawnName = "imperial_star_defender_3", spawnType = SHIP_SPAWN_SINGLE, x = -4109, z = 7131, y = 3757, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 4,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_cargo_to_junk", spawnType = SHIP_SPAWN_SINGLE, x = -5019, z = 6550, y = 2419, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 350, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_cargo_to_junk_00", "imperial_cargo_to_junk_01", "imperial_cargo_to_junk_02", "imperial_cargo_to_junk_03", "imperial_cargo_to_junk_04", "imperial_cargo_to_junk_05", "imperial_cargo_to_junk_06", "imperial_cargo_to_junk_07", "imperial_cargo_to_junk_08", "imperial_cargo_to_junk_09", "imperial_cargo_to_junk_10", "imperial_cargo_to_junk_11"},
			shipSpawns = {"imperial_cargo_tower"}
		},
		{spawnName = "imperial_collector_n_engineer_1", spawnType = SHIP_SPAWN_SINGLE, x = -5141, z = 6454, y = 2274, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_collector_n_engineer_1_00", "imperial_collector_n_engineer_1_01", "imperial_collector_n_engineer_1_02", "imperial_collector_n_engineer_1_03", "imperial_collector_n_engineer_1_04", "imperial_collector_n_engineer_1_05", "imperial_collector_n_engineer_1_06", "imperial_collector_n_engineer_1_07", "imperial_collector_n_engineer_1_08", "imperial_collector_n_engineer_1_09", "imperial_collector_n_engineer_1_10", "imperial_collector_n_engineer_1_11", "imperial_collector_n_engineer_1_12", "imperial_collector_n_engineer_1_13", "imperial_collector_n_engineer_1_14", "imperial_collector_n_engineer_1_15", "imperial_collector_n_engineer_1_16"},
			shipSpawns = {"imperial_debris_collector", "imperial_engineer"}
		},
		{spawnName = "imperial_astroid_demo_2", spawnType = SHIP_SPAWN_SINGLE, x = -6618, z = 7359, y = 2054, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 80, maxPatrol = 360, totalSpawns = 1,
			shipSpawns = {"imperial_demolition"}
		},
		{spawnName = "imperial_demolition_1", spawnType = SHIP_SPAWN_SINGLE, x = -5199, z = 6548, y = 2453, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_demolition_1_00", "imperial_demolition_1_01", "imperial_demolition_1_02", "imperial_demolition_1_03", "imperial_demolition_1_04", "imperial_demolition_1_05", "imperial_demolition_1_06", "imperial_demolition_1_07", "imperial_demolition_1_08", "imperial_demolition_1_09", "imperial_demolition_1_10", "imperial_demolition_1_11"},
			shipSpawns = {"imperial_demolition"}
		},
		{spawnName = "imperial_debris_collector_1", spawnType = SHIP_SPAWN_SINGLE, x = -5195, z = 6642, y = 2287, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_debris_collector_1_00", "imperial_debris_collector_1_01", "imperial_debris_collector_1_02", "imperial_debris_collector_1_03", "imperial_debris_collector_1_04", "imperial_debris_collector_1_05", "imperial_debris_collector_1_06", "imperial_debris_collector_1_07", "imperial_debris_collector_1_08", "imperial_debris_collector_1_09", "imperial_debris_collector_1_10", "imperial_debris_collector_1_11", "imperial_debris_collector_1_12", "imperial_debris_collector_1_13", "imperial_debris_collector_1_14", "imperial_debris_collector_1_15", "imperial_debris_collector_1_16"},
			shipSpawns = {"imperial_debris_collector", "imp_decimator_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_star_defender_6", spawnType = SHIP_SPAWN_SINGLE, x = -6179, z = 6889, y = 2161, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 4,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_star_defender_2", spawnType = SHIP_SPAWN_SINGLE, x = -1978, z = 7153, y = 2331, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 4,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_fighter_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_star_guards_1", spawnType = SHIP_SPAWN_SINGLE, x = -3205, z = 6234, y = 957, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 4,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_junk_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = -4832, z = 4513, y = -602, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 3,
			shipSpawns = {"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_junk_guard_2", spawnType = SHIP_SPAWN_SINGLE, x = -5518, z = 4725, y = -537, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 3,
			shipSpawns = {"imp_tie_advanced_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4"}
		},
		{spawnName = "spice_pirates_defend_3", spawnType = SHIP_SPAWN_SINGLE, x = 1990, z = -5150, y = 2922, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 4,
			shipSpawns = {"spice_pirate_fighter_tier4"}
		},
		{spawnName = "imperial_trade_route_gaurd_1", spawnType = SHIP_SPAWN_SINGLE, x = -421, z = -5113, y = 2145, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_trade_route_gaurd_1_00", "imperial_trade_route_gaurd_1_01", "imperial_trade_route_gaurd_1_02", "imperial_trade_route_gaurd_1_03", "imperial_trade_route_gaurd_1_04", "imperial_trade_route_gaurd_1_05", "imperial_trade_route_gaurd_1_06", "imperial_trade_route_gaurd_1_07", "imperial_trade_route_gaurd_1_08", "imperial_trade_route_gaurd_1_09", "imperial_trade_route_gaurd_1_10", "imperial_trade_route_gaurd_1_11", "imperial_trade_route_gaurd_1_12", "imperial_trade_route_gaurd_1_13", "imperial_trade_route_gaurd_1_14", "imperial_trade_route_gaurd_1_15"},
			shipSpawns = {"imp_decimator_tier4", "imp_tie_advanced_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "trader_fighter_guards_1", spawnType = SHIP_SPAWN_SINGLE, x = -2062, z = -5676, y = 567, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"endor_trader_bodyguard_hire"}
		},
		{spawnName = "spice_pirates_defend_2", spawnType = SHIP_SPAWN_SINGLE, x = 1062, z = -4727, y = -953, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 80, maxPatrol = 360, totalSpawns = 4,
			shipSpawns = {"spice_pirate_fighter_tier4"}
		},
		{spawnName = "spice_defenders_1", spawnType = SHIP_SPAWN_SINGLE, x = 2084, z = -5135, y = 481, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"spice_pirate_fighter_tier4"}
		},
		{spawnName = "generator_to_spice_base_1", spawnType = SHIP_SPAWN_SINGLE, x = 2067, z = -5512, y = 462, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 20, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"generator_to_spice_base_1_00", "generator_to_spice_base_1_01", "generator_to_spice_base_1_02", "generator_to_spice_base_1_03", "generator_to_spice_base_1_04"},
			shipSpawns = {"spice_pirate_transport_tier4"}
		},
		{spawnName = "scientist_lookout_4", spawnType = SHIP_SPAWN_SINGLE, x = -1029, z = 989, y = 278, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, minPatrol = 90, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"nebula_scientist_bodyguard_tier4", "nebula_scientist_lookout_tier4"}
		},
		{spawnName = "scientist_lookout_3", spawnType = SHIP_SPAWN_SINGLE, x = 635, z = 2847, y = 601, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, minPatrol = 90, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"nebula_scientist_bodyguard_tier4", "nebula_scientist_lookout_tier4"}
		},
		{spawnName = "corellia_privateer_tier3_inspect_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 1317, z = -455, y = -2876, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 10, maxRespawn = 20, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"corellia_privateer_tier3_inspect_spawner_00", "corellia_privateer_tier3_inspect_spawner_01"},
			shipSpawns = {"evil_raider_tyrant_tier3"}
		},
		{spawnName = "stn_endor_spynet_inspect_1", spawnType = SHIP_SPAWN_SINGLE, x = 251, z = 6, y = -1973, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 45, maxRespawn = 90, minSpawnDistance = 150, maxSpawnDistance = 200, minPatrol = 300, maxPatrol = 750, totalSpawns = 1,
			shipSpawns = {"spynet_watcher_tier3"}
		},
		{spawnName = "imperial_generator_defense_2", spawnType = SHIP_SPAWN_SINGLE, x = -655, z = -2005, y = -202, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"}
		},
		{spawnName = "imperial_generator_defense_1", spawnType = SHIP_SPAWN_SINGLE, x = -791, z = -2202, y = -96, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "scientist_operation_2", spawnType = SHIP_SPAWN_SINGLE, x = 563, z = 989, y = 1179, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"scientist_operation_2_00", "scientist_operation_2_01", "scientist_operation_2_02", "scientist_operation_2_03"},
			shipSpawns = {"nebula_scientist_analyst_tier4", "nebula_scientist_researcher_tier4"}
		},
		{spawnName = "scientist_operation_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = 400, z = 1020, y = 1160, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, minPatrol = 90, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"nebula_scientist_bodyguard_tier4"}
		},
		{spawnName = "scientist_operation_guard_2", spawnType = SHIP_SPAWN_SINGLE, x = -630, z = 1120, y = 1370, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, minPatrol = 90, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"nebula_scientist_bodyguard_tier4"}
		},
		{spawnName = "scientist_operation_1", spawnType = SHIP_SPAWN_SINGLE, x = -1147, z = 1105, y = 1493, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"scientist_operation_1_00", "scientist_operation_1_01", "scientist_operation_1_02", "scientist_operation_1_03", "scientist_operation_1_04", "scientist_operation_1_05", "scientist_operation_1_06", "scientist_operation_1_07", "scientist_operation_1_08"},
			shipSpawns = {"nebula_scientist_analyst_tier4", "nebula_scientist_researcher_tier4"}
		},
		{spawnName = "scientists_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 608, z = -423, y = 2569, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 40, maxSpawnDistance = 80, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"scientists_route_1_00", "scientists_route_1_01", "scientists_route_1_02", "scientists_route_1_03", "scientists_route_1_04", "scientists_route_1_05", "scientists_route_1_06", "scientists_route_1_07", "scientists_route_1_08", "scientists_route_1_09", "scientists_route_1_10", "scientists_route_1_11", "scientists_route_1_12", "scientists_route_1_13", "scientists_route_1_14", "scientists_route_1_15", "scientists_route_1_16", "scientists_route_1_17", "scientists_route_1_18", "scientists_route_1_19", "scientists_route_1_20", "scientists_route_1_21", "scientists_route_1_22"},
			shipSpawns = {"nebula_scientist_analyst_tier4", "nebula_scientist_researcher_tier4", "nebula_scientist_bodyguard_tier4"}
		},
	},
}

registerScreenPlay("SpaceEndorSpawner", true)
