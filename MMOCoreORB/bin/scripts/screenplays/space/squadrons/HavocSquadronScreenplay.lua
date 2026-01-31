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
		{patrolPointName = "rebel_patrol_1", x = 6439, z = -5021, y = -2217, patrolNumber = 1, radius = 150},
		{patrolPointName = "rebel_patrol_2", x = 6031, z = -4540, y = -1962, patrolNumber = 2, radius = 150},
		{patrolPointName = "rebel_patrol_3", x = 4891, z = -3215, y = -1345, patrolNumber = 3, radius = 150},
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
		spawns = {{count = 3, shipName = "imp_tie_fighter_tier1"}},
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
		"imp_tie_fighter_tier1", "imp_tie_fighter_tier2", "imp_tie_fighter_tier3", "imp_tie_fighter_tier4",
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
		{species = {-1}, item = "object/tangible/wearables/bodysuit/bodysuit_s14.iff"},
	},

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestName = "corellia_rebel_3",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 2,
	sideQuestDelay = 20,

	patrolPoints = {
		{patrolPointName = "rebel_security_patrol_1", x = 5024, z = -3710, y = -1723, patrolNumber = 1, radius = 150},
		{patrolPointName = "rebel_security_patrol_2", x = 3933, z = -3285, y = -3098, patrolNumber = 2, radius = 150},
		{patrolPointName = "rebel_security_patrol_3", x = 3574, z = -2819, y = -4741, patrolNumber = 3, radius = 150},
		{patrolPointName = "rebel_security_patrol_4", x = 4496, z = -1657, y = -6222, patrolNumber = 4, radius = 150},
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

	escortShips = {"reb_freightermedium_tier1"},

	escortPoints = {
		{patrolPointName = "rebel_escort_1", zoneName = "space_corellia", x = 7188, z = 1899, y = -2831, escortNumber = 1, radius = 250},
		{patrolPointName = "rebel_escort_2", zoneName = "space_corellia", x = 6446, z = 2694, y = -5694, escortNumber = 2, radius = 250},
		{patrolPointName = "rebel_escort_3", zoneName = "space_corellia", x = 4453, z = 3127, y = -7150, escortNumber = 3, radius = 250},
		{patrolPointName = "rebel_escort_4", zoneName = "space_corellia", x = 1085, z = 4064, y = -7316, escortNumber = 4, radius = 250},
	},

	attackDelay = 80,

	attackShips = {
		{"imp_tie_fighter_tier1"},
		{"imp_tie_fighter_tier1"},
		{"imp_tie_fighter_tier1"},
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
		target = "imp_tie_fighter_veteran_tier2",
		escorts = {"imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1", "imp_tie_fighter_tier1"},
	},

	targetPatrols = {
		{patrolPointName = "rebel_security_patrol_2", x = 3933, z = -3285, y = -3098},
		{patrolPointName = "naboo_privateer_tier3_leg_2_rescue_egress_4", x = 1156, z = -7106, y = -2482},
		{patrolPointName = "trade_escort_4", x = 895, z = 210, y = 695},
		{patrolPointName = "military_escort_2", x = 2915, z = 3828, y = 2887},
		{patrolPointName = "corellia_imperial_tier3_leg_1_recovery_recover_1", x = 752, z = -2678, y = -1479},
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

	totalLevels = 5,
	totalRounds = 2,
	totalWaves = 3,

	minDistance = 12500,
	maxDistance = 17500,

	bossShip = "imp_tie_fighter_tier2",
	shipTypes = {
		{"imp_tie_fighter_tier1"},
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

	escortShips = {"reb_transport_tier1", "reb_freightermedium_tier1", "reb_freighterlight_tier1", "reb_freighterheavy_tier1"},

	escortPoints = {
		{patrolPointName = "rebel_escort_1", zoneName = "space_corellia", x = 7188, z = 1899, y = -2831, escortNumber = 1, radius = 250},
		{patrolPointName = "rebel_escort_4", zoneName = "space_corellia", x = 1085, z = 4064, y = -7316, escortNumber = 2, radius = 250},
		{patrolPointName = "rebel_patrol_1", zoneName = "space_corellia", x = 6439, z = -5021, y = -2217, escortNumber = 3, radius = 250},
		{patrolPointName = "rebel_patrol_3", zoneName = "space_corellia", x = 4891, z = -3215, y = -1345, escortNumber = 4, radius = 250},
	},

	attackDelay = 100,

	attackShips = {
		{"imp_tie_fighter_tier1"},
		{"imp_tie_fighter_tier1"},
		{"imp_tie_fighter_tier1"},
	},

	creditKillBonus = 100,
}

registerScreenPlay("escort_duty_corellia_rebel_7", true)

--[[
	Tier 2 -- Viopa Main Missions (Lok)
]]

-- Mission 1: Inspect with surprise attack side quest
inspect_viopa_rebel_1 = SpaceInspectScreenplay:new {
	className = "inspect_viopa_rebel_1",

	questName = "viopa_rebel_1",
	questType = "inspect",

	questZone = "space_lok",

	creditReward = 5000,

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "viopa_rebel_1",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	inspectTargets = {"viopa_mission_1_shuttle"},
	inspectCargo = "imperial_data",

	targetLocation = {x = 1992, z = 800, y = 2716},
}

registerScreenPlay("inspect_viopa_rebel_1", true)

destroy_surpriseattack_viopa_rebel_1 = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_viopa_rebel_1",

	questName = "viopa_rebel_1",
	questType = "destroy_surpriseattack",

	questZone = "space_lok",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "inspect_viopa_rebel_1",
	parentQuestType = "inspect",
	parentQuestName = "viopa_rebel_1",

	surpriseAttackShips = {
		zone = "space_lok",
		spawns = {{count = 3, shipName = "imp_tie_fighter_tier2"}},
	},
}

registerScreenPlay("destroy_surpriseattack_viopa_rebel_1", true)

-- Mission 2: Escort (in Dantooine)
escort_viopa_rebel_2 = SpaceEscortScreenplay:new {
	className = "escort_viopa_rebel_2",

	questName = "viopa_rebel_2",
	questType = "escort",

	questZone = "space_dantooine",

	creditReward = 5000,

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"viopa_mission_2_smuggler"},

	escortPoints = {
		{patrolPointName = "viopa_rebel_2_1", zoneName = "space_dantooine", x = 1000, z = -900, y = -2100, escortNumber = 1, radius = 250},
		{patrolPointName = "viopa_rebel_2_2", zoneName = "space_dantooine", x = -28, z = -908, y = -2207, escortNumber = 2, radius = 250},
		{patrolPointName = "viopa_rebel_2_3", zoneName = "space_dantooine", x = -1158, z = -952, y = -2363, escortNumber = 3, radius = 250},
		{patrolPointName = "viopa_rebel_2_4", zoneName = "space_dantooine", x = -2566, z = -1057, y = -2599, escortNumber = 4, radius = 250},
		{patrolPointName = "viopa_rebel_2_5", zoneName = "space_dantooine", x = -2436, z = -1574, y = -3167, escortNumber = 5, radius = 250},
		{patrolPointName = "viopa_rebel_2_6", zoneName = "space_dantooine", x = -2129, z = -1970, y = -3738, escortNumber = 6, radius = 250},
	},

	attackDelay = 70,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
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

	arrivalDelay = 15,
	recoveryDelay = 30,

	recoverShip = "viopa_mission_3_shuttle",
	recoveryConversationMobile = "object/mobile/shared_dressed_rebel_commando_rodian_male_01.iff",

	escortShips = {"imp_tie_fighter_tier2"},

	preRecoveryPoints = {
		{patrolPointName = "viopa_rebel_3_target_1", zoneName = "space_lok", x = -5500, z = 3900, y = 3600, escortNumber = 1, radius = 250},
		{patrolPointName = "viopa_rebel_3_target_2", zoneName = "space_lok", x = -4775, z = 3294, y = 3140, escortNumber = 2, radius = 250},
		{patrolPointName = "viopa_rebel_3_target_3", zoneName = "space_lok", x = -3923, z = 2964, y = 2395, escortNumber = 3, radius = 250},
		{patrolPointName = "viopa_rebel_3_target_4", zoneName = "space_lok", x = -3191, z = 2904, y = 1706, escortNumber = 4, radius = 250},
		{patrolPointName = "viopa_rebel_3_target_5", zoneName = "space_lok", x = -2496, z = 2865, y = 751, escortNumber = 5, radius = 250},
		{patrolPointName = "viopa_rebel_3_target_6", zoneName = "space_lok", x = -1540, z = 2528, y = -1100, escortNumber = 6, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "viopa_rebel_3_recover_1", zoneName = "space_lok", x = -3381, z = 2517, y = 877, escortNumber = 1, radius = 250},
		{patrolPointName = "viopa_rebel_3_recover_2", zoneName = "space_lok", x = -3512, z = 1885, y = -192, escortNumber = 2, radius = 250},
		{patrolPointName = "viopa_rebel_3_recover_3", zoneName = "space_lok", x = -3723, z = 1223, y = -989, escortNumber = 3, radius = 250},
		{patrolPointName = "viopa_rebel_3_recover_4", zoneName = "space_lok", x = -4257, z = -227, y = -2707, escortNumber = 4, radius = 250},
	},

	attackDelay = 80,

	attackShips = {
		{"imp_tie_interceptor_tier2", "imp_tie_fighter_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
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

	arrivalDelay = 10,
	failTimer = 20,

	assassinateSpawns = {
		target = "viopa_mission_4_freighter",
		escorts = {"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier3"},
	},

	targetPatrols = {
		{patrolPointName = "viopa_rebel_four_1", x = 2800, z = 2400, y = 2800},
		{patrolPointName = "viopa_rebel_four_2", x = 1662, z = 2407, y = 2790},
		{patrolPointName = "viopa_rebel_four_3", x = 533, z = 2411, y = 3116},
		{patrolPointName = "viopa_rebel_four_4", x = -1109, z = 2414, y = 3581},
		{patrolPointName = "viopa_rebel_four_5", x = -2303, z = 2415, y = 4011},
		{patrolPointName = "viopa_rebel_four_6", x = -3674, z = 2416, y = 4444},
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

	totalLevels = 5,
	totalRounds = 2,
	totalWaves = 3,

	minDistance = 12500,
	maxDistance = 17500,

	bossShip = "imp_tie_interceptor_tier3",
	shipTypes = {
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
		{"imp_tie_interceptor_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
	},
}

registerScreenPlay("destroy_duty_viopa_rebel_6", true)

recovery_duty_viopa_rebel_7 = SpaceDutyRecoveryScreenplay:new {
	className = "recovery_duty_viopa_rebel_7",

	questName = "viopa_rebel_7",
	questType = "recovery_duty",

	questZone = "space_lok",

	creditReward = 2500,
	creditKillBonus = 200,

	sideQuest = false,
	sideQuestType = "",

	arrivalDelay = 15,
	recoveryDelay = 30,

	recoverShips = {"corsair_manowar_tier2", "corsair_behemoth_tier2"},
	recoveryConversationMobile = "object/mobile/shared_dressed_nym_patrol_elite_nikto_m.iff",

	escortShips = {"corsair_sloop_tier2"},

	preRecoveryPoints = {
		{patrolPointName = "corellia_rebel_tier2_recovery_duty_1", zoneName = "space_lok", x = -5007, z = -5499, y = -3499, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier2_recovery_duty_2", zoneName = "space_lok", x = -6466, z = -6879, y = -4229, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier2_recovery_duty_3", zoneName = "space_lok", x = -6974, z = -7081, y = -1544, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier2_recovery_duty_4", zoneName = "space_lok", x = -7169, z = -6943, y = 1241, escortNumber = 4, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "corellia_rebel_tier2_recovery_duty_5", zoneName = "space_lok", x = -5700, z = -5955, y = -2034, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier2_recovery_duty_6", zoneName = "space_lok", x = -5033, z = -4822, y = -3028, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier2_recovery_duty_7", zoneName = "space_lok", x = -4768, z = -3941, y = -3678, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier2_recovery_duty_8", zoneName = "space_lok", x = -4757, z = -3078, y = -3964, escortNumber = 4, radius = 250},
	},

	attackDelay = 100,

	attackShips = {
		{"corsair_raider_tier2", "corsair_sloop_tier2"},
		{"corsair_sloop_tier2", "corsair_sloop_tier2"},
	},
}

registerScreenPlay("recovery_duty_viopa_rebel_7", true)

escort_duty_viopa_rebel_5 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_viopa_rebel_5",

	questName = "viopa_rebel_5",
	questType = "escort_duty",

	questZone = "space_lok",

	creditReward = 2500,

	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"nym_smuggle_vessel", "reb_smuggler_ykl37r_tier2", "reb_smuggler_yt1300_tier2"},

	escortPoints = {
		{patrolPointName = "vortex_mission_1_4", zoneName = "space_lok", x = -1009, z = -1075, y = -2900, escortNumber = 1, radius = 250},
		{patrolPointName = "lok_imp_pirate_9", zoneName = "space_lok", x = 1492, z = 662, y = -2814, escortNumber = 2, radius = 250},
		{patrolPointName = "vortex_mission_1_1", zoneName = "space_lok", x = 2241, z = -1210, y = -2943, escortNumber = 3, radius = 250},
		{patrolPointName = "vortex_mission_1_5", zoneName = "space_lok", x = -2464, z = -1051, y = -2900, escortNumber = 4, radius = 250},
	},

	attackDelay = 80,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_bomber_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
	},

	creditKillBonus = 200,
}

registerScreenPlay("escort_duty_viopa_rebel_5", true)

--[[
	Tier 3 -- Arkon Main Missions (Corellia)
]]

-- Mission 1: Recovery (Space Yavin4 - Imperial spy trying to escape with Rebel fleet hangar info)
recovery_corellia_rebel_tier3_1 = SpaceRecoveryScreenplay:new {
	className = "recovery_corellia_rebel_tier3_1",

	questName = "corellia_rebel_tier3_1",
	questType = "recovery",

	questZone = "space_yavin4",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "patrol",
	sideQuestName = "patrol_corellia_rebel_tier3_1_A",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	arrivalDelay = 20,
	recoveryDelay = 30,

	recoverShip = "tier_3_1_a_spy",
	recoveryConversationMobile = "object/mobile/ig_assassin_droid.iff",

	escortShips = {},

	preRecoveryPoints = {
		{patrolPointName = "spy_flight_path_2", zoneName = "space_yavin4", escortNumber = 1, radius = 250},
		{patrolPointName = "spy_flight_path_3", zoneName = "space_yavin4", escortNumber = 2, radius = 250},
		{patrolPointName = "spy_flight_path_4", zoneName = "space_yavin4", escortNumber = 3, radius = 250},
		{patrolPointName = "spy_flight_path_5", zoneName = "space_yavin4", escortNumber = 4, radius = 250},
		{patrolPointName = "spy_flight_path_6", zoneName = "space_yavin4", escortNumber = 5, radius = 250},
		{patrolPointName = "spy_flight_path_7", zoneName = "space_yavin4", escortNumber = 6, radius = 250},
		{patrolPointName = "spy_flight_path_1", zoneName = "space_yavin4", escortNumber = 7, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "spy_recovery_path_1", zoneName = "space_yavin4", escortNumber = 1, radius = 250},
		{patrolPointName = "spy_recovery_path_2", zoneName = "space_yavin4", escortNumber = 2, radius = 250},
		{patrolPointName = "spy_recovery_path_3", zoneName = "space_yavin4", escortNumber = 3, radius = 250},
		{patrolPointName = "spy_recovery_path_4", zoneName = "space_yavin4", escortNumber = 4, radius = 250},
	},

	attackDelay = 70,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier2"},
	},
}

registerScreenPlay("recovery_corellia_rebel_tier3_1", true)

-- Mission 2: Inspect (Space Endor - Rebel fleet forced out of hyperspace, need intel from Hutt smugglers)
inspect_corellia_rebel_tier3_2 = SpaceInspectScreenplay:new {
	className = "inspect_corellia_rebel_tier3_2",

	questName = "corellia_rebel_tier3_2",
	questType = "inspect",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "delivery",
	sideQuestName = "delivery_corellia_rebel_tier3_2_a",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	inspectTargets = {"huttsmuggler"},
	inspectCargo = "sector_recon_data",

	validSpawns = {"space_endor:hutt_smuggler_01", "space_endor:hutt_smuggler_02", "space_endor:hutt_smuggler_route"},
}

registerScreenPlay("inspect_corellia_rebel_tier3_2", true)

-- Mission 3: Delivery (Space Endor - Meet Nym smuggler with intel data from Lok Alliance Navy)
delivery_corellia_rebel_tier3_3 = SpaceDeliveryScreenplay:new {
	className = "delivery_corellia_rebel_tier3_3",

	questName = "corellia_rebel_tier3_3",
	questType = "delivery",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "assassinate_corellia_rebel_tier3_3_a",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	pickupShip = "nym_smuggler",
	deliveryShip = "reb_gunboat_tier3",

	pickupPoint = "space_endor:corellia_rebel_tier_3_3_pickup",
	deliveryPoint = "space_endor:corellia_rebel_tier_3_3_deliver",

	attackDelay = 80,

	attackShips = {
		{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier3"},
		{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier3"},
		{"imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3"},
	},
}

registerScreenPlay("delivery_corellia_rebel_tier3_3", true)

-- Mission 4: Assassinate (Space Dathomir - Stop Imperial fighter officer from reaching Dathomir fleet)
assassinate_corellia_rebel_tier3_4 = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_rebel_tier3_4",

	questType = "assassinate",
	questName = "corellia_rebel_tier3_4",

	questZone = "space_dathomir",

	creditReward = 0,
	itemReward = {},

	sideQuest = true,
	sideQuestType = "patrol",
	sideQuestName = "patrol_corellia_rebel_tier3_4_a",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	arrivalDelay = 15,
	failTimer = 20,

	assassinateSpawns = {
		target = "tieadvanced_quest_officer_rebel_t3",
		escorts = {"imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_rebel_tier3_4_assassin_1", zoneName = "space_dathomir"},
		{patrolPointName = "corellia_rebel_tier3_4_assassin_2", zoneName = "space_dathomir"},
		{patrolPointName = "corellia_rebel_tier3_4_assassin_3", zoneName = "space_dathomir"},
		{patrolPointName = "corellia_rebel_tier3_4_assassin_4", zoneName = "space_dathomir"},
	},
}

registerScreenPlay("assassinate_corellia_rebel_tier3_4", true)

--[[
	Tier 4 -- Aqzow Main Missions (Dathomir/Dantooine/Endor - Black Sun vs Nym Pirates)
]]

-- Mission 1: Survival (Space Dathomir - Hold off Black Sun assault on Nym miners)
survival_corellia_rebel_tier4_1 = SpaceSurvivalScreenplay:new {
	className = "survival_corellia_rebel_tier4_1",

	questName = "corellia_rebel_tier4_1",
	questType = "survival",

	questZone = "space_dathomir",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "space_battle",
	sideQuestName = "space_battle_corellia_rebel_tier4_1_a",
	sideQuestSplitType = "both",
	sideQuestName2 = "space_battle_corellia_rebel_tier4_1_b",

	survivalTime = 300,
	survivalPoint = "space_dathomir:corellia_rebel_tier4_1_survival_point",
	delayToFirstAttack = 5,

	attackDelay = 60,

	attackShips = {
		{"blacksun_fighter_s03_tier4", "blacksun_bomber_s03_tier4", "blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4"},
		{"blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4"},
		{"blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4", "blacksun_marauder_tier4", "blacksun_vehement_tier4"},
		{"blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4"},
	},
}

registerScreenPlay("survival_corellia_rebel_tier4_1", true)

-- Mission 2: Assassinate (Space Dathomir - Terminate Imperial Inquisitor before he reaches the fleet)
assassinate_corellia_rebel_tier4_2 = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_rebel_tier4_2",

	questType = "assassinate",
	questName = "corellia_rebel_tier4_2",

	questZone = "space_dathomir",

	creditReward = 0,
	itemReward = {},

	sideQuest = true,
	sideQuestType = "delivery_no_pickup",
	sideQuestName = "delivery_no_pickup_corellia_rebel_tier4_2_a",
	sideQuestSplitType = "both",
	sideQuestName2 = "rescue_corellia_rebel_tier4_2_b",
	sideQuestType2 = "rescue",

	arrivalDelay = 5,
	failTimer = 20,

	assassinateSpawns = {
		target = "tieadvanced_inquisitor_tier4",
		escorts = {"tieinterceptor_inquisitor_guard", "tieinterceptor_inquisitor_guard", "tieinterceptor_inquisitor_guard", "tieinterceptor_inquisitor_guard", "tieinterceptor_inquisitor_guard", "tieinterceptor_inquisitor_guard"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_rebel_tier4_2_assassin_1", zoneName = "space_dathomir"},
		{patrolPointName = "corellia_rebel_tier4_2_assassin_2", zoneName = "space_dathomir"},
		{patrolPointName = "corellia_rebel_tier4_2_assassin_3", zoneName = "space_dathomir"},
		{patrolPointName = "corellia_rebel_tier4_2_assassin_4", zoneName = "space_dathomir"},
		{patrolPointName = "corellia_rebel_tier4_2_assassin_5", zoneName = "space_dathomir"},
		{patrolPointName = "corellia_rebel_tier4_2_assassin_6", zoneName = "space_dathomir"},
	},
}

registerScreenPlay("assassinate_corellia_rebel_tier4_2", true)

-- Mission 3: Space Battle (Space Dathomir - Guerilla strike on Imperial space station)
space_battle_corellia_rebel_tier4_3 = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_rebel_tier4_3",

	questName = "corellia_rebel_tier4_3",
	questType = "space_battle",

	questZone = "space_dathomir",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "space_battle",
	sideQuestName = "space_battle_corellia_rebel_tier4_3_a",
	sideQuestSplitType = "both",
	sideQuestName2 = "survival_corellia_rebel_tier4_3_b",
	sideQuestType2 = "survival",

	battlePoint = "space_dathomir:corellia_rebel_tier4_3_battle_point",
	allyArrivalDelay = 60,
	enemyArrivalDelay = 30,
	allyOriginDist = 600,
	enemyOriginDist = -1100,
	allyArrivalDist = 50,
	enemyArrivalDist = -200,

	alliedShips = {
		{"nym_fighter_tier4"},
		{"nym_fighter_tier4"},
		{"nym_fighter_tier4"},
		{"nym_fighter_tier4"},
		{"nym_enforcer_tier5"},
	},

	enemyShips = {
		{"imp_imperial_gunboat_tier4"},
		{"imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier4"},
	},
}

registerScreenPlay("space_battle_corellia_rebel_tier4_3", true)

-- Mission 4: Recovery (Space Dantooine - Kidnap Imperial technician building space station)
recovery_corellia_rebel_tier4_4 = SpaceRecoveryScreenplay:new {
	className = "recovery_corellia_rebel_tier4_4",

	questName = "corellia_rebel_tier4_4",
	questType = "recovery",

	questZone = "space_dantooine",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "assassinate_corellia_rebel_tier4_4_a",
	sideQuestSplitType = "both",
	sideQuestName2 = "rescue_corellia_rebel_tier4_4_b",
	sideQuestType2 = "rescue",

	arrivalDelay = 10,
	recoveryDelay = 30,

	recoverShip = "imp_lambda_shuttle_tier4",
	recoveryConversationMobile = "object/mobile/dressed_rebel_commando_moncal_male_01.iff",

	escortShips = {"imp_tie_aggressor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4"},

	preRecoveryPoints = {
		{patrolPointName = "corellia_rebel_tier4_4_recovery_1", zoneName = "space_dantooine", escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_2", zoneName = "space_dantooine", escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_3", zoneName = "space_dantooine", escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_4", zoneName = "space_dantooine", escortNumber = 4, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "corellia_rebel_tier4_4_recovery_5", zoneName = "space_dantooine", escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_6", zoneName = "space_dantooine", escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_7", zoneName = "space_dantooine", escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_8", zoneName = "space_dantooine", escortNumber = 4, radius = 250},
	},

	attackDelay = 50,

	attackShips = {
		{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4", "imp_tie_fighter_tier4", "imp_tie_oppressor_tier4"},
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

-- Escort Duty (Space Dathomir - Escort Nym freighters carrying loot from Imperial outpost raid)
escort_duty_corellia_rebel_tier4_1 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_corellia_rebel_tier4_1",

	questName = "corellia_rebel_tier4_1",
	questType = "escort_duty",

	questZone = "space_dathomir",

	creditReward = 5000,
	creditKillBonus = 300,

	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	escortShips = {"nym_freighterheavy_tier4", "nym_freighterlight_tier4", "nym_freightermedium_tier4"},

	escortPoints = {
		{patrolPointName = "corellia_rebel_tier4_1_escort_duty_1", zoneName = "space_dathomir", escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_escort_duty_2", zoneName = "space_dathomir", escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_escort_duty_3", zoneName = "space_dathomir", escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_escort_duty_4", zoneName = "space_dathomir", escortNumber = 4, radius = 250},
	},

	attackDelay = 50,

	attackShips = {
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_bomber_tier4", "imp_tie_advanced_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"},
	},
}

registerScreenPlay("escort_duty_corellia_rebel_tier4_1", true)

-- Rescue Duty (Space Dantooine - Rescue disabled Rebel ships left after Imperial attack)
rescue_duty_corellia_rebel_tier4_1 = SpaceDutyRescueScreenplay:new {
	className = "rescue_duty_corellia_rebel_tier4_1",

	questName = "corellia_rebel_tier4_1",
	questType = "rescue_duty",

	questZone = "space_dantooine",

	creditReward = 5000,
	creditKillBonus = 300,

	sideQuest = false,
	sideQuestType = "",

	targetShips = {"reb_xwing_tier4", "reb_transport_tier4", "reb_ywing_tier4", "reb_ykl37r_tier4", "reb_freightermedium_tier4", "reb_freighterheavy_tier4", "reb_freighterlight_tier4"},

	targetArrivalDelay = 3,

	recoveryPoints = {
		{patrolPointName = "corellia_rebel_tier4_1_rescue_duty_1", zoneName = "space_dantooine", radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_rescue_duty_2", zoneName = "space_dantooine", radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_rescue_duty_3", zoneName = "space_dantooine", radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_rescue_duty_4", zoneName = "space_dantooine", radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_rescue_duty_5", zoneName = "space_dantooine", radius = 250},
	},

	attackDelay = 60,

	attackShips = {
		{"imp_lambda_shuttle_tier4", "imp_lambda_shuttle_tier4", "imp_lambda_shuttle_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_advanced_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_advanced_tier4"},
	},
}

registerScreenPlay("rescue_duty_corellia_rebel_tier4_1", true)

-- Recovery Duty (Space Endor - Nym pirates infiltrate Imperial troop transports)
recovery_duty_corellia_rebel_tier4_1 = SpaceDutyRecoveryScreenplay:new {
	className = "recovery_duty_corellia_rebel_tier4_1",

	questName = "corellia_rebel_tier4_1",
	questType = "recovery_duty",

	questZone = "space_endor",

	creditReward = 5000,
	creditKillBonus = 300,

	sideQuest = false,
	sideQuestType = "",

	targetShip = "lambdashuttle_troop_transport_ace",
	targetArrivalDelay = 10,
	recoveryDelay = 30,

	recoveryFaction = "nym",
	recoveryConversationMobile = "object/mobile/dressed_nym_brawler_tran_m.iff",

	escortShips = {"imp_tie_interceptor_tier4"},

	preRecoveryPoints = {
		{patrolPointName = "corellia_rebel_tier4_1_recovery_duty_1", zoneName = "space_endor", escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_recovery_duty_2", zoneName = "space_endor", escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_recovery_duty_3", zoneName = "space_endor", escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_recovery_duty_4", zoneName = "space_endor", escortNumber = 4, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "corellia_rebel_tier4_1_recovery_duty_5", zoneName = "space_endor", escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_recovery_duty_6", zoneName = "space_endor", escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_recovery_duty_7", zoneName = "space_endor", escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_1_recovery_duty_8", zoneName = "space_endor", escortNumber = 4, radius = 250},
	},

	attackDelay = 45,

	attackShips = {
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_bomber_tier4", "imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_fighter_tier4", "imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_fighter_tier4", "imp_tie_advanced_tier4"},
	},
}

registerScreenPlay("recovery_duty_corellia_rebel_tier4_1", true)

-- Destroy Duty (Space Dantooine - Nym/Rebel alliance putting the squeeze on the Black Sun)
destroy_duty_corellia_rebel_tier4_1 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_corellia_rebel_tier4_1",

	questName = "corellia_rebel_tier4_1",
	questType = "destroy_duty",

	questZone = "space_dantooine",

	creditReward = 300,

	sideQuest = false,
	sideQuestType = "",

	totalLevels = 5,
	totalRounds = 2,
	totalWaves = 5,

	minDistance = 12500,
	maxDistance = 17500,

	bossShip = "blacksun_marauder_tier4",
	shipTypes = {
		{"blacksun_fighter_s01_tier4", "blacksun_fighter_s01_tier4"},
		{"blacksun_fighter_s01_tier4", "blacksun_fighter_s01_tier4"},
		{"blacksun_fighter_s01_tier4", "blacksun_fighter_s01_tier4"},
		{"blacksun_fighter_s01_tier4"},
		{"blacksun_vehement_tier4"},
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

	removeQuestStatus(playerID .. "HavocSquadronScreenplay:kreezo_finished")
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

	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":introduced")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward")
	removeQuestStatus(playerID .. "HavocSquadron:viopaSmuggler")
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
