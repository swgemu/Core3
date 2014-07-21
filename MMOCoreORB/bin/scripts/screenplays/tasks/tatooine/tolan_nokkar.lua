tolan_nokkar_missions =
	{
		{
			missionType = "hunt",
			huntTarget = { npcTemplate = "tusken_king_quest", npcName = "A Tusken King", planetName = "tatooine", waypointX = -5320, waypointY = -4442 },
			rewards =
			{
				{ rewardType = "credits", amount = 20000 },
			}
		},

	}

npcMapTolanNokkar =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "tolan_nokkar", x = -5477, z = 30.0, y = -3881, direction = 118, cellID = 0, position = STAND },
			worldPosition = { x = -5477, y = -3881 },
			npcNumber = 1,
			stfFile = "@spawning/static_npc/tusken_village_quest_npc",
			missions = tolan_nokkar_missions
		},
	}

TolanNokkar = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapTolanNokkar,
	className = "TolanNokkar",
	screenPlayState = "tolan_nokkar_quest",
}

registerScreenPlay("TolanNokkar", true)

tolan_nokkar_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = TolanNokkar
}
tolan_nokkar_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = TolanNokkar
}