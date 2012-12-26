factional_imperial = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 0,

	lairSpawns = {
		{
			
			lairTemplateName = "rebel_npc",
			spawnLimit = 0,
			minDifficulty = 12,
			maxDifficulty = 18,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},
		{
			
			lairTemplateName = "rebel",
			spawnLimit = 0,
			minDifficulty = 22,
			maxDifficulty = 28,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},
		{
			
			lairTemplateName = "global_rebel_resistance_dissident_camp_rebel_small_theater",
			spawnLimit = 0,
			minDifficulty = 5,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},
		{
			
			lairTemplateName = "global_rebel_resistance_anarchist_camp_rebel_small_theater",
			spawnLimit = 0,
			minDifficulty = 7,
			maxDifficulty = 11,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},
		{
			
			lairTemplateName = "global_rebel_patrol_camp_rebel_small_theater",
			spawnLimit = 0,
			minDifficulty = 16,
			maxDifficulty = 22,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},
	}
}

addLairGroup("factional_imperial", factional_imperial);
