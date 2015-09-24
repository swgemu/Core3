shibb_nisshil_missions =
{
	{
		missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "gnarled_rancor", planetName = "dathomir", npcName = "Gnarled Rancor" }
			},
			secondarySpawns = {
				{ npcTemplate = "brigand", planetName = "dathomir", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 },
				{ rewardType = "faction", faction = "imperial", amount = 10 }
			}
	},
	{
		missionType = "escort",
			primarySpawns =
			 {
				{ npcTemplate = "shibb_test_rancor", planetName = "dathomir", npcName = "Test Rancor" }
			 },
			 secondarySpawns =
			{
				{ npcTemplate = "brigand_leader", planetName = "dathomir", npcName = "random" },
				{ npcTemplate = "brigand", planetName = "dathomir", npcName = "random" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 300 },
				{ rewardType = "faction", faction = "imperial", amount = 10 }
			}
	},
	{
		missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "brigand_leader", planetName = "dathomir", npcName = "Bounty Hunter" }
			},
			secondarySpawns = {
				{ npcTemplate = "thug", planetName = "dathomir", npcName = "a terrorist" },
				{ npcTemplate = "thug", planetName = "dathomir", npcName = "a terrorist" },
				{ npcTemplate = "thug", planetName = "dathomir", npcName = "a terrorist" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 300 },
				{ rewardType = "faction", faction = "imperial", amount = 10 }
			}
	}
}

npcMapShibbNisshil =
{
	{
		spawnData = { planetName = "dathomir", npcTemplate = "shibb_nisshil", x = -71.1537, z = 18, y = -1639.84, direction = 66, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/dathomir/dathomir_researchoutpost_shibb_nisshil",
		missions = shibb_nisshil_missions
	},
}

ShibbNisshil = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapShibbNisshil,
	permissionMap = permissionMapImperial,
	className = "ShibbNisshil",
	screenPlayState = "shibb_nisshil_quest",
	distance = 1200,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("ShibbNisshil", true)

shibb_nisshil_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ShibbNisshil
}
shibb_nisshil_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ShibbNisshil
}
