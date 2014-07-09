jilljoo_jab_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "jilljoo_slave", planetName = "tatooine", npcName = "Sadelli" }
			},
			secondarySpawns = 
			{
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "a Thug" },
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "a Thug" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "jilljoo_slave", planetName = "tatooine", npcName = "Soolami" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "a Thug" },
				{ npcTemplate = "slaver", planetName = "tatooine", npcName = "a Slaver" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 2000 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "woff_btar", planetName = "tatooine", npcName = "Woff B'tar" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "jabba_thug", planetName = "tatooine", npcName = "a Jabba Thug" },
				{ npcTemplate = "jabba_thug", planetName = "tatooine", npcName = "a Jabba Thug" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 4000 },
			}
		},

	}

npcMapJilljooJab =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "jilljoo_jab", x = 10.58, z = -0.89, y = -3.56, direction = 237.7, cellID = 1256058, position = STAND },
			worldPosition = { x = -3001, y = 2161 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/jilljoo_jab",
			missions = jilljoo_jab_missions
		},
	}

JilljooJab = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapJilljooJab,
	className = "JilljooJab",
	screenPlayState = "jilljoo_jab_quest",
	distance = 800
}

registerScreenPlay("JilljooJab", true)

jilljoo_jab_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = JilljooJab
}
jilljoo_jab_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = JilljooJab
}