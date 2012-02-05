coro_newbie = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 50,

	lairSpawns = {
		{
			lairTemplateName = "corellian_butterfly_lair",
			spawnLimit = -1,
			minDifficulty = 7,
			maxDifficulty = 30,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		},
		{
			lairTemplateName = "capper_spineflap_easy",
			spawnLimit = -1,
			minDifficulty = 20,
			maxDifficulty = 30,
			numberToSpawn = 5,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("coro_newbie", coro_newbie);
