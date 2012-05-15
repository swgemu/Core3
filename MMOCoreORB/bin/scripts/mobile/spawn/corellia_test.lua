corellia_test = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 20,

	lairSpawns = {
		{
			lairTemplateName = "cu_pa_hard",
			spawnLimit = -1,
			minDifficulty = 90,
			maxDifficulty = 99,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("corellia_test", corellia_test);
