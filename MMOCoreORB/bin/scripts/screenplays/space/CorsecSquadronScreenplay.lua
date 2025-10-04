local Logger = require("utils.logger")

--[[

	Corsec Squadron Missions

]]

-- Sgt Rhea Main Missions

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
		{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
		{zoneName = "space_corellia", x = -4540, z = -6023, y = -6111, patrolNumber = 2, radius = 150},
		{zoneName = "space_corellia", x = -2907, z = -4914, y = -5085, patrolNumber = 3, radius = 150},
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

	-- Screenplay Specific Variables

	parentQuest = "patrol_corellia_privateer_1",
	parentQuestType = "patrol",

	surpriseAttackShips = {
		zone = "space_corellia",
		spawns = {{count = 1, shipName = "blacksun_fighter_s02_tier1"}, {count = 3, shipName = "blacksun_fighter_s01_tier1"}},
		total = 4,
	},
}

registerScreenPlay("destroy_surpriseattack_corellia_privateer_1", true)

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
		{name = "black_sun_asteroid_1", x = 590, z = -3500, y = -6000},
		{name = "blacksun_asteroid_three_spawner", x = -6420, z = 6215, y = 6292},
		{name = "blacksun_asteroid_two_spawner", x = -5209, z = 6681, y = 6765},
		{name = "blacksun_deep_one_spawner", x = -5175, z = 5404, y = 6138},
		{name = "blacksun_fighter_five_spawner", x = -1894, z = 3873, y = 3360},
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
		{zoneName = "space_corellia", x = 5549, z = -6501, y = -2720, patrolNumber = 1, radius = 150},
		{zoneName = "space_corellia", x = 1325, z = -6577, y = -3409, patrolNumber = 2, radius = 150},
		{zoneName = "space_corellia", x = -1514, z = -6488, y = -3864, patrolNumber = 3, radius = 150},
		{zoneName = "space_corellia", x = -5687, z = -6381, y = -4872, patrolNumber = 4, radius = 150},
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

	parentQuest = "patrol_corellia_privateer_1",
	parentQuestType = "patrol",

	-- Screenplay Specific Variables

	escortShip = "freighterheavy_tier1",

	escortPoints = {
		{name = "corellia_privateer_security_escort_1", zoneName = "space_corellia", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{name = "corellia_privateer_security_escort_2", zoneName = "space_corellia", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{name = "corellia_privateer_security_escort_3", zoneName = "space_corellia", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{name = "corellia_privateer_security_escort_4", zoneName = "space_corellia", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
	},

	attackDelay = 90, -- In Seconds
	attackShips = {"blacksun_fighter_s02_tier1", "blacksun_fighter_s03_tier1", "blacksun_fighter_s02_tier1"},
}

registerScreenPlay("escort_corellia_privateer_3", true)

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
		{name = "assassinate_4", x = 2650, z = -1672, y = -105},
		{name = "assassinate_5", x = 4431, z = -1858, y = 2196},
		{name = "corellia_imperial_tier2_assassinate_1", x = -6932, z = -1364, y = -644},
		{name = "corellia_imperial_tier2_assassinate_2", x = -5276, z = -1117, y = -6270},
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
		{name = "corellia_privateer_security_escort_1", zoneName = "space_corellia", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{name = "corellia_privateer_security_escort_2", zoneName = "space_corellia", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{name = "corellia_privateer_security_escort_3", zoneName = "space_corellia", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{name = "corellia_privateer_security_escort_4", zoneName = "space_corellia", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
	},

	attackDelay = 90, -- In Seconds

	totalAttackGroups = 2,

	attackGroups = {
		{"blacksun_fighter_s01_tier1", "blacksun_fighter_s02_tier1"},
		{"blacklight_bomber_tier1", "blacksun_fighter_s03_tier1"},
	},

	creditKillBonus = 100,
}

registerScreenPlay("escort_duty_corellia_privateer_7", true)

-- Cpt Rikkh Main Missions

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

escort_corellia_privateer_14 = SpaceEscortScreenplay:new {
	className = "escort_corellia_privateer_14",

	questName = "corellia_privateer_14",
	questType = "escort",

	questZone = "space_yavin4",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "",
	parentQuestType = "",

	-- Screenplay Specific Variables

	escortShip = "freighterheavy_tier3",

	escortPoints = {
		{name = "privateer_escort_1", zoneName = "space_yavin4", x = -2163, z = 956, y = 4991, escortNumber = 1, radius = 250},
		{name = "privateer_escort_2", zoneName = "space_yavin4", x = -637, z = -295, y = 4770, escortNumber = 2, radius = 250},
		{name = "privateer_escort_3", zoneName = "space_yavin4", x = 2043, z = -1230, y = 5414, escortNumber = 3, radius = 250},
		{name = "privateer_escort_4", zoneName = "space_yavin4", x = -2064, z = -929, y = -3183, escortNumber = 4, radius = 250},
	},

	attackDelay = 180, -- In Seconds
	attackShips = {"reb_xwing_tier2", "reb_xwing_tier2", "reb_ywing_tier3", "reb_xwing_tier3", "reb_z95_tier2", "reb_z95_tier2"},
}

registerScreenPlay("escort_corellia_privateer_14", true)

inspect_corellia_privateer_15 = SpaceInspectScreenplay:new {
	className = "inspect_corellia_privateer_15",

	questName = "corellia_privateer_15",
	questType = "inspect",

	questZone = "space_lok",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "",
	parentQuestType = "",
}

registerScreenPlay("inspect_corellia_privateer_15", true)

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
		{name = "corellia_imperial_tier3_leg_4_assassinate_three_1", x = -137, z = -1281, y = 2629},
		{name = "corellia_imperial_tier4_recovery1_2", x = 1014, z = -432, y = 1398},
		{name = "corellia_privateer_tier4_rescue_duty_2", x = 2514, z = 4958, y = 2580},
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
		{name = "corellia_privateer_security_escort_1", zoneName = "space_lok", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{name = "corellia_privateer_security_escort_2", zoneName = "space_lok", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{name = "corellia_privateer_security_escort_3", zoneName = "space_lok", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{name = "corellia_privateer_security_escort_4", zoneName = "space_lok", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
	},

	attackDelay = 90, -- In Seconds

	totalAttackGroups = 2,

	attackGroups = {
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

-- CDR Ramna Main Missions

recovery_corellia_privateer_tier3_1 = SpaceRecoveryScreenplay:new {
	className = "recovery_corellia_privateer_tier3_1",

	questName = "corellia_privateer_tier3_1",
	questType = "recovery",

	questZone = "space_lok",

	creditReward = 100,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables

	arrivalDelay = 13,
	recoveryDelay = 15,

	recoverShip = "nym_enforcer_tier3",
	recoveryConversationMobile = "object/mobile/shared_dressed_nym_guard_elite_nikto_m.iff",

	escortShips = {"nym_fighter_tier2", "nym_fighter_tier2"},

	preRecoveryPoints = {
		{name = "corellia_privateer_tier3_recovery_point_1", zoneName = "space_lok", x = 4250, z = 1204, y = 3259, escortNumber = 1, radius = 250},
		{name = "corellia_privateer_tier3_recovery_point_2", zoneName = "space_lok", x = 4318, z = 463, y = 3868, escortNumber = 2, radius = 250},
		{name = "corellia_privateer_tier3_recovery_point_3", zoneName = "space_lok", x = 4379, z = -203, y = 4415, escortNumber = 3, radius = 250},
		{name = "corellia_privateer_tier3_recovery_point_4", zoneName = "space_lok", x = 4441, z = -876, y = 4967, escortNumber = 4, radius = 250},
		{name = "imperial_ss_interception_1", zoneName = "space_lok", x = 3230, z = -3912, y = -7336, escortNumber = 3, radius = 250},
		{name = "rebel_tier3_2_a_delivery", zoneName = "space_lok", x = 1000, z = -2000, y = -3452, escortNumber = 4, radius = 250},
	},

	recoveryPoints = {
		{name = "corellia_privateer_tier3_recovery_point_5", zoneName = "space_lok", x = 4693, z = -604, y = 3823, escortNumber = 1, radius = 250},
		{name = "corellia_privateer_tier3_recovery_point_6", zoneName = "space_lok", x = 5053, z = -1137, y = 3171, escortNumber = 2, radius = 250},
		{name = "corellia_privateer_tier3_recovery_point_7", zoneName = "space_lok", x = 5133, z = -1919, y = 2854, escortNumber = 3, radius = 250},
		{name = "corellia_privateer_tier3_recovery_point_8", zoneName = "space_lok", x = 5187, z = -2757, y = 2564, escortNumber = 4, radius = 250},
	},

	attackDelay = 110, -- In Seconds

	attackShips = {
		{"nym_bomber_tier3", "nym_bomber_tier3", "nym_fighter_tier3"},
	},
}

registerScreenPlay("recovery_corellia_privateer_tier3_1", true)

inspect_corellia_privateer_tier3_2 = SpaceInspectScreenplay:new {
	className = "inspect_corellia_privateer_tier3_2",

	questName = "corellia_privateer_tier3_2",
	questType = "inspect",

	questZone = "space_corellia",

	creditReward = 100,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
}

registerScreenPlay("inspect_corellia_privateer_tier3_2", true)

delivery_corellia_privateer_tier3_3 = SpaceDeliveryScreenplay:new {
	className = "delivery_corellia_privateer_tier3_3",

	questName = "corellia_privateer_tier3_3",
	questType = "delivery",

	questZone = "space_corellia",

	creditReward = 100,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
}

registerScreenPlay("delivery_corellia_privateer_tier3_3", true)

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
		{name = "privateer_tier3_assassin_1", x = 5978, z = 1103, y = -3021},
		{name = "privateer_tier3_assassin_2", x = 1503, z = 857, y = -4461},
		{name = "privateer_tier3_assassin_3", x = -1962, z = 658, y = -3496},
		{name = "privateer_tier3_assassin_4", x = -5906, z = 487, y = -2508},
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

	sideQuest = false,
	sideQuestType = "",
	sideQuestName = "",

	parentQuest = "assassinate_corellia_privateer_tier3_4",
	parentQuestType = "assassinate",

	-- Screenplay Specific Variables
}

registerScreenPlay("assassinate_corellia_privateer_tier3_4", true)

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
	TIER3_QUEST_STRING_2 = {type = "inspect", name = "corellia_privateer_tier3_2"},
	TIER3_QUEST_STRING_3 = {type = "delivery", name = "corellia_privateer_tier3_3"},
	TIER3_QUEST_STRING_4 = {type = "assassinate", name = "corellia_privateer_tier3_4"},
	TIER3_QUEST_STRING_4_SIDE = {type = "survival", name = "corellia_privateer_tier3_4_a"},

	-- Tier4
	TIER4_QUEST_STRING_1 = {type = "patrol", name = "corellia_privateer_tier4_1a"},
	TIER4_QUEST_STRING_2 = {type = "assassinate", name = "corellia_privateer_tier4_2a"},
	TIER4_QUEST_STRING_3 = {type = "space_battle", name = "corellia_privateer_tier4_3a"},
	TIER4_QUEST_STRING_4 = {type = "assassinate", name = "corellia_privateer_tier4_4a"},
	TIER4_QUEST_STRING_DUTY_1 = {type = "escort_duty", name = "corellia_privateer_tier4_1"},
	TIER4_QUEST_STRING_DUTY_2 = {type = "rescue_duty", name = "corellia_privateer_tier4_1"},
	TIER4_QUEST_STRING_DUTY_3 = {type = "recovery_duty", name = "corelliacorellia_privateer_tier4_1_privateer_11"},
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

	patrol_corellia_privateer_1:failQuest(pPlayer, "false")
	destroy_surpriseattack_corellia_privateer_1:failQuest(pPlayer, "false")
	destroy_corellia_privateer_2:failQuest(pPlayer, "false")
	patrol_corellia_privateer_3:failQuest(pPlayer, "false")
	escort_corellia_privateer_3:failQuest(pPlayer, "false")
	assassinate_corellia_privateer_tier1_4a:failQuest(pPlayer, "false")

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_3_SIDE.type, self.QUEST_STRING_3_SIDE.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_3_SIDE.type, self.QUEST_STRING_3_SIDE.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_4.type, self.QUEST_STRING_4.name, false)
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

	destroy_corellia_privateer_13a:failQuest(pPlayer, "false")
	escort_corellia_privateer_14:failQuest(pPlayer, "false")
	inspect_corellia_privateer_15:failQuest(pPlayer, "false")
	assassinate_corellia_privateer_tier2_4a:failQuest(pPlayer, "false")

	destroy_duty_corellia_privateer_9:failQuest(pPlayer, "false")
	escort_duty_corellia_privateer_10:failQuest(pPlayer, "false")
	destroy_duty_corellia_privateer_11:failQuest(pPlayer, "false")
	recovery_duty_corellia_privateer_12:failQuest(pPlayer, "false")

	SpaceHelpers:failSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_1.type, self.TIER2_QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_1.type, self.TIER2_QUEST_STRING_1.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_2.type, self.TIER2_QUEST_STRING_2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_2.type, self.TIER2_QUEST_STRING_2.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_3.type, self.TIER2_QUEST_STRING_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_3.type, self.TIER2_QUEST_STRING_3.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_4.type, self.TIER2_QUEST_STRING_4.name, false)
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

	recovery_corellia_privateer_tier3_1:failQuest(pPlayer, "false")
	inspect_corellia_privateer_tier3_2:failQuest(pPlayer, "false")
	delivery_corellia_privateer_tier3_3:failQuest(pPlayer, "false")
	assassinate_corellia_privateer_tier3_4:failQuest(pPlayer, "false")
	survival_corellia_privateer_tier3_4_a:failQuest(pPlayer, "false")

	SpaceHelpers:failSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1.type, self.TIER3_QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_1.type, self.TIER3_QUEST_STRING_1.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2.type, self.TIER3_QUEST_STRING_2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_2.type, self.TIER3_QUEST_STRING_2.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3.type, self.TIER3_QUEST_STRING_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_3.type, self.TIER3_QUEST_STRING_3.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4.type, self.TIER3_QUEST_STRING_4.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4.type, self.TIER3_QUEST_STRING_4.name, false)

	SpaceHelpers:failSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4_SIDE.type, self.TIER3_QUEST_STRING_4_SIDE.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER3_QUEST_STRING_4_SIDE.type, self.TIER3_QUEST_STRING_4_SIDE.name, false)

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


end