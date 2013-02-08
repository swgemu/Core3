lx_466_missions =
{
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "lx_466_rebel_commander", planetName = "dantooine", npcName = "Ivo (a Stranded Rebel Commander)" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "lx_466_rebel_scout", planetName = "dantooine", npcName = "Casa (a Stranded Rebel Scout)" },
				{ npcTemplate = "lx_466_rebel_scout", planetName = "dantooine", npcName = "Parana (a Stranded Rebel Scout)" }
		},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 480 },		
			{ rewardType = "faction", faction = "imperial", amount = 300 },
		}
	},
	{ 
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "lx_466_dantari", planetName = "dantooine", npcName = "Drak (a Dantari tribesman)" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "huurton_huntress", planetName = "dantooine", npcName = "(a huurton huntress)" },
				{ npcTemplate = "huurton_bloodhunter", planetName = "dantooine", npcName = "(a huurton bloodhunter)" }
		},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/lx466_q2_needed.iff", itemName = "Rations" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 620 },		
			{ rewardType = "faction", faction = "imperial", amount = 400 },
		}
	},	
	{ 
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "lx_466_imperial_courier", planetName = "dantooine", npcName = "Re (an Imperial Courier)" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "mercenary_aggro", planetName = "dantooine", npcName = "random" },				
				{ npcTemplate = "mercenary_aggro", planetName = "dantooine", npcName = "random" },
				{ npcTemplate = "mercenary_aggro", planetName = "dantooine", npcName = "random" }
		},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/lx466_q3_needed.iff", itemName = "recording rod" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 745 },		
			{ rewardType = "faction", faction = "imperial", amount = 500 },
		}
	}	
}

npcMapLX466 = 
{ 
	{ 
		spawnData = { planetName = "dantooine", npcTemplate = "lx_466", x = -4181.94, z = 3, y = -2385.99, direction = 345.343, cellID = 0, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@static_npc/dantooine/lx_466", 
		missions = lx_466_missions 
	},
}

LX466 = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapLX466,
	permissionMap = {},
	className = "LX466",
	screenPlayState = "lx_466_quest",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = "@theme_park/messages:static_completion_message"
}

registerScreenPlay("LX466", true)

lx_466_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LX466
}
lx_466_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = LX466
}
