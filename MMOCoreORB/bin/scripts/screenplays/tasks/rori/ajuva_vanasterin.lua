ajuva_vanasterin_missions =
{
	{
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "jinderliss_prason", npcName = "Jinderliss Prason" }
		}, 
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/ajuva_vamasterin_q1_needed.iff", itemName = "" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 25 },
			{ rewardType = "faction", faction = "naboo", amount = 5 },
		}
	},
	{
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "art_dealer", npcName = "Art Dealer" }
		}, 
		secondarySpawns =
		{

		}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/ajuva_vamasterin_q2_needed.iff", itemName = "" }
		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 25 },
			{ rewardType = "faction", faction = "naboo", amount = 5 }
		}
	}
}

npcMapAjuvaVanasterin = 
{ 
	{ 
		spawnData = { npcTemplate = "ajuva_vanasterin", x = 5203, z = 80, y = 5700, direction = 180, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/rori/rori_restuss_ajuva_vanasterin",
		missions = ajuva_vanasterin_missions
	},
}

AjuvaVanasterin = ThemeParkLogic:new {
	npcMap = npcMapAjuvaVanasterin,
	className = "AjuvaVanasterin",
	screenPlayState = "ajuva_vanasterin_quest",
	planetName = "rori",
	distance = 600
}

registerScreenPlay("AjuvaVanasterin", true)

ajuva_vanasterin_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = AjuvaVanasterin
}
ajuva_vanasterin_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = AjuvaVanasterin
}
