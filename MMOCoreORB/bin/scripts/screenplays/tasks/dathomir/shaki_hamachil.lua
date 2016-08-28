shaki_hamachil_missions =
{
	{
		missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "shaki_smuggler_q1", npcName = "smuggler" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/shaki_hamachil_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
				{ rewardType = "faction",faction = "imperial", amount = 5 }
			}
	},
	{
		missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "shaki_imperial_q2", npcName = "an Imperial Second Lieutenant" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/shaki_hamachil_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 150 },
				{ rewardType = "faction",faction = "imperial",amount = 5 }

			}
		}

}



npcMapShakiHamachil =
	{
		{ spawnData = { npcTemplate = "shaki_hamachil", x = -101.049, z = 18, y = -1542.62, direction = 0, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/dathomir/dathomir_researchoutpost_shaki_hamachil",
			missions = shaki_hamachil_missions
		}
	}

ShakiHamachil = ThemeParkLogic:new {
	npcMap = npcMapShakiHamachil,
	className = "ShakiHamachil",
	screenPlayState = "shaki_hamachil_quest",
	planetName = "dathomir",
	distance = 1200,
	faction = FACTIONIMPERIAL
}

registerScreenPlay("ShakiHamachil", true)

shaki_hamachil_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ShakiHamachil
}

shaki_hamachil_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ShakiHamachil
}
