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
	--{"naboo_space_station", -2500, 900, -4800, {CUBOID, 6144, 6144, 6144}, SPAWNAREA, {"naboo_traffic"}, 24},
	--{"naboo_space_station_nospawn", -2491.26, 905.49, -6460.67, {SPHERE, 1024}, NOSPAWNAREA},

	--{"rori_space_station", 4800, -4450.57, 484.75, {CUBOID, 6144, 6144, 6144}, SPAWNAREA, {"naboo_traffic"}, 24},
	--{"rori_space_station_nospawn", 4800, -4450.57, 484.75, {SPHERE, 1024}, NOSPAWNAREA},

	--{"imperial_naboo", 3511.83, 1774.71, 944.36, {SPHERE, 4096}, SPAWNAREA, {"imperial_easy"}, 12},
	--{"imperial_naboo_nospawn", 6226.22, -4450.57, 484.75, {SPHERE, 512}, NOSPAWNAREA},
}
