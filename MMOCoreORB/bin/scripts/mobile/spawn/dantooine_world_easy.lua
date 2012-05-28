dantooine_world_easy = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "dantooine_quenker_bile_drenched_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_voritor_tracker_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 50,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_graul_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_graul_mauler_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_huurton_pack_neutral_none",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_piket_plains_walker_herd_neutral_none",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_quenker_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_thune_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 80,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_bol_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 20,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("dantooine_world_easy", dantooine_world_easy);
