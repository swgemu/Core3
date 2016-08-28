kavas_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "cie_vos", npcName = "Cie Vos" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/toxic_rations.iff", itemName = "Toxic Rations" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 2000 },
				{ rewardType = "faction", faction = "valarian", amount = 50 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "jabba_enforcer", npcName = "Jabba's enforcer" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 3000 },
				{ rewardType = "faction", faction = "valarian", amount = 75 }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "ysho", npcName = "Ysho" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "jabba_thug", npcName = "Jabba's thug" },
				{ npcTemplate = "jabba_thug", npcName = "Jabba's thug" },
				{ npcTemplate = "jabba_thug", npcName = "Jabba's thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/proclamation_s01.iff", itemName = "An Official Proclamation" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 4000 },
				{ rewardType = "faction", faction = "valarian", amount = 100 }
			}
		},
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "kishai", npcName = "Ki'shai" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/camera_s01.iff", itemName = "A Camera" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 5000 },
				{ rewardType = "faction", faction = "valarian", amount = 125 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "jabba_enforcer", npcName = "Jabba's enforcer" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 6000 },
				{ rewardType = "faction", faction = "valarian", amount = 150 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "kavas_jabba_assassin", npcName = "Jabba's assassin" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/briefcase_s01.iff", itemName = "A Locked Briefcase" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 7000 },
				{ rewardType = "faction", faction = "valarian", amount = 200 }
			}
		}
	}

ind_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "valarian_chief_assassin", npcName = "Valarian's Chief Assassin" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/ledger_s01.iff", itemName = "A Ledger" }
			},
			rewards =
			{
				{ rewardType = "loot",  lootGroup = "task_reward_ind_q1" },
				{ rewardType = "faction", faction = "valarian", amount = 50 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "valarian_compound_guard_quest", npcName = "Valarian's Compound Guard" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "jabba_henchman", npcName = "Jabba's henchman" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 },
				{ rewardType = "faction", faction = "valarian", amount = 100 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "dr_kaum", npcName = "Dr. Kaum" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 3000 },
				{ rewardType = "loot",  lootGroup = "task_reward_ind_q3" },
				{ rewardType = "faction", faction = "valarian", amount = 125 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "assassin", npcName = "Roden Venthral" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 5000 },
				{ rewardType = "faction", faction = "valarian", amount = 150 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "ind_jabba_enforcer", npcName = "Jabba's enforcer" },
			},
			secondarySpawns =
			{
				{ npcTemplate = "jabba_enforcer", npcName = "Jabba's enforcer" },
				{ npcTemplate = "jabba_enforcer", npcName = "Jabba's enforcer" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/toxic_rations.iff", itemName = "Toxic Rations" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 7000 },
				{ rewardType = "faction", faction = "valarian", amount = 200 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "ind_jabba_henchman", npcName = "Jabba's Delivery Boy" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "jabba_enforcer", npcName = "Jabba's enforcer" },
				{ npcTemplate = "jabba_enforcer", npcName = "Jabba's enforcer" },
				{ npcTemplate = "jabba_enforcer", npcName = "Jabba's enforcer" },
				{ npcTemplate = "jabba_enforcer", npcName = "Jabba's enforcer" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/petrified_avian_egg.iff", itemName = "Petrified Avian Egg" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 8000 },
				{ rewardType = "faction", faction = "valarian", amount = 200 }
			}
		}
	}

lady_valarian_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "jabba_enforcer", npcName = "Una Gitori" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 2000 },
				{ rewardType = "faction", faction = "valarian", amount = 75 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "tough_thug_male_rodian", npcName = "Soobu Javeedo" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a Thug" },
				{ npcTemplate = "thug", npcName = "a Thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 4000 },
				{ rewardType = "faction", faction = "valarian", amount = 100 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "bodyguard_zabrak_female", npcName = "Kilth Saanu" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a Thug" },
				{ npcTemplate = "thug", npcName = "a Thug" },
				{ npcTemplate = "thug", npcName = "a Thug" },
				{ npcTemplate = "thug", npcName = "a Thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 6000 },
				{ rewardType = "faction", faction = "valarian", amount = 125 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "assassin_twilek_mate", npcName = "Arrud Barsoomu" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 8000 },
				{ rewardType = "faction", faction = "valarian", amount = 200 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "chadra_fan_assassin", npcName = "Duska Murgo" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "ig_assassin_droid", npcName = "an IG assassin droid" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 10000 },
				{ rewardType = "faction", faction = "valarian", amount = 225 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "brigand_assassin", npcName = "Siron Vurn'ke" },
			},
			secondarySpawns =
			{
				{ npcTemplate = "weequay_thug", npcName = "a Weequay Thug" },
				{ npcTemplate = "weequay_thug", npcName = "a Weequay Thug" },
				{ npcTemplate = "weequay_thug", npcName = "a Weequay Thug" },
				{ npcTemplate = "weequay_thug", npcName = "a Weequay Thug" },
				{ npcTemplate = "weequay_thug", npcName = "a Weequay Thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 14000 },
				{ rewardType = "faction", faction = "valarian", amount = 300 },
				{ rewardType = "loot",  lootGroup = "task_reward_valarian_dagger" }
			}
		},
	}

npcMapThemeParkValarian =
	{
		{
			spawnData = { npcTemplate = "lady_valarian", x = -23.84, z = 9.01, y = 0.61, direction = 147, cellID = 1076945, position = STAND },
			worldPosition = { x = 3363, y = -4607 },
			npcNumber = 4,
			stfFile = "@static_npc/tatooine/lady_valarian",
			missions = lady_valarian_missions
		},
		{
			spawnData = { npcTemplate = "ind", x = -24.62, z = 9.01, y = -8.01, direction = 133.6, cellID = 1076944, position = STAND },
			worldPosition = { x = 3366, y = -4615 },
			npcNumber = 2,
			stfFile = "@spawning/static_npc/tato_valarian_ind",
			missions = ind_missions
		},
		{
			spawnData = { npcTemplate = "kavas_urdano", x = -13.79, z = 7.01, y = -3.96, direction = 12, cellID = 1076943, position = STAND },
			worldPosition = { x = 3374, y = -4607 },
			npcNumber = 1,
			stfFile = "@spawning/static_npc/tato_valarian_kavas_urdano",
			missions = kavas_missions
		},
	}

ThemeParkValarian = ThemeParkLogic:new {
	npcMap = npcMapThemeParkValarian,
	className = "ThemeParkValarian",
	screenPlayState = "theme_park_valarian",
	requiresEliteCombat = true,
	planetName = "tatooine",
	distance = 800,
	requiredFaction = "valarian"
}

registerScreenPlay("ThemeParkValarian", true)

theme_park_valarian_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThemeParkValarian
}
theme_park_valarian_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThemeParkValarian
}
