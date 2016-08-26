grobber_missions =
{
	{
		missionType = "escort",
		primarySpawns =
		{
			{ npcTemplate = "criminal_quest_grobber", planetName = "corellia", npcName = "Hammond Ballater" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "thug", planetName = "corellia", npcName = "Bodyguard" },
			{ npcTemplate = "thug", planetName = "corellia", npcName = "Bodyguard" }
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
		primarySpawns =
		{
			{ npcTemplate = "criminal_quest_grobber", planetName = "corellia", npcName = "Dev Breeger" }
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
		primarySpawns =
		{
			{ npcTemplate = "criminal_quest_zekka", planetName = "corellia", npcName = "Korowee Fa'lorn" }
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
		primarySpawns =
		{
			{ npcTemplate = "criminal_quest_zekka2", planetName = "corellia", npcName = "Wedu Belar" }
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
		primarySpawns =
		{
			{ npcTemplate = "corsec_agent_quest_zekka", planetName = "corellia", npcName = "Wililikin" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "thug", planetName = "corellia", npcName = "" },
			{ npcTemplate = "thug", planetName = "corellia", npcName = "" }
		},
		itemSpawns = {},
		rewards =
		{
			{ rewardType = "credits", amount = 500 }
		}
	},
	{
		missionType = "assassinate",
		primarySpawns =
		{
			{ npcTemplate = "assassin_quest_zekka", planetName = "tatooine", npcName = "Drune Juntura" }
			--PROBLEM AGAIN, CUZ WE NEED THE *NEW* FUNCTIONALITY TO SPAWN 'OFF-PLANET' QUEST SPAWNS ^
		},
		secondarySpawns =
		{
			{ npcTemplate = "thug", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "thug", planetName = "tatooine", npcName = "" }
			--AGAIN, SEE *NOTE ABOVE* ^^  (re: OFF-PLANET SPAWNS)
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
	numberOfActs = 1,
	npcMap = npcMapBlkSunTasks,
	permissionMap = {},
	className = "BlkSunTasks",
	screenPlayState = "blk_sun_tasks_task",
	distance = 1100,
}

registerScreenPlay("BlkSunTasks", true)

blk_sun_tasks_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = BlkSunTasks
}
blk_sun_tasks_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = BlkSunTasks
}