skinkner_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "dancer_agent_quest_skinkner", npcName = "Kalar'naa" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 150 }
			}
		}
	}

npcMapSkinkner =
	{
		{
			spawnData = { npcTemplate = "skinkner", x = 10.3, z = -0.9, y = 21.7, direction = -142, cellID = 3005403, position = SIT },
			worldPosition = { x = -3456.1, y = 3086.9 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/skinkner",
			missions = skinkner_missions
		},
	}

Skinkner = ThemeParkLogic:new {
	npcMap = npcMapSkinkner,
	className = "Skinkner",
	screenPlayState = "skinkner_task",
	planetName = "corellia",
	distance = 900,
}

registerScreenPlay("Skinkner", true)

skinkner_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = Skinkner
}
skinkner_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = Skinkner
}
