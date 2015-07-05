global_hard = {

	lairSpawns = {
		{
			lairTemplateName = "global_dark_adept_neutral_none",
			spawnLimit = 5,
			minDifficulty = 136,
			maxDifficulty = 145,
			numberToSpawn = 0,
			weighting = 3,
			size = 25
		},
		{
			lairTemplateName = "global_dark_jedi_camp_dark_jedi_theater",
			spawnLimit = 3,
			minDifficulty = 261,
			maxDifficulty = 270,
			numberToSpawn = 0,
			weighting = 2,
			size = 20
		},
		{
			lairTemplateName = "global_dark_jedi_knight_neutral_none",
			spawnLimit = 3,
			minDifficulty = 261,
			maxDifficulty = 270,
			numberToSpawn = 0,
			weighting = 2,
			size = 25
		},
		{
			lairTemplateName = "global_dark_jedi_master_neutral_none",
			spawnLimit = 2,
			minDifficulty = 287,
			maxDifficulty = 296,
			numberToSpawn = 0,
			weighting = 1,
			size = 25
		},
	}
}

addSpawnGroup("global_hard", global_hard);
