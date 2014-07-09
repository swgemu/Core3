xalox_guul_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "xalox_informant", planetName = "talus", npcName = "Bothan Informant" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "xalox_smuggler", planetName = "talus", npcName = "a Smuggler" },
				{ npcTemplate = "xalox_smuggler", planetName = "talus", npcName = "a Smuggler" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
				{ rewardType = "faction", faction = "imperial", amount = 15 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "xalox_smuggler2", planetName = "talus", npcName = "Smuggler" },
			},
			secondarySpawns =
			{
				{ npcTemplate = "xalox_criminal", planetName = "talus", npcName = "a Criminal" },
				{ npcTemplate = "xalox_criminal", planetName = "talus", npcName = "a Criminal" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/xalox_guul_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
				{ rewardType = "faction", faction = "imperial", amount = 15 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "xalox_slicer", planetName = "talus", npcName = "Data Slicer" },
			},
			secondarySpawns =
			{
				{ npcTemplate = "xalox_criminal", planetName = "talus", npcName = "a Criminal" },
				{ npcTemplate = "xalox_criminal", planetName = "talus", npcName = "a Criminal" },
				{ npcTemplate = "xalox_criminal", planetName = "talus", npcName = "a Criminal" },
				{ npcTemplate = "xalox_criminal", planetName = "talus", npcName = "a Criminal" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
				{ rewardType = "faction", faction = "imperial", amount = 15 },
			}
		},
	}

npcMapXaloxGuul =
	{
		{
			spawnData = { planetName = "talus", npcTemplate = "xalox_guul", x = 5.3, z = -0.1, y = -3.9, direction = -90, cellID = 4965435, position = SIT },
			worldPosition = { x = -2180, y = 2262 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_imperialoutpost_xalox_guul",
			missions = xalox_guul_missions
		},
	}

XaloxGuul = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapXaloxGuul,
	className = "XaloxGuul",
	screenPlayState = "xalox_guul_quest",
	distance = 800,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("XaloxGuul", true)

xalox_guul_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = XaloxGuul
}
xalox_guul_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = XaloxGuul
}