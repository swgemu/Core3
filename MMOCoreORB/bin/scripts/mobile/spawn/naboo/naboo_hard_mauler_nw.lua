naboo_hard_mauler_nw = {
	lairSpawns = {
		{
			lairTemplateName = "naboo_mauler_sect_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 30,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 20,
			size = 22,
		},
		{
			lairTemplateName = "naboo_mauler_roamers_neutral_none",
			spawnLimit = -1,
			minDifficulty = 50,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 25,
			size = 22,
		},
		{
			lairTemplateName = "naboo_mauler_pilgrimage_neutral_none",
			spawnLimit = -1,
			minDifficulty = 75,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 25,
			size = 22,
		},
		{
			lairTemplateName = "naboo_mauler_conclave_neutral_large_theater",
			spawnLimit = -1,
			minDifficulty = 75,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 25,
			size = 22,
		},
	}
}

addSpawnGroup("naboo_hard_mauler_nw", naboo_hard_mauler_nw);
