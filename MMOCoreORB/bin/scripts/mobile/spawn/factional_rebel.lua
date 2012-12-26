factional_rebel = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 0,

	lairSpawns = {
		
		{
			lairTemplateName = "imperial_banner",
			spawnLimit = 0,
			minDifficulty = 14,
			maxDifficulty = 20,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},	
		{
			lairTemplateName = "imperial",
			spawnLimit = 0,
			minDifficulty = 22,
			maxDifficulty = 28,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},
		
		{
			lairTemplateName = "global_stormtrooper",
			spawnLimit = -1,
			minDifficulty = 22,
			maxDifficulty = 28,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},
		{
			lairTemplateName = "global_imperial_cadet_camp_imperial_small_theater",
			spawnLimit = 0,
			minDifficulty = 6,
			maxDifficulty = 8,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},
        {
			lairTemplateName = "global_imperial_cadet_senior_camp_imperial_small_theater",
			spawnLimit = 0,
			minDifficulty = 8,
			maxDifficulty = 12,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},
		{
			lairTemplateName = "global_imperial_cadet_squadleader_camp_imperial_small_theater",
			spawnLimit = 0,
			minDifficulty = 9,
			maxDifficulty = 13,
			numberToSpawn = 0,
			weighting = 5,
			size = 15,
		},
	
	
	
	}
}

addLairGroup("factional_rebel", factional_rebel);
