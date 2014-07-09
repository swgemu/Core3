mullud_bombo_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "sentellus_gavrel", planetName = "naboo", npcName = "Sentellus Gavrel" }
			},
			secondarySpawns = {},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/mullud_bombo_q1_needed.iff", itemName = "Some survey equipment." }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
	}

npcMapMulludBombo =
	{
		{
			spawnData = { planetName = "naboo", npcTemplate = "mullud_bombo", x = 5045.9, z = -192, y = 6787.1, direction = -87, cellID = 0, position = STAND },
			worldPosition = { x = 5046, y = 6787 },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/mullud_bombo",
			missions = mullud_bombo_missions
		}
	}

MulludBombo = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapMulludBombo,
	className = "MulludBombo",
	screenPlayState = "mullud_bombo_quest",
	distance = 600
}

registerScreenPlay("MulludBombo", true)

mullud_bombo_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = MulludBombo
}
mullud_bombo_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = MulludBombo
}