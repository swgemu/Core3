vhaunda_missions =
{
	{
		missionType = "confiscate",
		primarySpawns =
		{
			{ npcTemplate = "stormtrooper_squad_leader_quest", planetName = "dathomir", npcName = "LX-613" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "stormtrooper", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "stormtrooper", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "stormtrooper", planetName = "dathomir", npcName = "" }
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/vhaunda_q1_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
			{ rewardType = "credits", amount = 50 }
		}
	},
	{
		missionType = "assassinate",
		primarySpawns =
		{
			{ npcTemplate = "theme_park_singing_mountain_clan_arch_witch_peila", planetName = "dathomir", npcName = "Peila" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
			{ rewardType = "credits", amount = 75 },
			{ rewardType = "loot",  lootGroup = "theme_park_reward_smc_vhaunda_polearm" }
		}
	}
}

izaryx_missions =
{
	{
		missionType = "escort",
		primarySpawns =
		{
			{ npcTemplate = "theme_park_singing_mountain_clan_rancor_tamer", planetName = "dathomir", npcName = "a Singing Mountain Clan Scout" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "nightsister_rancor_tamer", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "nightsister_sentry", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "nightsister_sentry", planetName = "dathomir", npcName = "" }
		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
			{ rewardType = "credits", amount = 800 }
		}
	},
	{
		missionType = "assassinate",
		primarySpawns =
		{
			{ npcTemplate = "nightsister_spell_weaver", planetName = "dathomir", npcName = "a Nightsister War-Party Leader" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "singing_mountain_clan_rancor_tamer", planetName = "dathomir", npcName = "a Singing Mountain Clan Scout" },
			{ npcTemplate = "nightsister_stalker", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "nightsister_stalker", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "nightsister_rancor_tamer", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "nightsister_rancor_tamer", planetName = "dathomir", npcName = "" }
		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
			{ rewardType = "credits", amount = 850 }
		}
	}
}

npcMapSingingMountainClan2 =
{
	{
		spawnData = { planetName = "dathomir", npcTemplate = "vhaunda", x = -22.3, z = 2, y = 5.05, direction = 5, cellID = 2665881, position = STAND },
		worldPosition = { x = 140.8, y = 4489.3 },
		npcNumber = 1,
		stfFile = "@static_npc/dathomir/vhaunda",
		missions = vhaunda_missions
	},
	{
		spawnData = { planetName = "dathomir", npcTemplate = "izaryx", x = -12, z = 2, y = -4, direction = -110, cellID = 2665882, position = STAND },
		worldPosition = { x = 152.5, y = 4482.3 },
		npcNumber = 2,
		stfFile = "@static_npc/dathomir/dathomir_singingmountainclanstronghold_izaryx",
		missions = izaryx_missions
	}
}

ThemeParkSingingMountainClan2 = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapSingingMountainClan2,
	className = "ThemeParkSingingMountainClan2",
	screenPlayState = "singing_mountain_clan2_theme_park",
	requiredFaction = "mtn_clan"
}

registerScreenPlay("ThemeParkSingingMountainClan2", true)

theme_park_singing_mountain_clan2_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkSingingMountainClan2
}
theme_park_singing_mountain_clan2_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkSingingMountainClan2
}