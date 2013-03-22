luthik_uwyr_missions =
{
	{ 
		missionType = "assassinate",
		silentTarget = "yes",
		primarySpawns = 
		{ 
			{ npcTemplate = "ancient_reptillian", planetName = "dantooine", npcName = "Ancient Reptillian" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = {}
	},
	{
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "dark_initiate", planetName = "dantooine", npcName = "Dark Initiate" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/luthik_uwyr_q2_needed.iff", itemName = "Holocron splinters" }
		}, 
		rewards = {}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "untrained_padawan", planetName = "dantooine", npcName = "Untrained Padawan" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/luthik_uwyr_q3_needed.iff", itemName = "Padawan braid" }
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
		spawnData = { planetName = "dantooine", npcTemplate = "luthik_uwyr", x = 4275.4, z = 8.2, y = 5351.4, direction = -110, cellID = 0, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@static_npc/dantooine/luthik_uwyr", 
		missions = luthik_uwyr_missions 
	},
}

LuthikUwyr = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapLuthikUwyr,
	permissionMap = {},
	className = "LuthikUwyr",
	screenPlayState = "luthik_uwyr_quest",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = "@theme_park/messages:static_completion_message"
}

registerScreenPlay("LuthikUwyr", true)

luthik_uwyr_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LuthikUwyr
}
luthik_uwyr_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = LuthikUwyr
}
