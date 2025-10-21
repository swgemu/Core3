SpaceTatooineSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceTatooineSpawner",

	spaceZone = "space_tatooine",

	shipSpawns = {
		{spawnName = "hutt_guards_base_4", spawnType = SHIP_SPAWN_SINGLE, x = 1428, z = 7355, y = -5554, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 50, maxPatrol = 120, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1_tatooine", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1_tatooine"}
		},
		{spawnName = "iron_roid_pirate_01", spawnType = SHIP_SPAWN_SINGLE, x = 1752, z = -1247, y = 531, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 50, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "iron_roid_pirate_02", spawnType = SHIP_SPAWN_SINGLE, x = 2514, z = -1699, y = 307, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 50, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "iron_roid_pirate_03", spawnType = SHIP_SPAWN_SINGLE, x = 2406, z = -1187, y = 165, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 50, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "hutt_hideout", spawnType = SHIP_SPAWN_SINGLE, x = -2875, z = -2740, y = -2927, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 50, maxPatrol = 200, totalSpawns = 4,
			shipSpawns = {"hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_starbomber", "hutt_fighter_s01_tier1_tatooine", "hutt_fighter_s01_tier1_tatooine", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1_tatooine"}
		},
		{spawnName = "freighter_victim", spawnType = SHIP_SPAWN_SINGLE, x = -2010, z = 1612, y = -2227, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 50, maxPatrol = 200, totalSpawns = 1,
			shipSpawns = {"freighterlight_tier1"}
		},
		{spawnName = "imp_base_defense_02", spawnType = SHIP_SPAWN_SINGLE, x = -3665, z = 618, y = 2970, patrolType = SHIP_AI_GUARD_PATROL, minRespawn = 40, maxRespawn = 90, minSpawnDistance = 4, maxSpawnDistance = 12, minPatrol = 50, maxPatrol = 200, totalSpawns = 6,
			shipSpawns = {"imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{spawnName = "blacksun_threat_2", spawnType = SHIP_SPAWN_SINGLE, x = 1098, z = 767, y = -2978, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 6, maxSpawnDistance = 14, minPatrol = 50, maxPatrol = 200, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_fighter_s02_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "reb_recon_threat_2", spawnType = SHIP_SPAWN_SINGLE, x = -2203, z = -2389, y = 518, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 4, maxSpawnDistance = 16, minPatrol = 50, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1"}
		},
		{spawnName = "blacksun_threat_3", spawnType = SHIP_SPAWN_SINGLE, x = 2816, z = 336, y = -1908, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 9, maxSpawnDistance = 20, minPatrol = 50, maxPatrol = 200, totalSpawns = 8,
			shipSpawns = {"blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2_tatooine", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s01_tier2_tatooine", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "bestine_pirates", spawnType = SHIP_SPAWN_SINGLE, x = 896, z = 1268, y = -2850, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "imperial_base_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = -6388, z = 4911, y = -1055, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 40, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 200, totalSpawns = 6,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_aggressor_tier1", "imp_tie_advanced_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{spawnName = "anchorhead_supply_threat_1", spawnType = SHIP_SPAWN_SINGLE, x = -982, z = -104, y = -1281, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 12, maxSpawnDistance = 32, minPatrol = 100, maxPatrol = 200, totalSpawns = 6,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1"}
		},
		{spawnName = "marcus_the_mad", spawnType = SHIP_SPAWN_SINGLE, x = 230, z = 1165, y = -2275, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 8, maxSpawnDistance = 32, minPatrol = 100, maxPatrol = 200, totalSpawns = 1,
			shipSpawns = {"marcus_the_mad"}
		},
		{spawnName = "anchorhead_tie_rally_alpha", spawnType = SHIP_SPAWN_SINGLE, x = 1948, z = -366, y = 2316, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 50, maxPatrol = 200, totalSpawns = 4,
			shipSpawns = {"imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_bomber_tier1", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{spawnName = "anchorhead_supply_threat_2", spawnType = SHIP_SPAWN_SINGLE, x = -3194, z = -425, y = -1769, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 4, maxSpawnDistance = 48, minPatrol = 50, maxPatrol = 200, totalSpawns = 6,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_aggressor_tier1", "imp_tie_advanced_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{spawnName = "blacksun_leader_guards", spawnType = SHIP_SPAWN_SINGLE, x = -2161, z = -1000, y = -5306, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 50, maxPatrol = 200, totalSpawns = 8,
			shipSpawns = {"blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2_tatooine", "blacksun_bomber_s01_tier2_tatooine", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s01_tier2_tatooine", "blacksun_fighter_s01_tier2_tatooine", "blacksun_marauder_tier1", "blacksun_starkiller_leader", "blacksun_vehement_tier1"}
		},
		{spawnName = "blacksun_pirates", spawnType = SHIP_SPAWN_SINGLE, x = -2024, z = 1619, y = -2219, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 50, maxPatrol = 200, totalSpawns = 8,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_fighter_s03_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "bestine_security_threat_1", spawnType = SHIP_SPAWN_SINGLE, x = -3461, z = 775, y = -1259, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 12, maxSpawnDistance = 64, minPatrol = 50, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "bestine_escort_threat_2", spawnType = SHIP_SPAWN_SINGLE, x = -1033, z = 2231, y = -423, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 14, maxSpawnDistance = 64, minPatrol = 50, maxPatrol = 200, totalSpawns = 4,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "bestine_security_threat_3", spawnType = SHIP_SPAWN_SINGLE, x = 2235, z = 1017, y = -388, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 16, maxSpawnDistance = 64, minPatrol = 50, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "bestine_escort_threat_1", spawnType = SHIP_SPAWN_SINGLE, x = 2525, z = 933, y = 851, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 24, maxSpawnDistance = 64, minPatrol = 50, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "bestine_pirate_leader_guards", spawnType = SHIP_SPAWN_SINGLE, x = -1599, z = -3076, y = 3432, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 12, maxSpawnDistance = 68, minPatrol = 50, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "bestine_escort_threat_3", spawnType = SHIP_SPAWN_SINGLE, x = -3855, z = 1057, y = 523, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 14, maxSpawnDistance = 68, minPatrol = 50, maxPatrol = 200, totalSpawns = 4,
			shipSpawns = {"bestine_pirate_tier1", "bestine_pirate_tier1", "bestine_pirate_tier1", "bestine_pirate_tier1", "bestine_pirate_leader_tier1"}
		},
		{spawnName = "bestine_security_threat_2", spawnType = SHIP_SPAWN_SINGLE, x = -519, z = 1650, y = -1372, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 6, maxSpawnDistance = 68, minPatrol = 50, maxPatrol = 200, totalSpawns = 5,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "mining_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = -6796, z = 5934, y = 2329, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 30, maxSpawnDistance = 80, minPatrol = 100, maxPatrol = 200, totalSpawns = 4,
			shipSpawns = {"mining_guard_ship", "mining_guard_ship_tatooine", "mining_guard_ship_tatooine", "mining_guard_ship"}
		},
		{spawnName = "smuggler_base_defense_02", spawnType = SHIP_SPAWN_SINGLE, x = 3147, z = 234, y = 3608, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 32, maxSpawnDistance = 96, minPatrol = 100, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "blacksun_pirates_and_leader", spawnType = SHIP_SPAWN_SINGLE, x = -2155, z = -1000, y = -5300, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 240, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 80, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"blacksun_ace_s04_tier2", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2_tatooine", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s01_tier2_tatooine", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "bestine_vs_valarians_1", spawnType = SHIP_SPAWN_SINGLE, x = 7066, z = 6890, y = 7230, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"valarian_bomber_tier2"}
		},
		{spawnName = "bestine_vs_valarians_2", spawnType = SHIP_SPAWN_SINGLE, x = 6982, z = 6813, y = 7266, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"bestine_pirate_tier2"}
		},
		{spawnName = "blacksun_guards_3", spawnType = SHIP_SPAWN_SINGLE, x = 4197, z = 417, y = 4421, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2_tatooine", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2"}
		},
		{spawnName = "bestine_pirate_guards_2", spawnType = SHIP_SPAWN_SINGLE, x = 7286, z = 5697, y = 5923, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "bestine_pirate_guards_6", spawnType = SHIP_SPAWN_SINGLE, x = 171, z = 4068, y = 2808, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "bestine_pirates_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = 5713, z = 5701, y = 7337, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"bestine_pirate_tier1", "bestine_pirate_tier1", "bestine_pirate_tier1", "bestine_pirate_leader_tier2"}
		},
		{spawnName = "bestine_pirates_guards_5", spawnType = SHIP_SPAWN_SINGLE, x = 4188, z = 6563, y = 4833, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "blacksun_n_stuff_1", spawnType = SHIP_SPAWN_SINGLE, x = 5588, z = 1002, y = 6147, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 8,
			shipSpawns = {"blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "valarian_spine_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = -4538, z = -4668, y = -5590, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "valarian_spine_guard_2", spawnType = SHIP_SPAWN_SINGLE, x = -3741, z = -824, y = -3582, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "valarian_spine_guard_4", spawnType = SHIP_SPAWN_SINGLE, x = -1877, z = 5565, y = -634, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "valarian_static_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = -6251, z = -6734, y = -7054, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "poi_quest_garett", spawnType = SHIP_SPAWN_SINGLE, x = -249, z = -3495, y = 1800, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 10, maxRespawn = 20, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"poi_garett_convo_ship_tier2"}
		},
		{spawnName = "poi_quest_mining", spawnType = SHIP_SPAWN_SINGLE, x = -5492, z = 35, y = 6255, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 10, maxRespawn = 20, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"poi_mining_convo_ship_tier2"}
		},
		{spawnName = "poi_quest_police", spawnType = SHIP_SPAWN_SINGLE, x = 3620, z = -5735, y = 3802, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 10, maxRespawn = 20, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"poi_eisley_captain_convo_ship_tier2"}
		},
		{spawnName = "poi_general2_spice_1", spawnType = SHIP_SPAWN_SINGLE, x = 783, z = 18, y = 3268, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 10, maxRespawn = 20, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"spice_pirate_fighter_tier1"}
		},
		{spawnName = "poi_general2_spice_2", spawnType = SHIP_SPAWN_SINGLE, x = 366, z = 150, y = 2073, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 10, maxRespawn = 20, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"spice_pirate_spy_tier1"}
		},
		{spawnName = "poi_privateer_inspect_blacksun", spawnType = SHIP_SPAWN_SINGLE, x = -4915, z = 3681, y = 456, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"blacksun_ace_s04_tier2", "blacksun_aggressor_tier2", "blacksun_bomber_ace_s04_tier2", "poi_blacksun_aggressor_tier2"}
		},
		{spawnName = "poi_privateer_inspect_valarian", spawnType = SHIP_SPAWN_SINGLE, x = -6087, z = -4435, y = -6333, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"poi_valarian_fighter_tier1", "valarian_fighter_tier1", "valarian_fighter_tier1", "valarian_fighter_tier1"}
		},
		{spawnName = "hutts_vs_valarian_2", spawnType = SHIP_SPAWN_SINGLE, x = -3975, z = 6686, y = 1033, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"hutt_bomber_s01_tier1"}
		},
		{spawnName = "hutts_vs_valarians_1", spawnType = SHIP_SPAWN_SINGLE, x = -3036, z = 3431, y = -813, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 4,
			shipSpawns = {"hutt_bomber_s01_tier1"}
		},
		{spawnName = "valarian_station_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = -1184, z = 6619, y = 1069, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 150, maxPatrol = 300, totalSpawns = 5,
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "valarian_station_guard_2", spawnType = SHIP_SPAWN_SINGLE, x = -770, z = 6077, y = -5, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 150, maxPatrol = 300, totalSpawns = 5,
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine", "valarian_gunship_tier1_tatooine", "valarian_gunship_tier1"}
		},
		{spawnName = "smuggler_base_defense_03", spawnType = SHIP_SPAWN_SINGLE, x = 3016, z = 167, y = 3229, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 16, maxSpawnDistance = 32, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "hutt_guards_base_1", spawnType = SHIP_SPAWN_SINGLE, x = 2692, z = 5872, y = -7252, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1_tatooine", "hutt_fighter_s01_tier1_tatooine", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1"}
		},
		{spawnName = "hutt_guards_base_2", spawnType = SHIP_SPAWN_SINGLE, x = -1258, z = 5837, y = -7297, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1_tatooine", "hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1_tatooine", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1"}
		},
		{spawnName = "hutt_guards_base_3", spawnType = SHIP_SPAWN_SINGLE, x = -112, z = 6021, y = -4741, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1"}
		},
		{spawnName = "hutt_guards_base_5", spawnType = SHIP_SPAWN_SINGLE, x = 1345, z = 3702, y = -5265, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1"}
		},
		{spawnName = "mining_guard_ships1", spawnType = SHIP_SPAWN_SINGLE, x = -6834, z = 625, y = 6305, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"mining_guard_ship"}
		},
		{spawnName = "mining_guard_ships2", spawnType = SHIP_SPAWN_SINGLE, x = -4732, z = -136, y = 5249, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"mining_guard_ship", "mining_guard_ship_tatooine", "mining_guard_ship_tatooine"}
		},
		{spawnName = "mining_guards3", spawnType = SHIP_SPAWN_SINGLE, x = -5377, z = 134, y = 4112, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"mining_guard_ship"}
		},
		{spawnName = "smuggler_asteroid_patrol_01", spawnType = SHIP_SPAWN_SINGLE, x = 3508, z = 913, y = 3105, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 2, maxSpawnDistance = 8, minPatrol = 100, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "imp_base_patrol_01", spawnType = SHIP_SPAWN_SINGLE, x = -3793, z = 415, y = 3156, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 40, maxRespawn = 90, minSpawnDistance = 2, maxSpawnDistance = 8, minPatrol = 50, maxPatrol = 320, totalSpawns = 6,
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{spawnName = "smuggler_mercenary_guard", spawnType = SHIP_SPAWN_SINGLE, x = -2613, z = 302, y = -2682, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 350, totalSpawns = 3,
			shipSpawns = {"mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_tyela_leader", "mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_guard_tier1"}
		},
		{spawnName = "valarian_mining_guard", spawnType = SHIP_SPAWN_SINGLE, x = -6523, z = -6375, y = -6388, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 350, totalSpawns = 4,
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "dest_rebel_base_smugglers", spawnType = SHIP_SPAWN_SINGLE, x = -1582, z = 2176, y = -3265, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 350, totalSpawns = 3,
			shipSpawns = {"reb_z95_tier1", "reb_ywing_tier1", "reb_xwing_tier1"}
		},
		{spawnName = "valarian_miners", spawnType = SHIP_SPAWN_SINGLE, x = -6619, z = -6330, y = -6458, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 150, minPatrol = 100, maxPatrol = 350, totalSpawns = 2,
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "tatooine_orbit_guard", spawnType = SHIP_SPAWN_SINGLE, x = 129, z = -1544, y = -3052, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 150, maxPatrol = 400, totalSpawns = 4,
			shipSpawns = {"mos_eisley_police"}
		},
		{spawnName = "rebel_recon_threat_1", spawnType = SHIP_SPAWN_SQUADRON, x = 1038, z = -1972, y = 227, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 200, maxPatrol = 400, totalSpawns = 1,
			shipSpawns = {"squad_tie_standard_tier1"}
		},
		{spawnName = "stn_dantooine_lordmistress_01", spawnType = SHIP_SPAWN_SINGLE, x = 3200, z = 4320, y = -4322, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 45, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 50, maxPatrol = 400, totalSpawns = 1,
			shipSpawns = {"lords_mistress_tier3"}
		},
		{spawnName = "valarian_vs_hutts_2", spawnType = SHIP_SPAWN_SINGLE, x = -3985, z = 6949, y = 1071, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, minPatrol = 200, maxPatrol = 400, totalSpawns = 4,
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "valarian_vs_hutts", spawnType = SHIP_SPAWN_SINGLE, x = -2113, z = 4695, y = 980, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 20, maxSpawnDistance = 50, minPatrol = 200, maxPatrol = 400, totalSpawns = 4,
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "bestine_pirates_and_leader", spawnType = SHIP_SPAWN_SINGLE, x = -1586, z = -3178, y = 3478, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 240, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 450, totalSpawns = 1,
			shipSpawns = {"bestine_pirate_leader_tier1"}
		},
		{spawnName = "rebel_base_guard_1", spawnType = SHIP_SPAWN_SQUADRON, x = 3440, z = -414, y = -2628, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 250, maxPatrol = 500, totalSpawns = 1,
			shipSpawns = {"squad_xwing_standard_tier1"}
		},
		{spawnName = "mining_operation_1", spawnType = SHIP_SPAWN_SINGLE, x = -6777, z = 5816, y = 2312, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 30, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 600, totalSpawns = 1,
			shipSpawns = {"mining_guard_ship_tatooine", "mining_guard_ship_tatooine", "mining_guard_ship", "mining_guard_ship"}
		},
		{spawnName = "bestine_pirates_planetoid_orbiters", spawnType = SHIP_SPAWN_SINGLE, x = 1873, z = -1771, y = 212, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"bestine_pirates_planetoid_orbiters_00", "bestine_pirates_planetoid_orbiters_01", "bestine_pirates_planetoid_orbiters_02", "bestine_pirates_planetoid_orbiters_03", "bestine_pirates_planetoid_orbiters_04", "bestine_pirates_planetoid_orbiters_05", "bestine_pirates_planetoid_orbiters_06", "bestine_pirates_planetoid_orbiters_07"},
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "valarian_mining_route", spawnType = SHIP_SPAWN_SINGLE, x = -6685, z = -6353, y = -6684, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 120, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"valarian_mining_route_00", "valarian_mining_route_01", "valarian_mining_route_02", "valarian_mining_route_03", "valarian_mining_route_04", "valarian_mining_route_05"},
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1", "valarian_starship_ace", "valarian_bomber_tier1", "valarian_bomber_tier1", "valarian_bomber_tier1", "valarian_bomber_tier1", "valarian_bomber_tier1_tatooine", "valarian_bomber_tier1_tatooine", "valarian_bomber_tier1_tatooine", "valarian_bomber_tier1_tatooine", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "hutt_attack_route_2", spawnType = SHIP_SPAWN_SQUADRON, x = -2913, z = -2853, y = -2980, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_attack_route_2_00", "hutt_attack_route_2_01", "hutt_attack_route_2_02", "hutt_attack_route_2_03", "hutt_attack_route_2_04", "hutt_attack_route_2_05", "hutt_attack_route_2_06", "hutt_attack_route_2_07", "hutt_attack_route_2_08", "hutt_attack_route_2_09"},
			shipSpawns = {"squad_hutt_skiffs_tier1"}
		},
		{spawnName = "hutt_attack_route_1", spawnType = SHIP_SPAWN_SQUADRON, x = -2988, z = -2789, y = -2991, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_attack_route_1_00", "hutt_attack_route_1_01", "hutt_attack_route_1_02", "hutt_attack_route_1_03", "hutt_attack_route_1_04", "hutt_attack_route_1_05"},
			shipSpawns = {"squad_hutt_skiffs_tier1"}
		},
		{spawnName = "valarian_mining_route_guard", spawnType = SHIP_SPAWN_SQUADRON, x = -6738, z = -6346, y = -6707, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"valarian_mining_route_guard_00", "valarian_mining_route_guard_01", "valarian_mining_route_guard_02", "valarian_mining_route_guard_03", "valarian_mining_route_guard_04", "valarian_mining_route_guard_05", "valarian_mining_route_guard_06"},
			shipSpawns = {"squad_valarian_fighter_tier1"}
		},
		{spawnName = "anchorhead_merchants", spawnType = SHIP_SPAWN_SINGLE, x = 3852, z = -3733, y = -866, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 4, maxSpawnDistance = 12, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"anchorhead_merchants_00", "anchorhead_merchants_01", "anchorhead_merchants_02", "anchorhead_merchants_03", "anchorhead_merchants_04", "anchorhead_merchants_05", "anchorhead_merchants_06", "anchorhead_merchants_07"},
			shipSpawns = {"civspeeder", "civtransport", "freighterheavy_tier1", "freighterheavy_tier3_story", "freighterlight_tier1", "freighterlight_tier1", "freighterlight_tier1", "freightermedium_tier1", "freightermedium_tier1", "freighterheavy_tier3"}
		},
		{spawnName = "imp_base_defense_03", spawnType = SHIP_SPAWN_SQUADRON, x = -3826, z = 380, y = 2983, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 40, maxRespawn = 90, minSpawnDistance = 4, maxSpawnDistance = 12, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imp_base_defense_03_00", "imp_base_defense_03_01", "imp_base_defense_03_02", "imp_base_defense_03_03", "imp_base_defense_03_04", "imp_base_defense_03_05", "imp_base_defense_03_06"},
			shipSpawns = {"squad_tie_standard_tier1"}
		},
		{spawnName = "dest_rebel_base_smugglers_1", spawnType = SHIP_SPAWN_SINGLE, x = -1402, z = 2401, y = -3682, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 30, maxSpawnDistance = 120, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"dest_rebel_base_smugglers_1_00", "dest_rebel_base_smugglers_1_01", "dest_rebel_base_smugglers_1_02", "dest_rebel_base_smugglers_1_03", "dest_rebel_base_smugglers_1_04", "dest_rebel_base_smugglers_1_05", "dest_rebel_base_smugglers_1_06", "dest_rebel_base_smugglers_1_07", "dest_rebel_base_smugglers_1_08", "dest_rebel_base_smugglers_1_09"},
			shipSpawns = {"smuggler_freighterheavy_tier1", "smuggler_freighterlight_tier1", "smuggler_freightermedium_tier1"}
		},
		{spawnName = "hutt_gunships_attack_1", spawnType = SHIP_SPAWN_SINGLE, x = 766, z = 5685, y = -4932, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_gunships_attack_1_00", "hutt_gunships_attack_1_01", "hutt_gunships_attack_1_02", "hutt_gunships_attack_1_03", "hutt_gunships_attack_1_04", "hutt_gunships_attack_1_05", "hutt_gunships_attack_1_06", "hutt_gunships_attack_1_07", "hutt_gunships_attack_1_08", "hutt_gunships_attack_1_09"},
			shipSpawns = {"hutt_yt1300_tier1"}
		},
		{spawnName = "hutt_gunship_attack_2", spawnType = SHIP_SPAWN_SINGLE, x = 1262, z = 6392, y = -5250, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_gunship_attack_2_00", "hutt_gunship_attack_2_01", "hutt_gunship_attack_2_02", "hutt_gunship_attack_2_03", "hutt_gunship_attack_2_04", "hutt_gunship_attack_2_05", "hutt_gunship_attack_2_06", "hutt_gunship_attack_2_07", "hutt_gunship_attack_2_08", "hutt_gunship_attack_2_09", "hutt_gunship_attack_2_10", "hutt_gunship_attack_2_11", "hutt_gunship_attack_2_12", "hutt_gunship_attack_2_13"},
			shipSpawns = {"hutt_yt1300_tier1"}
		},
		{spawnName = "blacksun_guard_1", spawnType = SHIP_SPAWN_SINGLE, x = 7152, z = 937, y = 6636, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"blacksun_guard_1_00", "blacksun_guard_1_01", "blacksun_guard_1_02", "blacksun_guard_1_03", "blacksun_guard_1_04", "blacksun_guard_1_05", "blacksun_guard_1_06", "blacksun_guard_1_07", "blacksun_guard_1_08", "blacksun_guard_1_09", "blacksun_guard_1_10"},
			shipSpawns = {"blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2_tatooine", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s01_tier2_tatooine", "blacksun_marauder_tier1"}
		},
		{spawnName = "valarian_to_spine_1", spawnType = SHIP_SPAWN_SINGLE, x = -7093, z = -6497, y = -6272, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"valarian_to_spine_1_00", "valarian_to_spine_1_01", "valarian_to_spine_1_02", "valarian_to_spine_1_03", "valarian_to_spine_1_04", "valarian_to_spine_1_05", "valarian_to_spine_1_06", "valarian_to_spine_1_07", "valarian_to_spine_1_08"},
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "bestine_pirate_base_1", spawnType = SHIP_SPAWN_SINGLE, x = 6052, z = 5659, y = 6541, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"bestine_pirate_base_1_00", "bestine_pirate_base_1_01", "bestine_pirate_base_1_02", "bestine_pirate_base_1_03", "bestine_pirate_base_1_04", "bestine_pirate_base_1_05", "bestine_pirate_base_1_06", "bestine_pirate_base_1_07"},
			shipSpawns = {"bestine_pirate_tier1"}
		},
		{spawnName = "station_to_mining_1", spawnType = SHIP_SPAWN_SINGLE, x = 1635, z = -5599, y = 2580, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 120, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"station_to_mining_1_00", "station_to_mining_1_01", "station_to_mining_1_02", "station_to_mining_1_03", "station_to_mining_1_04"},
			shipSpawns = {"freighterheavy_mining", "freighterlight_mining", "freightermedium_mining"}
		},
		{spawnName = "hutt_squad_1", spawnType = SHIP_SPAWN_SQUADRON, x = 1196, z = 5760, y = -4017, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 1200, maxRespawn = 3600, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_squad_1_00", "hutt_squad_1_01", "hutt_squad_1_02", "hutt_squad_1_03", "hutt_squad_1_04", "hutt_squad_1_05"},
			shipSpawns = {"squad_hutt_tatooine_1"}
		},
		{spawnName = "tatooine_station_passenger_1", spawnType = SHIP_SPAWN_SINGLE, x = 1935, z = -5859, y = 1605, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"tatooine_station_passenger_1_00", "tatooine_station_passenger_1_01", "tatooine_station_passenger_1_02", "tatooine_station_passenger_1_03"},
			shipSpawns = {"civilian_science_transport_tier1"}
		},
		{spawnName = "imperial_pirate_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = -3194, z = 1005, y = -3259, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 120, maxRespawn = 90, minSpawnDistance = 30, maxSpawnDistance = 240, totalSpawns = 9,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_pirate_patrol_1_00", "imperial_pirate_patrol_1_01", "imperial_pirate_patrol_1_02", "imperial_pirate_patrol_1_03", "imperial_pirate_patrol_1_04", "imperial_pirate_patrol_1_05", "imperial_pirate_patrol_1_06", "imperial_pirate_patrol_1_07", "imperial_pirate_patrol_1_08", "imperial_pirate_patrol_1_09", "imperial_pirate_patrol_1_10", "imperial_pirate_patrol_1_11", "imperial_pirate_patrol_1_12", "imperial_pirate_patrol_1_13", "imperial_pirate_patrol_1_14", "imperial_pirate_patrol_1_15", "imperial_pirate_patrol_1_16", "imperial_pirate_patrol_1_17", "imperial_pirate_patrol_1_18", "imperial_pirate_patrol_1_19", "imperial_pirate_patrol_1_20", "imperial_pirate_patrol_1_21"},
			shipSpawns = {"imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1", "imperial_cpt_starfire"}
		},
		{spawnName = "rebel_convoy_01", spawnType = SHIP_SPAWN_SINGLE, x = 3311, z = -194, y = -2736, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 2, maxSpawnDistance = 3, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_convoy_01_00", "rebel_convoy_01_01", "rebel_convoy_01_02", "rebel_convoy_01_03", "rebel_convoy_01_04", "rebel_convoy_01_05", "rebel_convoy_01_06", "rebel_convoy_01_07", "rebel_convoy_01_08", "rebel_convoy_01_09", "rebel_convoy_01_10", "rebel_convoy_01_11"},
			shipSpawns = {"freighterlight_rebel", "reb_xwing_tier1", "reb_ywing_tier1", "reb_xwing_tier1_tatooine", "reb_ywing_tier1_tatooine", "reb_xwing_tier1", "reb_ywing_tier1"}
		},
		{spawnName = "valarian_spine_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = -2945, z = -6985, y = -6764, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 15,
			patrolsToAssign = 5, fixedPatrolPoints = {"valarian_spine_patrol_1_00", "valarian_spine_patrol_1_01", "valarian_spine_patrol_1_02", "valarian_spine_patrol_1_03", "valarian_spine_patrol_1_04", "valarian_spine_patrol_1_05", "valarian_spine_patrol_1_06", "valarian_spine_patrol_1_07", "valarian_spine_patrol_1_08", "valarian_spine_patrol_1_09", "valarian_spine_patrol_1_10"},
			shipSpawns = {"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{spawnName = "valarian_hutt_attack_1", spawnType = SHIP_SPAWN_SINGLE, x = -2004, z = 6630, y = 247, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 120, maxRespawn = 180, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"valarian_hutt_attack_1_00", "valarian_hutt_attack_1_01", "valarian_hutt_attack_1_02", "valarian_hutt_attack_1_03", "valarian_hutt_attack_1_04", "valarian_hutt_attack_1_05", "valarian_hutt_attack_1_06", "valarian_hutt_attack_1_07", "valarian_hutt_attack_1_08", "valarian_hutt_attack_1_09", "valarian_hutt_attack_1_10"},
			shipSpawns = {"valarian_gunship_tier1", "valarian_gunship_tier1_tatooine"}
		},
		{spawnName = "station_to_smugglers", spawnType = SHIP_SPAWN_SINGLE, x = 3939, z = -5611, y = 3421, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 120, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"station_to_smugglers_00", "station_to_smugglers_01", "station_to_smugglers_02"},
			shipSpawns = {"smuggler_freighterlight_tier3", "smuggler_freightermedium_tier3"}
		},
		{spawnName = "tatooine_station_freighter_route2", spawnType = SHIP_SPAWN_SINGLE, x = 2157, z = -2993, y = 5457, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"tatooine_station_freighter_route2_00", "tatooine_station_freighter_route2_01"},
			shipSpawns = {"freighterheavy_tier1", "freighterlight_tier1", "freightermedium_tier1"}
		},
		{spawnName = "bestine_imperial_commerce_support", spawnType = SHIP_SPAWN_SINGLE, x = -2062, z = 830, y = 1065, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 2, maxSpawnDistance = 32, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"bestine_imperial_commerce_support_00", "bestine_imperial_commerce_support_01", "bestine_imperial_commerce_support_02", "bestine_imperial_commerce_support_03", "bestine_imperial_commerce_support_04", "bestine_imperial_commerce_support_05", "bestine_imperial_commerce_support_06", "bestine_imperial_commerce_support_07", "bestine_imperial_commerce_support_08", "bestine_imperial_commerce_support_09", "bestine_imperial_commerce_support_10", "bestine_imperial_commerce_support_11", "bestine_imperial_commerce_support_12", "bestine_imperial_commerce_support_13", "bestine_imperial_commerce_support_14", "bestine_imperial_commerce_support_15", "bestine_imperial_commerce_support_16", "bestine_imperial_commerce_support_17", "bestine_imperial_commerce_support_18", "bestine_imperial_commerce_support_19", "bestine_imperial_commerce_support_20", "bestine_imperial_commerce_support_21", "bestine_imperial_commerce_support_22", "bestine_imperial_commerce_support_23", "bestine_imperial_commerce_support_24", "bestine_imperial_commerce_support_25", "bestine_imperial_commerce_support_26", "bestine_imperial_commerce_support_27", "bestine_imperial_commerce_support_28", "bestine_imperial_commerce_support_29", "bestine_imperial_commerce_support_30"},
			shipSpawns = {"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{spawnName = "pirate_attack_route", spawnType = SHIP_SPAWN_SINGLE, x = -562, z = 2682, y = -445, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 5, maxSpawnDistance = 32, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"pirate_attack_route_00", "pirate_attack_route_01", "pirate_attack_route_02", "pirate_attack_route_03", "pirate_attack_route_04", "pirate_attack_route_05", "pirate_attack_route_06", "pirate_attack_route_07", "pirate_attack_route_08"},
			shipSpawns = {"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_ace_s04_tier1", "blacksun_bomber_s01_tier1", "blacksun_dark_eclipse_tier1", "blacksun_fighter_s01_tier1", "blacksun_gunship_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{spawnName = "bestine_commerce_02", spawnType = SHIP_SPAWN_SINGLE, x = 2289, z = 1016, y = -2981, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 24, maxSpawnDistance = 48, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"bestine_commerce_02_00", "bestine_commerce_02_01", "bestine_commerce_02_02", "bestine_commerce_02_03", "bestine_commerce_02_04", "bestine_commerce_02_05", "bestine_commerce_02_06", "bestine_commerce_02_07", "bestine_commerce_02_08", "bestine_commerce_02_09", "bestine_commerce_02_10", "bestine_commerce_02_11", "bestine_commerce_02_12", "bestine_commerce_02_13", "bestine_commerce_02_14", "bestine_commerce_02_15", "bestine_commerce_02_16", "bestine_commerce_02_17", "bestine_commerce_02_18", "bestine_commerce_02_19", "bestine_commerce_02_20", "bestine_commerce_02_21", "bestine_commerce_02_22", "bestine_commerce_02_23"},
			shipSpawns = {"freighterheavy_tier3_story", "freighterheavy_tier3", "freighterheavy_tier1", "freighterlight_tier1", "freighterlight_tier1", "freightermedium_tier1", "freightermedium_tier1"}
		},
		{spawnName = "smuggler_base_defense_01", spawnType = SHIP_SPAWN_SINGLE, x = 3053, z = -45, y = 3653, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 4, maxSpawnDistance = 5, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"smuggler_base_defense_01_00", "smuggler_base_defense_01_01", "smuggler_base_defense_01_02", "smuggler_base_defense_01_03", "smuggler_base_defense_01_04", "smuggler_base_defense_01_05", "smuggler_base_defense_01_06", "smuggler_base_defense_01_07", "smuggler_base_defense_01_08"},
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "hutt_base_asteroid_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = 1558, z = 4845, y = -5452, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_base_asteroid_patrol_1_00", "hutt_base_asteroid_patrol_1_01", "hutt_base_asteroid_patrol_1_02", "hutt_base_asteroid_patrol_1_03", "hutt_base_asteroid_patrol_1_04", "hutt_base_asteroid_patrol_1_05"},
			shipSpawns = {"hutt_bomber_s01_tier1_tatooine", "hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1_tatooine", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "mos_eisley_police_1", spawnType = SHIP_SPAWN_SINGLE, x = 271, z = -5507, y = -695, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"mos_eisley_police_1_00", "mos_eisley_police_1_01", "mos_eisley_police_1_02", "mos_eisley_police_1_03", "mos_eisley_police_1_04", "mos_eisley_police_1_05", "mos_eisley_police_1_06"},
			shipSpawns = {"mos_eisley_police"}
		},
		{spawnName = "merchants_to_station", spawnType = SHIP_SPAWN_SINGLE, x = 3321, z = -3327, y = -406, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 120, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"merchants_to_station_00", "merchants_to_station_01", "merchants_to_station_02"},
			shipSpawns = {"freighterlight_tier1", "mercenary_courier_tier1", "mercenary_guard_tier1"}
		},
		{spawnName = "miners_to_station_1", spawnType = SHIP_SPAWN_SINGLE, x = -5508, z = -327, y = 6214, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"miners_to_station_1_00", "miners_to_station_1_01", "miners_to_station_1_02", "miners_to_station_1_03", "miners_to_station_1_04", "miners_to_station_1_05", "miners_to_station_1_06"},
			shipSpawns = {"freighterheavy_mining", "freighterlight_mining", "freightermedium_mining", "freighterheavy_mining"}
		},
		{spawnName = "tatooine_station_freighter_route_1", spawnType = SHIP_SPAWN_SINGLE, x = 2505, z = -1792, y = 7529, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"tatooine_station_freighter_route_1_00", "tatooine_station_freighter_route_1_01", "tatooine_station_freighter_route_1_02"},
			shipSpawns = {"freighterheavy_tier1", "freighterlight_tier1", "freightermedium_tier1"}
		},
		{spawnName = "po_mcannon_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = -1135, z = -6847, y = -5191, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 600, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"po_mcannon_spawner_00", "po_mcannon_spawner_01", "po_mcannon_spawner_02", "po_mcannon_spawner_03", "po_mcannon_spawner_04"},
			shipSpawns = {"squad_po_mcannon_tier2"}
		},
		{spawnName = "vsin_starbomber_spawner", spawnType = SHIP_SPAWN_SQUADRON, x = 6476, z = 3999, y = 2460, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 600, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"vsin_starbomber_spawner_00", "vsin_starbomber_spawner_01", "vsin_starbomber_spawner_02", "vsin_starbomber_spawner_03", "vsin_starbomber_spawner_04"},
			shipSpawns = {"squad_vsin_starbomber_tier2"}
		},
		{spawnName = "imperial_squad_1", spawnType = SHIP_SPAWN_SQUADRON, x = -4099, z = -602, y = 4240, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 40, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_squad_1_00", "imperial_squad_1_01", "imperial_squad_1_02", "imperial_squad_1_03", "imperial_squad_1_04", "imperial_squad_1_05"},
			shipSpawns = {"squad_imperial_tatooine_1"}
		},
		{spawnName = "imperial_squad_3", spawnType = SHIP_SPAWN_SQUADRON, x = -3856, z = -2920, y = -3319, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 40, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_squad_3_00", "imperial_squad_3_01", "imperial_squad_3_02", "imperial_squad_3_03", "imperial_squad_3_04", "imperial_squad_3_05"},
			shipSpawns = {"squad_imperial_tatooine_3"}
		},
		{spawnName = "imperial_squad_4", spawnType = SHIP_SPAWN_SQUADRON, x = 514, z = 1767, y = 1878, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 40, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_squad_4_00", "imperial_squad_4_01", "imperial_squad_4_02", "imperial_squad_4_03", "imperial_squad_4_04", "imperial_squad_4_05"},
			shipSpawns = {"squad_imperial_tatooine_4"}
		},
		{spawnName = "imperial_squad_2", spawnType = SHIP_SPAWN_SQUADRON, x = 4526, z = 1609, y = -225, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 40, maxRespawn = 90, minSpawnDistance = 10, maxSpawnDistance = 50, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_squad_2_00", "imperial_squad_2_01", "imperial_squad_2_02", "imperial_squad_2_03", "imperial_squad_2_04", "imperial_squad_2_05", "imperial_squad_2_06"},
			shipSpawns = {"squad_imperial_tatooine_2"}
		},
		{spawnName = "bestine_commerce_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 2203, z = 976, y = -2239, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 12, maxSpawnDistance = 64, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"bestine_commerce_spawner_00", "bestine_commerce_spawner_01", "bestine_commerce_spawner_02", "bestine_commerce_spawner_03", "bestine_commerce_spawner_04", "bestine_commerce_spawner_05", "bestine_commerce_spawner_06", "bestine_commerce_spawner_07", "bestine_commerce_spawner_08", "bestine_commerce_spawner_09", "bestine_commerce_spawner_10", "bestine_commerce_spawner_11", "bestine_commerce_spawner_12", "bestine_commerce_spawner_13", "bestine_commerce_spawner_14", "bestine_commerce_spawner_15"},
			shipSpawns = {"freighterheavy_tier3_story", "freighterheavy_tier3", "freighterheavy_tier3", "freighterheavy_tier1", "freighterheavy_tier2", "freighterlight_tier1", "freighterlight_tier1", "freighterlight_tier2", "freightermedium_tier1", "freightermedium_tier1", "freightermedium_tier2"}
		},
		{spawnName = "anchorhead_supply_route", spawnType = SHIP_SPAWN_SINGLE, x = -549, z = -164, y = -2941, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 32, maxSpawnDistance = 64, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"anchorhead_supply_route_00", "anchorhead_supply_route_01", "anchorhead_supply_route_02", "anchorhead_supply_route_03"},
			shipSpawns = {"freighterheavy_tier3_story", "freighterheavy_tier1", "freighterheavy_tier3", "freighterlight_tier1", "freighterlight_tier1", "freightermedium_tier1", "freightermedium_tier1"}
		},
		{spawnName = "smugglers_to_station", spawnType = SHIP_SPAWN_SINGLE, x = -1770, z = -911, y = -1815, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 120, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 70, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"smugglers_to_station_00", "smugglers_to_station_01", "smugglers_to_station_02", "smugglers_to_station_03"},
			shipSpawns = {"freighterheavy_tier3_story", "freighterheavy_tier3_story", "smuggler_freighterlight_tier3", "smuggler_freightermedium_tier3"}
		},
		{spawnName = "smuggler_asteroid_patrol_02", spawnType = SHIP_SPAWN_SINGLE, x = 3535, z = -793, y = 4323, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 2, maxSpawnDistance = 8, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"smuggler_asteroid_patrol_02_00", "smuggler_asteroid_patrol_02_01", "smuggler_asteroid_patrol_02_02", "smuggler_asteroid_patrol_02_03", "smuggler_asteroid_patrol_02_04", "smuggler_asteroid_patrol_02_05", "smuggler_asteroid_patrol_02_06", "smuggler_asteroid_patrol_02_07", "smuggler_asteroid_patrol_02_08"},
			shipSpawns = {"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{spawnName = "rebel_smuggler_escape", spawnType = SHIP_SPAWN_SINGLE, x = 2708, z = 2359, y = -1251, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 60, maxRespawn = 120, minSpawnDistance = 10, maxSpawnDistance = 80, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_smuggler_escape_00", "rebel_smuggler_escape_01", "rebel_smuggler_escape_02", "rebel_smuggler_escape_03"},
			shipSpawns = {"rebel_smuggler"}
		},
		{spawnName = "tie_smuggler_ambush", spawnType = SHIP_SPAWN_SQUADRON, x = 4134, z = 2613, y = -1290, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 80, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"tie_smuggler_ambush_00", "tie_smuggler_ambush_01", "tie_smuggler_ambush_02", "tie_smuggler_ambush_03", "tie_smuggler_ambush_04", "tie_smuggler_ambush_05", "tie_smuggler_ambush_06"},
			shipSpawns = {"squad_tie_standard_tier1"}
		},
		{spawnName = "mining_route_1", spawnType = SHIP_SPAWN_SINGLE, x = -6912, z = 6077, y = 2586, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 30, maxSpawnDistance = 80, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"mining_route_1_00", "mining_route_1_01", "mining_route_1_02", "mining_route_1_03", "mining_route_1_04", "mining_route_1_05", "mining_route_1_06", "mining_route_1_07"},
			shipSpawns = {"freighterheavy_mining", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_mining", "freightermedium_mining"}
		},
	},
}

registerScreenPlay("SpaceTatooineSpawner", true)
