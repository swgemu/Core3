--[[ Space Region Definitions
For SPHERE and CUBOID: x, z, y are the center point.

SPHERE Examples:
{"regionName", x, z, y, {SPHERE, radius}, type},
{"regionName", x, z, y, {SPHERE, radius}, SPACESPAWNAREA, {"spawnGroup1", "spawnGroup2"}, maxSpawnLimit}

CUBOID Examples:
{"regionName", x, z, y, {CUBOID, length, width, height}, type},
{"regionName", x, z, y, {CUBOID, length, width, height}, SPACESPAWNAREA, {"spawnGroup1", "spawnGroup2"}, maxSpawnLimit}
]]

require("scripts.managers.space.regions.regions")

space_corellia_regions = {
	--{"corellia_space_station", 4800, -4800, -2600, {CUBOID, 6144, 6144, 6144}, SPAWNAREA, {"corellia_traffic"}, 24},
	--{"talus_space_station", -4800, -4800, -3957, {CUBOID, 6144, 6144, 6144}, SPAWNAREA, {"corellia_traffic"}, 24},

	--{"corellia_rebel_1", -4090, 2340, 2013, {SPHERE, 4096}, SPAWNAREA, {"rebel_easy"}, 12},
	--{"corellia_rebel_2", -1463, 318, -1012, {SPHERE, 4096}, SPAWNAREA, {"rebel_easy"}, 12},
}
