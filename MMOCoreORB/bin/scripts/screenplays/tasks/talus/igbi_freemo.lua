igbi_freemo_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "igbi_hutt_operative", planetName = "talus", npcName = "a Hutt operative" }
			},
			secondarySpawns =	{ },
			itemSpawns = { },
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "igbi_hutt_hotshot", planetName = "talus", npcName = "Hutt hotshot" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "igbi_thug", planetName = "talus", npcName = "a Thug" },
				{ npcTemplate = "igbi_thug", planetName = "talus", npcName = "a Thug" },
			},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/igbi_freemo_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
			}
		},
	}

npcMapIgbiFreemo =
	{
		{
			spawnData = { planetName = "talus", npcTemplate = "igbi_freemo", x = 4541, z = 2, y = 5069, direction = 145, cellID = 0, position = STAND },
			worldPosition = { x = 4541, y = 5069 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_nashal_igbi_freemo",
			missions = igbi_freemo_missions
		},
	}

IgbiFreemo = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapIgbiFreemo,
	className = "IgbiFreemo",
	screenPlayState = "igbi_freemo_quest",
	distance = 800
}

registerScreenPlay("IgbiFreemo", true)

igbi_freemo_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = IgbiFreemo
}
igbi_freemo_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = IgbiFreemo
}