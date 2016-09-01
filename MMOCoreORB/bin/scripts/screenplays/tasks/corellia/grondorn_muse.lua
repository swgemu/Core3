grondorn_muse_missions =
{
	{
		missionType = "escort",
		primarySpawns =
		{
			{ npcTemplate = "bandmember_quest_grondorn", npcName = "Vincol Dunker" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "credits", amount = 150 }
		}
	},
	{
		missionType = "deliver",
		primarySpawns =
		{
			{ npcTemplate = "bandleader_quest_grondorn", npcName = "Pytor Tuko" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/grondorn_muse_q2_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 250 }
		}
	}
}

npcMapGrondornMuse =
{
	{
		spawnData = { npcTemplate = "grondorn_muse", x = 6838.2, z = 315.0, y = -5767.7, direction = -99, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/corellia/grondorn_muse",
		missions = grondorn_muse_missions
	},
}

GrondornMuse = ThemeParkLogic:new {
	npcMap = npcMapGrondornMuse,
	className = "GrondornMuse",
	screenPlayState = "grondorn_muse_task",
	planetName = "corellia",
	distance = 800,
}

registerScreenPlay("GrondornMuse", true)

grondorn_muse_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = GrondornMuse
}
grondorn_muse_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = GrondornMuse
}