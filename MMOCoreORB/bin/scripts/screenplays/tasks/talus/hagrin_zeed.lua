hagrin_zeed_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "hagrin_information_broker", planetName = "talus", npcName = "Information Broker" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "hagrin_thug", planetName = "talus", npcName = "a Thug" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/hagrin_zeed_q1_needed.iff", itemName = "Message for Jusani Zhord" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "hagrin_information_broker", planetName = "talus", npcName = "Information Broker" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "hagrin_thug", planetName = "talus", npcName = "a Thug" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/hagrin_zeed_q2_needed.iff", itemName = "Bribe" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "owetary", planetName = "talus", npcName = "Owetary" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "hagrin_fed_dub_patrolman", planetName = "talus", npcName = "" },
				{ npcTemplate = "hagrin_fed_dub_patrolman", planetName = "talus", npcName = "" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "hagrin_aide", planetName = "talus", npcName = "Blackmailer" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "hagrin_fed_dub_patrolman", planetName = "talus", npcName = "" },
				{ npcTemplate = "hagrin_fed_dub_patrolman", planetName = "talus", npcName = "" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		},
	}

npcMapHagrinZeed =
	{
		{
			spawnData = { planetName = "talus", npcTemplate = "hagrin_zeed", x = -35.8, z = 1.3, y = -3.0, direction = 53, cellID = 6255471, position = SIT },
			worldPosition = { x = 653, y = -3177 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_dearic_hagrin_zeed",
			missions = hagrin_zeed_missions
		},
	}

HagrinZeed = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapHagrinZeed,
	className = "HagrinZeed",
	screenPlayState = "hagrin_zeed_quest",
	distance = 800,
	missionCompletionMessageStf = "@theme_park/messages:static_completion_message",
}

registerScreenPlay("HagrinZeed", true)

hagrin_zeed_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = HagrinZeed
}
hagrin_zeed_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = HagrinZeed
}