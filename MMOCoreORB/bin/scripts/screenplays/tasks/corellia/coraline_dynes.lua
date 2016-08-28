coraline_dynes_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "lith_kalis", npcName = "Lith K'alis" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 350 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "kalio_uldi", npcName = "Kalio Uldi" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 700 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "blurga_vuto", npcName = "Blurga Vuto" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1400 }
			}
		}
	}

npcMapCoralineDynes =
	{
		{
			spawnData = { npcTemplate = "coraline_dynes", x = -24.39, z = -0.52, y = 10.55, direction = -8, cellID = 3075439, position = STAND },
			worldPosition = { x = 3269, y = 5337 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/coraline_dynes",
			missions = coraline_dynes_missions
		}
	}

CoralineDynes = ThemeParkLogic:new {
	npcMap = npcMapCoralineDynes,
	className = "CoralineDynes",
	screenPlayState = "coraline_dynes_quest",
	planetName = "corellia",
	distance = 800
}

registerScreenPlay("CoralineDynes", true)

coraline_dynes_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = CoralineDynes
}

coraline_dynes_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = CoralineDynes
}