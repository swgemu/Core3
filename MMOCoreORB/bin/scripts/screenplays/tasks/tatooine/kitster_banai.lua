kitster_banai_missions =
{
	{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "jawa_leader", planetName = "tatooine", npcName = "" }
		}, 
		secondarySpawns =
		{
			{ npcTemplate = "jawa_henchman", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "jawa_henchman", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "jawa_henchman", planetName = "tatooine", npcName = "" }
		},
		itemSpawns =
		{

		}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 1500 },
			{ rewardType = "faction", faction = "jawa", amount = -100 },
			{ rewardType = "faction", faction = "tusken_raider", amount = 50 },
			{ rewardType = "loot", lootGroup = "task_reward_kitster_banai_helmet" }
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "deeng", planetName = "tatooine", npcName = "Deeng" }
		}, 
		secondarySpawns =
		{

		}, 
		itemSpawns = 
		{

		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 1800 },
			{ rewardType = "faction", faction = "thug", amount = -160 },
			{ rewardType = "faction", faction = "townsperson", amount = 80 }
		}
	},
	{
		missionType = "assassinate", 
		primarySpawns = 
		{ 
			{ npcTemplate = "sont_toipo", planetName = "tatooine", npcName = "Sont Toipo" }
		}, 
		secondarySpawns =
		{
			{ npcTemplate = "moisture_farmer", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "moisture_farmer", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "moisture_farmer", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "moisture_farmer", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "moisture_farmer", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "moisture_farmer", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "moisture_farmer", planetName = "tatooine", npcName = "" },
			{ npcTemplate = "moisture_farmer", planetName = "tatooine", npcName = "" }
		}, 
		itemSpawns = 
		{

		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 1500 },
			{ rewardType = "faction", faction = "thug", amount = -160 },
			{ rewardType = "faction", faction = "townsperson", amount = 80 },
			{ rewardType = "loot", lootGroup = "task_reward_kitster_banai_droid_brain" }
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "krin_vel", planetName = "tatooine", npcName = "Krin Vel" }
		}, 
		secondarySpawns =
		{

		}, 
		itemSpawns = 
		{

		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 2500 }
		}
	},
	{
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "thermal_det", planetName = "tatooine", npcName = "Thermal Det" }
		}, 
		secondarySpawns =
		{

		}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/kitster_banai_q5_needed.iff", itemName = "" }
		}, 
		rewards = 
		{
			{ rewardType = "credits", amount = 2500 }
		}
	}
}

npcMapKitsterBanai = 
{ 
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "kitster_banai", x = -2887, z = 5, y = 2494, direction = 330, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/tatooine/kitster_banai",
		missions = kitster_banai_missions
	},
}

KitsterBanai = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapKitsterBanai,
	permissionMap = {},
	className = "KitsterBanai",
	screenPlayState = "kitster_banai_quest",
	distance = 600
}

registerScreenPlay("KitsterBanai", true)

kitster_banai_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = KitsterBanai
}
kitster_banai_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = KitsterBanai
}