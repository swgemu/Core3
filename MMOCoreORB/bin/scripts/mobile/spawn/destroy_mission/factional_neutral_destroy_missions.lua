factional_neutral_destroy_missions = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,

	destroyMissionSpawns = {
		{
			lairTemplateName = "global_criminal_neutral_none",
			minDifficulty = 7,
			maxDifficulty = 7,
			size = 25,
		}
	}
}

addDestroyMissionGroup("factional_neutral_destroy_missions", factional_neutral_destroy_missions);
