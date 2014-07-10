gramm_rile_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "gramm_surveyor", planetName = "tatooine", npcName = "a Surveyor" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "gramm_surveyor", planetName = "tatooine", npcName = "a Farmer" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 500 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "gramm_businessman", planetName = "tatooine", npcName = "a Businessman" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 750 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "chastina_rile", planetName = "tatooine", npcName = "Chastina Rile" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" },
				{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "", dead = "true" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1200 },
			}
		}
	}

npcMapGrammRile =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "gramm_rile", x = 3887.3, z = 33, y = 2348.6, direction = 300, cellID = 0, position = STAND },
			worldPosition = { x = 3887, y = 2347 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/gramm_rile",
			missions = gramm_rile_missions
		},
	}

GrammRile = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapGrammRile,
	className = "GrammRile",
	screenPlayState = "gramm_rile_quest",
	distance = 600
}

registerScreenPlay("GrammRile", true)

gramm_rile_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = GrammRile
}
gramm_rile_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = GrammRile
}