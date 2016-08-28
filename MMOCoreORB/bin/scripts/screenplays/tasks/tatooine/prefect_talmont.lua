wilhalm_skrim_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "dak_linser", npcName = "Dak Linser" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/wilhalm_skrim_q1_needed.iff", itemName = "Skrim's Datadisc" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 2000 },
				{ rewardType = "faction", faction = "imperial", amount = 100 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "nethlekvaa", npcName = "Nethlek'Vaa" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "rebel_scout", npcName = "a Rebel scout" },
				{ npcTemplate = "rebel_scout", npcName = "a Rebel scout" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/wilhalm_skrim_q2_needed.iff", itemName = "Datadisc" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 5000 },
				{ rewardType = "faction", faction = "imperial", amount = 200 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "ananda_dwyce", npcName = "Ananda Dwyce" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "rebel_scout", npcName = "a Rebel scout" },
				{ npcTemplate = "rebel_scout", npcName = "a Rebel scout" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 7000 },
				{ rewardType = "faction", faction = "imperial", amount = 400 }
			}
		}
	}

prefect_talmont_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "akkar_plint", npcName = "Akkar Plint" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 },
				{ rewardType = "faction", faction = "imperial", amount = 50 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "gohn_bimmin", npcName = "Gohn Bimmin" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 2000 },
				{ rewardType = "faction", faction = "imperial", amount = 100 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "tough_wookiee_brawler", npcName = "Snrrrlagga" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 4000 },
				{ rewardType = "faction", faction = "imperial", amount = 150 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "nwilla_tharlyat", npcName = "Nwilla Thar'Lyat" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 6000 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "klaua_jik", npcName = "Klaua Jik" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 8000 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "harbo_linn", npcName = "Harbo Linn" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 10000 },
			}
		}
	}

npcMapPrefectTalmont =
	{
		{
			spawnData = { npcTemplate = "wilhalm_skrim", x = 28.89, z = 1.3, y = -5.98, direction = 40, cellID = 926482, position = STAND },
			worldPosition = { x = -1182, y = -3609 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/wilhalm_skrim",
			missions = wilhalm_skrim_missions
		},
		{
			spawnData = { npcTemplate = "prefect_talmont", x = -1.9, z = 3, y = -10, direction = 180, cellID = 926475, position = STAND },
			worldPosition = { x = -1166, y = -3582 },
			npcNumber = 2,
			stfFile = "@static_npc/tatooine/prefect_talmont",
			missions = prefect_talmont_missions
		},
	}

PrefectTalmont = ThemeParkLogic:new {
	npcMap = npcMapPrefectTalmont,
	className = "PrefectTalmont",
	screenPlayState = "prefect_talmont_quest",
	planetName = "tatooine",
	distance = 800,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("PrefectTalmont", true)

prefect_talmont_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = PrefectTalmont
}
prefect_talmont_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = PrefectTalmont
}