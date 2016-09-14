jusani_zhord_missions =
	{
		{--*The dialog options npc_5_1 and npc_6_1  don't seem to be achievable when conversing with Jusani???
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "exec_quest_jusani", npcName = "a CSA Officer" }
			},--*Because of the way we can't converse (yet?) with 'ATTACKABLE' targets, the dialog option of player_more_1_1
					--doesn't seem to be achievable.
			secondarySpawns =
			{
				{ npcTemplate = "thug", npcName = "Corporate Bodyguard" },
				{ npcTemplate = "thug", npcName = "Corporate Bodyguard" }
			},
			itemSpawns = 
			{
				{ itemTemplate = "object/tangible/mission/quest_item/jusani_zhord_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 500 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "protoman_quest_jusani", npcName = "" }
			},
			secondarySpawns =
			{
			},
			itemSpawns = 
			{--*The string-file dialog clearly states there should be a 'confiscate' LOOT ITEM (re: "Ion Engine Prototype")
				--but unfortunately SOE neglected to create the _q2_needed.iff , so i changed the mission to be 'assassinate'
				--type mission w/ guaranteed npc loot, so it would function properly and match what Jusani's dialog is.
			},
			rewards =
			{
				{ rewardType = "credits", amount = 1000 },
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