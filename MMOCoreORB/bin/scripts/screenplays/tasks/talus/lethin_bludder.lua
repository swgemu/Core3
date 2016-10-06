rebelLab =
	{
		type = "destructible",
		buildingTemplate = "object/building/military/pirate_warehouse.iff",
		terminal = { template = "object/tangible/terminal/terminal_destructible_building.iff", vectorCellID = 3, x = 0, z = 0.3, y = -6.0 },
		childNpcs = {
			{ npcTemplate = "rebel_medic", npcName = "", vectorCellID = 3, x = 0, z = 0.3, y = -3.0 }
		}
	}

lethin_bludder_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "defector_quest_lethin", npcName = "an Imperial Defector" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "rebel_specforce_pathfinder", npcName = "" },
				{ npcTemplate = "rebel_specforce_pathfinder", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 250 },
				{ rewardType = "faction", faction = "imperial", amount = 50 }
			}
		},
		{
			missionType = "destroy",
			buildingSpawn = rebelLab,
			primarySpawns =
			{
				{ npcTemplate = "rebel_scout", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "rebel_trooper", npcName = "" },
				{ npcTemplate = "rebel_trooper", npcName = "" },
				{ npcTemplate = "rebel_trooper", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 500 },
				{ rewardType = "faction", faction = "imperial", amount = 100 }
			}
		}
	}

npcMapLethinBludder =
	{
		{
			spawnData = { npcTemplate = "lethin_bludder", x = 3.9, z = 0.1, y = 0.4, direction = -179, cellID = 1392911, position = SIT },
			npcNumber = 1,
			worldPosition = { x = -2163, y = 2331 },
			stfFile = "@static_npc/talus/talus_imperialoutpost_lethin_bludder",
			missions = lethin_bludder_missions
		},
	}

LethinBludder = ThemeParkLogic:new {
	npcMap = npcMapLethinBludder,
	className = "LethinBludder",
	screenPlayState = "lethin_bludder_tasks",
	planetName = "talus",
	distance = 700,
	faction = FACTIONIMPERIAL,
}

registerScreenPlay("LethinBludder", true)

lethin_bludder_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LethinBludder
}
lethin_bludder_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = LethinBludder
}
