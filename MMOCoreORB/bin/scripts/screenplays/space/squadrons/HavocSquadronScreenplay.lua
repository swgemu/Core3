local Logger = require("utils.logger")
local SpaceHelpers = require("utils.space_helpers")

--[[

	Havoc Squadron Missions (Arkon's Havoc Squadron - Rebel)

]]

--[[
	Tier 1 -- Kreezo Main Missions (Corellia)
]]

-- Mission 1: Patrol with surprise attack
patrol_corellia_rebel_1 = SpacePatrolScreenplay:new {
	className = "patrol_corellia_rebel_1",

	questName = "corellia_rebel_1",
	questType = "patrol",

	questZone = "space_corellia",

	creditReward = 100,

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "corellia_rebel_1",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 2,
	sideQuestDelay = 20,

	patrolPoints = {
		{patrolPointName = "rebel_corellia_patrol_1", x = -5100, z = -4500, y = -2300, patrolNumber = 1, radius = 150},
		{patrolPointName = "rebel_corellia_patrol_2", x = -4800, z = -5200, y = -2800, patrolNumber = 2, radius = 150},
		{patrolPointName = "rebel_corellia_patrol_3", x = -4200, z = -4800, y = -3200, patrolNumber = 3, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_rebel_1", true)

destroy_surpriseattack_corellia_rebel_1 = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_corellia_rebel_1",

	questName = "corellia_rebel_1",
	questType = "destroy_surpriseattack",

	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "patrol_corellia_rebel_1",
	parentQuestType = "patrol",
	parentQuestName = "corellia_rebel_1",

	surpriseAttackShips = {
		zone = "space_corellia",
		spawns = {{count = 2, shipName = "imp_tie_fighter_tier1"}, {count = 2, shipName = "imp_tie_light_tier1"}},
	},
}

registerScreenPlay("destroy_surpriseattack_corellia_rebel_1", true)

-- Mission 2: Destroy
destroy_corellia_rebel_2 = SpaceDestroyScreenplay:new {
	className = "destroy_corellia_rebel_2",

	questName = "corellia_rebel_2",
	questType = "destroy",

	questZone = "space_corellia",

	creditReward = 200,

	sideQuest = false,
	sideQuestType = "",

	killsRequired = 4,

	shipLocations = {
		{patrolPointName = "imperial_patrol_1", x = 590, z = -3500, y = -6000},
		{patrolPointName = "imperial_patrol_2", x = -2500, z = 4000, y = 3500},
		{patrolPointName = "imperial_patrol_3", x = -3800, z = 2500, y = 5000},
	},

	shipTypes = {
		"imp_tie_fighter_tier1", "imp_tie_fighter_tier2", "imp_tie_light_tier1", "imp_tie_light_tier2",
		"imp_tie_bomber_tier1", "imp_tie_bomber_tier2", "imp_tie_interceptor_tier1", "imp_tie_interceptor_tier2",
	},
}

registerScreenPlay("destroy_corellia_rebel_2", true)

-- Mission 3: Patrol with escort side quest
patrol_corellia_rebel_3 = SpacePatrolScreenplay:new {
	className = "patrol_corellia_rebel_3",

	questName = "corellia_rebel_3",
	questType = "patrol",

	questZone = "space_corellia",

	creditReward = 500,
	itemReward = {
		{species = {SPECIES_WOOKIEE}, item = "object/tangible/wearables/bandolier/multipocket_bandolier.iff"},
		{species = {SPECIES_ITHORIAN}, item = "object/tangible/wearables/bandolier/ith_multipocket_bandolier.iff"},
		{species = {-1}, item = "object/tangible/wearables/bodysuit/rebel_bodysuit_s14.iff"},
	},

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestName = "corellia_rebel_3",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 2,
	sideQuestDelay = 20,

	patrolPoints = {
		{patrolPointName = "rebel_security_patrol_1", x = 5549, z = -6501, y = -2720, patrolNumber = 1, radius = 150},
		{patrolPointName = "rebel_security_patrol_2", x = 1325, z = -6577, y = -3409, patrolNumber = 2, radius = 150},
		{patrolPointName = "rebel_security_patrol_3", x = -1514, z = -6488, y = -3864, patrolNumber = 3, radius = 150},
		{patrolPointName = "rebel_security_patrol_4", x = -5687, z = -6381, y = -4872, patrolNumber = 4, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_rebel_3", true)

escort_corellia_rebel_3 = SpaceEscortScreenplay:new {
	className = "escort_corellia_rebel_3",

	questName = "corellia_rebel_3",
	questType = "escort",

	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "patrol_corellia_rebel_3",
	parentQuestType = "patrol",
	parentQuestName = "corellia_rebel_3",

	escortShips = {"freighterheavy_tier1"},

	escortPoints = {
		{patrolPointName = "rebel_security_escort_1", zoneName = "space_corellia", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{patrolPointName = "rebel_security_escort_2", zoneName = "space_corellia", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{patrolPointName = "rebel_security_escort_3", zoneName = "space_corellia", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{patrolPointName = "rebel_security_escort_4", zoneName = "space_corellia", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
	},

	attackDelay = 90,

	attackShips = {
		{"imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_light_tier1"},
	}
}

registerScreenPlay("escort_corellia_rebel_3", true)

-- Mission 4: Assassinate
assassinate_corellia_rebel_4 = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_rebel_4",

	questType = "assassinate",
	questName = "corellia_rebel_4",

	questZone = "space_corellia",

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
		{patrolPointName = "rebel_assassinate_1", x = 2650, z = -1672, y = -105},
		{patrolPointName = "rebel_assassinate_2", x = 4431, z = -1858, y = 2196},
		{patrolPointName = "rebel_assassinate_3", x = -6932, z = -1364, y = -644},
	},
}

registerScreenPlay("assassinate_corellia_rebel_4", true)

-- Kreezo Duty Missions
destroy_duty_corellia_rebel_6 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_corellia_rebel_6",

	questName = "corellia_rebel_6",
	questType = "destroy_duty",

	questZone = "space_corellia",

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

registerScreenPlay("destroy_duty_corellia_rebel_6", true)

escort_duty_corellia_rebel_7 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_corellia_rebel_7",

	questName = "corellia_rebel_7",
	questType = "escort_duty",

	questZone = "space_corellia",

	creditReward = 1000,

	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"freighterheavy_tier1", "freighterlight_tier1", "freightermedium_tier1"},

	escortPoints = {
		{patrolPointName = "rebel_escort_duty_1", zoneName = "space_corellia", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{patrolPointName = "rebel_escort_duty_2", zoneName = "space_corellia", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{patrolPointName = "rebel_escort_duty_3", zoneName = "space_corellia", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{patrolPointName = "rebel_escort_duty_4", zoneName = "space_corellia", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
	},

	attackDelay = 90,

	attackShips = {
		{"imp_tie_fighter_tier1", "imp_tie_light_tier1"},
		{"imp_tie_bomber_tier1", "imp_tie_interceptor_tier1"},
	},

	creditKillBonus = 100,
}

registerScreenPlay("escort_duty_corellia_rebel_7", true)

--[[
	Tier 2 -- Viopa Main Missions (Lok)
]]

-- Mission 1: Inspect
inspect_viopa_rebel_1 = SpaceInspectScreenplay:new {
	className = "inspect_viopa_rebel_1",

	questName = "viopa_rebel_1",
	questType = "inspect",

	questZone = "space_lok",

	creditReward = 5000,

	sideQuest = false,
	sideQuestType = "",

	inspectTargets = {"imp_transport_tier2"},
	inspectCargo = "shipment_orders",

	targetLocation = {x = 3719, z = -2284, y = -1151},
}

registerScreenPlay("inspect_viopa_rebel_1", true)

-- Mission 2: Escort
escort_viopa_rebel_2 = SpaceEscortScreenplay:new {
	className = "escort_viopa_rebel_2",

	questName = "viopa_rebel_2",
	questType = "escort",

	questZone = "space_lok",

	creditReward = 5000,

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"freighterheavy_tier2"},

	escortPoints = {
		{patrolPointName = "viopa_escort_1", zoneName = "space_lok", x = -2163, z = 956, y = 4991, escortNumber = 1, radius = 250},
		{patrolPointName = "viopa_escort_2", zoneName = "space_lok", x = -637, z = -295, y = 4770, escortNumber = 2, radius = 250},
		{patrolPointName = "viopa_escort_3", zoneName = "space_lok", x = 2043, z = -1230, y = 5414, escortNumber = 3, radius = 250},
		{patrolPointName = "viopa_escort_4", zoneName = "space_lok", x = -2064, z = -929, y = -3183, escortNumber = 4, radius = 250},
	},

	attackDelay = 180,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_bomber_tier2", "imp_tie_interceptor_tier2"},
	}
}

registerScreenPlay("escort_viopa_rebel_2", true)

-- Mission 3: Recovery
recovery_viopa_rebel_3 = SpaceRecoveryScreenplay:new {
	className = "recovery_viopa_rebel_3",

	questName = "viopa_rebel_3",
	questType = "recovery",

	questZone = "space_lok",

	creditReward = 5000,

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 13,
	recoveryDelay = 15,

	recoverShip = "reb_ywing_tier2",
	recoveryConversationMobile = "object/mobile/shared_dressed_rebel_pilot_human_male_01.iff",

	escortShips = {},

	preRecoveryPoints = {
		{patrolPointName = "viopa_recovery_pre_1", zoneName = "space_lok", x = 4250, z = 1204, y = 3259, escortNumber = 1, radius = 250},
		{patrolPointName = "viopa_recovery_pre_2", zoneName = "space_lok", x = 4318, z = 463, y = 3868, escortNumber = 2, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "viopa_recovery_1", zoneName = "space_lok", x = 4693, z = -604, y = 3823, escortNumber = 1, radius = 250},
		{patrolPointName = "viopa_recovery_2", zoneName = "space_lok", x = 5053, z = -1137, y = 3171, escortNumber = 2, radius = 250},
	},

	attackDelay = 110,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_bomber_tier2"},
	},
}

registerScreenPlay("recovery_viopa_rebel_3", true)

-- Mission 4: Assassinate
assassinate_viopa_rebel_4 = SpaceAssassinateScreenplay:new {
	className = "assassinate_viopa_rebel_4",

	questType = "assassinate",
	questName = "viopa_rebel_4",

	questZone = "space_lok",

	creditReward = 0,
	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 7,
	failTimer = 20,

	assassinateSpawns = {
		target = "imp_tie_advanced_tier3",
		escorts = {"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier2"},
	},

	targetPatrols = {
		{patrolPointName = "viopa_assassinate_1", x = -137, z = -1281, y = 2629},
		{patrolPointName = "viopa_assassinate_2", x = 1014, z = -432, y = 1398},
		{patrolPointName = "viopa_assassinate_3", x = 2514, z = 4958, y = 2580},
	},
}

registerScreenPlay("assassinate_viopa_rebel_4", true)

-- Viopa Duty Missions
destroy_duty_viopa_rebel_6 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_viopa_rebel_6",

	questName = "viopa_rebel_6",
	questType = "destroy_duty",

	questZone = "space_lok",

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
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
		{"imp_tie_bomber_tier2", "imp_tie_bomber_tier2"},
	},
}

registerScreenPlay("destroy_duty_viopa_rebel_6", true)

recovery_duty_viopa_rebel_7 = SpaceDutyDestroyScreenplay:new {
	className = "recovery_duty_viopa_rebel_7",

	questName = "viopa_rebel_7",
	questType = "recovery_duty",

	questZone = "space_lok",

	creditReward = 100,

	sideQuest = false,
	sideQuestType = "",

	totalLevels = 2,
	totalRounds = 2,
	totalWaves = 2,

	minDistance = 12500,
	maxDistance = 17500,

	bossShip = "imp_tie_advanced_tier2",
	shipTypes = {"imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
}

registerScreenPlay("recovery_duty_viopa_rebel_7", true)

escort_duty_viopa_rebel_5 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_viopa_rebel_5",

	questName = "viopa_rebel_5",
	questType = "escort_duty",

	questZone = "space_lok",

	creditReward = 1000,

	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"freighterheavy_tier2", "freighterlight_tier2", "freightermedium_tier2"},

	escortPoints = {
		{patrolPointName = "viopa_escort_duty_1", zoneName = "space_lok", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{patrolPointName = "viopa_escort_duty_2", zoneName = "space_lok", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{patrolPointName = "viopa_escort_duty_3", zoneName = "space_lok", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{patrolPointName = "viopa_escort_duty_4", zoneName = "space_lok", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
	},

	attackDelay = 90,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_light_tier2"},
		{"imp_tie_bomber_tier2", "imp_tie_interceptor_tier2"},
	},

	creditKillBonus = 100,
}

registerScreenPlay("escort_duty_viopa_rebel_5", true)

--[[
	Tier 3 -- Arkon Main Missions (Corellia)
]]

-- Mission 1: Recovery
recovery_corellia_rebel_tier3_1 = SpaceRecoveryScreenplay:new {
	className = "recovery_corellia_rebel_tier3_1",

	questName = "corellia_rebel_tier3_1",
	questType = "recovery",

	questZone = "space_corellia",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 13,
	recoveryDelay = 15,

	recoverShip = "reb_xwing_tier3",
	recoveryConversationMobile = "object/mobile/shared_dressed_rebel_pilot_human_male_01.iff",

	escortShips = {},

	preRecoveryPoints = {
		{patrolPointName = "arkon_recovery_pre_1", zoneName = "space_corellia", x = 4250, z = 1204, y = 3259, escortNumber = 1, radius = 250},
		{patrolPointName = "arkon_recovery_pre_2", zoneName = "space_corellia", x = 4318, z = 463, y = 3868, escortNumber = 2, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "arkon_recovery_1", zoneName = "space_corellia", x = 4693, z = -604, y = 3823, escortNumber = 1, radius = 250},
		{patrolPointName = "arkon_recovery_2", zoneName = "space_corellia", x = 5053, z = -1137, y = 3171, escortNumber = 2, radius = 250},
	},

	attackDelay = 110,

	attackShips = {
		{"imp_tie_fighter_tier3", "imp_tie_bomber_tier3"},
	},
}

registerScreenPlay("recovery_corellia_rebel_tier3_1", true)

-- Mission 2: Inspect
inspect_corellia_rebel_tier3_2 = SpaceInspectScreenplay:new {
	className = "inspect_corellia_rebel_tier3_2",

	questName = "corellia_rebel_tier3_2",
	questType = "inspect",

	questZone = "space_corellia",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	inspectTargets = {"imp_transport_tier3"},
	inspectCargo = "shipment_orders",

	targetLocation = {x = 3719, z = -2284, y = -1151},
}

registerScreenPlay("inspect_corellia_rebel_tier3_2", true)

-- Mission 3: Delivery
delivery_corellia_rebel_tier3_3 = SpaceDeliveryScreenplay:new {
	className = "delivery_corellia_rebel_tier3_3",

	questName = "corellia_rebel_tier3_3",
	questType = "delivery",

	questZone = "space_corellia",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	deliveryShip = "reb_ywing_tier3",

	deliveryPoints = {
		{patrolPointName = "arkon_delivery_1", zoneName = "space_corellia", x = 4693, z = -604, y = 3823, deliveryNumber = 1, radius = 250},
		{patrolPointName = "arkon_delivery_2", zoneName = "space_corellia", x = 5053, z = -1137, y = 3171, deliveryNumber = 2, radius = 250},
	},
}

registerScreenPlay("delivery_corellia_rebel_tier3_3", true)

-- Mission 4: Assassinate
assassinate_corellia_rebel_tier3_4 = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_rebel_tier3_4",

	questType = "assassinate",
	questName = "corellia_rebel_tier3_4",

	questZone = "space_corellia",

	creditReward = 0,
	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 7,
	failTimer = 20,

	assassinateSpawns = {
		target = "imp_tie_advanced_tier4",
		escorts = {"imp_tie_fighter_tier3", "imp_tie_fighter_tier3", "imp_tie_interceptor_tier3", "imp_tie_bomber_tier3"},
	},

	targetPatrols = {
		{patrolPointName = "arkon_assassinate_1", x = -137, z = -1281, y = 2629},
		{patrolPointName = "arkon_assassinate_2", x = 1014, z = -432, y = 1398},
	},
}

registerScreenPlay("assassinate_corellia_rebel_tier3_4", true)

--[[
	Tier 4 -- Aqzow Main Missions (Corellia)
]]

-- Mission 1: Survival
survival_corellia_rebel_tier4_1 = SpaceSurvivalScreenplay:new {
	className = "survival_corellia_rebel_tier4_1",

	questName = "corellia_rebel_tier4_1",
	questType = "survival",

	questZone = "space_corellia",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	survivalTime = 300,

	attackShips = {
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_bomber_tier4"},
	},
}

registerScreenPlay("survival_corellia_rebel_tier4_1", true)

-- Mission 2: Assassinate
assassinate_corellia_rebel_tier4_2 = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_rebel_tier4_2",

	questType = "assassinate",
	questName = "corellia_rebel_tier4_2",

	questZone = "space_corellia",

	creditReward = 0,
	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 7,
	failTimer = 20,

	assassinateSpawns = {
		target = "imp_tie_advanced_tier4",
		escorts = {"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_bomber_tier4"},
	},

	targetPatrols = {
		{patrolPointName = "aqzow_assassinate_1", x = -137, z = -1281, y = 2629},
		{patrolPointName = "aqzow_assassinate_2", x = 1014, z = -432, y = 1398},
	},
}

registerScreenPlay("assassinate_corellia_rebel_tier4_2", true)

-- Mission 3: Space Battle
space_battle_corellia_rebel_tier4_3 = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_rebel_tier4_3",

	questName = "corellia_rebel_tier4_3",
	questType = "space_battle",

	questZone = "space_corellia",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	battleTime = 600,

	alliedShips = {
		{"reb_xwing_tier4", "reb_xwing_tier4", "reb_ywing_tier4"},
	},

	enemyShips = {
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_bomber_tier4", "imp_tie_interceptor_tier4"},
	},
}

registerScreenPlay("space_battle_corellia_rebel_tier4_3", true)

-- Mission 4: Recovery
recovery_corellia_rebel_tier4_4 = SpaceRecoveryScreenplay:new {
	className = "recovery_corellia_rebel_tier4_4",

	questName = "corellia_rebel_tier4_4",
	questType = "recovery",

	questZone = "space_corellia",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 13,
	recoveryDelay = 15,

	recoverShip = "reb_awing_tier4",
	recoveryConversationMobile = "object/mobile/shared_dressed_rebel_pilot_human_male_01.iff",

	escortShips = {},

	preRecoveryPoints = {
		{patrolPointName = "aqzow_recovery_pre_1", zoneName = "space_corellia", x = 4250, z = 1204, y = 3259, escortNumber = 1, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "aqzow_recovery_1", zoneName = "space_corellia", x = 4693, z = -604, y = 3823, escortNumber = 1, radius = 250},
	},

	attackDelay = 110,

	attackShips = {
		{"imp_tie_fighter_tier4", "imp_tie_bomber_tier4", "imp_tie_interceptor_tier4"},
	},
}

registerScreenPlay("recovery_corellia_rebel_tier4_4", true)

-- Master Mission: Destroy
destroy_corellia_rebel_master = SpaceDestroyScreenplay:new {
	className = "destroy_corellia_rebel_master",

	questName = "corellia_rebel_master",
	questType = "destroy",

	questZone = "space_corellia",

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

registerScreenPlay("destroy_corellia_rebel_master", true)

-- Aqzow Duty Missions
escort_duty_corellia_rebel_tier4_1 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_corellia_rebel_tier4_1",

	questName = "corellia_rebel_tier4_1",
	questType = "escort_duty",

	questZone = "space_corellia",

	creditReward = 1000,

	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"freighterheavy_tier4", "freighterlight_tier4", "freightermedium_tier4"},

	escortPoints = {
		{patrolPointName = "aqzow_escort_duty_1", zoneName = "space_corellia", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{patrolPointName = "aqzow_escort_duty_2", zoneName = "space_corellia", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{patrolPointName = "aqzow_escort_duty_3", zoneName = "space_corellia", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{patrolPointName = "aqzow_escort_duty_4", zoneName = "space_corellia", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
	},

	attackDelay = 90,

	attackShips = {
		{"imp_tie_fighter_tier4", "imp_tie_light_tier4"},
		{"imp_tie_bomber_tier4", "imp_tie_interceptor_tier4"},
	},

	creditKillBonus = 100,
}

registerScreenPlay("escort_duty_corellia_rebel_tier4_1", true)

rescue_duty_corellia_rebel_tier4_1 = SpaceDutyDestroyScreenplay:new {
	className = "rescue_duty_corellia_rebel_tier4_1",

	questName = "corellia_rebel_tier4_1",
	questType = "rescue_duty",

	questZone = "space_corellia",

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
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_fighter_tier4"},
		{"imp_tie_bomber_tier4", "imp_tie_bomber_tier4"},
	},
}

registerScreenPlay("rescue_duty_corellia_rebel_tier4_1", true)

recovery_duty_corellia_rebel_tier4_1 = SpaceDutyDestroyScreenplay:new {
	className = "recovery_duty_corellia_rebel_tier4_1",

	questName = "corellia_rebel_tier4_1",
	questType = "recovery_duty",

	questZone = "space_corellia",

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

registerScreenPlay("recovery_duty_corellia_rebel_tier4_1", true)

destroy_duty_corellia_rebel_tier4_1 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_corellia_rebel_tier4_1",

	questName = "corellia_rebel_tier4_1",
	questType = "destroy_duty",

	questZone = "space_corellia",

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
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_fighter_tier4"},
		{"imp_tie_bomber_tier4", "imp_tie_bomber_tier4"},
		{"imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4"},
	},
}

registerScreenPlay("destroy_duty_corellia_rebel_tier4_1", true)

--[[

	HavocSquadronScreenplay

]]

HavocSquadronScreenplay = ScreenPlay:new {
	screenplayName = "HavocSquadronScreenplay",

	-- Tier 1 (Kreezo)
	QUEST_STRING_1 = {type = "patrol", name = "corellia_rebel_1"},
	QUEST_STRING_1_SIDE = {type = "destroy_surpriseattack", name = "corellia_rebel_1"},
	QUEST_STRING_2 = {type = "destroy", name = "corellia_rebel_2"},
	QUEST_STRING_3 = {type = "patrol", name = "corellia_rebel_3"},
	QUEST_STRING_3_SIDE = {type = "escort", name = "corellia_rebel_3"},
	QUEST_STRING_4 = {type = "assassinate", name = "corellia_rebel_4"},
	QUEST_STRING_DUTY_1 = {type = "destroy_duty", name = "corellia_rebel_6"},
	QUEST_STRING_DUTY_2 = {type = "escort_duty", name = "corellia_rebel_7"},

	-- Tier 2 (Viopa)
	TIER2_QUEST_STRING_1 = {type = "inspect", name = "viopa_rebel_1"},
	TIER2_QUEST_STRING_2 = {type = "escort", name = "viopa_rebel_2"},
	TIER2_QUEST_STRING_3 = {type = "recovery", name = "viopa_rebel_3"},
	TIER2_QUEST_STRING_4 = {type = "assassinate", name = "viopa_rebel_4"},
	TIER2_QUEST_STRING_DUTY_1 = {type = "destroy_duty", name = "viopa_rebel_6"},
	TIER2_QUEST_STRING_DUTY_2 = {type = "recovery_duty", name = "viopa_rebel_7"},
	TIER2_QUEST_STRING_DUTY_3 = {type = "escort_duty", name = "viopa_rebel_5"},

	-- Tier 3 (Arkon)
	TIER3_QUEST_STRING_1 = {type = "recovery", name = "corellia_rebel_tier3_1"},
	TIER3_QUEST_STRING_2 = {type = "inspect", name = "corellia_rebel_tier3_2"},
	TIER3_QUEST_STRING_3 = {type = "delivery", name = "corellia_rebel_tier3_3"},
	TIER3_QUEST_STRING_4 = {type = "assassinate", name = "corellia_rebel_tier3_4"},

	-- Tier 4 (Aqzow)
	TIER4_QUEST_STRING_1 = {type = "survival", name = "corellia_rebel_tier4_1"},
	TIER4_QUEST_STRING_2 = {type = "assassinate", name = "corellia_rebel_tier4_2"},
	TIER4_QUEST_STRING_3 = {type = "space_battle", name = "corellia_rebel_tier4_3"},
	TIER4_QUEST_STRING_4 = {type = "recovery", name = "corellia_rebel_tier4_4"},
	TIER4_QUEST_STRING_MASTER = {type = "destroy", name = "corellia_rebel_master"},
	TIER4_QUEST_STRING_DUTY_1 = {type = "escort_duty", name = "corellia_rebel_tier4_1"},
	TIER4_QUEST_STRING_DUTY_2 = {type = "rescue_duty", name = "corellia_rebel_tier4_1"},
	TIER4_QUEST_STRING_DUTY_3 = {type = "recovery_duty", name = "corellia_rebel_tier4_1"},
	TIER4_QUEST_STRING_DUTY_4 = {type = "destroy_duty", name = "corellia_rebel_tier4_1"},
}

registerScreenPlay("HavocSquadronScreenplay", false)

function HavocSquadronScreenplay:start()
end

-- Reset functions for quest clearing

function HavocSquadronScreenplay:resetKreezoQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- Mission 1
	patrol_corellia_rebel_1:resetQuest(pPlayer)
	destroy_surpriseattack_corellia_rebel_1:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, false)

	-- Mission 2
	destroy_corellia_rebel_2:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, false)

	-- Mission 3
	patrol_corellia_rebel_3:resetQuest(pPlayer)
	escort_corellia_rebel_3:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_3_SIDE.type, self.QUEST_STRING_3_SIDE.name, false)

	-- Mission 4
	assassinate_corellia_rebel_4:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_4.type, self.QUEST_STRING_4.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_4.name .. ":reward")
end

function HavocSquadronScreenplay:resetViopaQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- Mission 1
	inspect_viopa_rebel_1:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_1.type, self.TIER2_QUEST_STRING_1.name, false)

	-- Mission 2
	escort_viopa_rebel_2:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_2.type, self.TIER2_QUEST_STRING_2.name, false)

	-- Mission 3
	recovery_viopa_rebel_3:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_3.type, self.TIER2_QUEST_STRING_3.name, false)

	-- Mission 4
	assassinate_viopa_rebel_4:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_4.type, self.TIER2_QUEST_STRING_4.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward")
end

function HavocSquadronScreenplay:resetArkonQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- Mission 1
	recovery_corellia_rebel_tier3_1:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1.type, self.TIER3_QUEST_STRING_1.name, false)

	-- Mission 2
	inspect_corellia_rebel_tier3_2:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2.type, self.TIER3_QUEST_STRING_2.name, false)

	-- Mission 3
	delivery_corellia_rebel_tier3_3:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3.type, self.TIER3_QUEST_STRING_3.name, false)

	-- Mission 4
	assassinate_corellia_rebel_tier3_4:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4.type, self.TIER3_QUEST_STRING_4.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward")
end

function HavocSquadronScreenplay:resetAqzowQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- Mission 1
	survival_corellia_rebel_tier4_1:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_1.type, self.TIER4_QUEST_STRING_1.name, false)

	-- Mission 2
	assassinate_corellia_rebel_tier4_2:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_2.type, self.TIER4_QUEST_STRING_2.name, false)

	-- Mission 3
	space_battle_corellia_rebel_tier4_3:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_3.type, self.TIER4_QUEST_STRING_3.name, false)

	-- Mission 4
	recovery_corellia_rebel_tier4_4:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_4.type, self.TIER4_QUEST_STRING_4.name, false)

	-- Master
	destroy_corellia_rebel_master:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_MASTER.type, self.TIER4_QUEST_STRING_MASTER.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. "HavocSquadronScreenplay:StartedAqzow")

	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":reward")
end
