lok_destroy_missions = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,

	destroyMissionSpawns = {
		{
			lairTemplateName = "lok_pharple_lair_neutral_medium",
			minDifficulty = 4,
			maxDifficulty = 6,
			size = 25,
		},
		{
			lairTemplateName = "lok_flit_lair_neutral_medium",
			minDifficulty = 7,
			maxDifficulty = 10,
			size = 25,
		},
		{
			lairTemplateName = "lok_spinded_snake_lair_neutral_medium",
			minDifficulty = 12,
			maxDifficulty = 16,
			size = 25,
		},
		{
			lairTemplateName = "lok_gurnaset_lair_neutral_medium",
			minDifficulty = 13,
			maxDifficulty = 17,
			size = 25,
		},
		{
			lairTemplateName = "lok_langlatch_lair_neutral_medium",
			minDifficulty = 13,
			maxDifficulty = 17,
			size = 25,
		},
		{
			lairTemplateName = "lok_perlek_pack_neutral_none",
			minDifficulty = 13,
			maxDifficulty = 17,
			size = 25,
		},
		{
			lairTemplateName = "lok_kusak_lair_neutral_medium",
			minDifficulty = 16,
			maxDifficulty = 20,
			size = 25,
		},
		{
			lairTemplateName = "lok_vesp_lair_neutral_medium",
			minDifficulty = 22,
			maxDifficulty = 28,
			size = 25,
		},
		{
			lairTemplateName = "lok_mynock_pack_neutral_none",
			minDifficulty = 22,
			maxDifficulty = 30,
			size = 25,
		},
		{
			lairTemplateName = "lok_gurk_lair_neutral_small",
			minDifficulty = 27,
			maxDifficulty = 34,
			size = 25,
		},
		{
			lairTemplateName = "lok_snorbal_lair_neutral_medium",
			minDifficulty = 27,
			maxDifficulty = 34,
			size = 25,
		},
		{
			lairTemplateName = "lok_blood_razor_camp_neutral_medium_theater",
			minDifficulty = 30,
			maxDifficulty = 40,
			size = 25,
		},
		{
			lairTemplateName = "lok_canyon_corsair_camp_neutral_medium_theater",
			minDifficulty = 26,
			maxDifficulty = 34,
			size = 25,
		},
		{
			lairTemplateName = "lok_canyon_corsair_camp2_neutral_medium_theater",
			minDifficulty = 36,
			maxDifficulty = 50,
			size = 25,
		},
		{
			lairTemplateName = "lok_kimogilla_pack_neutral_none",
			spawnLimit = 15,
			minDifficulty = 85,
			maxDifficulty = 150,
			size = 25,
		}
	}
}

addDestroyMissionGroup("lok_destroy_missions", lok_destroy_missions);
