raglith_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "gondula_tribesman", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "gondula_worker", npcName = "" },
				{ npcTemplate = "gondula_worker", npcName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 20 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "lantern_bird", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "lantern_bird", npcName = "" },
				{ npcTemplate = "lantern_bird", npcName = "" },
				{ npcTemplate = "lantern_bird", npcName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_marauder_ewok_pelt", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "masterful_ewok_warrior", npcName = "" },
				{ npcTemplate = "masterful_ewok_warrior", npcName = "" },
				{ npcTemplate = "masterful_ewok_warrior", npcName = "" },
				{ npcTemplate = "masterful_ewok_warrior", npcName = "" },
				{ npcTemplate = "masterful_ewok_warrior", npcName = "" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/raglith_q3_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 40 },
				{ rewardType = "loot",  lootGroup = "theme_park_reward_marauder_armor_boots" }
			}
		}
	}

npcMapMarauderRaglith =
	{
		{
			spawnData = { npcTemplate = "raglith", x = -4677.5, z = 82, y = -2278.5, direction = 300, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/endor/raglith",
			missions = raglith_missions
		}
	}

ThemeParkMarauderRaglith = ThemeParkLogic:new {
	npcMap = npcMapMarauderRaglith,
	className = "ThemeParkMarauderRaglith",
	screenPlayState = "marauder_theme_park_raglith",
	requiredFaction = "endor_marauder",
	planetName = "endor",
}

registerScreenPlay("ThemeParkMarauderRaglith", true)

theme_park_marauder_raglith_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkMarauderRaglith
}
theme_park_marauder_raglith_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkMarauderRaglith
}
