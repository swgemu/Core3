farious_gletch_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "greenfingers", planetName = "tatooine", npcName = "Greenfingers" }
			},
			secondarySpawns =	{},
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
				{ npcTemplate = "gordul_koga", planetName = "tatooine", npcName = "Gordul Koga" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "a Thug" },
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "a Thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 3000 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "ripper", planetName = "tatooine", npcName = "Ripper" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "jabba_thug", planetName = "tatooine", npcName = "a Jabba Thug" },
				{ npcTemplate = "jabba_thug", planetName = "tatooine", npcName = "a Jabba Thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 4000 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "professor_whisper", planetName = "tatooine", npcName = "Professor Whisper" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 6000 },
			}
		}
	}

npcMapFariousGletch =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "farious_gletch", x = 1.7, z = -0.4, y = -5.5, direction = 315, cellID = 1278989, position = STAND },
			worldPosition = { x = -1334, y = -3886 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/farious_gletch",
			missions = farious_gletch_missions
		},
	}

FariousGletch = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapFariousGletch,
	className = "FariousGletch",
	screenPlayState = "farious_gletch_quest",
	distance = 800
}

registerScreenPlay("FariousGletch", true)

farious_gletch_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = FariousGletch
}
farious_gletch_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = FariousGletch
}
