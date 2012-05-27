endor_world_creatures = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 2048,

	lairSpawns = {
		{
			lairTemplateName = "endor_bark_mite_burrower_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 20,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_blooming_jax_neutral_none",
			spawnLimit = -1,
			minDifficulty = 27,
			maxDifficulty = 37,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_blurrg_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 50,
			maxDifficulty = 60,
			numberToSpawn = 0,
			weighting = 10,
			size = 25
		},
		{
			lairTemplateName = "endor_blushing_jax_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 27,
			maxDifficulty = 37,
			numberToSpawn = 0,
			weighting = 10,
			size = 25
		},
		{
			lairTemplateName = "endor_boar_wolf_lair_neutral_small",
			spawnLimit = -1,
			minDifficulty = 25,
			maxDifficulty = 35,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_bordok_stud_mare_neutral_small",
			spawnLimit = -1,
			minDifficulty = 10,
			maxDifficulty = 20,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_gurreck_neutral_none",
			spawnLimit = -1,
			minDifficulty = 50,
			maxDifficulty = 60,
			numberToSpawn = 0,
			weighting = 10,
			size = 25
		},
		{
			lairTemplateName = "endor_lantern_bird_neutral_small",
			spawnLimit = -1,
			minDifficulty = 21,
			maxDifficulty = 31,
			numberToSpawn = 0,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "endor_swirl_prong_neutral_small",
			spawnLimit = -1,
			minDifficulty = 19,
			maxDifficulty = 29,
			numberToSpawn = 0,
			weighting = 30,
			size = 25
		}
	}
}

addLairGroup("endor_world_creatures", endor_world_creatures);
