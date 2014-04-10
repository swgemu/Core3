dantooine_destroy_missions = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,

	destroyMissionSpawns = {
		{
			lairTemplateName = "dantooine_bol_herd_neutral_none",
			minDifficulty = 8,
			maxDifficulty = 12,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_huurton_howler_lair_neutral_medium",
			minDifficulty = 14,
			maxDifficulty = 18,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_quenker_lair_neutral_medium",
			minDifficulty = 20,
			maxDifficulty = 26,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_thune_lair_neutral_medium",
			minDifficulty = 23,
			maxDifficulty = 29,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_bol_lair_neutral_medium",
			minDifficulty = 24,
			maxDifficulty = 32,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_graul_lair_neutral_medium",
			minDifficulty = 27,
			maxDifficulty = 34,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_piket_plains_walker_herd_neutral_none",
			minDifficulty = 28,
			maxDifficulty = 36,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_quenker_bile_drenched_lair_neutral_medium",
			minDifficulty = 30,
			maxDifficulty = 38,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_graul_mauler_lair_neutral_large",
			minDifficulty = 31,
			maxDifficulty = 39,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_voritor_tracker_lair_neutral_medium",
			minDifficulty = 40,
			maxDifficulty = 50,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_mokk_scout_neutral_none",
			minDifficulty = 35,
			maxDifficulty = 55,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_kunga_scout_neutral_none",
			minDifficulty = 35,
			maxDifficulty = 55,
			size = 25,
		},
		{
			lairTemplateName = "dantooine_janta_scout_neutral_none",
			minDifficulty = 35,
			maxDifficulty = 55,
			size = 25,
		},
	}
}

addDestroyMissionGroup("dantooine_destroy_missions", dantooine_destroy_missions);
