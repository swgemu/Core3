bren_kingal_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "thark", planetName = "tatooine", npcName = "Thark" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/bren_kingal_q1_needed.iff", itemName = "Shield Generator" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
				{ rewardType = "loot",  lootGroup = "task_reward_bren_kingal_q1" },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "kli_sithrin", planetName = "tatooine", npcName = "Kli Sithrin" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/bren_kingal_q2_needed.iff", itemName = "Stamina Medpack" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
				{ rewardType = "loot",  lootGroup = "task_reward_bren_kingal_q2" },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "jespral_farandan", planetName = "tatooine", npcName = "Jespral Farandan" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/bren_kingal_q3_needed.iff", itemName = "Farandan's datadisk" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
				{ rewardType = "loot",  lootGroup = "task_reward_bren_kingal_q3" },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "trone_thanamiroc", planetName = "tatooine", npcName = "Trone Thanamiroc" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/bren_kingal_q4_needed.iff", itemName = "AT-ST pilot's helmet" }
			},
			staticObjects =
			{
				{ objectTemplate = "object/static/vehicle/static_speeder_bike.iff", planetName = "tatooine" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
				{ rewardType = "loot",  lootGroup = "task_reward_bren_kingal_q4" },
			}
		}
	}

npcMapBrenKingal =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "bren_kingal", x = 3770.8, z = 8.3, y = 2346.7, direction = 20, cellID = 0, position = STAND },
			worldPosition = { x = 3771, y = 2347 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/bren_kingal",
			missions = bren_kingal_missions
		},
	}

BrenKingal = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapBrenKingal,
	permissionMap = {},
	className = "BrenKingal",
	screenPlayState = "bren_kingal_quest",
	distance = 800,
	faction = FACTIONREBEL

}

registerScreenPlay("BrenKingal", true)

bren_kingal_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = BrenKingal
}
bren_kingal_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = BrenKingal
}