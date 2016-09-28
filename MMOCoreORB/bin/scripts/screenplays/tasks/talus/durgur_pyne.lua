durgur_pyne_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "pirate_quest_durgur", npcName = "a Sleemo Lieutenant" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "sleemo_scamp", npcName = "" },
				{ npcTemplate = "sleemo_scamp", npcName = "" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "agent_quest_durgur", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "sleemo_vandal", npcName = "a Sleemo Vandal" },
				{ npcTemplate = "sleemo_scamp", npcName = "" },
				{ npcTemplate = "sleemo_scamp", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "pirate_captain", npcName = "a Pirate Captain" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "sleemo_delinquent", npcName = "" },
				{ npcTemplate = "sleemo_hoodlum", npcName = "" },
				{ npcTemplate = "sleemo_hoodlum", npcName = "" },
				{ npcTemplate = "sleemo_hoodlum", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 75 },
			}
		}
	}

npcMapDurgurPyne =
	{
		{
			spawnData = { npcTemplate = "durgur_pyne", x = 3.0, z = -0.1, y = 4.4, direction = -22, cellID = 4265614, position = STAND },
			worldPosition = { x = 4546, y = 5149 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_nashal_durgur_pyne",
			missions = durgur_pyne_missions
		},
	}

DurgurPyne = ThemeParkLogic:new {
	npcMap = npcMapDurgurPyne,
	className = "DurgurPyne",
	screenPlayState = "durgur_pyne_tasks",
	planetName = "talus",
	distance = 900
}

registerScreenPlay("DurgurPyne", true)

durgur_pyne_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = DurgurPyne
}
durgur_pyne_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = DurgurPyne
}