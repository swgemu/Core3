chertyl_ruluwoor_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "kafleer_tredahl", npcName = "Kafleer Tredahl" }
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
				{ npcTemplate = "zayna", npcName = "Zayna" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
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
			spawnData = { npcTemplate = "chertyl_ruluwoor", x = -8.54, z = 1.6, y = -11.59, direction = 98.8, cellID = 3005674, position = STAND },
			worldPosition = { x = -3233, y = 3084 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/chertyl_ruluwoor",
			missions = chertyl_ruluwoor_missions
		}
	}

ChertylRuluwoor = ThemeParkLogic:new {
	npcMap = npcMapChertylRuluwoor,
	className = "ChertylRuluwoor",
	screenPlayState = "chertyl_ruluwoor_quest",
	planetName = "corellia",
	distance = 800
}

registerScreenPlay("ChertylRuluwoor", true)

chertyl_ruluwoor_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ChertylRuluwoor
}

chertyl_ruluwoor_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ChertylRuluwoor
}
