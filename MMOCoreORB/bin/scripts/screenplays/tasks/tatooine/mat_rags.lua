mat_rags_missions =
{
	{ 
		missionType = "confiscate",
		primarySpawns = 
		{ 
			{ npcTemplate = "mat_rags_desert_squill", npcName = "desert squill" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/mat_rags_q1_needed.iff", itemName = "" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 2000 },
		}
	},
	{
		missionType = "confiscate",
		primarySpawns = 
		{ 
			{ npcTemplate = "mat_rags_greater_desert_womp_rat", npcName = "a greater desert womp rat" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/mat_rags_q2_needed.iff", itemName = "" }
		},  
		rewards = 
		{ 
			{ rewardType = "credits", amount = 4000 },
		}
	},
	{
		missionType = "confiscate",
		primarySpawns = 
		{ 
			{ npcTemplate = "mat_rags_bantha_matriarch", npcName = "a bantha matriarch" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/mat_rags_q3_needed.iff", itemName = "" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 6000 },
		}
	},	
	{
		missionType = "confiscate",
		primarySpawns = 
		{ 
			{ npcTemplate = "mat_rags_grizzled_dewback", npcName = "a grizzled dewback" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/mat_rags_q4_needed.iff", itemName = "" }
		}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "task_reward_mat_rags" },
			{ rewardType = "credits", amount = 6000 },			
		}
	}	
}

npcMapMatRags = 
{ 
	{ 
		spawnData = { npcTemplate = "mat_rags", x = -2977, z = 5, y = 2458, direction = -65, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/tatooine/mat_rags",
		missions = mat_rags_missions
	},
}

MatRags = ThemeParkLogic:new {
	npcMap = npcMapMatRags,
	className = "MatRags",
	screenPlayState = "mat_rags_quest",
	planetName = "tatooine",
	distance = 1000
}

registerScreenPlay("MatRags", true)

mat_rags_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = MatRags
}
mat_rags_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = MatRags
}
