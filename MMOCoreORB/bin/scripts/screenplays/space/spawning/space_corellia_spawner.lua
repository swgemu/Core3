SpaceCorelliaSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceCorelliaSpawner",

	spaceZone = "space_corellia",

	shipSpawns = {
		{spawnName = "binyare_fighter_eight_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 6562, z = -6987, y = 6527, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"binyare_fighter_eight_spawner_00", "binyare_fighter_eight_spawner_01", "binyare_fighter_eight_spawner_02", "binyare_fighter_eight_spawner_03", "binyare_fighter_eight_spawner_04", "binyare_fighter_eight_spawner_05", "binyare_fighter_eight_spawner_06", "binyare_fighter_eight_spawner_07", "binyare_fighter_eight_spawner_08", "binyare_fighter_eight_spawner_09", "binyare_fighter_eight_spawner_10", "binyare_fighter_eight_spawner_11", "binyare_fighter_eight_spawner_12", "binyare_fighter_eight_spawner_13", "binyare_fighter_eight_spawner_14"},
			shipSpawns = {"binyare_raider_average", "binyare_raider_average", "binyare_raider_average", "binyare_raider_average"}
		},
		{spawnName = "binyare_spacestation_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -544, z = 4956, y = 4451, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"binyare_spacestation_spawner_00", "binyare_spacestation_spawner_01", "binyare_spacestation_spawner_02", "binyare_spacestation_spawner_03", "binyare_spacestation_spawner_04", "binyare_spacestation_spawner_05", "binyare_spacestation_spawner_06", "binyare_spacestation_spawner_07", "binyare_spacestation_spawner_08", "binyare_spacestation_spawner_09", "binyare_spacestation_spawner_10", "binyare_spacestation_spawner_11"},
			shipSpawns = {"binyare_raider_average", "binyare_raider_rookie"}
		},
		{spawnName = "talus_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = 5196, z = -4512, y = -2624, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 30, maxSpawnDistance = 60, minPatrol = 100, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"trade_fed_fighter"}
		},
		{spawnName = "hutt_fighterleader_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 7034, z = -4780, y = -487, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_fighterleader_spawner_00", "hutt_fighterleader_spawner_01", "hutt_fighterleader_spawner_02", "hutt_fighterleader_spawner_03", "hutt_fighterleader_spawner_04", "hutt_fighterleader_spawner_05"},
			shipSpawns = {"hutt_mesot_tier3", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "civtransport_corellia_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 5801, z = -4932, y = -3147, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"civtransport_corellia_spawner_00", "civtransport_corellia_spawner_01", "civtransport_corellia_spawner_02", "civtransport_corellia_spawner_03", "civtransport_corellia_spawner_04", "civtransport_corellia_spawner_05"},
			shipSpawns = {"civilian_science_transport_tier1", "freighterheavy_tier3_story", "freighterheavy_tier3_story"}
		},
		{spawnName = "talus_corsecguards_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 5818, z = -5566, y = -2954, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 7,
			patrolsToAssign = 5, fixedPatrolPoints = {"talus_corsecguards_one_spawner_00", "talus_corsecguards_one_spawner_01", "talus_corsecguards_one_spawner_02", "talus_corsecguards_one_spawner_03", "talus_corsecguards_one_spawner_04", "talus_corsecguards_one_spawner_05", "talus_corsecguards_one_spawner_06", "talus_corsecguards_one_spawner_07", "talus_corsecguards_one_spawner_08", "talus_corsecguards_one_spawner_09", "talus_corsecguards_one_spawner_10", "talus_corsecguards_one_spawner_11", "talus_corsecguards_one_spawner_12"},
			shipSpawns = {"corsec_fighter_tier1", "corsec_interceptor_tier1", "corsec_lancer_tier1"}
		},
		{spawnName = "talus_civi_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 6086, z = -5443, y = -2869, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"talus_civi_two_spawner_00", "talus_civi_two_spawner_01", "talus_civi_two_spawner_02", "talus_civi_two_spawner_03", "talus_civi_two_spawner_04", "talus_civi_two_spawner_05", "talus_civi_two_spawner_06", "talus_civi_two_spawner_07", "talus_civi_two_spawner_08"},
			shipSpawns = {"civilian_science_transport_tier1", "freighterheavy_tier1", "freighterlight_tier1", "freightermedium_tier1"}
		},
		{spawnName = "talus2corellia_transport_1", spawnType = SHIP_SPAWN_SINGLE, x = 5717, z = -5438, y = -3532, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 11, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"talus2corellia_transport_1_00", "talus2corellia_transport_1_01", "talus2corellia_transport_1_02", "talus2corellia_transport_1_03", "talus2corellia_transport_1_04", "talus2corellia_transport_1_05", "talus2corellia_transport_1_06", "talus2corellia_transport_1_07", "talus2corellia_transport_1_08", "talus2corellia_transport_1_09"},
			shipSpawns = {"freighterlight_tier1", "freighterheavy_tier1", "freightermedium_tier1"}
		},
		{spawnName = "corsec_fighter_four_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 5779, z = -5139, y = -3739, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 100, maxSpawnDistance = 101, minPatrol = 100, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"corsec_interceptor_tier1"}
		},
		{spawnName = "rebel_fighter_six_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 4652, z = -7032, y = -5491, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier1", "reb_z95_tier1", "reb_ywing_tier1", "reb_bwing_tier1", "reb_awing_tier1"}
		},
		{spawnName = "rebel_squad_3", spawnType = SHIP_SPAWN_SQUADRON, x = -713, z = 1740, y = 6555, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_squad_3_00", "rebel_squad_3_01", "rebel_squad_3_02", "rebel_squad_3_03", "rebel_squad_3_04", "rebel_squad_3_05"},
			shipSpawns = {"squad_rebel_corellia_3"}
		},
		{spawnName = "binyare_fighter_six_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -1974, z = -5810, y = 6408, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"binyare_raider_average", "binyare_raider_average"}
		},
		{spawnName = "binyare_fighter_seven_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 766, z = -3683, y = 5708, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"binyare_raider_average", "binyare_raider_average"}
		},
		{spawnName = "blacksun_asteroid_three_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -6420, z = 6215, y = 6292, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier2", "blacksun_aggressor_tier2", "blacksun_bomber_s02_tier2", "blacksun_marauder_tier2", "blacksun_vehement_tier2"}
		},
		{spawnName = "blacksun_deep_three_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -5955, z = 5450, y = 5453, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 500, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "blacksun_deep_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -7181, z = 5751, y = 5501, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_s03_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "blacksun_deep_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -5175, z = 5404, y = 6138, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"blacksun_deep_one_spawner_00", "blacksun_deep_one_spawner_01", "blacksun_deep_one_spawner_02", "blacksun_deep_one_spawner_03", "blacksun_deep_one_spawner_04", "blacksun_deep_one_spawner_05", "blacksun_deep_one_spawner_06"},
			shipSpawns = {"blacksun_aggressor_tier1", "blacksun_bomber_ace_s04_tier1", "blacksun_fighter_s01_tier1"}
		},
		{spawnName = "blacksun_asteroid_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -5209, z = 6681, y = 6765, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 23, minPatrol = 100, maxPatrol = 500, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier2"}
		},
		{spawnName = "blacksun_fighter_eight_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -1960, z = 6841, y = 6285, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_ace_s04_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1"}
		},
		{spawnName = "blacksun_asteroid_three_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -2722, z = 6677, y = 6430, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, minPatrol = 100, maxPatrol = 400, totalSpawns = 3,
			shipSpawns = {"blacksun_ace_s04_tier2", "blacksun_aggressor_tier2", "blacksun_bomber_s02_tier2", "blacksun_fighter_s01_tier2", "blacksun_vehement_tier2"}
		},
		{spawnName = "blacksun_asteroid_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -7004, z = 6652, y = 7272, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, minPatrol = 100, maxPatrol = 500, totalSpawns = 6,
			shipSpawns = {"blacksun_aggressor_tier1", "blacksun_bomber_ace_s04_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "blacksun_leader_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -7051, z = 7151, y = 6872, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 150, maxRespawn = 210, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"blacksun_leader_spawner_00", "blacksun_leader_spawner_01", "blacksun_leader_spawner_02", "blacksun_leader_spawner_03", "blacksun_leader_spawner_04", "blacksun_leader_spawner_05", "blacksun_leader_spawner_06", "blacksun_leader_spawner_07", "blacksun_leader_spawner_08"},
			shipSpawns = {"blacksun_anianti", "blacksun_marauder_tier1", "blacksun_vehement_tier1", "blacksun_bomber_s01_tier1", "blacksun_aggressor_tier1", "blacksun_ace_s04_tier1"}
		},
		{spawnName = "blacksun_cmdship_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -7080, z = 6932, y = 6888, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"blacksun_cmdship_spawner_00", "blacksun_cmdship_spawner_01", "blacksun_cmdship_spawner_02", "blacksun_cmdship_spawner_03", "blacksun_cmdship_spawner_04", "blacksun_cmdship_spawner_05", "blacksun_cmdship_spawner_06", "blacksun_cmdship_spawner_07", "blacksun_cmdship_spawner_08", "blacksun_cmdship_spawner_09"},
			shipSpawns = {"blacksun_freighterheavy_tier1", "blacksun_freighterlight_tier1"}
		},
		{spawnName = "blacksun_deep_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -4224, z = 6600, y = 6408, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_ace_s04_tier1", "blacksun_bomber_s03_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "rebel_nebula_two_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -6864, z = -4111, y = 1964, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_nebula_two_spawner_00", "rebel_nebula_two_spawner_01", "rebel_nebula_two_spawner_02", "rebel_nebula_two_spawner_03", "rebel_nebula_two_spawner_04", "rebel_nebula_two_spawner_05", "rebel_nebula_two_spawner_06", "rebel_nebula_two_spawner_07"},
			shipSpawns = {"squad_rebel_gunboat_tier1"}
		},
		{spawnName = "rebel_nebula_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -6495, z = 2218, y = 2325, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_nebula_spawner_00", "rebel_nebula_spawner_01", "rebel_nebula_spawner_02", "rebel_nebula_spawner_03", "rebel_nebula_spawner_04", "rebel_nebula_spawner_05", "rebel_nebula_spawner_06", "rebel_nebula_spawner_07"},
			shipSpawns = {"squad_rebel_gunboat_tier1"}
		},
		{spawnName = "rebel_transport_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -6821, z = 2535, y = 2091, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_transport_spawner_00", "rebel_transport_spawner_01"},
			shipSpawns = {"reb_freightermedium_tier1", "reb_xwing_tier1"}
		},
		{spawnName = "rebel_fighterleader_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -7412, z = 1480, y = 980, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier1", "reb_ywing_tier1", "rebel_major_metoni", "reb_z95_tier1", "reb_awing_tier1", "reb_bwing_tier1"}
		},
		{spawnName = "black_sun_asteroid_5", spawnType = SHIP_SPAWN_SINGLE, x = -2727, z = -34, y = -4571, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 64, minPatrol = 30, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1"}
		},
		{spawnName = "binyare_fighterleader_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 3435, z = -6177, y = 5145, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 15, minPatrol = 100, maxPatrol = 400, totalSpawns = 4,
			shipSpawns = {"binyare_black_jack", "binyare_raider_average", "binyare_raider_average", "binyare_raider_average", "binyare_raider_average", "binyare_raider_average", "binyare_raider_average", "binyare_raider_average", "binyare_raider_average", "binyare_raider_average", "binyare_raider_average"}
		},
		{spawnName = "binyare_fighter_four_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -991, z = -7394, y = 4683, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 101, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"binyare_raider_average", "binyare_raider_rookie"}
		},
		{spawnName = "binyare_debris_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 155, z = -6269, y = 3573, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"binyare_raider_rookie", "binyare_raider_average"}
		},
		{spawnName = "binyare_fighter_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 1820, z = -7172, y = 3717, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"binyare_raider_average", "binyare_raider_rookie"}
		},
		{spawnName = "binyare_fighter_three", spawnType = SHIP_SPAWN_SINGLE, x = -1931, z = -4354, y = 3430, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"binyare_raider_rookie", "binyare_raider_average"}
		},
		{spawnName = "blacksun_deep_four_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -2450, z = -2902, y = 4451, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 350, totalSpawns = 3,
			shipSpawns = {"blacksun_bomber_ace_s04_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "hiddendagger_fighter_three_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 5981, z = 5575, y = 490, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_executioner_tier1", "hidden_daggers_killer_tier1"}
		},
		{spawnName = "hiddendagger_fighterb_five_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 6984, z = 6594, y = 1498, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 120, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_executioner_tier1", "hidden_daggers_slayer_tier1"}
		},
		{spawnName = "hiddendagger_fighter_eight_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 5246, z = 7047, y = 1239, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_eliminator_tier1", "hidden_daggers_enforcer_tier1"}
		},
		{spawnName = "hutt_fighter_three_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 7101, z = 874, y = 1329, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "hutt_fighter_five_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 6033, z = -71, y = 399, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "hutt_fighter_six_spawnwer", spawnType = SHIP_SPAWN_SINGLE, x = 5870, z = -928, y = -661, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 100, maxSpawnDistance = 200, minPatrol = 100, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"hutt_bomber_s02_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "hutt_fighter_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 4615, z = -605, y = -375, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "hutt_fighter_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 3519, z = -1006, y = -1241, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1"}
		},
		{spawnName = "rebel_squad_2", spawnType = SHIP_SPAWN_SQUADRON, x = 1786, z = -1621, y = -964, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_squad_2_00", "rebel_squad_2_01", "rebel_squad_2_02", "rebel_squad_2_03", "rebel_squad_2_04", "rebel_squad_2_05"},
			shipSpawns = {"squad_rebel_corellia_2"}
		},
		{spawnName = "rebel_fighter_seven_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 4213, z = -937, y = -2413, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_xwing_tier1", "reb_z95_tier1", "reb_ywing_tier1", "reb_bwing_tier1", "reb_awing_tier1"}
		},
		{spawnName = "corelliatotalus_transport", spawnType = SHIP_SPAWN_SINGLE, x = -5761, z = -5231, y = -4493, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 11, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"corelliatotalus_transport_00", "corelliatotalus_transport_01", "corelliatotalus_transport_02", "corelliatotalus_transport_03", "corelliatotalus_transport_04", "corelliatotalus_transport_05", "corelliatotalus_transport_06", "corelliatotalus_transport_07", "corelliatotalus_transport_08", "corelliatotalus_transport_09", "corelliatotalus_transport_10"},
			shipSpawns = {"freighterlight_tier1", "freighterheavy_tier3_story", "freighterheavy_tier3_story"}
		},
		{spawnName = "corellia_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = -5868, z = -4844, y = -4600, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 14, minSpawnDistance = 30, maxSpawnDistance = 120, minPatrol = 100, maxPatrol = 400, totalSpawns = 3,
			shipSpawns = {"corsec_interceptor_tier1", "corsec_lancer_tier1"}
		},
		{spawnName = "corl_cmrs_way", spawnType = SHIP_SPAWN_SINGLE, x = -5628, z = -5335, y = -4672, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 120, maxRespawn = 240, minSpawnDistance = 3, maxSpawnDistance = 24, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"corl_cmrs_way_00", "corl_cmrs_way_01", "corl_cmrs_way_02", "corl_cmrs_way_03", "corl_cmrs_way_04", "corl_cmrs_way_05"},
			shipSpawns = {"corsec_fighter_tier1", "freighterlight_tier1", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freightermedium_tier1"}
		},
		{spawnName = "corellia_commerce", spawnType = SHIP_SPAWN_SINGLE, x = -5775, z = -6034, y = -4691, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 4, maxSpawnDistance = 32, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"corellia_commerce_00", "corellia_commerce_01", "corellia_commerce_02", "corellia_commerce_03", "corellia_commerce_04", "corellia_commerce_05"},
			shipSpawns = {"civilian_science_transport_tier1", "corsec_fighter_tier1", "freightermedium_tier1", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_tier1"}
		},
		{spawnName = "corsec_fighter_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -2745, z = -5149, y = -4811, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 500, totalSpawns = 3,
			shipSpawns = {"corsec_fighter_tier1"}
		},
		{spawnName = "corsec_security_2", spawnType = SHIP_SPAWN_SINGLE, x = -4194, z = -5203, y = -4467, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 32, minPatrol = 150, maxPatrol = 450, totalSpawns = 4,
			shipSpawns = {"corsec_fighter_tier1"}
		},
		{spawnName = "rebel_squad_1", spawnType = SHIP_SPAWN_SQUADRON, x = -5132, z = -1506, y = 365, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_squad_1_00", "rebel_squad_1_01", "rebel_squad_1_02", "rebel_squad_1_03", "rebel_squad_1_04", "rebel_squad_1_05"},
			shipSpawns = {"squad_rebel_corellia_1"}
		},
		{spawnName = "imperial_fighter_five_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -6064, z = 218, y = -2678, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 45, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_tie_bomberwithguard_tier1"}
		},
		{spawnName = "imperial_fighter_eight_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -7186, z = 410, y = -2021, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 45, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 7,
			shipSpawns = {"imp_tie_fighter_tier1", "imp_tie_bomber_tier1", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{spawnName = "imperial_fighter_three_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -6902, z = -240, y = 174, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 45, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_tie_mix_tier1"}
		},
		{spawnName = "rebel_fighter_three_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -5518, z = 399, y = 406, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier1", "reb_ywing_tier1", "reb_z95_tier1", "reb_awing_tier1", "reb_bwing_tier1"}
		},
		{spawnName = "imperial_fighter_two_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -5428, z = 370, y = 385, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 45, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_tie_bomberwithguard_tier1"}
		},
		{spawnName = "imperial_fighter_seven_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -6458, z = -2137, y = -1846, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 45, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 7,
			shipSpawns = {"imp_tie_fighter_tier1", "imp_tie_bomber_tier1", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{spawnName = "imperial_debris_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -5993, z = -2602, y = -1569, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_fighter_tier1", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_oppressor_tier1", "imp_tie_interceptor_tier1"}
		},
		{spawnName = "imperial_salvage_one", spawnType = SHIP_SPAWN_SINGLE, x = -5856, z = -1867, y = -1197, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 15, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_salvage_one_00", "imperial_salvage_one_01", "imperial_salvage_one_02", "imperial_salvage_one_03", "imperial_salvage_one_04", "imperial_salvage_one_05", "imperial_salvage_one_06", "imperial_salvage_one_07"},
			shipSpawns = {"imp_freighterheavy_tier1"}
		},
		{spawnName = "rebel_debris_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -609, z = -4293, y = -3426, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier1", "reb_awing_tier1", "reb_bwing_tier1", "reb_ywing_tier1", "reb_z95_tier1"}
		},
		{spawnName = "corsec_fighter_five_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 1183, z = -4940, y = -4298, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"corsec_interceptor_tier1", "corsec_lancer_tier1"}
		},
		{spawnName = "rebel_fighter_four_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 3475, z = -7014, y = -6208, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_z95_tier1", "reb_ywing_tier1", "reb_bwing_tier1", "reb_awing_tier1"}
		},
		{spawnName = "corsec_fighterleader_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -463, z = -5717, y = -5334, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"corsec_chief_noloinian", "corsec_fighter_tier1", "corsec_fighter_tier1", "corsec_fighter_tier1", "corsec_fighter_tier1", "corsec_fighter_tier1", "corsec_fighter_tier1", "corsec_fighter_tier1", "corsec_fighter_tier1", "corsec_interceptor_tier1"}
		},
		{spawnName = "corsec_spacestation_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 183, z = -5333, y = -6676, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"corsec_spacestation_spawner_00", "corsec_spacestation_spawner_01", "corsec_spacestation_spawner_02", "corsec_spacestation_spawner_03", "corsec_spacestation_spawner_04", "corsec_spacestation_spawner_05", "corsec_spacestation_spawner_06", "corsec_spacestation_spawner_07", "corsec_spacestation_spawner_08"},
			shipSpawns = {"corsec_fighter_tier1", "corsec_lancer_tier1"}
		},
		{spawnName = "corsec_leaderspawner_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 501, z = -5721, y = -6124, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, minPatrol = 100, maxPatrol = 400, totalSpawns = 3,
			shipSpawns = {"corsec_cpt_tibbs", "corsec_interceptor_tier1", "corsec_interceptor_tier1", "corsec_interceptor_tier1", "corsec_interceptor_tier1", "corsec_interceptor_tier1", "corsec_interceptor_tier1", "corsec_interceptor_tier1", "corsec_interceptor_tier1", "corsec_lancer_tier1"}
		},
		{spawnName = "corsec_fighter_three_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 145, z = -5604, y = -6045, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 500, totalSpawns = 2,
			shipSpawns = {"corsec_fighter_tier1", "corsec_interceptor_tier1"}
		},
		{spawnName = "corsectocorellia_transport_one", spawnType = SHIP_SPAWN_SINGLE, x = 130, z = -5345, y = -5694, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 11, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"corsectocorellia_transport_one_00", "corsectocorellia_transport_one_01", "corsectocorellia_transport_one_02", "corsectocorellia_transport_one_03", "corsectocorellia_transport_one_04", "corsectocorellia_transport_one_05", "corsectocorellia_transport_one_06", "corsectocorellia_transport_one_07", "corsectocorellia_transport_one_08", "corsectocorellia_transport_one_09", "corsectocorellia_transport_one_10"},
			shipSpawns = {"freighterlight_tier1", "freighterheavy_tier3_story", "freighterheavy_tier3_story"}
		},
		{spawnName = "corsec_fighter_six_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 463, z = -5369, y = -5745, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"corsec_fighter_tier1"}
		},
		{spawnName = "corsec_fighter_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 882, z = -5514, y = -5283, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 50, maxSpawnDistance = 80, minPatrol = 100, maxPatrol = 500, totalSpawns = 2,
			shipSpawns = {"corsec_fighter_tier1", "corsec_lancer_tier1"}
		},
		{spawnName = "black_sun_asteroid_1", spawnType = SHIP_SPAWN_SINGLE, x = 590, z = -3500, y = -6000, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 64, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"blacksun_aggressor_tier1", "blacksun_bomber_ace_s04_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "hiddendagger_fighterleader_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 3976, z = 7232, y = 1122, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"hiddendagger_fighterleader_spawner_00", "hiddendagger_fighterleader_spawner_01", "hiddendagger_fighterleader_spawner_02", "hiddendagger_fighterleader_spawner_03", "hiddendagger_fighterleader_spawner_04", "hiddendagger_fighterleader_spawner_05", "hiddendagger_fighterleader_spawner_06", "hiddendagger_fighterleader_spawner_07", "hiddendagger_fighterleader_spawner_08", "hiddendagger_fighterleader_spawner_09", "hiddendagger_fighterleader_spawner_10", "hiddendagger_fighterleader_spawner_11"},
			shipSpawns = {"hidden_blackrazorcat", "hidden_daggers_eliminator_tier1", "hidden_daggers_eliminator_tier1", "hidden_daggers_eliminator_tier1", "hidden_daggers_eliminator_tier1", "hidden_daggers_eliminator_tier1", "hidden_daggers_eliminator_tier1", "hidden_daggers_killer_tier1", "hidden_daggers_killer_tier1", "hidden_daggers_killer_tier1", "hidden_daggers_killer_tier1", "hidden_daggers_nebula_stalker_tier1"}
		},
		{spawnName = "hiddendagger_fighter_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 3581, z = 6686, y = -1315, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 4, maxSpawnDistance = 10, minPatrol = 100, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"hidden_daggers_eliminator_tier1", "hidden_daggers_killer_tier1"}
		},
		{spawnName = "hiddendagger_fighter_five_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 3480, z = 6768, y = -11, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 101, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_executioner_tier1", "hidden_daggers_killer_tier1"}
		},
		{spawnName = "hiddendagger_fighterb_three_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -208, z = 5843, y = -790, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_enforcer_tier1", "hidden_daggers_executioner_tier1"}
		},
		{spawnName = "hiddendagger_fighter_four_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 1986, z = 6154, y = 989, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_enforcer_tier1", "hidden_daggers_slayer_tier1"}
		},
		{spawnName = "binyare_debris_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 5160, z = -1744, y = 4818, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"binyare_raider_rookie", "binyare_raider_average"}
		},
		{spawnName = "binyare_fighter_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 5948, z = -1938, y = 6031, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"binyare_raider_average", "binyare_raider_rookie"}
		},
		{spawnName = "binyare_fighter_five_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 4252, z = -2744, y = 6133, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"binyare_raider_average", "binyare_raider_rookie"}
		},
		{spawnName = "binyare_asteroid_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 6426, z = -1500, y = 6518, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"binyare_raider_rookie", "binyare_raider_average"}
		},
		{spawnName = "blacksun_raider_patrol", spawnType = SHIP_SPAWN_SINGLE, x = -4346, z = 5255, y = 5274, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 5, maxSpawnDistance = 25, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"blacksun_raider_patrol_00", "blacksun_raider_patrol_01", "blacksun_raider_patrol_02", "blacksun_raider_patrol_03", "blacksun_raider_patrol_04", "blacksun_raider_patrol_05", "blacksun_raider_patrol_06", "blacksun_raider_patrol_07"},
			shipSpawns = {"blacksun_bomber_ace_s04_tier1", "blacksun_fighter_s01_tier1"}
		},
		{spawnName = "blacksun_fighter_five_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -1894, z = 3873, y = 3360, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_ace_s04_tier1", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "rebel_squad_4", spawnType = SHIP_SPAWN_SQUADRON, x = -102, z = 2780, y = 1974, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_squad_4_00", "rebel_squad_4_01", "rebel_squad_4_02", "rebel_squad_4_03", "rebel_squad_4_04", "rebel_squad_4_05"},
			shipSpawns = {"squad_rebel_corellia_4"}
		},
		{spawnName = "hiddendagger_fighterb_four_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 41, z = 1568, y = 1463, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_eliminator_tier1", "hidden_daggers_slayer_tier1"}
		},
		{spawnName = "corellia_imperial_tier2_inspect_freighter", spawnType = SHIP_SPAWN_SINGLE, x = -2466, z = 1971, y = 6320, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 10, maxRespawn = 30, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"rebel_spysmuggler_tier2"}
		},
		{spawnName = "hiddendaggers_fighterb_one", spawnType = SHIP_SPAWN_SINGLE, x = 2581, z = 1675, y = -3728, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_eliminator_tier1", "hidden_daggers_enforcer_tier1"}
		},
		{spawnName = "rebel_asteroid_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -530, z = -932, y = -1935, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 500, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier1", "reb_bwing_tier1", "reb_xwing_tier1", "reb_ywing_tier1", "reb_z95_tier1"}
		},
		{spawnName = "hiddendaggers_nebula_four_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 4675, z = 3781, y = -441, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 400, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_executioner_tier1", "hidden_daggers_killer_tier1"}
		},
		{spawnName = "hiddendagger_fighterb_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 5235, z = 5758, y = -2569, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 101, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_executioner_tier1", "hidden_daggers_killer_tier1"}
		},
		{spawnName = "rebel_fighterleader_three_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -4156, z = 302, y = 796, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier1", "reb_ywing_tier1", "rebel_lt_asperago", "reb_z95_tier1", "reb_bwing_tier1", "reb_awing_tier1"}
		},
		{spawnName = "imperial_fighterleader_one_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -4219, z = 328, y = 829, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 150, maxRespawn = 210, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 500, totalSpawns = 1,
			shipSpawns = {"squad_boss_corellia_imperial_major_gek"}
		},
		{spawnName = "rebel_corellia_deep_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -3466, z = 971, y = 493, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier1", "reb_bwing_tier1", "reb_xwing_cadet_tier1", "reb_ywing_tier1", "reb_z95_tier1"}
		},
		{spawnName = "rebel_asteroid_raider_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -1899, z = 1466, y = 1141, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 150, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier1", "reb_bwing_tier1", "reb_xwing_cadet_tier1", "reb_xwing_tier1", "reb_ywing_tier1", "reb_z95_tier1"}
		},
		{spawnName = "small_rebel_outpost", spawnType = SHIP_SPAWN_SINGLE, x = -1970, z = 1384, y = 1138, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 32, maxSpawnDistance = 64, minPatrol = 80, maxPatrol = 200, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier1", "reb_ywing_tier1", "reb_z95_tier1", "reb_awing_tier1", "reb_bwing_tier1"}
		},
		{spawnName = "rebel_fighter_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -3936, z = 2704, y = 2172, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_ywing_tier1", "reb_z95_tier1", "reb_awing_tier1", "reb_bwing_tier1"}
		},
		{spawnName = "rebel_spacestation_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -959, z = -5, y = -1328, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier1", "reb_bwing_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_ywing_tier1", "reb_z95_tier1"}
		},
		{spawnName = "rebel_ace_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = -1528, z = 152, y = -1096, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 12, maxSpawnDistance = 64, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier1", "reb_bwing_tier1", "reb_xwing_cadet_tier1", "reb_xwing_tier1", "reb_ywing_tier1", "reb_z95_tier1"}
		},
		{spawnName = "imperial_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = -3613, z = 1585, y = -2617, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 30, maxSpawnDistance = 60, totalSpawns = 7,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_patrol_1_00", "imperial_patrol_1_01", "imperial_patrol_1_02", "imperial_patrol_1_03", "imperial_patrol_1_04", "imperial_patrol_1_05", "imperial_patrol_1_06", "imperial_patrol_1_07", "imperial_patrol_1_08", "imperial_patrol_1_09", "imperial_patrol_1_10", "imperial_patrol_1_11", "imperial_patrol_1_12", "imperial_patrol_1_13", "imperial_patrol_1_14", "imperial_patrol_1_15", "imperial_patrol_1_16"},
			shipSpawns = {"imp_tie_fighter_tier1", "imp_tie_bomber_tier1", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{spawnName = "rebel_fighter_eight_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -3560, z = 1055, y = -3043, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_ywing_tier1", "reb_awing_tier1", "reb_bwing_tier1", "reb_xwing_tier1", "reb_z95_tier1"}
		},
		{spawnName = "binyare_nebula_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 3701, z = 500, y = 4875, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"binyare_nebula_spawner_00", "binyare_nebula_spawner_01", "binyare_nebula_spawner_02", "binyare_nebula_spawner_03", "binyare_nebula_spawner_04", "binyare_nebula_spawner_05", "binyare_nebula_spawner_06", "binyare_nebula_spawner_07", "binyare_nebula_spawner_08"},
			shipSpawns = {"binyare_raider_rookie"}
		},
		{spawnName = "rebel_fighter_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 1674, z = -3672, y = -3223, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_ywing_tier1", "reb_xwing_tier1", "reb_z95_tier1", "reb_bwing_tier1", "reb_awing_tier1"}
		},
		{spawnName = "corsec_security_1", spawnType = SHIP_SPAWN_SINGLE, x = 3779, z = -5178, y = -3888, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 32, minPatrol = 150, maxPatrol = 400, totalSpawns = 2,
			shipSpawns = {"corsec_fighter_tier1"}
		},
		{spawnName = "corsec_corellia_defender_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 2251, z = -4768, y = -3941, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"corsec_corellia_defender_spawner_00", "corsec_corellia_defender_spawner_01", "corsec_corellia_defender_spawner_02", "corsec_corellia_defender_spawner_03", "corsec_corellia_defender_spawner_04", "corsec_corellia_defender_spawner_05"},
			shipSpawns = {"corsec_lancer_tier1"}
		},
		{spawnName = "binyare_patrol_one", spawnType = SHIP_SPAWN_SINGLE, x = 3002, z = 4900, y = 6177, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"binyare_patrol_one_00", "binyare_patrol_one_01", "binyare_patrol_one_02", "binyare_patrol_one_03", "binyare_patrol_one_04", "binyare_patrol_one_05", "binyare_patrol_one_06"},
			shipSpawns = {"binyare_raider_rookie"}
		},
		{spawnName = "hiddendagger_fighter_one_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 2976, z = 5952, y = 2256, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_eliminator_tier1", "hidden_daggers_enforcer_tier1"}
		},
		{spawnName = "hiddendagger_fighter_six", spawnType = SHIP_SPAWN_SINGLE, x = 4158, z = 5402, y = 3373, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_executioner_tier1", "hidden_daggers_slayer_tier1"}
		},
		{spawnName = "hiddendagger_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 6181, z = 6021, y = 3423, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 40, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"hiddendagger_spawner_00", "hiddendagger_spawner_01", "hiddendagger_spawner_02", "hiddendagger_spawner_03", "hiddendagger_spawner_04", "hiddendagger_spawner_05", "hiddendagger_spawner_06", "hiddendagger_spawner_07", "hiddendagger_spawner_08"},
			shipSpawns = {"hidden_daggers_eliminator_tier1", "hidden_daggers_enforcer_tier1", "hidden_daggers_killer_tier1"}
		},
		{spawnName = "black_sun_asteroid_3", spawnType = SHIP_SPAWN_SINGLE, x = 2090, z = -482, y = -4257, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 64, minPatrol = 30, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "pirate_poi_asteroid", spawnType = SHIP_SPAWN_SINGLE, x = 839, z = 3015, y = 4011, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_aggressor_tier1", "blacksun_ace_s04_tier1"}
		},
		{spawnName = "rebel_xwing_rookie", spawnType = SHIP_SPAWN_SINGLE, x = -182, z = -89, y = -864, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 12, maxSpawnDistance = 64, minPatrol = 80, maxPatrol = 200, totalSpawns = 6,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_ywing_tier1", "reb_z95_tier1", "reb_awing_tier1", "reb_bwing_tier1"}
		},
		{spawnName = "imperial_fighter_four_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -3532, z = -1293, y = -1945, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 45, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_tie_bomberwithguard_tier1"}
		},
		{spawnName = "rebel_fighter_five_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -3558, z = -2340, y = -1909, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_tier1", "reb_z95_tier1", "reb_ywing_tier1", "reb_bwing_tier1", "reb_awing_tier1"}
		},
		{spawnName = "imperial_salvage_two", spawnType = SHIP_SPAWN_SINGLE, x = -5525, z = -2268, y = -1586, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 11, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_salvage_two_00", "imperial_salvage_two_01", "imperial_salvage_two_02", "imperial_salvage_two_03", "imperial_salvage_two_04", "imperial_salvage_two_05", "imperial_salvage_two_06", "imperial_salvage_two_07"},
			shipSpawns = {"imp_freightermedium_tier1"}
		},
		{spawnName = "rebel_corellia_deep_two_spawner", spawnType = SHIP_SPAWN_SINGLE, x = -6118, z = -3233, y = -2733, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 100, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_xwing_cadet_tier1", "reb_bwing_tier1", "reb_awing_tier1", "reb_z95_tier1", "reb_ywing_tier1"}
		},
		{spawnName = "imperial_fighter_one_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -3611, z = -3225, y = -2999, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 45, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_tie_standard_tier1"}
		},
		{spawnName = "rebel_ace_guard_2", spawnType = SHIP_SPAWN_SINGLE, x = -4760, z = -1716, y = -1676, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 12, maxSpawnDistance = 64, minPatrol = 100, maxPatrol = 400, totalSpawns = 6,
			shipSpawns = {"reb_awing_tier1", "reb_bwing_tier1", "reb_xwing_cadet_tier1", "reb_xwing_tier1", "reb_ywing_tier1", "reb_z95_tier1"}
		},
		{spawnName = "imperial_fighter_six_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -4810, z = -1763, y = -1779, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 45, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_tie_standard_tier1"}
		},
		{spawnName = "rebel_gunboat_patrol_01", spawnType = SHIP_SPAWN_SQUADRON, x = -6895, z = 5978, y = 4549, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_gunboat_patrol_01_00", "rebel_gunboat_patrol_01_01", "rebel_gunboat_patrol_01_02", "rebel_gunboat_patrol_01_03", "rebel_gunboat_patrol_01_04"},
			shipSpawns = {"squad_rebel_gunboat_tier1"}
		},
		{spawnName = "rebel_gunboat_patrol_02", spawnType = SHIP_SPAWN_SQUADRON, x = 880, z = 5802, y = 7013, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_gunboat_patrol_02_00", "rebel_gunboat_patrol_02_01", "rebel_gunboat_patrol_02_02", "rebel_gunboat_patrol_02_03", "rebel_gunboat_patrol_02_04"},
			shipSpawns = {"squad_rebel_gunboat_tier1"}
		},
		{spawnName = "rebel_gunboat_patrol_03", spawnType = SHIP_SPAWN_SQUADRON, x = -2863, z = 5802, y = -5738, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 25, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_gunboat_patrol_03_00", "rebel_gunboat_patrol_03_01", "rebel_gunboat_patrol_03_02", "rebel_gunboat_patrol_03_03", "rebel_gunboat_patrol_03_04", "rebel_gunboat_patrol_03_05"},
			shipSpawns = {"squad_rebel_gunboat_tier1"}
		},
	},
}

registerScreenPlay("SpaceCorelliaSpawner", true)
