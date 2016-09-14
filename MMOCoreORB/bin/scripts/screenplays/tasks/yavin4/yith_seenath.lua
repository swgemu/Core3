
yith_seenath_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "imperial_courier_quest_yith", npcName = "Imperial Courier" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "stormtrooper", npcName = "" },
				{ npcTemplate = "stormtrooper", npcName = "" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/yith_seenath_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
				{ rewardType = "faction", faction = "rebel", amount = 15 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "imperial_lieutenant_colonel", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
				{ rewardType = "faction", faction = "rebel", amount = 20 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "imperial_inquisitor", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "storm_commando", npcName = "" },
				{ npcTemplate = "storm_commando", npcName = "" },
				{ npcTemplate = "storm_commando", npcName = "" },
				{ npcTemplate = "storm_commando", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 150 },
				{ rewardType = "faction", faction = "rebel", amount = 30 },
			}
		}
	}

npcMapYithSeenath =
	{
		{
			spawnData = { npcTemplate = "yith_seenath", x = 1590.0, z = 101.0, y = 1536.1, direction = 162, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/yavin/yavin_rebelcamp_yith_seenath",
			missions = yith_seenath_missions
		},
	}

YithSeenath = ThemeParkLogic:new {
	npcMap = npcMapYithSeenath,
	className = "YithSeenath",
	screenPlayState = "yith_seenath_quest",
	planetName = "yavin4",
	distance = 700,
	faction = FACTIONREBEL
}

registerScreenPlay("YithSeenath", true)

yith_seenath_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = YithSeenath
}
yith_seenath_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = YithSeenath
}
