supplyDepot =
	{
		type = "destructible",
		buildingTemplate = "object/building/military/pirate_warehouse.iff",
		terminal = { template = "object/tangible/terminal/terminal_destructible_building.iff", vectorCellID = 3, x = 0, z = 0.3, y = -6.0 },
		childNpcs = {
			{ npcTemplate = "rebel_network_leader", npcName = "", vectorCellID = 3, x = 0, z = 0.3, y = -3.0 }
		}
	}

cx_425_trooper_missions =
	{
		{
			missionType = "destroy",
			buildingSpawn = supplyDepot,
			primarySpawns =
			{
				{ npcTemplate = "rebel_medic", npcName = "Lead Sympathizer" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "rogue", npcName = "a Rebel Sympathizer" },
				{ npcTemplate = "rogue", npcName = "a Rebel Sympathizer" },
				{ npcTemplate = "rogue", npcName = "a Rebel Sympathizer" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
				{ rewardType = "faction", faction = "imperial", amount = 50 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "kliknik_dark_defender", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "kliknik", npcName = "" },
				{ npcTemplate = "kliknik", npcName = "" },
				{ npcTemplate = "kliknik", npcName = "" }
			},
			staticObjects =
			{
				{ objectTemplate = "object/tangible/lair/base/poi_all_lair_nest_large_evil_fire_small.iff", objectName = "a 'Rebel' lair" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 200 },
				{ rewardType = "faction", faction = "imperial", amount = 75 },
			}
		}
	}

npcMapCx425Trooper =
	{
		{
			spawnData = { npcTemplate = "cx_425", x = -3192.1, z = 69.8, y = -3136.2, direction = -90, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/yavin/yavin_massassi_cx-425",
			missions = cx_425_trooper_missions
		},
	}

Cx425Trooper = ThemeParkLogic:new {
	npcMap = npcMapCx425Trooper,
	className = "Cx425Trooper",
	screenPlayState = "cx_425_trooper_tasks",
	planetName = "yavin4",
	distance = 900,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("Cx425Trooper", true)

cx_425_trooper_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = Cx425Trooper
}
cx_425_trooper_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = Cx425Trooper
}
