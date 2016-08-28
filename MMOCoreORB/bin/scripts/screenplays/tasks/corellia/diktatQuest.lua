brantleeMissions =
{
	{ 
		missionType = "retrieve",
		primarySpawns = 
		{ 
			{ npcTemplate = "midgoss_dlabaninaph", npcName = "Midgoss D'labaninaph" }
		},
		secondarySpawns = 
		{
			{ npcTemplate = "carrion_spat", npcName = "a carrion spat" },
			{ npcTemplate = "carrion_spat", npcName = "a carrion spat" }		
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
			{ npcTemplate = "zoda_burb", npcName = "Zoda Burb" } 
		},
		secondarySpawns = 
		{
			{ npcTemplate = "dalyrake", npcName = "a dalyrake" },
			{ npcTemplate = "dalyrake", npcName = "a dalyrake" }		
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
			{ npcTemplate = "missy", npcName = "Missy" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "razor_cat", npcName = "a razor cat" }			
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
			{ npcTemplate = "windle_meeker", npcName = "Windle Meeker" } 
		},
		secondarySpawns = 
		{
			{ npcTemplate = "carrion_spat", npcName = "a carrion spat" },
			{ npcTemplate = "carrion_spat", npcName = "a carrion spat" }		
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
			{ npcTemplate = "merlyx_dolv", npcName = "Merlyx Dolv" } 
		},
		secondarySpawns = 
		{
			{ npcTemplate = "razor_cat", npcName = "a razor cat" }		
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
			{ npcTemplate = "dwynn_biuval", npcName = "Dwynn Biuval" } 
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
			{ npcTemplate = "lieutenant_mien_halloor", npcName = "Lt. Mien Halloor" }
		},
		secondarySpawns = 
		{
			{ npcTemplate = "razor_cat", npcName = "a razor cat" },
			{ npcTemplate = "razor_cat", npcName = "a razor cat" }	
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
			{ npcTemplate = "merlyx_dolv", npcName = "Merlyx Dolv" }  
		},
		secondarySpawns = 
		{
			{ npcTemplate = "mercenary_aggro", npcName = "a mercenary" },
			{ npcTemplate = "mercenary_aggro", npcName = "a mercenary" }	
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
			{ npcTemplate = "morgo_one_shot", npcName = "Morgo One-Shot" }
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
		spawnData = { npcTemplate = "brantlee_spondoon", x = -24.7, z = 1.3, y = -0.5,
			direction = 124, cellID = 1855463, position = STAND }, 
		worldPosition = { x = -234.0, y = -4570.0 },
		npcNumber = 1,   
		stfFile = "@static_npc/corellia/brantlee_spondoon", 
		missions = brantleeMissions
	},
	{ 
		spawnData = { npcTemplate = "daclif_gallamby", x = -35.6875, z = 1.29422,
			y = -1.70805, direction = 88.4786, cellID = 1855467, position = STAND }, 
		worldPosition = { x = -245.0, y = -4571.0 },
		npcNumber = 2,   
		stfFile = "@static_npc/corellia/daclif_gallamby", 
		missions = daclifMissions
	}
}

diktatQuest = ThemeParkLogic:new {
	npcMap = npcMapDiktat,
	className = "diktatQuest",
	screenPlayState = "diktatQuestState",
	planetName = "corellia",
	distance = 1000,
}

registerScreenPlay("diktatQuest", true)

diktatGiverHandler = mission_giver_conv_handler:new {
	themePark = diktatQuest
}

diktatTargetHandler = mission_target_conv_handler:new {
	themePark = diktatQuest
}
