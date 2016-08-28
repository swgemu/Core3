corran_horn_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "chandra_conrad", npcName = "Chandra Conrad" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "obrio_caldori", npcName = "Obrio Caldori" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 400 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "voydd_blancken", npcName = "Voydd Blancken" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 800 }
			}
		}
	}

npcMapCorranHorn =
	{
		{
			spawnData = { npcTemplate = "corran_horn", x = -2.8, z = 2.5, y = 12.1, direction = 40, cellID = 3075353, position = STAND },
			worldPosition = { x = 3189, y = 5239 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/corran_horn",
			missions = corran_horn_missions
		}
	}

CorranHorn = ThemeParkLogic:new {
	npcMap = npcMapCorranHorn,
	className = "CorranHorn",
	screenPlayState = "corran_horn_quest",
	planetName = "corellia",
	distance = 800
}

registerScreenPlay("CorranHorn", true)

corran_horn_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = CorranHorn
}

corran_horn_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = CorranHorn
}