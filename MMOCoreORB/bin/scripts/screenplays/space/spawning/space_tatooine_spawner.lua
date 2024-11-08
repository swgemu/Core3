SpaceTatooineSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceTatooineSpawner",

	spaceZone = "space_tatooine",

	shipSpawns = {
		{"hutt_guards_base_4", 1428, 7355, -5554, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 50, 120, 3,
			{"hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1_tatooine", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1_tatooine"}
		},
		{"iron_roid_pirate_01", 1752, -1247, 531, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 100, 50, 200, 3,
			{"bestine_pirate_tier1"}
		},
		{"iron_roid_pirate_02", 2514, -1699, 307, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 100, 50, 200, 3,
			{"bestine_pirate_tier1"}
		},
		{"iron_roid_pirate_03", 2406, -1187, 165, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 100, 50, 200, 3,
			{"bestine_pirate_tier1"}
		},
		{"hutt_hideout", -2875, -2740, -2927, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 100, 50, 200, 4,
			{"hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_starbomber", "hutt_fighter_s01_tier1_tatooine", "hutt_fighter_s01_tier1_tatooine", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1_tatooine"}
		},
		{"freighter_victim", -2010, 1612, -2227, SHIP_AI_RANDOM_PATROL, 300, 420, 10, 100, 50, 200, 1,
			{"freighterlight_tier1"}
		},
		{"imp_base_defense_02", -3665, 618, 2970, SHIP_AI_GUARD_PATROL, 40, 90, 4, 12, 50, 200, 6,
			{"imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{"blacksun_threat_2", 1098, 767, -2978, SHIP_AI_RANDOM_PATROL, 60, 120, 6, 14, 50, 200, 6,
			{"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_fighter_s02_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{"reb_recon_threat_2", -2203, -2389, 518, SHIP_AI_RANDOM_PATROL, 60, 120, 4, 16, 50, 200, 3,
			{"imp_tie_bomber_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1"}
		},
		{"blacksun_threat_3", 2816, 336, -1908, SHIP_AI_RANDOM_PATROL, 60, 120, 9, 20, 50, 200, 8,
			{"blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2_tatooine", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s01_tier2_tatooine", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{"bestine_pirates", 896, 1268, -2850, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 30, 50, 200, 3,
			{"bestine_pirate_tier1"}
		},
		{"imperial_base_guard_1", -6388, 4911, -1055, SHIP_AI_RANDOM_PATROL, 40, 90, 10, 30, 50, 200, 6,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_aggressor_tier1", "imp_tie_advanced_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{"anchorhead_supply_threat_1", -982, -104, -1281, SHIP_AI_RANDOM_PATROL, 60, 120, 12, 32, 100, 200, 6,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1"}
		},
		{"marcus_the_mad", 230, 1165, -2275, SHIP_AI_RANDOM_PATROL, 60, 120, 8, 32, 100, 200, 1,
			{"marcus_the_mad"}
		},
		{"anchorhead_tie_rally_alpha", 1948, -366, 2316, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 40, 50, 200, 4,
			{"imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_bomber_tier1", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{"anchorhead_supply_threat_2", -3194, -425, -1769, SHIP_AI_RANDOM_PATROL, 60, 120, 4, 48, 50, 200, 6,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_aggressor_tier1", "imp_tie_advanced_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{"blacksun_leader_guards", -2161, -1000, -5306, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 50, 200, 8,
			{"blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2_tatooine", "blacksun_bomber_s01_tier2_tatooine", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s01_tier2_tatooine", "blacksun_fighter_s01_tier2_tatooine", "blacksun_marauder_tier1", "blacksun_starkiller_leader", "blacksun_vehement_tier1"}
		},
		{"blacksun_pirates", -2024, 1619, -2219, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 50, 200, 8,
			{"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_fighter_s03_tier1", "blacksun_vehement_tier1"}
		},
		{"bestine_security_threat_1", -3461, 775, -1259, SHIP_AI_RANDOM_PATROL, 60, 120, 12, 64, 50, 200, 3,
			{"bestine_pirate_tier1"}
		},
		{"bestine_escort_threat_2", -1033, 2231, -423, SHIP_AI_RANDOM_PATROL, 60, 120, 14, 64, 50, 200, 4,
			{"bestine_pirate_tier1"}
		},
		{"bestine_security_threat_3", 2235, 1017, -388, SHIP_AI_RANDOM_PATROL, 60, 120, 16, 64, 50, 200, 3,
			{"bestine_pirate_tier1"}
		},
		{"bestine_escort_threat_1", 2525, 933, 851, SHIP_AI_RANDOM_PATROL, 60, 120, 24, 64, 50, 200, 3,
			{"bestine_pirate_tier1"}
		},
		{"bestine_pirate_leader_guards", -1599, -3076, 3432, SHIP_AI_RANDOM_PATROL, 60, 120, 12, 68, 50, 200, 3,
			{"bestine_pirate_tier1"}
		},
		{"bestine_escort_threat_3", -3855, 1057, 523, SHIP_AI_RANDOM_PATROL, 60, 120, 14, 68, 50, 200, 4,
			{"bestine_pirate_tier1", "bestine_pirate_tier1", "bestine_pirate_tier1", "bestine_pirate_tier1", "bestine_pirate_leader_tier1"}
		},
		{"bestine_security_threat_2", -519, 1650, -1372, SHIP_AI_RANDOM_PATROL, 60, 120, 6, 68, 50, 200, 5,
			{"bestine_pirate_tier1"}
		},
		{"mining_guard_1", -6796, 5934, 2329, SHIP_AI_RANDOM_PATROL, 60, 120, 30, 80, 100, 200, 4,
			{"mining_guard_ship", "mining_guard_ship_tatooine", "mining_guard_ship_tatooine", "mining_guard_ship"}
		},
		{"smuggler_base_defense_02", 3147, 234, 3608, SHIP_AI_RANDOM_PATROL, 60, 120, 32, 96, 100, 200, 3,
			{"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{"blacksun_pirates_and_leader", -2155, -1000, -5300, SHIP_AI_RANDOM_PATROL, 180, 240, 10, 100, 80, 300, 4,
			{"blacksun_ace_s04_tier2", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2_tatooine", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s01_tier2_tatooine", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{"bestine_vs_valarians_1", 7066, 6890, 7230, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 3,
			{"valarian_bomber_tier2"}
		},
		{"bestine_vs_valarians_2", 6982, 6813, 7266, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 3,
			{"bestine_pirate_tier2"}
		},
		{"blacksun_guards_3", 4197, 417, 4421, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 6,
			{"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2_tatooine", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2"}
		},
		{"bestine_pirate_guards_2", 7286, 5697, 5923, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 4,
			{"bestine_pirate_tier1"}
		},
		{"bestine_pirate_guards_6", 171, 4068, 2808, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 4,
			{"bestine_pirate_tier1"}
		},
		{"bestine_pirates_guard_1", 5713, 5701, 7337, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 4,
			{"bestine_pirate_tier1", "bestine_pirate_tier1", "bestine_pirate_tier1", "bestine_pirate_leader_tier2"}
		},
		{"bestine_pirates_guards_5", 4188, 6563, 4833, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 4,
			{"bestine_pirate_tier1"}
		},
		{"blacksun_n_stuff_1", 5588, 1002, 6147, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 8,
			{"blacksun_aggressor_tier1", "blacksun_bomber_s01_tier1", "blacksun_fighter_s01_tier1", "blacksun_marauder_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{"valarian_spine_guard_1", -4538, -4668, -5590, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 4,
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{"valarian_spine_guard_2", -3741, -824, -3582, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 4,
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{"valarian_spine_guard_4", -1877, 5565, -634, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 4,
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{"valarian_static_guard_1", -6251, -6734, -7054, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 20, 150, 300, 4,
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{"poi_quest_garett", -249, -3495, 1800, SHIP_AI_RANDOM_PATROL, 10, 20, 10, 20, 150, 300, 1,
			{"poi_garett_convo_ship_tier2"}
		},
		{"poi_quest_mining", -5492, 35, 6255, SHIP_AI_RANDOM_PATROL, 10, 20, 10, 20, 150, 300, 1,
			{"poi_mining_convo_ship_tier2"}
		},
		{"poi_quest_police", 3620, -5735, 3802, SHIP_AI_RANDOM_PATROL, 10, 20, 10, 20, 150, 300, 1,
			{"poi_eisley_captain_convo_ship_tier2"}
		},
		{"poi_general2_spice_1", 783, 18, 3268, SHIP_AI_RANDOM_PATROL, 10, 20, 10, 20, 150, 300, 3,
			{"spice_pirate_fighter_tier1"}
		},
		{"poi_general2_spice_2", 366, 150, 2073, SHIP_AI_RANDOM_PATROL, 10, 20, 10, 20, 150, 300, 3,
			{"spice_pirate_spy_tier1"}
		},
		{"poi_privateer_inspect_blacksun", -4915, 3681, 456, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 20, 150, 300, 6,
			{"blacksun_ace_s04_tier2", "blacksun_aggressor_tier2", "blacksun_bomber_ace_s04_tier2", "poi_blacksun_aggressor_tier2"}
		},
		{"poi_privateer_inspect_valarian", -6087, -4435, -6333, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 20, 150, 300, 3,
			{"poi_valarian_fighter_tier1", "valarian_fighter_tier1", "valarian_fighter_tier1", "valarian_fighter_tier1"}
		},
		{"hutts_vs_valarian_2", -3975, 6686, 1033, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 20, 150, 300, 4,
			{"hutt_bomber_s01_tier1"}
		},
		{"hutts_vs_valarians_1", -3036, 3431, -813, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 20, 150, 300, 4,
			{"hutt_bomber_s01_tier1"}
		},
		{"valarian_station_guard_1", -1184, 6619, 1069, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 20, 150, 300, 5,
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{"valarian_station_guard_2", -770, 6077, -5, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 150, 300, 5,
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine", "valarian_gunship_tier1_tatooine", "valarian_gunship_tier1"}
		},
		{"smuggler_base_defense_03", 3016, 167, 3229, SHIP_AI_RANDOM_PATROL, 60, 120, 16, 32, 100, 300, 3,
			{"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{"hutt_guards_base_1", 2692, 5872, -7252, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 300, 3,
			{"hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1_tatooine", "hutt_fighter_s01_tier1_tatooine", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1"}
		},
		{"hutt_guards_base_2", -1258, 5837, -7297, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 300, 3,
			{"hutt_bomber_s01_tier1_tatooine", "hutt_bomber_s01_tier1", "hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1_tatooine", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1"}
		},
		{"hutt_guards_base_3", -112, 6021, -4741, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 300, 3,
			{"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1"}
		},
		{"hutt_guards_base_5", 1345, 3702, -5265, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 300, 3,
			{"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1"}
		},
		{"mining_guard_ships1", -6834, 625, 6305, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 300, 3,
			{"mining_guard_ship"}
		},
		{"mining_guard_ships2", -4732, -136, 5249, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 300, 3,
			{"mining_guard_ship", "mining_guard_ship_tatooine", "mining_guard_ship_tatooine"}
		},
		{"mining_guards3", -5377, 134, 4112, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 50, 100, 300, 3,
			{"mining_guard_ship"}
		},
		{"smuggler_asteroid_patrol_01", 3508, 913, 3105, SHIP_AI_RANDOM_PATROL, 60, 120, 2, 8, 100, 300, 3,
			{"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{"imp_base_patrol_01", -3793, 415, 3156, SHIP_AI_RANDOM_PATROL, 40, 90, 2, 8, 50, 320, 6,
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{"smuggler_mercenary_guard", -2613, 302, -2682, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 100, 100, 350, 3,
			{"mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_tyela_leader", "mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_guard_tier1", "mercenary_guard_tier1"}
		},
		{"valarian_mining_guard", -6523, -6375, -6388, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 100, 100, 350, 4,
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine", "valarian_bomber_tier1_tatooine"}
		},
		{"dest_rebel_base_smugglers", -1582, 2176, -3265, SHIP_AI_RANDOM_PATROL, 300, 420, 10, 100, 100, 350, 3,
			{"reb_z95_tier1", "reb_ywing_tier1", "reb_xwing_tier1"}
		},
		{"valarian_miners", -6619, -6330, -6458, SHIP_AI_RANDOM_PATROL, 300, 420, 10, 150, 100, 350, 2,
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{"tatooine_orbit_guard", 129, -1544, -3052, SHIP_AI_RANDOM_PATROL, 60, 120, 10, 100, 150, 400, 4,
			{"mos_eisley_police"}
		},
		{"stn_dantooine_lordmistress_01", 3200, 4320, -4322, SHIP_AI_RANDOM_PATROL, 30, 45, 10, 100, 50, 400, 1,
			{"lords_mistress_tier3"}
		},
		{"valarian_vs_hutts_2", -3985, 6949, 1071, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 20, 200, 400, 4,
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{"valarian_vs_hutts", -2113, 4695, 980, SHIP_AI_RANDOM_PATROL, 30, 60, 20, 50, 200, 400, 4,
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{"bestine_pirates_and_leader", -1586, -3178, 3478, SHIP_AI_RANDOM_PATROL, 180, 240, 10, 100, 100, 450, 1,
			{"bestine_pirate_leader_tier1"}
		},
		{"rebel_base_guard_1", 3440, -414, -2628, SHIP_AI_RANDOM_PATROL, 300, 420, 10, 40, 250, 500, 1,
			{"squad_xwing_standard_tier1"}
		},
		{"mining_operation_1", -6777, 5816, 2312, SHIP_AI_RANDOM_PATROL, 300, 420, 30, 100, 100, 600, 1,
			{"mining_guard_ship_tatooine", "mining_guard_ship_tatooine", "mining_guard_ship", "mining_guard_ship"}
		},
		{"bestine_pirates_planetoid_orbiters", 1873, -1771, 212, SHIP_AI_FIXED_PATROL, 60, 120, 10, 100, 3,
			5, {"bestine_pirates_planetoid_orbiters_00", "bestine_pirates_planetoid_orbiters_01", "bestine_pirates_planetoid_orbiters_02", "bestine_pirates_planetoid_orbiters_03", "bestine_pirates_planetoid_orbiters_04", "bestine_pirates_planetoid_orbiters_05", "bestine_pirates_planetoid_orbiters_06", "bestine_pirates_planetoid_orbiters_07"},
			{"bestine_pirate_tier1"}
		},
		{"valarian_mining_route", -6685, -6353, -6684, SHIP_AI_FIXED_PATROL, 120, 300, 10, 100, 3,
			5, {"valarian_mining_route_00", "valarian_mining_route_01", "valarian_mining_route_02", "valarian_mining_route_03", "valarian_mining_route_04", "valarian_mining_route_05"},
			{"valarian_bomber_tier1", "valarian_bomber_tier1", "valarian_starship_ace", "valarian_bomber_tier1", "valarian_bomber_tier1", "valarian_bomber_tier1", "valarian_bomber_tier1", "valarian_bomber_tier1_tatooine", "valarian_bomber_tier1_tatooine", "valarian_bomber_tier1_tatooine", "valarian_bomber_tier1_tatooine", "valarian_bomber_tier1_tatooine"}
		},
		{"hutt_attack_route_2", -2913, -2853, -2980, SHIP_AI_FIXED_PATROL, 300, 420, 10, 100, 1,
			5, {"hutt_attack_route_2_00", "hutt_attack_route_2_01", "hutt_attack_route_2_02", "hutt_attack_route_2_03", "hutt_attack_route_2_04", "hutt_attack_route_2_05", "hutt_attack_route_2_06", "hutt_attack_route_2_07", "hutt_attack_route_2_08", "hutt_attack_route_2_09"},
			{"squad_hutt_skiffs_tier1"}
		},
		{"hutt_attack_route_1", -2988, -2789, -2991, SHIP_AI_FIXED_PATROL, 300, 420, 10, 100, 1,
			5, {"hutt_attack_route_1_00", "hutt_attack_route_1_01", "hutt_attack_route_1_02", "hutt_attack_route_1_03", "hutt_attack_route_1_04", "hutt_attack_route_1_05"},
			{"squad_hutt_skiffs_tier1"}
		},
		{"valarian_mining_route_guard", -6738, -6346, -6707, SHIP_AI_FIXED_PATROL, 300, 420, 10, 100, 1,
			5, {"valarian_mining_route_guard_00", "valarian_mining_route_guard_01", "valarian_mining_route_guard_02", "valarian_mining_route_guard_03", "valarian_mining_route_guard_04", "valarian_mining_route_guard_05", "valarian_mining_route_guard_06"},
			{"squad_valarian_fighter_tier1"}
		},
		{"anchorhead_merchants", 3852, -3733, -866, SHIP_AI_FIXED_PATROL, 300, 420, 4, 12, 3,
			5, {"anchorhead_merchants_00", "anchorhead_merchants_01", "anchorhead_merchants_02", "anchorhead_merchants_03", "anchorhead_merchants_04", "anchorhead_merchants_05", "anchorhead_merchants_06", "anchorhead_merchants_07"},
			{"civspeeder", "civtransport", "freighterheavy_tier1", "freighterheavy_tier3_story", "freighterlight_tier1", "freighterlight_tier1", "freighterlight_tier1", "freightermedium_tier1", "freightermedium_tier1", "freighterheavy_tier3"}
		},
		{"dest_rebel_base_smugglers_1", -1402, 2401, -3682, SHIP_AI_FIXED_PATROL, 300, 420, 30, 120, 3,
			5, {"dest_rebel_base_smugglers_1_00", "dest_rebel_base_smugglers_1_01", "dest_rebel_base_smugglers_1_02", "dest_rebel_base_smugglers_1_03", "dest_rebel_base_smugglers_1_04", "dest_rebel_base_smugglers_1_05", "dest_rebel_base_smugglers_1_06", "dest_rebel_base_smugglers_1_07", "dest_rebel_base_smugglers_1_08", "dest_rebel_base_smugglers_1_09"},
			{"smuggler_freighterheavy_tier1", "smuggler_freighterlight_tier1", "smuggler_freightermedium_tier1"}
		},
		{"hutt_gunships_attack_1", 766, 5685, -4932, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 1,
			5, {"hutt_gunships_attack_1_00", "hutt_gunships_attack_1_01", "hutt_gunships_attack_1_02", "hutt_gunships_attack_1_03", "hutt_gunships_attack_1_04", "hutt_gunships_attack_1_05", "hutt_gunships_attack_1_06", "hutt_gunships_attack_1_07", "hutt_gunships_attack_1_08", "hutt_gunships_attack_1_09"},
			{"hutt_yt1300_tier1"}
		},
		{"hutt_gunship_attack_2", 1262, 6392, -5250, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 1,
			5, {"hutt_gunship_attack_2_00", "hutt_gunship_attack_2_01", "hutt_gunship_attack_2_02", "hutt_gunship_attack_2_03", "hutt_gunship_attack_2_04", "hutt_gunship_attack_2_05", "hutt_gunship_attack_2_06", "hutt_gunship_attack_2_07", "hutt_gunship_attack_2_08", "hutt_gunship_attack_2_09", "hutt_gunship_attack_2_10", "hutt_gunship_attack_2_11", "hutt_gunship_attack_2_12", "hutt_gunship_attack_2_13"},
			{"hutt_yt1300_tier1"}
		},
		{"blacksun_guard_1", 7152, 937, 6636, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 6,
			5, {"blacksun_guard_1_00", "blacksun_guard_1_01", "blacksun_guard_1_02", "blacksun_guard_1_03", "blacksun_guard_1_04", "blacksun_guard_1_05", "blacksun_guard_1_06", "blacksun_guard_1_07", "blacksun_guard_1_08", "blacksun_guard_1_09", "blacksun_guard_1_10"},
			{"blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2_tatooine", "blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s01_tier2_tatooine", "blacksun_marauder_tier1"}
		},
		{"valarian_to_spine_1", -7093, -6497, -6272, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 5,
			5, {"valarian_to_spine_1_00", "valarian_to_spine_1_01", "valarian_to_spine_1_02", "valarian_to_spine_1_03", "valarian_to_spine_1_04", "valarian_to_spine_1_05", "valarian_to_spine_1_06", "valarian_to_spine_1_07", "valarian_to_spine_1_08"},
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{"bestine_pirate_base_1", 6052, 5659, 6541, SHIP_AI_FIXED_PATROL, 60, 120, 10, 20, 6,
			5, {"bestine_pirate_base_1_00", "bestine_pirate_base_1_01", "bestine_pirate_base_1_02", "bestine_pirate_base_1_03", "bestine_pirate_base_1_04", "bestine_pirate_base_1_05", "bestine_pirate_base_1_06", "bestine_pirate_base_1_07"},
			{"bestine_pirate_tier1"}
		},
		{"station_to_mining_1", 1635, -5599, 2580, SHIP_AI_FIXED_PATROL, 120, 300, 10, 20, 3,
			5, {"station_to_mining_1_00", "station_to_mining_1_01", "station_to_mining_1_02", "station_to_mining_1_03", "station_to_mining_1_04"},
			{"freighterheavy_mining", "freighterlight_mining", "freightermedium_mining"}
		},
		{"hutt_squad_1", 1196, 5760, -4017, SHIP_AI_FIXED_PATROL, 1200, 3600, 10, 20, 1,
			5, {"hutt_squad_1_00", "hutt_squad_1_01", "hutt_squad_1_02", "hutt_squad_1_03", "hutt_squad_1_04", "hutt_squad_1_05"},
			{"squad_hutt_tatooine_1"}
		},
		{"tatooine_station_passenger_1", 1935, -5859, 1605, SHIP_AI_FIXED_PATROL, 30, 60, 10, 20, 1,
			5, {"tatooine_station_passenger_1_00", "tatooine_station_passenger_1_01", "tatooine_station_passenger_1_02", "tatooine_station_passenger_1_03"},
			{"civilian_science_transport_tier1"}
		},
		{"imperial_pirate_patrol_1", -3194, 1005, -3259, SHIP_AI_FIXED_PATROL, 120, 90, 30, 240, 9,
			5, {"imperial_pirate_patrol_1_00", "imperial_pirate_patrol_1_01", "imperial_pirate_patrol_1_02", "imperial_pirate_patrol_1_03", "imperial_pirate_patrol_1_04", "imperial_pirate_patrol_1_05", "imperial_pirate_patrol_1_06", "imperial_pirate_patrol_1_07", "imperial_pirate_patrol_1_08", "imperial_pirate_patrol_1_09", "imperial_pirate_patrol_1_10", "imperial_pirate_patrol_1_11", "imperial_pirate_patrol_1_12", "imperial_pirate_patrol_1_13", "imperial_pirate_patrol_1_14", "imperial_pirate_patrol_1_15", "imperial_pirate_patrol_1_16", "imperial_pirate_patrol_1_17", "imperial_pirate_patrol_1_18", "imperial_pirate_patrol_1_19", "imperial_pirate_patrol_1_20", "imperial_pirate_patrol_1_21"},
			{"imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1", "imperial_cpt_starfire"}
		},
		{"rebel_convoy_01", 3311, -194, -2736, SHIP_AI_FIXED_PATROL, 60, 120, 2, 3, 3,
			5, {"rebel_convoy_01_00", "rebel_convoy_01_01", "rebel_convoy_01_02", "rebel_convoy_01_03", "rebel_convoy_01_04", "rebel_convoy_01_05", "rebel_convoy_01_06", "rebel_convoy_01_07", "rebel_convoy_01_08", "rebel_convoy_01_09", "rebel_convoy_01_10", "rebel_convoy_01_11"},
			{"freighterlight_rebel", "reb_xwing_tier1", "reb_ywing_tier1", "reb_xwing_tier1_tatooine", "reb_ywing_tier1_tatooine", "reb_xwing_tier1", "reb_ywing_tier1"}
		},
		{"valarian_spine_patrol_1", -2945, -6985, -6764, SHIP_AI_FIXED_PATROL, 60, 120, 10, 30, 15,
			5, {"valarian_spine_patrol_1_00", "valarian_spine_patrol_1_01", "valarian_spine_patrol_1_02", "valarian_spine_patrol_1_03", "valarian_spine_patrol_1_04", "valarian_spine_patrol_1_05", "valarian_spine_patrol_1_06", "valarian_spine_patrol_1_07", "valarian_spine_patrol_1_08", "valarian_spine_patrol_1_09", "valarian_spine_patrol_1_10"},
			{"valarian_bomber_tier1", "valarian_bomber_tier1_tatooine"}
		},
		{"valarian_hutt_attack_1", -2004, 6630, 247, SHIP_AI_FIXED_PATROL, 120, 180, 10, 30, 4,
			5, {"valarian_hutt_attack_1_00", "valarian_hutt_attack_1_01", "valarian_hutt_attack_1_02", "valarian_hutt_attack_1_03", "valarian_hutt_attack_1_04", "valarian_hutt_attack_1_05", "valarian_hutt_attack_1_06", "valarian_hutt_attack_1_07", "valarian_hutt_attack_1_08", "valarian_hutt_attack_1_09", "valarian_hutt_attack_1_10"},
			{"valarian_gunship_tier1", "valarian_gunship_tier1_tatooine"}
		},
		{"station_to_smugglers", 3939, -5611, 3421, SHIP_AI_FIXED_PATROL, 120, 300, 10, 30, 3,
			5, {"station_to_smugglers_00", "station_to_smugglers_01", "station_to_smugglers_02"},
			{"smuggler_freighterlight_tier3", "smuggler_freightermedium_tier3"}
		},
		{"tatooine_station_freighter_route2", 2157, -2993, 5457, SHIP_AI_FIXED_PATROL, 30, 60, 10, 30, 1,
			5, {"tatooine_station_freighter_route2_00", "tatooine_station_freighter_route2_01"},
			{"freighterheavy_tier1", "freighterlight_tier1", "freightermedium_tier1"}
		},
		{"bestine_imperial_commerce_support", -2062, 830, 1065, SHIP_AI_FIXED_PATROL, 60, 120, 2, 32, 4,
			5, {"bestine_imperial_commerce_support_00", "bestine_imperial_commerce_support_01", "bestine_imperial_commerce_support_02", "bestine_imperial_commerce_support_03", "bestine_imperial_commerce_support_04", "bestine_imperial_commerce_support_05", "bestine_imperial_commerce_support_06", "bestine_imperial_commerce_support_07", "bestine_imperial_commerce_support_08", "bestine_imperial_commerce_support_09", "bestine_imperial_commerce_support_10", "bestine_imperial_commerce_support_11", "bestine_imperial_commerce_support_12", "bestine_imperial_commerce_support_13", "bestine_imperial_commerce_support_14", "bestine_imperial_commerce_support_15", "bestine_imperial_commerce_support_16", "bestine_imperial_commerce_support_17", "bestine_imperial_commerce_support_18", "bestine_imperial_commerce_support_19", "bestine_imperial_commerce_support_20", "bestine_imperial_commerce_support_21", "bestine_imperial_commerce_support_22", "bestine_imperial_commerce_support_23", "bestine_imperial_commerce_support_24", "bestine_imperial_commerce_support_25", "bestine_imperial_commerce_support_26", "bestine_imperial_commerce_support_27", "bestine_imperial_commerce_support_28", "bestine_imperial_commerce_support_29", "bestine_imperial_commerce_support_30"},
			{"imp_tie_bomber_tier1", "imp_tie_bomber_tier1_tatooine", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1_tatooine", "imp_tie_advanced_tier1", "imp_tie_aggressor_tier1", "imp_tie_interceptor_tier1", "imp_tie_oppressor_tier1"}
		},
		{"pirate_attack_route", -562, 2682, -445, SHIP_AI_FIXED_PATROL, 60, 120, 5, 32, 6,
			5, {"pirate_attack_route_00", "pirate_attack_route_01", "pirate_attack_route_02", "pirate_attack_route_03", "pirate_attack_route_04", "pirate_attack_route_05", "pirate_attack_route_06", "pirate_attack_route_07", "pirate_attack_route_08"},
			{"blacksun_ace_s04_tier1", "blacksun_aggressor_tier1", "blacksun_bomber_ace_s04_tier1", "blacksun_bomber_s01_tier1", "blacksun_dark_eclipse_tier1", "blacksun_fighter_s01_tier1", "blacksun_gunship_tier1", "blacksun_marauder_tier1", "blacksun_vehement_tier1"}
		},
		{"bestine_commerce_02", 2289, 1016, -2981, SHIP_AI_FIXED_PATROL, 300, 420, 24, 48, 3,
			5, {"bestine_commerce_02_00", "bestine_commerce_02_01", "bestine_commerce_02_02", "bestine_commerce_02_03", "bestine_commerce_02_04", "bestine_commerce_02_05", "bestine_commerce_02_06", "bestine_commerce_02_07", "bestine_commerce_02_08", "bestine_commerce_02_09", "bestine_commerce_02_10", "bestine_commerce_02_11", "bestine_commerce_02_12", "bestine_commerce_02_13", "bestine_commerce_02_14", "bestine_commerce_02_15", "bestine_commerce_02_16", "bestine_commerce_02_17", "bestine_commerce_02_18", "bestine_commerce_02_19", "bestine_commerce_02_20", "bestine_commerce_02_21", "bestine_commerce_02_22", "bestine_commerce_02_23"},
			{"freighterheavy_tier3_story", "freighterheavy_tier3", "freighterheavy_tier1", "freighterlight_tier1", "freighterlight_tier1", "freightermedium_tier1", "freightermedium_tier1"}
		},
		{"smuggler_base_defense_01", 3053, -45, 3653, SHIP_AI_FIXED_PATROL, 60, 120, 4, 5, 4,
			5, {"smuggler_base_defense_01_00", "smuggler_base_defense_01_01", "smuggler_base_defense_01_02", "smuggler_base_defense_01_03", "smuggler_base_defense_01_04", "smuggler_base_defense_01_05", "smuggler_base_defense_01_06", "smuggler_base_defense_01_07", "smuggler_base_defense_01_08"},
			{"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{"hutt_base_asteroid_patrol_1", 1558, 4845, -5452, SHIP_AI_FIXED_PATROL, 60, 120, 10, 50, 5,
			5, {"hutt_base_asteroid_patrol_1_00", "hutt_base_asteroid_patrol_1_01", "hutt_base_asteroid_patrol_1_02", "hutt_base_asteroid_patrol_1_03", "hutt_base_asteroid_patrol_1_04", "hutt_base_asteroid_patrol_1_05"},
			{"hutt_bomber_s01_tier1_tatooine", "hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1", "hutt_fighter_s01_tier1_tatooine", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{"mos_eisley_police_1", 271, -5507, -695, SHIP_AI_FIXED_PATROL, 60, 120, 10, 50, 5,
			5, {"mos_eisley_police_1_00", "mos_eisley_police_1_01", "mos_eisley_police_1_02", "mos_eisley_police_1_03", "mos_eisley_police_1_04", "mos_eisley_police_1_05", "mos_eisley_police_1_06"},
			{"mos_eisley_police"}
		},
		{"merchants_to_station", 3321, -3327, -406, SHIP_AI_FIXED_PATROL, 120, 300, 10, 50, 3,
			5, {"merchants_to_station_00", "merchants_to_station_01", "merchants_to_station_02"},
			{"freighterlight_tier1", "mercenary_courier_tier1", "mercenary_guard_tier1"}
		},
		{"miners_to_station_1", -5508, -327, 6214, SHIP_AI_FIXED_PATROL, 300, 420, 10, 50, 4,
			5, {"miners_to_station_1_00", "miners_to_station_1_01", "miners_to_station_1_02", "miners_to_station_1_03", "miners_to_station_1_04", "miners_to_station_1_05", "miners_to_station_1_06"},
			{"freighterheavy_mining", "freighterlight_mining", "freightermedium_mining", "freighterheavy_mining"}
		},
		{"tatooine_station_freighter_route_1", 2505, -1792, 7529, SHIP_AI_FIXED_PATROL, 30, 60, 10, 50, 1,
			5, {"tatooine_station_freighter_route_1_00", "tatooine_station_freighter_route_1_01", "tatooine_station_freighter_route_1_02"},
			{"freighterheavy_tier1", "freighterlight_tier1", "freightermedium_tier1"}
		},
		{"po_mcannon_spawner", -1135, -6847, -5191, SHIP_AI_FIXED_PATROL, 300, 600, 10, 50, 1,
			5, {"po_mcannon_spawner_00", "po_mcannon_spawner_01", "po_mcannon_spawner_02", "po_mcannon_spawner_03", "po_mcannon_spawner_04"},
			{"squad_po_mcannon_tier2"}
		},
		{"vsin_starbomber_spawner", 6476, 3999, 2460, SHIP_AI_FIXED_PATROL, 300, 600, 10, 50, 1,
			5, {"vsin_starbomber_spawner_00", "vsin_starbomber_spawner_01", "vsin_starbomber_spawner_02", "vsin_starbomber_spawner_03", "vsin_starbomber_spawner_04"},
			{"squad_vsin_starbomber_tier2"}
		},
		{"imperial_squad_1", -4099, -602, 4240, SHIP_AI_FIXED_PATROL, 40, 90, 10, 50, 1,
			5, {"imperial_squad_1_00", "imperial_squad_1_01", "imperial_squad_1_02", "imperial_squad_1_03", "imperial_squad_1_04", "imperial_squad_1_05"},
			{"squad_imperial_tatooine_1"}
		},
		{"imperial_squad_3", -3856, -2920, -3319, SHIP_AI_FIXED_PATROL, 40, 90, 10, 50, 1,
			5, {"imperial_squad_3_00", "imperial_squad_3_01", "imperial_squad_3_02", "imperial_squad_3_03", "imperial_squad_3_04", "imperial_squad_3_05"},
			{"squad_imperial_tatooine_3"}
		},
		{"imperial_squad_4", 514, 1767, 1878, SHIP_AI_FIXED_PATROL, 40, 90, 10, 50, 1,
			5, {"imperial_squad_4_00", "imperial_squad_4_01", "imperial_squad_4_02", "imperial_squad_4_03", "imperial_squad_4_04", "imperial_squad_4_05"},
			{"squad_imperial_tatooine_4"}
		},
		{"imperial_squad_2", 4526, 1609, -225, SHIP_AI_FIXED_PATROL, 40, 90, 10, 50, 1,
			5, {"imperial_squad_2_00", "imperial_squad_2_01", "imperial_squad_2_02", "imperial_squad_2_03", "imperial_squad_2_04", "imperial_squad_2_05", "imperial_squad_2_06"},
			{"squad_imperial_tatooine_2"}
		},
		{"bestine_commerce_spawner", 2203, 976, -2239, SHIP_AI_FIXED_PATROL, 300, 420, 12, 64, 3,
			5, {"bestine_commerce_spawner_00", "bestine_commerce_spawner_01", "bestine_commerce_spawner_02", "bestine_commerce_spawner_03", "bestine_commerce_spawner_04", "bestine_commerce_spawner_05", "bestine_commerce_spawner_06", "bestine_commerce_spawner_07", "bestine_commerce_spawner_08", "bestine_commerce_spawner_09", "bestine_commerce_spawner_10", "bestine_commerce_spawner_11", "bestine_commerce_spawner_12", "bestine_commerce_spawner_13", "bestine_commerce_spawner_14", "bestine_commerce_spawner_15"},
			{"freighterheavy_tier3_story", "freighterheavy_tier3", "freighterheavy_tier3", "freighterheavy_tier1", "freighterheavy_tier2", "freighterlight_tier1", "freighterlight_tier1", "freighterlight_tier2", "freightermedium_tier1", "freightermedium_tier1", "freightermedium_tier2"}
		},
		{"anchorhead_supply_route", -549, -164, -2941, SHIP_AI_FIXED_PATROL, 300, 420, 32, 64, 3,
			5, {"anchorhead_supply_route_00", "anchorhead_supply_route_01", "anchorhead_supply_route_02", "anchorhead_supply_route_03"},
			{"freighterheavy_tier3_story", "freighterheavy_tier1", "freighterheavy_tier3", "freighterlight_tier1", "freighterlight_tier1", "freightermedium_tier1", "freightermedium_tier1"}
		},
		{"smugglers_to_station", -1770, -911, -1815, SHIP_AI_FIXED_PATROL, 120, 300, 10, 70, 4,
			5, {"smugglers_to_station_00", "smugglers_to_station_01", "smugglers_to_station_02", "smugglers_to_station_03"},
			{"freighterheavy_tier3_story", "freighterheavy_tier3_story", "smuggler_freighterlight_tier3", "smuggler_freightermedium_tier3"}
		},
		{"smuggler_asteroid_patrol_02", 3535, -793, 4323, SHIP_AI_FIXED_PATROL, 60, 120, 2, 8, 4,
			5, {"smuggler_asteroid_patrol_02_00", "smuggler_asteroid_patrol_02_01", "smuggler_asteroid_patrol_02_02", "smuggler_asteroid_patrol_02_03", "smuggler_asteroid_patrol_02_04", "smuggler_asteroid_patrol_02_05", "smuggler_asteroid_patrol_02_06", "smuggler_asteroid_patrol_02_07", "smuggler_asteroid_patrol_02_08"},
			{"hutt_bomber_s01_tier1", "hutt_fighter_s01_tier1", "hutt_pirate_s01_tier1"}
		},
		{"rebel_smuggler_escape", 2708, 2359, -1251, SHIP_AI_FIXED_PATROL, 60, 120, 10, 80, 1,
			5, {"rebel_smuggler_escape_00", "rebel_smuggler_escape_01", "rebel_smuggler_escape_02", "rebel_smuggler_escape_03"},
			{"rebel_smuggler"}
		},
		{"mining_route_1", -6912, 6077, 2586, SHIP_AI_FIXED_PATROL, 300, 420, 30, 80, 3,
			5, {"mining_route_1_00", "mining_route_1_01", "mining_route_1_02", "mining_route_1_03", "mining_route_1_04", "mining_route_1_05", "mining_route_1_06", "mining_route_1_07"},
			{"freighterheavy_mining", "freighterheavy_tier3_story", "freighterheavy_tier3_story", "freighterlight_mining", "freightermedium_mining"}
		},
	},
}

registerScreenPlay("SpaceTatooineSpawner", true)

function SpaceTatooineSpawner:start()
	if (not isZoneEnabled(self.spaceZone)) then
		return
	end

	self:populateSpawns()
end
