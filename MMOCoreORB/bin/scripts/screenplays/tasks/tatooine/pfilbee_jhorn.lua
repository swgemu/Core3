pfilbee_jhorn_missions =
{
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "greater_desert_womp_rat", npcName = "a greater desert womp rat" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "greater_desert_womp_rat", npcName = "a greater desert womp rat" }
		},
		itemSpawns = {}, 
		rewards = {
			{ rewardType = "faction", faction = "imperial", amount = 50 },
			{ rewardType = "credits", amount = 2000 },
		}
	},
	{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "tatooine_mynock", npcName = "a tatooine mynock" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "tatooine_mynock", npcName = "a tatooine mynock" }
		},
		itemSpawns = {}, 
		rewards = {
			{ rewardType = "faction", faction = "imperial", amount = 100 },
			{ rewardType = "credits", amount = 3000 },
		}
	},
	{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "dragonet", npcName = "a dragonet" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "dragonet", npcName = "a dragonet" },
				{ npcTemplate = "dragonet", npcName = "a dragonet" }
		},
		itemSpawns = {}, 
		rewards = {
			{ rewardType = "faction", faction = "imperial", amount = 150 },
			{ rewardType = "credits", amount = 4000 },
		}
	},	
	{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "dune_lizard", npcName = "a dune lizard" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "dune_lizard", npcName = "a dune lizard" },
				{ npcTemplate = "dune_lizard", npcName = "a dune lizard" },
				{ npcTemplate = "dune_lizard", npcName = "a dune lizard" }				
		},
		itemSpawns = {}, 
		rewards = {
			{ rewardType = "faction", faction = "imperial", amount = 150 },
			{ rewardType = "credits", amount = 6000 },
			{ rewardType = "loot", lootGroup = "task_reward_pfilbee_jhorn" },
		}
	}	
}

npcMapPfilbeeJhorn = 
{ 
	{ 
		spawnData = { npcTemplate = "pfilbee_jhorn", x = 4.9, z = 0.1, y = -3.9, direction = -90, cellID = 1279923, position = STAND }, 
		worldPosition = { x = -1129.4, y = -3914.4 }, 
		npcNumber = 1, 
		stfFile = "@static_npc/tatooine/pfilbee_jhorn", 
		missions = pfilbee_jhorn_missions 
	},
}

PfilbeeJhorn = ThemeParkLogic:new {
	npcMap = npcMapPfilbeeJhorn,
	className = "PfilbeeJhorn",
	screenPlayState = "pfilbee_jhorn_quest",
	planetName = "tatooine",
	distance = 1000,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("PfilbeeJhorn", true)

pfilbee_jhorn_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = PfilbeeJhorn
}
pfilbee_jhorn_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = PfilbeeJhorn
}
