didina_lippinoss_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "bin_huusir", npcName = "Bin Huusir" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/didina_lippinoss_q1_needed.iff", itemName = "Flim's Correspondence" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 200 }
			}
		}
	}

npcMapDidinaLippinoss =
	{
		{
			spawnData = { npcTemplate = "didina_lippinoss", x = -8.43, z = 1.6, y = -11.42, direction = 69.197, cellID = 1935530, position = STAND },
			worldPosition = { x = -5508, y = -2557 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/didina_lippinoss",
			missions = didina_lippinoss_missions
		}
	}

DidinaLippinoss = ThemeParkLogic:new {
	npcMap = npcMapDidinaLippinoss,
	className = "DidinaLippinoss",
	screenPlayState = "didina_lippinoss_quest",
	planetName = "corellia",
	distance = 800
}

registerScreenPlay("DidinaLippinoss", true)

didina_lippinoss_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = DidinaLippinoss
}

didina_lippinoss_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = DidinaLippinoss
}