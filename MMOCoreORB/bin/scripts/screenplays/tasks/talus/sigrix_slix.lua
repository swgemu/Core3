sigrix_slix_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "cenik", npcName = "Cenik (a Spice Collective courier)" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "sigrix_thug", npcName = "a Thug" },
			},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/sigrix_slix_q1_needed.iff", itemName = "Um... Ambient Wildlife Calls... yeah." }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "wooral", npcName = "Wooral" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "sigrix_selonian_warrior", npcName = "a Selonian Warrior" },
			},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/sigrix_slix_q2_needed.iff", itemName = "Selonian Verovakin" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 30 },
			}
		},
	}

npcMapSigrixSlix =
	{
		{
			spawnData = { npcTemplate = "sigrix_slix", x = 17.2, z = -0.9, y = -6.8, direction = 25, cellID = 4265375, position = STAND },
			worldPosition = { x = 4302, y = 5310 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_nashal_sigrix_slix",
			missions = sigrix_slix_missions
		},
	}

SigrixSlix = ThemeParkLogic:new {
	npcMap = npcMapSigrixSlix,
	className = "SigrixSlix",
	screenPlayState = "sigrix_slix_quest",
	planetName = "talus",
	distance = 800
}

registerScreenPlay("SigrixSlix", true)

sigrix_slix_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = SigrixSlix
}
sigrix_slix_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = SigrixSlix
}