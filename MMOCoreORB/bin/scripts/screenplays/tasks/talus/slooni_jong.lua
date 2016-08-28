slooni_jong_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "slooni_smuggler", npcName = "Smuggler" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a Thug" },
				{ npcTemplate = "thug", npcName = "a Thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/slooni_jong_q1_needed.iff", itemName = "Briefcase" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
				{ rewardType = "faction", faction = "fed_dub", amount = 5 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "slooni_slave", npcName = "Twi'lek slave" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "slaver", npcName = "a Slaver" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
				{ rewardType = "faction", faction = "fed_dub", amount = 5 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "slooni_slavemaster", npcName = "Slavemaster" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "slaver", npcName = "a Slaver" },
				{ npcTemplate = "slaver", npcName = "a Slaver" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
				{ rewardType = "faction", faction = "fed_dub", amount = 10 },
			}
		},
	}

npcMapSlooniJong =
	{
		{
			spawnData = { npcTemplate = "slooni_jong", x = 10.8, z = 1.7, y = -18, direction = -2, cellID = 4265440, position = STAND },
			worldPosition = { x = 4303, y = 5090 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_nashal_slooni_jong",
			missions = slooni_jong_missions
		},
	}

SlooniJong = ThemeParkLogic:new {
	npcMap = npcMapSlooniJong,
	className = "SlooniJong",
	screenPlayState = "slooni_jong_quest",
	planetName = "talus",
	distance = 800
}

registerScreenPlay("SlooniJong", true)

slooni_jong_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = SlooniJong
}
slooni_jong_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = SlooniJong
}