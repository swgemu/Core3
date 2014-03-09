rori_destroy_missions = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,

	destroyMissionSpawns = {
		{
			lairTemplateName = "rori_squall_warren_neutral_medium",
			minDifficulty = 5,
			maxDifficulty = 7,
			size = 25,
		},
		{
			lairTemplateName = "rori_capper_spineflap_hive_neutral_large",
			minDifficulty = 5,
			maxDifficulty = 7,
			size = 25,
		},
		{
			lairTemplateName = "rori_ikopi_lair_neutral_medium",
			minDifficulty = 6,
			maxDifficulty = 8,
			size = 25,
		},
		{
			lairTemplateName = "rori_nightspider_lair_neutral_small",
			minDifficulty = 6,
			maxDifficulty = 8,
			size = 25,
		},
		{
			lairTemplateName = "rori_sickle_rasp_nest_neutral_medium",
			minDifficulty = 7,
			maxDifficulty = 9,
			size = 25,
		},
		{
			lairTemplateName = "rori_nudfuh_lair_neutral_medium",
			minDifficulty = 8,
			maxDifficulty = 10,
			size = 25,
		},
		{
			lairTemplateName = "rori_borgle_lair_neutral_large",
			minDifficulty = 10,
			maxDifficulty = 14,
			size = 25,
		},
		{
			lairTemplateName = "rori_fuzzy_jax_lair_neutral_medium",
			minDifficulty = 11,
			maxDifficulty = 15,
			size = 25,
		},
		{
			lairTemplateName = "rori_nudfuh_pack_neutral_none",
			minDifficulty = 11,
			maxDifficulty = 15,
			size = 25,
		},
		{
			lairTemplateName = "rori_gualama_small_lair_neutral_medium",
			minDifficulty = 11,
			maxDifficulty = 15,
			size = 25,
		},
		{
			lairTemplateName = "rori_kai_tok_lair_neutral_medium",
			minDifficulty = 11,
			maxDifficulty = 16,
			size = 25,
		},
		{
			lairTemplateName = "rori_forest_mite_lair_neutral_small",
			minDifficulty = 12,
			maxDifficulty = 16,
			size = 25,
		},
		{
			lairTemplateName = "rori_vrobal_lair_neutral_medium",
			minDifficulty = 12,
			maxDifficulty = 16,
			size = 25,
		},
		{
			lairTemplateName = "pugoriss",
			minDifficulty = 12,
			maxDifficulty = 16,
			size = 25,
		},
		{
			lairTemplateName = "rori_chared_krevol_lair_neutral_medium",
			minDifficulty = 13,
			maxDifficulty = 17,
			size = 25,
		},
		{
			lairTemplateName = "rori_savage_pugoriss_lair_neutral_medium",
			minDifficulty = 13,
			maxDifficulty = 17,
			size = 25,
		},
		{
			lairTemplateName = "tusk_cat",
			minDifficulty = 14,
			maxDifficulty = 18,
			size = 25,
		},
		{
			lairTemplateName = "rori_tattered_torton_lair_neutral_large",
			minDifficulty = 15,
			maxDifficulty = 19,
			size = 25,
		},
		{
			lairTemplateName = "rori_torton_lair_neutral_large",
			minDifficulty = 21,
			maxDifficulty = 27,
			size = 25,
		},
		{
			lairTemplateName = "rori_ravenous_torton_lair_neutral_large",
			minDifficulty = 30,
			maxDifficulty = 38,
			size = 25,
		},
		{
			lairTemplateName = "rori_kobola_miner_base_neutral_large_theater",
			minDifficulty = 6,
			maxDifficulty = 14,
			size = 25,
		},
		{
			lairTemplateName = "rori_kobola_underboss_base_neutral_large_theater",
			minDifficulty = 19,
			maxDifficulty = 28,
			size = 25,
		}
	}
}

addDestroyMissionGroup("rori_destroy_missions", rori_destroy_missions);
