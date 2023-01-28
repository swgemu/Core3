tatooine_medium_bugland_ne = {
	lairSpawns = {
		{
			lairTemplateName = "tatooine_kreetle_herd_neutral_none",
			spawnLimit = -1,
			minDifficulty = 3,
			maxDifficulty = 10,
			numberToSpawn = 15,
			weighting = 80,
			size = 15,
		},
		{
			lairTemplateName = "tatooine_kreetle_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 3,
			maxDifficulty = 10,
			numberToSpawn = 15,
			weighting = 20,
			size = 15,
		},
	}
}

addSpawnGroup("tatooine_medium_bugland_ne", tatooine_medium_bugland_ne);
