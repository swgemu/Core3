SpaceDathomirSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceDathomirSpawner",

	spaceZone = "space_dathomir",

	shipSpawns = {
		{spawnName = "imperial_generator_lookout_1", spawnType = SHIP_SPAWN_SINGLE, x = 1365, z = -6750, y = 7020, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 100, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 70, maxPatrol = 340, totalSpawns = 6,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_advanced_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "bh_target_escort_elite_01", spawnType = SHIP_SPAWN_SQUADRON, x = -1835, z = -33, y = 3647, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 4, maxSpawnDistance = 24, minPatrol = 320, maxPatrol = 320, totalSpawns = 2,
			shipSpawns = {"squad_dath_deathmarked_mercenary"}
		},
		{spawnName = "warlord_ship_to_imp", spawnType = SHIP_SPAWN_SINGLE, x = -2700, z = -6358, y = 1958, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 420, maxRespawn = 620, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"warlord_ship_to_imp_00", "warlord_ship_to_imp_01", "warlord_ship_to_imp_02", "warlord_ship_to_imp_03", "warlord_ship_to_imp_04", "warlord_ship_to_imp_05", "warlord_ship_to_imp_06", "warlord_ship_to_imp_07", "warlord_ship_to_imp_08", "warlord_ship_to_imp_09", "warlord_ship_to_imp_10", "warlord_ship_to_imp_11", "warlord_ship_to_imp_12", "warlord_ship_to_imp_13", "warlord_ship_to_imp_14", "warlord_ship_to_imp_15", "warlord_ship_to_imp_16", "warlord_ship_to_imp_17", "warlord_ship_to_imp_18", "warlord_ship_to_imp_19", "warlord_ship_to_imp_20", "warlord_ship_to_imp_21", "warlord_ship_to_imp_22", "warlord_ship_to_imp_23", "warlord_ship_to_imp_24", "warlord_ship_to_imp_25", "warlord_ship_to_imp_26", "warlord_ship_to_imp_27", "warlord_ship_to_imp_28", "warlord_ship_to_imp_29", "warlord_ship_to_imp_30", "warlord_ship_to_imp_31", "warlord_ship_to_imp_32"},
			shipSpawns = {"blacksun_dark_eclipse_tier5", "blacksun_bomber_s03_tier5", "blacksun_aggressor_tier5", "blacksun_ace_s04_tier5", "blacksun_fighter_s01_tier5"}
		},
		{spawnName = "rebel_attackers_are_cool", spawnType = SHIP_SPAWN_SQUADRON, x = -2448, z = -1160, y = 6868, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 3600, maxRespawn = 8200, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_attackers_are_cool_00", "rebel_attackers_are_cool_01", "rebel_attackers_are_cool_02", "rebel_attackers_are_cool_03", "rebel_attackers_are_cool_04", "rebel_attackers_are_cool_05", "rebel_attackers_are_cool_06"},
			shipSpawns = {"squad_corvette_blockade_run"}
		},
		{spawnName = "imperial_beacon_lookout_1", spawnType = SHIP_SPAWN_SINGLE, x = -2974, z = -3082, y = 2835, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 120, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 50, maxPatrol = 320, totalSpawns = 3,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_station_guard_interceptor_1", spawnType = SHIP_SPAWN_SQUADRON, x = 4994, z = -4896, y = -1322, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_tie_interceptor_ace"}
		},
		{spawnName = "random_imperial_dudes_1", spawnType = SHIP_SPAWN_SINGLE, x = 272, z = -6947, y = -6161, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 320, totalSpawns = 6,
			shipSpawns = {"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "random_imperial_dudes", spawnType = SHIP_SPAWN_SINGLE, x = -861, z = -6791, y = -7342, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 320, totalSpawns = 6,
			shipSpawns = {"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_fighter_tier4"}
		},
		{spawnName = "generator_imperial_defense_2", spawnType = SHIP_SPAWN_SINGLE, x = -4504, z = 2537, y = 4026, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 30, maxSpawnDistance = 40, minPatrol = 60, maxPatrol = 320, totalSpawns = 3,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"}
		},
		{spawnName = "generator_imperial_defense_1", spawnType = SHIP_SPAWN_SINGLE, x = -4549, z = 3176, y = 4114, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 60, maxPatrol = 320, totalSpawns = 3,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "tier3_privateer_witchblood_inspect_01", spawnType = SHIP_SPAWN_SINGLE, x = 6228, z = -6411, y = -5797, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 10, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"dath_witchblood_clan_soldier_tier3"}
		},
		{spawnName = "imperial_station_guard_2", spawnType = SHIP_SPAWN_SQUADRON, x = 3123, z = -5170, y = -4160, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"squad_tie_standard_ace"}
		},
		{spawnName = "imperial_station_guard_1", spawnType = SHIP_SPAWN_SQUADRON, x = 5228, z = -4847, y = -3716, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 300, totalSpawns = 2,
			shipSpawns = {"squad_tie_standard_ace"}
		},
		{spawnName = "imperial_generator_defense_5", spawnType = SHIP_SPAWN_SINGLE, x = 4350, z = -5175, y = -7118, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 90, maxPatrol = 300, totalSpawns = 6,
			shipSpawns = {"tieaggressor_ace_tier4", "tieadvanced_inquisitor_tier4", "tieadvanced_ace_tier4", "tieoppressor_ace_tier4"}
		},
		{spawnName = "imperial_uber_fleet_1", spawnType = SHIP_SPAWN_SQUADRON, x = 5874, z = -5465, y = -7280, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 7200, maxRespawn = 8200, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_uber_fleet_1_00", "imperial_uber_fleet_1_01", "imperial_uber_fleet_1_02", "imperial_uber_fleet_1_03", "imperial_uber_fleet_1_04", "imperial_uber_fleet_1_05"},
			shipSpawns = {"squad_imperial_fleet"}
		},
		{spawnName = "imperial_generator_lookout_4", spawnType = SHIP_SPAWN_SINGLE, x = 6234, z = -1952, y = -7218, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 70, maxPatrol = 340, totalSpawns = 6,
			shipSpawns = {"imp_tie_bomber_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "naboo_imperial_tier4_inspect1_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 7606, z = 4673, y = -1681, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 30, minPatrol = 50, maxPatrol = 140, totalSpawns = 1,
			shipSpawns = {"crystal_smuggler_yt1300_tier4"}
		},
		{spawnName = "imperial_secret_station_guard_2", spawnType = SHIP_SPAWN_SQUADRON, x = 6338, z = 6281, y = -6527, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_tie_mix_ace"}
		},
		{spawnName = "imp_gunboat_1", spawnType = SHIP_SPAWN_SINGLE, x = 6086, z = 6130, y = -6737, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imp_gunboat_1_00", "imp_gunboat_1_01", "imp_gunboat_1_02", "imp_gunboat_1_03", "imp_gunboat_1_04", "imp_gunboat_1_05", "imp_gunboat_1_06", "imp_gunboat_1_07", "imp_gunboat_1_08", "imp_gunboat_1_09", "imp_gunboat_1_10", "imp_gunboat_1_11", "imp_gunboat_1_12", "imp_gunboat_1_13", "imp_gunboat_1_14", "imp_gunboat_1_15", "imp_gunboat_1_16", "imp_gunboat_1_17", "imp_gunboat_1_18", "imp_gunboat_1_19", "imp_gunboat_1_20", "imp_gunboat_1_21", "imp_gunboat_1_22", "imp_gunboat_1_23", "imp_gunboat_1_24"},
			shipSpawns = {"imp_imperial_gunboat_tier4"}
		},
		{spawnName = "imperial_secret_station_guard_1", spawnType = SHIP_SPAWN_SQUADRON, x = 5531, z = 5803, y = -5911, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_tie_mix_ace"}
		},
		{spawnName = "imperial_secret_station_guard_3", spawnType = SHIP_SPAWN_SQUADRON, x = 6309, z = 5641, y = -6127, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"squad_tie_advanced_ace"}
		},
		{spawnName = "imperial_fleet_to_imp", spawnType = SHIP_SPAWN_SQUADRON, x = 5712, z = 5708, y = -6515, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 10, maxSpawnDistance = 30, totalSpawns = 1,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_fleet_to_imp_00", "imperial_fleet_to_imp_01", "imperial_fleet_to_imp_02", "imperial_fleet_to_imp_03", "imperial_fleet_to_imp_04", "imperial_fleet_to_imp_05", "imperial_fleet_to_imp_06", "imperial_fleet_to_imp_07", "imperial_fleet_to_imp_08", "imperial_fleet_to_imp_09", "imperial_fleet_to_imp_10", "imperial_fleet_to_imp_11", "imperial_fleet_to_imp_12", "imperial_fleet_to_imp_13", "imperial_fleet_to_imp_14", "imperial_fleet_to_imp_15", "imperial_fleet_to_imp_16", "imperial_fleet_to_imp_17", "imperial_fleet_to_imp_18", "imperial_fleet_to_imp_19", "imperial_fleet_to_imp_20", "imperial_fleet_to_imp_21"},
			shipSpawns = {"squad_imperial_fleet"}
		},
		{spawnName = "tatooine_rebel_tier3_2_suspect_1", spawnType = SHIP_SPAWN_SINGLE, x = 5585, z = 4809, y = -2403, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 30, maxRespawn = 120, minSpawnDistance = 1, maxSpawnDistance = 100, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"tatooine_rebel_tier3_2_suspect_1_00", "tatooine_rebel_tier3_2_suspect_1_01", "tatooine_rebel_tier3_2_suspect_1_02", "tatooine_rebel_tier3_2_suspect_1_03"},
			shipSpawns = {"tatooine_tier3_2_inspect_awing", "tatooine_tier3_2_inspect_bwing", "tatooine_tier3_2_inspect_xwing", "tatooine_tier3_2_inspect_ywing", "reb_awing_tier4", "reb_bwing_tier4"}
		},
		{spawnName = "tatooine_rebel_tier3_2_suspect_2", spawnType = SHIP_SPAWN_SINGLE, x = 4719, z = 5053, y = -3111, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 30, maxRespawn = 120, minSpawnDistance = 1, maxSpawnDistance = 100, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"tatooine_rebel_tier3_2_suspect_2_00", "tatooine_rebel_tier3_2_suspect_2_01", "tatooine_rebel_tier3_2_suspect_2_02", "tatooine_rebel_tier3_2_suspect_2_03", "tatooine_rebel_tier3_2_suspect_2_04", "tatooine_rebel_tier3_2_suspect_2_05"},
			shipSpawns = {"reb_awing_tier4", "reb_bwing_tier4", "tatooine_tier3_2_inspect_awing", "tatooine_tier3_2_inspect_bwing", "tatooine_tier3_2_inspect_xwing", "tatooine_tier3_2_inspect_ywing", "tatooine_tier3_2_inspect_ywing"}
		},
		{spawnName = "naboo_imperial_tier3_inspect3escort_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 2021, z = 4211, y = -3441, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 5,
			shipSpawns = {"xwing_ace"}
		},
		{spawnName = "naboo_imperial_tier3_inspect3_spawner", spawnType = SHIP_SPAWN_SINGLE, x = 2005, z = 4299, y = -3566, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 30, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 50, minPatrol = 100, maxPatrol = 300, totalSpawns = 1,
			shipSpawns = {"rebel_spyfreighter_tier3"}
		},
		{spawnName = "corellia_imperial_tier4_inspect3", spawnType = SHIP_SPAWN_SINGLE, x = -1184, z = -670, y = -4776, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 70, maxPatrol = 240, totalSpawns = 1,
			shipSpawns = {"velocity_commander_tier4"}
		},
		{spawnName = "generator_coynite_defense_2", spawnType = SHIP_SPAWN_SINGLE, x = -110, z = -2251, y = 6620, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 60, maxPatrol = 320, totalSpawns = 3,
			shipSpawns = {"coynite_merc_captain_tier5", "coynite_merc_pulsar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_quasar_tier4"}
		},
		{spawnName = "generator_coynite_defense_1", spawnType = SHIP_SPAWN_SINGLE, x = -234, z = -1620, y = 6655, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 40, minPatrol = 60, maxPatrol = 320, totalSpawns = 3,
			shipSpawns = {"coynite_merc_neutron_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_pulsar_boss", "coynite_merc_quasar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_neutron_tier4", "coynite_merc_neutron_tier4", "coynite_merc_neutron_tier4"}
		},
		{spawnName = "imperial_generator_defense_4", spawnType = SHIP_SPAWN_SINGLE, x = 2244, z = -1295, y = 7106, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 30, minPatrol = 60, maxPatrol = 320, totalSpawns = 6,
			shipSpawns = {"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_advanced_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{spawnName = "imperial_generator_defense_3", spawnType = SHIP_SPAWN_SINGLE, x = 2221, z = -760, y = 7145, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 120, maxRespawn = 300, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 60, maxPatrol = 320, totalSpawns = 6,
			shipSpawns = {"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"}
		},
		{spawnName = "generator_imperial_defense_4", spawnType = SHIP_SPAWN_SINGLE, x = 1960, z = -1036, y = 7451, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 400, minSpawnDistance = 20, maxSpawnDistance = 40, minPatrol = 60, maxPatrol = 120, totalSpawns = 5,
			shipSpawns = {"imp_tie_bomber_tier4", "imp_tie_fighter_tier4"}
		},
		{spawnName = "hiddendaggers_route_1", spawnType = SHIP_SPAWN_SINGLE, x = -837, z = 4833, y = 1180, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 50, maxSpawnDistance = 100, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"hiddendaggers_route_1_00", "hiddendaggers_route_1_01", "hiddendaggers_route_1_02", "hiddendaggers_route_1_03", "hiddendaggers_route_1_04", "hiddendaggers_route_1_05", "hiddendaggers_route_1_06", "hiddendaggers_route_1_07", "hiddendaggers_route_1_08", "hiddendaggers_route_1_09", "hiddendaggers_route_1_10", "hiddendaggers_route_1_11", "hiddendaggers_route_1_12", "hiddendaggers_route_1_13", "hiddendaggers_route_1_14", "hiddendaggers_route_1_15", "hiddendaggers_route_1_16", "hiddendaggers_route_1_17", "hiddendaggers_route_1_18", "hiddendaggers_route_1_19", "hiddendaggers_route_1_20", "hiddendaggers_route_1_21", "hiddendaggers_route_1_22", "hiddendaggers_route_1_23", "hiddendaggers_route_1_24", "hiddendaggers_route_1_25", "hiddendaggers_route_1_26", "hiddendaggers_route_1_27", "hiddendaggers_route_1_28", "hiddendaggers_route_1_29", "hiddendaggers_route_1_30", "hiddendaggers_route_1_31", "hiddendaggers_route_1_32", "hiddendaggers_route_1_33", "hiddendaggers_route_1_34", "hiddendaggers_route_1_35", "hiddendaggers_route_1_36", "hiddendaggers_route_1_37"},
			shipSpawns = {"hidden_daggers_slayer_tier4", "hidden_daggers_killer_tier4", "hidden_daggers_enforcer_tier4", "hidden_daggers_gunship_tier5"}
		},
		{spawnName = "bh_target_escort_01", spawnType = SHIP_SPAWN_SQUADRON, x = 2849, z = 1098, y = 996, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 6, maxSpawnDistance = 18, minPatrol = 210, maxPatrol = 420, totalSpawns = 1,
			shipSpawns = {"squad_dath_witchblood_clan"}
		},
		{spawnName = "bh_target_escort_elite_02", spawnType = SHIP_SPAWN_SQUADRON, x = 830, z = 651, y = 1000, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 4, maxSpawnDistance = 26, minPatrol = 80, maxPatrol = 310, totalSpawns = 1,
			shipSpawns = {"squad_dath_freelance_killer"}
		},
		{spawnName = "tier3_privateer_witchblood_inspect_02", spawnType = SHIP_SPAWN_SINGLE, x = -808, z = -379, y = 1892, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 14, maxSpawnDistance = 24, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"tier3_privateer_witchblood_inspect_02_00", "tier3_privateer_witchblood_inspect_02_01", "tier3_privateer_witchblood_inspect_02_02", "tier3_privateer_witchblood_inspect_02_03", "tier3_privateer_witchblood_inspect_02_04", "tier3_privateer_witchblood_inspect_02_05", "tier3_privateer_witchblood_inspect_02_06"},
			shipSpawns = {"dath_witchblood_clan_soldier_tier4", "dath_witchblood_clan_punisher_tier3"}
		},
		{spawnName = "corellia_privateer_tier3_2_inspect", spawnType = SHIP_SPAWN_SINGLE, x = -50, z = 1375, y = 1510, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 45, maxRespawn = 60, minSpawnDistance = 10, maxSpawnDistance = 120, minPatrol = 200, maxPatrol = 500, totalSpawns = 1,
			shipSpawns = {"civshuttle_cor_tier3_pilot_capture"}
		},
		{spawnName = "corellia_privateer_tier4_leg_2_destroy_two", spawnType = SHIP_SPAWN_SINGLE, x = 684, z = -2863, y = -1310, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 30, maxSpawnDistance = 60, minPatrol = 80, maxPatrol = 290, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_killer_tier4", "hidden_daggers_slayer_tier4", "hidden_daggers_nebula_stalker_tier5"}
		},
		{spawnName = "imperial_squad_patrol_1", spawnType = SHIP_SPAWN_SQUADRON, x = -129, z = -732, y = 12, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 3600, maxRespawn = 10800, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 3,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperial_squad_patrol_1_00", "imperial_squad_patrol_1_01", "imperial_squad_patrol_1_02", "imperial_squad_patrol_1_03", "imperial_squad_patrol_1_04", "imperial_squad_patrol_1_05", "imperial_squad_patrol_1_06"},
			shipSpawns = {"squad_tie_oppressor_ace", "imp_decimator_boss"}
		},
		{spawnName = "engineers_to_base_1", spawnType = SHIP_SPAWN_SINGLE, x = 40, z = -687, y = -5, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 20, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"engineers_to_base_1_00", "engineers_to_base_1_01", "engineers_to_base_1_02", "engineers_to_base_1_03", "engineers_to_base_1_04"},
			shipSpawns = {"imperial_engineer", "tieinterceptor_ace_tier4"}
		},
		{spawnName = "imperial_generator_defense_2", spawnType = SHIP_SPAWN_SINGLE, x = -7086, z = 2295, y = -760, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 90, maxPatrol = 380, totalSpawns = 6,
			shipSpawns = {"tieaggressor_ace_tier4", "tieadvanced_ace_tier4", "tieaggressor_inquisitor_tier3", "tiebomber_ace_tier4", "tiedecimator_ace_tier4", "tieinterceptor_ace_tier4"}
		},
		{spawnName = "station_police_1", spawnType = SHIP_SPAWN_SINGLE, x = -5537, z = 2258, y = -3028, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 90, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"corsec_fighter_tier4"}
		},
		{spawnName = "station_police_patrol", spawnType = SHIP_SPAWN_SINGLE, x = -6146, z = 2677, y = -4616, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"station_police_patrol_00", "station_police_patrol_01", "station_police_patrol_02", "station_police_patrol_03", "station_police_patrol_04", "station_police_patrol_05", "station_police_patrol_06", "station_police_patrol_07", "station_police_patrol_08", "station_police_patrol_09", "station_police_patrol_10"},
			shipSpawns = {"corsec_fighter_tier4", "corsec_lancer_tier4", "corsec_gunship_tier4", "corsec_fighter_tier4", "corsec_fighter_tier4", "corsec_fighter_tier4", "corsec_lancer_tier4", "corsec_lancer_tier4", "corsec_lancer_tier4"}
		},
		{spawnName = "imperial_generator_defense_1", spawnType = SHIP_SPAWN_SINGLE, x = -7392, z = 2059, y = -1933, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 90, maxPatrol = 380, totalSpawns = 6,
			shipSpawns = {"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4", "tieinterceptor_ace_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"}
		},
		{spawnName = "station_police_2", spawnType = SHIP_SPAWN_SINGLE, x = -5190, z = 2048, y = -1933, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 90, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"corsec_fighter_tier4"}
		},
		{spawnName = "station_traders_to_generator", spawnType = SHIP_SPAWN_SINGLE, x = -7168, z = 2679, y = -3628, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"station_traders_to_generator_00", "station_traders_to_generator_01"},
			shipSpawns = {"freighterheavy", "freighterlight_mining", "freighterheavy_tier3_story", "freighterheavy_tier3_story"}
		},
		{spawnName = "rebel_defenders_2", spawnType = SHIP_SPAWN_SINGLE, x = 5131, z = 242, y = -512, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 90, maxPatrol = 380, totalSpawns = 6,
			shipSpawns = {"reb_bwing_tier4", "reb_awing_tier4"}
		},
		{spawnName = "rebel_patrol_1", spawnType = SHIP_SPAWN_SINGLE, x = 7077, z = -1467, y = 1776, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 6,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebel_patrol_1_00", "rebel_patrol_1_01", "rebel_patrol_1_02", "rebel_patrol_1_03", "rebel_patrol_1_04", "rebel_patrol_1_05", "rebel_patrol_1_06", "rebel_patrol_1_07", "rebel_patrol_1_08", "rebel_patrol_1_09"},
			shipSpawns = {"reb_awing_tier4", "reb_awing_tier4", "reb_awing_tier4", "reb_awing_tier4", "reb_bwing_tier4", "reb_bwing_tier4", "reb_bwing_tier4", "reb_bwing_tier4", "reb_xwing_tier4", "reb_ykl37r_tier4", "reb_ywing_tier4"}
		},
		{spawnName = "rebel_defenders_1", spawnType = SHIP_SPAWN_SINGLE, x = 7438, z = -450, y = 1370, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 90, maxPatrol = 380, totalSpawns = 6,
			shipSpawns = {"reb_bwing_tier4", "reb_awing_tier4"}
		},
		{spawnName = "nebula_assassin_guardians_2", spawnType = SHIP_SPAWN_SINGLE, x = -1969, z = 2659, y = -7044, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 90, maxPatrol = 300, totalSpawns = 3,
			shipSpawns = {"nebula_assassin_bomber_tier4", "nebula_assassin_saboteur_tier5"}
		},
		{spawnName = "nebula_assassin_patrol_inside", spawnType = SHIP_SPAWN_SINGLE, x = -7393, z = -7555, y = -7641, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 5, maxSpawnDistance = 10, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"nebula_assassin_patrol_inside_00", "nebula_assassin_patrol_inside_01", "nebula_assassin_patrol_inside_02", "nebula_assassin_patrol_inside_03", "nebula_assassin_patrol_inside_04", "nebula_assassin_patrol_inside_05", "nebula_assassin_patrol_inside_06", "nebula_assassin_patrol_inside_07", "nebula_assassin_patrol_inside_08", "nebula_assassin_patrol_inside_09", "nebula_assassin_patrol_inside_10"},
			shipSpawns = {"nebula_assassin_bomber_tier4", "nebula_assassin_bounty_hunter_tier5", "nebula_assassin_fighter_tier4", "nebula_assassin_boss", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_bomber_tier4", "nebula_assassin_bomber_tier4", "nebula_assassin_bomber_tier4", "nebula_assassin_bomber_tier4", "nebula_assassin_bomber_tier4", "nebula_assassin_bomber_tier4"}
		},
		{spawnName = "nebula_assassin_guardians_1", spawnType = SHIP_SPAWN_SINGLE, x = -3149, z = -2583, y = -5926, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 5, maxSpawnDistance = 10, minPatrol = 90, maxPatrol = 200, totalSpawns = 3,
			shipSpawns = {"nebula_assassin_bomber_tier5", "nebula_assassin_bounty_hunter_tier5"}
		},
		{spawnName = "hutt_smuggler_route_1", spawnType = SHIP_SPAWN_SINGLE, x = -3378, z = 3317, y = -3140, patrolType = SHIP_AI_SINGLE_PATROL_ROTATION, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 10, maxSpawnDistance = 100, totalSpawns = 2,
			patrolsToAssign = 5, fixedPatrolPoints = {"hutt_smuggler_route_1_00", "hutt_smuggler_route_1_01", "hutt_smuggler_route_1_02", "hutt_smuggler_route_1_03", "hutt_smuggler_route_1_04", "hutt_smuggler_route_1_05"},
			shipSpawns = {"hutt_bomber_s02_tier4", "hutt_fighter_s02_tier4", "hutt_pirate_s02_tier4"}
		},
		{spawnName = "corellia_privateer_tier4_leg_2_destroy_one", spawnType = SHIP_SPAWN_SINGLE, x = 4664, z = -3490, y = 4841, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 30, maxSpawnDistance = 60, minPatrol = 80, maxPatrol = 360, totalSpawns = 3,
			shipSpawns = {"hidden_daggers_killer_tier4", "hidden_daggers_gunship_tier4", "hidden_daggers_slayer_tier4"}
		},
		{spawnName = "bh_target_escort_02", spawnType = SHIP_SPAWN_SQUADRON, x = 801, z = -1284, y = -3418, patrolType = SHIP_AI_RANDOM_PATROL, minRespawn = 300, maxRespawn = 420, minSpawnDistance = 9, maxSpawnDistance = 18, minPatrol = 140, maxPatrol = 420, totalSpawns = 1,
			shipSpawns = {"squad_dath_witchblood_clan"}
		},
		{spawnName = "tier3_privateer_witchblood_inspect_01", spawnType = SHIP_SPAWN_SINGLE, x = -1662, z = 721, y = -313, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 300, minSpawnDistance = 24, maxSpawnDistance = 48, totalSpawns = 4,
			patrolsToAssign = 5, fixedPatrolPoints = {"tier3_privateer_witchblood_inspect_01_00", "tier3_privateer_witchblood_inspect_01_01", "tier3_privateer_witchblood_inspect_01_02", "tier3_privateer_witchblood_inspect_01_03", "tier3_privateer_witchblood_inspect_01_04", "tier3_privateer_witchblood_inspect_01_05", "tier3_privateer_witchblood_inspect_01_06"},
			shipSpawns = {"dath_witchblood_clan_soldier_tier3"}
		},
	},
}

registerScreenPlay("SpaceDathomirSpawner", true)
