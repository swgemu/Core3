luthik_uwyr_missions =
{
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "ancient_reptillian", npcName = "Ancient Reptillian" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = {}
	},
	{
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "dark_initiate", npcName = "Dark Initiate" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/luthik_uwyr_q2_needed.iff", itemName = "Holocron splinters" }
		}, 
		rewards = {}
	},
	{
		missionType = "confiscate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "untrained_padawan", npcName = "Untrained Padawan" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/luthik_uwyr_q3_needed.iff", itemName = "" }
		}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "task_reward_luthik_uwyr" },
		}
	}	
}

npcMapLuthikUwyr = 
{ 
	{ 
		spawnData = { npcTemplate = "luthik_uwyr", x = 4275.4, z = 8.2, y = 5351.4, direction = -110, cellID = 0, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@static_npc/dantooine/luthik_uwyr", 
		missions = luthik_uwyr_missions 
	},
}

LuthikUwyr = ThemeParkLogic:new {
	npcMap = npcMapLuthikUwyr,
	className = "LuthikUwyr",
	screenPlayState = "luthik_uwyr_quest",
	planetName = "dantooine",
	distance = 1000,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("LuthikUwyr", true)

luthik_uwyr_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LuthikUwyr
}
luthik_uwyr_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = LuthikUwyr
}
