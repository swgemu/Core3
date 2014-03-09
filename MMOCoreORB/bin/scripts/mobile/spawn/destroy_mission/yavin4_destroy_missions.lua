yavin4_destroy_missions = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,

	destroyMissionSpawns = {
		{
			lairTemplateName = "yavin4_tanc_mite_lair_neutral_medium",
			minDifficulty = 8,
			maxDifficulty = 11,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_gackle_bat_lair_neutral_medium",
			minDifficulty = 8,
			maxDifficulty = 12,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_spined_puc_lair_neutral_medium",
			minDifficulty = 12,
			maxDifficulty = 16,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_stintaril_lair_neutral_medium",
			minDifficulty = 12,
			maxDifficulty = 16,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_choku_herd_neutral_none",
			minDifficulty = 13,
			maxDifficulty = 18,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_whisper_bird_lair_neutral_medium",
			minDifficulty = 14,
			maxDifficulty = 18,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_kliknik_lair_neutral_medium",
			minDifficulty = 16,
			maxDifficulty = 20,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_mamien_pack_neutral_none",
			minDifficulty = 16,
			maxDifficulty = 21,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_skreeg_lair_neutral_hard",
			minDifficulty = 16,
			maxDifficulty = 22,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_angler_lair_neutral_medium",
			minDifficulty = 19,
			maxDifficulty = 25,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_mawgax_herd_neutral_none",
			minDifficulty = 20,
			maxDifficulty = 26,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_tybis_lair_neutral_medium",
			minDifficulty = 21,
			maxDifficulty = 27,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_crystal_snake_lair_neutral_medium",
			minDifficulty = 22,
			maxDifficulty = 28,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_angler_pack_neutral_none",
			minDifficulty = 26,
			maxDifficulty = 34,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_mawgax_lair_neutral_medium",
			minDifficulty = 28,
			maxDifficulty = 36,
			size = 25,
		},
		{
			lairTemplateName = "yavin4_hutt_expedition_force_camp_hutt_medium_theater",
			minDifficulty = 14,
			maxDifficulty = 22,
			size = 25,
		},
	}
}

addDestroyMissionGroup("yavin4_destroy_missions", yavin4_destroy_missions);
