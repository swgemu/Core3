talon_karrde_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "ara_niorri", npcName = "Ara Niorri" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "male_rodian_thug_low", npcName = "a thug" }
			},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/talon_karrde_q1_needed.iff", itemName = "Official Travel Documents" }
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
				{ npcTemplate = "vralla", npcName = "Vralla" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 400 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "talon_courier", npcName = "a Hutt courier" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "jabba_thug", npcName = "a Hutt thug" },
				{ npcTemplate = "jabba_thug", npcName = "a Hutt thug" }
			},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/talon_karrde_q3_needed.iff", itemName = "Package" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 800 }
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "talon_bcb_courier", npcName = "a BCB courier" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "jabba_thug", npcName = "a Hutt thug" }
			},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/talon_karrde_q4_needed.iff", itemName = "Virus Flask" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 1600 }
			}
		}
	}

npcMapTalonKarrde =
	{
		{
			spawnData = { npcTemplate = "talon_karrde", x = 5.617, z = -0.895, y = 20.963, direction = -175, cellID = 3075433, position = STAND },
			worldPosition = { x = 3255, y = 5308 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/talon_karrde",
			missions = talon_karrde_missions
		}
	}

TalonKarrde = ThemeParkLogic:new {
	npcMap = npcMapTalonKarrde,
	className = "TalonKarrde",
	screenPlayState = "talon_karrde_quest",
	planetName = "corellia",
	distance = 800
}

registerScreenPlay("TalonKarrde", true)

talon_karrde_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = TalonKarrde
}

talon_karrde_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = TalonKarrde
}