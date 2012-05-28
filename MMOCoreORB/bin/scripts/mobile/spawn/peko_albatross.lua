peko_albatross = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 5,

	lairSpawns = {
		{
			lairTemplateName = "naboo_peko_peko_albatross_neutral_none",
			spawnLimit = -1,
			minDifficulty = 99,
			maxDifficulty = 155,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("peko_albatross", peko_albatross);
