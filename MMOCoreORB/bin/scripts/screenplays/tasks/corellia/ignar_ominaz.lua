ignar_ominaz_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "delivery_agent_quest_ignar", npcName = "a Delivery Agent" }
			},
			secondarySpawns =
			{

			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "race_rival_quest_ignar", npcName = "Dinnik Innik" }
			},
			secondarySpawns =
			{

			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 200 }
			}
		}
	}

npcMapIgnarOminaz =
	{
		{
			spawnData = { npcTemplate = "ignar_ominaz", x = 1806.0, z = 29.9, y = 4989.0, direction = -33, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/ignar_ominaz",
			missions = ignar_ominaz_missions
		}
	}

IgnarOminaz = ThemeParkLogic:new {
	npcMap = npcMapIgnarOminaz,
	className = "IgnarOminaz",
	screenPlayState = "ignar_ominaz_task",
	planetName = "corellia",
	distance = 900,
}

registerScreenPlay("IgnarOminaz", true)

ignar_ominaz_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = IgnarOminaz
}
ignar_ominaz_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = IgnarOminaz
}
