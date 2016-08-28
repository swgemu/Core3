om_aynat_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "om_aynat_escort", npcName = "a Sand Dragon Fresher Rep" }
			},
			secondarySpawns = {},
			itemSpawns = {
			},
			rewards =
			{
				{ rewardType = "loot", lootGroup = "task_reward_om_aynat_q1" }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "om_aynat_escort", npcName = "Om's Legal Advocate" }
			},
			secondarySpawns = {},
			itemSpawns = {
			},
			rewards =
			{
				{ rewardType = "loot", lootGroup = "task_reward_om_aynat_q2" }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "om_aynat_chef", npcName = "Fallen Star Hotel Chef" }
			},
			secondarySpawns = {},
			itemSpawns = {
			},
			rewards =
			{
				{ rewardType = "loot", lootGroup = "task_reward_om_aynat_q3" }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "om_aynat_escort", npcName = "Star-Crossed Lover" }
			},
			secondarySpawns = {},
			itemSpawns = {
			},
			rewards =
			{
				{ rewardType = "loot", lootGroup = "task_reward_om_aynat_q4" }
			}
		},
	}

npcMapOmAynat =
	{
		{
			spawnData = { npcTemplate = "om_aynat", x = 1615.5, z = 7.0, y = 2956.4, direction = 168, cellID = 0, position = SIT },
			npcNumber = 1,
			stfFile = "@static_npc/tatooine/om_aynat",
			missions = om_aynat_missions
		},
	}

OmAynat = ThemeParkLogic:new {
	npcMap = npcMapOmAynat,
	className = "OmAynat",
	screenPlayState = "om_aynat_task",
	planetName = "tatooine",
	distance = 800
}

registerScreenPlay("OmAynat", true)

om_aynat_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = OmAynat
}
om_aynat_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = OmAynat
}
