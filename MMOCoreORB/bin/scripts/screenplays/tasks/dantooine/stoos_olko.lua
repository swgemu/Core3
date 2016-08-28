stoos_olko_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "coer_clem", npcName = "Coer Clem" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "stoos_bandit", npcName = "a bandit" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/stoos_olko_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 5000 },
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "stoos_imperial_ensign", npcName = "Imperial Ensign" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "bounty_hunter_thug", npcName = "a Bounty Hunter" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/stoos_olko_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 10000 },
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "stoos_stormtrooper_squad_leader", npcName = "Stormtrooper Squad Leader" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "scout_trooper", npcName = "a Scout Trooper" },
				{ npcTemplate = "scout_trooper", npcName = "a Scout Trooper" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/stoos_olko_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 5000 },
				{ rewardType = "faction", faction = "imperial", amount = 100 },
			}
		},
	}

npcMapStoosOlko =
	{
		{
			spawnData = { npcTemplate = "stoos_olko", x = 5.4, z = 0.1, y = -3.6, direction = -110, cellID = 1365990, position = SIT },
			worldPosition = { x = -593, y = 2544 },
			npcNumber = 1,
			stfFile = "@static_npc/dantooine/dantooine_mining_outpost_stoos_olko",
			missions = stoos_olko_missions
		},
	}

StoosOlko = ThemeParkLogic:new {
	npcMap = npcMapStoosOlko,
	className = "StoosOlko",
	screenPlayState = "stoos_olko_quest",
	planetName = "dantooine",
	distance = 800,
}

registerScreenPlay("StoosOlko", true)

stoos_olko_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = StoosOlko
}
stoos_olko_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = StoosOlko
}
