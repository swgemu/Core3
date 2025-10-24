local Logger = require("utils.logger")

--[[

	Corsec Squadron Missions

]]

--[[
	Tier 1 -- Sgt Rhea Main Missions
]]

-- Mission 1

patrol_corellia_privateer_1 = SpacePatrolScreenplay:new {
	className = "patrol_corellia_privateer_1",

	questName = "corellia_privateer_1",
	questType = "patrol",

	questZone = "space_corellia",

	creditReward = 100,

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "corellia_privateer_1",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 2, -- Patrol Point Number
	sideQuestDelay = 20, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	patrolPoints = {
		{patrolPointName = "privateer_patrol_1", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
		{patrolPointName = "privateer_patrol_2", x = -4540, z = -6023, y = -6111, patrolNumber = 2, radius = 150},
		{patrolPointName = "privateer_patrol_3", x = -2907, z = -4914, y = -5085, patrolNumber = 3, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_privateer_1", true)

destroy_surpriseattack_corellia_privateer_1 = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_corellia_privateer_1",

	questName = "corellia_privateer_1",
	questType = "destroy_surpriseattack",

	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "patrol_corellia_privateer_1",
	parentQuestType = "patrol",
	parentQuestName = "corellia_privateer_1",

	-- Screenplay Specific Variables

	surpriseAttackShips = {
		zone = "space_corellia",
		spawns = {{count = 1, shipName = "blacksun_fighter_s02_tier1"}, {count = 3, shipName = "blacksun_fighter_s01_tier1"}},
	},
}

registerScreenPlay("destroy_surpriseattack_corellia_privateer_1", true)

-- Mission 2

destroy_corellia_privateer_2 = SpaceDestroyScreenplay:new {
	className = "destroy_corellia_privateer_2",

	questName = "corellia_privateer_2",
	questType = "destroy",

	questZone = "space_corellia",

	creditReward = 200,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	killsRequired = 4,

	shipLocations = {
		{patrolPointName = "black_sun_asteroid_1", x = 590, z = -3500, y = -6000},
		{patrolPointName = "blacksun_asteroid_three_spawner", x = -6420, z = 6215, y = 6292},
		{patrolPointName = "blacksun_asteroid_two_spawner", x = -5209, z = 6681, y = 6765},
		{patrolPointName = "blacksun_deep_one_spawner", x = -5175, z = 5404, y = 6138},
		{patrolPointName = "blacksun_fighter_five_spawner", x = -1894, z = 3873, y = 3360},
	},

	shipTypes = {
		"blacksun_ace_s04_tier1", "blacksun_ace_s04_tier2", "blacksun_aggressor_tier1", "blacksun_aggressor_tier2", "blacksun_bomber_ace_s04_tier1", "blacksun_bomber_ace_s04_tier2",
		"blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s02_tier1", "blacksun_bomber_s02_tier2", "blacksun_bomber_s03_tier1", "blacksun_bomber_s03_tier2",
		"blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s02_tier1", "blacksun_fighter_s02_tier2", "blacksun_fighter_s03_tier1", "blacksun_fighter_s03_tier2",
		"blacksun_gunship_tier1", "blacksun_gunship_tier2", "blacksun_marauder_tier1", "blacksun_marauder_tier2", "blacksun_vehement_tier1", "blacksun_vehement_tier2", "blacksun_yt1300_tier1",
		"blacksun_yt1300_tier2", "blacksun_bomber_ace_tier3_dantooine", "blacksun_bomber_s01_tier2_tatooine", "blacksun_bomber_s02_tier3_dantooine", "blacksun_fighter_s01_tier2_tatooine",
		"blacksun_fighter_s02_tier3_dantooine",
	},
}

registerScreenPlay("destroy_corellia_privateer_2", true)

-- Mission 3

patrol_corellia_privateer_3 = SpacePatrolScreenplay:new {
	className = "patrol_corellia_privateer_3",

	questName = "corellia_privateer_3",
	questType = "patrol",

	questZone = "space_corellia",

	creditReward = 500,
	itemReward = {
		{species = {SPECIES_ITHORIAN}, item = "object/tangible/wearables/bandolier/ith_mercenary_bandolier.iff"},
		{species = {-1}, item = "object/tangible/wearables/bandolier/mercenary_bandolier.iff"},
	},

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestName = "corellia_privateer_3",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 2,
	sideQuestDelay = 20, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	patrolPoints = {
		{patrolPointName = "privateer_security_patrol_1", x = 5549, z = -6501, y = -2720, patrolNumber = 1, radius = 150},
		{patrolPointName = "privateer_security_patrol_2", x = 1325, z = -6577, y = -3409, patrolNumber = 2, radius = 150},
		{patrolPointName = "privateer_security_patrol_3", x = -1514, z = -6488, y = -3864, patrolNumber = 3, radius = 150},
		{patrolPointName = "privateer_security_patrol_4", x = -5687, z = -6381, y = -4872, patrolNumber = 4, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_privateer_3", true)

escort_corellia_privateer_3 = SpaceEscortScreenplay:new {
	className = "escort_corellia_privateer_3",

	questName = "corellia_privateer_3",
	questType = "escort",

	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "patrol_corellia_privateer_3",
	parentQuestType = "patrol",
	parentQuestName = "corellia_privateer_3",

	-- Screenplay Specific Variables

	escortShips = {"freighterheavy_tier1"},

	escortPoints = {
		{patrolPointName = "privateer_security_escort_1", zoneName = "space_corellia", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{patrolPointName = "privateer_security_escort_2", zoneName = "space_corellia", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{patrolPointName = "privateer_security_escort_3", zoneName = "space_corellia", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{patrolPointName = "privateer_security_escort_4", zoneName = "space_corellia", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
	},

	attackDelay = 90, -- In Seconds

	attackShips = {
		{"blacksun_fighter_s02_tier1", "blacksun_fighter_s03_tier1", "blacksun_fighter_s02_tier1"},
	}
}

registerScreenPlay("escort_corellia_privateer_3", true)

-- Mission 4

assassinate_corellia_privateer_tier1_4a = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier1_4a",

	questType = "assassinate",
	questName = "corellia_privateer_tier1_4a",

	questZone = "space_corellia",

	creditReward = 1000,
	itemReward = {
		{species = {-1}, item = "object/tangible/ship/components/weapon/wpn_mission_reward_neutral_mandal_light_blaster.iff"},
	},

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	arrivalDelay = 6, -- Seconds
	failTimer = 20, -- Minutes

	assassinateSpawns = {
		target = "hidden_daggers_eliminator_tier2",
		escorts = {"hidden_daggers_enforcer_tier1", "hidden_daggers_enforcer_tier1", "hidden_daggers_enforcer_tier1"},
	},

	targetPatrols = {
		{patrolPointName = "assassinate_4", x = 2650, z = -1672, y = -105},
		{patrolPointName = "assassinate_5", x = 4431, z = -1858, y = 2196},
		{patrolPointName = "corellia_imperial_tier2_assassinate_1", x = -6932, z = -1364, y = -644},
		{patrolPointName = "corellia_imperial_tier2_assassinate_2", x = -5276, z = -1117, y = -6270},
	},
}

registerScreenPlay("assassinate_corellia_privateer_tier1_4a", true)

-- Sgt Rhea Duty Missions

destroy_duty_corellia_privateer_6 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_corellia_privateer_6",

	questName = "corellia_privateer_6",
	questType = "destroy_duty",

	questZone = "space_corellia",

	creditReward = 100,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	totalLevels = 2, -- Amount of levels a player has to complete to finish mission
	totalRounds = 2, -- Total Rounds for each of the levels
	totalWaves = 2, -- Total waves at each location that is not the boss ship

	minDistance = 12500, -- Minimum distance away for new location
	maxDistance = 17500, -- Maximum distance away for new location

	bossShip = "hidden_daggers_executioner_tier1",
	shipTypes = {
		{"hidden_daggers_eliminator_tier1", "hidden_daggers_enforcer_tier1"},
	},
}

registerScreenPlay("destroy_duty_corellia_privateer_6", true)

escort_duty_corellia_privateer_7 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_corellia_privateer_7",

	questName = "corellia_privateer_7",
	questType = "escort_duty",

	questZone = "space_corellia",

	creditReward = 1000,

	itemReward = {
		--{species = {}, item = ""},
	},

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	escortShips = {"freighterheavy_tier1", "freighterlight_tier1", "freightermedium_tier1"},

	escortPoints = {
		{patrolPointName = "privateer_security_escort_1", zoneName = "space_corellia", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{patrolPointName = "privateer_security_escort_2", zoneName = "space_corellia", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{patrolPointName = "privateer_security_escort_3", zoneName = "space_corellia", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{patrolPointName = "privateer_security_escort_4", zoneName = "space_corellia", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
	},

	attackDelay = 90, -- In Seconds

	attackShips = {
		{"blacksun_fighter_s01_tier1", "blacksun_fighter_s02_tier1"},
		{"blacklight_bomber_tier1", "blacksun_fighter_s03_tier1"},
	},

	creditKillBonus = 100,
}

registerScreenPlay("escort_duty_corellia_privateer_7", true)

--[[
	Tier 2 -- Cpt Rikkh Main Missions
]]

-- Mission 1

destroy_corellia_privateer_13a = SpaceDestroyScreenplay:new {
	className = "destroy_corellia_privateer_13a",

	questName = "corellia_privateer_13a",
	questType = "destroy",

	questZone = "space_lok",

	creditReward = 5000,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	killsRequired = 5,

	shipLocations = {},

	shipTypes = {
		"nym_blastboat_tier2", "nym_blastboat_tier3", "nym_blastboat_tier3", "nym_blastboat_tier4", "nym_blastboat_tier5",
		"nym_bomber_tier2", "nym_bomber_tier3", "nym_bomber_tier3", "nym_bomber_tier4", "nym_bomber_tier5", "nym_cannon_ship",
		"nym_cannon_ship_tier2", "nym_cannon_ship_tier4", "nym_enforcer_tier2", "nym_enforcer_tier3", "nym_enforcer_tier3",
		"nym_enforcer_tier4", "nym_enforcer_tier5", "nym_fighter_tier2", "nym_fighter_tier3", "nym_fighter_tier3", "nym_fighter_tier4",
		"nym_fighter_tier5", "nym_gunship_tier1", "nym_gunship_tier2", "nym_gunship_tier3", "nym_gunship_tier4", "nym_gunship_tier5",
		"nym_interceptor_tier4", "nym_lieutenant_tier4", "nym_patrol_craft_tier2", "nym_patrol_craft_tier3", "nym_patrol_craft_tier4",
		"nym_patrol_craft_tier5", "nym_patrol_craft_tier5", "nym_enforcer_captain_tier4", "nym_escort_fighter_tier4"
	},
}

registerScreenPlay("destroy_corellia_privateer_13a", true)

-- Mission 2

escort_corellia_privateer_14 = SpaceEscortScreenplay:new {
	className = "escort_corellia_privateer_14",

	questName = "corellia_privateer_14",
	questType = "escort",

	questZone = "space_yavin4",

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	escortShips = {"freighterheavy_tier3"},

	escortPoints = {
		{patrolPointName = "privateer_escort_1", zoneName = "space_yavin4", x = -2163, z = 956, y = 4991, escortNumber = 1, radius = 250},
		{patrolPointName = "privateer_escort_2", zoneName = "space_yavin4", x = -637, z = -295, y = 4770, escortNumber = 2, radius = 250},
		{patrolPointName = "privateer_escort_3", zoneName = "space_yavin4", x = 2043, z = -1230, y = 5414, escortNumber = 3, radius = 250},
		{patrolPointName = "privateer_escort_4", zoneName = "space_yavin4", x = -2064, z = -929, y = -3183, escortNumber = 4, radius = 250},
	},

	attackDelay = 180, -- In Seconds

	attackShips = {
		{"reb_xwing_tier2", "reb_xwing_tier2", "reb_ywing_tier3", "reb_xwing_tier3", "reb_z95_tier2", "reb_z95_tier2"},
	}
}

registerScreenPlay("escort_corellia_privateer_14", true)

-- Mission 3

inspect_corellia_privateer_15 = SpaceInspectScreenplay:new {
	className = "inspect_corellia_privateer_15",

	questName = "corellia_privateer_15",
	questType = "inspect",

	questZone = "space_lok",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	inspectTargets = {"nym_cannon_ship_tier2"},
	inspectCargo = "shipment_orders",

	targetLocation = {x = 3719, z = -2284, y = -1151},
}

registerScreenPlay("inspect_corellia_privateer_15", true)

-- Mission 4

assassinate_corellia_privateer_tier2_4a = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier2_4a",

	questType = "assassinate",
	questName = "corellia_privateer_tier2_4a",

	questZone = "space_dantooine",

	creditReward = 0,
	itemReward = {},

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	arrivalDelay = 7, -- Seconds
	failTimer = 20, -- Minutes

	assassinateSpawns = {
		target = "hutt_transport_tier3",
		escorts = {"hutt_fighter_s01_tier2", "hutt_fighter_s01_tier2", "hutt_bomber_s01_tier2", "hutt_bomber_s01_tier2", "hutt_fighter_s02_tier3"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_imperial_tier3_leg_4_assassinate_three_1", x = -137, z = -1281, y = 2629},
		{patrolPointName = "corellia_imperial_tier4_recovery1_2", x = 1014, z = -432, y = 1398},
		{patrolPointName = "corellia_privateer_tier4_rescue_duty_2", x = 2514, z = 4958, y = 2580},
	},
}

registerScreenPlay("assassinate_corellia_privateer_tier2_4a", true)

-- Cpt Rikkh Duty Missions

destroy_duty_corellia_privateer_9 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_corellia_privateer_9",

	questName = "corellia_privateer_9",
	questType = "destroy_duty",

	questZone = "space_corellia",

	creditReward = 200,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	totalLevels = 2, -- Amount of levels a player has to complete to finish mission
	totalRounds = 2, -- Total Rounds for each of the levels
	totalWaves = 2, -- Total waves at each location that is not the boss ship

	minDistance = 12500, -- Minimum distance away for new location
	maxDistance = 17500, -- Maximum distance away for new location

	bossShip = "imp_tie_advanced_tier3",
	shipTypes = {
		{"imp_tie_fighter_tier2", "imp_tie_fighter_tier2", "imp_tie_fighter_tier2"},
		{"imp_tie_bomber_tier2", "imp_tie_bomber_tier2"},
		{"imp_tie_interceptor_tier2", "imp_tie_interceptor_tier2"},
	},
}

registerScreenPlay("destroy_duty_corellia_privateer_9", true)

escort_duty_corellia_privateer_10 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_corellia_privateer_10",

	questName = "corellia_privateer_10",
	questType = "escort_duty",

	questZone = "space_lok",

	creditReward = 1000,

	itemReward = {
		--{species = {}, item = ""},
	},

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	escortShips = {"freighterheavy_tier1", "freighterlight_tier1", "freightermedium_tier1"},

	escortPoints = {
		{patrolPointName = "privateer_security_escort_1", zoneName = "space_lok", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{patrolPointName = "privateer_security_escort_2", zoneName = "space_lok", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{patrolPointName = "privateer_security_escort_3", zoneName = "space_lok", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{patrolPointName = "privateer_security_escort_4", zoneName = "space_lok", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
	},

	attackDelay = 90, -- In Seconds

	attackShips = {
		{"blacksun_fighter_s01_tier1", "blacksun_fighter_s02_tier1"},
		{"blacklight_bomber_tier1", "blacksun_fighter_s03_tier1"},
	},

	creditKillBonus = 100,
}

registerScreenPlay("escort_duty_corellia_privateer_10", true)

destroy_duty_corellia_privateer_11 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_corellia_privateer_11",

	questName = "corellia_privateer_11",
	questType = "destroy_duty",

	questZone = "space_corellia",

	creditReward = 200,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	totalLevels = 2, -- Amount of levels a player has to complete to finish mission
	totalRounds = 2, -- Total Rounds for each of the levels
	totalWaves = 2, -- Total waves at each location that is not the boss ship

	minDistance = 12500, -- Minimum distance away for new location
	maxDistance = 17500, -- Maximum distance away for new location

	bossShip = "hidden_daggers_enforcer_tier3",
	shipTypes = {
		{"hidden_daggers_slayer_tier2", "hidden_daggers_slayer_tier2", "hidden_daggers_slayer_tier2"},
		{"hidden_daggers_killer_tier2", "hidden_daggers_killer_tier2", "hidden_daggers_killer_tier2"},
		{"hidden_daggers_executioner_tier2", "hidden_daggers_executioner_tier2", "hidden_daggers_executioner_tier2"},
	}
}

registerScreenPlay("destroy_duty_corellia_privateer_11", true)

recovery_duty_corellia_privateer_12 = SpaceDutyDestroyScreenplay:new {
	className = "recovery_duty_corellia_privateer_12",

	questName = "corellia_privateer_12",
	questType = "recovery_duty",

	questZone = "space_corellia",

	creditReward = 100,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	totalLevels = 2, -- Amount of levels a player has to complete to finish mission
	totalRounds = 2, -- Total Rounds for each of the levels
	totalWaves = 2, -- Total waves at each location that is not the boss ship

	minDistance = 12500, -- Minimum distance away for new location
	maxDistance = 17500, -- Maximum distance away for new location

	bossShip = "hidden_daggers_executioner_tier1",
	shipTypes = {"hidden_daggers_enforcer_tier1", "hidden_daggers_eliminator_tier1"},
}

registerScreenPlay("recovery_duty_corellia_privateer_12", true)

--[[
	Tier 3 -- CDR Ramna Main Missions
]]

-- Mission 1

recovery_corellia_privateer_tier3_1 = SpaceRecoveryScreenplay:new {
	className = "recovery_corellia_privateer_tier3_1",

	questName = "corellia_privateer_tier3_1",
	questType = "recovery",

	questZone = "space_lok",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "patrol",
	sideQuestName = "corellia_privateer_tier3_1_a",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	-- Screenplay Specific Variables

	arrivalDelay = 13,
	recoveryDelay = 15,

	recoverShip = "nym_enforcer_tier3",
	recoveryConversationMobile = "object/mobile/shared_dressed_nym_guard_elite_nikto_m.iff",

	escortShips = {"nym_fighter_tier2", "nym_fighter_tier2"},

	preRecoveryPoints = {
		{patrolPointName = "corellia_privateer_tier3_recovery_point_1", zoneName = "space_lok", x = 4250, z = 1204, y = 3259, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_recovery_point_2", zoneName = "space_lok", x = 4318, z = 463, y = 3868, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_recovery_point_3", zoneName = "space_lok", x = 4379, z = -203, y = 4415, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_recovery_point_4", zoneName = "space_lok", x = 4441, z = -876, y = 4967, escortNumber = 4, radius = 250},
		{patrolPointName = "imperial_ss_interception_1", zoneName = "space_lok", x = 3230, z = -3912, y = -7336, escortNumber = 3, radius = 250},
		{patrolPointName = "rebel_tier3_2_a_delivery", zoneName = "space_lok", x = 1000, z = -2000, y = -3452, escortNumber = 4, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "corellia_privateer_tier3_recovery_point_5", zoneName = "space_lok", x = 4693, z = -604, y = 3823, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_recovery_point_6", zoneName = "space_lok", x = 5053, z = -1137, y = 3171, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_recovery_point_7", zoneName = "space_lok", x = 5133, z = -1919, y = 2854, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_recovery_point_8", zoneName = "space_lok", x = 5187, z = -2757, y = 2564, escortNumber = 4, radius = 250},
	},

	attackDelay = 110, -- In Seconds

	attackShips = {
		{"nym_bomber_tier3", "nym_bomber_tier3", "nym_fighter_tier3"},
	},
}

registerScreenPlay("recovery_corellia_privateer_tier3_1", true)

patrol_corellia_privateer_tier3_1_a = SpacePatrolScreenplay:new {
	className = "patrol_corellia_privateer_tier3_1_a",

	questName = "corellia_privateer_tier3_1_a",
	questType = "patrol",

	questZone = "space_endor",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestName = "corellia_privateer_tier3_1_b",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 3,
	sideQuestDelay = 4, -- Time in seconds to wait to trigger side quest

	parentQuest = "recovery_corellia_privateer_tier3_1",
	parentQuestType = "recovery",
	parentQuestName = "corellia_privateer_tier3_1",

	-- Screenplay Specific Variables

	patrolPoints = {
		{patrolPointName = "corellia_privateer_tier3_supply_patrol_1", x = 4335, z = -2305, y = -4373, patrolNumber = 1, radius = 150},
		{patrolPointName = "corellia_privateer_tier3_supply_patrol_2", x = 3891, z = -2322, y = -5265, patrolNumber = 2, radius = 150},
		{patrolPointName = "corellia_privateer_tier3_supply_patrol_3", x = 3676, z = -2888, y = -5498, patrolNumber = 3, radius = 150},
		{patrolPointName = "corellia_privateer_tier3_supply_patrol_4", x = 3502, z = -3126, y = -4475, patrolNumber = 4, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_privateer_tier3_1_a", true)

escort_corellia_privateer_tier3_1_b = SpaceEscortScreenplay:new {
	className = "escort_corellia_privateer_tier3_1_b",

	questName = "corellia_privateer_tier3_1_b",
	questType = "escort",

	questZone = "space_endor",

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "corellia_privateer_tier3_1_c",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 5, -- Time in seconds to wait to trigger side quest

	parentQuest = "patrol_corellia_privateer_tier3_1_a",
	parentQuestType = "patrol",
	parentQuestName = "corellia_privateer_tier3_1_a",

	-- Screenplay Specific Variables

	escortShips = {"freighterlight_tier3"},

	escortPoints = {
		{patrolPointName = "corellia_privateer_tier3_supply_escort_1", zoneName = "space_endor", x = 3799, z = -362, y = -3019, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_supply_escort_2", zoneName = "space_endor", x = 4281, z = 295, y = -2818, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_supply_escort_3", zoneName = "space_endor", x = 4775, z = 743, y = -1925, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_supply_escort_4", zoneName = "space_endor", x = 4895, z = 1220, y = -913, escortNumber = 4, radius = 250},
	},

	attackDelay = 110, -- In Seconds

	attackShips = {
		{"scavenger_hunter_tier3", "scavenger_hunter_tier3"},
		{"scavenger_fanatic_tier3", "scavenger_fanatic_tier3", "scavenger_missileboat_tier3"},
	}
}

registerScreenPlay("escort_corellia_privateer_tier3_1_b", true)

destroy_surpriseattack_corellia_privateer_tier3_1_c = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_corellia_privateer_tier3_1_c",

	questName = "corellia_privateer_tier3_1_c",
	questType = "destroy_surpriseattack",

	questZone = "space_endor",

	parentQuest = "escort_corellia_privateer_tier3_1_b",
	parentQuestType = "escort",
	parentQuestName = "corellia_privateer_tier3_1_b",

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	surpriseAttackShips = {
		zone = "space_endor",
		spawns = {{count = 4, shipName = "scavenger_hunter_tier3"}},
	},
}

registerScreenPlay("destroy_surpriseattack_corellia_privateer_tier3_1_c", true)

-- Mission 2

inspect_corellia_privateer_tier3_2 = SpaceInspectScreenplay:new {
	className = "inspect_corellia_privateer_tier3_2",

	questName = "corellia_privateer_tier3_2",
	questType = "inspect",

	questZone = "space_dathomir",

	creditReward = 0,

	parentQuest = "",
	parentQuestType = "",
	parentQuestName = "",

	sideQuest = true,
	sideQuestType = "survival",
	sideQuestName = "corellia_privateer_tier3_2_a",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	-- Screenplay Specific Variables

	inspectTargets = {"civshuttle_cor_tier3_pilot_capture"},
	inspectCargo = "cor_priv_tier3_capture_pilot",

	targetLocation = {x = -50, z = 1375, y = 1510},
}

registerScreenPlay("inspect_corellia_privateer_tier3_2", true)

survival_corellia_privateer_tier3_2_a = SpaceSurvivalScreenplay:new {
	className = "survival_corellia_privateer_tier3_2_a",

	questName = "corellia_privateer_tier3_2_a",
	questType = "survival",

	questZone = "space_endor",

	creditReward = 0,

	parentQuest = "inspect_corellia_privateer_tier3_2",
	parentQuestType = "inspect",
	parentQuestName = "corellia_privateer_tier3_2",

	sideQuest = true,
	sideQuestType = "delivery",
	sideQuestName = "corellia_privateer_tier3_2_b",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,
	sideQuestDelay = 4, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables
}

registerScreenPlay("survival_corellia_privateer_tier3_2_a", true)

delivery_corellia_privateer_tier3_2_b = SpaceDeliveryScreenplay:new {
	className = "delivery_corellia_privateer_tier3_2_b",

	questName = "corellia_privateer_tier3_2_b",
	questType = "delivery",

	questZone = "space_dathomir",

	parentQuest = "survival_corellia_privateer_tier3_2_a",
	parentQuestType = "survival",
	parentQuestName = "corellia_privateer_tier3_2_a",

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "corellia_privateer_tier3_2_c",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,
	sideQuestDelay = 5, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables
}

registerScreenPlay("delivery_corellia_privateer_tier3_2_b", true)

destroy_surpriseattack_corellia_privateer_tier3_2_c = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_corellia_privateer_tier3_2_c",

	questName = "corellia_privateer_tier3_2_c",
	questType = "destroy_surpriseattack",

	questZone = "space_dathomir",

	parentQuest = "delivery_corellia_privateer_tier3_2_b",
	parentQuestType = "delivery",
	parentQuestName = "corellia_privateer_tier3_2_b",

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	surpriseAttackShips = {
		zone = "space_dathomir",
		spawns = {{count = 5, shipName = "blacksun_aggressor_tier3"}},
	},
}

registerScreenPlay("destroy_surpriseattack_corellia_privateer_tier3_2_c", true)

-- Mission 3

delivery_corellia_privateer_tier3_3 = SpaceDeliveryScreenplay:new {
	className = "delivery_corellia_privateer_tier3_3",

	questName = "corellia_privateer_tier3_3",
	questType = "delivery",

	questZone = "space_dantooine",

	creditReward = 100,

	parentQuest = "",
	parentQuestType = "",
	parentQuestName = "",

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestName = "corellia_privateer_tier3_3_pre_a",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	-- Screenplay Specific Variables
}

registerScreenPlay("delivery_corellia_privateer_tier3_3", true)

escort_corellia_privateer_tier3_3_pre_a = SpaceEscortScreenplay:new {
	className = "escort_corellia_privateer_tier3_3_pre_a",

	questName = "corellia_privateer_tier3_3_pre_a",
	questType = "escort",

	questZone = "space_dantooine",

	parentQuest = "delivery_corellia_privateer_tier3_3",
	parentQuestType = "delivery",
	parentQuestName = "corellia_privateer_tier3_3",

	sideQuest = true,
	sideQuestType = "patrol",
	sideQuestName = "corellia_privateer_tier3_3_a",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,
	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	escortShips = {"corsec_spec_ops_transport_tier3"},

	escortPoints = {
		{patrolPointName = "corellia_privateer_tier3_delivery", zoneName = "space_dantooine", x = 1633, z = -2059, y = -1925, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_patrol_4", zoneName = "space_dantooine", x = -4468, z = -3583, y = 624, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_privateer_tier3_patrol_1", zoneName = "space_dantooine", x = -4204, z = -3241, y = 3652, escortNumber = 3, radius = 250},
	},

	attackDelay = 255, -- In Seconds

	attackShips = {
		{"scavenger_fanatic_tier3", "scavenger_fanatic_tier3"},
	}
}

registerScreenPlay("escort_corellia_privateer_tier3_3_pre_a", true)

patrol_corellia_privateer_tier3_3_a = SpacePatrolScreenplay:new {
	className = "patrol_corellia_privateer_tier3_3_a",

	questName = "corellia_privateer_tier3_3_a",
	questType = "patrol",

	questZone = "space_dantooine",

	creditReward = 0,

	parentQuest = "escort_corellia_privateer_tier3_3_pre_a",
	parentQuestType = "escort",
	parentQuestName = "corellia_privateer_tier3_3_pre_a",

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "corellia_privateer_tier3_3d",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,
	sideQuestDelay = 4, -- Time in seconds to wait to trigger side quest

	sideQuestPatrolStart = 3,

	-- Screenplay Specific Variables

	patrolPoints = {
		{patrolPointName = "corellia_privateer_tier3_patrol_1", zoneName = "space_dantooine", x = 1633, z = -2059, y = -1925, patrolNumber = 1, radius = 150},
		{patrolPointName = "corellia_privateer_tier3_patrol_2", zoneName = "space_dantooine", x = -4468, z = -3583, y = 624, patrolNumber = 2, radius = 150},
		{patrolPointName = "corellia_privateer_tier3_patrol_3", zoneName = "space_dantooine", x = -4204, z = -3241, y = 3652, patrolNumber = 3, radius = 150},
		{patrolPointName = "corellia_privateer_tier3_patrol_4", zoneName = "space_dantooine", x = -4204, z = -3241, y = 3652, patrolNumber = 4, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_privateer_tier3_3_a", true)

assassinate_corellia_privateer_tier3_3d = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier3_3d",

	questType = "assassinate",
	questName = "corellia_privateer_tier3_3d",

	questZone = "space_dantooine",

	creditReward = 0,
	itemReward = {},

	parentQuest = "patrol_corellia_privateer_tier3_3_a",
	parentQuestType = "patrol",
	parentQuestName = "corellia_privateer_tier3_3_a",

	sideQuest = false,
	sideQuestType = "space_battle",
	sideQuestName = "corellia_privateer_tier4_3c_win",
	sideFailQuestType = "space_battle",
	sideFailQuestName = "corellia_privateer_tier4_3c_lose",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.BIDIRECTIONAL,
	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	arrivalDelay = 7, -- Seconds
	failTimer = 20, -- Minutes

	assassinateSpawns = {
		target = "blacksun_gunship_tier2",
		escorts = {"blacksun_aggressor_tier3", "blacksun_aggressor_tier4", "blacksun_marauder_tier3", "blacksun_marauder_tier3"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_privateer_tier3_patrol_4", x = -4468, z = -3583, y = 624},
		{patrolPointName = "corellia_privateer_tier3_patrol_1", x = -4204, z = -3241, y = 3652},
		{patrolPointName = "corellia_privateer_tier3_patrol_2", x = -4773, z = -3338, y = 2891},
	},
}

registerScreenPlay("assassinate_corellia_privateer_tier3_3d", true)

-- Mission 4

assassinate_corellia_privateer_tier3_4 = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier3_4",

	questType = "assassinate",
	questName = "corellia_privateer_tier3_4",

	questZone = "space_endor",

	creditReward = 0,
	itemReward = {},

	sideQuest = true,
	sideQuestType = "survival",
	sideQuestName = "corellia_privateer_tier3_4_a",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	arrivalDelay = 12, -- Seconds
	failTimer = 20, -- Minutes

	assassinateSpawns = {
		target = "evil_raider_tyrant_tier3",
		escorts = {"evil_raider_cutthroat_tier3", "evil_raider_cutthroat_tier3", "evil_raider_fighter_tier3", "evil_raider_fighter_tier3", "evil_raider_fighter_tier3"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_privateer_tier3_assassin_1", x = 5978, z = 1103, y = -3021},
		{patrolPointName = "corellia_privateer_tier3_assassin_2", x = 1503, z = 857, y = -4461},
		{patrolPointName = "corellia_privateer_tier3_assassin_3", x = -1962, z = 658, y = -3496},
		{patrolPointName = "corellia_privateer_tier3_assassin_4", x = -5906, z = 487, y = -2508},
	},
}

registerScreenPlay("assassinate_corellia_privateer_tier3_4", true)

survival_corellia_privateer_tier3_4_a = SpaceSurvivalScreenplay:new {
	className = "survival_corellia_privateer_tier3_4_a",

	questType = "survival",
	questName = "corellia_privateer_tier3_4_a",

	questZone = "space_endor",

	creditReward = 0,
	itemReward = {},

	parentQuest = "assassinate_corellia_privateer_tier3_4",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_privateer_tier3_4",

	sideQuest = false,
	sideQuestType = "",
	sideQuestName = "",

	-- Screenplay Specific Variables
}

registerScreenPlay("survival_corellia_privateer_tier3_4_a", true)

--[[
	Tier 4 -- Adwan Turoldine Main Missions
]]

-- Mission 1

patrol_corellia_privateer_tier4_1a = SpacePatrolScreenplay:new {
	className = "patrol_corellia_privateer_tier4_1a",

	questName = "corellia_privateer_tier4_1a",
	questType = "patrol",

	questZone = "space_dantooine",

	creditReward = 0,

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "corellia_privateer_tier4_1b",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 4, -- Patrol Point Number
	sideQuestDelay = 11, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	patrolPoints = {
		{patrolPointName = "corellia_privateer_tier4_leg_1_patrol_one_1", x = -856, z = 950, y = -2616, patrolNumber = 1, radius = 150},
		{patrolPointName = "corellia_privateer_tier4_leg_1_patrol_one_2", x = -1482, z = 1725, y = -4173, patrolNumber = 2, radius = 150},
		{patrolPointName = "corellia_privateer_tier4_leg_1_patrol_one_3", x = -2220, z = 2638, y = -6006, patrolNumber = 3, radius = 150},
		{patrolPointName = "corellia_privateer_tier4_leg_1_patrol_one_4", x = 293, z = 4511, y = -4776, patrolNumber = 4, radius = 150},
		{patrolPointName = "corellia_privateer_tier4_leg_1_patrol_one_5", x = 3152, z = 7350, y = -3831, patrolNumber = 5, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_privateer_tier4_1a", true)

assassinate_corellia_privateer_tier4_1b = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier4_1b",

	questType = "assassinate",
	questName = "corellia_privateer_tier4_1b",

	questZone = "space_dantooine",

	creditReward = 0,
	itemReward = {
	},

	parentQuest = "patrol_corellia_privateer_tier4_1a",
	parentQuestType = "patrol",
	parentQuestName = "corellia_privateer_tier4_1a",

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "corellia_privateer_tier4_1c",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,

	-- Screenplay Specific Variables

	arrivalDelay = 3, -- Seconds
	failTimer = 20, -- Minutes

	assassinateSpawns = {
		target = "blacksun_yt1300_tier4",
		escorts = {"blacksun_vehement_tier4", "blacksun_vehement_tier4", "blacksun_vehement_tier4"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_privateer_assassinate_42a_1", x = -6621, z = -6310, y = -1147},
		{patrolPointName = "corellia_privateer_assassinate_42a_2", x = -4435, z = -2591, y = -2467},
		{patrolPointName = "corellia_privateer_assassinate_42a_3", x = -2107, z = -1811, y = -4301},
		{patrolPointName = "corellia_privateer_assassinate_42a_4", x = -337, z = -3780, y = -7480},
	},
}

registerScreenPlay("assassinate_corellia_privateer_tier4_1b", true)

destroy_surpriseattack_corellia_privateer_tier4_1c = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_corellia_privateer_tier4_1c",

	questName = "corellia_privateer_tier4_1c",
	questType = "destroy_surpriseattack",

	questZone = "space_dantooine",

	parentQuest = "assassinate_corellia_privateer_tier4_1b",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_privateer_tier4_1b",

	sideQuest = false,
	sideQuestType = "",
	sideQuestName = "",

	-- Screenplay Specific Variables

	surpriseAttackShips = {
		zone = "space_dantooine",
		spawns = {{count = 2, shipName = "blacksun_ace_s04_tier4"}, {count = 2, shipName = "blacksun_bomber_ace_s04_tier4"}},
	},
}

registerScreenPlay("destroy_surpriseattack_corellia_privateer_tier4_1c", true)

-- Mission 2

assassinate_corellia_privateer_tier4_2a = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier4_2a",

	questType = "assassinate",
	questName = "corellia_privateer_tier4_2a",

	questZone = "space_dathomir",

	creditReward = 0,
	itemReward = {},

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestName = "corellia_privateer_tier4_2b",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,
	sideQuestDelay = 2, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	arrivalDelay = 6, -- Seconds
	failTimer = 20, -- Minutes

	assassinateSpawns = {
		target = "hidden_daggers_executioner_tier5",
		escorts = {"hidden_daggers_eliminator_tier5", "hidden_daggers_eliminator_tier5", "hidden_daggers_eliminator_tier5", "hidden_daggers_eliminator_tier5"},
	},

	targetPatrols = {
		{patrolPointName = "bh_path_alpha_04", x = 520, z = 765, -5177},
		{patrolPointName = "corellia_imperial_tier3_leg_3_recovery_escort_3", x = -636, z = 3866, y = 330},
		{patrolPointName = "corellia_imperial_tier4_escort1_2", x = -7504, z = -314, y = -4018},
		{patrolPointName = "corellia_imperial_tier4_recovery2_7", x = 5904, z = -3381, y = -2643},
	},
}

registerScreenPlay("assassinate_corellia_privateer_tier4_2a", true)

escort_corellia_privateer_tier4_2b = SpaceEscortScreenplay:new {
	className = "escort_corellia_privateer_tier4_2b",

	questName = "corellia_privateer_tier4_2b",
	questType = "escort",

	questZone = "space_dathomir",

	parentQuest = "assassinate_corellia_privateer_tier4_2a",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_privateer_tier4_2a",

	sideQuest = false,
	sideQuestType = "",
	sideQuestName = "",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.NONE,
	sideQuestDelay = 5, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	escortShips = {"freighterlight_tier3"},

	escortPoints = {
		{patrolPointName = "corellia_privateer_tier4_leg_2_escort_1", zoneName = "space_dathomir", x = 2611, z = -387, y = 3617, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_leg_2_escort_2", zoneName = "space_dathomir", x = 683, z = 1485, y = 3209, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_leg_2_escort_3", zoneName = "space_dathomir", x = -1642, z = 3578, y = 2633, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_leg_2_escort_4", zoneName = "space_dathomir", x = -2146, z = 5611, y = 2738, escortNumber = 4, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_leg_2_escort_5", zoneName = "space_dathomir", x = -2682, z = 7408, y = 2855, escortNumber = 4, radius = 250},
	},

	attackDelay = 85, -- In Seconds

	attackShips = {
		{"hidden_daggers_slayer_tier4", "hidden_daggers_slayer_tier4"},
		{"hidden_daggers_killer_tier4", "hidden_daggers_killer_tier4", "hidden_daggers_killer_tier4"},
		{"hidden_daggers_nebula_stalker_tier4", "hidden_daggers_executioner_tier4", "hidden_daggers_executioner_tier4"},
	}
}

registerScreenPlay("escort_corellia_privateer_tier4_2b", true)

-- Mission 3

space_battle_corellia_privateer_tier4_3a = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_privateer_tier4_3a",

	questType = "space_battle",
	questName = "corellia_privateer_tier4_3a",

	questZone = "space_dantooine",

	creditReward = 0,
	itemReward = {},

	parentQuest = "",
	parentQuestType = "",
	parentQuestName = "",

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "corellia_privateer_tier4_3b",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,
	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	battleLocation = {patrolPointName = "corellia_privateer_tier4_leg_3_space_battle_one", x = 5063, y = -816, z = -3364},

	supportShipsDelay = 60,
	enemyShipsDelay = 90,

	supportShips = {"corsec_interdiction_craft_tier4", "corsec_interdiction_craft_tier4", "corsec_interceptor_tier4", "corsec_interceptor_tier4"},
	enemyShips = {"blacksun_aggressor_tier4", "blacksun_aggressor_tier4", "blacksun_bomber_s01_tier4", "blacksun_bomber_s01_tier4", "blacksun_fighter_s02_tier4", "blacksun_fighter_s02_tier4"},
}

registerScreenPlay("space_battle_corellia_privateer_tier4_3a", true)

assassinate_corellia_privateer_tier4_3b = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier4_3b",

	questType = "assassinate",
	questName = "corellia_privateer_tier4_3b",

	questZone = "space_dantooine",

	creditReward = 0,
	itemReward = {},

	parentQuest = "space_battle_corellia_privateer_tier4_3a",
	parentQuestType = "space_battle",
	parentQuestName = "corellia_privateer_tier4_3a",

	sideQuest = true,
	sideQuestType = "space_battle",
	sideQuestName = "corellia_privateer_tier4_3c_win",
	sideFailQuestType = "space_battle",
	sideFailQuestName = "corellia_privateer_tier4_3c_lose",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.BIDIRECTIONAL,
	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	arrivalDelay = 15, -- Seconds
	failTimer = 20, -- Minutes

	assassinateSpawns = {
		target = "blacksun_vehement_tier4",
		escorts = {"blacksun_aggressor_tier4", "blacksun_aggressor_tier4", "blacksun_aggressor_tier4", "blacksun_aggressor_tier4"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_privateer_tier4_leg_3_assassin_1", x = 4401, z = -3102, y = -743},
		{patrolPointName = "corellia_privateer_tier4_leg_3_assassin_2", x = 4003, z = -4997, y = 717},
		{patrolPointName = "corellia_privateer_tier4_leg_3_assassin_3", x = 3748, z = -6743, y = 1992},
		{patrolPointName = "corellia_privateer_tier4_leg_3_assassin_4", x = 3568, z = -7363, y = 2904},
	},
}

registerScreenPlay("assassinate_corellia_privateer_tier4_3b", true)

space_battle_corellia_privateer_tier4_3c_win = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_privateer_tier4_3c_win",

	questType = "space_battle",
	questName = "corellia_privateer_tier4_3c_win",

	questZone = "space_dantooine",

	creditReward = 0,
	itemReward = {},

	parentQuest = "assassinate_corellia_privateer_tier4_3b",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_privateer_tier4_3b",

	sideQuest = false,
	sideQuestType = "",
	sideQuestName = "",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.NONE,
	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	battleLocation = {patrolPointName = "corellia_privateer_tier4_leg_3_space_battle_two", x = 7512, z = -5651, y = 1803},

	supportShipsDelay = 30,
	enemyShipsDelay = 90,

	supportShips = {"corsec_gunship_tier4", "corsec_interdiction_craft_tier4", "corsec_lancer_tier4", "corsec_interceptor_tier4"},
	enemyShips = {"blacksun_aggressor_tier4", "blacksun_aggressor_tier4", "blacksun_gunship_tier4", "blacksun_marauder_tier4", "blacksun_marauder_tier4", "blacksun_vehement_tier4", "blacksun_gunship_tier4"},
}

registerScreenPlay("space_battle_corellia_privateer_tier4_3c_win", true)

space_battle_corellia_privateer_tier4_3c_lose = SpaceBattleScreenplay:new {
	className = "space_battle_corellia_privateer_tier4_3c_lose",

	questType = "space_battle",
	questName = "corellia_privateer_tier4_3c_lose",

	questZone = "space_dantooine",

	creditReward = 0,
	itemReward = {},

	parentQuest = "assassinate_corellia_privateer_tier4_3b",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_privateer_tier4_3b",

	sideQuest = false,
	sideQuestType = "",
	sideQuestName = "",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.NONE,
	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	battleLocation = {patrolPointName = "corellia_privateer_tier4_leg_3_space_battle_two", x = 7512, z = -5651, y = 1803},

	supportShipsDelay = 60,
	enemyShipsDelay = 90,

	supportShips = {"corsec_gunship_tier4", "corsec_interdiction_craft_tier4", "corsec_lancer_tier4", "corsec_fighter_tier4"},

	enemyShips = {"blacksun_aggressor_tier4", "blacksun_aggressor_tier4", "blacksun_aggressor_tier4", "blacksun_aggressor_tier4S", "blacksun_bomber_s02_tier4", "blacksun_bomber_s02_tier4", "blacksun_gunship_tier4", "blacksun_marauder_tier4",
		"blacksun_marauder_tier4", "blacksun_marauder_tier4", "blacksun_vehement_tier4", "blacksun_vehement_tier4", "blacksun_vehement_tier4"
	},
}

registerScreenPlay("space_battle_corellia_privateer_tier4_3c_lose", true)

-- Mission 4

assassinate_corellia_privateer_tier4_4a = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier4_4a",

	questType = "assassinate",
	questName = "corellia_privateer_tier4_4a",

	questZone = "space_dathomir",

	creditReward = 0,
	itemReward = {},

	parentQuest = "",
	parentQuestType = "",
	parentQuestName = "",

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "corellia_privateer_tier4_4b",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,
	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	arrivalDelay = 12, -- Seconds
	failTimer = 20, -- Minutes

	assassinateSpawns = {
		target = "hidden_daggers_nebula_stalker_tier5",
		escorts = {"hidden_daggers_enforcer_tier4", "hidden_daggers_enforcer_tier4"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_one_1", x = -2673, z = -2332, y = -502},
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_one_2", x = -4323, z = -3711, y = -844},
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_one_3", x = -5818, z = -4961, y = -1155},
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_one_4", x = -7473, z = -6718, y = -1559},
	},
}

registerScreenPlay("assassinate_corellia_privateer_tier4_4a", true)

assassinate_corellia_privateer_tier4_4b = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier4_4b",

	questType = "assassinate",
	questName = "corellia_privateer_tier4_4b",

	questZone = "space_dathomir",

	creditReward = 0,
	itemReward = {},

	parentQuest = "assassinate_corellia_privateer_tier4_4a",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_privateer_tier4_4a",

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "corellia_privateer_tier4_4c",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,
	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	arrivalDelay = 12, -- Seconds
	failTimer = 20, -- Minutes

	assassinateSpawns = {
		target = "hidden_daggers_nebula_stalker_tier5",
		escorts = {"hidden_daggers_enforcer_tier4", "hidden_daggers_enforcer_tier4"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_two_2", x = -6427, z = -5576, y = -4129},
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_two_1", x = -7303, z = -6224, y = -2668},
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_two_3", x = -5716, z = -4752, y = -5611},
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_two_4", x = -4808, z = -3578, y = -7512},
	},
}

registerScreenPlay("assassinate_corellia_privateer_tier4_4b", true)

destroy_surpriseattack_corellia_privateer_tier4_4c = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_corellia_privateer_tier4_4c",

	questName = "corellia_privateer_tier4_4c",
	questType = "destroy_surpriseattack",

	questZone = "space_dathomir",

	parentQuest = "assassinate_corellia_privateer_tier4_4b",
	parentQuestType = "assassinate",
	parentQuestName = "corellia_privateer_tier4_4b",

	sideQuest = true,
	sideQuestType = "assassinate",
	sideQuestName = "corellia_privateer_tier4_4d",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.COMPLETION,
	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	surpriseAttackShips = {
		zone = "space_dathomir",
		spawns = {
			{count = 3, shipName = "hidden_daggers_killer_tier4"}, {count = 2, shipName = "hidden_daggers_slayer_tier4"}
		},
	},
}

registerScreenPlay("destroy_surpriseattack_corellia_privateer_tier4_4c", true)

assassinate_corellia_privateer_tier4_4d = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier4_4d",

	questType = "assassinate",
	questName = "corellia_privateer_tier4_4d",

	questZone = "space_dathomir",

	creditReward = 0,
	itemReward = {},

	sideQuest = false,
	sideQuestType = "",
	sideQuestName = "",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.NONE,
	sideQuestDelay = 1, -- Time in seconds to wait to trigger side quest

	-- Screenplay Specific Variables

	arrivalDelay = 15, -- Seconds
	failTimer = 20, -- Minutes

	assassinateSpawns = {
		target = "hidden_daggers_eliminator_tier5",
		escorts = {"hidden_daggers_enforcer_tier4", "hidden_daggers_enforcer_tier4", "hidden_daggers_enforcer_tier4", "hidden_daggers_enforcer_tier4", "hidden_daggers_enforcer_tier4"},
	},

	targetPatrols = {
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_two_1", x = -7303, z = -6224, y = -2668},
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_two_2", x = -6427, z = -5576, y = -4129},
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_two_3", x = -5716, z = -4752, y = -5611},
		{patrolPointName = "corellia_privateer_tier4_leg_4_assassin_two_4", x = -4808, z = -3578, y = -7512},
	},
}

registerScreenPlay("assassinate_corellia_privateer_tier4_4d", true)

-- Turoldine Duty Missions

destroy_duty_corellia_privateer_tier4_1 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_corellia_privateer_tier4_1",

	questName = "corellia_privateer_tier4_1",
	questType = "destroy_duty",

	questZone = "space_dathomir",

	creditReward = 300,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	totalLevels = 2, -- Amount of levels a player has to complete to finish mission
	totalRounds = 4, -- Total Rounds for each of the levels
	totalWaves = 3, -- Total waves at each location that is not the boss ship

	minDistance = 12500, -- Minimum distance away for new location
	maxDistance = 17500, -- Maximum distance away for new location

	bossShip = "hidden_daggers_enforcer_tier4",
	shipTypes = {
		{"hidden_daggers_killer_tier4", "hidden_daggers_killer_tier4", "hidden_daggers_killer_tier4", "hidden_daggers_killer_tier4"},
		{"hidden_daggers_eliminator_tier4", "hidden_daggers_eliminator_tier4", "hidden_daggers_eliminator_tier4", "hidden_daggers_eliminator_tier4"},
		{"hidden_daggers_slayer_tier4", "hidden_daggers_slayer_tier4", "hidden_daggers_slayer_tier4", "hidden_daggers_slayer_tier4"},
		{"hidden_daggers_executioner_tier4", "hidden_daggers_executioner_tier4", "hidden_daggers_executioner_tier4", "hidden_daggers_executioner_tier4"},
	},
}

registerScreenPlay("destroy_duty_corellia_privateer_tier4_1", true)

rescue_duty_corellia_privateer_tier4_1 = SpaceDutyRescueScreenplay:new {
	className = "rescue_duty_corellia_privateer_tier4_1",

	questName = "corellia_privateer_tier4_1",
	questType = "rescue_duty",

	questZone = "space_lok",

	creditReward = 0,

	itemReward = {
		--{species = {}, item = ""},
	},

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

}

registerScreenPlay("rescue_duty_corellia_privateer_tier4_1", true)

recovery_duty_corellia_privateer_tier4_1 = SpaceDutyRecoveryScreenplay:new {
	className = "recovery_duty_corellia_privateer_tier4_1",

	questName = "corellia_privateer_tier4_1",
	questType = "recovery_duty",

	questZone = "space_dantooine",

	creditReward = 5000,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	arrivalDelay = 15,
	recoveryDelay = 24,

	recoverShip = "blacksun_transport_tier4",
	recoveryConversationMobile = "object/mobile/shared_dressed_nym_guard_elite_nikto_m.iff",

	escortShips = {"blacksun_aggressor_tier4", "blacksun_aggressor_tier4"},

	preRecoveryPoints = {
		{patrolPointName = "corellia_privateer_tier4_recovery_duty_escort_1", x = -397, z = 4235, y = 2013, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_recovery_duty_escort_2", x = -1096, z = 2908, y = -340, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_recovery_duty_escort_3", x = -1863, z = 2415, y = -2912, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_recovery_duty_escort_4", x = -3093, z = 1706, y = -6585, escortNumber = 4, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_leg_1_patrol_one_4", x = 293, z = 4511, y = -4776, escortNumber = 5, radius = 250},
	},

	recoveryPoints = {
		{patrolPointName = "corellia_privateer_tier4_recovery_duty_egress_1", x = -2157, z = -731, y = -5594, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_recovery_duty_egress_3", x = -491, z = -6021, y = -3466, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_recovery_duty_egress_4", x = 57, z = -7525, y = -2756, escortNumber = 3, radius = 250},
	},

	attackDelay = 90, -- In Seconds

	attackShips = {
		{"blacksun_bomber_s02_tier4", "blacksun_bomber_s02_tier4", "blacksun_fighter_s01_tier4", "blacksun_fighter_s01_tier4"},
		{"blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4", "blacksun_fighter_s03_tier4"},
		{"blacksun_aggressor_tier4", "blacksun_aggressor_tier4", "blacksun_aggressor_tier4", "blacksun_aggressor_tier4"},
	},

	killReward = 300,
}

registerScreenPlay("recovery_duty_corellia_privateer_tier4_1", true)

escort_duty_corellia_privateer_tier4_1 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_corellia_privateer_tier4_1",

	questName = "corellia_privateer_tier4_1",
	questType = "escort_duty",

	questZone = "space_dathomir",

	creditReward = 5000,

	itemReward = {
		--{species = {}, item = ""},
	},

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	escortShips = {"freighterheavy_tier4", "freighterlight_tier4"},

	escortPoints = {
		{patrolPointName = "corellia_privateer_tier4_escort_duty_1", zoneName = "space_dathomir", x = 3523, z = 400, y = -4024, escortNumber = 1, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_escort_duty_2", zoneName = "space_dathomir", x = 2089, z = 4103, y = -4060, escortNumber = 2, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_escort_duty_3", zoneName = "space_dathomir", x = 1396, z = 5751, y = -3946, escortNumber = 3, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_escort_duty_4", zoneName = "space_dathomir", x = 817, z = 7127, y = -3851, escortNumber = 4, radius = 250},
		{patrolPointName = "corellia_privateer_tier4_escort_duty_5", zoneName = "space_dathomir", x = 23729, z = 7391, y = -1995, escortNumber = 5, radius = 250},
	},

	attackDelay = 90, -- In Seconds

	attackShips = {
		{"dath_witchblood_clan_punisher_tier4", "dath_witchblood_clan_punisher_tier4", "dath_witchblood_clan_punisher_tier4", "dath_witchblood_clan_punisher_tier4"},
		{"dath_witchblood_clan_soldier_tier4", "dath_witchblood_clan_soldier_tier4", "dath_witchblood_clan_soldier_tier4", "dath_witchblood_clan_soldier_tier4"},
	},

	creditKillBonus = 300,
}

registerScreenPlay("escort_duty_corellia_privateer_tier4_1", true)

--[[

	CorsecSquadronScreenplay

]]

CorsecSquadronScreenplay = ScreenPlay:new {
	screenplayName = "CorsecSquadronScreenplay",

	DEBUG_CORSEC = false,

	-- Tier1
	QUEST_STRING_1 = {type = "patrol", name = "corellia_privateer_1"},
	QUEST_STRING_1_SIDE = {type = "destroy_surpriseattack", name = "corellia_privateer_1"},
	QUEST_STRING_2 = {type = "destroy", name = "corellia_privateer_2"},
	QUEST_STRING_3 = {type = "patrol", name = "corellia_privateer_3"},
	QUEST_STRING_3_SIDE = {type = "escort", name = "corellia_privateer_3"},
	QUEST_STRING_4 = {type = "assassinate", name = "corellia_privateer_tier1_4a"},
	QUEST_STRING_DUTY_4_1 = {type = "destroy_duty", name = "corellia_privateer_6"},
	QUEST_STRING_DUTY_4_2 = {type = "escort_duty", name = "corellia_privateer_7"},

	-- Tier2
	TIER2_QUEST_STRING_1 = {type = "destroy", name = "corellia_privateer_13a"},
	TIER2_QUEST_STRING_2 = {type = "escort", name = "corellia_privateer_14"},
	TIER2_QUEST_STRING_3 = {type = "inspect", name = "corellia_privateer_15"},
	TIER2_QUEST_STRING_4 = {type = "assassinate", name = "corellia_privateer_tier2_4a"},
	TIER2_QUEST_STRING_DUTY_1 = {type = "destroy_duty", name = "corellia_privateer_9"},
	TIER2_QUEST_STRING_DUTY_2 = {type = "escort_duty", name = "corellia_privateer_10"},
	TIER2_QUEST_STRING_DUTY_3 = {type = "destroy_duty", name = "corellia_privateer_11"},
	TIER2_QUEST_STRING_DUTY_4 = {type = "recovery_duty", name = "corellia_privateer_12"},

	-- Tier3
	TIER3_QUEST_STRING_1 = {type = "recovery", name = "corellia_privateer_tier3_1"},
	TIER3_QUEST_STRING_1_SIDE1 = {type = "patrol", name = "corellia_privateer_tier3_1_a"},
	TIER3_QUEST_STRING_1_SIDE2 = {type = "escort", name = "corellia_privateer_tier3_1_b"},
	TIER3_QUEST_STRING_1_SIDE3 = {type = "destroy_surpriseattack", name = "corellia_privateer_tier3_1_c"},
	TIER3_QUEST_STRING_2 = {type = "inspect", name = "corellia_privateer_tier3_2"},
	TIER3_QUEST_STRING_2_SIDE1 = {type = "survival", name = "corellia_privateer_tier3_2_a"},
	TIER3_QUEST_STRING_2_SIDE2 = {type = "delivery", name = "corellia_privateer_tier3_2_b"},
	TIER3_QUEST_STRING_2_SIDE3 = {type = "destroy_surpriseattack", name = "corellia_privateer_tier3_2_c"},
	TIER3_QUEST_STRING_3 = {type = "delivery", name = "corellia_privateer_tier3_3"},
	TIER3_QUEST_STRING_3_SIDE1 = {type = "escort", name = "corellia_privateer_tier3_3_pre_a"},
	TIER3_QUEST_STRING_3_SIDE2 = {type = "patrol", name = "corellia_privateer_tier3_3_a"},
	TIER3_QUEST_STRING_3_SIDE3 = {type = "assassinate", name = "corellia_privateer_tier3_3d"},
	TIER3_QUEST_STRING_4 = {type = "assassinate", name = "corellia_privateer_tier3_4"},
	TIER3_QUEST_STRING_4_SIDE1 = {type = "survival", name = "corellia_privateer_tier3_4_a"},

	-- Tier4
	TIER4_QUEST_STRING_1 = {type = "patrol", name = "corellia_privateer_tier4_1a"},
	TIER4_QUEST_STRING_1_SIDE1 = {type = "assassinate", name = "corellia_privateer_tier4_1b"},
	TIER4_QUEST_STRING_1_SIDE2 = {type = "destroy_surpriseattack", name = "corellia_privateer_tier4_1c"},
	TIER4_QUEST_STRING_2 = {type = "assassinate", name = "corellia_privateer_tier4_2a"},
	TIER4_QUEST_STRING_2_SIDE1 = {type = "escort", name = "corellia_privateer_tier4_2b"},
	TIER4_QUEST_STRING_3 = {type = "space_battle", name = "corellia_privateer_tier4_3a"},
	TIER4_QUEST_STRING_3_SIDE1 = {type = "assassinate", name = "corellia_privateer_tier4_3b"},
	TIER4_QUEST_STRING_3_SIDE2A = {type = "space_battle", name = "corellia_privateer_tier4_3c_win"},
	TIER4_QUEST_STRING_3_SIDE2B = {type = "space_battle", name = "corellia_privateer_tier4_3c_lose"},
	TIER4_QUEST_STRING_4 = {type = "assassinate", name = "corellia_privateer_tier4_4a"},
	TIER4_QUEST_STRING_4_SIDE1 = {type = "assassinate", name = "corellia_privateer_tier4_4b"},
	TIER4_QUEST_STRING_4_SIDE2 = {type = "destroy_surpriseattack", name = "corellia_privateer_tier4_4c"},
	TIER4_QUEST_STRING_4_SIDE3 = {type = "assassinate", name = "corellia_privateer_tier4_4d"},

	TIER4_QUEST_STRING_DUTY_1 = {type = "escort_duty", name = "corellia_privateer_tier4_1"},
	TIER4_QUEST_STRING_DUTY_2 = {type = "rescue_duty", name = "corellia_privateer_tier4_1"},
	TIER4_QUEST_STRING_DUTY_3 = {type = "recovery_duty", name = "corellia_privateer_tier4_1"},
	TIER4_QUEST_STRING_DUTY_4 = {type = "destroy_duty", name = "corellia_privateer_tier4_1"},
}

registerScreenPlay("CorsecSquadronScreenplay", false)

function CorsecSquadronScreenplay:start()
end

function CorsecSquadronScreenplay:resetRheaQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):setPilotTier(1)

	-- Mission 1
	patrol_corellia_privateer_1:resetQuest(pPlayer)
	destroy_surpriseattack_corellia_privateer_1:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, false)

	-- Mission 2
	destroy_corellia_privateer_2:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, false)

	-- Mission 3
	patrol_corellia_privateer_3:resetQuest(pPlayer)
	escort_corellia_privateer_3:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_3_SIDE.type, self.QUEST_STRING_3_SIDE.name, false)

	-- Mission 4
	assassinate_corellia_privateer_tier1_4a:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_4.type, self.QUEST_STRING_4.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_4.name .. ":reward")
end

function CorsecSquadronScreenplay:resetRikkhQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):setPilotTier(2)

	-- Mission 1
	destroy_corellia_privateer_13a:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_1.type, self.TIER2_QUEST_STRING_1.name, false)

	-- Mission 2
	escort_corellia_privateer_14:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_2.type, self.TIER2_QUEST_STRING_2.name, false)

	-- Mission 3
	inspect_corellia_privateer_15:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_3.type, self.TIER2_QUEST_STRING_3.name, false)

	-- Mission 4
	assassinate_corellia_privateer_tier2_4a:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_4.type, self.TIER2_QUEST_STRING_4.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward")
end

function CorsecSquadronScreenplay:resetRamnaQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):setPilotTier(3)

	-- Mission 1
	recovery_corellia_privateer_tier3_1:resetQuest(pPlayer)
	patrol_corellia_privateer_tier3_1_a:resetQuest(pPlayer)
	escort_corellia_privateer_tier3_1_b:resetQuest(pPlayer)
	destroy_surpriseattack_corellia_privateer_tier3_1_c:resetQuest(pPlayer)

	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1.type, self.TIER3_QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1_SIDE1.type, self.TIER3_QUEST_STRING_1_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1_SIDE2.type, self.TIER3_QUEST_STRING_1_SIDE2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1_SIDE3.type, self.TIER3_QUEST_STRING_1_SIDE3.name, false)

	-- Mission 2
	inspect_corellia_privateer_tier3_2:resetQuest(pPlayer)
	survival_corellia_privateer_tier3_2_a:resetQuest(pPlayer)
	delivery_corellia_privateer_tier3_2_b:resetQuest(pPlayer)
	destroy_surpriseattack_corellia_privateer_tier3_2_c:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2.type, self.TIER3_QUEST_STRING_2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2_SIDE1.type, self.TIER3_QUEST_STRING_2_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2_SIDE2.type, self.TIER3_QUEST_STRING_2_SIDE2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2_SIDE3.type, self.TIER3_QUEST_STRING_2_SIDE3.name, false)

	-- Mission 3
	delivery_corellia_privateer_tier3_3:resetQuest(pPlayer)
	escort_corellia_privateer_tier3_3_pre_a:resetQuest(pPlayer)
	patrol_corellia_privateer_tier3_3_a:resetQuest(pPlayer)
	assassinate_corellia_privateer_tier3_3d:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3.type, self.TIER3_QUEST_STRING_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3_SIDE1.type, self.TIER3_QUEST_STRING_3_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3_SIDE2.type, self.TIER3_QUEST_STRING_3_SIDE2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3_SIDE3.type, self.TIER3_QUEST_STRING_3_SIDE3.name, false)

	-- Mission 4
	assassinate_corellia_privateer_tier3_4:resetQuest(pPlayer)
	survival_corellia_privateer_tier3_4_a:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4.type, self.TIER3_QUEST_STRING_4.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4_SIDE1.type, self.TIER3_QUEST_STRING_4_SIDE1.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward")
end

function CorsecSquadronScreenplay:resetTuroldineQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):setPilotTier(4)

	-- Mission 1
	patrol_corellia_privateer_tier4_1a:resetQuest(pPlayer)
	assassinate_corellia_privateer_tier4_1b:resetQuest(pPlayer)
	destroy_surpriseattack_corellia_privateer_tier4_1c:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_1.type, self.TIER4_QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_1_SIDE1.type, self.TIER4_QUEST_STRING_1_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_1_SIDE2.type, self.TIER4_QUEST_STRING_1_SIDE2.name, false)

	-- Mission 2
	assassinate_corellia_privateer_tier4_2a:resetQuest(pPlayer)
	escort_corellia_privateer_tier4_2b:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_2.type, self.TIER4_QUEST_STRING_2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_2_SIDE1.type, self.TIER4_QUEST_STRING_2_SIDE1.name, false)

	-- Mission 3
	space_battle_corellia_privateer_tier4_3a:resetQuest(pPlayer)
	assassinate_corellia_privateer_tier4_3b:resetQuest(pPlayer)
	space_battle_corellia_privateer_tier4_3c_win:resetQuest(pPlayer)
	space_battle_corellia_privateer_tier4_3c_lose:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_3.type, self.TIER4_QUEST_STRING_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_3_SIDE1.type, self.TIER4_QUEST_STRING_3_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_3_SIDE2A.type, self.TIER4_QUEST_STRING_3_SIDE2A.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_3_SIDE2B.type, self.TIER4_QUEST_STRING_3_SIDE2B.name, false)

	-- Mission 4
	assassinate_corellia_privateer_tier4_4a:resetQuest(pPlayer)
	assassinate_corellia_privateer_tier4_4b:resetQuest(pPlayer)
	destroy_surpriseattack_corellia_privateer_tier4_4c:resetQuest(pPlayer)
	assassinate_corellia_privateer_tier4_4d:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_4.type, self.TIER4_QUEST_STRING_4.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_4_SIDE1.type, self.TIER4_QUEST_STRING_4_SIDE1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_4_SIDE2.type, self.TIER4_QUEST_STRING_4_SIDE2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER4_QUEST_STRING_4_SIDE3.type, self.TIER4_QUEST_STRING_4_SIDE3.name, false)

	local playerID = SceneObject(pPlayer):getObjectID()

	removeQuestStatus(playerID .. "CorsecSquadronScreenplay:StartedTuroldine")

	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":reward")
end
