irenez_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "tessa_wylden", planetName = "corellia", npcName = "Tessa Wylden" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "assassin", planetName = "corellia", npcName = "Skazz" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns = 
			{
				{ npcTemplate = "tough_thug_male_rodian", planetName = "corellia", npcName = "a thug" },
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" },
				{ npcTemplate = "thug", planetName = "corellia", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 500 }
			}
		}
	}

garm_bel_iblis_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "hlaano_dunlix", planetName = "corellia", npcName = "Hlaano Dunlix" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 125 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "drillen_foyle", planetName = "corellia", npcName = "Drillen Foyle" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "a Stormtrooper" },
				{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "a Stormtrooper" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/garm_beliblis_q2_needed.iff", itemName = "Datadisc" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 250 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "imperial_army_captain", planetName = "corellia", npcName = "Captain Egan Garrud" } -- 6k ham imp captain
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 500 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "fadulk_dikeer", planetName = "corellia", npcName = "Fadulk Di'keer" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "a Stormtrooper" },
				{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "a Stormtrooper" },
				{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "a Stormtrooper" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 750 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "kalia_kulmina", planetName = "corellia", npcName = "Kalia Kulmina" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "stormtrooper_groupleader", planetName = "corellia", npcName = "an Imperial Stormtrooper Commander" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "storm_commando", planetName = "corellia", npcName = "an Imperial storm commando" },
				{ npcTemplate = "storm_commando", planetName = "corellia", npcName = "an Imperial storm commando" },
				{ npcTemplate = "dark_trooper", planetName = "corellia", npcName = "a Dark Trooper" },
				{ npcTemplate = "dark_trooper", planetName = "corellia", npcName = "a Dark Trooper" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1500 }
			}
		}
	}

npcMapGarmBelIblis =
	{
		{
			spawnData = { planetName = "corellia", npcTemplate = "garm_bel_iblis", x = -33.9, z = 1.3, y = -7.7, direction = 40.0, cellID = 1855467, position = STAND },
			worldPosition = { x = -243.9, y = -4577.7 },
			npcNumber = 2,
			stfFile = "@static_npc/corellia/garm_bel_iblis",
			faction = FACTIONREBEL,
			missions = garm_bel_iblis_missions
		},
		{
			spawnData = { planetName = "corellia", npcTemplate = "irenez", x = -24.7, z = 1.3, y = -5.2, direction = 40.0, cellID = 1855463, position = STAND },
			worldPosition = { x = -234.0, y = -4575.0 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/irenez",
			missions = irenez_missions
		}

	}

GarmBelIblis = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapGarmBelIblis,
	className = "GarmBelIblis",
	screenPlayState = "garm_bel_iblis_quest",
	distance = 800
}

registerScreenPlay("GarmBelIblis", true)

garm_bel_iblis_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = GarmBelIblis
}

garm_bel_iblis_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = GarmBelIblis
}