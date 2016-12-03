charal_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_marauder_ewok_spleen", npcName = "" }
			},
			secondarySpawns =
			{

			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/charal_q1_needed.iff", itemName = "" }
			},
			rewards =
			{

			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_marauder_lizardman", npcName = "Lizardman the Slave" }
			},
			secondarySpawns =
			{

			},
			itemSpawns =
			{

			},
			rewards =
			{

			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_marauder_ewok_juicy", npcName = "Juicy Ewok" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "gondula_warrior", npcName = "" },
				{ npcTemplate = "gondula_warrior", npcName = "" },
				{ npcTemplate = "gondula_warrior", npcName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{

			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_marauder_dengo", npcName = "Dengo Haribonn" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "marooned_pirate", npcName = "" },
				{ npcTemplate = "marooned_pirate", npcName = "" },
				{ npcTemplate = "marooned_pirate", npcName = "" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/charal_q4_needed.iff", itemName = "" }
			},
			rewards =
			{

			}
		}
	}

npcMapMarauderCharal =
	{
		{
			spawnData = { npcTemplate = "charal", x = -4564, z = 99, y = -2297, direction = 0, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/endor/charal",
			missions = charal_missions
		}
	}

ThemeParkMarauderCharal = ThemeParkLogic:new {
	npcMap = npcMapMarauderCharal,
	className = "ThemeParkMarauderCharal",
	screenPlayState = "marauder_theme_park_charal",
	requiredFaction = "endor_marauder",
	planetName = "endor",
}

registerScreenPlay("ThemeParkMarauderCharal", true)

theme_park_marauder_charal_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkMarauderCharal
}
theme_park_marauder_charal_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkMarauderCharal
}
