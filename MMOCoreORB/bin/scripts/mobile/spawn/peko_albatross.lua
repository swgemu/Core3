peko_albatross = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "peko_albatross_lair",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("peko_albatross", peko_albatross);
