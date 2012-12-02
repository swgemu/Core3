dantooine_hard_graul = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 1024,

	lairSpawns = {
		{
			lairTemplateName = "dantooine_graul_ancient_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 40,
			maxDifficulty = 60,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		},
		{
			lairTemplateName = "dantooine_graul_frenzied_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 40,
			maxDifficulty = 60,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		}
	}
}

addLairGroup("dantooine_hard_graul", dantooine_hard_graul);