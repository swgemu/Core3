tatooine_krayt = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 32,

	lairSpawns = {
		{
			lairTemplateName = "tatooine_evil_settlement_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 3,
			maxDifficulty = 6,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_diseased_bocatt_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 7,
			maxDifficulty = 10,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_dune_lizard_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 16,
			maxDifficulty = 20,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_bocatt_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 19,
			maxDifficulty = 25,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_dragonet_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 24,
			maxDifficulty = 34,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "krayt_dragon",
			spawnLimit = 5,
			minDifficulty = 107,
			maxDifficulty = 137,
			numberToSpawn = 0,
			weighting = 10,
			size = 25
		},
		{
			lairTemplateName = "tatooine_canyon_krayt_dragon_lair_neutral_large",
			spawnLimit = 2,
			minDifficulty = 260,
			maxDifficulty = 290,
			numberToSpawn = 0,
			weighting = 5,
			size = 25
		},
		{
			lairTemplateName = "tatooine_giant_canyon_krayt_dragon_lair_neutral_large",
			spawnLimit = 2,
			minDifficulty = 280,
			maxDifficulty = 300,
			numberToSpawn = 0,
			weighting = 1,
			size = 25
		},
	}
}

addLairGroup("tatooine_krayt", tatooine_krayt);
