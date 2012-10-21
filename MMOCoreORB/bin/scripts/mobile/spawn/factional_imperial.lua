factional_imperial = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 0,

	lairSpawns = {
		{
			
			lairTemplateName = "rebel_npc",
			spawnLimit = 0,
			minDifficulty = 15,
			maxDifficulty = 15,
			numberToSpawn = 0,
			weighting = 5,
			size = 15
		},
		{
			
			lairTemplateName = "rebel",
			spawnLimit = 0,
			minDifficulty = 25,
			maxDifficulty = 25,
			numberToSpawn = 0,
			weighting = 5,
			size = 15
		},
	}
}

addLairGroup("factional_imperial", factional_imperial);
