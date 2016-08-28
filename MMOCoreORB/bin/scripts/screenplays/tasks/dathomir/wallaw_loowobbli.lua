wallaw_loowobbli_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "wallaw_bull_rancor", npcName = "Bull Rancor" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "brigand", npcName = "random" },
				{ npcTemplate = "brigand", npcName = "random" },
				{ npcTemplate = "brigand", npcName = "random" },
				{ npcTemplate = "brigand_leader", npcName = "random" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 300 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "nightsister_outcast", npcName = "Nightsister Outcast" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nightsister_slave", npcName = "" },
				{ npcTemplate = "nightsister_slave", npcName = "" },
				{ npcTemplate = "nightsister_slave", npcName = "" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 500 }, -- Temporary, needs to be researched.
			}
		},
	}

npcMapWallawLoowobbli =
	{
		{
			spawnData = { npcTemplate = "wallaw_loowobbli", x = 1.2, z = 0.6, y = 6.0, direction = -120, cellID = 6955367, position = STAND },
			worldPosition = { x = 604, y = 3041 },
			npcNumber = 1,
			stfFile = "@static_npc/dathomir/dathomir_tradeoutpost_wallaw_loowobbli",
			missions = wallaw_loowobbli_missions
		},

	}

WallawLoowobbli = ThemeParkLogic:new {
	npcMap = npcMapWallawLoowobbli,
	className = "WallawLoowobbli",
	screenPlayState = "wallaw_loowobbli_quest",
	planetName = "dathomir",
	distance = 400
}

registerScreenPlay("WallawLoowobbli", true)

wallaw_loowobbli_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = WallawLoowobbli
}
wallaw_loowobbli_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = WallawLoowobbli
}
