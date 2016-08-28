bardo_klinj_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "imperial_courier_quest_bardo", npcName = "an Imperial Courier" }
			},
			secondarySpawns =
			{
				{npcTemplate = "thug", npcName = "Kritus' gang member"},
				{npcTemplate = "thug", npcName = "Kritus' gang member"}
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/bardo_klinj_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 }
			}
		},
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "imperial_courier_quest_bardo2", npcName = "Val Tula" }
			},
			secondarySpawns = {},
			itemSpawns = {
				{ itemTemplate = "object/tangible/mission/quest_item/bardo_klinj_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 150 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "gungan_reject_quest_bardo", npcName = "Mubarr" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/bardo_klinj_q3_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 200 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "majordomo_quest_bardo", npcName = "Xan'lak" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "brawler", npcName = "Kritus' gang leader" },
				{ npcTemplate = "thug", npcName = "Kritus' gang member" },
				{ npcTemplate = "thug", npcName = "Kritus' gang member" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 250 }
			}
		}
	}

npcMapBardoKlinj =
	{
		{
			spawnData = { npcTemplate = "bardo_klinj", x = -6.5, z = 6.1, y = -8.5, direction = 90, cellID = 1661384, position = STAND },
			worldPosition = { x = 1822.5, y = 2780.5 },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/bardo_klinj",
			missions = bardo_klinj_missions
		},
	}

BardoKlinj = ThemeParkLogic:new {
	npcMap = npcMapBardoKlinj,
	className = "BardoKlinj",
	screenPlayState = "bardo_klinj_task",
	planetName = "naboo",
	distance = 1000,
}

registerScreenPlay("BardoKlinj", true)

bardo_klinj_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = BardoKlinj
}
bardo_klinj_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = BardoKlinj
}
