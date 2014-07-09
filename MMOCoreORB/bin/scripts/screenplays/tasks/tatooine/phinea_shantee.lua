phinea_shantee_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "wookiee_brawler", planetName = "tatooine", npcName = "Chalurrekk" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
				{ rewardType = "loot",  lootGroup = "task_reward_phinea_shantee_q1" }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "korrkoressk", planetName = "tatooine", npcName = "Korrkoressk" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
				{ rewardType = "loot",  lootGroup = "task_reward_phinea_shantee_q2" }
			}
		}
	}

npcMapPhineaShantee =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "phinea_shantee", x = -10.3, z = -0.9, y = -18.7, direction = 27, cellID = 1028652, position = STAND },
			worldPosition = { x = -1420, y = -3682 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/phinea_shantee",
			missions = phinea_shantee_missions
		},
	}

PhineaShantee = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapPhineaShantee,
	className = "PhineaShantee",
	screenPlayState = "phinea_shantee_quest",
	distance = 800
}

registerScreenPlay("PhineaShantee", true)

phinea_shantee_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = PhineaShantee
}
phinea_shantee_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = PhineaShantee
}