booto_lubble_missions =
{
	{ 
		missionType = "confiscate",
		primarySpawns = 
		{ 
			{ npcTemplate = "luhin_jinnor", npcName = "Warrant Officer Luhin Jinnor" } 
		},
		secondarySpawns =
		{
			{ npcTemplate = "stormtrooper", npcName = "" },
			{ npcTemplate = "stormtrooper", npcName = "" },
			{ npcTemplate = "stormtrooper", npcName = "" }
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/booto_lubble_q1_needed.iff", itemName = "" }
		},
		rewards = 
		{ 
			{ rewardType = "credits", amount = 50 } 
		}
	},
	{
		missionType = "confiscate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "rohd_gostervek", npcName = "Captain Rohd Gostervek" }	
		},
		secondarySpawns =
		{
			{ npcTemplate = "stormtrooper", npcName = "" },
			{ npcTemplate = "stormtrooper", npcName = "" },
			{ npcTemplate = "stormtrooper", npcName = "" },
			{ npcTemplate = "stormtrooper", npcName = "" }
		}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/booto_lubble_q2_needed.iff", itemName = "" }
		},
		rewards = 
		{
			{ rewardType = "credits", amount = 50 },
			{ rewardType = "faction", faction = "rebel", amount = 10 }
		}
	},
}

npcMapBootoLubble = 
{ 
	{ 
		spawnData = { npcTemplate = "booto_lubble", x = 4.0, z = 0.7, y = 0.5, direction = 170, cellID = 4505791, position = STAND },
		worldPosition = { x = 3701, y = -6488 }, 
		npcNumber = 1,
		stfFile = "@static_npc/rori/rori_rebeloutpost_booto_lubble",
		missions = booto_lubble_missions
	},
}

BootoLubble = ThemeParkLogic:new {
	npcMap = npcMapBootoLubble,
	className = "BootoLubble",
	screenPlayState = "booto_lubble_quest",
	planetName = "rori",
	distance = 800,
	faction = FACTIONREBEL
}

registerScreenPlay("BootoLubble", true)

booto_lubble_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = BootoLubble
}
booto_lubble_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = BootoLubble
}
