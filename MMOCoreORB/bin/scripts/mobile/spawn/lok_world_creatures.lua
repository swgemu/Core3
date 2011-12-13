lok_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "desert_vesp_lair",
			spawnLimit = -1,
			minDifficulty = 30,
			maxDifficulty = 40,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "feral_gurk_lair",
			spawnLimit = -1,
			minDifficulty = 34,
			maxDifficulty = 44,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "flit_lair",
			spawnLimit = -1,
			minDifficulty = 8,
			maxDifficulty = 18,
			numberToSpawn = 0,
			weighting = 25,
			size = 25
		},
		{
			lairTemplateName = "gurk_lair",
			spawnLimit = -1,
			minDifficulty = 30,
			maxDifficulty = 40,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "gurnaset_lair",
			spawnLimit = -1,
			minDifficulty = 15,
			maxDifficulty = 25,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "kusak_lair",
			spawnLimit = -1,
			minDifficulty = 18,
			maxDifficulty = 28,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "langlatch_lair",
			spawnLimit = -1,
			minDifficulty = 20,
			maxDifficulty = 30,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "vesp_lair",
			spawnLimit = -1,
			minDifficulty = 93,
			maxDifficulty = 103,
			numberToSpawn = 0,
			weighting = 5,
			size = 25
		}
	}
}

addLairGroup("lok_world_creatures", lok_world_creatures);
