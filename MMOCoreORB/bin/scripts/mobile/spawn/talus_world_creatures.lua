talus_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "flite_rasp_lair",
			spawnLimit = -1,
			minDifficulty = 8,
			maxDifficulty = 18,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "fynock_lair",
			spawnLimit = -1,
			minDifficulty = 12,
			maxDifficulty = 22,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "guf_drolg_lair",
			spawnLimit = -1,
			minDifficulty = 14,
			maxDifficulty = 24,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "huf_dun_lair",
			spawnLimit = -1,
			minDifficulty = 21,
			maxDifficulty = 31,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "kima_lair",
			spawnLimit = -1,
			minDifficulty = 18,
			maxDifficulty = 28,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "roba_lair",
			spawnLimit = -1,
			minDifficulty = 26,
			maxDifficulty = 36,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("talus_world_creatures", talus_world_creatures);
