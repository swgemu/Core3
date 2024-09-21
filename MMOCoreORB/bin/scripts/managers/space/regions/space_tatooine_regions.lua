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

space_tatooine_regions = {
}
