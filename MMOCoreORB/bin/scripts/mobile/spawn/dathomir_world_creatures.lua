dathomir_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "dathomir_verne_herd_neutral_none",
			spawnLimit = -1,
			minDifficulty = 7,
			maxDifficulty = 10,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_kwi_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 9,
			maxDifficulty = 12,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_reptilian_flyer_flock_neutral_none",
			spawnLimit = -1,
			minDifficulty = 14,
			maxDifficulty = 18,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_shear_mite_pack_neutral_none",
			spawnLimit = -1,
			minDifficulty = 14,
			maxDifficulty = 18,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_purbole_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 15,
			maxDifficulty = 19,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_bolma_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 17,
			maxDifficulty = 21,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_baz_nitch_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 19,
			maxDifficulty = 25,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dathomir_malkloc_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 19,
			maxDifficulty = 25,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_brackaset_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 23,
			maxDifficulty = 29,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_gaping_spider_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 23,
			maxDifficulty = 29,
			numberToSpawn = 0,
			weighting = 5,
			size = 25
		},
		{
			lairTemplateName = "dathomir_giant_baz_nitch_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 32,
			maxDifficulty = 39,
			numberToSpawn = 0,
			weighting = 5,
			size = 25
		},
		{
			lairTemplateName = "dathomir_rancor_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 45,
			maxDifficulty = 55,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "dathomir_rancor_bull_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 60,
			maxDifficulty = 70,
			numberToSpawn = 0,
			weighting = 5,
			size = 25
		}
	}
}

addLairGroup("dathomir_world_creatures", dathomir_world_creatures);
