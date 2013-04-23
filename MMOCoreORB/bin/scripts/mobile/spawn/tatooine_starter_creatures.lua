tatooine_starter_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 1280,

	lairSpawns = {
		{
			lairTemplateName = "tatooine_kreetle_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 2,
			maxDifficulty = 4,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_rockmite_swarm_neutral_none",
			spawnLimit = -1,
			minDifficulty = 2,
			maxDifficulty = 4,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_womprat_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 2,
			maxDifficulty = 4,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_evil_settlement_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 2,
			maxDifficulty = 5,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_moisture_settler_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 3,
			maxDifficulty = 5,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_kreetle_over_swarming_neutral_medium_boss_02",
			spawnLimit = -1,
			minDifficulty = 4,
			maxDifficulty = 6,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_gorg_herd_neutral_none",
			spawnLimit = -1,
			minDifficulty = 4,
			maxDifficulty = 6,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_eopie_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 5,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_sevorrt_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 5,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_gorg_glutton_neutral_none",
			spawnLimit = -1,
			minDifficulty = 5,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_diseased_bocatt_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 5,
			maxDifficulty = 8,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_cu_pa_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 7,
			maxDifficulty = 10,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tatooine_alkhara_bandit_patrol_neutral_none",
			spawnLimit = -1,
			minDifficulty = 8,
			maxDifficulty = 11,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("tatooine_starter_creatures", tatooine_starter_creatures);
