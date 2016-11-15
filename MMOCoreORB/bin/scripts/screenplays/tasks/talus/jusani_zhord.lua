jusani_zhord_missions =
	{
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "exec_quest_jusani", npcName = "a CSA Officer" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "teras_kasi_master", npcName = "Corporate Bodyguard" },
				{ npcTemplate = "teras_kasi_master", npcName = "Corporate Bodyguard" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/jusani_zhord_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 50 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "protoman_quest_jusani", npcName = "" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/hyperdrive_part_s01.iff", itemName = "An Ion Engine Prototype" }
				--Unfortunately SOE neglected to create the _q2_needed.iff ^
			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		}
	}

npcMapJusaniZhord =
	{
		{
			spawnData = { npcTemplate = "jusani_zhord", x = 19.9, z = 1.3, y = -1.0, direction = -94, cellID = 4265423, position = STAND },
			worldPosition = { x = 4328, y = 5144 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_nashal_jusani_zhord",
			missions = jusani_zhord_missions
		},
	}

JusaniZhord = ThemeParkLogic:new {
	npcMap = npcMapJusaniZhord,
	className = "JusaniZhord",
	screenPlayState = "jusani_zhord_tasks",
	planetName = "talus",
	distance = 900
}

registerScreenPlay("JusaniZhord", true)

jusani_zhord_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = JusaniZhord
}
jusani_zhord_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = JusaniZhord
}
