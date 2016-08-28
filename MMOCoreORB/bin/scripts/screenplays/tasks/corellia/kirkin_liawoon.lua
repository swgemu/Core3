kirkin_liawoon_missions =
{
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "lacnor_liawoon", npcName = "Lacnor Liawoon" } 
		},
		secondarySpawns = {
			{ npcTemplate = "kirkin_human_thug", npcName = "a thug" },
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
			{ npcTemplate = "kiantryl_liawoon", npcName = "Kiantryl Liawoon" } 
		},
		secondarySpawns = {
			{ npcTemplate = "kirkin_human_thug", npcName = "a thug" }
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
			{ npcTemplate = "lacnor_liawoon", npcName = "Lacnor Liawoon" } 
		},
		secondarySpawns = {
			{ npcTemplate = "kirkin_human_thug", npcName = "a thug" },
			{ npcTemplate = "kirkin_human_thug", npcName = "a thug" },
			{ npcTemplate = "kirkin_human_thug", npcName = "a thug" }
		},
		itemSpawns = {},
		rewards = {}
	}
}

npcMapKirkinLiawoon = 
{ 
	{ 
		spawnData = { npcTemplate = "kirkin_liawoon", x = -178.2, z = 28.0, y = -4498.0,
			direction = -91, cellID = 0, position = STAND }, 
		worldPosition = { x = -178.2, y = -4498.0 },
		npcNumber = 1,   
		stfFile = "@static_npc/corellia/kirkin_liawoon", 
		missions = kirkin_liawoon_missions
	}
}

KirkinLiawoon = ThemeParkLogic:new {
	npcMap = npcMapKirkinLiawoon,
	className = "KirkinLiawoon",
	screenPlayState = "kirkin_liawoon_quest",
	planetName = "corellia",
	distance = 1000
}

registerScreenPlay("KirkinLiawoon", true)

kirkin_liawoon_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = KirkinLiawoon
}

kirkin_liawoon_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = KirkinLiawoon
}
