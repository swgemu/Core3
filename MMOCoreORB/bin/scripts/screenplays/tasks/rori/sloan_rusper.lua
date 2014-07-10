sloan_rusper_missions =
{
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "deadly_forest_mite_guardian", planetName = "rori", npcName = "" } 
		}, 
		secondarySpawns =
		{
		
		},
		itemSpawns =
		{

		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 75 },
			{ rewardType = "faction", faction = "naboo", amount = 10 }
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "ablest", planetName = "rori", npcName = "Ablest" }	
		}, 
		secondarySpawns =
		{
			{ npcTemplate = "nightspider_aggressor", planetName = "rori", npcName = "" },
			{ npcTemplate = "nightspider_aggressor", planetName = "rori", npcName = "" }
		}, 
		itemSpawns = 
		{

		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 75 },
			{ rewardType = "faction", faction = "naboo", amount = 10 }
		}
	},
}

npcMapSloanRusper = 
{ 
	{ 
		spawnData = { planetName = "rori", npcTemplate = "lord_sloan_rusper", x = 5065, z = 80, y = 5715, direction = 0, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/rori/rori_restuss_sloan_rusper",
		missions = sloan_rusper_missions
	},
}

SloanRusper = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapSloanRusper,
	permissionMap = {},
	className = "SloanRusper",
	screenPlayState = "sloan_rusper_quest",
	distance = 600
}

registerScreenPlay("SloanRusper", true)

sloan_rusper_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = SloanRusper
}
sloan_rusper_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = SloanRusper
}
