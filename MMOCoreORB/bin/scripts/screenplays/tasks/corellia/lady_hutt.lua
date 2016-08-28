lasha_bindari_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "lasha_courier", npcName = "a courier" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/lasha_bindari_q1_needed.iff", itemName = "Evidence List" }
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
				{ npcTemplate = "corsec_cadet", npcName = "Officer Jax" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "corsec_cadet", npcName = "a CorSec officer" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 300 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "corsec_investigator", npcName = "Chief Investigator Klusoe" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "corsec_cadet", npcName = "a CorSec cadet" },
				{ npcTemplate = "corsec_cadet", npcName = "a CorSec cadet" },
				{ npcTemplate = "corsec_cadet", npcName = "a CorSec cadet" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 500 }
			}
		}
	}

karena_keer_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "dray_ithicus", npcName = "Dray Ithicus" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/karena_keer_q1_needed.iff", itemName = "Bank authorizations" }
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
				{ npcTemplate = "breelik_nar", npcName = "Breel'ik Nar" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/karena_keer_q2_needed.iff", itemName = "Spice" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 400 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "assassin", npcName = "Lacklo Blant" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "mercenary_aggro", npcName = "a mercenary" },
				{ npcTemplate = "mercenary_aggro", npcName = "a mercenary" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 600 }
			}
		}
	}

shalera_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "lasha_courier", npcName = "a Black Sun courier" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/shalera_q1_needed.iff", itemName = "Message for Black Sun" }
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
				{ npcTemplate = "mercenary_aggro", npcName = "a Black Sun mercenary" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 400 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "shalera_accountant", npcName = "Shalera's accountant" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "a thug" },
				{ npcTemplate = "thug", npcName = "a thug" }
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
				{ npcTemplate = "sharpshooter", npcName = "Yime Kalulez" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 800 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "naz_tulos", npcName = "Naz Tulos" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "corsec_trooper", npcName = "a CorSec trooper" },
				{ npcTemplate = "corsec_trooper", npcName = "a CorSec trooper" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "lasha_courier", npcName = "a Jabba courier" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "assassin", npcName = "a Black Sun assassin" },
				{ npcTemplate = "assassin", npcName = "a Black Sun assassin" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/shalera_q6_needed.iff", itemName = "Virus sample" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 1200 }
			}
		}
	}

npcMapLadyHutt =
	{
		{
			spawnData = { npcTemplate = "lasha_bindari", x = 39, z = 0.1, y = 0.9, direction = 189, cellID = 3005397, position = STAND },
			worldPosition = { x = -3463, y = 3052 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/lasha_bindari",
			missions = lasha_bindari_missions
		},
		{
			spawnData = { npcTemplate = "karena_keer", x = -7.912, z = -0.9, y = 18.58, direction = 115.51, cellID = 2625361, position = STAND },
			worldPosition = { x = -5232, y = -2519 },
			npcNumber = 2,
			stfFile = "@static_npc/corellia/karena_keer",
			missions = karena_keer_missions
		},
		{
			spawnData = { npcTemplate = "shalera_the_hutt", x = -19.21, z = -0.895, y = 22.01, direction = 239.1, cellID = 2625364, position = STAND },
			worldPosition = { x = -5239, y = -2509 },
			npcNumber = 4,
			stfFile = "@static_npc/corellia/shalera",
			missions = shalera_missions
		}
	}

LadyHutt = ThemeParkLogic:new {
	npcMap = npcMapLadyHutt,
	className = "LadyHutt",
	screenPlayState = "lady_hutt_quest",
	planetName = "corellia",
	distance = 800
}

registerScreenPlay("LadyHutt", true)

lady_hutt_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LadyHutt
}

lady_hutt_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = LadyHutt
}