jatrian_lytus_missions =
{
	{ 
		missionType = "escort",
		primarySpawns = 
		{ 
			{ npcTemplate = "nai", planetName = "dantooine", npcName = "Nai (a Rogue Trooper)" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "rebel_brigadier_general", planetName = "dantooine", npcName = "random" },	
				{ npcTemplate = "specforce_major", planetName = "dantooine", npcName = "random" }					
		},
		itemSpawns = {}, 		
		rewards = 
		{ 
			{ rewardType = "faction", faction = "imperial", amount = 200 },
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "chino", planetName = "dantooine", npcName = "Chino (an Empire Chief Inquisitor)" } 		
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "imperial", amount = 500 },
		}
	},	
	{
		missionType = "retrieve", 
		primarySpawns = 
		{ 
			{ npcTemplate = "echi", planetName = "dantooine", npcName = "Echi (a Holovid Developer)" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/loot/simple_kit/datadisk.iff", itemName = "Datadisk" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 5000 },
		}
	},
	{
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "jaaves", planetName = "dantooine", npcName = "Jaaves" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/jatrian_lytus_q3_needed.iff", itemName = "Datadisc" }
		}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "task_reward_jatrian_lytus" },
		}
	}	
}

npcMapJatrianLytus = 
{ 
	{ 
		spawnData = { planetName = "dantooine", npcTemplate = "jatrian_lytus", x = 3.1801, z = 0.125266, y = 3.64218, direction = 209.67, cellID = 1365879, position = STAND }, 
		worldPosition = { x = -4203.8, y = -2426.5 }, 
		npcNumber = 1,   
		stfFile = "@static_npc/dantooine/dantooine_imperialgarrison_jatrian_lytus", 
		missions = jatrian_lytus_missions 
	},
}

JatrianLytus = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapJatrianLytus,
	permissionMap = {},
	className = "JatrianLytus",
	screenPlayState = "jatrian_lytus_quest",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = ""
}

registerScreenPlay("JatrianLytus", true)

jatrian_lytus_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = JatrianLytus
}
jatrian_lytus_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = JatrianLytus
}
