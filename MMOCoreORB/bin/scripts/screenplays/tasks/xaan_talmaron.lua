xaan_talmaron_missions =
{
	{ 
		missionType = "retrieve",
		primarySpawns = 
		{ 
			{ npcTemplate = "ezawo_wagli", planetName = "dantooine", npcName = "Ezawo Wagli" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "xaan_bandit", planetName = "dantooine", npcName = "a bandit" }	
		},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/xaan_talmaron_q1_needed.iff", itemName = "Fragment of Alderaan" }
		}, 		
		rewards = 
		{ 
			{ rewardType = "credits", amount = 4000 },
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "orip_erchi", planetName = "dantooine", npcName = "Orip Erchi (a space pirate)" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "xaan_bandit", planetName = "dantooine", npcName = "a bandit" },
				{ npcTemplate = "xaan_bandit", planetName = "dantooine", npcName = "a bandit" },
				{ npcTemplate = "xaan_bandit", planetName = "dantooine", npcName = "a bandit" }				
		},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 6000 },
		}
	},
	{
		missionType = "retrieve", 
		primarySpawns = 
		{ 
			{ npcTemplate = "eni_ayka", planetName = "dantooine", npcName = "Eni A'Yka" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "xaan_bandit", planetName = "dantooine", npcName = "a bandit" },
				{ npcTemplate = "xaan_bandit", planetName = "dantooine", npcName = "a bandit" }			
		},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/xaan_talmaron_q3_needed.iff", itemName = "Death Star Transmission" }
		}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "task_reward_xaan_talmaron" },
		}
	}	
}

npcMapXaanTalmaron = 
{ 
	{ 
		spawnData = { planetName = "dantooine", npcTemplate = "xaan_talmaron", x = 0.923707, z = 0.125264, y = -4.46262, direction = 160.225, cellID = 1380125, position = STAND }, 
		worldPosition = { x = -4184.4, y = -2407.1 }, 
		npcNumber = 1,   
		stfFile = "@static_npc/dantooine/dantooine_imperialgarrison_xaan_talmaron", 
		missions = xaan_talmaron_missions 
	},
}

XaanTalmaron = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapXaanTalmaron,
	permissionMap = {},
	className = "XaanTalmaron",
	screenPlayState = "xaan_talmaron_quest",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = ""
}

registerScreenPlay("XaanTalmaron", true)

xaan_talmaron_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = XaanTalmaron
}
xaan_talmaron_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = XaanTalmaron
}
