denell_kel_vannon_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "shaedra_valouri", planetName = "corellia", npcName = "Shaedra Valouri" }
			},
			secondarySpawns =	{},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/denell_kelvannon_q1_needed.iff", itemName = "CorSec evidence" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 300 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "mac_varley", planetName = "corellia", npcName = "Captain Mac Varley" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 400 }
			}
		},
		-- Quest 3 disabled as no information on quest is available (quest 2 was bugged on live)
		--[[ 
		{
			missionType = "assassinate",
			primarySpawns = {},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards = {}
		}]]
	}

npcMapDenellKelVannon =
	{
		{
			spawnData = { planetName = "corellia", npcTemplate = "denell_kelvannon", x = -3414.11, z = 74, y = 3337.52, direction = 28, cellID = 0, position = STAND },
			worldPosition = { x = -3414, y = 3336 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/denell_kel_vannon",
			missions = denell_kel_vannon_missions
		}
	}

DenellKelVannon = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapDenellKelVannon,
	className = "DenellKelVannon",
	screenPlayState = "denell_kel_vannon_quest",
	distance = 800
}

registerScreenPlay("DenellKelVannon", true)

denell_kel_vannon_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = DenellKelVannon
}

denell_kel_vannon_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = DenellKelVannon
}