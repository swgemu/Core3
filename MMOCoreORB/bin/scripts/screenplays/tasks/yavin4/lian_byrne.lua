lian_byrne_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "lian_imperial_courier", npcName = "Imperial Courier" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "rebel_trooper", npcName = "" },
				{ npcTemplate = "rebel_trooper", npcName = "" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/lian_byrne_q1_needed.iff", itemName = "Forensics report" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
				{ rewardType = "faction", faction = "imperial", amount = 10 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "lian_imperial_operative", npcName = "Imperial Operative" }
			},
			secondarySpawns = {
				{ npcTemplate = "lian_thief", npcName = "Scavenger" },
				{ npcTemplate = "lian_thief", npcName = "Scavenger" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
				{ rewardType = "faction", faction = "imperial", amount = 10 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "lian_spynet_operative", npcName = "Rebel Spy" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/lian_byrne_q3_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
				{ rewardType = "faction", faction = "imperial", amount = 15 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "lian_rebel_specforce_urban_guerrilla", npcName = "" },
				{ npcTemplate = "lian_rebel_specforce_urban_guerrilla", npcName = "" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 },
				{ rewardType = "faction", faction = "imperial", amount = 15 }
			}
		},
	}

npcMapLianByrne =
	{
		{
			spawnData = { npcTemplate = "lian_byrne", x = -8.6, z = 58.0, y = -52.4, direction = 115, cellID = 3465362, position = STAND },
			worldPosition = { x = -2985, y = -2965 },
			npcNumber = 1,
			stfFile = "@static_npc/yavin/yavin_massassi_lian_byrne",
			missions = lian_byrne_missions
		},

	}

LianByrne = ThemeParkLogic:new {
	npcMap = npcMapLianByrne,
	className = "LianByrne",
	screenPlayState = "lian_byrne_quest",
	planetName = "yavin4",
	distance = 500,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("LianByrne", true)

lian_byrne_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LianByrne
}
lian_byrne_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = LianByrne
}
