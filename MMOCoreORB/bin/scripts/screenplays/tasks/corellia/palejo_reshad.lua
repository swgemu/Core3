palejo_reshad_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "sharpshooter", planetName = "corellia", npcName = "Blackmailer" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 500 }
			}
		}
	}

npcMapPalejoReshad =
	{
		{
			spawnData = { planetName = "corellia", npcTemplate = "palejo_reshad", x = 1.06, z = -0.895, y = 21.22, direction = 111.145, cellID = 3375359, position = STAND },
			worldPosition = { x = 6700, y = -5755 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/palejo_reshad",
			missions = palejo_reshad_missions
		}
	}

PalejoReshad = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapPalejoReshad,
	className = "PalejoReshad",
	screenPlayState = "palejo_reshad_quest",
	distance = 800
}

registerScreenPlay("PalejoReshad", true)

palejo_reshad_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = PalejoReshad
}

palejo_reshad_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = PalejoReshad
}