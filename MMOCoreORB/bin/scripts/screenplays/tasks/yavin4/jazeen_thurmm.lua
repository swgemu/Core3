jazeen_thurmm_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "surveyor_quest_jazeen", npcName = "Lead Surveyor" }
			},
			secondarySpawns =
			{
			},
			staticObjects =
			{
				{ objectTemplate = "object/mobile/kaadu.iff", objectName = "a pack kaadu" },
				{ objectTemplate = "object/mobile/dressed_commoner_tatooine_nikto_male_04.iff", objectName = "a Surveyor" },
				{ objectTemplate = "object/mobile/dressed_commoner_tatooine_aqualish_female_07.iff", objectName = "a Surveyor" },
				{ objectTemplate = "object/mobile/dressed_commoner_tatooine_ishitib_male_02.iff", objectName = "a Surveyor" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/jazeen_thurmm_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "angler_recluse", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "angler", npcName = "" },
				{ npcTemplate = "angler", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 150 },
				{ rewardType = "loot", lootGroup = "task_reward_suit_jazeen" },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "survivor_quest_jazeen", npcName = "Survey Team Survivor" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "choku_hunter", npcName = "" },
				{ npcTemplate = "choku", npcName = "" },
				{ npcTemplate = "choku", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 200 },
			}
		}
	}

npcMapJazeenThurmm =
	{
		{
			spawnData = { npcTemplate = "jazeen_thurmm", x = 7.7, z = 0.6, y = -6.0, direction = -70, cellID = 7925452, position = STAND },
			npcNumber = 1,
			worldPosition = { x = -355, y = 4874 },
			stfFile = "@static_npc/yavin/jazeen_thumm",
			missions = jazeen_thurmm_missions
		},
	}

JazeenThurmm = ThemeParkLogic:new {
	npcMap = npcMapJazeenThurmm,
	className = "JazeenThurmm",
	screenPlayState = "jazeen_thurmm_tasks",
	planetName = "yavin4",
	distance = 900
}

registerScreenPlay("JazeenThurmm", true)

jazeen_thurmm_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = JazeenThurmm
}
jazeen_thurmm_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = JazeenThurmm
}
