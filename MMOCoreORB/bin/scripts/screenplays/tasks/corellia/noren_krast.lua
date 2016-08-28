noren_krast_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "banyon_craddok", npcName = "Banyon Craddok" }
			},
			secondarySpawns =	
			{
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/noren_krast_q1_needed.iff", itemName = "Credit disk" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 200 }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "fugue", npcName = "Fugue" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/noren_krast_q2_needed.iff", itemName = "A datadisc" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 500 }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "jeter_corona", npcName = "Jeter Corona" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/noren_krast_q3_needed.iff", itemName = "Message to Lasha Bindari" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 }
			}
		}
	}

npcMapNorenKrast =
	{
		{
			spawnData = { npcTemplate = "noren_krast", x = -5203.33, z = 21.0, y = -2488.13, direction = 176.643, cellID = 0, position = STAND },
			worldPosition = { x = -5203, y = -2488 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/noren_krast",
			missions = noren_krast_missions
		}
	}

NorenKrast = ThemeParkLogic:new {
	npcMap = npcMapNorenKrast,
	className = "NorenKrast",
	screenPlayState = "noren_krast_quest",
	planetName = "corellia",
	distance = 800
}

registerScreenPlay("NorenKrast", true)

noren_krast_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = NorenKrast
}

noren_krast_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = NorenKrast
}