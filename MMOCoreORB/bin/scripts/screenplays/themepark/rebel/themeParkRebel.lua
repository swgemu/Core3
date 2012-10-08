THEME_PARK_REBEL_BADGE = 107

c3po_missions = 
{
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_selonian_female", planetName = "corellia", npcName = "random" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/food/base/side_dish_base.iff", itemName = "Food" }
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
			{ npcTemplate = "theme_park_rebel_captain", planetName = "corellia", npcName = "Captain Montrasword" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/medicine/crafted/medpack_wound_health_a.iff", itemName = "Medicine" }
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
			{ npcTemplate = "theme_park_rebel_captain", planetName = "corellia", npcName = "Captain Teargle" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 150 } 
		} 
	},
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_captain", planetName = "corellia", npcName = "Captain Drexsler" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Contact Information" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 200 }, 
			{ rewardType = "faction", faction = "rebel", amount = 50 }, 
			{ rewardType = "loot",  lootGroup = "theme_park_reward_rebel_c_3po" }
		}
	}
}

qualdo_missions = 
{
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_ithorian", planetName = "corellia", npcName = "I'klee'trao" } 
		}, 
		secondarySpawns = {},
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/loot/tool/comlink_naboo_broken.iff", itemName = "Comlink" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 200 } 
		} 
	},
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_sergeant_montage", planetName = "corellia", npcName = "Sergeant Montage" } 
		}, 
		secondarySpawns = 
		{ 
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" } 
		}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/component/item/quest_item/particle_sensor.iff", itemName = "Compound" }
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
			{ npcTemplate = "theme_park_imperial_captain_sargon", planetName = "corellia", npcName = "Captain Sargon" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" }
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
			{ npcTemplate = "theme_park_rebel_ithorian", planetName = "corellia", npcName = "I'klee'trao" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 75 }, 
			{ rewardType = "loot", lootGroup = "theme_park_reward_rebel_qualdo_herm" } 
		}
	}
}
wedge_missions = 
{
	{ 
		missionType = "deliver",
	 	primarySpawns = 
	 	{ 
	 		{ npcTemplate = "theme_park_rebel_officer", planetName = "corellia", npcName = "Officer Devlin" } 
	 	}, 
	 	secondarySpawns = {}, 
	 	itemSpawns = 
	 	{
	 		{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Confirmation Letter" }
	 	}, 
	 	rewards = 
	 	{ 
	 		{ rewardType = "credits", amount = 350 } 
	 	}
	},
	{ 
		missionType = "assassinate",
		primarySpawns =  
		{ 
			{ npcTemplate = "theme_park_rebel_iris", planetName = "corellia", npcName = "Iris" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 400 } 
		}
	},
	{ 
		missionType = "assassinate",
	 	primarySpawns = 
	 	{ 
	 		{ npcTemplate = "theme_park_imperial_general_graise", planetName = "corellia", npcName = "General Graise" } 
	 	}, 
	 	secondarySpawns = 
	 	{
			{ npcTemplate = "imperial_first_lieutenant", planetName = "corellia", npcName = "Imperial First Lieutenant" },
			{ npcTemplate = "imperial_staff_corporal", planetName = "corellia", npcName = "Imperial Staff Corporal" }
		}, 
	 	itemSpawns = 
	 	{
	 		{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Documents" }
	 	}, 
	 	rewards = 
	 	{ 
	 		{ rewardType = "credits", amount = 450 } 
	 	}
	},
	{ 
		missionType = "assassinate",
	 	primarySpawns = 
	 	{ 
	 		{ npcTemplate = "theme_park_imperial_general_graise", planetName = "corellia", npcName = "General Boize" } 
	 	}, 
	 	secondarySpawns = 
	 	{
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" }
		}, 
	 	itemSpawns = 
	 	{
	 		{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Documents" }
	 	},  
	 	rewards = 
	 	{
	 		{ rewardType = "credits", amount = 500 } 
	 	}
	},
	{ 
		missionType = "assassinate",
	 	primarySpawns = 
	 	{ 
	 		{ npcTemplate = "theme_park_rebel_captain_montrasword", planetName = "corellia", npcName = "random" } 
	 	}, 
	 	secondarySpawns = 
	 	{
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" }
		}, 
	 	itemSpawns = 
	 	{
	 		{ itemTemplate = "object/tangible/loot/misc/key_electronic_s01.iff", itemName = "Code Cylinder" }
	 	}, 
	 	rewards = 
	 	{ 
	 		{ rewardType = "faction", faction = "rebel", amount = 100 }, 
	 		{ rewardType = "loot", lootGroup = "theme_park_reward_rebel_wedge_antilles" } 
	 	}
	}
}

leia_missions = 
{
	{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_deasie_afresel", planetName = "corellia", npcName = "Deasie A'Fresel" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 550 } 
		}
	},
	{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_officer_tennelt", planetName = "corellia", npcName = "Officer Tennelt" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = { }, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 600 } 
		} 
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_selonian_female", planetName = "corellia", npcName = "random" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 650 } 
		}
	},
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_bothan", planetName = "corellia", npcName = "Fnast" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
	 		{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Imperial Codes" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 700 } 
		} 
	},
	{ 
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_commander.lua", planetName = "corellia", npcName = "Imperial Undercover Commander" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "corellia", npcName = "Stormtrooper" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 125 },
			{ rewardType = "loot", lootGroup = "theme_park_reward_rebel_leia_organa" }
		}
	}
}

nien_missions = 
{
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_engineer", planetName = "lok", npcName = "Engineer" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 750 } 
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_bounty_hunter", planetName = "lok", npcName = "Bounty Hunter" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 800 } 
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_pirate", planetName = "lok", npcName = "Pirate" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 850 } 
		}
	},
	{
		missionType = "retrieve", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_hyperdrive_seller", planetName = "lok", npcName = "Pirate" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 150 },
			{ rewardType = "loot", lootGroup = "theme_park_reward_rebel_nien_nunb" }
		}
	}
}

han_missions = 
{
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_edycu", planetName = "lok", npcName = "E'Dycu" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 900 } 
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_pirate_holocron", planetName = "lok", npcName = "random" }, 
			{ npcTemplate = "theme_park_rebel_pirate", planetName = "lok", npcName = "random" },
			{ npcTemplate = "theme_park_rebel_pirate", planetName = "lok", npcName = "random" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/loot/misc/holocron_splinters_sith_s01.iff", itemName = "Holocron Splinters" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", 950 } 
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_pirate", planetName = "lok", npcName = "Bandit Leader" } 
		}, 
		secondarySpawns = 
		{			
			{ npcTemplate = "theme_park_rebel_pirate", planetName = "lok", npcName = "Pirate" },
			{ npcTemplate = "theme_park_rebel_pirate", planetName = "lok", npcName = "Pirate" },
			{ npcTemplate = "theme_park_rebel_pirate", planetName = "lok", npcName = "Pirate" }  
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1000 } 
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_edycu", planetName = "lok", npcName = "Eso Itrik" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "lok", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "lok", npcName = "Stormtrooper" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1050 } 
		}
	},
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_nym_contact", planetName = "lok", npcName = "Nateba Kerr" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Payment" }
		}, 
		rewards = 
		{
			{ rewardType = "faction", faction = "rebel", amount = 175 }, 
			{ rewardType = "loot",  lootGroup = "theme_park_reward_rebel_han_solo" }
		}
	}
}

ackbar_missions =
{
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "Stormtrooper" }
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1100 } 
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_disgruntled_citizen", planetName = "dantooine", npcName = "Disgruntled Citizen" }
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
			{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Information" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1150 } 
		}
	},
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{
			{ npcTemplate = "theme_park_rebel_teria_alessie", planetName = "dantooine", npcName = "Teria Alessie" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
	 		{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Corrupted Disk" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1200 } 
		} 
	},
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{
			{ npcTemplate = "theme_park_rebel_jeremes_kelton", planetName = "dantooine", npcName = "Jeremes Kelton" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "Stormtrooper" },
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "Stormtrooper" }
		}, 
		itemSpawns = 
		{ 
	 		{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Flight Paths" }
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
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "Stormtrooper" }
		}, 
		secondarySpawns =  
		{
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-437" },
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-871" }
		},  
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 200 }, 
			{ rewardType = "loot",  lootGroup = "theme_park_reward_rebel_captain_ackbar" }
		}
	}
}

mon_missions = 
{
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{
			{ npcTemplate = "theme_park_rebel_bothan_spy", planetName = "dantooine", npcName = "Wala Am'kre" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
	 		{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Holovid" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1300 } 
		} 
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "stormtrooper_squad_leader", planetName = "dantooine", npcName = "Strike Team Leader" }
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-221" },
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-982" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1350 } 
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_jeremes_kelton", planetName = "dantooine", npcName = "Altapi T'mman" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-179" },
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-322" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1400 } 
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "stormtrooper_squad_leader", planetName = "dantooine", npcName = "TK-1132" }
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-658" },
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-459" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1450 } 
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_engineer", planetName = "dantooine", npcName = "Engineer" } 
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-134" },
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-873" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1500 } 
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "imperial_general", planetName = "dantooine", npcName = "Imperial General" }
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-297" },
			{ npcTemplate = "stormtrooper", planetName = "dantooine", npcName = "TK-447" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 225 }, 
			{ rewardType = "loot",  lootGroup = "theme_park_reward_rebel_mon_mothma" }
		}
	},
}

jan_missions = 
{
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "stormtrooper_squad_leader", planetName = "yavin4", npcName = "TK-419" }
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "yavin4", npcName = "TK-447" },
			{ npcTemplate = "stormtrooper", planetName = "yavin4", npcName = "TK-428" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1550 } 
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_imperial_engineer", planetName = "yavin4", npcName = "Rebel Contact" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1600 } 
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "stormtrooper_squad_leader", planetName = "yavin4", npcName = "TK-770" }
		}, 
		secondarySpawns = 
		{
			{ npcTemplate = "stormtrooper", planetName = "yavin4", npcName = "TK-400" },
			{ npcTemplate = "stormtrooper", planetName = "yavin4", npcName = "TK-105" }
		}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", 1650 } 
		}
	},
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{
			{ npcTemplate = "theme_park_rebel_bothan_spy", planetName = "yavin4", npcName = "Nateba Kurr" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
	 		{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Information" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1700 } 
		} 
	},
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{
			{ npcTemplate = "theme_park_rebel_bothan_spy", planetName = "yavin4", npcName = "Pilot" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
	 		{ itemTemplate = "object/tangible/mission/mission_datadisk.iff", itemName = "Information" }
		}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 250 }, 
			{ rewardType = "loot",  lootGroup = "theme_park_reward_rebel_jan_dodonna" }
		} 
	},
}

luke_missions = 
{
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_supervisor", planetName = "yavin4", npcName = "Supervisor" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1750 } 
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_big_creature", planetName = "yavin4", npcName = "Big Creature" }
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{
	 		{ itemTemplate = "object/tangible/loot/tool/recording_rod_broken.iff", itemName = "R2 Motivator Unit" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1800 } 
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_supervisor", planetName = "yavin4", npcName = "Expidition Team Member" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1850 } 
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "theme_park_rebel_big_creature_cage", planetName = "yavin4", npcName = "Big Creature" }
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{
	 		{ itemTemplate = "object/static/item/item_cage_bamboo.iff", itemName = "An Empty Cage" }
		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1900 } 
		}
	},
	{ 
		missionType = "deliver", 
		primarySpawns = 
		{
			{ npcTemplate = "theme_park_rebel_supervisor", planetName = "yavin4", npcName = "Tribesman" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{ 
	 		{ itemTemplate = "object/static/item/item_cage_bamboo.iff", itemName = "An Empty Cage" }
		}, 
		rewards = 
		{ 
			{ rewardType = "faction", faction = "rebel", amount = 300 }, 
			{ rewardType = "credits", amount = 1950 },
			{ rewardType = "loot",  lootGroup = "theme_park_reward_rebel_luke_skywalker" },
			{ rewardType = "badge", badge = THEME_PARK_REBEL_BADGE }			
		} 
	},
}

npcMapRebel = 
{ 
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "c_3po", x = -2.3, z = 2.0, y = 4.0, direction = 150, cellID = 8555472, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@theme_park_rebel/c3po",
		missions = c3po_missions
	},
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "r2d2", x = -3.98, z = 1.01, y = -0.67, direction = 58, cellID = 8555472, position = STAND }, 
		npcNumber = -1,  
		stfFile = "",               
		missions = {} 
	},
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "qualdo_herm", x = 14.91, z = 1.01, y = -6.68, direction = 0, cellID = 8555475, position = STAND }, 
		npcNumber = 2,   
		stfFile = "@theme_park_rebel/qualdo_herm",    
		missions = qualdo_missions 
	},
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "wedge_antilles", x = 0.01, z = 1.01, y = -22.01, direction = 0, cellID = 8555477, position = SIT }, 
		npcNumber = 4,   
		stfFile = "@theme_park_rebel/wedge_antilles", 
		missions = wedge_missions 
	},
	{ 
		spawnData = { planetName = "corellia", npcTemplate = "leia_organa", x = -11.13, z = 7.00971, y = 11.31, direction = 175, cellID = 8555481, position = STAND }, 
		npcNumber = 8,   
		stfFile = "@theme_park_rebel/princess_leia",  
		missions = {} 
	},
	{ 
		spawnData = { planetName = "lok", npcTemplate = "nien_nunb", x = -12.12, z = -0.894992, y = 23.08, direction = 80.0024, cellID = 8145384, position = SIT }, 
		npcNumber = 16,  
		stfFile = "@theme_park_rebel/nien_nunb",      
		missions = nien_missions 
	},
	{ 
		spawnData = { planetName = "lok", npcTemplate = "chewbacca", x = -28.48, z = -0.519991, y = 5.87, direction = 12.0003, cellID = 8145388, position = STAND }, 
		npcNumber = -1,  
		stfFile = "",               
		missions = {} 
	},
	{ 
		spawnData = { planetName = "lok", npcTemplate = "han_solo", x = -30.2, z = -0.519991, y = 7.24, direction = 45.0013, cellID = 8145388, position = STAND }, 
		npcNumber = 32,  
		stfFile = "@theme_park_rebel/han_solo",       
		missions = han_missions 
	},
	{ 
		spawnData = { planetName = "dantooine", npcTemplate = "ackbar", x = -14.4, z = 1.0, y = -21.7, direction = 0, cellID = 6555566, position = STAND }, 
		npcNumber = 64,  
		stfFile = "@theme_park_rebel/captain_ackbar", 
		missions = ackbar_missions 
	},
	{ 
		spawnData = { planetName = "dantooine", npcTemplate = "mon_mothma", x = -3.4, z = 7.0, y = -12.2, direction = -34, cellID = 6555568, position = STAND }, 
		npcNumber = 128, 
		stfFile = "@theme_park_rebel/mon_mothma",     
		missions = mon_missions 
	},
	{ 
		spawnData = { planetName = "yavin4", npcTemplate = "jan_dodonna", x = 0, z = 0, y = -41.9, direction = 0, cellID = 3465388, position = STAND }, 
		npcNumber = 256, 
		stfFile = "@theme_park_rebel/jan_dodonna",    
		missions = jan_missions 
	},
	{ 
		spawnData = { planetName = "yavin4", npcTemplate = "luke_skywalker", x = 1.2, z = -6.0, y = -26.8, direction = 180, cellID = 3465390, position = STAND }, 
		npcNumber = 512, 
		stfFile = "@theme_park_rebel/luke_skywalker", 
		missions = {} 
	}
}

permissionMapRebel = {
	{
		planetName = "corellia", 
		regionName = "rebel_hideout",		
		permissions = 
		{ 
			{ 
				cells = { 8555471, 8555472, 8555473, 8555474, 8555475, 8555476, 8555477, 8555478, 8555479, 8555480, 8555481, 8555482 },
				conditions = 
				{
					{ permissionType = "faction", faction = FACTIONREBEL }
				}
			}
		}
	},
	{
		planetName = "dantooine", 
		regionName = "abandoned_rebel_base_1",
		permissions = 
		{ 
			{
				cells = { 6555559, 6555560, 6555561, 6555562, 6555563, 6555564, 6555565, 6555566, 6555567, 6555568, 6555569, 6555570 },
				conditions = 
				{
					{ permissionType = "faction", faction = FACTIONREBEL }
				}
			}
		}
	},
	{
		planetName = "yavin4",
		regionName = "temple_of_exar_kun",
		permissions =
		{
			{
				cells = { 3465380, 3465381, 3465382, 3465383, 3465384, 3465385, 3465386, 3465387, 3465388, 3465389, 3465390, 3465391, 3465392, 3465393, 3465394 },
				conditions = 
				{
					{ permissionType = "missionState", mission = "theme_park_rebel", missionState = 128 },
					{ permissionType = "faction", faction = FACTIONREBEL }
				}
			},
			{
				cells = { 3465380, 3465381, 3465382, 3465383, 3465384, 3465385, 3465386, 3465387, 3465388, 3465389, 3465390, 3465391, 3465392, 3465393, 3465394 },
				conditions = 
				{
					{ permissionType = "missionState", mission = "theme_park_rebel", missionState = 256 },
					{ permissionType = "faction", faction = FACTIONREBEL }
				}
			}
		}
	}
}

ThemeParkRebel = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapRebel,
	permissionMap = permissionMapRebel,
	className = "ThemeParkRebel",
	screenPlayState = "rebel_theme_park",
	missionDescriptionStf = "@theme_park_rebel/quest_details:rebel_hideout_",
	missionCompletionMessageStf = "@theme_park/messages:rebel_hideout_message"
}

registerScreenPlay("ThemeParkRebel", true)

mission_giver_conv_handler:setThemePark(ThemeParkRebel)

mission_target_conv_handler:setThemePark(ThemeParkRebel)