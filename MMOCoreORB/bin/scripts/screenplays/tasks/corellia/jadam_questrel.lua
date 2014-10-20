jadam_questrel_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "nola_indrivin", planetName = "corellia", npcName = "Nola Indrivin" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "corsec_agent", planetName = "corellia", npcName = "a CorSec agent" },
				{ npcTemplate = "corsec_agent", planetName = "corellia", npcName = "a CorSec agent" }
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
				{ npcTemplate = "nola_indrivin", planetName = "corellia", npcName = "Nola Indrivin" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "corsec_investigator", planetName = "corellia", npcName = "a CorSec investigator" },
				{ npcTemplate = "corsec_master_sergeant", planetName = "corellia", npcName = "a CorSec Master Sergeant" },
				{ npcTemplate = "corsec_master_sergeant", planetName = "corellia", npcName = "a CorSec Master Sergeant" }
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
				{ npcTemplate = "lunce_targettal", planetName = "corellia", npcName = "Lunce Targettal" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "corsec_captain", planetName = "corellia", npcName = "a CorSec Captain" },
				{ npcTemplate = "corsec_trooper", planetName = "corellia", npcName = "a CorSec trooper" },
				{ npcTemplate = "corsec_trooper", planetName = "corellia", npcName = "a CorSec trooper" },
				{ npcTemplate = "corsec_trooper", planetName = "corellia", npcName = "a CorSec trooper" }
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
			spawnData = { planetName = "corellia", npcTemplate = "jadam_questrel", x = 9.78, z = -0.89, y = -14.48, direction = 262, cellID = 3075432, position = STAND },
			worldPosition = { x = 3227, y = 5330 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/jadam_questrel",
			missions = jadam_questrel_missions
		}
	}

JadamQuestrel = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapJadamQuestrel,
	className = "JadamQuestrel",
	screenPlayState = "jadam_questrel_quest",
	distance = 800
}

registerScreenPlay("JadamQuestrel", true)

jadam_questrel_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = JadamQuestrel
}

jadam_questrel_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = JadamQuestrel
}