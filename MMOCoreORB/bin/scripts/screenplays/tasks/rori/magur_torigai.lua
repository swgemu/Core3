magur_torigai_missions =
{
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "giant_gubbur", npcName = "" }
		}, 
		secondarySpawns =
		{

		},
		itemSpawns =
		{

		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 40 },
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "guf_drolg", npcName = "" }	
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
		}
	},
}

npcMapMagurTorigai = 
{ 
	{ 
		spawnData = { npcTemplate = "magur_torigai", x = 5132, z = 80, y = 5729, direction = 0, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/rori/rori_restuss_magur_torigai",
		missions = magur_torigai_missions
	},
}

MagurTorigai = ThemeParkLogic:new {
	npcMap = npcMapMagurTorigai,
	className = "MagurTorigai",
	screenPlayState = "magur_torigai_quest",
	planetName = "rori",
	distance = 800
}

registerScreenPlay("MagurTorigai", true)

magur_torigai_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = MagurTorigai
}
