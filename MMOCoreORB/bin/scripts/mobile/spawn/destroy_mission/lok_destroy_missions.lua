lok_destroy_missions = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 0,

	lairSpawns = {
		{
			lairTemplateName = "lok_pharple_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 4,
			maxDifficulty = 6,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_flit_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 7,
			maxDifficulty = 10,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_spinded_snake_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 12,
			maxDifficulty = 16,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_gurnaset_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 13,
			maxDifficulty = 17,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_langlatch_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 13,
			maxDifficulty = 17,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_perlek_pack_neutral_none",
			spawnLimit = -1,
			minDifficulty = 13,
			maxDifficulty = 17,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_kusak_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 16,
			maxDifficulty = 20,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_vesp_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 22,
			maxDifficulty = 28,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_mynock_pack_neutral_none",
			spawnLimit = -1,
			minDifficulty = 22,
			maxDifficulty = 30,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_gurk_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 27,
			maxDifficulty = 34,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_snorbal_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 27,
			maxDifficulty = 34,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_blood_razor_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 30,
			maxDifficulty = 40,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_canyon_corsair_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 26,
			maxDifficulty = 34,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_canyon_corsair_camp2_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 36,
			maxDifficulty = 50,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "lok_kimogilla_pack_neutral_none",
			spawnLimit = 15,
			minDifficulty = 85,
			maxDifficulty = 150,
			numberToSpawn = 0,
			weighting = 3,
			size = 25
		}
	}
}

addLairGroup("lok_destroy_missions", lok_destroy_missions);
