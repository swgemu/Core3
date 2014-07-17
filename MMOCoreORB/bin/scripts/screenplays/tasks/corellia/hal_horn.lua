hal_horn_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "doogo", planetName = "corellia", npcName = "Doogo" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/hal_horn_q1_needed.iff", itemName = "Slythmonger's Notes" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 500 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "mwaloob", planetName = "corellia", npcName = "Mwaloob" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 750 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "sporg_lutwink", planetName = "corellia", npcName = "Sporg Lutwink" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "smuggler", planetName = "corellia", npcName = "a smuggler" },
				{ npcTemplate = "smuggler", planetName = "corellia", npcName = "a smuggler" },
				{ npcTemplate = "smuggler", planetName = "corellia", npcName = "a smuggler" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 }
			}
		}
	}

npcMapHalHorn =
	{
		{
			spawnData = { planetName = "corellia", npcTemplate = "hal_horn", x = -15.05, z = 2.25, y = 11.14, direction = 0, cellID = 1935472, position = STAND },
			worldPosition = { x = -5516, y = -2805 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/hal_horn",
			missions = hal_horn_missions
		}
	}

HalHorn = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapHalHorn,
	className = "HalHorn",
	screenPlayState = "hal_horn_quest",
	distance = 800
}

registerScreenPlay("HalHorn", true)

hal_horn_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = HalHorn
}

hal_horn_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = HalHorn
}