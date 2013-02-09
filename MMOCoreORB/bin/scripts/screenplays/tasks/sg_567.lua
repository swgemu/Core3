sg_567_missions =
{
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "sg_567_droideka", planetName = "dantooine", npcName = "(a Malfunctioning Droideka)" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 5000 },		
			{ rewardType = "faction", faction = "imperial", amount = 400 },
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "sg_619", planetName = "dantooine", npcName = "SG-619" } 
		}, 
		secondarySpawns = 
		{				
				{ npcTemplate = "rebel_specforce_sergeant", planetName = "dantooine", npcName = "random" },
				{ npcTemplate = "specforce_major", planetName = "dantooine", npcName = "random" }
		},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 3000 },		
			{ rewardType = "faction", faction = "imperial", amount = 600 },
		}
	}
}

npcMapSG567 = 
{ 
	{ 
		spawnData = { planetName = "dantooine", npcTemplate = "sg_567", x = -4216.85, z = 3, y = -2434.33, direction = 312.817, cellID = 0, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@static_npc/dantooine/sg_567", 
		missions = sg_567_missions 
	},
}

SG567 = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapSG567,
	permissionMap = {},
	className = "SG567",
	screenPlayState = "sg_567_quest",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = "@theme_park/messages:static_completion_message"
}

registerScreenPlay("SG567", true)

sg_567_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = SG567
}
sg_567_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = SG567
}