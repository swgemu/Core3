dantooine_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "dantooine_bol_herd_neutral_none",
			spawnLimit = -1,
			minDifficulty = 8,
			maxDifficulty = 12,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "tusk_cat",
			spawnLimit = -1,
			minDifficulty = 14,
			maxDifficulty = 18,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_huurton_pack_neutral_none",
			spawnLimit = -1,
			minDifficulty = 16,
			maxDifficulty = 20,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_quenker_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 20,
			maxDifficulty = 26,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_thune_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 23,
			maxDifficulty = 29,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_bol_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 26,
			maxDifficulty = 32,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_graul_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 27,
			maxDifficulty = 34,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_piket_plains_walker_herd_neutral_none",
			spawnLimit = -1,
			minDifficulty = 28,
			maxDifficulty = 36,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_quenker_bile_drenched_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 30,
			maxDifficulty = 38,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_graul_mauler_lair_neutral_large",
			spawnLimit = -1,
			minDifficulty = 31,
			maxDifficulty = 39,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_voritor_tracker_lair_neutral_medium",
			spawnLimit = -1,
			minDifficulty = 40,
			maxDifficulty = 50,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("dantooine_world_creatures", dantooine_world_creatures);
