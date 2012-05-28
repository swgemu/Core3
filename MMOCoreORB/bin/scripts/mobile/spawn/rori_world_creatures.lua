rori_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "rori_borgle_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 12,
			maxDifficulty = 22,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_sickle_rasp_nest_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 6,
			maxDifficulty = 16,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_ikopi_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 7,
			maxDifficulty = 17,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_squall_warren_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 6,
			maxDifficulty = 16,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_torton_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 24,
			maxDifficulty = 34,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("rori_world_creatures", rori_world_creatures);
