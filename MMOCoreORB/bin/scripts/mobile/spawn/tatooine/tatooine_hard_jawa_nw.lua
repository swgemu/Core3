tatooine_hard_jawa_nw = {
	lairSpawns = {
		{
			lairTemplateName = "tatooine_jawa_squad_neutral_none",
			spawnLimit = -1,
			minDifficulty = 18,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 35,
			size = 15,
		},
		{
			lairTemplateName = "tatooine_jawa_troop_neutral_none",
			spawnLimit = -1,
			minDifficulty = 24,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 35,
			size = 15,
		},
		{
			lairTemplateName = "tatooine_jawa_warband_neutral_none",
			spawnLimit = -1,
			minDifficulty = 20,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 15,
			size = 20,
		},
	}
}

addSpawnGroup("tatooine_hard_jawa_nw", tatooine_hard_jawa_nw);
