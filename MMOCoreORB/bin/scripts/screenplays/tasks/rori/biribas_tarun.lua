biribas_tarun_missions =
{
	{ 
		missionType = "retrieve",
		primarySpawns = 
		{ 
			{ npcTemplate = "naboo_police_agent", npcName = "Biribas' Agent" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "naboo_pirate", npcName = "" },
			{ npcTemplate = "naboo_pirate", npcName = "" }
},
		itemSpawns = {
			{ itemTemplate = "object/tangible/mission/quest_item/biribas_tarun_q1_needed.iff", itemName = "" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 50 },
			{ rewardType = "faction", faction = "naboo", amount = 10 }
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "dispatcher", npcName = "Dispatcher" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "naboo_gunrunner", npcName = "" },
			{ npcTemplate = "naboo_gunrunner", npcName = "" }
}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 50 },
			{ rewardType = "faction", faction = "naboo", amount = 15 }
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "security_guards_wife", npcName = "Security Guard's Wife" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "naboo_gunrunner", npcName = "" },
			{ npcTemplate = "naboo_gunrunner", npcName = "" }
}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 60 },
			{ rewardType = "faction", faction = "naboo", amount = 15 }
		}
	},
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "naboo_dread_pirate", npcName = "Gunrunner Leader" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "naboo_gunrunner", npcName = "" },
			{ npcTemplate = "naboo_gunrunner", npcName = "" },
			{ npcTemplate = "thug", npcName = "" }
},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 75 },
			{ rewardType = "faction", faction = "naboo", amount = 20 }
		}
	},
}

npcMapBiribasTarun = 
{ 
	{ 
		spawnData = { npcTemplate = "biribas_tarun", x = -17.2, z = 2.3, y = 18.3, direction = 146, cellID = 4635522, position = STAND }, 
		worldPosition = { x = -5173.6, y = -2463.7 }, 
		npcNumber = 1,   
		stfFile = "@static_npc/rori/rori_narmle_biribas_tarun", 
		missions = biribas_tarun_missions 
	},
}

BiribasTarun = ThemeParkLogic:new {
	npcMap = npcMapBiribasTarun,
	className = "BiribasTarun",
	screenPlayState = "biribas_tarun_task",
	planetName = "rori",
	distance = 800
}

registerScreenPlay("BiribasTarun", true)

biribas_tarun_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = BiribasTarun
}
biribas_tarun_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = BiribasTarun
}
