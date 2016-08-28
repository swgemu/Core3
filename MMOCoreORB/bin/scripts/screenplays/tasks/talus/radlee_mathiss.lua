radlee_mathiss_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "radlee_businessman", npcName = "a Businessman" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "radlee_thug", npcName = "a Thug" },
				{ npcTemplate = "radlee_thug", npcName = "a Thug" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/radlee_mathiss_q1_needed.iff", itemName = "Credit Disc" }
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
				{ npcTemplate = "radlee_businessman", npcName = "a CSA Representive" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "radlee_thug", npcName = "a Thug" },
				{ npcTemplate = "radlee_thug", npcName = "a Thug" },
				{ npcTemplate = "radlee_thug", npcName = "a Thug" },
			},
			itemSpawns = { },
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "radlee_criminal", npcName = "a Criminal" },
				{ npcTemplate = "radlee_criminal", npcName = "a Criminal" },
				{ npcTemplate = "radlee_criminal", npcName = "a Criminal" },
			},
			secondarySpawns = { },
			itemSpawns = { },
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
			}
		},
	}

npcMapRadleeMathiss =
	{
		{
			spawnData = { npcTemplate = "radlee_mathiss", x = -2.6, z = 0, y = 6.3, direction = 90, cellID = 3175391, position = STAND },
			worldPosition = { x = 435, y = -2922 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_dearic_radlee_mathiss",
			missions = radlee_mathiss_missions
		},
	}

RadleeMathiss = ThemeParkLogic:new {
	npcMap = npcMapRadleeMathiss,
	className = "RadleeMathiss",
	screenPlayState = "radlee_mathiss_quest",
	planetName = "talus",
	distance = 800
}

registerScreenPlay("RadleeMathiss", true)

radlee_mathiss_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = RadleeMathiss
}
radlee_mathiss_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = RadleeMathiss
}