factional_neutral_destroy_missions = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 0,

	lairSpawns = {
		{
			lairTemplateName = "global_criminal_neutral_none",
			spawnLimit = 0,
			minDifficulty = 7,
			maxDifficulty = 7,
			numberToSpawn = 0,
			weighting = 5,
			size = 15
		}
	}
}

addLairGroup("factional_neutral_destroy_missions", factional_neutral_destroy_missions);
