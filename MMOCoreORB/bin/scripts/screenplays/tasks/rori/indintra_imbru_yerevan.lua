indintra_imbru_yerevan_missions =
{
	{
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "briska_gil", planetName = "rori", npcName = "Briska Gil" }
		}, 
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/indintra_imbru_yerevan_q1_needed.iff", itemName = "" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 40 }
		}
	},
	{
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "shaultra_loraweet", planetName = "rori", npcName = "Shaultra Loraweet" }
		}, 
		secondarySpawns =
		{

		}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/indintra_imbru_yerevan_q2_needed.iff", itemName = "" }
		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 75 }
		}
	}
}

npcMapIndintraImbruYerevan = 
{ 
	{ 
		spawnData = { planetName = "rori", npcTemplate = "indintra_imbru_yerevan", x = -6.5, z = 1.6, y = -14, direction = 0, cellID = 4635647, position = STAND },
		worldPosition = { x = 5143.5, y = 5639 }, 
		npcNumber = 1,
		stfFile = "@static_npc/rori/rori_narmle_indintra_imbru_yerevan",
		missions = indintra_imbru_yerevan_missions
	},
}

IndintraImbruYerevan = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapIndintraImbruYerevan,
	permissionMap = {},
	className = "IndintraImbruYerevan",
	screenPlayState = "indintra_imbru_yerevan_quest",
	distance = 600
}

registerScreenPlay("IndintraImbruYerevan", true)

indintra_imbru_yerevan_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = IndintraImbruYerevan
}
indintra_imbru_yerevan_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = IndintraImbruYerevan
}
