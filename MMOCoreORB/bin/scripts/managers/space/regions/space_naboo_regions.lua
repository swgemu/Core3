--[[ Space Region Definitions
For SPHERE and CUBOID: x, z, y are the center point.

SPHERE Examples:
{"regionName", x, z, y, {SPHERE, radius}, type},
{"regionName", x, z, y, {SPHERE, radius}, SPAWNAREA, {"spawnGroup1", "spawnGroup2"}, maxSpawnLimit}

CUBOID Examples:
{"regionName", x, z, y, {CUBOID, length, width, height}, type},
{"regionName", x, z, y, {CUBOID, length, width, height}, SPAWNAREA, {"spawnGroup1", "spawnGroup2"}, maxSpawnLimit}
]]

require("scripts.managers.space.regions.regions")

space_naboo_regions = {
	{"naboo_space_station", -2500, 900, -6000, {CUBOID, 4096, 4096, 4096}, SPAWNAREA, {"naboo_traffic"}, 24},
	{"rori_space_station", 6226.22, -4450.57, 484.75, {CUBOID, 4096, 4096, 4096}, SPAWNAREA, {"naboo_traffic"}, 24},

	{"imperial_naboo", 3511.83, 1774.71, 944.36, {SPHERE, 4096}, SPAWNAREA, {"imperial_easy"}, 12},

	-- Top
	{"naboo_space_test1", 4000, 4000, 4000, {SPHERE, 2048}, SPAWNAREA, {"naboo_traffic"}, 12},
	{"naboo_space_test2", -4000, 4000, 4000, {SPHERE, 2048}, SPAWNAREA, {"naboo_traffic"}, 12},
	{"naboo_space_test3", 4000, 4000, -4000, {SPHERE, 2048}, SPAWNAREA, {"naboo_traffic"}, 12},
	{"naboo_space_test4", -4000, 4000, -4000, {SPHERE, 2048}, SPAWNAREA, {"naboo_traffic"}, 12},
	-- Bottom
	{"naboo_space_test5", 4000, -4000, 4000, {SPHERE, 2048}, SPAWNAREA, {"naboo_traffic"}, 12},
	{"naboo_space_test6", -4000, -4000, 4000, {SPHERE, 2048}, SPAWNAREA, {"naboo_traffic"}, 12},
	{"naboo_space_test7", 4000, -4000, -4000, {SPHERE, 2048}, SPAWNAREA, {"naboo_traffic"}, 12},
	{"naboo_space_test8", -4000, -4000, -4000, {SPHERE, 2048}, SPAWNAREA, {"naboo_traffic"}, 12},
}
