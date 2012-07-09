talus_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "talus_rasp_flite_large_neutral_none",
			spawnLimit = -1,
			minDifficulty = 6,
			maxDifficulty = 9,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_decay_mite_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 8,
			maxDifficulty = 11,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_song_rasp_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 9,
			maxDifficulty = 12,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_fynock_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 14,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_guf_drolg_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 12,
			maxDifficulty = 16,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_kima_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 16,
			maxDifficulty = 20,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_huf_dun_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 19,
			maxDifficulty = 24,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "talus_roba_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 23,
			maxDifficulty = 29,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("talus_world_creatures", talus_world_creatures);
