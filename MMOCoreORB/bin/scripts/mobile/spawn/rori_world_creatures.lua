rori_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "borgle_lair",
			spawnLimit = -1,
			minDifficulty = 12,
			maxDifficulty = 22,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "horned_rasp_lair",
			spawnLimit = -1,
			minDifficulty = 6,
			maxDifficulty = 16,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "ikopi_lair",
			spawnLimit = -1,
			minDifficulty = 7,
			maxDifficulty = 17,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "squall_lair",
			spawnLimit = -1,
			minDifficulty = 6,
			maxDifficulty = 16,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "torton_lair",
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
