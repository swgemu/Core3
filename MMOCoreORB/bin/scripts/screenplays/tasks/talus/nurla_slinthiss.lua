nurla_slinthiss_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "nurla_corsec_captain", planetName = "talus", npcName = "" }
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
				{ npcTemplate = "nurla_employee", planetName = "talus", npcName = "Nurla's Employee" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nurla_corsec_rogue", planetName = "talus", npcName = "" },
				{ npcTemplate = "nurla_corsec_rogue", planetName = "talus", npcName = "" },
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
				{ npcTemplate = "nurla_businessman", planetName = "talus", npcName = "Businessman" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nurla_jabba_enforcer", planetName = "talus", npcName = "" },
				{ npcTemplate = "nurla_jabba_enforcer", planetName = "talus", npcName = "" },
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
				{ npcTemplate = "nurla_assassin", planetName = "talus", npcName = "Assassin" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nurla_hutt_gangster", planetName = "talus", npcName = "a Hutt gangster" },
				{ npcTemplate = "nurla_hutt_gangster", planetName = "talus", npcName = "a Hutt gangster" },
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
			spawnData = { planetName = "talus", npcTemplate = "nurla_slinthiss", x = -5.3, z = -0.9, y = -21, direction = 0, cellID = 3175396, position = STAND },
			worldPosition = { x = 435, y = -2948 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_dearic_nurla_slinthiss",
			missions = nurla_slinthiss_missions
		},
	}

NurlaSlinthiss = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapNurlaSlinthiss,
	className = "NurlaSlinthiss",
	screenPlayState = "nurla_slinthiss_quest",
	distance = 800
}

registerScreenPlay("NurlaSlinthiss", true)

nurla_slinthiss_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = NurlaSlinthiss
}
nurla_slinthiss_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = NurlaSlinthiss
}