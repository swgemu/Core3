talus_decay_mite_medium = {
	lairSpawns = {
		{
			lairTemplateName = "talus_decay_mite_lair_neutral_boss_04",
			spawnLimit = -1,
			minDifficulty = 45,
			maxDifficulty = 55,
			numberToSpawn = 15,
			weighting = 15,
			size = 25,
		},
		{
			lairTemplateName = "talus_rot_mite_pack_neutral_none",
			spawnLimit = -1,
			minDifficulty = 45,
			maxDifficulty = 55,
			numberToSpawn = 15,
			weighting = 15,
			size = 25,
		},
		{
			lairTemplateName = "talus_decay_mite_lair_neutral_small_03",
			spawnLimit = -1,
			minDifficulty = 45,
			maxDifficulty = 55,
			numberToSpawn = 15,
			weighting = 15,
			size = 25,
		},
	}
}

addSpawnGroup("talus_decay_mite_medium", talus_decay_mite_medium);
