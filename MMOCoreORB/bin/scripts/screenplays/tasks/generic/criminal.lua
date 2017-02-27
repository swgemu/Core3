generic_criminal_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/shisa_decorative_s01.iff" }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/holocron_splinters_sith_s01.iff" }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/decryptor_broken_s01.iff" }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/speaker_s01.iff" }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/medallion_black_sun_s01.iff", itemName = "A Black Sun Medallion" }
			},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/shisa_decorative_s01.iff" }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/camera_s01.iff", itemName = "A Camera" }
			},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/decryptor_broken_s01.iff" }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/medallion_black_sun_s01.iff", itemName = "A Black Sun Medallion" }
			},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/holocron_splinters_sith_s01.iff" }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/key_electronic_s01.iff", itemName = "An Electronic Key" }
			},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/speaker_s01.iff" }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/medallion_black_sun_s01.iff", itemName = "A Black Sun Medallion" }
			},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/shisa_decorative_s01.iff" }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target_merchant", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/camera_s01.iff", itemName = "A Camera" }
			},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/decryptor_broken_s01.iff" }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target_noble", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/medallion_dark_jedi_s01.iff", itemName = "A Dark Jedi Medallion" }
			},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/holocron_splinters_sith_s01.iff" }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "criminal_target_rival", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/key_electronic_s01.iff", itemName = "An Electronic Key" }
			},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/speaker_s01.iff" }
			}
		},
	}

npcMapGenericCriminal =
	{
		{
			npcNumber = 1,
			stfFile = "@random_quest/criminal",
			missions = generic_criminal_missions
		}
	}

GenericCriminal = ThemeParkLogic:new {
	genericGiver = true,
	npcMap = npcMapGenericCriminal,
	className = "GenericCriminal",
	screenPlayState = "generic_criminal_quest",
	distance = 1000,
}

registerScreenPlay("GenericCriminal", true)

generic_criminal_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = GenericCriminal
}
generic_criminal_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = GenericCriminal
}
