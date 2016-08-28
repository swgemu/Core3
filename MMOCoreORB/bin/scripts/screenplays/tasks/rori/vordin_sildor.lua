vordin_sildor_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "vordin_scientist", npcName = "a Scientist" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "vordin_bounty_hunter", npcName = "a Bounty Hunter" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
				{ rewardType = "faction", faction = "rebel", amount = 10 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "vordin_girlfriend", npcName = "Smuggler's Girlfriend" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "vordin_pirate", npcName = "a Pirate" },
				{ npcTemplate = "vordin_pirate", npcName = "a Pirate" },
				{ npcTemplate = "vordin_pirate", npcName = "a Pirate" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
				{ rewardType = "faction", faction = "rebel", amount = 25 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "vordin_pirate_captain", npcName = "Pirate Captain" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "vordin_pirate", npcName = "a Pirate" },
				{ npcTemplate = "vordin_pirate", npcName = "a Pirate" },
				{ npcTemplate = "vordin_pirate", npcName = "a Pirate" },
				{ npcTemplate = "vordin_pirate", npcName = "a Pirate" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/vordin_sildor_q3_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
				{ rewardType = "faction", faction = "rebel", amount = 50 }
			}
		},
	}

npcMapVordinSildor =
	{
		{
			spawnData = { npcTemplate = "vordin_sildor", x = 4.2, z = 0.1, y = 0.8, direction = 196, cellID = 4505667, position = SIT },
			worldPosition = { x = 3650, y = -6470 },
			npcNumber = 1,
			stfFile = "@static_npc/rori/rori_rebeloutpost_vordin_sildor",
			missions = vordin_sildor_missions
		},

	}

VordinSildor = ThemeParkLogic:new {
	npcMap = npcMapVordinSildor,
	className = "VordinSildor",
	screenPlayState = "vordin_sildor_quest",
	planetName = "rori",
	distance = 600,
	faction = FACTIONREBEL
}

registerScreenPlay("SindraLintikoor", true)

vordin_sildor_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = VordinSildor
}
vordin_sildor_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = VordinSildor
}
