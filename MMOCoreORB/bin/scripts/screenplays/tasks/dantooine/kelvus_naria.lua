kelvus_naria_missions =
{
	{ 
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "kelvus_imperial", planetName = "dantooine", npcName = "Imperial Corporal" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/kelvus_naria_q1_needed.iff", itemName = "Mining records" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 2000 },		
			{ rewardType = "faction", faction = "imperial", amount = 150 },
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "kelvus_miner", planetName = "dantooine", npcName = "random" } 
		}, 
		secondarySpawns = 
		{				
				{ npcTemplate = "kelvus_criminal", planetName = "dantooine", npcName = "random" },
				{ npcTemplate = "kelvus_criminal", planetName = "dantooine", npcName = "random" }
		},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 4000 },		
		}
	}
}

npcMapKelvusNaria = 
{ 
	{ 
		spawnData = { planetName = "dantooine", npcTemplate = "kelvus_naria", x = -618.741, z = 3, y = 2539.25, direction = 57.3847, cellID = 0, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@static_npc/dantooine/dantooine_miningoutpost_kelvus_naria", 
		missions = kelvus_naria_missions 
	},
}

KelvusNaria = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapKelvusNaria,
	permissionMap = {},
	className = "KelvusNaria",
	screenPlayState = "kelvus_naria_quest",
	distance = 1000,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("KelvusNaria", true)

kelvus_naria_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = KelvusNaria
}
kelvus_naria_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = KelvusNaria
}
