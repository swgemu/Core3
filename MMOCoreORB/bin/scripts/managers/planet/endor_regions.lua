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

endor_regions = {
	-- No Build Zones
	{"northedge_endor_nobuild", -8000, 7640, {RECTANGLE, 8000, 8000}, NOBUILDZONEAREA},
	{"westedge_endor_nobuild", -8000, -7640, {RECTANGLE, -7640, 7640}, NOBUILDZONEAREA},
	{"southedge_endor_nobuild", -8000, -8000, {RECTANGLE, 8000, -7640}, NOBUILDZONEAREA},
	{"eastedge_endor_nobuild", 7640, -7640, {RECTANGLE, 8000, 7640}, NOBUILDZONEAREA},
	{"old_battlefield_nobuild_end1", -469, 3651, {CIRCLE, 256}, NOBUILDZONEAREA},
	{"old_battlefield_nobuild_end2", -2790, -4457, {CIRCLE, 256}, NOBUILDZONEAREA},

	-- Named Regions, POIs and Decor
	{"awning_with_pillars", 278, 3829, {CIRCLE, 30}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"elevated_hut", -1770, -4090, {CIRCLE, 50}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"ewok_hut", 3879, 4211, {CIRCLE, 50}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"hot_springs", 2372, 2182, {CIRCLE, 50}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"hut", -1800, 6023, {CIRCLE, 30}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"huts_and_campfire", -1538, -6013, {CIRCLE, 50}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"imperial_ruins", 2318, 5860, {CIRCLE, 50}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"korga_cave", 2163, 3617, {CIRCLE, 150}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"life_day_home", -1088, -996, {CIRCLE, 100}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"marauders_stronghold", -4648, -2273, {CIRCLE, 200}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"skeleton_hut", 267, -1444, {CIRCLE, 30}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"stone_village", 3924, 5787, {CIRCLE, 75}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"three_huts", 2047, 4316, {CIRCLE, 50}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"tree_stand", -1876, -1474, {CIRCLE, 50}, NOSPAWNAREA + NOBUILDZONEAREA},

	{"@endor_region_names:ewok_village_tree_1", 84, 39, {CIRCLE, 80}, NOSPAWNAREA + NOBUILDZONEAREA + NAVAREA + NAMEDREGION},
	{"@endor_region_names:ewok_village_tree_2", 4545, -2395, {CIRCLE, 128}, NOSPAWNAREA + NOBUILDZONEAREA + NAVAREA + NAMEDREGION},
	{"@endor_region_names:ewok_lake_village_1", 1459.44, -3251.81, {CIRCLE, 150}, NOSPAWNAREA + NOBUILDZONEAREA + NAVAREA + NAMEDREGION},
	{"@endor_region_names:ewok_lake_village_2", -583.299, -5052.59, {CIRCLE, 175}, NOSPAWNAREA + NOBUILDZONEAREA + NAVAREA + NAMEDREGION},
	{"@endor_region_names:dulok_village_1", 6068, -2475, {CIRCLE, 100}, NOSPAWNAREA + NOBUILDZONEAREA + NAVAREA + NAMEDREGION},
	{"@endor_region_names:dulok_village_2", -1211, 2952, {CIRCLE, 128}, NOSPAWNAREA + NOBUILDZONEAREA + NAVAREA + NAMEDREGION},
	{"endor_marauder_base", -4677, -2271, {CIRCLE, 229}, NOSPAWNAREA},
	{"endor_marauder_base_nobuild_1", -4677, -2271, {CIRCLE, 329}, NOBUILDZONEAREA},
	{"endor_dulok_korga_cave", 2268, 3530, {CIRCLE, 198}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"endor_marauder_orphans_cave", -6902, 700, {CIRCLE, 198}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"endor_jinda_cave", -1712, 0, {CIRCLE, 198}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"@endor_region_names:salma_desert_1", -416, 4416, {CIRCLE, 1530}, NAMEDREGION},
	{"@endor_region_names:salma_desert_2", 1984, 4960, {CIRCLE, 1248}, NAMEDREGION},
	{"@endor_region_names:salma_desert_3", 3792, 5808, {CIRCLE, 1040}, NAMEDREGION},
	{"@endor_region_names:salma_desert_4", 5088, 5920, {CIRCLE, 736}, NAMEDREGION},
	{"@endor_region_names:salma_desert_5", -1280, 5600, {RECTANGLE, 3648, 6496}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_1", -992, 2880, {CIRCLE, 216}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_2", 272, 2864, {CIRCLE, 228}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_3", 624, 3120, {CIRCLE, 240}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_4", 848, 3408, {CIRCLE, 208}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_5", 1024, 3744, {CIRCLE, 192}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_6", 1328, 3888, {CIRCLE, 208}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_7", 1488, 3728, {CIRCLE, 208}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_8", -896, 2688, {RECTANGLE, 192, 2976}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_9", 1632, 3552, {RECTANGLE, 2496, 3840}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_10", 2688, 3776, {CIRCLE, 192}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_11", 3008, 4064, {CIRCLE, 192}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_12", 2976, 4192, {RECTANGLE, 3232, 4928}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_13", 3360, 4800, {CIRCLE, 160}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_14", 3456, 4640, {RECTANGLE, 4512, 4832}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_15", 4672, 4800, {CIRCLE, 160}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_16", 4928, 4960, {CIRCLE, 128}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_17", 5152, 5120, {CIRCLE, 160}, NAMEDREGION},
	{"@endor_region_names:yawari_cliffs_18", 5472, 5280, {CIRCLE, 160}, NAMEDREGION},
	{"@endor_region_names:nub_shanda", 1280, -3808, {CIRCLE, 1300}, NAMEDREGION},
	{"@endor_region_names:jiberah_plains_1", -256, 384, {RECTANGLE, 5920, 2656}, NAMEDREGION},
	{"@endor_region_names:jiberah_plains_2", 1312, -128, {RECTANGLE, 4544, 3488}, NAMEDREGION},
	{"@endor_region_names:jiberah_plains_3", 3488, -224, {RECTANGLE, 5952, 4576}, NAMEDREGION},
	{"@endor_region_names:jiberah_plains_4", 3600, 3760, {CIRCLE, 560}, NAMEDREGION},
	{"@endor_region_names:jiberah_plains_5", 1264, 2832, {CIRCLE, 464}, NAMEDREGION},
	{"@endor_region_names:marauder_mountain_1", -5072, -1744, {CIRCLE, 1042}, NAMEDREGION},
	{"@endor_region_names:marauder_mountain_2", -4256, -2816, {CIRCLE, 960}, NAMEDREGION},
	{"@endor_region_names:marauder_mountain_3", -5600, -3040, {RECTANGLE, -3712, -1856}, NAMEDREGION},
	{"@endor_region_names:oniantae_hills_1", -2912, 2496, {CIRCLE, 896}, NAMEDREGION},
	{"@endor_region_names:oniantae_hills_2", -1856, 896, {CIRCLE, 992}, NAMEDREGION},
	{"@endor_region_names:oniantae_hills_3", -3232, 1280, {RECTANGLE, -1760, 2016}, NAMEDREGION},
	{"@endor_region_names:mertune_forest_1", -6368, -512, {RECTANGLE, -3872, 3680}, NAMEDREGION},
	{"@endor_region_names:mertune_forest_2", -4960, 3456, {RECTANGLE, -2240, 4608}, NAMEDREGION},
	{"@endor_region_names:fersal_hills", 4832, -4320, {CIRCLE, 992}, NAMEDREGION},
	{"endor_coa2_imperial_base", -1953, 1046, {CIRCLE, 50}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"endor_coa2_rebel_base", 4008, 2985, {CIRCLE, 50}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"endor_death_watch_bunker", -4645, 4341, {CIRCLE, 200}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"endor_force_shrine_01", -3871, -4468, {CIRCLE, 199}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"endor_force_shrine_02", 5117, 1924, {CIRCLE, 199}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"endor_force_shrine_03", 670, 5548, {CIRCLE, 199}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"endor_force_shrine_04", -5627, 4814, {CIRCLE, 199}, NOSPAWNAREA + NOBUILDZONEAREA},
	{"endor_force_shrine_05", -5056, -1703, {CIRCLE, 199}, NOSPAWNAREA + NOBUILDZONEAREA},

	-- Cities / Outposts
	{"@endor_region_names:endor_smuggler_outpost", -898, 1587, {CIRCLE, 400}, CITY + NOSPAWNAREA + NOBUILDZONEAREA},
	{"@endor_region_names:endor_neutral_outpost", 3222, -3467, {CIRCLE, 400}, CITY + NOSPAWNAREA},
	{"@endor_region_names:endor_neutral_outpost_nobuild_1", 3222, -3467, {CIRCLE, 200}, NOBUILDZONEAREA},

	-- Spawns
	{"@endor_region_names:central_east_medium", 80, -970, {RECTANGLE, 4106, 3990}, SPAWNAREA, {"endor_central_east_medium"} ,256},
	{"@endor_region_names:central_western_easy", -3942, -975, {RECTANGLE, 80, 2720}, SPAWNAREA, {"endor_central_western_easy"}, 192},
	{"@endor_region_names:eastern_medium", 4091, -5425, {RECTANGLE, 8000, 1000}, SPAWNAREA, {"endor_eastern_medium"} ,256},
	{"@endor_region_names:northeastern_hard", 4108, 991, {RECTANGLE, 8000, 7890}, SPAWNAREA, {"endor_northeastern_hard"} ,256},
	{"@endor_region_names:northeastern_medium", 41, 3991, {RECTANGLE, 4100, 7890}, SPAWNAREA, {"endor_northeastern_medium"} ,256},
	{"@endor_region_names:northeastern_veryhard", 4949, 4391, {CIRCLE, 191}, SPAWNAREA, {"endor_northeastern_veryhard"}, 4},
	{"@endor_region_names:northern_medium", -3942, 2725, {RECTANGLE, 50, 7900}, SPAWNAREA, {"endor_northern_medium"}, 256},
	{"@endor_region_names:northwestern_hard", -8000, 1798, {RECTANGLE, -3950, 7920}, SPAWNAREA, {"endor_northwestern_hard"} ,256},
	{"@endor_region_names:southeastern_medium", 3108, -7490, {RECTANGLE, 8000, -5425}, SPAWNAREA ,{"endor_southeastern_medium"}, 128},
	{"@endor_region_names:southern_central_easy", 75, -5420, {RECTANGLE, 4090, -970}, SPAWNAREA, {"endor_southern_central_easy"}, 256},
	{"@endor_region_names:southern_central_medium", -3959, -6525, {RECTANGLE, 80, -970}, SPAWNAREA, {"endor_southern_central_medium"}, 320},
	{"@endor_region_names:western_hard", -8000, -6520, {RECTANGLE, -3950, 1800}, SPAWNAREA ,{"endor_western_hard"}, 512},

	-- Desert
	{"@endor_region_names:desert_one", -1500, 4000, {RECTANGLE, 6000, 7000}, SPAWNAREA, {"endor_eastern_desert", "endor_central_desert"}, 256},
	{"@endor_region_names:desert_two", 2752, 5024, {RECTANGLE, 5600, 6752}, SPAWNAREA, {"endor_hard_desert_marauder_ne"}, 32},
	-- Mountains
	{"@endor_region_names:mountain_one", -6160, 5936, {CIRCLE, 1520}, SPAWNAREA, {"endor_northern_mountains", "endor_western_mountains"}, 128},
	{"@endor_region_names:mountain_two", -7808, -4416, {RECTANGLE, -7008, 3456}, SPAWNAREA, {"endor_western_mountains"}, 128},
	{"@endor_region_names:mountain_three", -2628, 6944, {RECTANGLE, 7552, 7712}, SPAWNAREA, {"endor_northern_mountains"}, 128},
	{"@endor_region_names:mountain_four", 6656, -5408, {RECTANGLE, 7584, 7520}, SPAWNAREA, {"endor_eastern_mountains"}, 256},
	-- Plains
	{"@endor_region_names:plains_one", -5504, -672, {RECTANGLE, -3808, 3264}, SPAWNAREA, {"endor_northwest_plains"}, 64},
	{"@endor_region_names:plains_two", -3296, -1952, {RECTANGLE, -2240, -416}, SPAWNAREA, {"endor_hard_bordok_sw", "endor_hard_gorax_sw"}, 64},
	{"@endor_region_names:plains_three", 1216, -512, {RECTANGLE, 4960, 3072}, SPAWNAREA, {"endor_northeast_plains"}, 64},
	{"@endor_region_names:plains_four", 416, -5152, {RECTANGLE, 2688, -2592}, SPAWNAREA, {"endor_medium_bolma_se"}, 32},
	-- Forest
	{"@endor_region_names:forest_one", -4384, 3552, {RECTANGLE, -2144, 6432}, SPAWNAREA, {"endor_hard_bordok_nw", "endor_hard_mantigrue_nw", "endor_hard_remmer_nw"}, 64},
	{"@endor_region_names:forest_two", -6752, -4640, {RECTANGLE, -5536, 3552}, SPAWNAREA, {"endor_hard_bordok_sw"}, 64},
	{"@endor_region_names:forest_three", -4960, -5792, {RECTANGLE, -928, -3360}, SPAWNAREA, {"endor_medium_blurrg_sw"}, 32},
	--{"@endor_region_names:forest_four", -7999, -7999, {RECTANGLE, 7999, 7999}, SPAWNAREA, {"endor_central_forest"}, 256},
	{"@endor_region_names:forest_five", 3360, 3232, {RECTANGLE, 4480, 4608}, SPAWNAREA, {"endor_medium_bolma_ne", "endor_medium_lantern_bird_ne"}, 32},
	{"@endor_region_names:forest_six", 1500, -6912, {RECTANGLE, 6272, -2272}, SPAWNAREA, {"endor_southeast_forest"}, 128},
	-- Peaks
	{"@endor_region_names:peak_one", -1696, 1152, {CIRCLE, 1500}, SPAWNAREA, {"endor_northern_peak"}, 128},
	{"@endor_region_names:peak_two", -4237.01, -3039.25, {CIRCLE, 1223}, SPAWNAREA, {"endor_southwest_peak"}, 256},
	{"@endor_region_names:peak_three", 2106.86, -1423.78, {CIRCLE, 912}, SPAWNAREA, {"endor_central_peak"}, 256},
	{"@endor_region_names:peak_four", 4848, -4144, {CIRCLE, 912}, SPAWNAREA, {"endor_southeast_peak"}, 256},

	-- endor_hard_mantigrue_se
	-- endor_hard_remmer_se

	{"@endor_region_names:world_spawner", 0, 0, {RECTANGLE, 0, 0}, SPAWNAREA + WORLDSPAWNAREA, {"endor_world"}, 2048},
}
