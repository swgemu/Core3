serjix_arrogantus_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "gleeb_tchotle", npcName = "Gleeb Tchotle" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/serjix_arrogantus_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 50 }
			}
		}
	}

npcMapSerjixArrogantus =
	{
		{
			spawnData = { npcTemplate = "serji_x_arrogantus", x = -201.4, z = 45.5, y = 4576.9, direction = -87, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/serji_x_arrogantus",
			missions = serjix_arrogantus_missions
		},
	}

SerjixArrogantus = ThemeParkLogic:new {
	npcMap = npcMapSerjixArrogantus,
	className = "SerjixArrogantus",
	screenPlayState = "serjix_arrogantus_task",
	planetName = "corellia",
	distance = 700,
}

registerScreenPlay("SerjixArrogantus", true)

serjix_arrogantus_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = SerjixArrogantus
}
serjix_arrogantus_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = SerjixArrogantus
}
