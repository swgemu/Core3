irenezMissions =
{
	{ 
		missionType = "escort",
		primarySpawns = 
		{ 
			{ npcTemplate = "tessa_wylden", planetName = "corellia", npcName = "Tessa Wylden" }
		},
		secondarySpawns = 
		{
			{ npcTemplate = "black_sun_guard_weak", planetName = "corellia", npcName = "a black sun guard" },
			{ npcTemplate = "black_sun_guard_weak", planetName = "corellia", npcName = "a black sun guard" }		
		},
		itemSpawns = {},
		rewards = {}
	},
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "skazz", planetName = "corellia", npcName = "Skazz" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {},
		rewards = 
		{ 
			{ rewardType = "credits", amount = 200 }
		}
	}
}

garmMissions =
{
	{ 
		missionType = "escort",
		faction = FACTIONREBEL,
		primarySpawns = 
		{ 
			{ npcTemplate = "hlaano_dunlix", planetName = "corellia", npcName = "Hlaano Dunlix" }
		},
		secondarySpawns = {},
		itemSpawns = {},
		rewards = 
		{	
			{ rewardType = "credits", amount = 125 }
		}
	},
	{ 
		missionType = "confiscate",
		faction = FACTIONREBEL,
		primarySpawns = 
		{ 
			{ npcTemplate = "drillen_foyle", planetName = "corellia", npcName = "Drillen Foyle" }
		},
		secondarySpawns = {
			{ npcTemplate = "dark_trooper", planetName = "corellia", npcName = "an Imperial stormtrooper" },
			{ npcTemplate = "crackdown_elite_dark_trooper_covert", planetName = "corellia", npcName = "an Imperial stormtrooper" },
			{ npcTemplate = "crackdown_elite_dark_trooper_covert", planetName = "corellia", npcName = "an Imperial stormtrooper" }
		},
		itemSpawns =
		{	
			{ itemTemplate = "object/tangible/mission/quest_item/garm_beliblis_q2_needed.iff",
				itemName = "Datadisc" }
		},
		rewards = 
		{	
			{ rewardType = "credits", amount = 250 }
		}
	},
	{
		missionType = "assassinate",
		faction = FACTIONREBEL,
		primarySpawns = 
		{ 
			{ npcTemplate = "egan_garrud", planetName = "corellia", npcName = "Captain Egan Garrud" }
		},
		secondarySpawns = {},
		itemSpawns = {},
		rewards = 
		{	
			{ rewardType = "credits", amount = 500 }
		}
	},
	{
		missionType = "escort",
		faction = FACTIONREBEL,
		primarySpawns = 
		{ 
			{ npcTemplate = "fadulk_dikeer", planetName = "corellia", npcName = "Fadulk Di'keer" }
		},
		secondarySpawns = {			
			{ npcTemplate = "dark_trooper", planetName = "corellia", npcName = "an Imperial stormtrooper" },
			{ npcTemplate = "dark_trooper", planetName = "corellia", npcName = "an Imperial stormtrooper" },
			{ npcTemplate = "stormtrooper_covert", planetName = "corellia", npcName = "an Imperial stormtrooper" }
		},
		itemSpawns = {},
		rewards = 
		{	
			{ rewardType = "credits", amount = 750 }
		}
	},
	{
		missionType = "assassinate",
		faction = FACTIONREBEL,
		primarySpawns = 
		{ 
			{ npcTemplate = "kalia_kulmina", planetName = "corellia", npcName = "Kalia Kulmina" }
		},
		secondarySpawns = {},
		itemSpawns = {},
		rewards = 
		{	
			{ rewardType = "credits", amount = 1000 }
		}
	},
	{
		missionType = "assassinate",
		faction = FACTIONREBEL,
		primarySpawns = {
			{ npcTemplate = "dark_trooper", planetName = "corellia", npcName = "an Imperial stormtrooper" },
			{ npcTemplate = "dark_trooper", planetName = "corellia", npcName = "an Imperial stormtrooper" },
			{ npcTemplate = "dark_trooper", planetName = "corellia", npcName = "an Imperial stormtrooper" },
			{ npcTemplate = "stormtrooper_brawler", planetName = "corellia", npcName = "an Imperial stormtrooper" },
			{ npcTemplate = "stormtrooper_brawler", planetName = "corellia", npcName = "an Imperial stormtrooper" },
			{ npcTemplate = "stormtrooper_covert", planetName = "corellia", npcName = "an Imperial stormtrooper" },
			{ npcTemplate = "stormtrooper_covert", planetName = "corellia", npcName = "an Imperial stormtrooper" }
		},
		secondarySpawns = {},
		itemSpawns = {},
		rewards = 
		{	
			{ rewardType = "credits", amount = 1000 }
		}
	}
}

npcMapGarm = 
{ 
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "irenez", x = -24.7, z = 1.3, y = -5.2,
			direction = 40.0, cellID = 1855463, position = STAND }, 
		worldPosition = { x = -234.0, y = -4575.0 },
		npcNumber = 1,   
		stfFile = "@static_npc/corellia/irenez", 
		missions = irenezMissions
	},
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "garm_bel_iblis", x = -33.9, z = 1.3, y = -7.7,
			direction = 40.0, cellID = 1855467, position = STAND }, 
		worldPosition = { x = -243.9, y = -4577.7 },
		npcNumber = 2,   
		stfFile = "@static_npc/corellia/garm_bel_iblis", 
		missions = garmMissions
	}
}

garmQuest = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapGarm,
	permissionMap = {},
	className = "garmQuest",
	screenPlayState = "garmQuestState",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = ""
	
}

registerScreenPlay("garmQuest", true)

garmGiverHandler = mission_giver_conv_handler:new {
	themePark = garmQuest
}

garmTargetHandler = mission_target_conv_handler:new {
	themePark = garmQuest
}
