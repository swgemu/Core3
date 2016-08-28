stella_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "bent_spur", npcName = "Bent Spur" }
			},
			secondarySpawns = {
				{ npcTemplate = "thug", npcName = "" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/stella_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "ulek_talstin", npcName = "Ulek Talstin" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/stella_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 }
			}
		},
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "chaw_troillya", npcName = "Chaw Troillya" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/stella_q3_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 }
			}
		}
	}

npcMapStella =
	{
		{
			spawnData = { npcTemplate = "stella", x = -4.2, z = 0.4, y = -8.7, direction = 39, cellID = 1154122, position = STAND },
			worldPosition = { x = 3772, y = 2395 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/stella",
			missions = stella_missions
		},
	}

Stella = ThemeParkLogic:new {
	npcMap = npcMapStella,
	className = "Stella",
	screenPlayState = "stella_task",
	planetName = "tatooine",
	distance = 600
}

registerScreenPlay("Stella", true)

stella_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = Stella
}
stella_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = Stella
}
