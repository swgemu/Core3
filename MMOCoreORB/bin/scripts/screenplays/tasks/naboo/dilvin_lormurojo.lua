dilvin_lormurojo_missions =
{
	{
		missionType = "assassinate",
		primarySpawns =
		{
			{ npcTemplate = "borvos_thug", planetName = "naboo", npcName = "" }
		},
		secondarySpawns = {},
		itemSpawns = {},
		rewards =
		{
			{ rewardType = "credits", amount = 100 }
		}
	}
}

-- Has initial convo strings for 3 more missions but is missing most of the other necessary strings.

npcMapDilvinLormurojo =
{
	{
		spawnData = { planetName = "naboo", npcTemplate = "dilvin_lormurojo", x = 4892, z = 3.8, y = -4997.6, direction = 176, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/naboo/dilvin_lormurojo",
		missions = dilvin_lormurojo_missions
	},
}

DilvinLormurojo = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapDilvinLormurojo,
	permissionMap = {},
	className = "DilvinLormurojo",
	screenPlayState = "dilvin_lormurojo_task",
	distance = 800,
}

registerScreenPlay("DilvinLormurojo", true)

dilvin_lormurojo_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = DilvinLormurojo
}
dilvin_lormurojo_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = DilvinLormurojo
}
