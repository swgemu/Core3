kormund_thrylle_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "reen_loruk", npcName = "Reen Loruk" }
			},
			secondarySpawns = {
				{ npcTemplate = "kormund_probot", npcName = "an Imperial Probot" },
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
				{ npcTemplate = "rodius_tharn", npcName = "Rodius Tharn" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "stormtrooper", npcName = "a Stormtrooper" },
				{ npcTemplate = "stormtrooper", npcName = "a Stormtrooper" },
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
			spawnData = { npcTemplate = "kormund_thrylle", x = -1043.98, z = 10, y = -3530.5, direction = 221.746, cellID = 0, position = STAND },
			worldPosition = { x = -1044, y = -3531 },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/kormund_thrylle",
			missions = kormund_thrylle_missions
		},
	}

KormundThrylle = ThemeParkLogic:new {
	npcMap = npcMapKormundThrylle,
	className = "KormundThrylle",
	screenPlayState = "kormund_thrylle_quest",
	planetName = "tatooine",
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