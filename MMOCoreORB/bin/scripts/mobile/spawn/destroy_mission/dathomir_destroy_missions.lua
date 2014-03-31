dathomir_destroy_missions = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,

	destroyMissionSpawns = {
		{
			lairTemplateName = "dathomir_verne_herd_neutral_none",
			minDifficulty = 7,
			maxDifficulty = 10,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_kwi_lair_neutral_small",
			minDifficulty = 9,
			maxDifficulty = 12,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_reptilian_flyer_flock_neutral_none",
			minDifficulty = 14,
			maxDifficulty = 18,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_shear_mite_pack_neutral_none",
			minDifficulty = 14,
			maxDifficulty = 18,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_purbole_lair_neutral_medium",
			minDifficulty = 15,
			maxDifficulty = 19,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_bolma_lair_neutral_medium",
			minDifficulty = 17,
			maxDifficulty = 21,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_baz_nitch_lair_neutral_small",
			minDifficulty = 19,
			maxDifficulty = 25,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_malkloc_lair_neutral_large",
			minDifficulty = 19,
			maxDifficulty = 25,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_reptilian_ancient_flyer_flock_neutral_none",
			minDifficulty = 22,
			maxDifficulty = 28,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_brackaset_lair_neutral_medium",
			minDifficulty = 23,
			maxDifficulty = 29,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_gaping_spider_lair_neutral_medium",
			minDifficulty = 23,
			maxDifficulty = 29,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_giant_baz_nitch_lair_neutral_medium",
			minDifficulty = 32,
			maxDifficulty = 39,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_rhoa_kwi_neutral_none",
			minDifficulty = 32,
			maxDifficulty = 39,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_kamurith_nocuous_neutral_none",
			minDifficulty = 40,
			maxDifficulty = 52,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_rancor_lair_neutral_large",
			minDifficulty = 40,
			maxDifficulty = 60,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_bolma_craggy_lair_neutral_medium",
			minDifficulty = 42,
			maxDifficulty = 52,
			size = 25,
		},
		{
			lairTemplateName = "dathomir_rancor_bull_lair_neutral_large",
			minDifficulty = 60,
			maxDifficulty = 70,
			size = 25,
		}
	}
}

addDestroyMissionGroup("dathomir_destroy_missions", dathomir_destroy_missions);
