coro_test = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 5,

	lairSpawns = {
		{
			lairTemplateName = "cu_pa_medium",
			spawnLimit = -1,
			minDifficulty = 60,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 25,
			size = 25
		}
	}
}

addLairGroup("coro_test", coro_test);
