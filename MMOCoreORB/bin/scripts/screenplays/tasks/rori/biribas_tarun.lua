biribas_tarun_missions =
{
	{ 
		missionType = "retrieve",
		primarySpawns = 
		{ 
			{ npcTemplate = "naboo_police_agent", planetName = "rori", npcName = "Biribas' Agent" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "naboo_pirate", planetName = "rori", npcName = "" },
			{ npcTemplate = "naboo_pirate", planetName = "rori", npcName = "" }
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
			{ npcTemplate = "dispatcher", planetName = "rori", npcName = "Dispatcher" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "naboo_gunrunner", planetName = "rori", npcName = "" },
			{ npcTemplate = "naboo_gunrunner", planetName = "rori", npcName = "" }
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
			{ npcTemplate = "security_guards_wife", planetName = "rori", npcName = "Security Guard's Wife" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "naboo_gunrunner", planetName = "rori", npcName = "" },
			{ npcTemplate = "naboo_gunrunner", planetName = "rori", npcName = "" }
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
			{ npcTemplate = "naboo_dread_pirate", planetName = "rori", npcName = "Gunrunner Leader" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "naboo_gunrunner", planetName = "rori", npcName = "" },
			{ npcTemplate = "naboo_gunrunner", planetName = "rori", npcName = "" },
			{ npcTemplate = "thug", planetName = "rori", npcName = "" }
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
		spawnData = { planetName = "rori", npcTemplate = "biribas_tarun", x = -17.2, z = 2.3, y = 18.3, direction = 146, cellID = 4635522, position = STAND }, 
		worldPosition = { x = -5173.6, y = -2463.7 }, 
		npcNumber = 1,   
		stfFile = "@static_npc/rori/rori_narmle_biribas_tarun", 
		missions = biribas_tarun_missions 
	},
}

BiribasTarun = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapBiribasTarun,
	permissionMap = {},
	className = "BiribasTarun",
	screenPlayState = "biribas_tarun_task",
	distance = 800
}

registerScreenPlay("BiribasTarun", true)

biribas_tarun_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = BiribasTarun
}
biribas_tarun_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = BiribasTarun
}
