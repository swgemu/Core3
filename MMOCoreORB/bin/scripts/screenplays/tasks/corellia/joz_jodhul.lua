joz_jodhul_missions =
{
	{
		missionType = "assassinate",
		primarySpawns =
		{
			{ npcTemplate = "scavenger_rat", npcName = "*The Beast*" }
		},
		secondarySpawns =
		{

		},
		staticObjects =
		{

		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "credits", amount = 50 }
		}
	}
}

npcMapJozJodhul =
{
	{
		spawnData = { npcTemplate = "joz_jodhul", x = 764.1, z = 423.3, y = 5866.2, direction = 143, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/corellia/joz_jodhul",
		missions = joz_jodhul_missions
	},
}

JozJodhul = ThemeParkLogic:new {
	npcMap = npcMapJozJodhul,
	className = "JozJodhul",
	screenPlayState = "joz_jodhul_quest",
	planetName = "corellia",
	distance = 3000,
}

registerScreenPlay("JozJodhul", true)

joz_jodhul_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = JozJodhul
}
joz_jodhul_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = JozJodhul
}
