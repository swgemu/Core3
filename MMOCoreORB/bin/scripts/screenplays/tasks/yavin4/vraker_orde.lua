rebelMobilebase =
	{
		type = "destructible",
		buildingTemplate = "object/building/military/pirate_warehouse.iff",
		terminal = { template = "object/tangible/terminal/terminal_destructible_building.iff", vectorCellID = 3, x = 0, z = 0.3, y = -6.0 },
		childNpcs = {
			{ npcTemplate = "rebel_colonel", npcName = "Mobile Command Leader", vectorCellID = 3, x = 0, z = 0.3, y = -3.0 }
		}
	}

vraker_orde_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "rebel_specforce_pathfinder", npcName = "Scout Leader" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "rebel_scout", npcName = "" },
				{ npcTemplate = "rebel_scout", npcName = "" },
				{ npcTemplate = "rebel_scout", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
				{ rewardType = "faction", faction = "imperial", amount = 15 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "rebel_medic", npcName = "Rescue Leader" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "rebel_commando", npcName = "" },
				{ npcTemplate = "rebel_commando", npcName = "" },
				{ npcTemplate = "rebel_commando", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
				{ rewardType = "faction", faction = "imperial", amount = 30 },
			}
		},
		{
			missionType = "destroy",
			buildingSpawn = rebelMobilebase,
			primarySpawns =
			{
				{ npcTemplate = "rebel_surface_marshall", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "rebel_commando", npcName = "" },
				{ npcTemplate = "rebel_commando", npcName = "" },
				{ npcTemplate = "rebel_commando", npcName = "" },
				{ npcTemplate = "rebel_commando", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
				{ rewardType = "faction", faction = "imperial", amount = 45 },
			}
		}
	}

npcMapVrakerOrde =
	{
		{
			spawnData = { npcTemplate = "vraker_orde", x = 4050.5, z = 37.0, y = -6256.1, direction = 49, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/yavin/yavin_imperialgarrison_vraker_orde",
			missions = vraker_orde_missions
		},
	}

VrakerOrde = ThemeParkLogic:new {
	npcMap = npcMapVrakerOrde,
	className = "VrakerOrde",
	screenPlayState = "vraker_orde_tasks",
	planetName = "yavin4",
	distance = 900,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("VrakerOrde", true)

vraker_orde_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = VrakerOrde
}
vraker_orde_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = VrakerOrde
}
