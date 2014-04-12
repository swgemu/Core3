sidoras_bey_missions =
{
	{ 
		missionType = "retrieve",
		primarySpawns = 
		{ 
			{ npcTemplate = "sidoras_artisan", planetName = "rori", npcName = "Jag (an Artisan)" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/sidoras_bey_q1_needed.iff", itemName = "" }
		}, 		
		rewards = 
		{ 
			{ rewardType = "credits", amount = 25 },
		}
	},
	{
		missionType = "escort", 				
		primarySpawns = 
		{ 
			{ npcTemplate = "sidoras_child", planetName = "rori", npcName = "Silaras Bey" } 
		}, 
		secondarySpawns = 
		{
				{ npcTemplate = "sidoras_thug", planetName = "rori", npcName = "" },
				{ npcTemplate = "sidoras_thug", planetName = "rori", npcName = "" },
				{ npcTemplate = "sidoras_thug", planetName = "rori", npcName = "" }				
		},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 50 },
		}
	},		
}

npcMapSidorasBey = 
{ 
	{ 
		spawnData = { planetName = "rori", npcTemplate = "sidoras_bey", x = -5247.0, z = 80.0, y = -2387.0, direction = 96, cellID = 0, position = STAND }, 	
		npcNumber = 1,   
		stfFile = "@static_npc/rori/rori_narmle_sidoras_bey", 		
		missions = sidoras_bey_missions 
	},
}

SidorasBey = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapSidorasBey,
	permissionMap = {},
	className = "SidorasBey",
	screenPlayState = "sidoras_bey_quest",
	distance = 800,
	missionDescriptionStf = "",
	missionCompletionMessageStf = "@theme_park/messages:static_completion_message",
}

registerScreenPlay("SidorasBey", true)

sidoras_bey_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = SidorasBey
}
sidoras_bey_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = SidorasBey
}