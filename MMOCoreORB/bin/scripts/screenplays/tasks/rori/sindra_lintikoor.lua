sindra_lintikoor_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "sindra_ingon_lakbo", npcName = "Ingon Lakbo" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "sindra_thug", npcName = "a Thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/sindra_lintikoor_q1_needed.iff", itemName = "Lakbo's Response" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "sindra_bieque", npcName = "Bieque Lozan-Lippid" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/sindra_lintikoor_q2_needed.iff", itemName = "Lozan-Lippid Invitation" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
			}
		}
	}

npcMapSindraLintikoor =
	{
		{
			spawnData = { npcTemplate = "sindra_lintikoor", x = -23.6, z = 1.6, y = -12.6, direction = -5, cellID = 4635599, position = STAND },
			worldPosition = { x = -5309, y = -2312 },
			npcNumber = 1,
			stfFile = "@static_npc/rori/rori_narmle_sindra_lintikoor",
			missions = sindra_lintikoor_missions
		},

	}

SindraLintikoor = ThemeParkLogic:new {
	npcMap = npcMapSindraLintikoor,
	className = "SindraLintikoor",
	screenPlayState = "sindra_lintikoor_quest",
	planetName = "rori",
	distance = 600
}

registerScreenPlay("SindraLintikoor", true)

sindra_lintikoor_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = SindraLintikoor
}
sindra_lintikoor_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = SindraLintikoor
}
