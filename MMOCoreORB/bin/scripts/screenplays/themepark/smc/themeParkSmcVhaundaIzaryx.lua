vhaunda_missions =
{
	{
		missionType = "confiscate",
		faction = FACTIONREBEL,
		primarySpawns =
		{
			{ npcTemplate = "stormtrooper_squad_leader_quest", npcName = "LX-613" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "stormtrooper", npcName = "" },
			{ npcTemplate = "stormtrooper", npcName = "" },
			{ npcTemplate = "stormtrooper", npcName = "" }
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
			{ npcTemplate = "singing_mountain_clan_arch_witch", npcName = "Peila" }
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
			{ npcTemplate = "theme_park_singing_mountain_clan_rancor_tamer", npcName = "a Singing Mountain Clan Scout" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "nightsister_rancor_tamer", npcName = "" },
			{ npcTemplate = "nightsister_rancor_tamer", npcName = "" },
			{ npcTemplate = "nightsister_sentry", npcName = "" }
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
			{ npcTemplate = "nightsister_spell_weaver", npcName = "a Nightsister War-Party Leader" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "singing_mountain_clan_rancor_tamer", npcName = "a Singing Mountain Clan Scout" },
			{ npcTemplate = "nightsister_stalker", npcName = "" },
			{ npcTemplate = "nightsister_stalker", npcName = "" },
			{ npcTemplate = "nightsister_rancor_tamer", npcName = "" },
			{ npcTemplate = "nightsister_rancor_tamer", npcName = "" }
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

npcMapSmcVhaundaIzaryx =
{
	{
		spawnData = { npcTemplate = "vhaunda", x = -22.3, z = 2, y = 5.05, direction = 5, cellID = 2665881, position = STAND },
		worldPosition = { x = 140.8, y = 4489.3 },
		npcNumber = 1,
		stfFile = "@static_npc/dathomir/vhaunda",
		missions = vhaunda_missions
	},
	{
		spawnData = { npcTemplate = "izaryx", x = -12, z = 2, y = -4, direction = -110, cellID = 2665882, position = STAND },
		worldPosition = { x = 152.5, y = 4482.3 },
		npcNumber = 2,
		stfFile = "@static_npc/dathomir/dathomir_singingmountainclanstronghold_izaryx",
		missions = izaryx_missions
	},
	{
		spawnData = { npcTemplate = "theme_park_smc_rancor_pygmy_shando", x = -12.6, z = 2.0, y = -2.0, direction = -125, cellID = 2665882, position = STAND },
		npcNumber = -1,
		stfFile = "",
		missions = {}
	},
	{
		spawnData = { npcTemplate = "theme_park_smc_rancor_pygmy_maufel", x = -11.5, z = 2.0, y = -5.7, direction = -99, cellID = 2665882, position = STAND },
		npcNumber = -1,
		stfFile = "",
		missions = {}
	}
}

ThemeParkSmcVhaundaIzaryx = ThemeParkLogic:new {
	npcMap = npcMapSmcVhaundaIzaryx,
	className = "ThemeParkSmcVhaundaIzaryx",
	screenPlayState = "smc_vhaunda_izaryx_theme_park",
	requiredFaction = "mtn_clan",
	planetName = "dathomir"
}

registerScreenPlay("ThemeParkSmcVhaundaIzaryx", true)

theme_park_smc_vhaunda_izaryx_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkSmcVhaundaIzaryx
}
theme_park_smc_vhaunda_izaryx_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkSmcVhaundaIzaryx
}