vinya_maysor_missions =
{
	{
		missionType = "deliver",
		primarySpawns =
		{
			{ npcTemplate = "slicer_quest_vinya", npcName = "Reeve Taggart" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/vinya_maysor_q1_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 50 }
		}
	},
	{
		missionType = "escort",
		primarySpawns =
		{
			{ npcTemplate = "miner_quest_vinya", npcName = "a Spice Mining Union Rep" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "credits", amount = 100 }
		}
	}
}

karrek_flim_missions =
{
	{
		missionType = "retrieve",
		primarySpawns =
		{
			{ npcTemplate = "courier_quest_karrek", npcName = "Mia" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/karrek_film_q1_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 100 }
		}
	},
	{
		missionType = "deliver",
		primarySpawns =
		{
			{ npcTemplate = "courier_quest_karrek2", npcName = "Tabor Claxx" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/karrek_film_q2_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 150 }
		}
	},
	{
		missionType = "retrieve",
		primarySpawns =
		{
			{ npcTemplate = "courier_quest_karrek2", npcName = "Tabor Claxx" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/karrek_film_q3_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 200 }
		}
	}
}

npcMapViceprexTasks =
{
	{
		spawnData = { npcTemplate = "vinya_maysor", x = -28.7, z = -0.5, y = 12.2, direction = 53, cellID = 3005707, position = STAND },
		npcNumber = 1,
		worldPosition = { x = -5242, y = -6401 },
		stfFile = "@static_npc/corellia/vinya_maysor",
		missions = vinya_maysor_missions
	},
	{
		spawnData = { npcTemplate = "karrek_flim", x = -6.2, z = 1.6, y = -7.5, direction = -152, cellID = 2775417, position = STAND },
		npcNumber = 2,
		worldPosition = { x = -5508, y = -6142 },
		stfFile = "@static_npc/corellia/karrek_flim",
		missions = karrek_flim_missions
	},
}

ViceprexTasks = ThemeParkLogic:new {
	npcMap = npcMapViceprexTasks,
	className = "ViceprexTasks",
	screenPlayState = "viceprex_tasks_questline",
	planetName = "corellia",
	distance = 300,
}

registerScreenPlay("ViceprexTasks", true)

viceprex_tasks_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ViceprexTasks
}
viceprex_tasks_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ViceprexTasks
}
