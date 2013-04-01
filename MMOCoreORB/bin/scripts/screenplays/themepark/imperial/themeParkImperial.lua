THEME_PARK_IMPERIAL_BADGE = 106


kaja_orzee_missions =
{
	{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "random" } 
		}, 
		secondarySpawns =
     		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 75 } 
		}
	},
	   { 
		missionType = "assassinate", 
		primarySpawns = 
		{
			{ npcTemplate = "rebel_corporal", planetName = "naboo", npcName = "a Rebel Sympathizer" }
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "rebel_corporal", planetName = "naboo", npcName = "a Rebel Corporal" },
			{ npcTemplate = "rebel_corporal", planetName = "naboo", npcName = "a Rebel Corporal" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 150 } 
		}
	},

	   { 
		missionType = "assassinate", 
		primarySpawns = 
		{
			{ npcTemplate = "skaak_tipper_crook", planetName = "naboo", npcName = "Assassin" }
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "rebel_corporal", planetName = "naboo", npcName = "a Rebel Specialist" },
			{ npcTemplate = "rebel_corporal", planetName = "naboo", npcName = "a Rebel Specialist" },
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 225 } 
		}
	},

	   { 
		missionType = "assassinate", 
		primarySpawns = 
		{
			{ npcTemplate = "skaak_tipper_crook", planetName = "naboo", npcName = "a Droid Programmer" },
			{ npcTemplate = "skaak_tipper_crook", planetName = "naboo", npcName = "a Droid Programmer" }
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "rebel_corporal", planetName = "naboo", npcName = "a Rebel Specialist" },
			{ npcTemplate = "rebel_corporal", planetName = "naboo", npcName = "a Rebel Specialist" },
			{ npcTemplate = "rebel_corporal", planetName = "naboo", npcName = "a Rebel Specialist" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 300 } 
		}
	},
	   { 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort_droid", planetName = "naboo", npcName = "random" } 
		}, 
		secondarySpawns =
     		{

		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "imperial", amount = 75 },
			{ rewardType = "loot", lootGroup = "theme_park_reward_imperial_kaja"} 
		}
	}
}

loam_hedge_missions =
{
	{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "random" } 
		}, 
		secondarySpawns =
     		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 375 } 
		}
	},

		{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "random" } 
		}, 
		secondarySpawns =
     		{
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
			{ npcTemplate = "skaak_tipper_crook", planetName = "naboo", npcName = "a Slicer" }
		}, 
		secondarySpawns = 
		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 300 } 
		}
	},

	   { 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "random" } 
		}, 
		secondarySpawns =
     		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "imperial", amount = 125 },
			{ rewardType = "loot", lootGroup = "theme_park_reward_imperial_hedge"}
		}
	}
}

lord_hethrir_missions =
{
	   { 
		missionType = "assassinate", 
		primarySpawns = 
		{
			{ npcTemplate = "skaak_tipper_crook", planetName = "naboo", npcName = "random" }
		}, 
		secondarySpawns = 
		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 600 } 
		}
	  },

	   { 
		missionType = "assassinate", 
		primarySpawns = 
		{
			{ npcTemplate = "skaak_tipper_crook", planetName = "naboo", npcName = "random" }
		}, 
		secondarySpawns = 
		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 675 } 
		}
	  },
	   { 
		missionType = "assassinate", 
		primarySpawns = 
		{
			{ npcTemplate = "skaak_tipper_crook", planetName = "naboo", npcName = "random" }
		}, 
		secondarySpawns = 
		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 750 } 
		}
	},

	{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "random" } 
		}, 
		secondarySpawns = 
		{
		}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/loot/misc/damaged_datapad.iff", itemName = "Holodisc" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 825 }  
		}
	},
	{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "random" } 
		}, 
		secondarySpawns =
     		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "imperial", amount = 175 },
			{ rewardType = "loot", lootGroup = "theme_park_reward_imperial_hethrir"}
		}
	},
}

thrown_missions =
{
	{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "Captain Dolman" } 
		}, 
		secondarySpawns =
     		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 900 } 
		}
	},

	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "valarian_thug", planetName = "naboo", npcName = "a Thug" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "valarian_thug", planetName = "naboo", npcName = "a Thug" },
			{ npcTemplate = "valarian_thug", planetName = "naboo", npcName = "a Thug" },
			{ npcTemplate = "valarian_thug", planetName = "naboo", npcName = "a Thug" } 		
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "credits", amount = 975 } 
		}
	},
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "Geg Winthasen" } 
		}, 
		secondarySpawns = 
		{
		}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/loot/misc/damaged_datapad.iff", itemName = "Holodisc" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1050 }  
		}
	},

	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "fambaa", planetName = "naboo", npcName = "a Fambaa" } 
		}, 
		secondarySpawns = {	
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1125 } 
		}
	},
	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_seller", planetName = "naboo", npcName = "a Seller" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
		},	
			rewards = 
		{ 
			{ rewardType = "credits", amount = 1200 } 
		}
	},

	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "rebel_commando", planetName = "naboo", npcName = "a Rebel Commando" } 
		}, 
		secondarySpawns = {	
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "faction", faction = "imperial", amount = 225 },
			{ rewardType = "loot", lootGroup = "theme_park_reward_imperial_thrawn"}
		}
	},
}

veers_missions =
{

	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "rebel_crewman", planetName = "naboo", npcName = "a Rebel Crewman" },
			{ npcTemplate = "rebel_coordinator", planetName = "naboo", npcName = "a Rebel Coordinator" },
			{ npcTemplate = "rebel_medic", planetName = "naboo", npcName = "a Rebel Medic" },
			{ npcTemplate = "rebel_crewman", planetName = "naboo", npcName = "a Crewman" },
		}, 
		secondarySpawns = {	
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1275 } 
		}
	},
	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "rebel_crewman", planetName = "naboo", npcName = "a Rebel Crewman" },
			{ npcTemplate = "rebel_coordinator", planetName = "naboo", npcName = "a Rebel Coordinator" },
			{ npcTemplate = "rebel_medic", planetName = "naboo", npcName = "a Rebel Medic" },
			{ npcTemplate = "rebel_crewman", planetName = "naboo", npcName = "a Crewman" },
		}, 
		secondarySpawns = {	
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1350 } 
		}
	},
	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "thug", planetName = "naboo", npcName = "a Thug" }
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
		},	
			rewards = 
		{ 
			{ rewardType = "credits", amount = 1425 } 
		}
	},

	{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort_twilek", planetName = "naboo", npcName = "Borvo the Twi'lek" } 
		}, 
		secondarySpawns =
     		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1500 } 
		}
	},

	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "rebel_crewman", planetName = "naboo", npcName = "a Rebel Crewman" },
			{ npcTemplate = "rebel_coordinator", planetName = "naboo", npcName = "a Rebel Coordinator" },
			{ npcTemplate = "rebel_medic", planetName = "naboo", npcName = "a Rebel Medic" },
			{ npcTemplate = "rebel_crewman", planetName = "naboo", npcName = "a Crewman" },
			{ npcTemplate = "theme_park_imperial_escort_twilek", planetName = "naboo", npcName = "Borvo the Twi'lek" }
		}, 
		secondarySpawns = {	
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "faction", faction = "imperial", amount = 275 },
			{ rewardType = "loot", lootGroup = "theme_park_reward_imperial_veers"}
		}
	},
}

palpatine_missions =
{

	{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "a Thug Ringleader" } 
		}, 
		secondarySpawns =
     		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1575 } 
		}
	},
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "a Thug Ringleader" } 
		}, 
		secondarySpawns = 
		{
		}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/component/item/quest_item/directional_sensor.iff", itemName = "Plans" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1650 }
		}
	},
	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "rsf_security_officer", planetName = "naboo", npcName = "a Security Officer" },
		}, 
		secondarySpawns = {	
			{ npcTemplate = "rsf_security_guard", planetName = "naboo", npcName = "a Security Guard" },
			{ npcTemplate = "rsf_security_guard", planetName = "naboo", npcName = "a Security Guard" }
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1725 } 
		}
	},

	{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort_handmaiden", planetName = "naboo", npcName = "a Handmaiden" } 
		}, 
		secondarySpawns =
     		{
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1800 } 
		}
	},

	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "rebel_trooper", planetName = "naboo", npcName = "a Rebel Trooper" },
			{ npcTemplate = "rebel_trooper", planetName = "naboo", npcName = "a Rebel Trooper" },
			{ npcTemplate = "rebel_trooper", planetName = "naboo", npcName = "a Rebel Trooper" }
		}, 
		secondarySpawns = {	
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1875 } 
		}
	},

	{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "a Parliament Courier" } 
		}, 
		secondarySpawns = 
		{
		}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "a Recording" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1950 }
		}
	},

	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "rebel_general", planetName = "naboo", npcName = "a Rebel General" }
		}, 
		secondarySpawns = {	
			{ npcTemplate = "rebel_trooper", planetName = "naboo", npcName = "a Rebel Trooper" },
			{ npcTemplate = "rebel_trooper", planetName = "naboo", npcName = "a Rebel Trooper" }
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "faction", faction = "imperial", amount = 325 },
			{ rewardType = "loot", lootGroup = "theme_park_reward_imperial_emperor"}
		}
	}

}

darth_vader_missions =
{
	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "rebel_general", planetName = "naboo", npcName = "a Rebel General" },
		}, 
		secondarySpawns = {
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "credits", amount = 2025 } 
		}
	},

	{ 
		missionType = "retrieve", 
		primarySpawns = 
		{ 
			{ npcTemplate = "mara_jade", planetName = "naboo", npcName = "Mara Jade" } 
		}, 
		secondarySpawns =
     		{
		}, 
		itemSpawns = {
			{ itemTemplate = "object/tangible/loot/misc/damaged_datapad.iff", itemName = "Documents" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 2100 } 
		}
	},

	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "rebel_trooper", planetName = "naboo", npcName = "Rebellion's Courier" }
		}, 
		secondarySpawns = {	
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "credits", amount = 2175 } 
		}
	},

	{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_escort", planetName = "naboo", npcName = "an Information Broker" } 
		}, 
		secondarySpawns = 
		{
		}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "a Datadisk" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 2250 }
		}
	},

		{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "thug", planetName = "naboo", npcName = "an Information Broker" }
		}, 
		secondarySpawns = {	
			{ npcTemplate = "assassin", planetName = "naboo", npcName = "an Assassin" },
			{ npcTemplate = "mercenary", planetName = "naboo", npcName = "a Mercenary" }
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "credits", amount = 2325 }
		}
	},

	{ 
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "thug", planetName = "naboo", npcName = "Kaydeer" }
		}, 
		secondarySpawns = {
		}, 
		itemSpawns = 
		{ 
		},	
		rewards = 
		{ 
			{ rewardType = "faction", faction = "imperial", amount = 425 }, 
			{ rewardType = "credits", amount = 2400 },
			{ rewardType = "loot",  lootGroup = "theme_park_reward_imperial_vader" },
			{ rewardType = "badge", badge = THEME_PARK_IMPERIAL_BADGE }	
		}
	}
}

npcMapImperial = 
{ 
	{ 
		spawnData = { planetName = "naboo", npcTemplate = "kaja_orzee", x = -2, z = 0.5, y = -12.6, direction = 90, cellID = 1418872, position = STAND }, 
		worldPosition = { x = 2047, y = -3941 }, 
		npcNumber = 1,   
		stfFile = "@theme_park_imperial/kaja_orzee",
		stfWarning = "not_imperial",
		missions = kaja_orzee_missions
	},
	{ 
		spawnData = { planetName = "naboo", npcTemplate = "loam_hedge", x = 24, z = 0.2, y = -24, direction = 180, cellID = 1418874, position = STAND }, 
		worldPosition = { x = 2402, y = -3940 }, 
		npcNumber = 2,   
		stfFile = "@theme_park_imperial/loam_redge",
		stfWarning = "kaja_orzee",
		missions = loam_hedge_missions
	},
	{ 
		spawnData = { planetName = "naboo", npcTemplate = "lord_hethrir", x = 23, z = 0.2, y = -42, direction = 1, cellID = 1418875, position = STAND }, 
		worldPosition = { x = 2382, y = -3970 }, 
		npcNumber = 4,   
		stfFile = "@theme_park_imperial/lord_hethrir",
		stfWarning = "loam_redge",
		missions = lord_hethrir_missions
	},
	{ 
		spawnData = { planetName = "naboo", npcTemplate = "thrown", x = 2372, z = 292, y = -3924, direction = 150, cellID = 0, position = STAND }, 
		npcNumber = 8,   
		stfFile = "@theme_park_imperial/thrawn",
		stfWarning = "lord_hethrir",
		missions = thrown_missions
	},
	{ 
		spawnData = { planetName = "naboo", npcTemplate = "veers", x = 2372, z = 292, y = -3917, direction = 90, cellID = 0, position = STAND }, 
		npcNumber = 16,   
		stfFile = "@theme_park_imperial/veers",
		stfWarning = "lord_hethrir",
		missions = veers_missions
	},
	{ 
		spawnData = { planetName = "naboo", npcTemplate = "palpatine", x = 13, z = 21, y = -25, direction = 180, cellID = 1418886, position = STAND },
		worldPosition = { x = -2397, y = -3958 },  
		npcNumber = 32,   
		stfFile = "@theme_park_imperial/emperor",
		stfWarning = "emperor",
		missions = palpatine_missions
	},
	{ 
		spawnData = { planetName = "naboo", npcTemplate = "darth_vader", x = -56, z = 0.2, y = -24, direction = 180, cellID = 1418884, position = STAND },
		worldPosition = { x = 2387, y = -3889 },  
		npcNumber = 64,   
		stfFile = "@theme_park_imperial/darth_vader",
		stfWarning = "vader",
		missions = darth_vader_missions
	}
}

permissionMapImperial = { -- Coming soon...
}

ThemeParkImperial = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapImperial,
	permissionMap = permissionMapImperial,
	className = "ThemeParkImperial",
	screenPlayState = "imperial_theme_park",
	missionDescriptionStf = "@theme_park_imperial/quest_details:imperial_retreat_",
	missionCompletionMessageStf = "@theme_park/messages:imperial_completion_message",
	--warningMessageStf = "@theme_park_imperial/warning:"
}

registerScreenPlay("ThemeParkImperial", true)

theme_park_imperial_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkImperial
}
theme_park_imperial_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkImperial
}
