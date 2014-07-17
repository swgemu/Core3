ging_darjeek_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "professor_minnet", planetName = "corellia", npcName = "\"Professor\" Minnet" }
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
				{ npcTemplate = "sivrool_linnaie", planetName = "corellia", npcName = "Siv'rool Linnaie" }
			},
			secondarySpawns =	
			{
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" }
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
				{ npcTemplate = "thug", planetName = "corellia", npcName = "Listening Post Guy" }
			},
			secondarySpawns =	
			{
				{ npcTemplate = "smuggler", planetName = "corellia", npcName = "a smuggler" },
				{ npcTemplate = "smuggler", planetName = "corellia", npcName = "a smuggler" },
				{ npcTemplate = "smuggler", planetName = "corellia", npcName = "a smuggler" },
				{ npcTemplate = "smuggler", planetName = "corellia", npcName = "a smuggler" }
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
			spawnData = { planetName = "corellia", npcTemplate = "ging_darjeek", x = -24.6629, z = -0.519991, y = 6.12104, direction = -112, cellID = 3375365, position = STAND },
			worldPosition = { x = 6708, y = -5783 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/ging_darjeek",
			missions = ging_darjeek_missions
		}
	}

GingDarjeek = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapGingDarjeek,
	className = "GingDarjeek",
	screenPlayState = "ging_darjeek_quest",
	distance = 800
}

registerScreenPlay("GingDarjeek", true)

ging_darjeek_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = GingDarjeek
}

ging_darjeek_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = GingDarjeek
}