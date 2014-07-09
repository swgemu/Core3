kathikiis_ruwahurr_missions =
{
	{
		missionType = "escort", 				
		primarySpawns = 
		{ 
			{ npcTemplate = "kathikiis_assist", planetName = "talus", npcName = "Kathikiis Assistant" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "kathikiis_thug", planetName = "talus", npcName = "a Thug" },
				{ npcTemplate = "kathikiis_thug", planetName = "talus", npcName = "a Thug" },
				{ npcTemplate = "kathikiis_thug", planetName = "talus", npcName = "a Thug" }				
		},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 40 },
		}
	},
	{
		missionType = "assassinate", 				
		primarySpawns = 
		{ 
			{ npcTemplate = "kathikiis_bh", planetName = "talus", npcName = "a Bounty Hunter" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 50 },		
		}
	},		
}

npcMapKathikiisRuwahurr = 
{ 
	{ 
		spawnData = { planetName = "talus", npcTemplate = "kathikiis_ruwahurr", x = 20.8, z = -0.9, y = -17.7, direction = -8, cellID = 3175392, position = STAND }, 
		worldPosition = { x = 460, y = -2948 }, 	
		npcNumber = 1,   
		stfFile = "@static_npc/talus/talus_dearic_kathikiis_ruwahurr", 		
		missions = kathikiis_ruwahurr_missions 
	},
}

KathikiisRuwahurr = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapKathikiisRuwahurr,
	permissionMap = {},
	className = "KathikiisRuwahurr",
	screenPlayState = "kathikiis_ruwahurr_quest",
	distance = 800
}

registerScreenPlay("KathikiisRuwahurr", true)

kathikiis_ruwahurr_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = KathikiisRuwahurr
}
kathikiis_ruwahurr_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = KathikiisRuwahurr
}