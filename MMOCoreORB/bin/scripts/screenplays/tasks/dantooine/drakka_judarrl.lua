drakka_judarrl_missions =
{
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "stormtrooper_rifleman", npcName = "random" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "stormtrooper_rifleman", npcName = "Stormtrooper Rifleman" },
				{ npcTemplate = "stormtrooper_rifleman", npcName = "Stormtrooper Rifleman" }
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
			{ npcTemplate = "aroho_preni", npcName = "Aroho Preni (a Dantari Raider)" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "stormtrooper_commando", npcName = "Stormtrooper Commando" },
				{ npcTemplate = "stormtrooper_commando", npcName = "Stormtrooper Commando" },				
				{ npcTemplate = "stormtrooper_commando", npcName = "Stormtrooper Commando" },
				{ npcTemplate = "stormtrooper_commando", npcName = "Stormtrooper Commando" }
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
			{ npcTemplate = "force_crystal_hunter", npcName = "Deelomae Raede (a force crystal hunter)" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "dark_side_savage", npcName = "random" },
				{ npcTemplate = "dark_side_savage", npcName = "random" },				
				{ npcTemplate = "dark_side_savage", npcName = "random" }
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
		spawnData = { npcTemplate = "drakka_judarrl", x = 73.1, z = -46, y = -141, direction = 97, cellID = 8535548, position = STAND }, 
		worldPosition = { x = 4221.2, y = 4959.3 }, 
		npcNumber = 1,   
		stfFile = "@static_npc/dantooine/dantooine_remotehaven_drakka_judarrl", 
		missions = drakka_judarrl_missions 
	},
}

DrakkaJudarrl = ThemeParkLogic:new {
	npcMap = npcMapDrakkaJudarrl,
	className = "DrakkaJudarrl",
	screenPlayState = "drakka_judarrl_quest",
	planetName = "dantooine",
	distance = 1000,
	faction = FACTIONREBEL
}

registerScreenPlay("DrakkaJudarrl", true)

drakka_judarrl_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = DrakkaJudarrl
}
drakka_judarrl_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = DrakkaJudarrl
}
