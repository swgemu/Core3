damalia_korde_missions =
{
	{ 
		missionType = "retrieve",
		primarySpawns = 
		{ 
			{ npcTemplate = "bor_ting", npcName = "Bor Ting" } 
		}, 
		secondarySpawns = {},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/damalia_korde_q1_needed.iff", itemName = "" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 25 } 
		}
	}
}

npcMapDamaliaKorde = 
{ 
	{ 
		spawnData = { npcTemplate = "damalia_korde", x = 5137.6, z = 346.5, y = -1531.5, direction = 34, cellID = 0, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@static_npc/naboo/damalia_korde", 
		missions = damalia_korde_missions 
	},
}

DamaliaKorde = ThemeParkLogic:new {
	npcMap = npcMapDamaliaKorde,
	className = "DamaliaKorde",
	screenPlayState = "damalia_korde_task",
	planetName = "naboo",
	distance = 800,
}

registerScreenPlay("DamaliaKorde", true)

damalia_korde_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = DamaliaKorde
}
damalia_korde_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = DamaliaKorde
}
