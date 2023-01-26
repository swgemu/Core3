rori_medium_tusk_cat_ne = {
	lairSpawns = {
		{
			lairTemplateName = "rori_borgle_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 20,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 45,
			size = 25,
		},
		{
			lairTemplateName = "rori_borgle_pack_neutral_none",
			spawnLimit = -1,
			minDifficulty = 30,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 50,
			size = 25,
		},
		{
			lairTemplateName = "rori_borgle_gruntling_neutral_none",
			spawnLimit = -1,
			minDifficulty = 30,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 40,
			size = 25,
		},
	}
}

addSpawnGroup("rori_medium_tusk_cat_ne", rori_medium_tusk_cat_ne);
