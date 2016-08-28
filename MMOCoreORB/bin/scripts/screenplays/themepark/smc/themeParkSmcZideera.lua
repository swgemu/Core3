zideera_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_commoner_old", npcName = "a Stranded Pirate" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nightsister_ranger", npcName = "" },
				{ npcTemplate = "nightsister_ranger", npcName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
				{ rewardType = "credits", amount = 300 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_commoner_old", npcName = "a Pirate Crewmate" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nightsister_rancor_tamer", npcName = "" },
				{ npcTemplate = "nightsister_rancor_tamer", npcName = "" },
				{ npcTemplate = "nightsister_stalker", npcName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
				{ rewardType = "credits", amount = 450 }
			}
		}
	}

npcMapSmcZideera =
	{
		{
			spawnData = { npcTemplate = "zideera", x = -14.2, z = 1.9, y = -21, direction = -20, cellID = 2665883, position = STAND },
			worldPosition = { x = 153.5, y = 4465.3 },
			npcNumber = 1,
			stfFile = "@static_npc/dathomir/dathomir_singingmountainclanstronghold_zideera",
			missions = zideera_missions
		}
	}

ThemeParkSmcZideera = ThemeParkLogic:new {
	npcMap = npcMapSmcZideera,
	className = "ThemeParkSmcZideera",
	screenPlayState = "smc_zideera_theme_park",
	requiredFaction = "mtn_clan",
	planetName = "dathomir"
}

registerScreenPlay("ThemeParkSmcZideera", true)

theme_park_smc_zideera_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkSmcZideera
}
theme_park_smc_zideera_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkSmcZideera
}
