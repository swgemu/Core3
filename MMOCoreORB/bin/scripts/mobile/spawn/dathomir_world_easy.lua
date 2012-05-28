dathomir_world_easy = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "dathomir_baz_nitch_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 22,
			maxDifficulty = 50,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dathomir_bolma_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 19,
			maxDifficulty = 30,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_brackaset_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 26,
			maxDifficulty = 36,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_rancor_bull_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 65,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 5,
			size = 25
		},
		{
			lairTemplateName = "dathomir_gaping_spider_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 26,
			maxDifficulty = 36,
			numberToSpawn = 0,
			weighting = 5,
			size = 25
		},
		{
			lairTemplateName = "dathomir_giant_baz_nitch_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 35,
			maxDifficulty = 45,
			numberToSpawn = 0,
			weighting = 5,
			size = 25
		},
		{
			lairTemplateName = "dathomir_kwi_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 20,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_malkloc_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 22,
			maxDifficulty = 32,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_purbole_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 17,
			maxDifficulty = 27,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_rancor_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 50,
			maxDifficulty = 100,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_reptilian_flyer_flock_neutral_none",
			spawnLimit = -1,
			minDifficulty = 16,
			maxDifficulty = 26,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_shear_mite_pack_neutral_none",
			spawnLimit = -1,
			minDifficulty = 16,
			maxDifficulty = 26,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_verne_herd_neutral_none",
			spawnLimit = -1,
			minDifficulty = 6,
			maxDifficulty = 16,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		}
	}
}

addLairGroup("dathomir_world_easy", dathomir_world_easy);
