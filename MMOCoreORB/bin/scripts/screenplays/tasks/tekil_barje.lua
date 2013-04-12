tekil_barje_missions =
{
	{ 
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "digger_dimms", planetName = "tatooine", npcName = "Dagonel \"Digger\" Dimms" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "womprat", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "womprat", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "womprat", planetName = "tatooine", npcName = "" }
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/tekil_barje_q1_needed.iff", itemName = "" }
		},
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "task_reward_tekil_barje_1" },
			{ rewardType = "credits", amount = 1000 } 
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "digger_dimms", planetName = "tatooine", npcName = "Dagonel \"Digger\" Dimms" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "task_reward_tekil_barje_2" },
			{ rewardType = "credits", amount = 2000 }
		}
	},
	{ 
		missionType = "assassinate",
		silentTarget = "yes",
		primarySpawns = 
		{ 
			{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "" }
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "loot",  lootGroup = "task_reward_tekil_barje_3" },
			{ rewardType = "credits", amount = 3000 } 
		}
	}
}

npcMapTekilBarje = 
{ 
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "tekil_barje", x = -5269.8, z = 75, y = -6567.61, direction = 237.663, cellID = 0, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@static_npc/tatooine/tekil_barje", 
		hasWaypointNames = "no", 
		missions = tekil_barje_missions 
	},
}

TekilBarje = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapTekilBarje,
	permissionMap = {},
	className = "TekilBarje",
	screenPlayState = "tekil_barje_task",
	distance = 500,
	missionDescriptionStf = "",
	missionCompletionMessageStf = "@theme_park/messages:static_completion_message"
}

registerScreenPlay("TekilBarje", true)

tekil_barje_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = TekilBarje
}
tekil_barje_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = TekilBarje
}
