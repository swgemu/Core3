sigrix_slix_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "cenik", planetName = "talus", npcName = "Cenik (a Spice Collective courier)" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "sigrix_thug", planetName = "talus", npcName = "a Thug" },
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
				{ npcTemplate = "wooral", planetName = "talus", npcName = "Wooral" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "sigrix_selonian_warrior", planetName = "talus", npcName = "a Selonian Warrior" },
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
			spawnData = { planetName = "talus", npcTemplate = "sigrix_slix", x = 17.2, z = -0.9, y = -6.8, direction = 25, cellID = 4265375, position = STAND },
			worldPosition = { x = 4302, y = 5310 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_nashal_sigrix_slix",
			missions = sigrix_slix_missions
		},
	}

SigrixSlix = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapSigrixSlix,
	className = "SigrixSlix",
	screenPlayState = "sigrix_slix_quest",
	distance = 800
}

registerScreenPlay("SigrixSlix", true)

sigrix_slix_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = SigrixSlix
}
sigrix_slix_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = SigrixSlix
}