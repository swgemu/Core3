lareen_dantara_missions =
{
	{
		missionType = "assassinate", 
		silentTarget = "yes",	
		primarySpawns = 
		{ 
			{ npcTemplate = "krahbu", planetName = "naboo", npcName = "a Crazy Krahbu" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 25 },		
		}
	},
	{
		missionType = "assassinate", 
		silentTarget = "yes",		
		primarySpawns = 
		{ 
			{ npcTemplate = "mott", planetName = "naboo", npcName = "a Infected Mott" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 50 },		
		}
	},		
}

npcMapLareenDantara = 
{ 
	{ 
		spawnData = { planetName = "naboo", npcTemplate = "lareen_dantara", x = -5495.0, z = -150.0, y = -5.0, direction = 345.343, cellID = 0, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@static_npc/naboo/lareen_dantara", 
		hasWaypointNames = "no",		
		missions = lareen_dantara_missions 
	},
}

LareenDantara = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapLareenDantara,
	permissionMap = {},
	className = "LareenDantara",
	screenPlayState = "lareen_dantara_quest",
	distance = 800,
	missionDescriptionStf = "",
	missionCompletionMessageStf = "@theme_park/messages:static_completion_message",
}

registerScreenPlay("LareenDantara", true)

lareen_dantara_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LareenDantara
}
lareen_dantara_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = LareenDantara
}
