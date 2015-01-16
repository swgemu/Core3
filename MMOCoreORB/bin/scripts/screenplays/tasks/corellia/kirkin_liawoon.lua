kirkin_liawoon_missions =
{
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "lacnor_liawoon", planetName = "corellia", npcName = "Lacnor Liawoon" } 
		},
		secondarySpawns = {
			{ npcTemplate = "kirkin_human_thug", planetName = "corellia", npcName = "a thug" },
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
			{ npcTemplate = "kiantryl_liawoon", planetName = "corellia", npcName = "Kiantryl Liawoon" } 
		},
		secondarySpawns = {
			{ npcTemplate = "kirkin_human_thug", planetName = "corellia", npcName = "a thug" }
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
			{ npcTemplate = "kirkin_human_thug", planetName = "corellia", npcName = "a thug" },
			{ npcTemplate = "kirkin_human_thug", planetName = "corellia", npcName = "a thug" },
			{ npcTemplate = "kirkin_human_thug", planetName = "corellia", npcName = "a thug" }
		},
		itemSpawns = {},
		rewards = {}
	}
}

npcMapKirkinLiawoon = 
{ 
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "kirkin_liawoon", x = -178.2, z = 28.0, y = -4498.0,
			direction = -91, cellID = 0, position = STAND }, 
		worldPosition = { x = -178.2, y = -4498.0 },
		npcNumber = 1,   
		stfFile = "@static_npc/corellia/kirkin_liawoon", 
		missions = kirkin_liawoon_missions
	}
}

KirkinLiawoon = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapKirkinLiawoon,
	permissionMap = {},
	className = "KirkinLiawoon",
	screenPlayState = "kirkin_liawoon_quest",
	distance = 1000
}

registerScreenPlay("KirkinLiawoon", true)

kirkin_liawoon_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = KirkinLiawoon
}

kirkin_liawoon_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = KirkinLiawoon
}
