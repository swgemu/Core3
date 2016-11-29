scholar_szingo_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_marauder_pirate_leader", npcName = "Pirate Captain" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "marooned_pirate", npcName = "" },
				{ npcTemplate = "marooned_pirate", npcName = "" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/szingo_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 75 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "rogue_marauder", npcName = "Marauder Scout Leader" }
			},
			secondarySpawns = {
				{ npcTemplate = "marauder", npcName = "" },
				{ npcTemplate = "marauder", npcName = "" },
				{ npcTemplate = "marauder", npcName = "" },
				{ npcTemplate = "marauder", npcName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 150 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "arachne_webmaster", npcName = "" }
			},
			secondarySpawns =
			{

			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 350 },
			}
		}
	}

king_terak_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_marauder_ewok_holy", npcName = "Ewok Holy One" }
			},
			secondarySpawns =
			{

			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/terak_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 500 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_marauder_indar", npcName = "Indar" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "marauder", npcName = "" },
				{ npcTemplate = "marauder", npcName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 300 },
				{ rewardType = "loot",  lootGroup = "theme_park_reward_marauder_armor_leggings" }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_marauder_stranded_mercenary", npcName = "random" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "mercenary_aggro", npcName = "" },
				{ npcTemplate = "mercenary_aggro", npcName = "" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/terak_q3_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 300 },
				{ rewardType = "loot_set",  lootGroup = "theme_park_reward_marauder_armor_bicep", setSize = 2 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "gondula_chief", npcName = "War Party Chief" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "ewok_outcast_raider", npcName = "" },
				{ npcTemplate = "ewok_outcast_raider", npcName = "" },
				{ npcTemplate = "ewok_outcast_raider", npcName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 575 },
				{ rewardType = "loot",  lootGroup = "theme_park_reward_marauder_armor_chest_plate" }
			}
		}
	}

npcMapMarauderSzingoTerak =
	{
		{
			spawnData = { npcTemplate = "scholar_szingo", x = -4618, z = 90, y = -2294, direction = 300, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/endor/endor_maraudercitadel_scholar_szingo",
			missions = scholar_szingo_missions
		},
		{
			spawnData = { npcTemplate = "king_terak", x = -4572, z = 99, y = -2273, direction = 270, cellID = 0, position = STAND },
			npcNumber = 2,
			stfFile = "@static_npc/endor/king_terak",
			missions = king_terak_missions
		}
	}

ThemeParkMarauderSzingoTerak = ThemeParkLogic:new {
	npcMap = npcMapMarauderSzingoTerak,
	className = "ThemeParkMarauderSzingoTerak",
	screenPlayState = "marauder_theme_park_szingo_terak",
	requiredFaction = "endor_marauder",
	planetName = "endor",
}

registerScreenPlay("ThemeParkMarauderSzingoTerak", true)

theme_park_marauder_szingo_terak_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkMarauderSzingoTerak
}
theme_park_marauder_szingo_terak_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkMarauderSzingoTerak
}
