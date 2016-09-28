scolex_grath_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "mining_rep_quest_scolex", npcName = "Jinz Finzer" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 1200 }
			}
		}
	}

npcMapScolexGrath =
	{
		{
			spawnData = { npcTemplate = "scolex_grath", x = 3347.3, z = 308.0, y = 5490.6, direction = 87, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/scolex_grath",
			missions = scolex_grath_missions
		},
	}

ScolexGrath = ThemeParkLogic:new {
	npcMap = npcMapScolexGrath,
	className = "ScolexGrath",
	screenPlayState = "scolex_grath_task",
	planetName = "corellia",
	distance = 900,
}

registerScreenPlay("ScolexGrath", true)

scolex_grath_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ScolexGrath
}
scolex_grath_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ScolexGrath
}
