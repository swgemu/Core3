kritus_morven_missions =
{
	{
		missionType = "retrieve",
		primarySpawns =
		{
			{ npcTemplate = "borvos_courier_quest_kritus", npcName = "Fekk Trunkel" }
		},
		secondarySpawns = {},
		itemSpawns = {
			{ itemTemplate = "object/tangible/mission/quest_item/kritus_morven_q1_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 50 }
		}
	},
	{
		missionType = "deliver",
		primarySpawns =
		{
			{ npcTemplate = "security_officer_quest_kritus", npcName = "a Naboo Security Officer" }
		},
		secondarySpawns =
		{
			{npcTemplate = "borvos_thug", npcName = ""},
			{npcTemplate = "borvos_thug", npcName = ""}
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/kritus_morven_q2_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 100 }
		}
	},
	{
		missionType = "deliver",
		primarySpawns =
		{
			{ npcTemplate = "security_officer_quest_kritus", npcName = "Dagrus Rhine" }
		},
		secondarySpawns =
		{
			{npcTemplate = "rsf_security_officer", npcName = ""},
			{npcTemplate = "rsf_security_officer", npcName = ""}
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/kritus_morven_q3_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 150 }
		}
	},
	{
		missionType = "escort",
		primarySpawns =
		{
			{ npcTemplate = "borvos_scientist_quest_kritus", npcName = "Borvo's Researcher" }
		},
		secondarySpawns =
		{
			{ npcTemplate = "borvos_thug", npcName = "" },
			{ npcTemplate = "borvos_thug", npcName = "" }
		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "credits", amount = 200 }
		}
	},
	{
		missionType = "confiscate",
		primarySpawns =
		{
			{ npcTemplate = "borvos_courier_quest_kritus2", npcName = "Dekker" }
		},
		secondarySpawns =
		{
		},
		itemSpawns =
		{
			{ itemTemplate = "object/tangible/mission/quest_item/kritus_morven_q5_needed.iff", itemName = "" }
		},
		rewards =
		{
			{ rewardType = "credits", amount = 250 }
		}
	}
}

npcMapKritusMorven =
{
	{
		spawnData = { npcTemplate = "kritus_morven", x = -5.3, z = -4.9, y = -8.9, direction = -41, cellID = 1685077, position = STAND },
		worldPosition = { x = 1614.1, y = 2503.7 },
		npcNumber = 1,
		stfFile = "@static_npc/naboo/kritus_morven",
		missions = kritus_morven_missions
	},
}

KritusMorven = ThemeParkLogic:new {
	npcMap = npcMapKritusMorven,
	className = "KritusMorven",
	screenPlayState = "kritus_morven_task",
	planetName = "naboo",
	distance = 1000,
}

registerScreenPlay("KritusMorven", true)

kritus_morven_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = KritusMorven
}
kritus_morven_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = KritusMorven
}
