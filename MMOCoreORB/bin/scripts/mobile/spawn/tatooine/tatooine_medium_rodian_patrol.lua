tatooine_medium_rodian_patrol = {
	lairSpawns = {
		{
			lairTemplateName = "global_rodian_tribe_camp",
			spawnLimit = -1,
			minDifficulty = 15,
			maxDifficulty = 20,
			numberToSpawn = 15,
			weighting = 15,
			size = 25,
		},
		{
			lairTemplateName = "tatooine_feral_bantha_herd_neutral_none",
			spawnLimit = -1,
			minDifficulty = 15,
			maxDifficulty = 20,
			numberToSpawn = 15,
			weighting = 15,
			size = 25,
		},
		{
			lairTemplateName = "tatooine_giant_worrt_herd_neutral_none",
			spawnLimit = -1,
			minDifficulty = 15,
			maxDifficulty = 20,
			numberToSpawn = 15,
			weighting = 15,
			size = 25,
		},
	}
}

addSpawnGroup("tatooine_medium_rodian_patrol", tatooine_medium_rodian_patrol);
