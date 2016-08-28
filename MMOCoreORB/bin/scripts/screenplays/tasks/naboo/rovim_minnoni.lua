rovim_minnoni_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "zazzi", npcName = "Zazzi" }
			},
			secondarySpawns = {},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/rovim_minnoni_q1_needed.iff", itemName = "Signal Finder" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},

-- Quests 2 and 3 disabled due to missing strings in string file 
--[[
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "bevon_cordh", npcName = "Bevon Cordh" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "nion_lipto", npcName = "Ni'on Lipto" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		}
--]]
	}

npcMapRovinMinnoni =
	{
		{
			spawnData = { npcTemplate = "rovim_minnoni", x = -5551.9, z = -150, y = -51.5, direction = -49, cellID = 0, position = STAND },
			worldPosition = { x = -5551, y = -51 },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/rovim_minnoni",
			missions = rovim_minnoni_missions
		}
	}

RovinMinnoni = ThemeParkLogic:new {
	npcMap = npcMapRovinMinnoni,
	className = "RovinMinnoni",
	screenPlayState = "rovim_minnoni_quest",
	planetName = "naboo",
	distance = 600
}

registerScreenPlay("RovinMinnoni", true)

rovim_minnoni_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = RovinMinnoni
}
rovim_minnoni_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = RovinMinnoni
}