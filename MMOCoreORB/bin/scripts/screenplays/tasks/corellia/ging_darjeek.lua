ging_darjeek_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "professor_minnet", npcName = "\"Professor\" Minnet" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/ging_darjeek_q1_needed.iff", itemName = "Minnet's Permit Data" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "sivrool_linnaie", npcName = "Siv'rool Linnaie" }
			},
			secondarySpawns =	
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "thug", npcName = "Listening Post Guy" }
			},
			secondarySpawns =	
			{
				{ npcTemplate = "smuggler", npcName = "a smuggler" },
				{ npcTemplate = "smuggler", npcName = "a smuggler" },
				{ npcTemplate = "smuggler", npcName = "a smuggler" },
				{ npcTemplate = "smuggler", npcName = "a smuggler" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1500 }
			}
		}
	}

npcMapGingDarjeek =
	{
		{
			spawnData = { npcTemplate = "ging_darjeek", x = -24.6629, z = -0.519991, y = 6.12104, direction = -112, cellID = 3375365, position = STAND },
			worldPosition = { x = 6708, y = -5783 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/ging_darjeek",
			missions = ging_darjeek_missions
		}
	}

GingDarjeek = ThemeParkLogic:new {
	npcMap = npcMapGingDarjeek,
	className = "GingDarjeek",
	screenPlayState = "ging_darjeek_quest",
	planetName = "corellia",
	distance = 800
}

registerScreenPlay("GingDarjeek", true)

ging_darjeek_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = GingDarjeek
}

ging_darjeek_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = GingDarjeek
}