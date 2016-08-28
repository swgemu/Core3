haleen_snowline_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "haleen_reactionist", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "haleen_thug", npcName = "a Thug" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/haleen_snowline_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "haleen_activist", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "haleen_reactionist2", npcName = "" },
				{ npcTemplate = "haleen_reactionist2", npcName = "" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/haleen_snowline_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 40 },
			}
		}
	}

hagrin_zeed_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "hagrin_information_broker", npcName = "Information Broker" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "hagrin_thug", npcName = "a Thug" },
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
				{ npcTemplate = "hagrin_information_broker", npcName = "Information Broker" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "hagrin_thug", npcName = "a Thug" },
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
				{ npcTemplate = "owetary", npcName = "Owetary" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "hagrin_fed_dub_patrolman", npcName = "" },
				{ npcTemplate = "hagrin_fed_dub_patrolman", npcName = "" },
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
				{ npcTemplate = "hagrin_aide", npcName = "Blackmailer" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "hagrin_fed_dub_patrolman", npcName = "" },
				{ npcTemplate = "hagrin_fed_dub_patrolman", npcName = "" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		},
	}

npcMapHaleenSnowlineHagrinZeed =
	{
		{
			spawnData = { npcTemplate = "haleen_snowline", x = -0.1, z = 3.12, y = 19.3, direction = 0, cellID = 6255466, position = STAND },
			worldPosition = { x = 683, y = -3152 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_dearic_haleen_snowline",
			missions = haleen_snowline_missions
		},
		{
			spawnData = { npcTemplate = "hagrin_zeed", x = -35.8, z = 1.3, y = -3.0, direction = 53, cellID = 6255471, position = SIT },
			worldPosition = { x = 653, y = -3177 },
			npcNumber = 2,
			stfFile = "@static_npc/talus/talus_dearic_hagrin_zeed",
			missions = hagrin_zeed_missions
		},
	}

HaleenSnowlineHagrinZeed = ThemeParkLogic:new {
	npcMap = npcMapHaleenSnowlineHagrinZeed,
	className = "HaleenSnowlineHagrinZeed",
	screenPlayState = "haleen_snowline_hagrin_zeed_quest",
	planetName = "talus",
	distance = 800
}

registerScreenPlay("HaleenSnowlineHagrinZeed", true)

haleen_snowline_hagrin_zeed_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = HaleenSnowlineHagrinZeed
}
haleen_snowline_hagrin_zeed_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = HaleenSnowlineHagrinZeed
}