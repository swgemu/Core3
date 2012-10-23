factional_rebel = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 0,

	lairSpawns = {
		
		{
			lairTemplateName = "imperial_banner",
			spawnLimit = 0,
			minDifficulty = 11,
			maxDifficulty = 11,
			numberToSpawn = 0,
			weighting = 5,
			size = 15
		},	
		{
			lairTemplateName = "imperial",
			spawnLimit = 0,
			minDifficulty = 25,
			maxDifficulty = 25,
			numberToSpawn = 0,
			weighting = 5,
			size = 15
		},
		
		{
			lairTemplateName = "global_stormtrooper",
			spawnLimit = -1,
			minDifficulty = 7,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 5,
			size = 15
		},
		{
			lairTemplateName = "global_imperial_cadet_camp_imperial_small_theater",
			spawnLimit = 0,
			minDifficulty = 7,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 5,
			size = 15
		},
        {
			lairTemplateName = "global_imperial_cadet_senior_camp_imperial_small_theater",
			spawnLimit = 0,
			minDifficulty = 7,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 5,
			size = 15
		},
		{
			lairTemplateName = "global_imperial_cadet_squadleader_camp_imperial_small_theater",
			spawnLimit = 0,
			minDifficulty = 7,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 5,
			size = 15
		},
	
	
	
	}
}

addLairGroup("factional_rebel", factional_rebel);
