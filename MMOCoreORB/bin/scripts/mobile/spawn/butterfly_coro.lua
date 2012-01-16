butterfly_coro = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 15,

	lairSpawns = {
		{
			lairTemplateName = "capper_spineflap_easy",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 20,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "capper_spineflap_medium",
			spawnLimit = -1,
			minDifficulty = 60,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 25,
			size = 25
		}
	}
}

addLairGroup("butterfly_coro", butterfly_coro);
