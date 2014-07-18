thrackan_sal_solo_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "selonian_separatist", planetName = "corellia", npcName = "a Selonian terrorist" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "jermo_tharrn", planetName = "corellia", npcName = "Jermo Tharrn" }
			},
			secondarySpawns =	
			{
				{ npcTemplate = "selonian_sentinel", planetName = "corellia", npcName = "a Selonian sentinel" },
				{ npcTemplate = "selonian_sentinel", planetName = "corellia", npcName = "a Selonian sentinel" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "tormyll_fassoola", planetName = "corellia", npcName = "Tormyll Fassoola" }
			},
			secondarySpawns =	{},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/thrackan_salsolo_q3_needed.iff", itemName = "Diktat's Death Squad" }
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
				{ npcTemplate = "selonian_champion", planetName = "corellia", npcName = "a Selonian leader" }
			},
			secondarySpawns =	
			{
				{ npcTemplate = "selonian_sentinel", planetName = "corellia", npcName = "a Selonian sentinel" },
				{ npcTemplate = "selonian_sentinel", planetName = "corellia", npcName = "a Selonian sentinel" },
				{ npcTemplate = "selonian_sentinel", planetName = "corellia", npcName = "a Selonian sentinel" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 800 }
			}
		}
	}

npcMapThrackanSalSolo =
	{
		{
			spawnData = { planetName = "corellia", npcTemplate = "thrackan_sal_solo", x = 0.4, z = 1.2, y = 0.8, direction = 0, cellID = 1855483, position = STAND },
			worldPosition = { x = -275, y = -4720 },
			npcNumber = 1,
			stfFile = "@static_npc/corellia/thrackan_sal_solo",
			missions = thrackan_sal_solo_missions
		}
	}

ThrackanSalSolo = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapThrackanSalSolo,
	className = "ThrackanSalSolo",
	screenPlayState = "thrackan_sal_solo_quest",
	distance = 800
}

registerScreenPlay("ThrackanSalSolo", true)

thrackan_sal_solo_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ThrackanSalSolo
}

thrackan_sal_solo_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ThrackanSalSolo
}