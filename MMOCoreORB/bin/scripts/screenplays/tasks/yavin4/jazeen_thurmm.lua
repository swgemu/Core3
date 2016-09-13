jazeen_thurmm_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "surveyor_quest_jazeen", npcName = "Lead Surveyor" },
				{ npcTemplate = "agriculturalist", npcName = "" },
				{ npcTemplate = "agriculturalist", npcName = "" },
				{ npcTemplate = "kaadu", npcName = "" }
				--* I had to add all of these extra spawns ^  here in 'Primary' cuz when i added them to 'Secondary', they
					--would all auto-aggro ME. The quest works fine though, despite all spawns having the "interesting" bit
					--ICON above head, the only one the player needs to converse with is the 'Lead Surveyor' obviously (which
					--btw is also the only one i designed to say the 'npc_breech_1' dialog)
			},
			secondarySpawns =
			{
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
			{--*The purple quest icon says "Angler LAIR", as does some of the string-file dialog, so can we have a 'destroy'
			--type mission here but spawn an actual angler LAIR template/theater???
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
