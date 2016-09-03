vurlene_missions =
{
	{
		missionType = "retrieve",
		planetName = "naboo",
		staticLoc = { {x = -2096, y = -5401} },
		primarySpawns =
		{
			{ npcTemplate = "theme_park_naboo_holy_man", npcName = "Skub" }
		},
		secondarySpawns =
		{},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/vurlene_q1_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
			{ rewardType = "credits", amount = 75 },
			{ rewardType = "loot",  lootGroup = "theme_park_reward_smc_vurlene_stims" }
		}
	},
	{
		missionType = "deliver",
		planetName = "dathomir",
		primarySpawns =
		{
			{ npcTemplate = "theme_park_singing_mountain_clan_arch_witch", npcName = "Selia" }
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
			{ rewardType = "loot",  lootGroup = "theme_park_reward_smc_vurlene_stims" }
		}
	},
	{
		missionType = "confiscate",
		planetName = "dathomir",
		primarySpawns =
		{
			{ npcTemplate = "nightsister_ranger_quest", npcName = "a Nightsister Patrol Leader" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "nightsister_initiate", npcName = "" },
			{ npcTemplate = "nightsister_initiate", npcName = "" }
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/vurlene_q3_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "faction", faction = "mtn_clan", amount = 10 },
			{ rewardType = "credits", amount = 100 },
			{ rewardType = "loot",  lootGroup = "theme_park_reward_smc_vurlene_stims" }
		}
	}
}

aujante_klee_missions =
{
	{
		missionType = "escort",
		planetName = "dathomir",
		primarySpawns =
		{
			{ npcTemplate = "theme_park_singing_mountain_clan_dragoon", npcName = "Aldiae" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "nightsister_outcast", npcName = "" }
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
		planetName = "dathomir",
		primarySpawns =
		{
			{ npcTemplate = "nightsister_stalker_quest_smctp", npcName = "Vhuransa" }
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
		planetName = "dathomir",
		primarySpawns =
		{
			{ npcTemplate = "theme_park_singing_mountain_clan_initiate", npcName = "Jhuryx" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "nightsister_stalker", npcName = "" },
			{ npcTemplate = "nightsister_rancor_tamer", npcName = "" }
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
		planetName = "dathomir",
		primarySpawns =
		{
			{ npcTemplate = "nightsister_spell_weaver", npcName = "Morathax" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "nightsister_initiate", npcName = "" },
			{ npcTemplate = "nightsister_initiate", npcName = "" },
			{ npcTemplate = "nightsister_outcast", npcName = "" },
			{ npcTemplate = "nightsister_outcast", npcName = "" }
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

npcMapSmcVurleneAujante =
{
	{
		spawnData = { planetName = "dathomir", npcTemplate = "vurlene", x = -12, z = 3, y = 9.5, direction = 72, cellID = 2665880, position = STAND },
		worldPosition = { x = 150.0, y = 4495.7 },
		npcNumber = 1,
		stfFile = "@static_npc/dathomir/vurlene",
		missions = vurlene_missions
	},
	{
		spawnData = { planetName = "dathomir", npcTemplate = "aujante_klee", x = 3, z = 3, y = -5.2, direction = 176, cellID = 2665884, position = STAND },
		worldPosition = { x = 167.5, y = 4483.9 },
		npcNumber = 2,
		stfFile = "@static_npc/dathomir/dathomir_singingmountainstronghold_aujante_klee",
		missions = aujante_klee_missions
	}
}

ThemeParkSmcVurleneAujante = ThemeParkLogic:new {
	npcMap = npcMapSmcVurleneAujante,
	className = "ThemeParkSmcVurleneAujante",
	screenPlayState = "smc_vurlene_aujante_theme_park",
	requiredFaction = "mtn_clan",
	requiredPlanets = { "dathomir", "naboo" },
}

registerScreenPlay("ThemeParkSmcVurleneAujante", true)

theme_park_smc_vurlene_aujante_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkSmcVurleneAujante
}
theme_park_smc_vurlene_aujante_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkSmcVurleneAujante
}
