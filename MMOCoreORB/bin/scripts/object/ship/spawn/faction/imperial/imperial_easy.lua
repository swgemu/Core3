imperial_easy = {
	{
		shipSpawnGroupName = "decimator",

		leadShips = {"tieinterceptor_tier2"},
		groupShips = {"tieinterceptor_tier1"},

		spawnLimit = -1,
		numberToSpawn = 4,
		weighting = 10,
		capitalShip = "decimator_tier_1",
	},
	{
		shipSpawnGroupName = "imperial_mixed_easy",

		leadShips = {"tieadvanced_tier1"},
		groupShips = {"tieaggressor_tier1", "tiebomber_tier1", "tiefighter_tier1", "tiefighter_tier1", "tieoppressor_tier1"},

		spawnLimit = -1,
		numberToSpawn = 5,
		weighting = 30,
		capitalShip = "",
	},
	{
		shipSpawnGroupName = "imperial_tie_easy",

		leadShips = {"tiefighter_tier2"},
		groupShips = {"tiefighter_tier1"},

		spawnLimit = -1,
		numberToSpawn = 5,
		weighting = 60,
		capitalShip = "",
	},
}

addShipSpawnGroup("imperial_easy", imperial_easy);
