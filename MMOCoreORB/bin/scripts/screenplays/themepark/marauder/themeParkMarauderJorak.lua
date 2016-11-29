fightmaster_jorak_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "bloodseeker_mite", npcName = "" }
			},
			secondarySpawns =
			{

			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 25 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "crimson_blurrg", npcName = "" }
			},
			secondarySpawns =
			{

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
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "deranged_mantigrue", npcName = "" }
			},
			secondarySpawns =
			{

			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 40 },
				{ rewardType = "loot_set",  lootGroup = "theme_park_reward_marauder_armor_bracer", setSize = 2 }
			}
		}
	}

npcMapMarauderJorak =
	{
		{
			spawnData = { npcTemplate = "fightmaster_jorak", x = -4582, z = 99, y = -2244, direction = 180, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/endor/endor_marauder_fightmaster_jorak",
			missions = fightmaster_jorak_missions
		}
	}

ThemeParkMarauderJorak = ThemeParkLogic:new {
	npcMap = npcMapMarauderJorak,
	className = "ThemeParkMarauderJorak",
	screenPlayState = "marauder_theme_park_jorak",
	requiredFaction = "endor_marauder",
	planetName = "endor",
}

registerScreenPlay("ThemeParkMarauderJorak", true)

theme_park_marauder_jorak_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkMarauderJorak
}
theme_park_marauder_jorak_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkMarauderJorak
}
