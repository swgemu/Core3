generic_scientist_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "scientist_target_robber", npcName = "random" }
			},
			secondarySpawns = 
			{
				{ npcTemplate = "thug", npcName = "a Thug" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/artifact_rare_s01.iff", itemName = "A Rare Artifact" }
			},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/insects_rare_s01.iff" }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "scientist_target_spy", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/cage_s01.iff", itemName = "An Empty Cage" }
			},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/picture_handheld_s01.iff" }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "criminal", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/insects_rare_s01.iff" }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "scientist_target_crazed_scientist", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/picture_handheld_s01.iff" }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "scientist_target_scientist", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/insects_rare_s01.iff" }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "scientist_target_scientist", npcName = "random" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/picture_handheld_s01.iff" }
			}
		}
	}

npcMapGenericScientist =
	{
		{
			npcNumber = 1,
			stfFile = "@random_quest/scientist",
			missions = generic_scientist_missions
		}
	}

GenericScientist = ThemeParkLogic:new {
	genericGiver = true,
	npcMap = npcMapGenericScientist,
	className = "GenericScientist",
	screenPlayState = "generic_scientist_quest",
	distance = 1000,
}

registerScreenPlay("GenericScientist", true)

generic_scientist_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = GenericScientist
}
generic_scientist_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = GenericScientist
}
