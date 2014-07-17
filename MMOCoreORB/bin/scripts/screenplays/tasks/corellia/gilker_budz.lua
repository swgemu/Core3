gilker_budz_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "sneeroos", planetName = "corellia", npcName = "Snee-Roos" }
			},
			secondarySpawns =	
			{
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/gilker_budz_q1_needed.iff", itemName = "Datadisc" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 250 }
			}
		}
	}

npcMapGilkerBudz =
	{
		{
			spawnData = { planetName = "corellia", npcTemplate = "gilker_budz", x = -3336.21, z = 72.4231, y = 2926.19, direction = 277.144, cellID = 0, position = STAND },
			worldPosition = { x = -3336, y = 2926 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/gilker_budz",
			missions = gilker_budz_missions
		}
	}

GilkerBudz = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapGilkerBudz,
	className = "GilkerBudz",
	screenPlayState = "gilker_budz_quest",
	distance = 800
}

registerScreenPlay("GilkerBudz", true)

gilker_budz_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = GilkerBudz
}

gilker_budz_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = GilkerBudz
}