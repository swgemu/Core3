lorne_prestar_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "worrt", npcName = "a worrt" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 30 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "mound_mite", npcName = "a mound mite" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 30 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a Thug" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 40 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "tusken_warlord", npcName = "a Tusken warlord" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "tusken_raider", npcName = "a Tusken raider" },
				{ npcTemplate = "tusken_raider", npcName = "a Tusken raider" },
				{ npcTemplate = "tusken_raider", npcName = "a Tusken raider" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 40 }
			}
		},
	}

npcMapLornePrestar =
	{
		{
			spawnData = { npcTemplate = "lorne_prestar", x = 3826.5, z = 20, y = 2367.9, direction = 260, cellID = 0, position = STAND },
			worldPosition = { x = 3827, y = 2368 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/lorne_prestar",
			missions = lorne_prestar_missions
		},
	}

LornePrestar = ThemeParkLogic:new {
	npcMap = npcMapLornePrestar,
	className = "LornePrestar",
	screenPlayState = "lorne_prestar_quest",
	planetName = "tatooine",
	distance = 600
}

registerScreenPlay("LornePrestar", true)

lorne_prestar_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LornePrestar
}
lorne_prestar_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = LornePrestar
}