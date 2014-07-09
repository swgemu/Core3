kormund_thrylle_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "reen_loruk", planetName = "tatooine", npcName = "Reen Loruk" }
			},
			secondarySpawns = {
				{ npcTemplate = "kormund_probot", planetName = "tatooine", npcName = "an Imperial Probot" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/kormund_thrylle_q1_needed.iff", itemName = "Datadisc" }
			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 100 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "rodius_tharn", planetName = "tatooine", npcName = "Rodius Tharn" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "stormtrooper", planetName = "tatooine", npcName = "a Stormtrooper" },
				{ npcTemplate = "stormtrooper", planetName = "tatooine", npcName = "a Stormtrooper" },
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 200 }
			}
		},
	}

npcMapKormundThrylle =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "kormund_thrylle", x = -1043.98, z = 10, y = -3530.5, direction = 221.746, cellID = 0, position = STAND },
			worldPosition = { x = -1044, y = -3531 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/kormund_thrylle",
			missions = kormund_thrylle_missions
		},
	}

KormundThrylle = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapKormundThrylle,
	className = "KormundThrylle",
	screenPlayState = "kormund_thrylle_quest",
	distance = 800,
	faction = FACTIONREBEL

}

registerScreenPlay("KormundThrylle", true)

kormund_thrylle_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = KormundThrylle
}
kormund_thrylle_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = KormundThrylle
}