tatooine_test = {
	wanderRadius = 10,
	commandLevel = 0,
		
	type = LAIR,
	
	maxSpawnLimit = 80,
	
	lairSpawns = {
		{   
			lairTemplateName = "cu_pa_easy",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 15,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		}
	}
}

addLairGroup("tatooine_test", tatooine_test);
