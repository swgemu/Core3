endor_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "endor_squall_rabid_neutral_small",
			spawnLimit = -1,
			minDifficulty = 8,
			maxDifficulty = 11,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_bark_mite_burrower_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 9,
			maxDifficulty = 12,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_pouncing_jax_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 11,
			maxDifficulty = 15,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_swirl_prong_neutral_small",
			spawnLimit = -1,
			minDifficulty = 17,
			maxDifficulty = 22,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		},
		{
			lairTemplateName = "endor_lantern_bird_neutral_small",
			spawnLimit = -1,
			minDifficulty = 19,
			maxDifficulty = 24,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_boar_wolf_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 22,
			maxDifficulty = 28,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_blooming_jax_neutral_none",
			spawnLimit = -1,
			minDifficulty = 24,
			maxDifficulty = 30,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_blushing_jax_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 24,
			maxDifficulty = 30,
			numberToSpawn = 0,
			weighting = 10,
			size = 25
		},
		{
			lairTemplateName = "endor_bordok_stud_mare_neutral_small",
			spawnLimit = -1,
			minDifficulty = 30,
			maxDifficulty = 38,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_blurrg_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 45,
			maxDifficulty = 55,
			numberToSpawn = 0,
			weighting = 10,
			size = 25
		},
		{
			lairTemplateName = "endor_gurreck_neutral_none",
			spawnLimit = -1,
			minDifficulty = 45,
			maxDifficulty = 55,
			numberToSpawn = 0,
			weighting = 10,
			size = 25
		}
	}
}

addLairGroup("endor_world_creatures", endor_world_creatures);
