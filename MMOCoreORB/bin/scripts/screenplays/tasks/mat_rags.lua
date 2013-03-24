mat_rags_missions =
{
	{ 
		missionType = "assassinate",
		silentTarget = "yes",
		primarySpawns = 
		{ 
			{ npcTemplate = "mat_rags_desert_squill", planetName = "tatooine", npcName = "desert squill" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/mat_rags_q1_needed.iff", itemName = "Squill Carcass" }
		}, 
		rewards = {}
	},
	{
		missionType = "assassinate",
		silentTarget = "yes",
		primarySpawns = 
		{ 
			{ npcTemplate = "mat_rags_greater_desert_womp_rat", planetName = "tatooine", npcName = "a greater desert womp rat" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/mat_rags_q2_needed.iff", itemName = "Womp Rat Hide" }
		},  
		rewards = {}
	},
	{
		missionType = "assassinate",
		silentTarget = "yes",
		primarySpawns = 
		{ 
			{ npcTemplate = "mat_rags_bantha_matriarch", planetName = "tatooine", npcName = "a bantha matriarch" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/mat_rags_q3_needed.iff", itemName = "Bantha Horns" }
		}, 
		rewards = {}
	},	
	{
		missionType = "assassinate",
		silentTarget = "yes",
		primarySpawns = 
		{ 
			{ npcTemplate = "mat_rags_grizzled_dewback", planetName = "tatooine", npcName = "a grizzled dewback" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/mat_rags_q4_needed.iff", itemName = "Grizzled Dewback Hide" }
		}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "task_reward_mat_rags" },
		}
	}	
}

npcMapMatRags = 
{ 
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "mat_rags", x = -2977, z = 5, y = 2458, direction = -65, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/tatooine/mat_rags",
		hasWaypointNames = "no",
		missions = mat_rags_missions
	},
}

MatRags = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapMatRags,
	permissionMap = {},
	className = "MatRags",
	screenPlayState = "mat_rags_quest",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = "@theme_park/messages:static_completion_message"
}

registerScreenPlay("MatRags", true)

mat_rags_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = MatRags
}
mat_rags_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = MatRags
}
