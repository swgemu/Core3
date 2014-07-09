lt_harburik_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "wend_dinard", planetName = "tatooine", npcName = "Wend Dinard" }
			},
			secondarySpawns = {
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "a Thug" },
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "a Thug" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 2000 },
				{ rewardType = "faction", faction = "imperial", amount = 100 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "ammow_dowwop", planetName = "tatooine", npcName = "Ammow Dowwop" }
			},
			secondarySpawns = {
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "a Thug" },
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "a Thug" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 4000 },
				{ rewardType = "faction", faction = "imperial", amount = 150 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "td334", planetName = "tatooine", npcName = "TD-334" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 5000 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "noda_lovan", planetName = "tatooine", npcName = "Noda Lovan" }
			},
			secondarySpawns = {
				{ npcTemplate = "smuggler", planetName = "tatooine", npcName = "a Smuggler" },
				{ npcTemplate = "smuggler", planetName = "tatooine", npcName = "a Smuggler" },
				{ npcTemplate = "smuggler", planetName = "tatooine", npcName = "a Smuggler" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 7000 },
				{ rewardType = "faction", faction = "imperial", amount = 200 }
			}
		}

	}

npcMapLtHarburik =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "lt_harburik", x = 3485.35, z = 4.93, y = -4740.37, direction = 234.88, cellID = 0, position = STAND },
			worldPosition = { x = 3485, y = -4740 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/lt_harburik",
			missions = lt_harburik_missions
		},
	}

LtHarburik = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapLtHarburik,
	permissionMap = {},
	className = "LtHarburik",
	screenPlayState = "lt_harburik_quest",
	distance = 800,
	faction = FACTIONIMPERIAL

}

registerScreenPlay("LtHarburik", true)

lt_harburik_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LtHarburik
}
lt_harburik_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = LtHarburik
}