THEME_PARK_JABBA_BADGE = 105


reelo_missions =
{
   { 
		missionType = "assassinate", 
		primarySpawns = 
		{
			{ npcTemplate = "tusken_raider", planetName = "tatooine", npcName = "Tusken Leader" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "tusken_commoner", planetName = "tatooine", npcName = "Tusken Commoner" },
			{ npcTemplate = "tusken_commoner", planetName = "tatooine", npcName = "Tusken Commoner" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 50 } 
		}
	},
	   { 
		missionType = "assassinate", 
		primarySpawns = 
		{
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" }
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 150 } 
		}
	},
	   { 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_jabba_escort", planetName = "tatooine", npcName = "random" } 
		}, 
		secondarySpawns =
     	{
		    { npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
		    { npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "jabba_theme_park_reelo" } 
		}
	}
}

ree_yees_missions =
{
   {
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Sirad's Thug" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Sirad's Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Sirad's Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Sirad's Thug" }, 
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 250 } 
		}
	},
    {
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_jawa", planetName = "tatooine", npcName = "Jawa" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "jawa_henchman", planetName = "tatooine", npcName = "Jawa" },
			{ npcTemplate = "jawa_henchman", planetName = "tatooine", npcName = "Jawa" },
			{ npcTemplate = "jawa_henchman", planetName = "tatooine", npcName = "Jawa" }, 
		}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/component/item/quest_item/directional_sensor.iff", itemName = "Transponder" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 350 } 
		}
	},
		{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "sirad_far", planetName = "tatooine", npcName = "Sirad Far" } 
		}, 
		secondarySpawns = 
		{
		    { npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Sirad's Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Sirad's Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Sirad's Thug" }, 
		}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/component/item/quest_item/directional_sensor.iff", itemName = "Transponder" }
		}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "jabba_theme_park_ree_yees" } 
		}
	}
}

ephant_mon_missions =
{
    {
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "valarian_assassin", planetName = "tatooine", npcName = "Valarian Assassin" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
		    { npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" }, 
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 450 } 
		}
	},
	    {
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "valarian_courier", planetName = "tatooine", npcName = "Valarian Courier" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
		    { npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" }, 
		}, 
		itemSpawns =
		{
					{ itemTemplate = "object/tangible/loot/misc/ledger_s01.iff", itemName = "Ledger" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 550 },
		}
	},
	   {
		missionType = "deliver",
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_jabba_sirad_far", planetName = "tatooine", npcName = "Sirad Far" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{
		          { itemTemplate = "object/tangible/loot/misc/ledger_s01.iff", itemName = "Ledger" }
		}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "jabba_theme_park_ephant_mon"},
		}
	}
}

porcellus_missions =
{
    {
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_jabba_kaadu", planetName = "tatooine", npcName = "Kaadu" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "theme_park_jabba_kaadu", planetName = "tatooine", npcName = "Kaadu" },
			{ npcTemplate = "theme_park_jabba_kaadu", planetName = "tatooine", npcName = "Kaadu" },
		    { npcTemplate = "theme_park_jabba_kaadu", planetName = "tatooine", npcName = "Kaadu" },
			{ npcTemplate = "theme_park_jabba_kaadu", planetName = "tatooine", npcName = "Kaadu" }, 
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 650 } 
		}
	},
	    {
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_jabba_veterinarian", planetName = "tatooine", npcName = "Veterinarian" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "alkhara_bandit", planetName = "tatooine", npcName = "Alkhara Bandit" },
			{ npcTemplate = "alkhara_bandit", planetName = "tatooine", npcName = "Alkhara Bandit" },
		}, 
		itemSpawns = {
					{ itemTemplate = "object/tangible/loot/misc/damaged_datapad.iff", itemName = "A Datapad" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 650 } 
		}
	},
	    {
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "dewback", planetName = "tatooine", npcName = "Dewback" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "dewback", planetName = "tatooine", npcName = "Dewback" },
			{ npcTemplate = "dewback", planetName = "tatooine", npcName = "Dewback" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "jabba_theme_park_porcellus"} 
		}
	}
}

barada_missions =
{
    {
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_jabba_valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "weak_mercenary", planetName = "lok", npcName = "Weak Mercenary" },
			
		}, 
		itemSpawns = {
		         { itemTemplate = "object/tangible/loot/misc/key_electronic_s01.iff", itemName = "Code Cylinder" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 850 } 
		}
	},
		{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "tiem_rutnar", planetName = "tatooine", npcName = "Tiem Rutnar" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/loot/misc/key_electronic_s01.iff", itemName = "Code Cylinder" }
		},	
			rewards = 
		{ 
			{ rewardType = "credits", amount = 950 } 
		}
	},
		{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "jabba_theme_park_barada"} 
		}
	}
}

bib_missions =
{
   {
   		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "romo_vax", planetName = "tatooine", npcName = "Romo Vax" } 
		}, 
		secondarySpawns =
     	{
		    { npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
		    { npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1050 }
		}
	},
	    {
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "sennex_slaver", planetName = "tatooine", npcName = "Hizram Riean" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "alkhara_bandit", planetName = "tatooine", npcName = "A Thug" },
			{ npcTemplate = "alkhara_bandit", planetName = "tatooine", npcName = "A Thug" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1150 } 
		}
	},
	    { 
		missionType = "retrieve", 
		primarySpawns = 
		{ 
			{ npcTemplate = "naeton_baykurr", planetName = "tatooine", npcName = "Naeton Baykurr" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/loot/misc/briefcase_s01.iff", itemName = "Locked Briefcase" }
		},	
			rewards = 
		{ 
			{ rewardType = "credits", amount = 1250 } 
		}
	},
		{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "slaver", planetName = "tatooine", npcName = "Slaver Leader" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "slaver", planetName = "tatooine", npcName = "Slaver" },
			{ npcTemplate = "slaver", planetName = "tatooine", npcName = "Slaver" },
			{ npcTemplate = "slaver", planetName = "tatooine", npcName = "Slaver" },
			
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "jabba_theme_park_bib"} 
		}
	}
}	

g5po_missions =
{
   {
   		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "scrib_leras", planetName = "tatooine", npcName = "Scrib Leras" } 
		}, 
		secondarySpawns = 
		{
		    { npcTemplate = "alkhara_bandit", planetName = "tatooine", npcName = "A Thug" },
			{ npcTemplate = "alkhara_bandit", planetName = "tatooine", npcName = "A Thug" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1350 }
					}
	},
		{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Interrogator" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "A Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "A Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "A Thug" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1450 } 
		}
	},
		{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Courier" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "A Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "A Thug" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1650 } 
		}
	},
	   {
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Thug Leader" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "A Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "A Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "A Thug" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1750 } 
		}
	},
		{ 
		missionType = "retrieve", 
		primarySpawns = 
		{ 
			{ npcTemplate = "belshu_dadar", planetName = "tatooine", npcName = "Belshu Dadar" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/component/item/quest_item/directional_sensor.iff", itemName = "Lady Valarian's Part" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1850 }
		}
	},
		{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Punk" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "A Thug" },
			{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "A Thug" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1950 } 
		}
	},
		{ 
		missionType = "retrieve", 
		primarySpawns = 
		{ 
			{ npcTemplate = "sliv_jurek", planetName = "tatooine", npcName = "Sliv Jurek" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/loot/misc/key_electronic_s01.iff", itemName = "Jabba's Key" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 2050 }
		}
	},
			{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_jabba_valarian_thug_02", planetName = "tatooine", npcName = "Valarian Thug" } 
		}, 
		secondarySpawns = 
		{
		{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
		{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
		{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
		}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/weapon/melee/sword/sword_rantok.iff", itemName = "Rantok" }
		}, 
		rewards = 
		{ 
			{ rewardType = "loot", lootGroup = "jabba_theme_park_g5p0"},
			{ rewardType = "badge", badge = THEME_PARK_JABBA_BADGE }
		} 
	},
}

npcMapJabba = 
{ 
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "reelo_baruk", x = -2, z = 0.199999, y = 113.01, direction = 53.9956, cellID = 1177466, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@theme_park_jabba/reelo_baruk",
		missions = reelo_missions
	},
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "ree_yees", x = 5.97, z = 0.299998, y = 116.1, direction = 248.813, cellID = 1177466, position = STAND }, 
		npcNumber = 2,   
		stfFile = "@theme_park_jabba/ree_yees",
		missions = ree_yees_missions
	},
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "ephant_mon", x = -6, z = 5.85, y = 84, direction = 277.481, cellID = 1177469, position = STAND }, 
		npcNumber = 4,   
		stfFile = "@theme_park_jabba/ephant_mon",
		missions = ephant_mon_missions
	},
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "porcellus", x = -43, z = 3, y = 64, direction = 306.623, cellID = 1177477, position = STAND }, 
		npcNumber = 8,   
		stfFile = "@theme_park_jabba/porcellus",
		missions = porcellus_missions
	},
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "barada", x = 30.57, z = 0.199999, y = -1.05, direction = 164.173, cellID = 1177499, position = STAND }, 
		npcNumber = 16,   
		stfFile = "@theme_park_jabba/barada",
		missions = barada_missions
	},
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "bib_fortuna", x = -12.09, z = 2, y = 49.41, direction = 176.373, cellID = 1177487, position = STAND }, 
		npcNumber = 32,   
		stfFile = "@theme_park_jabba/bib_fortuna",
		missions = bib_missions
	},
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "g_5po", x = -15.07, z = 2, y = 45.9, direction = 119.771, cellID = 1177487, position = STAND }, 
		npcNumber = 64,   
		stfFile = "@theme_park_jabba/g5po",
		missions = g5po_missions
	}
}

ThemeParkJabba = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapJabba,
	className = "ThemeParkJabba",
	screenPlayState = "jabba_theme_park",
	missionDescriptionStf = "@theme_park_jabba/quest_details:jabbas_palace_",
	missionCompletionMessageStf = "@theme_park/messages:jabba_completion_message"
}

registerScreenPlay("ThemeParkJabba", true)

theme_park_jabba_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkJabba
}
theme_park_jabba_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkJabba
}