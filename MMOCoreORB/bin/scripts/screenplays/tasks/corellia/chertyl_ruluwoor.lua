chertyl_ruluwoor_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "kafleer_tredahl", planetName = "corellia", npcName = "Kafleer Tredahl" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/chertyl_ruruwoor_q1_needed.iff", itemName = "Datadisc" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 300 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "zayna", planetName = "corellia", npcName = "Zayna" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards = 
			{
				{ rewardType = "credits", amount = 500 }
			}
		}
	}

npcMapChertylRuluwoor =
	{
		{
			spawnData = { planetName = "corellia", npcTemplate = "chertyl_ruluwoor", x = -8.54, z = 1.6, y = -11.59, direction = 98.8, cellID = 3005674, position = STAND },
			worldPosition = { x = -3233, y = 3084 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/chertyl_ruluwoor",
			missions = chertyl_ruluwoor_missions
		}
	}

ChertylRuluwoor = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapChertylRuluwoor,
	className = "ChertylRuluwoor",
	screenPlayState = "chertyl_ruluwoor_quest",
	distance = 800
}

registerScreenPlay("ChertylRuluwoor", true)

chertyl_ruluwoor_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ChertylRuluwoor
}

chertyl_ruluwoor_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ChertylRuluwoor
}
