hedon_istee_missions =
{
	{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "drognuz", npcName = "Drognuz" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 3000 } 
		}
	},
	{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "rath_kanaz", npcName = "Rath Kanaz" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 6000 } 
		}
	},
	{
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "serene_floater", npcName = "Serene Floater" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/hedon_istee_q3_needed.iff", itemName = "B'omarr Sacred Scroll" }
		}, 
		rewards = 
		{ 
			{ rewardType = "loot",  lootGroup = "task_reward_hedon_istee" },
		}
	}
}

npcMapHedonIstee = 
{ 
	{ 
		spawnData = { npcTemplate = "hedon_istee", x = 1390, z = 7, y = 3197, direction = 0, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/tatooine/hedon_istee",
		missions = hedon_istee_missions
	},
}

HedonIstee = ThemeParkLogic:new {
	npcMap = npcMapHedonIstee,
	className = "HedonIstee",
	screenPlayState = "hedon_istee_task",
	requiresEliteCombat = true,
	planetName = "tatooine",
	distance = 800,
}

registerScreenPlay("HedonIstee", true)

hedon_istee_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = HedonIstee
}
hedon_istee_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = HedonIstee
}
