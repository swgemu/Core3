lok_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "lok_vesp_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 30,
			maxDifficulty = 40,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_gurk_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 34,
			maxDifficulty = 44,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_flit_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 8,
			maxDifficulty = 18,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_gurk_lair_neutral_small_01",
			spawnLimit = -1,
			minDifficulty = 30,
			maxDifficulty = 40,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_gurnaset_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 15,
			maxDifficulty = 25,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_kusak_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 18,
			maxDifficulty = 28,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_langlatch_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 20,
			maxDifficulty = 30,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("lok_world_creatures", lok_world_creatures);
