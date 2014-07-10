hefsen_zindalai_missions =
{
	{
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "maestro", planetName = "rori", npcName = "Maestro" }
		}, 
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/hefsen_zindalai_q1_needed.iff", itemName = "" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 25 },
			{ rewardType = "faction", faction = "naboo", amount = 5 },
		}
	},
	{
		missionType = "escort",
		primarySpawns = 
		{ 
			{ npcTemplate = "runaway_gualama", planetName = "rori", npcName = "a runaway gualama" }
		}, 
		secondarySpawns =
		{
			{ npcTemplate = "blood_thirsty_borgle", planetName = "rori", npcName = "" },
			{ npcTemplate = "blood_thirsty_borgle", planetName = "rori", npcName = "" }
		}, 
		itemSpawns = 
		{

		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 50 },
			{ rewardType = "faction", faction = "naboo", amount = 10 }
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "wealthy_patron", planetName = "rori", npcName = "a wealthy patron" }
		}, 
		secondarySpawns =
		{
			{ npcTemplate = "bandit", planetName = "rori", npcName = "" },
			{ npcTemplate = "bandit", planetName = "rori", npcName = "" },
			{ npcTemplate = "bandit", planetName = "rori", npcName = "" }
		}, 
		itemSpawns = 
		{

		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 100 },
			{ rewardType = "faction", faction = "naboo", amount = 15 }
		}
	}
}

npcMapHefsenZindalai = 
{ 
	{ 
		spawnData = { planetName = "rori", npcTemplate = "hefsen_zindalai", x = -11, z = 1.7, y = -20, direction = 0, cellID = 4635710, position = STAND },
		worldPosition = { x = 5298.6, y = 5896.8 },
		npcNumber = 1,
		stfFile = "@static_npc/rori/rori_restuss_hefsen_zindalai",
		missions = hefsen_zindalai_missions
	},
}

HefsenZindalai = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapHefsenZindalai,
	permissionMap = {},
	className = "HefsenZindalai",
	screenPlayState = "hefsen_zindalai_quest",
	distance = 600
}

registerScreenPlay("HefsenZindalai", true)

hefsen_zindalai_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = HefsenZindalai
}
hefsen_zindalai_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = HefsenZindalai
}
