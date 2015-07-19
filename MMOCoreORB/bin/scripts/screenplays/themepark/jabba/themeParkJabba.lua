THEME_PARK_JABBA_BADGE = 105

buildingBarada =
	{
		type = "destructible",
		building = { template = "object/building/military/pirate_warehouse.iff", planet = "tatooine" },
		terminal = { template = "object/tangible/terminal/terminal_destructible_building.iff", vectorCellID = 3, x = 0, z = 0.3, y = -6.0 },
		childNpcs = {}
	}

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
				{ rewardType = "loot", lootGroup = "jabba_theme_park_reelo" },
				{ rewardType = "faction", faction = "jabba", amount = 25 }
			}
		}
	}

ree_yees_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Raf Daris" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian's Thug" },
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian's Thug" },
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian's Thug" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 250 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_jawa", planetName = "tatooine", npcName = "Jawa" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "jawa_henchman", planetName = "tatooine", npcName = "a Jawa" },
				{ npcTemplate = "jawa_henchman", planetName = "tatooine", npcName = "a Jawa" },
				{ npcTemplate = "jawa_henchman", planetName = "tatooine", npcName = "a Jawa" },
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
				{ rewardType = "loot", lootGroup = "jabba_theme_park_ree_yees" },
				{ rewardType = "permission", permissionGroup = "jabba_palace1" },
				{ rewardType = "faction", faction = "jabba", amount = 50 }
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
			missionType = "confiscate",
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
				{ rewardType = "permission", permissionGroup = "jabba_palace2" },
				{ rewardType = "faction", faction = "jabba", amount = 75 }
			}
		}
	}

porcellus_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_jabba_kaadu", planetName = "tatooine", npcName = "Kaadu" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "mercenary_aggro", planetName = "tatooine", npcName = "a Mercenary" },
				{ npcTemplate = "mercenary_aggro", planetName = "tatooine", npcName = "a Mercenary" },
			},
			itemSpawns = {
				{ itemTemplate = "object/tangible/loot/misc/petrified_avian_egg.iff", itemName = "Petrified Avian Egg" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 650 }
			}
		},
		{
			missionType = "confiscate",
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
				{ rewardType = "credits", amount = 750 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_jabba_meatbeast", planetName = "tatooine", npcName = "Meatbeast" }
			},
			secondarySpawns =
			{},
			itemSpawns = {
				{ itemTemplate = "object/tangible/food/meat_object.iff", itemName = "Chicken Leg" }
			},
			rewards =
			{
				{ rewardType = "loot", lootGroup = "jabba_theme_park_porcellus"},
				{ rewardType = "permission", permissionGroup = "jabba_palace3" },
				{ rewardType = "faction", faction = "jabba", amount = 100 }
			}
		}
	}

barada_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "theme_park_jabba_valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "theme_park_jabba_weak_mercenary", planetName = "tatooine", npcName = "Weak Mercenary" },

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
			missionType = "destroy",
			buildingSpawn = buildingBarada,
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
				{ rewardType = "loot", lootGroup = "jabba_theme_park_barada"},
				{ rewardType = "permission", permissionGroup = "jabba_palace4" },
				{ rewardType = "faction", faction = "jabba", amount = 125 }
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
			secondarySpawns = {},
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
				{ npcTemplate = "theme_park_jabba_sennex_slaver", planetName = "tatooine", npcName = "Hizram Riean" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "A Thug" },
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "A Thug" },
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
				{ rewardType = "loot", lootGroup = "jabba_theme_park_bib"},
				{ rewardType = "faction", faction = "jabba", amount = 150 }
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
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
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
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Interrogator" }
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
				{ rewardType = "credits", amount = 1450 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "valarian_courier", planetName = "tatooine", npcName = "Valarian Courier" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			},
			itemSpawns = {
				{ itemTemplate = "object/tangible/loot/misc/ledger_s01.iff", itemName = "Ledger" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 1550 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "valarian_assassin", planetName = "tatooine", npcName = "Valarian Strike Team Leader" }
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
				{ rewardType = "credits", amount = 1650 }
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
				{ rewardType = "credits", amount = 1750 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "valarian_assassin", planetName = "tatooine", npcName = "Punk" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
				{ npcTemplate = "valarian_thug", planetName = "tatooine", npcName = "Valarian Thug" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1850 }
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
				{ rewardType = "credits", amount = 1950 }
			}
		},
		{
			missionType = "confiscate",
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
				{ itemTemplate = "object/weapon/melee/sword/sword_rantok.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "loot", lootGroup = "jabba_theme_park_g5p0"},
				{ rewardType = "badge", badge = THEME_PARK_JABBA_BADGE },
				{ rewardType = "faction", faction = "jabba", amount = 200 },
				{ rewardType = "permission", permissionGroup = "jabba_palace5" },
				{ rewardType = "credits", amount = 2000 }
			}
		},
	}

npcMapJabba =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "reelo_baruk", x = -2, z = 0.199999, y = 113.01, direction = 53.9956, cellID = 1177466, position = STAND },
			worldPosition = { x = -5899.5, y = -6226.7 },
			npcNumber = 1,
			stfFile = "@theme_park_jabba/reelo_baruk",
			missions = reelo_missions
		},
		{
			spawnData = { planetName = "tatooine", npcTemplate = "ree_yees", x = 5.97, z = 0.299998, y = 116.1, direction = 248.813, cellID = 1177466, position = STAND },
			worldPosition = { x = -5892.3, y = -6230.8 },
			npcNumber = 2,
			stfFile = "@theme_park_jabba/ree_yees",
			missions = ree_yees_missions
		},
		{
			spawnData = { planetName = "tatooine", npcTemplate = "ephant_mon", x = -6, z = 5.85, y = 84, direction = 277.481, cellID = 1177469, position = STAND },
			worldPosition = { x = -5924.4, y = -6242.4 },
			npcNumber = 4,
			stfFile = "@theme_park_jabba/ephant_mon",
			missions = ephant_mon_missions
		},
		{
			spawnData = { planetName = "tatooine", npcTemplate = "porcellus", x = -43, z = 3, y = 64, direction = 306.623, cellID = 1177477, position = STAND },
			worldPosition = { x = -5963.5, y = -6226.9 },
			npcNumber = 8,
			stfFile = "@theme_park_jabba/porcellus",
			missions = porcellus_missions
		},
		{
			spawnData = { planetName = "tatooine", npcTemplate = "barada", x = 30.57, z = 0.199999, y = -1.05, direction = 164.173, cellID = 1177499, position = STAND },
			worldPosition = { x = -5965.8, y = -6325.1 },
			npcNumber = 16,
			stfFile = "@theme_park_jabba/barada",
			missions = barada_missions
		},
		{
			spawnData = { planetName = "tatooine", npcTemplate = "bib_fortuna", x = -12.09, z = 2, y = 49.41, direction = 176.373, cellID = 1177487, position = STAND },
			worldPosition = { x = -5954.9, y = -6260.0 },
			npcNumber = 32,
			stfFile = "@theme_park_jabba/bib_fortuna",
			missions = bib_missions
		},
		{
			spawnData = { planetName = "tatooine", npcTemplate = "g_5po", x = -15.07, z = 2, y = 45.9, direction = 119.771, cellID = 1177487, position = STAND },
			worldPosition = { x = -5959.4, y = -6259.9 },
			npcNumber = 64,
			stfFile = "@theme_park_jabba/g5po",
			missions = g5po_missions
		},
		{
			spawnData = { planetName = "tatooine", npcTemplate = "record_keeper_jabba", x =6.56792, z =0.299999, y = 128.257, direction = 353.004, cellID = 1177466, position = STAND },
			npcNumber = -1,
			stfFile = "",
			missions = {}
		},

	}

permissionMapJabba = {
	{
		planetName = "tatooine",
		regionName = "jabba_palace",
		permissions =
		{
			{
				cells = { 1177467, 1177468, 1177469, 1177489, 1177490 },
				conditions =
				{
					{ permissionType = "missionState", mission = "theme_park_jabba", missionState = 2 }
				}
			},
			{
				cells = {1177470, 1177474, 1177475, 1177476, 1177477, 1177478, 1177479, 1177480, 1177481, 1177488 },
				conditions =
				{
					{ permissionType = "missionState", mission = "theme_park_jabba", missionState = 4 }
				}
			},
			{
				cells = { 1177471, 1177472, 1177473, 1177484, 1177499, 1177502 },
				conditions =
				{
					{ permissionType = "missionState", mission = "theme_park_jabba", missionState = 8 }
				}
			},
			{
				cells = { 1177482, 1177483, 1177485, 1177487, 1177500, 1177501 },
				conditions =
				{
					{ permissionType = "missionState", mission = "theme_park_jabba", missionState = 16 }
				}
			},
			{
				cells = { 1177486 },
				conditions =
				{
					{ permissionType = "missionState", mission = "theme_park_jabba", missionState = 64 }
				}
			}
		}
	}
}

ThemeParkJabba = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapJabba,
	permissionMap = permissionMapJabba,
	className = "ThemeParkJabba",
	screenPlayState = "jabba_theme_park",
	distance = 850,
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
