ebenn_q3_baobab_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "rinto_liprus", npcName = "Rinto Liprus" }
			},
			secondarySpawns =
			{

			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "tanner_helton", npcName = "Tanner Helton" }
			},
			secondarySpawns =
			{
				{npcTemplate = "rsf_security_guard", npcName = ""},
				{npcTemplate = "rsf_security_guard", npcName = ""}
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/ebenn_baobab_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 150 }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "nura_tinall", npcName = "Nura Tinall" }
			},
			secondarySpawns =
			{
				{npcTemplate = "thug", npcName = ""},
				{npcTemplate = "thug", npcName = ""},
				{npcTemplate = "thug", npcName = ""}
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/ebenn_baobab_q3_needed.iff", itemName = "" }
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
				{ npcTemplate = "wert_jopi", npcName = "Wert Jopi" }
			},
			secondarySpawns =
			{
				{npcTemplate = "gungan_mercenary", npcName = ""},
				{npcTemplate = "gungan_mercenary", npcName = ""},
				{npcTemplate = "gungan_mercenary", npcName = ""}
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

npcMapEbennQ3Baobab =
	{
		{
			spawnData = { npcTemplate = "ebenn_q3_baobab", x = 4869.0, z = 3.8, y = -4873.0, direction = -90, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/ebenn_q3_baobab",
			missions = ebenn_q3_baobab_missions
		},
	}

EbennQ3Baobab = ThemeParkLogic:new {
	faction = FACTIONREBEL,
	npcMap = npcMapEbennQ3Baobab,
	className = "EbennQ3Baobab",
	screenPlayState = "ebenn_q3_baobab_task",
	planetName = "naboo",
	distance = 1000,
}

registerScreenPlay("EbennQ3Baobab", true)

ebenn_q3_baobab_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = EbennQ3Baobab
}
ebenn_q3_baobab_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = EbennQ3Baobab
}
