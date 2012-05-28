talus_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "talus_song_rasp_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 8,
			maxDifficulty = 18,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_fynock_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 12,
			maxDifficulty = 22,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_guf_drolg_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 14,
			maxDifficulty = 24,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_huf_dun_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 21,
			maxDifficulty = 31,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_kima_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 18,
			maxDifficulty = 28,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_roba_lair_neutral_large",
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
