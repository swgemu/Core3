warden_vinzel_haylon_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "prisoner_quest_vinzel", npcName = "Ezker 'The Brain' Kennin" }
			},
			secondarySpawns =
			{

			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "faction", faction = "imperial", amount = 5 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "escaped_traitor_quest_vinzel", npcName = "Teen Queevello" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "abandoned_rebel_private", npcName = "" },
				{ npcTemplate = "abandoned_rebel_private", npcName = "" },
				{ npcTemplate = "abandoned_rebel_private", npcName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "faction", faction = "imperial", amount = 15 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "nightsister_outcast", npcName = "a Nightsister Instigator" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "faction", faction = "imperial", amount = 10 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "prisoner_quest_vinzel_too", npcName = "Ezker Kennin" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "prisoner_quest_vinzel_riot", npcName = "" },
				{ npcTemplate = "prisoner_quest_vinzel_riot", npcName = "" },
				{ npcTemplate = "prisoner_quest_vinzel_riot", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "faction", faction = "imperial", amount = 10 }
			}
		}
	}

npcMapWardenVinzelHaylon =
	{
		{
			spawnData = { npcTemplate = "warden_vinzel_haylon", x = 16.8, z = 1.0, y = 20.9, direction = 159, cellID = 2665366, position = STAND },
			worldPosition = { x = -6343.1, y = 911.0 },
			npcNumber = 1,
			stfFile = "@static_npc/dathomir/vinzel_haylon",
			missions = warden_vinzel_haylon_missions
		}
	}

WardenVinzelHaylon = ThemeParkLogic:new {
	npcMap = npcMapWardenVinzelHaylon,
	className = "WardenVinzelHaylon",
	screenPlayState = "warden_vinzel_haylon_task",
	faction = FACTIONIMPERIAL,
	planetName = "dathomir",
	distance = 900,
}

registerScreenPlay("WardenVinzelHaylon", true)

warden_vinzel_haylon_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = WardenVinzelHaylon
}
warden_vinzel_haylon_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = WardenVinzelHaylon
}
