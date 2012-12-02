dantooine_world_npc = {
	wanderRadius = 10,
	commandLevel = 0,

	type = LAIR,
	maxSpawnLimit = 1024,

	lairSpawns = {
		{
			lairTemplateName = "dantooine_janta_leader_camp_neutral_large_theater",
			spawnLimit = -1,
			minDifficulty = 0,
			maxDifficulty = 90,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		},
		{
			lairTemplateName = "dantooine_janta_rockshaper_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 0,
			maxDifficulty = 90,
			numberToSpawn = 5,
			weighting = 15,
			size = 25
		},
		{
			lairTemplateName = "dantooine_janta_shaman_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 0,
			maxDifficulty = 90,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		},
		{
			lairTemplateName = "dantooine_janta_warrior_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 0,
			maxDifficulty = 90,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		},
		{
			lairTemplateName = "dantooine_kunga_rockshaper_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 0,
			maxDifficulty = 90,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		},
		{
			lairTemplateName = "dantooine_kunga_warrior_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 0,
			maxDifficulty = 90,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		},
		{
			lairTemplateName = "dantooine_kunga_leader_camp_neutral_large_theater",
			spawnLimit = -1,
			minDifficulty = 0,
			maxDifficulty = 90,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		},
		{
			lairTemplateName = "dantooine_mokk_leader_camp_neutral_large_theater",
			spawnLimit = -1,
			minDifficulty = 0,
			maxDifficulty = 90,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		},
		{
			lairTemplateName = "dantooine_mokk_shaman_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 0,
			maxDifficulty = 90,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		},
		{
			lairTemplateName = "dantooine_mokk_soothsayer_camp_neutral_medium_theater",
			spawnLimit = -1,
			minDifficulty = 0,
			maxDifficulty = 90,
			numberToSpawn = 5,
			weighting = 15,
			size = 15
		}
	}
}

addLairGroup("dantooine_world_npc", dantooine_world_npc);
