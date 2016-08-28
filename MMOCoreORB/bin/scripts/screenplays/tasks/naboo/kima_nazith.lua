kima_nazith_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "benbul_leedee", npcName = "Benbul Leedee" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "imperial_trooper", npcName = "" },
				{ npcTemplate = "imperial_trooper", npcName = "" },
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
				{ npcTemplate = "hrodius_goragg", npcName = "Hrodius Goragg" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "imperial_trooper", npcName = "" },
				{ npcTemplate = "imperial_trooper", npcName = "" },
				{ npcTemplate = "stormtrooper", npcName = "" },
				{ npcTemplate = "stormtrooper", npcName = "" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "kunn_kuroosh", npcName = "Kunn Kuroosh" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "stormtrooper", npcName = "" },
				{ npcTemplate = "stormtrooper", npcName = "" },
				{ npcTemplate = "stormtrooper", npcName = "" },
				{ npcTemplate = "stormtrooper", npcName = "" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
			}
		},
	}

npcMapKimaNazith =
	{
		{
			spawnData = { npcTemplate = "kima_nazith", x = 4972, z = 360, y = -1582, direction = -178, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/kima_nazith",
			missions = kima_nazith_missions
		}
	}

KimaNazith = ThemeParkLogic:new {
	npcMap = npcMapKimaNazith,
	className = "KimaNazith",
	screenPlayState = "kima_nazith_quest",
	planetName = "naboo",
	distance = 800,
	faction = FACTIONREBEL,
}

registerScreenPlay("KimaNazith", true)

kima_nazith_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = KimaNazith
}
kima_nazith_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = KimaNazith
}


