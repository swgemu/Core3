aaph_koden_missions =
{
	{
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "talia_reede", planetName = "tatooine", npcName = "Talia Reede" }
		}, 
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/aaph_koden_q1_needed.iff", itemName = "" }
		}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 150 },
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "stormtrooper_groupleader", planetName = "tatooine", npcName = "GK-72" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "tatooine", npcName = "Imperial Storm Trooper" },
			{ npcTemplate = "stormtrooper", planetName = "tatooine", npcName = "Imperial Storm Trooper" }
		},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 400 },
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "talia_reede", planetName = "tatooine", npcName = "Talia Reede" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "stormtrooper", planetName = "tatooine", npcName = "Imperial Storm Trooper" },
			{ npcTemplate = "stormtrooper", planetName = "tatooine", npcName = "Imperial Storm Trooper" },
			{ npcTemplate = "stormtrooper", planetName = "tatooine", npcName = "Imperial Storm Trooper" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 600 }
		}
	}

}

npcMapAaphKoden = 
{ 
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "aaph_koden", x = 130.0, z = 52.0, y = -5399.6, direction = -67, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/tatooine/aaph_koden",
		missions = aaph_koden_missions
	},
}

AaphKoden = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapAaphKoden,
	permissionMap = {},
	className = "AaphKoden",
	screenPlayState = "aaph_koden_quest",
	distance = 600,
	faction = FACTIONREBEL

}

registerScreenPlay("AaphKoden", true)

aaph_koden_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = AaphKoden
}
aaph_koden_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = AaphKoden
}
