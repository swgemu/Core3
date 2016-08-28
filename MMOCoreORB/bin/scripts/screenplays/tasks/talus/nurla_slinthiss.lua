nurla_slinthiss_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "nurla_corsec_captain", npcName = "" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/nurla_slinthiss_q1_needed.iff", itemName = "datadisc" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "nurla_employee", npcName = "Nurla's Employee" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nurla_corsec_rogue", npcName = "" },
				{ npcTemplate = "nurla_corsec_rogue", npcName = "" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "nurla_businessman", npcName = "Businessman" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nurla_jabba_enforcer", npcName = "" },
				{ npcTemplate = "nurla_jabba_enforcer", npcName = "" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/nurla_slinthiss_q3_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "nurla_assassin", npcName = "Assassin" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nurla_hutt_gangster", npcName = "a Hutt gangster" },
				{ npcTemplate = "nurla_hutt_gangster", npcName = "a Hutt gangster" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
			}
		},
	}

npcMapNurlaSlinthiss =
	{
		{
			spawnData = { npcTemplate = "nurla_slinthiss", x = -5.3, z = -0.9, y = -21, direction = 0, cellID = 3175396, position = STAND },
			worldPosition = { x = 435, y = -2948 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_dearic_nurla_slinthiss",
			missions = nurla_slinthiss_missions
		},
	}

NurlaSlinthiss = ThemeParkLogic:new {
	npcMap = npcMapNurlaSlinthiss,
	className = "NurlaSlinthiss",
	screenPlayState = "nurla_slinthiss_quest",
	planetName = "talus",
	distance = 800
}

registerScreenPlay("NurlaSlinthiss", true)

nurla_slinthiss_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = NurlaSlinthiss
}
nurla_slinthiss_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = NurlaSlinthiss
}