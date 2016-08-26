grobber_missions =
{
	{
		missionType = "escort",
		planetName = "corellia",
		primarySpawns =
		{
			{ npcTemplate = "criminal_quest_grobber", npcName = "Hammond Ballater" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "thug", npcName = "Bodyguard" },
			{ npcTemplate = "thug", npcName = "Bodyguard" }
		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "credits", amount = 125 }
		}
	},
	{
		missionType = "assassinate",
		planetName = "corellia",
		primarySpawns =
		{
			{ npcTemplate = "criminal_quest_grobber", npcName = "Dev Breeger" }
		},
		secondarySpawns =	{},
		itemSpawns = {},
		rewards =
		{
			{ rewardType = "credits", amount = 450 }
		}
	}
}

zekka_thyne_missions =
{
	{
		missionType = "confiscate",
		planetName = "corellia",
		primarySpawns =
		{
			{ npcTemplate = "criminal_quest_zekka", npcName = "Korowee Fa'lorn" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/zekka_thyne_q1_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 125 }
		}
	},
	{
		missionType = "assassinate",
		planetName = "corellia",
		primarySpawns =
		{
			{ npcTemplate = "criminal_quest_zekka2", npcName = "Wedu Belar" }
		},
		secondarySpawns =
		{

		},
		itemSpawns = {},
		rewards =
		{
			{ rewardType = "credits", amount = 250 }
		}
	},
	{
		missionType = "assassinate",
		planetName = "corellia",
		primarySpawns =
		{
			{ npcTemplate = "corsec_agent_quest_zekka", npcName = "Wililikin" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "thug", npcName = "" },
			{ npcTemplate = "thug", npcName = "" }
		},
		itemSpawns = {},
		rewards =
		{
			{ rewardType = "credits", amount = 500 }
		}
	},
	{
		missionType = "assassinate",
		planetName = "tatooine",
		staticLoc = {x = 3253, y = -4924},
		primarySpawns =
		{
			{ npcTemplate = "assassin_quest_zekka",  npcName = "Drune Juntura" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "thug", npcName = "" },
			{ npcTemplate = "thug", npcName = "" }
		},
		itemSpawns = {},
		rewards =
		{
			{ rewardType = "credits", amount = 750 }
		}
	}
}

npcMapBlkSunTasks =
{
	{
		spawnData = { planetName = "corellia", npcTemplate = "grobber", x = -15.5, z = 1.0, y = -8.3, direction = 0, cellID = 1855551, position = STAND },
		worldPosition = { x = -453.7, y = -4688.5 },
		npcNumber = 1,
		stfFile = "@static_npc/corellia/grobber",
		missions = grobber_missions
	},
	{
		spawnData = { planetName = "corellia", npcTemplate = "zekka_thyne", x = -22.4, z = 1.6, y = -15.4, direction = 0, cellID = 1855554, position = STAND },
		worldPosition = { x = -447.5, y = -4695.5 },
		npcNumber = 2,
		stfFile = "@static_npc/corellia/zekka_thyne",
		missions = zekka_thyne_missions
	},
}

BlkSunTasks = ThemeParkLogic:new {
	npcMap = npcMapBlkSunTasks,
	className = "BlkSunTasks",
	screenPlayState = "blk_sun_tasks_task",
	requiredPlanets = { "corellia", "tatooine" },
	distance = 1100,
}

registerScreenPlay("BlkSunTasks", true)

blk_sun_tasks_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = BlkSunTasks
}
blk_sun_tasks_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = BlkSunTasks
}