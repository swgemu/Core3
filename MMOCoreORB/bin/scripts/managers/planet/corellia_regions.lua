-- Planet Region Definitions
--
-- {"regionName", x, y, shape and size, tier, {"spawnGroup1", ...}, maxSpawnLimit}
-- For circle and ring, x and y are the center point
-- For rectangles, x and y are the bottom left corner. x2 and y2 (see below) are the upper right corner
-- Shape and size is a table with the following format depending on the shape of the area:
--   - Circle: {CIRCLE, radius}
--   - Rectangle: {RECTANGLE, x2, y2}
--   - Ring: {RING, inner radius, outer radius}
-- Tier is a bit mask with the following possible values where each hexadecimal position is one possible configuration.
-- That means that it is not possible to have both a spawn area and a no spawn area in the same region, but
-- a spawn area that is also a no build zone is possible.

require("scripts.managers.planet.regions")

corellia_regions = {
	-- No Build Zones
	{"northedge_corellia_nobuild", -8000, 7640, {RECTANGLE, 8000, 8000}, NOBUILDZONEAREA},
	{"westegde_corellia_nobuild", -8000, -7640, {RECTANGLE, -7640, 7640}, NOBUILDZONEAREA},
	{"southedge_corellia_nobuild", -7995, -8000, {RECTANGLE, 8000, -7640}, NOBUILDZONEAREA},
	{"eastedge_corellia_nobuild", 7640, -7640, {RECTANGLE, 8000, 7640}, NOBUILDZONEAREA},

	-- Named Regions, POIs and Decor
	{"sdungeon_rogue_corsec_bunker", 5225, 1567, {CIRCLE, 128}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"sdungeon_imperial_outpost", 4664, -5784, {CIRCLE, 128}, NOBUILDZONEAREA},
	{"corellia_rebel_hideout", -6507, 5992, {CIRCLE, 225}, NOBUILDZONEAREA},
	{"corellia_sdungeon_cave_01", 1360, -329, {CIRCLE, 128}, NOBUILDZONEAREA},
	{"corellia_sdungeon_cave_02", 1029, 4198, {CIRCLE, 128}, NOBUILDZONEAREA},
	{"corellia_sdungeon_cave_03", -2510, 2922, {CIRCLE, 128}, NOBUILDZONEAREA},
	{"@corellia_region_names:agrilat_swamp_1", 816, 4624, {CIRCLE, 1168}, NAMEDREGION},
	{"@corellia_region_names:golden_beaches_1", 7028, 4128, {CIRCLE, 600}, NAMEDREGION},
	{"@corellia_region_names:golden_beaches_2", 6304, 3680, {CIRCLE, 704}, NAMEDREGION},
	{"@corellia_region_names:golden_beaches_3", 5600, 3168, {CIRCLE, 576}, NAMEDREGION},
	{"@corellia_region_names:golden_beaches_4", 4384, -64, {RECTANGLE, 5120, 2624}, NAMEDREGION},
	{"@corellia_region_names:golden_beaches_5", 5200, 2672, {CIRCLE, 496}, NAMEDREGION},
	{"@corellia_region_names:golden_beaches_6", 5808, -496, {CIRCLE, 592}, NAMEDREGION},
	{"@corellia_region_names:golden_beaches_7", 5920, -1664, {RECTANGLE, 8000, -800}, NAMEDREGION},
	{"@corellia_region_names:golden_beaches_8", 5168, -144, {CIRCLE, 496}, NAMEDREGION},
	{"@corellia_region_names:denendre_valley_1", -4800, 3936, {RECTANGLE, -3360, 7008}, NAMEDREGION},
	{"@corellia_region_names:denendre_valley_2", -6016, 6368, {RECTANGLE, -4768, 7424}, NAMEDREGION},
	{"@corellia_region_names:denendre_valley_3", -3120, 6896, {CIRCLE, 400}, NAMEDREGION},
	{"@corellia_region_names:denendre_valley_4", -4720, 6352, {CIRCLE, 400}, NAMEDREGION},
	{"@corellia_region_names:thaos_mountains_1", -2368, 6176, {RECTANGLE, 4288, 7456}, NAMEDREGION},
	{"@corellia_region_names:thaos_mountains_2", -2224, 5168, {CIRCLE, 1008}, NAMEDREGION},
	{"@corellia_region_names:thaos_mountains_3", -2336, 5024, {RECTANGLE, -1216, 7264}, NAMEDREGION},
	{"@corellia_region_names:rier_let", -928, 2976, {CIRCLE, 928}, NAMEDREGION},
	{"@corellia_region_names:rier_vem", 976, 2512, {CIRCLE, 720}, NAMEDREGION},
	{"@corellia_region_names:rhalers_bastion", -6350, 5120, {CIRCLE, 1450}, NAMEDREGION},
	{"@corellia_region_names:bindreg_hills_1", -7616, 288, {RECTANGLE, -5728, 2656}, NAMEDREGION},
	{"@corellia_region_names:bindreg_hills_2", -4640, 768, {CIRCLE, 864}, NAMEDREGION},
	{"@corellia_region_names:bindreg_hills_3", -7488, 160, {RECTANGLE, -4640, 1664}, NAMEDREGION},
	{"@corellia_region_names:riverlands_1", -3296, -2112, {RECTANGLE, 4224, 1696}, NAMEDREGION},
	{"@corellia_region_names:riverlands_2", -5504, -2176, {RECTANGLE, -2080, -704},  NAMEDREGION},
	{"@corellia_region_names:riverlands_3", -768, -4448, {RECTANGLE, 3360, -2208},  NAMEDREGION},
	{"@corellia_region_names:riverlands_4", -1120, -2464, {CIRCLE, 864}, NAMEDREGION},
	{"@corellia_region_names:riverlands_5", 2720, -2368, {RECTANGLE, 7232, -1504}, NAMEDREGION},
	{"@corellia_region_names:riverlands_6", 4624, -1360, {CIRCLE, 944}, NAMEDREGION},
	{"@corellia_region_names:suntir_plains", 1312, -7936, {RECTANGLE, 5024, -5184},  NAMEDREGION},
	{"@corellia_region_names:dregans_pike", 4336, -4144, {CIRCLE, 976}, NAMEDREGION},
	{"@corellia_region_names:malal_mountains", 5900, -8000, {RECTANGLE, 8000, -3968}, NAMEDREGION},
	{"@corellia_region_names:loch_khaxus", 7344, 7024, {CIRCLE, 525}, NAMEDREGION},
	{"corellia_rebel_vs_imperial_battlesite", 4112, -1260, {CIRCLE, 300}, NOBUILDZONEAREA},
	{"corellia_force_shrine_01", -6907, 4527, {CIRCLE, 199}, NOBUILDZONEAREA},
	{"corellia_force_shrine_02", -7392, -3938, {CIRCLE, 199}, NOBUILDZONEAREA},
	{"corellia_force_shrine_03", 6093, -5578, {CIRCLE, 199}, NOBUILDZONEAREA},
	{"corellia_force_shrine_04", 6301, 6688, {CIRCLE, 199}, NOBUILDZONEAREA},
	{"corellia_force_shrine_05", -2384, 6393, {CIRCLE, 199}, NOBUILDZONEAREA},
	{"abandoned_camp_site_01", 6295, -3954, {CIRCLE, 40}, NOBUILDZONEAREA},
	{"abandoned_mine_project_02", 5602, -1529, {CIRCLE, 60}, NOBUILDZONEAREA},
	{"windmill_power_plant_03", 6217, 4682, {CIRCLE, 40}, NOBUILDZONEAREA},
	{"bandoned_smugglers_camp_04", 6047, 6400, {CIRCLE, 40}, NOBUILDZONEAREA},
	{"beach_hut_05_", 7511, -1780, {CIRCLE, 40}, NOBUILDZONEAREA},
	{"corellian_monument_06", 751, 2487, {CIRCLE, 30}, NOBUILDZONEAREA},
	{"memorial_statue_09", -7065, -1593, {CIRCLE, 40}, NOBUILDZONEAREA},
	{"monument_10", -7138, 132, {CIRCLE, 50}, NOBUILDZONEAREA},
	{"crystal_arch_half_11", -6833, 2183, {CIRCLE, 100}, NOBUILDZONEAREA},
	{"crystal_steam_vent_12", -7524, 4618, {CIRCLE, 60}, NOBUILDZONEAREA},
	{"listening_post_15", -1419, 1972, {CIRCLE, 20}, NOBUILDZONEAREA},
	{"face_monlith_16", -1905, 3990, {CIRCLE, 50}, NOBUILDZONEAREA},
	{"bridge_underconstruction_18", 414, -2806, {CIRCLE, 50}, NOBUILDZONEAREA},
	{"power_plant_20", 528, -415, {CIRCLE, 50}, NOBUILDZONEAREA},
	{"broken_ore_extracter_21", 111, 1726, {CIRCLE, 60}, NOBUILDZONEAREA},
	{"half_arch_and_gyser_22", 4117, -4312, {CIRCLE, 60}, NOBUILDZONEAREA},
	{"flaming_bowl_24", 4516, 4313, {CIRCLE, 40}, NOBUILDZONEAREA},
	{"rock_bowl_25", 4872, 6692, {CIRCLE, 40}, NOBUILDZONEAREA},
	{"crashed_landing_pod_26", -5467, -934, {CIRCLE, 30}, NOBUILDZONEAREA},
	{"ruined_milotary_installation_27", -5324, 213, {CIRCLE, 50}, NOBUILDZONEAREA},
	{"crash_site_28", -5416, 2080, {CIRCLE, 40}, NOBUILDZONEAREA},
	{"ruined_guard_tower_29", -5899, 4674, {CIRCLE, 75}, NOBUILDZONEAREA},
	{"monument_31", -2938, -1839, {CIRCLE, 60}, NOBUILDZONEAREA},
	{"abandoned_milotary_site_32", -3613, -354, {CIRCLE, 60}, NOBUILDZONEAREA},
	{"ruins_in_river_35", -4476, 5540, {CIRCLE, 100}, NOBUILDZONEAREA},
	{"a_crash_site_37", -1754, -3280, {CIRCLE, 40}, NOBUILDZONEAREA},
	{"abandoned_power_generator_38", -2295, -1335, {CIRCLE, 40}, NOBUILDZONEAREA},
	{"a_droid_graveyard_39", -1869, -143, {CIRCLE, 75}, NOBUILDZONEAREA},
	{"old_battlefield_nobuild_cor1", 263, 4620, {CIRCLE, 256}, NOBUILDZONEAREA},
	{"old_battlefield_nobuild_cor2", -1870, -1223, {CIRCLE, 192}, NOBUILDZONEAREA},
	{"old_battlefield_nobuild_cor3", 3785, -4037, {CIRCLE, 192}, NOBUILDZONEAREA},

	-- Cities
	{"@corellia_region_names:bela_vistal", 6788, -5654, {CIRCLE, 480}, CITY + NOSPAWNAREA},
	{"@corellia_region_names:coronet", -178, -4504, {CIRCLE, 581}, CITY + NOSPAWNAREA},
	{"@corellia_region_names:tyrena", -5282, -2526, {CIRCLE, 622}, CITY + NOSPAWNAREA},
	{"@corellia_region_names:kor_vella", -3512, 3184, {CIRCLE, 758}, CITY + NOSPAWNAREA},
	{"@corellia_region_names:doaba_guerfel", 3272, 5456, {CIRCLE, 632}, CITY + NOSPAWNAREA},
	{"@corellia_region_names:vreni_island", -5472, -6272, {CIRCLE, 690}, CITY + NOSPAWNAREA},
	{"@corellia_region_names:vreni_island_1", -5488, -6288, {CIRCLE, 528}, NOBUILDZONEAREA},

	{"coronet_nobuild_1", -178, -4504, {CIRCLE, 1000}, CAMPINGAREA + NOBUILDZONEAREA},
	{"tyrena_nobuild_1", -5282, -2526, {CIRCLE, 1200}, CAMPINGAREA + NOBUILDZONEAREA},
	{"bela_vistal_nobuild_1", 6788, -5654, {CIRCLE, 1000}, CAMPINGAREA + NOBUILDZONEAREA},
	{"vreni_island_nobuild_1", -5472, -6272, {CIRCLE, 1400}, CAMPINGAREA + NOBUILDZONEAREA},
	{"kor_vella_nobuild_1", -3512, 3184, {CIRCLE, 1500}, CAMPINGAREA + NOBUILDZONEAREA},
	{"daoba_guerfel_nobuild_1", 3272, 5456, {CIRCLE, 1200}, CAMPINGAREA + NOBUILDZONEAREA},
	{"corellia_vreni_island_outdoor_theater", -5442, -6283, {RECTANGLE, -5398, -6221}, NOBUILDZONEAREA},

	-- Spawn Areas
	{"@corellia_region_names:bela_vistal_easy_newbie", 6788, -5654, {RING, 480, 800}, SPAWNAREA + NOWORLDSPAWNAREA, {"bela_vistal_easy_newbie"}, 32},
	{"@corellia_region_names:bela_vistal_medium_newbie", 6788, -5654, {RING, 800, 1200}, SPAWNAREA + NOWORLDSPAWNAREA, {"bela_vistal_medium_newbie"}, 32},
	{"@corellia_region_names:central_easy", 825, -1959, {RECTANGLE, 4090, 4570}, SPAWNAREA, {"corellia_central_easy"}, 320},
	{"@corellia_region_names:central_medium", -2075, -1959, {RECTANGLE, 840, 4570}, SPAWNAREA, {"corellia_central_medium"}, 256},
	{"@corellia_region_names:central_plains", -3296, -2312, {RECTANGLE, 4224, 1496}, SPAWNAREA + NAMEDREGION, {"corellia_central_plains"}, 32},
	{"@corellia_region_names:coronest_easy_newbie", -178, -4504, {RING, 581, 1000}, SPAWNAREA + NOWORLDSPAWNAREA, {"coronet_easy_newbie"}, 32},
	{"@corellia_region_names:coronet_medium_newbie", -178, -4504, {RING, 1000, 1500}, SPAWNAREA + NOWORLDSPAWNAREA, {"coronet_medium_newbie"}, 32},
	{"@corellia_region_names:doaba_guefel_easy_newbie", 3272, 5456, {RING, 632, 1000}, SPAWNAREA + NOWORLDSPAWNAREA, {"doaba_guerfel_easy_newbie"}, 32},
	{"@corellia_region_names:doaba_guefel_medium_newbie", 3272, 5456, {RING, 1000, 1500}, SPAWNAREA + NOWORLDSPAWNAREA, {"doaba_guerfel_medium_newbie"}, 32},
	{"@corellia_region_names:east_sea_coast", 3926, -1559, {RECTANGLE, 7373, 5072}, SPAWNAREA, {"corellia_east_sea_coast"}, 256},
	{"@corellia_region_names:eastern_medium", 4090, -6075, {RECTANGLE, 8000, 4570}, SPAWNAREA, {"corellia_eastern_medium"}, 512},
	{"@corellia_region_names:eastern_rogue_corsec_medium", 5136, 1636, {CIRCLE, 211}, SPAWNAREA, {"corellia_eastern_rogue_corsec_medium"}, 32},
	{"@corellia_region_names:forest1", -3696, -1968, {CIRCLE, 608}, SPAWNAREA, {"corellia_forest_1"}, 32},
	{"@corellia_region_names:forest2", -2047, 3272, {CIRCLE, 615}, SPAWNAREA, {"corellia_forest_2"}, 32},
	{"@corellia_region_names:forest3", -2336, -784, {RECTANGLE, -1056, 1120}, SPAWNAREA, {"corellia_forest_3"}, 32},
	{"@corellia_region_names:forest4", -1862, 5878, {RECTANGLE, 3766, 7434}, SPAWNAREA, {"corellia_northwest_forest"}, 256},
	{"@corellia_region_names:forest5", 6888, -7208, {CIRCLE, 750}, SPAWNAREA, {"corellia_southwest_forest"}, 256},
	{"@corellia_region_names:kor_vella_easy_newbie", -3512, 3184, {RING, 758, 1200}, SPAWNAREA, {"kor_vella_easy_newbie"}, 32},
	{"@corellia_region_names:kor_vella_medium_newbie", -3512, 3184, {RING, 1200, 1600}, SPAWNAREA, {"kor_vella_medium_newbie"}, 32},
	{"@corellia_region_names:lord_nyax_hard", 1650, -500, {CIRCLE, 175}, SPAWNAREA, {"corellia_lord_nyax_hard"}, 8},
	{"@corellia_region_names:swamp1", 816, 4560, {CIRCLE, 1497}, SPAWNAREA, {"agrilat_swamp"}, 128},
	{"@corellia_region_names:tyrena_easy_newbie", -5352, -5160, {RING, 622, 1000}, SPAWNAREA, {"tyrena_easy_newbie"}, 256},
	{"@corellia_region_names:tyrena_medium_newbie", -5352, -5160, {RING, 1000, 1400}, SPAWNAREA, {"tyrena_medium_newbie"}, 256},
	{"@corellia_region_names:vreni_island_medium_newbie", -5352, -5160, {CIRCLE, 2600}, SPAWNAREA, {"vreni_island_medium_newbie"}, 256},

	-- North
	{"@corellia_region_names:northern_beladonas_hard", 6229, 5779, {CIRCLE, 221}, SPAWNAREA, {"corellia_northern_beladonas_hard"}, 8},
	{"@corellia_region_names:northern_selonian_hard", 2442, 5012, {CIRCLE, 250}, SPAWNAREA, {"corellia_northern_selonian_hard"}, 8},
	-- North East
	{"@corellia_region_names:northeastern_hard", -2092, 4570, {RECTANGLE, 7950, 7882}, SPAWNAREA, {"corellia_northeastern_hard"}, 1211},
	{"@corellia_region_names:northeastern_dark_adept_hard", 5478, 7079, {CIRCLE, 250}, SPAWNAREA, {"corellia_northeastern_dark_adept_hard"}, 8},

	-- North West
	{"@corellia_region_names:northwestern_medium", -7875, 8, {RECTANGLE, -2090, 7870}, SPAWNAREA, {"corellia_northwestern_medium"}, 512},
	{"@corellia_region_names:northwestern_gronda_hard", -3241, 4099, {CIRCLE, 250}, SPAWNAREA, {"corellia_northwestern_gronda_hard", "corellia_hard_gronda_nw"}, 8},
	--corellia_hard_greater_gulginaw_nw
	--corellia_medium_murra_nw

	-- South East
	{"@corellia_region_names:se_medium", 290, -7859, {RECTANGLE, 8000, -6070}, SPAWNAREA, {"corellia_se_medium" ,"corellia_medium_dire_cat_se", "corellia_medium_murra_se", "corellia_medium_sand_panther_se", "corellia_medium_slice_hound_se"}, 256},

	-- South West
	{"@corellia_region_names:southwestern_medium", -7870, -5200, {RECTANGLE, -2090, 0}, SPAWNAREA, {"corellia_southerwestern_medium"}, 256},
	{"@corellia_region_names:hard_crimson_sand_panther_sw", -5166, -1426, {CIRCLE, 3000}, SPAWNAREA, {"corellia_hard_crimson_sand_panther_sw"}, 128},

	--corellia_medium_slice_hound_sw

	-- South Central
	{"@corellia_region_names:southern_central_easy", -2090, -6075, {RECTANGLE, 4080, -1950}, SPAWNAREA, {"corellia_southern_central_easy"}, 256},

	{"@corellia_region_names:grassland1", -4088, 3176, {CIRCLE, 1896}, SPAWNAREA, {"corellia_northwest_plains"}, 192},
	{"@corellia_region_names:grassland2", 3200, 3728, {CIRCLE, 864}, SPAWNAREA, {"corellia_medium_dire_cat_ne"}, 32},
	{"@corellia_region_names:grassland3", 5368, 5016, {CIRCLE, 1112}, SPAWNAREA, {"corellia_hard_gronda_ne", "corellia_hard_gulginaw_ne"}, 64},
	{"@corellia_region_names:grassland4", -5360, -1376, {CIRCLE, 1392}, SPAWNAREA, {"corellia_hard_gronda_sw", "corellia_hard_gulginaw_sw"}, 256},
	{"@corellia_region_names:grassland5", -992, -320, {CIRCLE, 2720}, SPAWNAREA, {"corellia_western_plains"}, 256},
	{"@corellia_region_names:grassland6", 3536, -720, {CIRCLE, 1552}, SPAWNAREA, {"corellia_southeast_plains"}, 192},
	{"@corellia_region_names:grassland7", 3336, -4536, {CIRCLE, 3323}, SPAWNAREA, {"corellia_southeast_plains"}, 256},
	{"@corellia_region_names:grassland8", 6760, -3000, {CIRCLE, 1200}, SPAWNAREA, {"corellia_southeast_plains"}, 64},

	{"@corellia_region_names:mountain1", 4440, -4136, {CIRCLE, 1080}, SPAWNAREA, {"corellia_southeast_mountain_peak"}, 64},
	{"@corellia_region_names:mountain2", 6032, -8000, {RECTANGLE, 8000, -3952}, SPAWNAREA, {"corellia_southeast_mountain_range"}, 256},
	{"@corellia_region_names:mountain3", -6152, 1320, {CIRCLE, 1800}, SPAWNAREA, {"corellia_western_mountain_forest"}, 64},
	{"@corellia_region_names:mountain4", -6368, 5424, {CIRCLE, 1600}, SPAWNAREA, {"corellia_northwest_mountains"}, 64},
	{"@corellia_region_names:mountain5", -2224, 5136, {CIRCLE, 1360}, SPAWNAREA, {"corellia_northwest_mountain_peak", "corellia_northwest_mountains"}, 64},
	{"@corellia_region_names:mountain6", -2032, 5440, {RECTANGLE, 4464, 7488}, SPAWNAREA, {"corellia_north_central_mountains"}, 256},
	{"@corellia_region_names:mountain7", 7112, 6552, {CIRCLE, 850}, SPAWNAREA, {"corellia_northeast_mountains"}, 32},
	{"@corellia_region_names:mountain8", 232, 2728, {CIRCLE, 1272}, SPAWNAREA, {"corellia_north_central_mountains"}, 64},

	-- TBD
	--[[
	{"@corellia_region_names:beach1", -5352, -5160, {CIRCLE, 2600}, SPAWNAREA, {""}, 256},
	{"@corellia_region_names:beach2", -3048, -4888, {CIRCLE, 3060}, SPAWNAREA, {""}, 256},
	{"@corellia_region_names:beach3", 976, -5664, {CIRCLE, 845}, SPAWNAREA, {""}, 32},
	{"@corellia_region_names:beach4", 4160, -2176, {RECTANGLE, 8000, 5280}, {""}, 256},
	{"@corellia_region_names:lake1", 2264, -152, {CIRCLE, 1016}, SPAWNAREA, {""}, 64},
	{"@corellia_region_names:lake2", -5744, -1984, {RECTANGLE, -2912, -736}, SPAWNAREA, {""}, 256},
	]]

	{"@corellia_region_names:world_spawner", 0, 0, {RECTANGLE, 0, 0}, WORLDSPAWNAREA + SPAWNAREA, {"corellia_world"}, 2048}
}