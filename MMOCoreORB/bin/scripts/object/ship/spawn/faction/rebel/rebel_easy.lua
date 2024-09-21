rebel_easy = {
	{
		shipSpawnGroupName = "ykl37r",

		leadShips = {"z95_tier2"},
		groupShips = {"z95_tier1", "ywing_tier1", "xwing_tier1"},

		spawnLimit = -1,
		numberToSpawn = 4,
		weighting = 10,
		capitalShip = "ykl37r_tier1",
	},
	{
		shipSpawnGroupName = "rebel_mixed_easy",

		leadShips = {"awing_tier1"},
		groupShips = {"z95_tier1", "ywing_tier1", "xwing_tier1", "bwing_tier1", "rebel_shuttle_tier1"},

		spawnLimit = -1,
		numberToSpawn = 5,
		weighting = 50,
		capitalShip = "",
	},
	{
		shipSpawnGroupName = "rebel_xwing_easy",

		leadShips = {"xwing_tier2"},
		groupShips = {"xwing_tier1"},

		spawnLimit = -1,
		numberToSpawn = 5,
		weighting = 75,
		capitalShip = "",
	},
}

addShipSpawnGroup("rebel_easy", rebel_easy);