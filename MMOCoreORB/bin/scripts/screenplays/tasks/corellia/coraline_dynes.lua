coraline_dynes_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "lith_kalis", planetName = "corellia", npcName = "Lith K'alis" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
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
				{ npcTemplate = "kalio_uldi", planetName = "corellia", npcName = "Kalio Uldi" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" }
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
				{ npcTemplate = "blurga_vuto", planetName = "corellia", npcName = "Blurga Vuto" }
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
			spawnData = { planetName = "corellia", npcTemplate = "coraline_dynes", x = -24.39, z = -0.52, y = 10.55, direction = -8, cellID = 3075439, position = STAND },
			worldPosition = { x = 3269, y = 5337 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/coraline_dynes",
			missions = coraline_dynes_missions
		}
	}

CoralineDynes = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapCoralineDynes,
	className = "CoralineDynes",
	screenPlayState = "coraline_dynes_quest",
	distance = 800
}

registerScreenPlay("CoralineDynes", true)

coraline_dynes_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = CoralineDynes
}

coraline_dynes_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = CoralineDynes
}