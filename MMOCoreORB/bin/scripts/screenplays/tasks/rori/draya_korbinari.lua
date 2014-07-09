draya_korbinari_missions =
{
	{
		missionType = "assassinate",
		primarySpawns =
		{ 
			{ npcTemplate = "tusk_cat", planetName = "rori", npcName = "a Tusk Cat" }
		},
		secondarySpawns =
		{

		},
		itemSpawns =
		{

		}, 
		rewards =
		{ 
			{ rewardType = "credits", amount = 50 },
			{ rewardType = "faction", faction = "naboo", amount = 5 }
		}
	},
	{
		missionType = "escort",
		primarySpawns =
		{
			{ npcTemplate = "draya_korbinari_thief", planetName = "rori", npcName = "a Thief" }
		},
		secondarySpawns =
		{

		}, 
		itemSpawns = 
		{

		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 30 },
			{ rewardType = "faction", faction = "naboo", amount = 5 }
		}
	},
	{
		missionType = "confiscate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "draya_korbinari_smuggler", planetName = "rori", npcName = "a Smuggler" }	
		},
		secondarySpawns =
		{

		}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/draya_korbinari_q3_needed.iff", itemName = "" }
		},
		rewards = 
		{
			{ rewardType = "credits", amount = 30 },
			{ rewardType = "faction", faction = "naboo", amount = 5 }
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "draya_korbinari_bounty_hunter", planetName = "rori", npcName = "a Bounty Hunter" }	
		}, 
		secondarySpawns =
		{

		}, 
		itemSpawns = 
		{

		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 40 },
			{ rewardType = "faction", faction = "naboo", amount = 5 }
		}
	}
}

npcMapDrayaKorbinari = 
{ 
	{ 
		spawnData = { planetName = "rori", npcTemplate = "draya_korbinari", x = -18, z = 0, y = 18, direction = 120, cellID = 4635705, position = STAND },
		worldPosition = { x = 5305, y = 5859 }, 
		npcNumber = 1,
		stfFile = "@static_npc/rori/rori_restuss_draya_korbinari",
		missions = draya_korbinari_missions
	},
}

DrayaKorbinari = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapDrayaKorbinari,
	permissionMap = {},
	className = "DrayaKorbinari",
	screenPlayState = "draya_korbinari_quest",
	distance = 500,
}

registerScreenPlay("DrayaKorbinari", true)

draya_korbinari_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = DrayaKorbinari
}
draya_korbinari_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = DrayaKorbinari
}
