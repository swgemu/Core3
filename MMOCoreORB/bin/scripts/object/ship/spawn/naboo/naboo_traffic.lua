naboo_traffic = {
	{
		shipSpawnGroupName = "hutt_light_easy",

		leadShips = {"hutt_light_s01_tier2", "hutt_light_s02_tier2"},
		groupShips = {"hutt_light_s01_tier1", "hutt_light_s02_tier1"},

		spawnLimit = -1,
		numberToSpawn = 5,
		weighting = 35,
		capitalShip = "",
	},
	{
		shipSpawnGroupName = "blacksun_light_easy",

		leadShips = {"blacksun_light_s01_tier2", "blacksun_light_s02_tier2", "blacksun_light_s03_tier2", "blacksun_light_s04_tier2"},
		groupShips = {"blacksun_light_s01_tier1", "blacksun_light_s02_tier1", "blacksun_light_s03_tier1", "blacksun_light_s04_tier1"},

		spawnLimit = -1,
		numberToSpawn = 5,
		weighting = 35,
		capitalShip = "",
	},
	{
		shipSpawnGroupName = "civillian",

		leadShips = {""},
		groupShips = {"civshuttle", "civspeeder1", "civspeeder2", "civtaxi", "civtransport"},

		spawnLimit = -1,
		numberToSpawn = 10,
		weighting = 35,
		capitalShip = "",
	},
}

addShipSpawnGroup("naboo_traffic", naboo_traffic);
