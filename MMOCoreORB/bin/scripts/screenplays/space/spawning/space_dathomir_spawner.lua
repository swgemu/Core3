SpaceDathomirSpawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceDathomirSpawner",

	spaceZone = "space_dathomir",

	shipSpawns = {
		{"imperial_generator_lookout_1", 1365, -6750, 7020, SHIP_AI_RANDOM_PATROL, 100, 300, 20, 40, 70, 340, 6,
			{"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_advanced_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"bh_target_escort_elite_01", -1835, -33, 3647, SHIP_AI_RANDOM_PATROL, 300, 420, 4, 24, 320, 320, 2,
			{"squad_dath_deathmarked_mercenary"}
		},
		{"warlord_ship_to_imp", -2700, -6358, 1958, SHIP_AI_FIXED_PATROL, 420, 620, 10, 20, 6,
			5, {"warlord_ship_to_imp_00", "warlord_ship_to_imp_01", "warlord_ship_to_imp_02", "warlord_ship_to_imp_03", "warlord_ship_to_imp_04", "warlord_ship_to_imp_05", "warlord_ship_to_imp_06", "warlord_ship_to_imp_07", "warlord_ship_to_imp_08", "warlord_ship_to_imp_09", "warlord_ship_to_imp_10", "warlord_ship_to_imp_11", "warlord_ship_to_imp_12", "warlord_ship_to_imp_13", "warlord_ship_to_imp_14", "warlord_ship_to_imp_15", "warlord_ship_to_imp_16", "warlord_ship_to_imp_17", "warlord_ship_to_imp_18", "warlord_ship_to_imp_19", "warlord_ship_to_imp_20", "warlord_ship_to_imp_21", "warlord_ship_to_imp_22", "warlord_ship_to_imp_23", "warlord_ship_to_imp_24", "warlord_ship_to_imp_25", "warlord_ship_to_imp_26", "warlord_ship_to_imp_27", "warlord_ship_to_imp_28", "warlord_ship_to_imp_29", "warlord_ship_to_imp_30", "warlord_ship_to_imp_31", "warlord_ship_to_imp_32"},
			{"blacksun_dark_eclipse_tier5", "blacksun_bomber_s03_tier5", "blacksun_aggressor_tier5", "blacksun_ace_s04_tier5", "blacksun_fighter_s01_tier5"}
		},
		{"rebel_attackers_are_cool", -2448, -1160, 6868, SHIP_AI_FIXED_PATROL, 3600, 8200, 5, 10, 1,
			5, {"rebel_attackers_are_cool_00", "rebel_attackers_are_cool_01", "rebel_attackers_are_cool_02", "rebel_attackers_are_cool_03", "rebel_attackers_are_cool_04", "rebel_attackers_are_cool_05", "rebel_attackers_are_cool_06"},
			{"squad_corvette_blockade_run"}
		},
		{"imperial_beacon_lookout_1", -2974, -3082, 2835, SHIP_AI_RANDOM_PATROL, 120, 300, 20, 40, 50, 320, 3,
			{"imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"random_imperial_dudes_1", 272, -6947, -6161, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 30, 50, 320, 6,
			{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"random_imperial_dudes", -861, -6791, -7342, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 30, 50, 320, 6,
			{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_fighter_tier4"}
		},
		{"generator_imperial_defense_2", -4504, 2537, 4026, SHIP_AI_RANDOM_PATROL, 180, 300, 30, 40, 60, 320, 3,
			{"imp_tie_aggressor_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"}
		},
		{"generator_imperial_defense_1", -4549, 3176, 4114, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 40, 60, 320, 3,
			{"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_oppressor_tier4"}
		},
		{"tier3_privateer_witchblood_inspect_01", 6228, -6411, -5797, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 100, 10, 300, 3,
			{"dath_witchblood_clan_soldier_tier3"}
		},
		{"imperial_station_guard_2", 3123, -5170, -4160, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 100, 100, 300, 2,
			{"squad_tie_standard_ace"}
		},
		{"imperial_station_guard_1", 5228, -4847, -3716, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 100, 100, 300, 2,
			{"squad_tie_standard_ace"}
		},
		{"imperial_generator_defense_5", 4350, -5175, -7118, SHIP_AI_RANDOM_PATROL, 180, 300, 5, 10, 90, 300, 6,
			{"tieaggressor_ace_tier4", "tieadvanced_inquisitor_tier4", "tieadvanced_ace_tier4", "tieoppressor_ace_tier4"}
		},
		{"imperial_uber_fleet_1", 5874, -5465, -7280, SHIP_AI_FIXED_PATROL, 7200, 8200, 5, 10, 1,
			5, {"imperial_uber_fleet_1_00", "imperial_uber_fleet_1_01", "imperial_uber_fleet_1_02", "imperial_uber_fleet_1_03", "imperial_uber_fleet_1_04", "imperial_uber_fleet_1_05"},
			{"squad_imperial_fleet"}
		},
		{"imperial_generator_lookout_4", 6234, -1952, -7218, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 70, 340, 6,
			{"imp_tie_bomber_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"naboo_imperial_tier4_inspect1_spawner", 7606, 4673, -1681, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 30, 50, 140, 1,
			{"crystal_smuggler_yt1300_tier4"}
		},
		{"imperial_secret_station_guard_2", 6338, 6281, -6527, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 100, 100, 300, 1,
			{"squad_tie_mix_ace"}
		},
		{"imp_gunboat_1", 6086, 6130, -6737, SHIP_AI_FIXED_PATROL, 300, 420, 5, 10, 1,
			5, {"imp_gunboat_1_00", "imp_gunboat_1_01", "imp_gunboat_1_02", "imp_gunboat_1_03", "imp_gunboat_1_04", "imp_gunboat_1_05", "imp_gunboat_1_06", "imp_gunboat_1_07", "imp_gunboat_1_08", "imp_gunboat_1_09", "imp_gunboat_1_10", "imp_gunboat_1_11", "imp_gunboat_1_12", "imp_gunboat_1_13", "imp_gunboat_1_14", "imp_gunboat_1_15", "imp_gunboat_1_16", "imp_gunboat_1_17", "imp_gunboat_1_18", "imp_gunboat_1_19", "imp_gunboat_1_20", "imp_gunboat_1_21", "imp_gunboat_1_22", "imp_gunboat_1_23", "imp_gunboat_1_24"},
			{"imp_imperial_gunboat_tier4"}
		},
		{"imperial_secret_station_guard_1", 5531, 5803, -5911, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 100, 100, 300, 1,
			{"squad_tie_mix_ace"}
		},
		{"imperial_secret_station_guard_3", 6309, 5641, -6127, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 100, 100, 300, 1,
			{"squad_tie_advanced_ace"}
		},
		{"imperial_fleet_to_imp", 5712, 5708, -6515, SHIP_AI_FIXED_PATROL, 300, 420, 10, 30, 1,
			5, {"imperial_fleet_to_imp_00", "imperial_fleet_to_imp_01", "imperial_fleet_to_imp_02", "imperial_fleet_to_imp_03", "imperial_fleet_to_imp_04", "imperial_fleet_to_imp_05", "imperial_fleet_to_imp_06", "imperial_fleet_to_imp_07", "imperial_fleet_to_imp_08", "imperial_fleet_to_imp_09", "imperial_fleet_to_imp_10", "imperial_fleet_to_imp_11", "imperial_fleet_to_imp_12", "imperial_fleet_to_imp_13", "imperial_fleet_to_imp_14", "imperial_fleet_to_imp_15", "imperial_fleet_to_imp_16", "imperial_fleet_to_imp_17", "imperial_fleet_to_imp_18", "imperial_fleet_to_imp_19", "imperial_fleet_to_imp_20", "imperial_fleet_to_imp_21"},
			{"squad_imperial_fleet"}
		},
		{"tatooine_rebel_tier3_2_suspect_1", 5585, 4809, -2403, SHIP_AI_FIXED_PATROL, 30, 120, 1, 100, 6,
			5, {"tatooine_rebel_tier3_2_suspect_1_00", "tatooine_rebel_tier3_2_suspect_1_01", "tatooine_rebel_tier3_2_suspect_1_02", "tatooine_rebel_tier3_2_suspect_1_03"},
			{"tatooine_tier3_2_inspect_awing", "tatooine_tier3_2_inspect_bwing", "tatooine_tier3_2_inspect_xwing", "tatooine_tier3_2_inspect_ywing", "reb_awing_tier4", "reb_bwing_tier4"}
		},
		{"tatooine_rebel_tier3_2_suspect_2", 4719, 5053, -3111, SHIP_AI_FIXED_PATROL, 30, 120, 1, 100, 6,
			5, {"tatooine_rebel_tier3_2_suspect_2_00", "tatooine_rebel_tier3_2_suspect_2_01", "tatooine_rebel_tier3_2_suspect_2_02", "tatooine_rebel_tier3_2_suspect_2_03", "tatooine_rebel_tier3_2_suspect_2_04", "tatooine_rebel_tier3_2_suspect_2_05"},
			{"reb_awing_tier4", "reb_bwing_tier4", "tatooine_tier3_2_inspect_awing", "tatooine_tier3_2_inspect_bwing", "tatooine_tier3_2_inspect_xwing", "tatooine_tier3_2_inspect_ywing", "tatooine_tier3_2_inspect_ywing"}
		},
		{"naboo_imperial_tier3_inspect3escort_spawner", 2021, 4211, -3441, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 50, 100, 300, 5,
			{"xwing_ace"}
		},
		{"naboo_imperial_tier3_inspect3_spawner", 2005, 4299, -3566, SHIP_AI_RANDOM_PATROL, 30, 60, 10, 50, 100, 300, 1,
			{"rebel_spyfreighter_tier3"}
		},
		{"corellia_imperial_tier4_inspect3", -1184, -670, -4776, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 40, 70, 240, 1,
			{"velocity_commander_tier4"}
		},
		{"generator_coynite_defense_2", -110, -2251, 6620, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 40, 60, 320, 3,
			{"coynite_merc_captain_tier5", "coynite_merc_pulsar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_quasar_tier4"}
		},
		{"generator_coynite_defense_1", -234, -1620, 6655, SHIP_AI_RANDOM_PATROL, 180, 300, 10, 40, 60, 320, 3,
			{"coynite_merc_neutron_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_pulsar_boss", "coynite_merc_quasar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_quasar_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_pulsar_tier4", "coynite_merc_neutron_tier4", "coynite_merc_neutron_tier4", "coynite_merc_neutron_tier4"}
		},
		{"imperial_generator_defense_4", 2244, -1295, 7106, SHIP_AI_RANDOM_PATROL, 180, 300, 20, 30, 60, 320, 6,
			{"imp_tie_aggressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_advanced_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"}
		},
		{"imperial_generator_defense_3", 2221, -760, 7145, SHIP_AI_RANDOM_PATROL, 120, 300, 20, 40, 60, 320, 6,
			{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"}
		},
		{"generator_imperial_defense_4", 1960, -1036, 7451, SHIP_AI_RANDOM_PATROL, 300, 400, 20, 40, 60, 120, 5,
			{"imp_tie_bomber_tier4", "imp_tie_fighter_tier4"}
		},
		{"hiddendaggers_route_1", -837, 4833, 1180, SHIP_AI_FIXED_PATROL, 180, 300, 50, 100, 4,
			5, {"hiddendaggers_route_1_00", "hiddendaggers_route_1_01", "hiddendaggers_route_1_02", "hiddendaggers_route_1_03", "hiddendaggers_route_1_04", "hiddendaggers_route_1_05", "hiddendaggers_route_1_06", "hiddendaggers_route_1_07", "hiddendaggers_route_1_08", "hiddendaggers_route_1_09", "hiddendaggers_route_1_10", "hiddendaggers_route_1_11", "hiddendaggers_route_1_12", "hiddendaggers_route_1_13", "hiddendaggers_route_1_14", "hiddendaggers_route_1_15", "hiddendaggers_route_1_16", "hiddendaggers_route_1_17", "hiddendaggers_route_1_18", "hiddendaggers_route_1_19", "hiddendaggers_route_1_20", "hiddendaggers_route_1_21", "hiddendaggers_route_1_22", "hiddendaggers_route_1_23", "hiddendaggers_route_1_24", "hiddendaggers_route_1_25", "hiddendaggers_route_1_26", "hiddendaggers_route_1_27", "hiddendaggers_route_1_28", "hiddendaggers_route_1_29", "hiddendaggers_route_1_30", "hiddendaggers_route_1_31", "hiddendaggers_route_1_32", "hiddendaggers_route_1_33", "hiddendaggers_route_1_34", "hiddendaggers_route_1_35", "hiddendaggers_route_1_36", "hiddendaggers_route_1_37"},
			{"hidden_daggers_slayer_tier4", "hidden_daggers_killer_tier4", "hidden_daggers_enforcer_tier4", "hidden_daggers_gunship_tier5"}
		},
		{"bh_target_escort_01", 2849, 1098, 996, SHIP_AI_RANDOM_PATROL, 300, 420, 6, 18, 210, 420, 1,
			{"squad_dath_witchblood_clan"}
		},
		{"bh_target_escort_elite_02", 830, 651, 1000, SHIP_AI_RANDOM_PATROL, 300, 420, 4, 26, 80, 310, 1,
			{"squad_dath_freelance_killer"}
		},
		{"tier3_privateer_witchblood_inspect_02", -808, -379, 1892, SHIP_AI_FIXED_PATROL, 180, 300, 14, 24, 4,
			5, {"tier3_privateer_witchblood_inspect_02_00", "tier3_privateer_witchblood_inspect_02_01", "tier3_privateer_witchblood_inspect_02_02", "tier3_privateer_witchblood_inspect_02_03", "tier3_privateer_witchblood_inspect_02_04", "tier3_privateer_witchblood_inspect_02_05", "tier3_privateer_witchblood_inspect_02_06"},
			{"dath_witchblood_clan_soldier_tier4", "dath_witchblood_clan_punisher_tier3"}
		},
		{"corellia_privateer_tier3_2_inspect", -50, 1375, 1510, SHIP_AI_RANDOM_PATROL, 45, 60, 10, 120, 200, 500, 1,
			{"civshuttle_cor_tier3_pilot_capture"}
		},
		{"corellia_privateer_tier4_leg_2_destroy_two", 684, -2863, -1310, SHIP_AI_RANDOM_PATROL, 180, 300, 30, 60, 80, 290, 3,
			{"hidden_daggers_killer_tier4", "hidden_daggers_slayer_tier4", "hidden_daggers_nebula_stalker_tier5"}
		},
		{"imperial_squad_patrol_1", -129, -732, 12, SHIP_AI_FIXED_PATROL, 3600, 10800, 5, 10, 3,
			5, {"imperial_squad_patrol_1_00", "imperial_squad_patrol_1_01", "imperial_squad_patrol_1_02", "imperial_squad_patrol_1_03", "imperial_squad_patrol_1_04", "imperial_squad_patrol_1_05", "imperial_squad_patrol_1_06"},
			{"squad_tie_oppressor_ace", "imp_decimator_boss"}
		},
		{"engineers_to_base_1", 40, -687, -5, SHIP_AI_FIXED_PATROL, 180, 300, 10, 20, 4,
			5, {"engineers_to_base_1_00", "engineers_to_base_1_01", "engineers_to_base_1_02", "engineers_to_base_1_03", "engineers_to_base_1_04"},
			{"imperial_engineer", "tieinterceptor_ace_tier4"}
		},
		{"imperial_generator_defense_2", -7086, 2295, -760, SHIP_AI_RANDOM_PATROL, 180, 300, 5, 10, 90, 380, 6,
			{"tieaggressor_ace_tier4", "tieadvanced_ace_tier4", "tieaggressor_inquisitor_tier3", "tiebomber_ace_tier4", "tiedecimator_ace_tier4", "tieinterceptor_ace_tier4"}
		},
		{"station_police_1", -5537, 2258, -3028, SHIP_AI_RANDOM_PATROL, 180, 300, 5, 10, 90, 300, 3,
			{"corsec_fighter_tier4"}
		},
		{"station_police_patrol", -6146, 2677, -4616, SHIP_AI_FIXED_PATROL, 300, 420, 5, 10, 4,
			5, {"station_police_patrol_00", "station_police_patrol_01", "station_police_patrol_02", "station_police_patrol_03", "station_police_patrol_04", "station_police_patrol_05", "station_police_patrol_06", "station_police_patrol_07", "station_police_patrol_08", "station_police_patrol_09", "station_police_patrol_10"},
			{"corsec_fighter_tier4", "corsec_lancer_tier4", "corsec_gunship_tier4", "corsec_fighter_tier4", "corsec_fighter_tier4", "corsec_fighter_tier4", "corsec_lancer_tier4", "corsec_lancer_tier4", "corsec_lancer_tier4"}
		},
		{"imperial_generator_defense_1", -7392, 2059, -1933, SHIP_AI_RANDOM_PATROL, 180, 300, 5, 10, 90, 380, 6,
			{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_oppressor_tier4", "tieinterceptor_ace_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"}
		},
		{"station_police_2", -5190, 2048, -1933, SHIP_AI_RANDOM_PATROL, 180, 300, 5, 10, 90, 300, 3,
			{"corsec_fighter_tier4"}
		},
		{"station_traders_to_generator", -7168, 2679, -3628, SHIP_AI_FIXED_PATROL, 300, 420, 5, 10, 2,
			5, {"station_traders_to_generator_00", "station_traders_to_generator_01"},
			{"freighterheavy", "freighterlight_mining", "freighterheavy_tier3_story", "freighterheavy_tier3_story"}
		},
		{"rebel_defenders_2", 5131, 242, -512, SHIP_AI_RANDOM_PATROL, 180, 300, 5, 10, 90, 380, 6,
			{"reb_bwing_tier4", "reb_awing_tier4"}
		},
		{"rebel_patrol_1", 7077, -1467, 1776, SHIP_AI_FIXED_PATROL, 300, 420, 5, 10, 6,
			5, {"rebel_patrol_1_00", "rebel_patrol_1_01", "rebel_patrol_1_02", "rebel_patrol_1_03", "rebel_patrol_1_04", "rebel_patrol_1_05", "rebel_patrol_1_06", "rebel_patrol_1_07", "rebel_patrol_1_08", "rebel_patrol_1_09"},
			{"reb_awing_tier4", "reb_awing_tier4", "reb_awing_tier4", "reb_awing_tier4", "reb_bwing_tier4", "reb_bwing_tier4", "reb_bwing_tier4", "reb_bwing_tier4", "reb_xwing_tier4", "reb_ykl37r_tier4", "reb_ywing_tier4"}
		},
		{"rebel_defenders_1", 7438, -450, 1370, SHIP_AI_RANDOM_PATROL, 180, 300, 5, 10, 90, 380, 6,
			{"reb_bwing_tier4", "reb_awing_tier4"}
		},
		{"nebula_assassin_guardians_2", -1969, 2659, -7044, SHIP_AI_RANDOM_PATROL, 300, 420, 5, 10, 90, 300, 3,
			{"nebula_assassin_bomber_tier4", "nebula_assassin_saboteur_tier5"}
		},
		{"nebula_assassin_patrol_inside", -7393, -7555, -7641, SHIP_AI_FIXED_PATROL, 300, 420, 5, 10, 5,
			5, {"nebula_assassin_patrol_inside_00", "nebula_assassin_patrol_inside_01", "nebula_assassin_patrol_inside_02", "nebula_assassin_patrol_inside_03", "nebula_assassin_patrol_inside_04", "nebula_assassin_patrol_inside_05", "nebula_assassin_patrol_inside_06", "nebula_assassin_patrol_inside_07", "nebula_assassin_patrol_inside_08", "nebula_assassin_patrol_inside_09", "nebula_assassin_patrol_inside_10"},
			{"nebula_assassin_bomber_tier4", "nebula_assassin_bounty_hunter_tier5", "nebula_assassin_fighter_tier4", "nebula_assassin_boss", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_fighter_tier4", "nebula_assassin_bomber_tier4", "nebula_assassin_bomber_tier4", "nebula_assassin_bomber_tier4", "nebula_assassin_bomber_tier4", "nebula_assassin_bomber_tier4", "nebula_assassin_bomber_tier4"}
		},
		{"nebula_assassin_guardians_1", -3149, -2583, -5926, SHIP_AI_RANDOM_PATROL, 300, 420, 5, 10, 90, 200, 3,
			{"nebula_assassin_bomber_tier5", "nebula_assassin_bounty_hunter_tier5"}
		},
		{"hutt_smuggler_route_1", -3378, 3317, -3140, SHIP_AI_FIXED_PATROL, 180, 300, 10, 100, 2,
			5, {"hutt_smuggler_route_1_00", "hutt_smuggler_route_1_01", "hutt_smuggler_route_1_02", "hutt_smuggler_route_1_03", "hutt_smuggler_route_1_04", "hutt_smuggler_route_1_05"},
			{"hutt_bomber_s02_tier4", "hutt_fighter_s02_tier4", "hutt_pirate_s02_tier4"}
		},
		{"corellia_privateer_tier4_leg_2_destroy_one", 4664, -3490, 4841, SHIP_AI_RANDOM_PATROL, 180, 300, 30, 60, 80, 360, 3,
			{"hidden_daggers_killer_tier4", "hidden_daggers_gunship_tier4", "hidden_daggers_slayer_tier4"}
		},
		{"bh_target_escort_02", 801, -1284, -3418, SHIP_AI_RANDOM_PATROL, 300, 420, 9, 18, 140, 420, 1,
			{"squad_dath_witchblood_clan"}
		},
		{"tier3_privateer_witchblood_inspect_01", -1662, 721, -313, SHIP_AI_FIXED_PATROL, 180, 300, 24, 48, 4,
			5, {"tier3_privateer_witchblood_inspect_01_00", "tier3_privateer_witchblood_inspect_01_01", "tier3_privateer_witchblood_inspect_01_02", "tier3_privateer_witchblood_inspect_01_03", "tier3_privateer_witchblood_inspect_01_04", "tier3_privateer_witchblood_inspect_01_05", "tier3_privateer_witchblood_inspect_01_06"},
			{"dath_witchblood_clan_soldier_tier3"}
		},
	},
}

registerScreenPlay("SpaceDathomirSpawner", true)

function SpaceDathomirSpawner:start()
	if (not isZoneEnabled(self.spaceZone)) then
		return
	end

	self:populateSpawns()
end
