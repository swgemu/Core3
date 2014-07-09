brantleeMissions =
{
	{ 
		missionType = "retrieve",
		primarySpawns = 
		{ 
			{ npcTemplate = "midgoss_dlabaninaph", planetName = "corellia", npcName = "Midgoss D'labaninaph" }
		},
		secondarySpawns = 
		{
			{ npcTemplate = "carrion_spat", planetName = "corellia", npcName = "a carrion spat" },
			{ npcTemplate = "carrion_spat", planetName = "corellia", npcName = "a carrion spat" }		
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/brantlee_spondoon_q1_needed.iff",
				itemName = "Devaronian Fur Glosser" }
		},
		rewards = 
		{
			{ rewardType = "credits", amount = 50 }
		}
	},
	{ 
		missionType = "retrieve",
		primarySpawns = 
		{ 
			{ npcTemplate = "zoda_burb", planetName = "corellia", npcName = "Zoda Burb" } 
		},
		secondarySpawns = 
		{
			{ npcTemplate = "dalyrake", planetName = "corellia", npcName = "a dalyrake" },
			{ npcTemplate = "dalyrake", planetName = "corellia", npcName = "a dalyrake" }		
		},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/brantlee_spondoon_q2_needed.iff",
				itemName = "Neonian Red Cheese" }
		},
		rewards = 
		{
			{ rewardType = "credits", amount = 100 }
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "missy", planetName = "corellia", npcName = "Missy" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "razor_cat", planetName = "corellia", npcName = "a razor cat" }			
		},
		rewards = 
		{
			{ rewardType = "credits", amount = 300 }
		}
	}
}

daclifMissions =
{
	{ 
		missionType = "retrieve",
		primarySpawns = 
		{
			{ npcTemplate = "windle_meeker", planetName = "corellia", npcName = "Windle Meeker" } 
		},
		secondarySpawns = 
		{
			{ npcTemplate = "carrion_spat", planetName = "corellia", npcName = "a carrion spat" },
			{ npcTemplate = "carrion_spat", planetName = "corellia", npcName = "a carrion spat" }		
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/daclif_gallamby_q1_needed.iff",
				itemName = "Bonadan Shipping Order" }
		},
		rewards = 
		{
			{ rewardType = "credits", amount = 50 }
		}
	},
	{ 
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "merlyx_dolv", planetName = "corellia", npcName = "Merlyx Dolv" } 
		},
		secondarySpawns = 
		{
			{ npcTemplate = "razor_cat", planetName = "corellia", npcName = "a razor cat" }		
		},
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/daclif_gallamby_q2_needed.iff",
				itemName = "Approved Bonadan Order" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 100 }
		}
	},
	{ 
		missionType = "retrieve",
		primarySpawns =
		{ 
			{ npcTemplate = "dwynn_biuval", planetName = "corellia", npcName = "Dwynn Biuval" } 
		},
		secondarySpawns = { },
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/daclif_gallamby_q3_needed.iff",
				itemName = "Donation to Diktat's Charity" }
		},
		rewards = 
		{
			{ rewardType = "credits", amount = 200 }
		}
	},
	{ 
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "lieutenant_mien_halloor", planetName = "corellia", npcName = "Lt. Mien Halloor" }
		},
		secondarySpawns = 
		{
			{ npcTemplate = "razor_cat", planetName = "corellia", npcName = "a razor cat" },
			{ npcTemplate = "razor_cat", planetName = "corellia", npcName = "a razor cat" }	
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/daclif_gallamby_q4_needed.iff",
				itemName = "Customs Charity Donation" }
		},
		rewards = 
		{
			{ rewardType = "credits", amount = 250 }
		}
	},
	{ 
		missionType = "escort",
		primarySpawns = 
		{ 
			{ npcTemplate = "merlyx_dolv", planetName = "corellia", npcName = "Merlyx Dolv" }  
		},
		secondarySpawns = 
		{
			{ npcTemplate = "mercenary_aggro", planetName = "corellia", npcName = "a mercenary" },
			{ npcTemplate = "mercenary_aggro", planetName = "corellia", npcName = "a mercenary" }	
		},
		rewards = 
		{
			{ rewardType = "credits", amount = 400 }
		}
	},
	{ 
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "morgo_one_shot", planetName = "corellia", npcName = "Morgo One-Shot" }
		},
		secondarySpawns = { },
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/daclif_gallamby_q6_needed.iff",
				itemName = "Orders for a Gangster" }
		},
		rewards = 
		{
			{ rewardType = "credits", amount = 750 }
		}
	}
}

npcMapDiktat = 
{ 
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "brantlee_spondoon", x = -24.7, z = 1.3, y = -0.5,
			direction = 124, cellID = 1855463, position = STAND }, 
		worldPosition = { x = -234.0, y = -4570.0 },
		npcNumber = 1,   
		stfFile = "@static_npc/corellia/brantlee_spondoon", 
		missions = brantleeMissions
	},
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "daclif_gallamby", x = -35.6875, z = 1.29422,
			y = -1.70805, direction = 88.4786, cellID = 1855467, position = STAND }, 
		worldPosition = { x = -245.0, y = -4571.0 },
		npcNumber = 2,   
		stfFile = "@static_npc/corellia/daclif_gallamby", 
		missions = daclifMissions
	}
}

diktatQuest = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapDiktat,
	permissionMap = {},
	className = "diktatQuest",
	screenPlayState = "diktatQuestState",
	distance = 1000,
}

registerScreenPlay("diktatQuest", true)

diktatGiverHandler = mission_giver_conv_handler:new {
	themePark = diktatQuest
}

diktatTargetHandler = mission_target_conv_handler:new {
	themePark = diktatQuest
}
