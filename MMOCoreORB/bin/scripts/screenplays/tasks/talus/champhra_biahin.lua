champhra_biahin_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "champhra_agriculturalist", npcName = "Agriculturalist" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "champhra_thug", npcName = "a Thug" },
			},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/champhra_biahin_q1_needed.iff", itemName = "Twin-Scented Natterbloom" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "champhra_farmer", npcName = "a farmer" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "champhra_thug", npcName = "a Thug" },
			},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/champhra_biahin_q2_needed.iff", itemName = "\"Flowers of Drall\"" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
			}
		},
	}

npcMapChamphraBiahin =
	{
		{
			spawnData = { npcTemplate = "champhra_biahin", x = 2.71, z = 0.18, y = 4.54, direction = 205, cellID = 3305354, position = STAND },
			worldPosition = { x = 316, y = -3055 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_dearic_champhra_biahin",
			missions = champhra_biahin_missions
		},
	}

ChamphraBiahin = ThemeParkLogic:new {
	npcMap = npcMapChamphraBiahin,
	className = "ChamphraBiahin",
	screenPlayState = "champhra_biahin_quest",
	planetName = "talus",
	distance = 800
}

registerScreenPlay("ChamphraBiahin", true)

champhra_biahin_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ChamphraBiahin
}
champhra_biahin_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ChamphraBiahin
}