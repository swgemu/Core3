xarot_korlin_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "xarot_nightsister_witch", npcName = "Nightsister Witch" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/xarot_korlin_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "faction", faction = "imperial", amount = 10 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "xarot_singing_mountain_clan_witch", npcName = "Singing Mountain Clan Witch" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/xarot_korlin_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "faction", faction = "imperial", amount = 10 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "xarot_nightsister_in_training", npcName = "Nightsister In Training" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nightsister_sentry", npcName = "" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "faction", faction = "imperial", amount = 10 },
			}
		},
	}

npcMapXarotKorlin =
	{
		{
			spawnData = { npcTemplate = "xarot_korlin", x = 9.9, z = 1.0, y = -21.6, direction = 33, cellID = 2665369, position = STAND },
			worldPosition = { x = -6385, y = 916 },
			npcNumber = 1,
			stfFile = "@static_npc/dathomir/xarot_korlin",
			missions = xarot_korlin_missions
		}
	}

XarotKorlin = ThemeParkLogic:new {
	npcMap = npcMapXarotKorlin,
	className = "XarotKorlin",
	screenPlayState = "xarot_korlin_quest",
	planetName = "dathomir",
	distance = 800,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("XarotKorlin", true)

xarot_korlin_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = XarotKorlin
}
xarot_korlin_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = XarotKorlin
}
