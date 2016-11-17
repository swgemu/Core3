mozo_bondog_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "mozo_escaped_tkm", npcName = "Escaped Prisoner" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nightsister_rancor_tamer", npcName = "" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
				{ rewardType = "faction", faction = "imperial", amount = 10 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "mozo_mercenary_warlord", npcName = "" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/mozo_bondog_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 150 },
				{ rewardType = "faction", faction = "imperial", amount = 10 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "janta_clan_leader", npcName = "" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 },
				{ rewardType = "faction", faction = "imperial", amount = 10 },
			}
		},
	}

dolac_legasi_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "dolac_escaped_prisoner", npcName = "Escaped Prisoner" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 350 },
				{ rewardType = "faction", faction = "imperial", amount = 10 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "dolac_dark_jedi_knight", npcName = "" }
			},
			secondarySpawns = {
				{ npcTemplate = "nightsister_protector", npcName = "" },
				{ npcTemplate = "nightsister_protector", npcName = "" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/dolac_legasi_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 450 },
				{ rewardType = "faction", faction = "imperial", amount = 10 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "dolac_dark_jedi_master", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "nightsister_spell_weaver", npcName = "" },
				{ npcTemplate = "nightsister_protector", npcName = "" },
				{ npcTemplate = "nightsister_protector", npcName = "" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1800 },
				{ rewardType = "faction", faction = "imperial", amount = 30 },
			}
		},
	}

npcMapDolacLegasi =
	{
		{
			spawnData = { npcTemplate = "mozo_bondog", x = -6313, z = 128, y = 734, direction = -91, cellID = 0, position = STAND },
			worldPosition = { x = -6313, y = 734 },
			npcNumber = 1,
			stfFile = "@static_npc/dathomir/dathomir_imperialprison_mozo_bondog",
			missions = mozo_bondog_missions
		},
		{
			spawnData = { npcTemplate = "dolac_legasi", x = -3.9, z = 0.1, y = -3.8, direction = 85, cellID = 5335777, position = STAND },
			worldPosition = { x = -6304, y = 748 },
			npcNumber = 2,
			stfFile = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi",
			missions = dolac_legasi_missions
		}
	}

DolacLegasi = ThemeParkLogic:new {
	npcMap = npcMapDolacLegasi,
	className = "DolacLegasi",
	screenPlayState = "dolac_legasi_quest",
	planetName = "dathomir",
	distance = 1000,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("DolacLegasi", true)

dolac_legasi_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = DolacLegasi
}
dolac_legasi_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = DolacLegasi
}
