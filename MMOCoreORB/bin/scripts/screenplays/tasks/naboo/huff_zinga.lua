huff_zinga_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "huff_blistmok", planetName = "naboo", npcName = "Adult blistmok" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "bocatt", planetName = "naboo", npcName = "Bocatt" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "sharptooth_langlatch", planetName = "naboo", npcName = "Langlatch" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "grassland_slice_hound", planetName = "naboo", npcName = "Corellian Slice Hound" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 },
			}
		},

	}

npcMapHuffZinga =
	{
		{
			spawnData = { planetName = "naboo", npcTemplate = "huff_zinga", x = 5155, z = -192, y = 6636, direction = 47, cellID = 0, position = STAND },
			worldPosition = { x = 5155, y = 6636 },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/huff_zinga",
			missions = huff_zinga_missions
		}
	}

HuffZinga = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapHuffZinga,
	className = "HuffZinga",
	screenPlayState = "huff_zinga_quest",
	distance = 600
}

registerScreenPlay("HuffZinga", true)

huff_zinga_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = HuffZinga
}
huff_zinga_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = HuffZinga
}