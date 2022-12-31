lok_volcano = {
	lairSpawns = {
		{
			lairTemplateName = "lok_mynock_pack_neutral_none",
			spawnLimit = 1,
			minDifficulty = 120,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 50,
			size = 15,
		},
		{
			lairTemplateName = "lok_mynock_lair_neutral_medium",
			spawnLimit = 1,
			minDifficulty = 90,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 50,
			size = 15,
		},
		{
			lairTemplateName = "lok_spinded_snake_lair2_neutral_medium",
			spawnLimit = 1,
			minDifficulty = 128,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 50,
			size = 15,
		},
		{
			lairTemplateName = "lok_spined_snake_pack2_neutral_none",
			spawnLimit = 1,
			minDifficulty = 60,
			maxDifficulty = 500,
			numberToSpawn = 15,
			weighting = 50,
			size = 15,
		},
	}
}

addSpawnGroup("lok_volcano", lok_volcano);
