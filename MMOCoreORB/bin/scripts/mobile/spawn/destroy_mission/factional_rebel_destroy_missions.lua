factional_rebel_destroy_missions = {

	lairSpawns = {
		{
			lairTemplateName = "imperial_banner",
			minDifficulty = 14,
			maxDifficulty = 20,
			size = 25,
		},
		{
			lairTemplateName = "imperial",
			minDifficulty = 22,
			maxDifficulty = 28,
			size = 25,
		},
		{
			lairTemplateName = "global_stormtrooper",
			minDifficulty = 22,
			maxDifficulty = 28,
			size = 25,
		},
		{
			lairTemplateName = "global_imperial_cadet_camp_imperial_small_theater",
			minDifficulty = 6,
			maxDifficulty = 8,
			size = 25,
		},
        	{
			lairTemplateName = "global_imperial_cadet_senior_camp_imperial_small_theater",
			minDifficulty = 8,
			maxDifficulty = 12,
			size = 25,
		},
		{
			lairTemplateName = "global_imperial_cadet_squadleader_camp_imperial_small_theater",
			minDifficulty = 9,
			maxDifficulty = 13,
			size = 25,
		},
	}
}

addDestroyMissionGroup("factional_rebel_destroy_missions", factional_rebel_destroy_missions);
