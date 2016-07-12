vurlene_missions =
{
	{
		missionType = "deliver",
		primarySpawns =
		{
    --THIS NPC NEEDS TO HAVE A SPECIFIC DESIGNATED WAYPOINT...BUT WE NEED NEW WP LOGIC FIRST??
			{ npcTemplate = "theme_park_naboo_holy_man", planetName = "naboo", npcName = "Skub" }
		},
		secondarySpawns =
		{

		},
		--A FORUM POST AT BOTTOM OF THE ALLAKHAZAM GUIDE SAYS SOMETHING ABOUT "keeping the Algae FRESH" ??
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/vurlene_q1_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
			{ rewardType = "credits", amount = 75 },
			{ rewardType = "loot",  lootGroup = "theme_park_reward_smc_vurlene_stimb" }
		}
	},
	{
		missionType = "deliver",
		primarySpawns =
		{
			{ npcTemplate = "theme_park_singing_mountain_clan_arch_witch", planetName = "dathomir", npcName = "Selia" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/vurlene_q2_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
			{ rewardType = "credits", amount = 75 },
			{ rewardType = "loot",  lootGroup = "theme_park_reward_smc_vurlene_stimc" }
		}
	},
	{
		missionType = "confiscate",
		primarySpawns =
		{
			{ npcTemplate = "nightsister_ranger_quest", planetName = "dathomir", npcName = "a Nightsister Patrol Leader" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "nightsister_initiate", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "nightsister_initiate", planetName = "dathomir", npcName = "" }
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/vurlene_q3_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
			{ rewardType = "credits", amount = 100 },
			{ rewardType = "loot",  lootGroup = "theme_park_reward_smc_vurlene_stimd" }
		}
	}
}

aujante_klee_missions =
{
	{
		missionType = "escort",
		primarySpawns =
		{
			{ npcTemplate = "theme_park_singing_mountain_clan_dragoon", planetName = "dathomir", npcName = "Aldiae" }
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
			{ rewardType = "credits", amount = 200 }
		}
	},
	{
		missionType = "confiscate",
		primarySpawns =
		{
			{ npcTemplate = "nightsister_stalker_quest_smctp", planetName = "dathomir", npcName = "Vhuransa" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/aujante_klee_q2_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 450 },
			{ rewardType = "credits", amount = 500 }
		}
	},
	{
		missionType = "escort",
		primarySpawns =
		{
			{ npcTemplate = "theme_park_singing_mountain_clan_initiate", planetName = "dathomir", npcName = "Jhuryx" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "nightsister_stalker", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "nightsister_rancor_tamer", planetName = "dathomir", npcName = "" }
		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
			{ rewardType = "credits", amount = 300 }
		}
	},
	{
		missionType = "assassinate",
		primarySpawns =
		{
			{ npcTemplate = "nightsister_spell_weaver", planetName = "dathomir", npcName = "Morathax" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "nightsister_initiate", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "nightsister_initiate", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "nightsister_outcast", planetName = "dathomir", npcName = "" },
			{ npcTemplate = "nightsister_outcast", planetName = "dathomir", npcName = "" }
		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 410 },
			{ rewardType = "credits", amount = 500 }
		}
	}
}

npcMapSingingMountainClan3 =
{
	{
		spawnData = { planetName = "dathomir", npcTemplate = "vurlene", x = -12, z = 3, y = 9.5, direction = 72, cellID = 2665880, position = STAND },
		worldPosition = { x = 150.0, y = 4495.7 },
		npcNumber = 8,
		stfFile = "@static_npc/dathomir/vurlene",
		missions = vurlene_missions
	},
	{
		spawnData = { planetName = "dathomir", npcTemplate = "aujante_klee", x = 3, z = 3, y = -5.2, direction = 176, cellID = 2665884, position = STAND },
		worldPosition = { x = 167.5, y = 4483.9 },
		npcNumber = 16,
		stfFile = "@static_npc/dathomir/dathomir_singingmountainstronghold_aujante_klee",
		missions = aujante_klee_missions
	}
}

ThemeParkSingingMountainClan3 = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapSingingMountainClan3,
	className = "ThemeParkSingingMountainClan3",
	screenPlayState = "singing_mountain_clan3_theme_park",
	requiredFaction = "mtn_clan"
}

registerScreenPlay("ThemeParkSingingMountainClan3", true)

theme_park_singing_mountain_clan3_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkSingingMountainClan3
}
theme_park_singing_mountain_clan3_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkSingingMountainClan3
}