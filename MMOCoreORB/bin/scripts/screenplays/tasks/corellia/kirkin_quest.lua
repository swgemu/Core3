kirkin_missions =
{
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "lacnor_liawoon", planetName = "corellia", npcName = "Lacnor Liawoon" } 
		},
		secondarySpawns = {
			{ npcTemplate = "human_thug", planetName = "corellia", npcName = "a thug" },
		},
		itemSpawns = {},
		rewards = 
		{	
			{ rewardType = "credits", amount = 75 }
		}
	},
	{
		missionType = "retrieve", 
		primarySpawns = 
		{ 
			{ npcTemplate = "kiantryl_liawoon", planetName = "corellia", npcName = "Lacnor Liawoon" } 
		},
		secondarySpawns = {
			{ npcTemplate = "human_thug", planetName = "corellia", npcName = "a thug" }
		},
		itemSpawns = {
			{ itemTemplate = "object/tangible/mission/quest_item/kirkin_liawoon_q2_needed.iff",
				itemName = "Anti-Selonian Meeting" }		
		},
		rewards = {}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "lacnor_liawoon", planetName = "corellia", npcName = "Lacnor Liawoon" } 
		},
		secondarySpawns = {
			{ npcTemplate = "human_thug", planetName = "corellia", npcName = "a thug" },
			{ npcTemplate = "human_thug", planetName = "corellia", npcName = "a thug" },
			{ npcTemplate = "human_thug", planetName = "corellia", npcName = "a thug" }
		},
		itemSpawns = {},
		rewards = {}
	}
}

npc_map_kirkin = 
{ 
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "kirkin_liawoon", x = -177.0, z = 28.0, y = -4498.0,
			direction = -91, cellID = 0, position = STAND }, 
		worldPosition = { x = -177.0, y = -4498.0 },
		npcNumber = 1,   
		stfFile = "@static_npc/corellia/kirkin_liawoon", 
		missions = kirkin_missions
	}
}

kirkin_quest = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npc_map_kirkin,
	permissionMap = {},
	className = "kirkin_quest",
	screenPlayState = "kirkin_quest_state",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = "",
	faction = NONE
}

registerScreenPlay("kirkin_quest", true)

kirkin_giver_handler = mission_giver_conv_handler:new {
	themePark = kirkin_quest
}

kirkin_target_handler = mission_target_conv_handler:new {
	themePark = kirkin_quest
}
