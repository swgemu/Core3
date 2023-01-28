tatooine_hard_jabba_thug_sw = {
	lairSpawns = {
		{
			lairTemplateName = "tatooine_jabba_assasin_camp_neutral_large_theater",
			spawnLimit = -1,
			minDifficulty = 150,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 30,
			size = 40,
		},
		{
			lairTemplateName = "tatooine_jabba_enforcer_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 60,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 35,
			size = 20,
		},
		{
			lairTemplateName = "tatooine_jabba_swooper_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 12,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 5,
			size = 10,
		},
	}
}

addSpawnGroup("tatooine_hard_jabba_thug_sw", tatooine_hard_jabba_thug_sw);
