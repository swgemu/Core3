corellia_eastern_rogue_corsec_medium = {
	lairSpawns = {
		{
			lairTemplateName = "corellia_corsec_traitor_base_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 22,
			maxDifficulty = 40,
			numberToSpawn = 15,
			weighting = 30,
			size = 25,
		},
		{
			lairTemplateName = "corellia_corellian_butterfly_hive_neutral_large",
			spawnLimit = -1,
			minDifficulty = 22,
			maxDifficulty = 40,
			numberToSpawn = 15,
			weighting = 15,
			size = 25,
		},
		{
			lairTemplateName = "corellia_corellian_butterfly_drone_large_neutral_none",
			spawnLimit = -1,
			minDifficulty = 22,
			maxDifficulty = 40,
			numberToSpawn = 15,
			weighting = 15,
			size = 25,
		},
	}
}

addSpawnGroup("corellia_eastern_rogue_corsec_medium", corellia_eastern_rogue_corsec_medium);
