vacationHome =
	{
		type = "destructible",
		buildingTemplate = "object/building/military/pirate_warehouse.iff",
		terminal = { template = "object/tangible/terminal/terminal_destructible_building.iff", vectorCellID = 3, x = 0, z = 0.3, y = -6.0 },
		childNpcs =
		{
			{ npcTemplate = "giant_gubbur", npcName = "Faswald's Pet", vectorCellID = 3, x = 0, z = 0.3, y = -3.0 }
		}
	}

venthan_chassu_missions =
	{
		{
			missionType = "destroy",
			buildingSpawn = vacationHome,
			primarySpawns =
			{
				{ npcTemplate = "r5", npcName = "" }
			},
			secondarySpawns =
			{

			},
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 250 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "critic_quest_venthan", npcName = "Faswald Vorsuble" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "bodyguard", npcName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 500 }
			}
		}
	}

npcMapVenthanChassu =
	{
		{
			spawnData = { npcTemplate = "venthan_chassu", x = -6.4, z = -0.9, y = -20.0, direction = -9, cellID = 3005702, position = STAND },
			npcNumber = 1,
			worldPosition = { x = -5219, y = -6433 },
			stfFile = "@static_npc/corellia/venthan_chassu",
			missions = venthan_chassu_missions
		},
	}

VenthanChassu = ThemeParkLogic:new {
	npcMap = npcMapVenthanChassu,
	className = "VenthanChassu",
	screenPlayState = "venthan_chassu_quest",
	planetName = "corellia",
	distance = 300,
}

registerScreenPlay("VenthanChassu", true)

venthan_chassu_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = VenthanChassu
}
venthan_chassu_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = VenthanChassu
}
