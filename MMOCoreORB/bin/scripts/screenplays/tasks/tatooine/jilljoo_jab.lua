jilljoo_jab_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "jilljoo_slave", npcName = "Sadelli" }
			},
			secondarySpawns = 
			{
				{ npcTemplate = "thug", npcName = "a Thug" },
				{ npcTemplate = "thug", npcName = "a Thug" },
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
				{ npcTemplate = "jilljoo_slave", npcName = "Soolami" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a Thug" },
				{ npcTemplate = "slaver", npcName = "a Slaver" },
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
				{ npcTemplate = "woff_btar", npcName = "Woff B'tar" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "jabba_thug", npcName = "a Jabba Thug" },
				{ npcTemplate = "jabba_thug", npcName = "a Jabba Thug" },
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
			spawnData = { npcTemplate = "jilljoo_jab", x = 10.58, z = -0.89, y = -3.56, direction = 237.7, cellID = 1256058, position = STAND },
			worldPosition = { x = -3001, y = 2161 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/jilljoo_jab",
			missions = jilljoo_jab_missions
		},
	}

JilljooJab = ThemeParkLogic:new {
	npcMap = npcMapJilljooJab,
	className = "JilljooJab",
	screenPlayState = "jilljoo_jab_quest",
	planetName = "tatooine",
	distance = 800
}

registerScreenPlay("JilljooJab", true)

jilljoo_jab_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = JilljooJab
}
jilljoo_jab_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = JilljooJab
}