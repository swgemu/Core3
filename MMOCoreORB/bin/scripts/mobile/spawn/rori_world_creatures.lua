rori_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "rori_squall_meek_avenger_neutral_none",
			spawnLimit = -1,
			minDifficulty = 5,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_squall_warren_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 5,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_ikopi_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 6,
			maxDifficulty = 8,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_sickle_rasp_nest_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 7,
			maxDifficulty = 9,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_borgle_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 14,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_forest_mite_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 12,
			maxDifficulty = 16,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_tattered_torton_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 15,
			maxDifficulty = 19,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "rori_torton_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 21,
			maxDifficulty = 27,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("rori_world_creatures", rori_world_creatures);
