jaleela_bindoo_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "odoof_grunda", npcName = "Odoof Grunda" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/jaleela_bindoo_q1_needed.iff", itemName = "Grunda Painting" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "jonda_trask", npcName = "Jonda Trask" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "jaleela_imperial_courier", npcName = "Imperial Courier" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/jaleela_bindoo_q3_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "jaleela_zim_graedler", npcName = "Zim Graedler" }
			},
			secondarySpawns = {
				{ npcTemplate = "jaleela_protestor_leader", npcName = "Protestor Leader" },
				{ npcTemplate = "jaleela_protestor", npcName = "a Protestor" },
				{ npcTemplate = "jaleela_protestor", npcName = "a Protestor" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 },
			}
		},
	}

npcMapJaleelaBindoo =
	{
		{
			spawnData = { npcTemplate = "jaleela_bindoo", x = -11.0, z = 1.7, y = -21.1, direction = 34, cellID = 4635527, position = STAND },
			worldPosition = { x = -5212, y = -2470 },
			npcNumber = 1,
			stfFile = "@static_npc/rori/rori_narmle_jaleela_bindoo",
			missions = jaleela_bindoo_missions
		},

	}

JaleelaBindoo = ThemeParkLogic:new {
	npcMap = npcMapJaleelaBindoo,
	className = "JaleelaBindoo",
	screenPlayState = "jaleela_bindoo_quest",
	planetName = "rori",
	distance = 800
}

registerScreenPlay("JaleelaBindoo", true)

jaleela_bindoo_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = JaleelaBindoo
}
jaleela_bindoo_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = JaleelaBindoo
}
