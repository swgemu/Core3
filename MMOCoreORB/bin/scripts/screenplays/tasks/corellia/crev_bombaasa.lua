crev_bombaasa_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "informant_quest_crev", npcName = "Sli'woon Biul" }
			},
			secondarySpawns =
			{
				{npcTemplate = "thug", npcName = ""},
				{npcTemplate = "thug", npcName = ""}
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/crev_bombaasa_q1_needed.iff", itemName = "" }
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
				{ npcTemplate = "servant_quest_crev", npcName = "Meeko" }
			},--THIS NPC^ IS SUPPOSED TO BE A 'TALZ' SPECIES, as per the convo string, BUT SOE NEVER ADDED THEM
			secondarySpawns =
			{
				{npcTemplate = "thug", npcName = ""},
				{npcTemplate = "thug", npcName = ""},
				{npcTemplate = "thug", npcName = ""}
			},
			itemSpawns = {
				{ itemTemplate = "object/tangible/mission/quest_item/crev_bombaasa_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 400 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "bountyhunter_quest_crev", npcName = "Mornng" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 800 }
			}
		}
	}

npcMapCrevBombaasa =
	{
		{
			spawnData = { npcTemplate = "crev_bombaasa", x = 45.2, z = 0.1, y = -0.0, direction = 128, cellID = 2625353, position = STAND },
			worldPosition = { x = -5201, y = -2566 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/crev_bombaasa",
			missions = crev_bombaasa_missions
		},
	}

CrevBombaasa = ThemeParkLogic:new {
	npcMap = npcMapCrevBombaasa,
	className = "CrevBombaasa",
	screenPlayState = "crev_bombaasa_task",
	planetName = "corellia",
	distance = 1000,
}

registerScreenPlay("CrevBombaasa", true)

crev_bombaasa_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = CrevBombaasa
}
crev_bombaasa_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = CrevBombaasa
}