vana_sage_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "vana_pilot", npcName = "Pilot" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "vana_thug", npcName = "Thug" },
				{ npcTemplate = "vana_thug", npcName = "Thug" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/vana_sage_q1_needed.iff", itemName = "Bribe" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "vana_captain", npcName = "Captain Vanool" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "gungan_outcast", npcName = "Gungan Raider" },
				{ npcTemplate = "gungan_outcast", npcName = "Gungan Raider" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "gungan_leader", npcName = "Gungan Leader" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "gungan_thug", npcName = "Gungan Raider" },
				{ npcTemplate = "gungan_thug", npcName = "Gungan Raider" },
				{ npcTemplate = "gungan_thug", npcName = "Gungan Raider" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 150 },
			}
		},
	}

npcMapVanaSage =
	{
		{
			spawnData = { npcTemplate = "vana_sage", x = 1276.1, z = 13.0, y = 2744.8, direction = -82, cellID = 0, position = STAND },
			worldPosition = { x = 1276, y = 2744 },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/vana_sage",
			missions = vana_sage_missions
		}
	}

VanaSage = ThemeParkLogic:new {
	npcMap = npcMapVanaSage,
	className = "VanaSage",
	screenPlayState = "vana_sage_quest",
	planetName = "naboo",
	distance = 600
}

registerScreenPlay("VanaSage", true)

vana_sage_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = VanaSage
}
vana_sage_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = VanaSage
}