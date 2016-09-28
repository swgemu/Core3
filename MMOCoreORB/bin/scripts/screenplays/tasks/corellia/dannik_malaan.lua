dannik_malaan_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "slicer_quest_dannik", npcName = "Raviel Tyrrus" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/dannik_malaan_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 300 }
			}
		}
	}

npcMapDannikMalaan =
	{
		{
			spawnData = { npcTemplate = "dannik_malaan", x = -377.5, z = 28.0, y = -4539.1, direction = -1, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/dannik_malaan",
			missions = dannik_malaan_missions
		},
	}

DannikMalaan = ThemeParkLogic:new {
	npcMap = npcMapDannikMalaan,
	className = "DannikMalaan",
	screenPlayState = "dannik_malaan_task",
	planetName = "corellia",
	distance = 1000,
}

registerScreenPlay("DannikMalaan", true)

dannik_malaan_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = DannikMalaan
}
dannik_malaan_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = DannikMalaan
}
