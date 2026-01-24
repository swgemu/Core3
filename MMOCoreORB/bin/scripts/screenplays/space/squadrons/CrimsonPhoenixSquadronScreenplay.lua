local Logger = require("utils.logger")
local SpaceHelpers = require("utils.space_helpers")

--[[

	Crimson Phoenix Squadron Missions (Rebel - Tatooine-based)

]]

--[[
	Tier 1 -- Eker Main Missions (Tatooine)
]]

-- Mission 1: Patrol with surprise attack
patrol_tatooine_rebel_1 = SpacePatrolScreenplay:new {
	className = "patrol_tatooine_rebel_1",

	questName = "tatooine_rebel_1",
	questType = "patrol",

	questZone = "space_tatooine",

	creditReward = 100,

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "tatooine_rebel_1",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 2,
	sideQuestDelay = 20,

	patrolPoints = {
		{patrolPointName = "rebel_tatooine_patrol_1", x = -3000, z = -2000, y = 2200, patrolNumber = 1, radius = 150},
		{patrolPointName = "rebel_tatooine_patrol_2", x = -2500, z = -2500, y = 2800, patrolNumber = 2, radius = 150},
		{patrolPointName = "rebel_tatooine_patrol_3", x = -2000, z = -2200, y = 3200, patrolNumber = 3, radius = 150},
	},
}

registerScreenPlay("patrol_tatooine_rebel_1", true)

destroy_surpriseattack_tatooine_rebel_1 = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_tatooine_rebel_1",

	questName = "tatooine_rebel_1",
	questType = "destroy_surpriseattack",

	questZone = "space_tatooine",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "patrol_tatooine_rebel_1",
	parentQuestType = "patrol",
	parentQuestName = "tatooine_rebel_1",

	surpriseAttackShips = {
		zone = "space_tatooine",
		spawns = {{count = 2, shipName = "imp_tie_fighter_tier1"}, {count = 2, shipName = "imp_tie_light_tier1"}},
	},
}

registerScreenPlay("destroy_surpriseattack_tatooine_rebel_1", true)

-- Mission 2: Patrol with escort
patrol_tatooine_rebel_2 = SpacePatrolScreenplay:new {
	className = "patrol_tatooine_rebel_2",

	questName = "tatooine_rebel_2",
	questType = "patrol",

	questZone = "space_tatooine",

	creditReward = 200,

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestName = "tatooine_rebel_2",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 2,
	sideQuestDelay = 20,

	patrolPoints = {
		{patrolPointName = "rebel_tatooine_patrol2_1", x = -2800, z = -3000, y = 1800, patrolNumber = 1, radius = 150},
		{patrolPointName = "rebel_tatooine_patrol2_2", x = -2300, z = -3500, y = 2400, patrolNumber = 2, radius = 150},
		{patrolPointName = "rebel_tatooine_patrol2_3", x = -1800, z = -3200, y = 2800, patrolNumber = 3, radius = 150},
	},
}

registerScreenPlay("patrol_tatooine_rebel_2", true)

escort_tatooine_rebel_2 = SpaceEscortScreenplay:new {
	className = "escort_tatooine_rebel_2",

	questName = "tatooine_rebel_2",
	questType = "escort",

	questZone = "space_tatooine",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "patrol_tatooine_rebel_2",
	parentQuestType = "patrol",
	parentQuestName = "tatooine_rebel_2",

	escortShips = {"freighterheavy_tier1"},

	escortPoints = {
		{patrolPointName = "rebel_tatooine_escort_1", zoneName = "space_tatooine", x = -3000, z = -2500, y = 3000, escortNumber = 1, radius = 250},
		{patrolPointName = "rebel_tatooine_escort_2", zoneName = "space_tatooine", x = -2500, z = -2800, y = 3500, escortNumber = 2, radius = 250},
		{patrolPointName = "rebel_tatooine_escort_3", zoneName = "space_tatooine", x = -2000, z = -3000, y = 4000, escortNumber = 3, radius = 250},
	},

	attackDelay = 90,

	attackShips = {
		{"imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_light_tier1"},
	}
}

registerScreenPlay("escort_tatooine_rebel_2", true)

-- Mission 3: Destroy
destroy_tatooine_rebel_3 = SpaceDestroyScreenplay:new {
	className = "destroy_tatooine_rebel_3",

	questName = "tatooine_rebel_3",
	questType = "destroy",

	questZone = "space_tatooine",

	creditReward = 500,

	sideQuest = false,
	sideQuestType = "",

	killsRequired = 4,

	shipLocations = {
		{patrolPointName = "imperial_tatooine_1", x = -1500, z = -2000, y = 2500},
		{patrolPointName = "imperial_tatooine_2", x = -2000, z = -1500, y = 3000},
	},

	shipTypes = {
		"imp_tie_fighter_tier1", "imp_tie_fighter_tier2", "imp_tie_light_tier1", "imp_tie_light_tier2",
		"imp_tie_bomber_tier1", "imp_tie_bomber_tier2",
	},
}

registerScreenPlay("destroy_tatooine_rebel_3", true)

-- Mission 4: Assassinate
assassinate_tatooine_rebel_4 = SpaceAssassinateScreenplay:new {
	className = "assassinate_tatooine_rebel_4",

	questType = "assassinate",
	questName = "tatooine_rebel_4",

	questZone = "space_tatooine",

	creditReward = 1000,
	itemReward = {
		{species = {-1}, item = "object/tangible/ship/components/armor/arm_mission_reward_rebel_incom_ultralight.iff"},
	},

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 6,
	failTimer = 20,

	assassinateSpawns = {
		target = "imp_tie_advanced_tier2",
		escorts = {"imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_interceptor_tier1"},
	},

	targetPatrols = {
		{patrolPointName = "rebel_tatooine_assassinate_1", x = -2500, z = -1800, y = 2800},
		{patrolPointName = "rebel_tatooine_assassinate_2", x = -1800, z = -2200, y = 3200},
	},
}

registerScreenPlay("assassinate_tatooine_rebel_4", true)

-- Eker Duty Missions
destroy_duty_tatooine_rebel_6 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_tatooine_rebel_6",

	questName = "tatooine_rebel_6",
	questType = "destroy_duty",

	questZone = "space_tatooine",

	creditReward = 100,

	sideQuest = false,
	sideQuestType = "",

	totalLevels = 2,
	totalRounds = 2,
	totalWaves = 2,

	minDistance = 12500,
	maxDistance = 17500,

	bossShip = "imp_tie_advanced_tier1",
	shipTypes = {
		{"imp_tie_fighter_tier1", "imp_tie_light_tier1"},
	},
}

registerScreenPlay("destroy_duty_tatooine_rebel_6", true)

escort_duty_tatooine_rebel_7 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_tatooine_rebel_7",

	questName = "tatooine_rebel_7",
	questType = "escort_duty",

	questZone = "space_tatooine",

	creditReward = 1000,

	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"freighterheavy_tier1", "freighterlight_tier1", "freightermedium_tier1"},

	escortPoints = {
		{patrolPointName = "rebel_tatooine_escort_duty_1", zoneName = "space_tatooine", x = -3000, z = -2500, y = 3000, escortNumber = 1, radius = 250},
		{patrolPointName = "rebel_tatooine_escort_duty_2", zoneName = "space_tatooine", x = -2500, z = -2800, y = 3500, escortNumber = 2, radius = 250},
		{patrolPointName = "rebel_tatooine_escort_duty_3", zoneName = "space_tatooine", x = -2000, z = -3000, y = 4000, escortNumber = 3, radius = 250},
	},

	attackDelay = 90,

	attackShips = {
		{"imp_tie_fighter_tier1", "imp_tie_light_tier1"},
		{"imp_tie_bomber_tier1", "imp_tie_interceptor_tier1"},
	},

	creditKillBonus = 100,
}

registerScreenPlay("escort_duty_tatooine_rebel_7", true)

--[[
	Tier 2 -- Socuna Main Missions (Tatooine)
]]

-- Mission 1: Destroy
destroy_socuna_rebel_1 = SpaceDestroyScreenplay:new {
	className = "destroy_socuna_rebel_1",

	questName = "rebel_destroy_03",
	questType = "destroy",

	questZone = "space_tatooine",

	creditReward = 5000,

	sideQuest = false,
	sideQuestType = "",

	killsRequired = 6,

	shipLocations = {},

	shipTypes = {
		"imp_tie_fighter_tier2", "imp_tie_fighter_tier3", "imp_tie_bomber_tier2", "imp_tie_bomber_tier3",
	},
}

registerScreenPlay("destroy_socuna_rebel_1", true)

-- Mission 2: Escort
escort_socuna_rebel_2 = SpaceEscortScreenplay:new {
	className = "escort_socuna_rebel_2",

	questName = "rebel_escort_01",
	questType = "escort",

	questZone = "space_tatooine",

	creditReward = 5000,

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"freighterheavy_tier2"},

	escortPoints = {
		{patrolPointName = "socuna_escort_1", zoneName = "space_tatooine", x = -2163, z = 956, y = 4991, escortNumber = 1, radius = 250},
		{patrolPointName = "socuna_escort_2", zoneName = "space_tatooine", x = -637, z = -295, y = 4770, escortNumber = 2, radius = 250},
		{patrolPointName = "socuna_escort_3", zoneName = "space_tatooine", x = 2043, z = -1230, y = 5414, escortNumber = 3, radius = 250},
	},

	attackDelay = 180,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_bomber_tier2"},
	}
}

registerScreenPlay("escort_socuna_rebel_2", true)

-- Mission 3: Patrol
patrol_socuna_rebel_3 = SpacePatrolScreenplay:new {
	className = "patrol_socuna_rebel_3",

	questName = "rebel_patrol_02",
	questType = "patrol",

	questZone = "space_tatooine",

	creditReward = 5000,

	sideQuest = false,
	sideQuestType = "",

	patrolPoints = {
		{patrolPointName = "socuna_patrol_1", x = -2500, z = -2000, y = 3000, patrolNumber = 1, radius = 150},
		{patrolPointName = "socuna_patrol_2", x = -2000, z = -2500, y = 3500, patrolNumber = 2, radius = 150},
		{patrolPointName = "socuna_patrol_3", x = -1500, z = -2200, y = 4000, patrolNumber = 3, radius = 150},
	},
}

registerScreenPlay("patrol_socuna_rebel_3", true)

-- Mission 4: Destroy
destroy_socuna_rebel_4 = SpaceDestroyScreenplay:new {
	className = "destroy_socuna_rebel_4",

	questName = "rebel_destroy_02",
	questType = "destroy",

	questZone = "space_tatooine",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	killsRequired = 8,

	shipLocations = {},

	shipTypes = {
		"imp_tie_fighter_tier2", "imp_tie_fighter_tier3", "imp_tie_bomber_tier2", "imp_tie_bomber_tier3",
		"imp_tie_interceptor_tier2", "imp_tie_interceptor_tier3",
	},
}

registerScreenPlay("destroy_socuna_rebel_4", true)

-- Socuna Duty Missions
destroy_duty_socuna_rebel_1 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_socuna_rebel_1",

	questName = "tatooine_rebel_duty_6",
	questType = "destroy_duty",

	questZone = "space_tatooine",

	creditReward = 200,

	sideQuest = false,
	sideQuestType = "",

	totalLevels = 2,
	totalRounds = 2,
	totalWaves = 2,

	minDistance = 12500,
	maxDistance = 17500,

	bossShip = "imp_tie_advanced_tier3",
	shipTypes = {
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
	},
}

registerScreenPlay("destroy_duty_socuna_rebel_1", true)

escort_duty_socuna_rebel_2 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_socuna_rebel_2",

	questName = "tatooine_rebel_duty_7",
	questType = "escort_duty",

	questZone = "space_tatooine",

	creditReward = 1000,

	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"freighterheavy_tier2", "freighterlight_tier2"},

	escortPoints = {
		{patrolPointName = "socuna_escort_duty_1", zoneName = "space_tatooine", x = -3000, z = -2500, y = 3000, escortNumber = 1, radius = 250},
		{patrolPointName = "socuna_escort_duty_2", zoneName = "space_tatooine", x = -2500, z = -2800, y = 3500, escortNumber = 2, radius = 250},
	},

	attackDelay = 90,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_light_tier2"},
	},

	creditKillBonus = 100,
}

registerScreenPlay("escort_duty_socuna_rebel_2", true)

--[[
	Tier 3 -- Ulvawop Main Missions (Tatooine)
]]

-- Mission 1: Recovery
recovery_tatooine_rebel_tier3_1 = SpaceRecoveryScreenplay:new {
	className = "recovery_tatooine_rebel_tier3_1",

	questName = "tatooine_rebel_tier3_1",
	questType = "recovery",

	questZone = "space_tatooine",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 13,
	recoveryDelay = 15,

	recoverShip = "reb_xwing_tier3",
	recoveryConversationMobile = "object/mobile/shared_dressed_rebel_pilot_human_male_01.iff",

	escortShips = {},

	preRecoveryPoints = {
		{patrolPointName = "ulvawop_recovery_pre_1", zoneName = "space_tatooine", x = 2500, z = 1200, y = 3000, escortNumber = 1, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "ulvawop_recovery_1", zoneName = "space_tatooine", x = 3000, z = -600, y = 3500, escortNumber = 1, radius = 250},
	},

	attackDelay = 110,

	attackShips = {
		{"imp_tie_fighter_tier3", "imp_tie_bomber_tier3"},
	},
}

registerScreenPlay("recovery_tatooine_rebel_tier3_1", true)

-- Mission 2: Inspect
inspect_tatooine_rebel_tier3_2 = SpaceInspectScreenplay:new {
	className = "inspect_tatooine_rebel_tier3_2",

	questName = "tatooine_rebel_tier3_2",
	questType = "inspect",

	questZone = "space_tatooine",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	inspectTargets = {"imp_transport_tier3"},
	inspectCargo = "shipment_orders",

	targetLocation = {x = 3000, z = -2000, y = 2500},
}

registerScreenPlay("inspect_tatooine_rebel_tier3_2", true)

-- Mission 3: Delivery
delivery_tatooine_rebel_tier3_3 = SpaceDeliveryScreenplay:new {
	className = "delivery_tatooine_rebel_tier3_3",

	questName = "tatooine_rebel_tier3_3",
	questType = "delivery",

	questZone = "space_tatooine",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	deliveryShip = "reb_ywing_tier3",

	deliveryPoints = {
		{patrolPointName = "ulvawop_delivery_1", zoneName = "space_tatooine", x = 3000, z = -600, y = 3500, deliveryNumber = 1, radius = 250},
		{patrolPointName = "ulvawop_delivery_2", zoneName = "space_tatooine", x = 3500, z = -1000, y = 3000, deliveryNumber = 2, radius = 250},
	},
}

registerScreenPlay("delivery_tatooine_rebel_tier3_3", true)

-- Mission 4: Assassinate
assassinate_tatooine_rebel_tier3_4 = SpaceAssassinateScreenplay:new {
	className = "assassinate_tatooine_rebel_tier3_4",

	questType = "assassinate",
	questName = "tatooine_rebel_tier3_4",

	questZone = "space_tatooine",

	creditReward = 0,
	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 7,
	failTimer = 20,

	assassinateSpawns = {
		target = "imp_tie_advanced_tier4",
		escorts = {"imp_tie_fighter_tier3", "imp_tie_fighter_tier3", "imp_tie_interceptor_tier3"},
	},

	targetPatrols = {
		{patrolPointName = "ulvawop_assassinate_1", x = -500, z = -1000, y = 2500},
		{patrolPointName = "ulvawop_assassinate_2", x = 500, z = -500, y = 1500},
	},
}

registerScreenPlay("assassinate_tatooine_rebel_tier3_4", true)

--[[
	Tier 4 -- Ufwol Main Missions (Tatooine)
]]

-- Mission 1: Space Battle
space_battle_tatooine_rebel_tier4_1 = SpaceBattleScreenplay:new {
	className = "space_battle_tatooine_rebel_tier4_1",

	questName = "tatooine_rebel_tier4_1",
	questType = "space_battle",

	questZone = "space_tatooine",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	battleTime = 600,

	alliedShips = {
		{"reb_xwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4"},
	},

	enemyShips = {
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_bomber_tier4"},
	},
}

registerScreenPlay("space_battle_tatooine_rebel_tier4_1", true)

-- Mission 2: Recovery
recovery_tatooine_rebel_tier4_2 = SpaceRecoveryScreenplay:new {
	className = "recovery_tatooine_rebel_tier4_2",

	questName = "tatooine_rebel_tier4_2",
	questType = "recovery",

	questZone = "space_tatooine",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 13,
	recoveryDelay = 15,

	recoverShip = "reb_awing_tier4",
	recoveryConversationMobile = "object/mobile/shared_dressed_rebel_pilot_human_male_01.iff",

	escortShips = {},

	preRecoveryPoints = {
		{patrolPointName = "ufwol_recovery_pre_1", zoneName = "space_tatooine", x = 2500, z = 1200, y = 3000, escortNumber = 1, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "ufwol_recovery_1", zoneName = "space_tatooine", x = 3000, z = -600, y = 3500, escortNumber = 1, radius = 250},
	},

	attackDelay = 110,

	attackShips = {
		{"imp_tie_fighter_tier4", "imp_tie_bomber_tier4"},
	},
}

registerScreenPlay("recovery_tatooine_rebel_tier4_2", true)

-- Mission 3: Space Battle
space_battle_tatooine_rebel_tier4_3 = SpaceBattleScreenplay:new {
	className = "space_battle_tatooine_rebel_tier4_3",

	questName = "tatooine_rebel_tier4_3",
	questType = "space_battle",

	questZone = "space_tatooine",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	battleTime = 600,

	alliedShips = {
		{"reb_xwing_tier4", "reb_xwing_tier4", "reb_awing_tier4"},
	},

	enemyShips = {
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_bomber_tier4"},
	},
}

registerScreenPlay("space_battle_tatooine_rebel_tier4_3", true)

-- Mission 4: Assassinate
assassinate_tatooine_rebel_tier4_4 = SpaceAssassinateScreenplay:new {
	className = "assassinate_tatooine_rebel_tier4_4",

	questType = "assassinate",
	questName = "tatooine_rebel_tier4_4",

	questZone = "space_tatooine",

	creditReward = 0,
	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 7,
	failTimer = 20,

	assassinateSpawns = {
		target = "imp_tie_advanced_tier5",
		escorts = {"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_bomber_tier4"},
	},

	targetPatrols = {
		{patrolPointName = "ufwol_assassinate_1", x = -500, z = -1000, y = 2500},
		{patrolPointName = "ufwol_assassinate_2", x = 500, z = -500, y = 1500},
	},
}

registerScreenPlay("assassinate_tatooine_rebel_tier4_4", true)

-- Master Mission: Destroy
destroy_tatooine_rebel_master = SpaceDestroyScreenplay:new {
	className = "destroy_tatooine_rebel_master",

	questName = "tatooine_rebel_master",
	questType = "destroy",

	questZone = "space_tatooine",

	creditReward = 10000,

	sideQuest = false,
	sideQuestType = "",

	killsRequired = 10,

	shipLocations = {},

	shipTypes = {
		"imp_tie_fighter_tier4", "imp_tie_fighter_tier5", "imp_tie_bomber_tier4", "imp_tie_bomber_tier5",
		"imp_tie_interceptor_tier4", "imp_tie_interceptor_tier5", "imp_tie_advanced_tier4", "imp_tie_advanced_tier5",
	},
}

registerScreenPlay("destroy_tatooine_rebel_master", true)

-- Ufwol Duty Missions
escort_duty_tatooine_rebel_tier4_1 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_tatooine_rebel_tier4_1",

	questName = "tatooine_rebel_tier4_1",
	questType = "escort_duty",

	questZone = "space_tatooine",

	creditReward = 1000,

	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"freighterheavy_tier4", "freighterlight_tier4"},

	escortPoints = {
		{patrolPointName = "ufwol_escort_duty_1", zoneName = "space_tatooine", x = -3000, z = -2500, y = 3000, escortNumber = 1, radius = 250},
		{patrolPointName = "ufwol_escort_duty_2", zoneName = "space_tatooine", x = -2500, z = -2800, y = 3500, escortNumber = 2, radius = 250},
	},

	attackDelay = 90,

	attackShips = {
		{"imp_tie_fighter_tier4", "imp_tie_light_tier4"},
	},

	creditKillBonus = 100,
}

registerScreenPlay("escort_duty_tatooine_rebel_tier4_1", true)

destroy_duty_tatooine_rebel_tier4_1 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_tatooine_rebel_tier4_1",

	questName = "tatooine_rebel_tier4_1",
	questType = "destroy_duty",

	questZone = "space_tatooine",

	creditReward = 200,

	sideQuest = false,
	sideQuestType = "",

	totalLevels = 2,
	totalRounds = 2,
	totalWaves = 2,

	minDistance = 12500,
	maxDistance = 17500,

	bossShip = "imp_tie_advanced_tier4",
	shipTypes = {
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4"},
	},
}

registerScreenPlay("destroy_duty_tatooine_rebel_tier4_1", true)

recovery_duty_tatooine_rebel_tier4_1 = SpaceDutyDestroyScreenplay:new {
	className = "recovery_duty_tatooine_rebel_tier4_1",

	questName = "tatooine_rebel_tier4_1",
	questType = "recovery_duty",

	questZone = "space_tatooine",

	creditReward = 100,

	sideQuest = false,
	sideQuestType = "",

	totalLevels = 2,
	totalRounds = 2,
	totalWaves = 2,

	minDistance = 12500,
	maxDistance = 17500,

	bossShip = "imp_tie_advanced_tier4",
	shipTypes = {"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"},
}

registerScreenPlay("recovery_duty_tatooine_rebel_tier4_1", true)

rescue_duty_tatooine_rebel_tier4_1 = SpaceDutyDestroyScreenplay:new {
	className = "rescue_duty_tatooine_rebel_tier4_1",

	questName = "tatooine_rebel_tier4_1",
	questType = "rescue_duty",

	questZone = "space_tatooine",

	creditReward = 200,

	sideQuest = false,
	sideQuestType = "",

	totalLevels = 2,
	totalRounds = 2,
	totalWaves = 2,

	minDistance = 12500,
	maxDistance = 17500,

	bossShip = "imp_tie_advanced_tier4",
	shipTypes = {
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4"},
	},
}

registerScreenPlay("rescue_duty_tatooine_rebel_tier4_1", true)

--[[

	CrimsonPhoenixSquadronScreenplay

]]

CrimsonPhoenixSquadronScreenplay = ScreenPlay:new {
	screenplayName = "CrimsonPhoenixSquadronScreenplay",

	-- Tier 1 (Eker)
	QUEST_STRING_1 = {type = "patrol", name = "tatooine_rebel_1"},
	QUEST_STRING_1_SIDE = {type = "destroy_surpriseattack", name = "tatooine_rebel_1"},
	QUEST_STRING_2 = {type = "patrol", name = "tatooine_rebel_2"},
	QUEST_STRING_2_SIDE = {type = "escort", name = "tatooine_rebel_2"},
	QUEST_STRING_3 = {type = "destroy", name = "tatooine_rebel_3"},
	QUEST_STRING_4 = {type = "assassinate", name = "tatooine_rebel_4"},
	QUEST_STRING_DUTY_1 = {type = "destroy_duty", name = "tatooine_rebel_6"},
	QUEST_STRING_DUTY_2 = {type = "escort_duty", name = "tatooine_rebel_7"},

	-- Tier 2 (Socuna)
	TIER2_QUEST_STRING_1 = {type = "destroy", name = "rebel_destroy_03"},
	TIER2_QUEST_STRING_2 = {type = "escort", name = "rebel_escort_01"},
	TIER2_QUEST_STRING_3 = {type = "patrol", name = "rebel_patrol_02"},
	TIER2_QUEST_STRING_4 = {type = "destroy", name = "rebel_destroy_02"},
	TIER2_QUEST_STRING_DUTY_1 = {type = "destroy_duty", name = "tatooine_rebel_duty_6"},
	TIER2_QUEST_STRING_DUTY_2 = {type = "escort_duty", name = "tatooine_rebel_duty_7"},

	-- Tier 3 (Ulvawop)
	TIER3_QUEST_STRING_1 = {type = "recovery", name = "tatooine_rebel_tier3_1"},
	TIER3_QUEST_STRING_2 = {type = "inspect", name = "tatooine_rebel_tier3_2"},
	TIER3_QUEST_STRING_3 = {type = "delivery", name = "tatooine_rebel_tier3_3"},
	TIER3_QUEST_STRING_4 = {type = "assassinate", name = "tatooine_rebel_tier3_4"},

	-- Tier 4 (Ufwol)
	TIER4_QUEST_STRING_1 = {type = "space_battle", name = "tatooine_rebel_tier4_1"},
	TIER4_QUEST_STRING_2 = {type = "recovery", name = "tatooine_rebel_tier4_2"},
	TIER4_QUEST_STRING_3 = {type = "space_battle", name = "tatooine_rebel_tier4_3"},
	TIER4_QUEST_STRING_4 = {type = "assassinate", name = "tatooine_rebel_tier4_4"},
	TIER4_QUEST_STRING_MASTER = {type = "destroy", name = "tatooine_rebel_master"},
	TIER4_QUEST_STRING_DUTY_1 = {type = "escort_duty", name = "tatooine_rebel_tier4_1"},
	TIER4_QUEST_STRING_DUTY_2 = {type = "destroy_duty", name = "tatooine_rebel_tier4_1"},
	TIER4_QUEST_STRING_DUTY_3 = {type = "recovery_duty", name = "tatooine_rebel_tier4_1"},
	TIER4_QUEST_STRING_DUTY_4 = {type = "rescue_duty", name = "tatooine_rebel_tier4_1"},
}

registerScreenPlay("CrimsonPhoenixSquadronScreenplay", false)

function CrimsonPhoenixSquadronScreenplay:start()
end

-- Reset functions for quest clearing

function CrimsonPhoenixSquadronScreenplay:resetEkerQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- Mission 1
	patrol_tatooine_rebel_1:resetQuest(pPlayer)
	destroy_surpriseattack_tatooine_rebel_1:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, false)

	-- Mission 2
	patrol_tatooine_rebel_2:resetQuest(pPlayer)
	escort_tatooine_rebel_2:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_2_SIDE.type, self.QUEST_STRING_2_SIDE.name, false)

	-- Mission 3
	destroy_tatooine_rebel_3:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, false)

	-- Mission 4
	assassinate_tatooine_rebel_4:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_4.type, self.QUEST_STRING_4.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_4.name .. ":reward")
end

function CrimsonPhoenixSquadronScreenplay:resetSocunaQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- Mission 1
	destroy_socuna_rebel_1:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_1.type, self.TIER2_QUEST_STRING_1.name, false)

	-- Mission 2
	escort_socuna_rebel_2:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_2.type, self.TIER2_QUEST_STRING_2.name, false)

	-- Mission 3
	patrol_socuna_rebel_3:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_3.type, self.TIER2_QUEST_STRING_3.name, false)

	-- Mission 4
	destroy_socuna_rebel_4:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_4.type, self.TIER2_QUEST_STRING_4.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward")
end

function CrimsonPhoenixSquadronScreenplay:resetUlvawopQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- Mission 1
	recovery_tatooine_rebel_tier3_1:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1.type, self.TIER3_QUEST_STRING_1.name, false)

	-- Mission 2
	inspect_tatooine_rebel_tier3_2:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2.type, self.TIER3_QUEST_STRING_2.name, false)

	-- Mission 3
	delivery_tatooine_rebel_tier3_3:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3.type, self.TIER3_QUEST_STRING_3.name, false)

	-- Mission 4
	assassinate_tatooine_rebel_tier3_4:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4.type, self.TIER3_QUEST_STRING_4.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward")
end

function CrimsonPhoenixSquadronScreenplay:resetUfwolQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- Mission 1
	space_battle_tatooine_rebel_tier4_1:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_1.type, self.TIER4_QUEST_STRING_1.name, false)

	-- Mission 2
	recovery_tatooine_rebel_tier4_2:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_2.type, self.TIER4_QUEST_STRING_2.name, false)

	-- Mission 3
	space_battle_tatooine_rebel_tier4_3:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_3.type, self.TIER4_QUEST_STRING_3.name, false)

	-- Mission 4
	assassinate_tatooine_rebel_tier4_4:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_4.type, self.TIER4_QUEST_STRING_4.name, false)

	-- Master
	destroy_tatooine_rebel_master:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_MASTER.type, self.TIER4_QUEST_STRING_MASTER.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. "CrimsonPhoenixSquadronScreenplay:StartedUfwol")

	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":reward")
end
