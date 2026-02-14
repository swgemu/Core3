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
	Tier 3 -- Aqzow Main Missions (Yavin4)
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
	sideQuestName = "corellia_rebel_tier3_1_A",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	arrivalDelay = 20,
	recoveryDelay = 30,

	recoverShip = "tier_3_1_a_spy",
	recoveryConversationMobile = "object/mobile/ig_assassin_droid.iff",

	escortShips = {},

	preRecoveryPoints = {
		{patrolPointName = "spy_flight_path_2", zoneName = "space_yavin4", x = 4793, z = -5425, y = 4509, escortNumber = 1, radius = 250},
		{patrolPointName = "spy_flight_path_3", zoneName = "space_yavin4", x = 4358, z = -4600, y = 4097, escortNumber = 2, radius = 250},
		{patrolPointName = "spy_flight_path_4", zoneName = "space_yavin4", x = 4040, z = -3996, y = 3796, escortNumber = 3, radius = 250},
		{patrolPointName = "spy_flight_path_5", zoneName = "space_yavin4", x = 3589, z = -3140, y = 3370, escortNumber = 4, radius = 250},
		{patrolPointName = "spy_flight_path_6", zoneName = "space_yavin4", x = 3280, z = -2554, y = 3078, escortNumber = 5, radius = 250},
		{patrolPointName = "spy_flight_path_7", zoneName = "space_yavin4", x = 2073, z = -2087, y = 2117, escortNumber = 6, radius = 250},
		{patrolPointName = "spy_flight_path_1", zoneName = "space_yavin4", x = 5199, z = -6199, y = 4893, escortNumber = 7, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "spy_recovery_path_1", zoneName = "space_yavin4", x = 3463, z = -2741, y = 2867, escortNumber = 1, radius = 250},
		{patrolPointName = "spy_recovery_path_2", zoneName = "space_yavin4", x = 3367, z = -2354, y = 2296, escortNumber = 2, radius = 250},
		{patrolPointName = "spy_recovery_path_3", zoneName = "space_yavin4", x = 3282, z = -2008, y = 1786, escortNumber = 3, radius = 250},
		{patrolPointName = "spy_recovery_path_4", zoneName = "space_yavin4", x = 3143, z = -1446, y = 956, escortNumber = 4, radius = 250},
	},

	attackDelay = 70,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier2"},
	},
}

registerScreenPlay("recovery_corellia_rebel_tier3_1", true)

-- Mission 1 Side Quest A: Patrol (Space Yavin4 - Clear Imperial ships from Rebel escape route)
patrol_corellia_rebel_tier3_1_A = SpacePatrolScreenplay:new {
	className = "patrol_corellia_rebel_tier3_1_A",

	questName = "corellia_rebel_tier3_1_A",
	questType = "patrol",

	questZone = "space_yavin4",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "corellia_rebel_tier3_1_b",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 3,
	sideQuestDelay = 5,

	parentQuest = "recovery_corellia_rebel_tier3_1",
	parentQuestType = "recovery",
	parentQuestName = "corellia_rebel_tier3_1",

	patrolPoints = {
		{patrolPointName = "rebel_tier_three_patrol_1", x = 2793, z = -276, y = -1231, patrolNumber = 1, radius = 150},
		{patrolPointName = "rebel_tier_three_patrol_2", x = 3215, z = -695, y = -1854, patrolNumber = 2, radius = 150},
		{patrolPointName = "rebel_tier_three_patrol_3", x = 3680, z = -853, y = -2726, patrolNumber = 3, radius = 150},
		{patrolPointName = "rebel_tier_three_patrol_4", x = 3975, z = -1404, y = -3805, patrolNumber = 4, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_rebel_tier3_1_A", true)

-- Mission 1 Side Quest B: Destroy Surprise Attack (Space Yavin4 - Destroy Imperial patrol on escape path)
destroy_surpriseattack_corellia_rebel_tier3_1_b = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_corellia_rebel_tier3_1_b",

	questName = "corellia_rebel_tier3_1_b",
	questType = "destroy_surpriseattack",

	questZone = "space_yavin4",

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "corellia_rebel_tier3_1_c",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 0,

	parentQuest = "patrol_corellia_rebel_tier3_1_A",
	parentQuestType = "patrol",
	parentQuestName = "corellia_rebel_tier3_1_A",

	surpriseAttackShips = {
		zone = "space_yavin4",
		spawns = {{count = 3, shipName = "imp_tie_fighter_tier3"}},
	},
}

registerScreenPlay("destroy_surpriseattack_corellia_rebel_tier3_1_b", true)

-- Mission 1 Side Quest C: Assassinate (Space Yavin4 - Stop Imperial scout patrol from escaping)
assassinate_corellia_rebel_tier3_1_c = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_rebel_tier3_1_c",

	questType = "assassinate",
	questName = "corellia_rebel_tier3_1_c",

	questZone = "space_yavin4",

	creditReward = 0,
	itemReward = {},

	sideQuest = true,
	sideQuestType = "space_battle",
	sideQuestName = "corellia_rebel_tier3_1_d",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 0,

	parentQuest = "destroy_surpriseattack_corellia_rebel_tier3_1_b",
	parentQuestType = "destroy_surpriseattack",
	parentQuestName = "corellia_rebel_tier3_1_b",

	arrivalDelay = 2,
	failTimer = 20,

	assassinateSpawns = {
		target = "imp_tie_interceptor_tier2",
		escorts = {"imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
	},

	targetPatrols = {
		{patrolPointName = "imperial_scout_flight_path_1", zoneName = "space_yavin4", x = 3593, z = -1050, y = -3060},
		{patrolPointName = "imperial_scout_flight_path_2", zoneName = "space_yavin4", x = 3255, z = -758, y = -2450},
		{patrolPointName = "imperial_scout_flight_path_3", zoneName = "space_yavin4", x = 2804, z = -215, y = -1382},
		{patrolPointName = "imperial_scout_flight_path_4", zoneName = "space_yavin4", x = 2290, z = 302, y = -266},
	},
}

registerScreenPlay("assassinate_corellia_rebel_tier3_1_c", true)

-- Mission 1 Side Quest D: Space Battle (Space Yavin4 - Assist X-Wing squad against Imperial patrol)
space_battle_corellia_rebel_tier3_1_d = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_rebel_tier3_1_d",

	questName = "corellia_rebel_tier3_1_d",
	questType = "space_battle",

	questZone = "space_yavin4",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "assassinate_corellia_rebel_tier3_1_c",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_rebel_tier3_1_c",

	battlePoint = "space_yavin4:rebel_tier3_1_d_space_battle",
	allyArrivalDelay = 20,
	enemyArrivalDelay = 35,
	allyOriginDist = -600,
	enemyOriginDist = 800,
	allyArrivalDist = -100,
	enemyArrivalDist = 0,

	alliedShips = {
		{"reb_xwing_tier3"},
		{"reb_xwing_tier3"},
		{"reb_xwing_tier3"},
	},

	enemyShips = {
		{"imp_tie_fighter_tier3"},
		{"imp_tie_fighter_tier3"},
		{"imp_tie_fighter_tier3"},
		{"imp_tie_interceptor_tier3"},
		{"imp_tie_interceptor_tier3"},
		{"imp_tie_interceptor_tier3"},
	},
}

registerScreenPlay("space_battle_corellia_rebel_tier3_1_d", true)

-- Mission 2: Inspect (Space Endor - Rebel fleet forced out of hyperspace, need intel from Hutt smugglers)
inspect_corellia_rebel_tier3_2 = SpaceInspectScreenplay:new {
	className = "inspect_corellia_rebel_tier3_2",

	questName = "corellia_rebel_tier3_2",
	questType = "inspect",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "delivery",
	sideQuestName = "corellia_rebel_tier3_2_a",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	inspectTargets = {"huttsmuggler"},
	inspectCargo = "sector_recon_data",

	validSpawns = {"space_endor:hutt_smuggler_01", "space_endor:hutt_smuggler_02", "space_endor:hutt_smuggler_route"},
}

registerScreenPlay("inspect_corellia_rebel_tier3_2", true)

-- Mission 2 Side Quest A: Delivery (Space Lok - Deliver data to Alliance fleet)
delivery_corellia_rebel_tier3_2_a = SpaceDeliveryScreenplay:new {
	className = "delivery_corellia_rebel_tier3_2_a",

	questName = "corellia_rebel_tier3_2_a",
	questType = "delivery",

	questZone = "space_lok",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "survival",
	sideQuestName = "corellia_rebel_tier3_2_b",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 3,

	parentQuest = "inspect_corellia_rebel_tier3_2",
	parentQuestType = "inspect",
	parentQuestName = "corellia_rebel_tier3_2",

	pickupShip = "reb_xwing_tier2",
	deliveryShip = "reb_awing_tier3",

	pickupPoint = "space_lok:rebel_tier3_2_a_meeting",
	deliveryPoint = "space_lok:rebel_tier3_2_a_delivery",

	attackDelay = 70,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier3", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
	},
}

registerScreenPlay("delivery_corellia_rebel_tier3_2_a", true)

-- Mission 2 Side Quest B: Survival (Space Endor - Defend fleet from Imperial fighter wings)
survival_corellia_rebel_tier3_2_b = SpaceSurvivalScreenplay:new {
	className = "survival_corellia_rebel_tier3_2_b",

	questName = "corellia_rebel_tier3_2_b",
	questType = "survival",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestName = "corellia_rebel_tier3_2_c",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 0,

	parentQuest = "delivery_corellia_rebel_tier3_2_a",
	parentQuestType = "delivery",
	parentQuestName = "corellia_rebel_tier3_2_a",

	survivalTime = 600,
	survivalPoint = "space_endor:rebel_tier3_2_b_defend_point",
	delayToFirstAttack = 5,

	attackDelay = 100,

	attackShips = {
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_bomber_tier2", "imp_tie_bomber_tier2", "imp_tie_bomber_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_fighter_tier2", "imp_tie_bomber_tier2", "imp_tie_bomber_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_interceptor_tier2", "imp_tie_interceptor_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
	},
}

registerScreenPlay("survival_corellia_rebel_tier3_2_b", true)

-- Mission 2 Side Quest C: Escort (Space Endor - Escort straggling freighter to new fleet position)
escort_corellia_rebel_tier3_2_c = SpaceEscortScreenplay:new {
	className = "escort_corellia_rebel_tier3_2_c",

	questName = "corellia_rebel_tier3_2_c",
	questType = "escort",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "survival_corellia_rebel_tier3_2_b",
	parentQuestType = "survival",
	parentQuestName = "corellia_rebel_tier3_2_b",

	escortShips = {"reb_freighterlight_tier3"},

	escortPoints = {
		{patrolPointName = "rebel_tier3_2_c_escort_1", zoneName = "space_endor", x = -239, z = 3935, y = 3280, escortNumber = 1, radius = 250},
		{patrolPointName = "rebel_tier3_2_c_escort_2", zoneName = "space_endor", x = -549, z = 3180, y = 3238, escortNumber = 2, radius = 250},
		{patrolPointName = "rebel_tier3_2_c_escort_3", zoneName = "space_endor", x = -1251, z = 1477, y = 3143, escortNumber = 3, radius = 250},
		{patrolPointName = "rebel_tier3_2_c_escort_4", zoneName = "space_endor", x = -1996, z = -330, y = 3042, escortNumber = 4, radius = 250},
	},

	attackDelay = 80,

	attackShips = {
		{"imp_tie_interceptor_tier2", "imp_tie_interceptor_tier2"},
		{"imp_tie_fighter_tier2", "imp_tie_interceptor_tier2"},
	},
}

registerScreenPlay("escort_corellia_rebel_tier3_2_c", true)

-- Mission 3: Delivery (Space Endor - Meet Nym smuggler with intel data from Lok Alliance Navy)
delivery_corellia_rebel_tier3_3 = SpaceDeliveryScreenplay:new {
	className = "delivery_corellia_rebel_tier3_3",

	questName = "corellia_rebel_tier3_3",
	questType = "delivery",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "corellia_rebel_tier3_3_a",
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

-- Mission 3 Side Quest A: Assassinate (Space Endor - Destroy Imperial advanced recon ship)
assassinate_corellia_rebel_tier3_3_a = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_rebel_tier3_3_a",

	questType = "assassinate",
	questName = "corellia_rebel_tier3_3_a",

	questZone = "space_endor",

	creditReward = 0,
	itemReward = {},

	sideQuest = true,
	sideQuestType = "space_battle",
	sideQuestName = "corellia_rebel_tier3_3_b",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 0,

	parentQuest = "delivery_corellia_rebel_tier3_3",
	parentQuestType = "delivery",
	parentQuestName = "corellia_rebel_tier3_3",

	arrivalDelay = 20,
	failTimer = 20,

	assassinateSpawns = {
		target = "lambdashuttle_advanced_recon",
		escorts = {"imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3", "imp_tie_interceptor_tier3"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_rebel_tier3_3_a_spyship_1", zoneName = "space_endor", x = 2940, z = -4680, y = 1200},
		{patrolPointName = "corellia_rebel_tier3_3_a_spyship_2", zoneName = "space_endor", x = 2922, z = -3692, y = 1654},
		{patrolPointName = "corellia_rebel_tier3_3_a_spyship_3", zoneName = "space_endor", x = 2900, z = -2445, y = 2228},
		{patrolPointName = "corellia_rebel_tier3_3_a_spyship_4", zoneName = "space_endor", x = 2892, z = -1093, y = 2859},
		{patrolPointName = "corellia_rebel_tier3_3_a_spyship_5", zoneName = "space_endor", x = 2892, z = 55, y = 3394},
		{patrolPointName = "corellia_rebel_tier3_3_a_spyship_6", zoneName = "space_endor", x = 2892, z = 1122, y = 3890},
	},
}

registerScreenPlay("assassinate_corellia_rebel_tier3_3_a", true)

-- Mission 3 Side Quest B: Space Battle (Space Endor - Assist Green squadron against TIE wing)
space_battle_corellia_rebel_tier3_3_b = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_rebel_tier3_3_b",

	questName = "corellia_rebel_tier3_3_b",
	questType = "space_battle",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestName = "corellia_rebel_tier3_3_c",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 0,

	parentQuest = "assassinate_corellia_rebel_tier3_3_a",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_rebel_tier3_3_a",

	battlePoint = "space_endor:corellia_rebel_tier3_3_b_battlepoint",
	allyArrivalDelay = 60,
	enemyArrivalDelay = 85,
	allyOriginDist = 500,
	enemyOriginDist = -750,
	allyArrivalDist = 50,
	enemyArrivalDist = -200,

	alliedShips = {
		{"reb_ywing_tier3"},
		{"reb_ywing_tier3"},
		{"reb_ywing_tier3"},
	},

	enemyShips = {
		{"imp_tie_fighter_tier3"},
		{"imp_tie_fighter_tier3"},
		{"imp_tie_fighter_tier3"},
		{"imp_tie_interceptor_tier3"},
		{"imp_tie_interceptor_tier3"},
		{"imp_tie_interceptor_tier3"},
	},
}

registerScreenPlay("space_battle_corellia_rebel_tier3_3_b", true)

-- Mission 3 Side Quest C: Escort (Space Endor - Escort Rebel smuggler transporting fleet repair materials)
escort_corellia_rebel_tier3_3_c = SpaceEscortScreenplay:new {
	className = "escort_corellia_rebel_tier3_3_c",

	questName = "corellia_rebel_tier3_3_c",
	questType = "escort",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "space_battle_corellia_rebel_tier3_3_b",
	parentQuestType = "space_battle",
	parentQuestName = "corellia_rebel_tier3_3_b",

	escortShips = {"rebel_smuggler_tier3"},

	escortPoints = {
		{patrolPointName = "corellia_rebel_tier3_3_c_escort_1", zoneName = "space_endor", x = -5250, z = -850, y = 2000, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier3_3_c_escort_2", zoneName = "space_endor", x = -4323, z = -525, y = 2310, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier3_3_c_escort_3", zoneName = "space_endor", x = -3632, z = -680, y = 1552, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier3_3_c_escort_4", zoneName = "space_endor", x = -2813, z = -400, y = 1793, escortNumber = 4, radius = 250},
	},

	attackDelay = 55,

	attackShips = {
		{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier3"},
		{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier3"},
	},
}

registerScreenPlay("escort_corellia_rebel_tier3_3_c", true)

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
	sideQuestName = "corellia_rebel_tier3_4_a",
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

-- Mission 4 Side Quest A: Patrol (Space Endor - Search for missing Magenta squadron)
patrol_corellia_rebel_tier3_4_a = SpacePatrolScreenplay:new {
	className = "patrol_corellia_rebel_tier3_4_a",

	questName = "corellia_rebel_tier3_4_a",
	questType = "patrol",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "corellia_rebel_tier3_4_b",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 3,
	sideQuestDelay = 5,

	parentQuest = "assassinate_corellia_rebel_tier3_4",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_rebel_tier3_4",

	patrolPoints = {
		{patrolPointName = "corellia_rebel_tier3_4_a_patrol_1", x = -3960, z = -400, y = -4950, patrolNumber = 1, radius = 150},
		{patrolPointName = "corellia_rebel_tier3_4_a_patrol_2", x = -3758, z = 345, y = -4588, patrolNumber = 2, radius = 150},
		{patrolPointName = "corellia_rebel_tier3_4_a_patrol_3", x = -3460, z = 37, y = -3563, patrolNumber = 3, radius = 150},
		{patrolPointName = "corellia_rebel_tier3_4_a_patrol_4", x = -2777, z = 778, y = -3350, patrolNumber = 4, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_rebel_tier3_4_a", true)

-- Mission 4 Side Quest B: Destroy Surprise Attack (Space Endor - Imperial Elite Ambush squad)
destroy_surpriseattack_corellia_rebel_tier3_4_b = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_corellia_rebel_tier3_4_b",

	questName = "corellia_rebel_tier3_4_b",
	questType = "destroy_surpriseattack",

	questZone = "space_endor",

	sideQuest = true,
	sideQuestType = "space_battle",
	sideQuestName = "corellia_rebel_tier3_4_c",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 0,

	parentQuest = "patrol_corellia_rebel_tier3_4_a",
	parentQuestType = "patrol",
	parentQuestName = "corellia_rebel_tier3_4_a",

	surpriseAttackShips = {
		zone = "space_endor",
		spawns = {{count = 6, shipName = "imp_tie_interceptor_tier3"}},
	},
}

registerScreenPlay("destroy_surpriseattack_corellia_rebel_tier3_4_b", true)

-- Mission 4 Side Quest C: Space Battle (Space Endor - Assist Blue Squadron attacking TIE bomber wing)
space_battle_corellia_rebel_tier3_4_c = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_rebel_tier3_4_c",

	questName = "corellia_rebel_tier3_4_c",
	questType = "space_battle",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "survival",
	sideQuestName = "corellia_rebel_tier3_4_d",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 0,

	parentQuest = "destroy_surpriseattack_corellia_rebel_tier3_4_b",
	parentQuestType = "destroy_surpriseattack",
	parentQuestName = "corellia_rebel_tier3_4_b",

	battlePoint = "space_endor:corellia_rebel_tier3_4_c_battlepoint",
	allyArrivalDelay = 60,
	enemyArrivalDelay = 80,
	allyOriginDist = 800,
	enemyOriginDist = -800,
	allyArrivalDist = 100,
	enemyArrivalDist = -50,

	alliedShips = {
		{"reb_bwing_tier3"},
		{"reb_bwing_tier3"},
		{"reb_ywing_tier3"},
		{"reb_ywing_tier3"},
	},

	enemyShips = {
		{"imp_tie_bomber_tier3"},
		{"imp_tie_bomber_tier3"},
		{"imp_tie_bomber_tier3"},
		{"imp_tie_fighter_tier3"},
		{"imp_tie_fighter_tier3"},
		{"imp_tie_fighter_tier3"},
	},
}

registerScreenPlay("space_battle_corellia_rebel_tier3_4_c", true)

-- Mission 4 Side Quest D: Survival (Space Endor - Guard fleet flank during hyperspace evacuation)
survival_corellia_rebel_tier3_4_d = SpaceSurvivalScreenplay:new {
	className = "survival_corellia_rebel_tier3_4_d",

	questName = "corellia_rebel_tier3_4_d",
	questType = "survival",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "space_battle_corellia_rebel_tier3_4_c",
	parentQuestType = "space_battle",
	parentQuestName = "corellia_rebel_tier3_4_c",

	survivalTime = 300,
	survivalPoint = "space_endor:corellia_rebel_tier3_4_c_survival",
	delayToFirstAttack = 5,

	attackDelay = 60,

	attackShips = {
		{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier3", "imp_tie_bomber_tier3"},
		{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier3", "imp_tie_bomber_tier3"},
		{"imp_tie_fighter_tier3", "imp_tie_interceptor_tier3", "imp_tie_bomber_tier3"},
	},
}

registerScreenPlay("survival_corellia_rebel_tier3_4_d", true)

--[[
	Tier 4 -- Arkon Main Missions (Dathomir/Dantooine/Endor - Black Sun vs Nym Pirates)
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
	sideQuestName = "corellia_rebel_tier4_1_a",
	sideQuestType2 = "space_battle",
	sideQuestName2 = "corellia_rebel_tier4_1_b",

	-- sideQuestSplitType = "both",

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

-- Mission 1 Side Quest A: Space Battle (Space Dathomir - Counter attack against Black Sun)
space_battle_corellia_rebel_tier4_1_a = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_rebel_tier4_1_a",

	questName = "corellia_rebel_tier4_1_a",
	questType = "space_battle",

	questZone = "space_dathomir",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "survival_corellia_rebel_tier4_1",
	parentQuestType = "survival",
	parentQuestName = "corellia_rebel_tier4_1",

	battlePoint = "space_dathomir:corellia_rebel_tier4_1_a_battle_point",
	allyArrivalDelay = 85,
	enemyArrivalDelay = 60,
	allyOriginDist = 600,
	enemyOriginDist = -850,
	allyArrivalDist = 50,
	enemyArrivalDist = -100,

	alliedShips = {
		{"nym_enforcer_tier4"},
		{"nym_enforcer_tier4"},
		{"nym_enforcer_tier4"},
		{"reb_xwing_tier4"},
		{"reb_xwing_tier4"},
	},

	enemyShips = {
		{"blacksun_fighter_s02_tier4"},
		{"blacksun_fighter_s02_tier4"},
		{"blacksun_fighter_s02_tier4"},
		{"blacksun_fighter_s03_tier4"},
		{"blacksun_fighter_s03_tier4"},
		{"blacksun_fighter_s03_tier4"},
		{"blacksun_marauder_tier4"},
		{"blacksun_vehement_tier4"},
		{"blacksun_marauder_tier4"},
	},
}

registerScreenPlay("space_battle_corellia_rebel_tier4_1_a", true)

-- Mission 1 Side Quest B: Space Battle (Space Dathomir - Save Nym freighters from Black Sun)
space_battle_corellia_rebel_tier4_1_b = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_rebel_tier4_1_b",

	questName = "corellia_rebel_tier4_1_b",
	questType = "space_battle",

	questZone = "space_dathomir",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "survival_corellia_rebel_tier4_1",
	parentQuestType = "survival",
	parentQuestName = "corellia_rebel_tier4_1",

	battlePoint = "space_dathomir:corellia_rebe_tier4_1_b_battle_point",
	allyArrivalDelay = 30,
	enemyArrivalDelay = 45,
	allyOriginDist = 600,
	enemyOriginDist = -850,
	allyArrivalDist = 50,
	enemyArrivalDist = -100,

	alliedShips = {
		{"nym_fighter_tier4"},
		{"nym_fighter_tier4"},
		{"nym_fighter_tier4"},
		{"nym_freighterheavy_tier4"},
		{"nym_freighterlight_tier4"},
		{"nym_freightermedium_tier4"},
	},

	enemyShips = {
		{"blacksun_fighter_s02_tier4"},
		{"blacksun_fighter_s02_tier4"},
		{"blacksun_fighter_s02_tier4"},
		{"blacksun_fighter_s02_tier4"},
		{"blacksun_fighter_s02_tier4"},
		{"blacksun_gunship_tier4"},
	},
}

registerScreenPlay("space_battle_corellia_rebel_tier4_1_b", true)

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
	sideQuestName = "corellia_rebel_tier4_2_a",
	sideQuestType2 = "rescue",
	sideQuestName2 = "corellia_rebel_tier4_2_b",

	-- sideQuestSplitType = "both",

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

-- Mission 2 Side Quest A: Delivery No Pickup (Space Dathomir - Deliver Inquisitor wreck data)
delivery_no_pickup_corellia_rebel_tier4_2_a = SpaceDeliveryNoPickupScreenplay:new {
	className = "delivery_no_pickup_corellia_rebel_tier4_2_a",

	questName = "corellia_rebel_tier4_2_a",
	questType = "delivery_no_pickup",

	questZone = "space_dathomir",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "assassinate_corellia_rebel_tier4_2",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_rebel_tier4_2",

	deliveryShip = "rebel_smuggler_tier3",
	deliveryPoint = "space_dathomir:corellia_rebel_tier4_2_a_delivery",

	attackDelay = 45,

	attackShips = {
		{"imp_tie_interceptor_tier4", "imp_tie_advanced_tier4", "imp_tie_fighter_tier4"},
		{"imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_fighter_tier4"},
		{"imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier3", "imp_tie_fighter_tier3", "imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier3", "imp_tie_fighter_tier3", "imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier3", "imp_tie_fighter_tier3", "imp_tie_fighter_tier4"},
	},
}

registerScreenPlay("delivery_no_pickup_corellia_rebel_tier4_2_a", true)

-- Mission 2 Side Quest B: Rescue (Space Dathomir - Rescue Rebel diplomat ambushed by Imperials)
rescue_corellia_rebel_tier4_2_b = SpaceRescueScreenplay:new {
	className = "rescue_corellia_rebel_tier4_2_b",

	questName = "corellia_rebel_tier4_2_b",
	questType = "rescue",

	questZone = "space_dathomir",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "assassinate_corellia_rebel_tier4_2",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_rebel_tier4_2",

	rescueShip = "reb_diplomat_tier4",
	rescueArrivalDelay = 3,

	rescuePoints = {
		{patrolPointName = "corellia_rebel_tier4_2_b_rescue_1", zoneName = "space_dathomir", x = 3872, z = 4158, y = -2791, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_2_b_rescue_2", zoneName = "space_dathomir", x = 2827, z = 3579, y = -4145, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_2_b_rescue_3", zoneName = "space_dathomir", x = 2103, z = 3204, y = -5079, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_2_b_rescue_4", zoneName = "space_dathomir", x = 1424, z = 2853, y = -5956, escortNumber = 4, radius = 250},
	},

	attackDelay = 50,

	attackShips = {
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_bomber_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_fighter_tier3", "imp_tie_fighter_tier3", "imp_tie_fighter_tier3"},
		{"imp_tie_fighter_tier3", "imp_tie_fighter_tier3", "imp_tie_fighter_tier3"},
		{"imp_tie_fighter_tier3", "imp_tie_fighter_tier3", "imp_tie_fighter_tier3"},
	},
}

registerScreenPlay("rescue_corellia_rebel_tier4_2_b", true)

-- Mission 3: Space Battle (Space Dathomir - Guerilla strike on Imperial space station)
space_battle_corellia_rebel_tier4_3 = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_rebel_tier4_3",

	questName = "corellia_rebel_tier4_3",
	questType = "space_battle",

	questZone = "space_dathomir",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "space_battle",
	sideQuestName = "corellia_rebel_tier4_3_a",
	sideQuestType2 = "survival",
	sideQuestName2 = "corellia_rebel_tier4_3_b",

	-- sideQuestSplitType = "both",

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

-- Mission 3 Side Quest A: Space Battle (Space Dathomir - Help ambushed B-Wing squadrons)
space_battle_corellia_rebel_tier4_3_a = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_rebel_tier4_3_a",

	questName = "corellia_rebel_tier4_3_a",
	questType = "space_battle",

	questZone = "space_dathomir",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "space_battle_corellia_rebel_tier4_3",
	parentQuestType = "space_battle",
	parentQuestName = "corellia_rebel_tier4_3",

	battlePoint = "space_dathomir:corellia_rebel_tier4_3_a_battle_point",
	allyArrivalDelay = 30,
	enemyArrivalDelay = 45,
	allyOriginDist = 600,
	enemyOriginDist = -700,
	allyArrivalDist = 50,
	enemyArrivalDist = -150,

	alliedShips = {
		{"reb_bwing_tier4"},
		{"reb_bwing_tier4"},
		{"reb_bwing_tier4"},
	},

	enemyShips = {
		{"imp_tie_aggressor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
	},
}

registerScreenPlay("space_battle_corellia_rebel_tier4_3_a", true)

-- Mission 3 Side Quest B: Survival (Space Dathomir - Defend Rebel bombers retreat after failed station attack)
survival_corellia_rebel_tier4_3_b = SpaceSurvivalScreenplay:new {
	className = "survival_corellia_rebel_tier4_3_b",

	questName = "corellia_rebel_tier4_3_b",
	questType = "survival",

	questZone = "space_dathomir",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "space_battle_corellia_rebel_tier4_3",
	parentQuestType = "space_battle",
	parentQuestName = "corellia_rebel_tier4_3",

	survivalTime = 480,
	survivalPoint = "space_dathomir:corellia_rebel_tier4_3_b_survival",
	delayToFirstAttack = 5,

	attackDelay = 45,

	attackShips = {
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_advanced_tier4", "imp_tie_aggressor_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_fighter_tier4"},
	},
}

registerScreenPlay("survival_corellia_rebel_tier4_3_b", true)

-- Mission 4: Recovery (Space Dantooine - Kidnap Imperial technician building space station)
recovery_corellia_rebel_tier4_4 = SpaceRecoveryScreenplay:new {
	className = "recovery_corellia_rebel_tier4_4",

	questName = "corellia_rebel_tier4_4",
	questType = "recovery",

	questZone = "space_dantooine",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "corellia_rebel_tier4_4_a",
	sideQuestType2 = "rescue",
	sideQuestName2 = "corellia_rebel_tier4_4_b",

	-- sideQuestSplitType = "both",

	arrivalDelay = 10,
	recoveryDelay = 30,

	recoverShip = "imp_lambda_shuttle_tier4",
	recoveryConversationMobile = "object/mobile/dressed_rebel_commando_moncal_male_01.iff",

	escortShips = {"imp_tie_aggressor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4"},

	preRecoveryPoints = {
		{patrolPointName = "corellia_rebel_tier4_4_recovery_1", zoneName = "space_dantooine", x = -4000, z = 3100, y = 2700, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_2", zoneName = "space_dantooine", x = -4400, z = 4410, y = 3481, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_3", zoneName = "space_dantooine", x = -4742, z = 5529, y = 4148, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_4", zoneName = "space_dantooine", x = -5049, z = 6532, y = 4746, escortNumber = 4, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "corellia_rebel_tier4_4_recovery_5", zoneName = "space_dantooine", x = -5330, z = 5655, y = 5488, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_6", zoneName = "space_dantooine", x = -5758, z = 5051, y = 6420, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_7", zoneName = "space_dantooine", x = -6046, z = 4645, y = 7048, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_recovery_8", zoneName = "space_dantooine", x = -7031, z = 4120, y = 6583, escortNumber = 4, radius = 250},
	},

	attackDelay = 50,

	attackShips = {
		{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4", "imp_tie_fighter_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4", "imp_tie_fighter_tier4", "imp_tie_oppressor_tier4"},
	},
}

registerScreenPlay("recovery_corellia_rebel_tier4_4", true)

-- Mission 4 Side Quest A: Assassinate (Space Endor - Destroy Imperial freighters carrying station materials)
assassinate_corellia_rebel_tier4_4_a = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_rebel_tier4_4_a",

	questType = "assassinate",
	questName = "corellia_rebel_tier4_4_a",

	questZone = "space_endor",

	creditReward = 0,
	itemReward = {},

	sideQuest = true,
	sideQuestType = "space_battle",
	sideQuestName = "corellia_rebel_tier4_4_c",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 0,

	parentQuest = "rescue_corellia_rebel_tier4_4_b",
	parentQuestType = "rescue",
	parentQuestName = "corellia_rebel_tier4_4_b",

	arrivalDelay = 10,
	failTimer = 20,

	assassinateSpawns = {
		target = "imp_freighterheavy_tier4",
		escorts = {"imp_tie_aggressor_tier4", "imp_tie_aggressor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4", "imp_tie_aggressor_tier4", "freighterlight_corellia_rebel_mission", "freightermedium_corellia_rebel_mission"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_rebel_tier4_4_a_assassinate_1", zoneName = "space_endor", x = 19, z = 5591, y = 1371},
		{patrolPointName = "corellia_rebel_tier4_4_a_assassinate_2", zoneName = "space_endor", x = 552, z = 5543, y = -5},
		{patrolPointName = "corellia_rebel_tier4_4_a_assassinate_3", zoneName = "space_endor", x = 2059, z = 5543, y = -1021},
		{patrolPointName = "corellia_rebel_tier4_4_a_assassinate_4", zoneName = "space_endor", x = 2632, z = 5518, y = -2724},
		{patrolPointName = "corellia_rebel_tier4_4_a_assassinate_5", zoneName = "space_endor", x = 4049, z = 5491, y = -4471},
		{patrolPointName = "corellia_rebel_tier4_4_a_assassinate_6", zoneName = "space_endor", x = 7162, z = 5467, y = -4481},
	},
}

registerScreenPlay("assassinate_corellia_rebel_tier4_4_a", true)

-- Mission 4 Side Quest B: Rescue (Space Endor - Escort SpyNet operative to safety for freighter route intel)
rescue_corellia_rebel_tier4_4_b = SpaceRescueScreenplay:new {
	className = "rescue_corellia_rebel_tier4_4_b",

	questName = "corellia_rebel_tier4_4_b",
	questType = "rescue",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "corellia_rebel_tier4_4_a",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 0,

	parentQuest = "recovery_corellia_rebel_tier4_4",
	parentQuestType = "recovery",
	parentQuestName = "corellia_rebel_tier4_4",

	rescueShip = "spynet_spy_tier4",
	rescueArrivalDelay = 5,

	rescuePoints = {
		{patrolPointName = "corellia_rebel_tier4_4_b_rescue_1", zoneName = "space_endor", x = -961, z = -5548, y = 513, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_b_rescue_2", zoneName = "space_endor", x = -1637, z = -5535, y = 354, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_b_rescue_3", zoneName = "space_endor", x = -2330, z = -5523, y = 191, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_b_rescue_4", zoneName = "space_endor", x = -3110, z = -5509, y = 7, escortNumber = 4, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_b_rescue_5", zoneName = "space_endor", x = -3915, z = -5494, y = -182, escortNumber = 5, radius = 250},
		{patrolPointName = "corellia_rebel_tier4_4_b_rescue_6", zoneName = "space_endor", x = -4794, z = -5884, y = -52, escortNumber = 6, radius = 250},
	},

	attackDelay = 50,

	attackShips = {
		{"imp_tie_advanced_tier4", "imp_tie_aggressor_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4", "imp_tie_interceptor_tier4", "imp_tie_oppressor_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_fighter_tier4"},
		{"imp_tie_fighter_tier4", "imp_tie_fighter_tier4", "imp_tie_fighter_tier4"},
	},
}

registerScreenPlay("rescue_corellia_rebel_tier4_4_b", true)

-- Mission 4 Side Quest C: Space Battle (Space Endor - Imperial retaliation for freighter attack)
space_battle_corellia_rebel_tier4_4_c = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_rebel_tier4_4_c",

	questName = "corellia_rebel_tier4_4_c",
	questType = "space_battle",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "assassinate_corellia_rebel_tier4_4_a",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_rebel_tier4_4_a",

	battlePoint = "space_endor:corellia_rebel_tier4_4_c_battle_point",
	allyArrivalDelay = 60,
	enemyArrivalDelay = 85,
	allyOriginDist = 800,
	enemyOriginDist = -850,
	allyArrivalDist = 150,
	enemyArrivalDist = -200,

	alliedShips = {
		{"reb_xwing_tier4"},
		{"reb_xwing_tier4"},
		{"reb_bwing_tier4"},
		{"nym_fighter_tier4"},
		{"nym_fighter_tier4"},
	},

	enemyShips = {
		{"imp_decimator_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_interceptor_tier4"},
		{"imp_tie_oppressor_tier4"},
		{"imp_tie_advanced_tier4"},
	},
}

registerScreenPlay("space_battle_corellia_rebel_tier4_4_c", true)

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
	TIER3_QUEST_STRING_1_SIDE1 = {type = "patrol", name = "patrol_corellia_rebel_tier3_1_A"},
	TIER3_QUEST_STRING_1_SIDE2 = {type = "destroy_surpriseattack", name = "corellia_rebel_tier3_1_b"},
	TIER3_QUEST_STRING_1_SIDE3 = {type = "assassinate", name = "corellia_rebel_tier3_1_c"},
	TIER3_QUEST_STRING_1_SIDE4 = {type = "space_battle", name = "corellia_rebel_tier3_1_d"},
	TIER3_QUEST_STRING_2 = {type = "inspect", name = "corellia_rebel_tier3_2"},
	TIER3_QUEST_STRING_2_SIDE1 = {type = "delivery", name = "delivery_corellia_rebel_tier3_2_a"},
	TIER3_QUEST_STRING_2_SIDE2 = {type = "survival", name = "corellia_rebel_tier3_2_b"},
	TIER3_QUEST_STRING_2_SIDE3 = {type = "escort", name = "corellia_rebel_tier3_2_c"},
	TIER3_QUEST_STRING_3 = {type = "delivery", name = "corellia_rebel_tier3_3"},
	TIER3_QUEST_STRING_3_SIDE1 = {type = "assassinate", name = "corellia_rebel_tier3_3_a"},
	TIER3_QUEST_STRING_3_SIDE2 = {type = "space_battle", name = "corellia_rebel_tier3_3_b"},
	TIER3_QUEST_STRING_3_SIDE3 = {type = "escort", name = "corellia_rebel_tier3_3_c"},
	TIER3_QUEST_STRING_4 = {type = "assassinate", name = "corellia_rebel_tier3_4"},
	TIER3_QUEST_STRING_4_SIDE1 = {type = "patrol", name = "patrol_corellia_rebel_tier3_4_a"},
	TIER3_QUEST_STRING_4_SIDE2 = {type = "destroy_surpriseattack", name = "corellia_rebel_tier3_4_b"},
	TIER3_QUEST_STRING_4_SIDE3 = {type = "space_battle", name = "corellia_rebel_tier3_4_c"},
	TIER3_QUEST_STRING_4_SIDE4 = {type = "survival", name = "corellia_rebel_tier3_4_d"},

	-- Tier 4 (Aqzow)
	TIER4_QUEST_STRING_1 = {type = "survival", name = "corellia_rebel_tier4_1"},
	TIER4_QUEST_STRING_1_SIDE1 = {type = "space_battle", name = "space_battle_corellia_rebel_tier4_1_a"},
	TIER4_QUEST_STRING_1_SIDE2 = {type = "space_battle", name = "space_battle_corellia_rebel_tier4_1_b"},
	TIER4_QUEST_STRING_2 = {type = "assassinate", name = "corellia_rebel_tier4_2"},
	TIER4_QUEST_STRING_2_SIDE1 = {type = "delivery_no_pickup", name = "delivery_no_pickup_corellia_rebel_tier4_2_a"},
	TIER4_QUEST_STRING_2_SIDE2 = {type = "rescue", name = "rescue_corellia_rebel_tier4_2_b"},
	TIER4_QUEST_STRING_3 = {type = "space_battle", name = "corellia_rebel_tier4_3"},
	TIER4_QUEST_STRING_3_SIDE1 = {type = "space_battle", name = "space_battle_corellia_rebel_tier4_3_a"},
	TIER4_QUEST_STRING_3_SIDE2 = {type = "survival", name = "survival_corellia_rebel_tier4_3_b"},
	TIER4_QUEST_STRING_4 = {type = "recovery", name = "corellia_rebel_tier4_4"},
	TIER4_QUEST_STRING_4_SIDE1 = {type = "assassinate", name = "assassinate_corellia_rebel_tier4_4_a"},
	TIER4_QUEST_STRING_4_SIDE2 = {type = "rescue", name = "rescue_corellia_rebel_tier4_4_b"},
	TIER4_QUEST_STRING_4_SIDE3 = {type = "space_battle", name = "corellia_rebel_tier4_4_c"},
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

function HavocSquadronScreenplay:resetAqzowQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- Mission 1
	recovery_corellia_rebel_tier3_1:resetQuest(pPlayer)
	patrol_corellia_rebel_tier3_1_A:resetQuest(pPlayer)
	destroy_surpriseattack_corellia_rebel_tier3_1_b:resetQuest(pPlayer)
	assassinate_corellia_rebel_tier3_1_c:resetQuest(pPlayer)
	space_battle_corellia_rebel_tier3_1_d:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1.type, self.TIER3_QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1_SIDE1.type, self.TIER3_QUEST_STRING_1_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1_SIDE2.type, self.TIER3_QUEST_STRING_1_SIDE2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1_SIDE3.type, self.TIER3_QUEST_STRING_1_SIDE3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1_SIDE4.type, self.TIER3_QUEST_STRING_1_SIDE4.name, false)

	-- Mission 2
	inspect_corellia_rebel_tier3_2:resetQuest(pPlayer)
	delivery_corellia_rebel_tier3_2_a:resetQuest(pPlayer)
	survival_corellia_rebel_tier3_2_b:resetQuest(pPlayer)
	escort_corellia_rebel_tier3_2_c:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2.type, self.TIER3_QUEST_STRING_2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2_SIDE1.type, self.TIER3_QUEST_STRING_2_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2_SIDE2.type, self.TIER3_QUEST_STRING_2_SIDE2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2_SIDE3.type, self.TIER3_QUEST_STRING_2_SIDE3.name, false)

	-- Mission 3
	delivery_corellia_rebel_tier3_3:resetQuest(pPlayer)
	assassinate_corellia_rebel_tier3_3_a:resetQuest(pPlayer)
	space_battle_corellia_rebel_tier3_3_b:resetQuest(pPlayer)
	escort_corellia_rebel_tier3_3_c:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3.type, self.TIER3_QUEST_STRING_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3_SIDE1.type, self.TIER3_QUEST_STRING_3_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3_SIDE2.type, self.TIER3_QUEST_STRING_3_SIDE2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3_SIDE3.type, self.TIER3_QUEST_STRING_3_SIDE3.name, false)

	-- Mission 4
	assassinate_corellia_rebel_tier3_4:resetQuest(pPlayer)
	patrol_corellia_rebel_tier3_4_a:resetQuest(pPlayer)
	destroy_surpriseattack_corellia_rebel_tier3_4_b:resetQuest(pPlayer)
	space_battle_corellia_rebel_tier3_4_c:resetQuest(pPlayer)
	survival_corellia_rebel_tier3_4_d:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4.type, self.TIER3_QUEST_STRING_4.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4_SIDE1.type, self.TIER3_QUEST_STRING_4_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4_SIDE2.type, self.TIER3_QUEST_STRING_4_SIDE2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4_SIDE3.type, self.TIER3_QUEST_STRING_4_SIDE3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4_SIDE4.type, self.TIER3_QUEST_STRING_4_SIDE4.name, false)

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

function HavocSquadronScreenplay:resetArkonQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- Mission 1
	survival_corellia_rebel_tier4_1:resetQuest(pPlayer)
	space_battle_corellia_rebel_tier4_1_a:resetQuest(pPlayer)
	space_battle_corellia_rebel_tier4_1_b:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_1.type, self.TIER4_QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_1_SIDE1.type, self.TIER4_QUEST_STRING_1_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_1_SIDE2.type, self.TIER4_QUEST_STRING_1_SIDE2.name, false)

	-- Mission 2
	assassinate_corellia_rebel_tier4_2:resetQuest(pPlayer)
	delivery_no_pickup_corellia_rebel_tier4_2_a:resetQuest(pPlayer)
	rescue_corellia_rebel_tier4_2_b:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_2.type, self.TIER4_QUEST_STRING_2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_2_SIDE1.type, self.TIER4_QUEST_STRING_2_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_2_SIDE2.type, self.TIER4_QUEST_STRING_2_SIDE2.name, false)

	-- Mission 3
	space_battle_corellia_rebel_tier4_3:resetQuest(pPlayer)
	space_battle_corellia_rebel_tier4_3_a:resetQuest(pPlayer)
	survival_corellia_rebel_tier4_3_b:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_3.type, self.TIER4_QUEST_STRING_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_3_SIDE1.type, self.TIER4_QUEST_STRING_3_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_3_SIDE2.type, self.TIER4_QUEST_STRING_3_SIDE2.name, false)

	-- Mission 4
	recovery_corellia_rebel_tier4_4:resetQuest(pPlayer)
	assassinate_corellia_rebel_tier4_4_a:resetQuest(pPlayer)
	rescue_corellia_rebel_tier4_4_b:resetQuest(pPlayer)
	space_battle_corellia_rebel_tier4_4_c:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_4.type, self.TIER4_QUEST_STRING_4.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_4_SIDE1.type, self.TIER4_QUEST_STRING_4_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_4_SIDE2.type, self.TIER4_QUEST_STRING_4_SIDE2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_4_SIDE3.type, self.TIER4_QUEST_STRING_4_SIDE3.name, false)

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
