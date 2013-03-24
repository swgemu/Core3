drakka_judarrl_missions =
{
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "stormtrooper_rifleman", planetName = "dantooine", npcName = "random" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "stormtrooper_rifleman", planetName = "dantooine", npcName = "Stormtrooper Rifleman" },
				{ npcTemplate = "stormtrooper_rifleman", planetName = "dantooine", npcName = "Stormtrooper Rifleman" }
		},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 500 },		
			{ rewardType = "faction", faction = "rebel", amount = 15 },
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "aroho_preni", planetName = "dantooine", npcName = "Aroho Preni (a Dantari Raider)" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "stormtrooper_commando", planetName = "dantooine", npcName = "Stormtrooper Commando" },
				{ npcTemplate = "stormtrooper_commando", planetName = "dantooine", npcName = "Stormtrooper Commando" },				
				{ npcTemplate = "stormtrooper_commando", planetName = "dantooine", npcName = "Stormtrooper Commando" },
				{ npcTemplate = "stormtrooper_commando", planetName = "dantooine", npcName = "Stormtrooper Commando" }
		},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 650 },		
			{ rewardType = "faction", faction = "rebel", amount = 15 },
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "force_crystal_hunter", planetName = "dantooine", npcName = "Deelomae Raede (a force crystal hunter)" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "dark_side_savage", planetName = "dantooine", npcName = "random" },
				{ npcTemplate = "dark_side_savage", planetName = "dantooine", npcName = "random" },				
				{ npcTemplate = "dark_side_savage", planetName = "dantooine", npcName = "random" }
		},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 800 },	
			{ rewardType = "loot", lootGroup = "task_reward_drakka_judarrl" },
		}
	}	
}

npcMapDrakkaJudarrl = 
{ 
	{ 
		spawnData = { planetName = "dantooine", npcTemplate = "drakka_judarrl", x = 73.1, z = -46, y = -141, direction = 97, cellID = 8535548, position = STAND }, 
		worldPosition = { x = 4221.2, y = 4959.3 }, 
		npcNumber = 1,   
		stfFile = "@static_npc/dantooine/dantooine_remotehaven_drakka_judarrl", 
		missions = drakka_judarrl_missions 
	},
}

DrakkaJudarrl = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapDrakkaJudarrl,
	permissionMap = {},
	className = "DrakkaJudarrl",
	screenPlayState = "drakka_judarrl_quest",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = ""
}

registerScreenPlay("DrakkaJudarrl", true)

drakka_judarrl_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = DrakkaJudarrl
}
drakka_judarrl_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = DrakkaJudarrl
}
