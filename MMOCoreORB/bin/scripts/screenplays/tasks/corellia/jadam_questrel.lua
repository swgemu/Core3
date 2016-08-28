jadam_questrel_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "nola_indrivin", npcName = "Nola Indrivin" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "corsec_agent", npcName = "a CorSec agent" },
				{ npcTemplate = "corsec_agent", npcName = "a CorSec agent" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/jadam_questrel_q1_needed.iff", itemName = "Bonadan Contract Report" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 500 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "nola_indrivin", npcName = "Nola Indrivin" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "corsec_investigator", npcName = "a CorSec investigator" },
				{ npcTemplate = "corsec_master_sergeant", npcName = "a CorSec Master Sergeant" },
				{ npcTemplate = "corsec_master_sergeant", npcName = "a CorSec Master Sergeant" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "lunce_targettal", npcName = "Lunce Targettal" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "corsec_captain", npcName = "a CorSec Captain" },
				{ npcTemplate = "corsec_trooper", npcName = "a CorSec trooper" },
				{ npcTemplate = "corsec_trooper", npcName = "a CorSec trooper" },
				{ npcTemplate = "corsec_trooper", npcName = "a CorSec trooper" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 2000 }
			}
		}
	}

npcMapJadamQuestrel =
	{
		{
			spawnData = { npcTemplate = "jadam_questrel", x = 9.78, z = -0.89, y = -14.48, direction = 262, cellID = 3075432, position = STAND },
			worldPosition = { x = 3227, y = 5330 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/jadam_questrel",
			missions = jadam_questrel_missions
		}
	}

JadamQuestrel = ThemeParkLogic:new {
	npcMap = npcMapJadamQuestrel,
	className = "JadamQuestrel",
	screenPlayState = "jadam_questrel_quest",
	planetName = "corellia",
	distance = 800
}

registerScreenPlay("JadamQuestrel", true)

jadam_questrel_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = JadamQuestrel
}

jadam_questrel_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = JadamQuestrel
}