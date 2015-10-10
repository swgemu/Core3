shibb_nisshil_missions =
{
	{
		missionType = "assassinate",
			primarySpawns = {
				{ npcTemplate = "shibb_gnarled_rancor", planetName = "dathomir", npcName = "Gnarled Rancor" },
			},
			secondarySpawns = {
				{ npcTemplate = "brigand_assassin", planetName = "dathomir", npcName = "a thug" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 },
				{ rewardType = "faction", faction = "imperial", amount = 10 }
			}
	},
	{
		missionType = "assassinate",
			primarySpawns =
			 {
				{ npcTemplate = "brigand_leader", planetName = "dathomir", npcName = "Rancor Thief" },
			 },
			 secondarySpawns =
			{
				{ npcTemplate = "brigand_assassin", planetName = "dathomir", npcName = "random" },
				{ npcTemplate = "brigand_assassin", planetName = "dathomir", npcName = "random" },
				{ npcTemplate = "brigand_assassin", planetName = "dathomir", npcName = "random" },
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
				{ npcTemplate = "bounty_hunter_thug", planetName = "dathomir", npcName = "Bounty Hunter" }
			},
			secondarySpawns = {
				{ npcTemplate = "terrorist", planetName = "dathomir", npcName = "a terrorist" },
				{ npcTemplate = "terrorist", planetName = "dathomir", npcName = "a terrorist" },
				{ npcTemplate = "terrorist", planetName = "dathomir", npcName = "a terrorist" }
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
		spawnData = { planetName = "dathomir", npcTemplate = "shibb_nisshil", x = -71.1537, z = 18, y = -1639.84, direction = 66, cellID = 0},
		npcNumber = 1,
		stfFile = "@static_npc/dathomir/dathomir_researchoutpost_shibb_nisshil",
		missions = shibb_nisshil_missions
	},
}

ShibbNisshil = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapShibbNisshil,
	className = "ShibbNisshil",
	screenPlayState = "shibb_nisshil_quest",
	distance = 1000,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("ShibbNisshil", true)

shibb_nisshil_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ShibbNisshil
}
shibb_nisshil_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ShibbNisshil
}

