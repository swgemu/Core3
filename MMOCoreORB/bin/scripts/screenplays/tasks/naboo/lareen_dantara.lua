lareen_dantara_missions =
{
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "krahbu", npcName = "a Crazy Krahbu" } 
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
		primarySpawns = 
		{ 
			{ npcTemplate = "mott", npcName = "a Infected Mott" } 
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
		spawnData = { npcTemplate = "lareen_dantara", x = -5495.0, z = -150.0, y = -5.0, direction = 345.343, cellID = 0, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@static_npc/naboo/lareen_dantara", 
		missions = lareen_dantara_missions 
	},
}

LareenDantara = ThemeParkLogic:new {
	npcMap = npcMapLareenDantara,
	className = "LareenDantara",
	screenPlayState = "lareen_dantara_quest",
	planetName = "naboo",
	distance = 800,
}

registerScreenPlay("LareenDantara", true)

lareen_dantara_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LareenDantara
}
lareen_dantara_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = LareenDantara
}
