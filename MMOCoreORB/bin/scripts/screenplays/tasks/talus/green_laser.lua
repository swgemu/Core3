green_laser_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "clientrep_quest_green", npcName = "Anonymous Representative" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/green_laser_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "fed_dub_investigator", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "fed_dub_patrolman", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 150 },
			}
		}
	}

npcMapGreenLaser =
	{
		{
			spawnData = { npcTemplate = "green_laser", x = 10.1, z = -0.9, y = 19.5, direction = -113, cellID = 4265379, position = STAND },
			worldPosition = { x = 4295, y = 5337 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_nashal_green_laser",
			missions = green_laser_missions
		},
	}

GreenLaser = ThemeParkLogic:new {
	npcMap = npcMapGreenLaser,
	className = "GreenLaser",
	screenPlayState = "green_laser_tasks",
	planetName = "talus",
	distance = 900
}

registerScreenPlay("GreenLaser", true)

green_laser_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = GreenLaser
}
green_laser_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = GreenLaser
}
