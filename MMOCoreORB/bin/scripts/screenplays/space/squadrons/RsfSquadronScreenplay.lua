local Logger = require("utils.logger")

--[[

	RSF Squadron Missions

]]

--[[
	Tier 1 -- RSF Trainer Main Missions
]]

-- Quest String Constants
RsfSquadronScreenplay = {
	-- Tier 1 Quest Strings
	QUEST_STRING_1 = {type = "patrol", name = "naboo_privateer_1"},
	QUEST_STRING_1_SIDE = {type = "destroy_surpriseattack", name = "naboo_privateer_1"},
	QUEST_STRING_2 = {type = "destroy", name = "naboo_privateer_2"},
	QUEST_STRING_3 = {type = "patrol", name = "naboo_privateer_3"},
	QUEST_STRING_3_SIDE = {type = "escort", name = "naboo_privateer_3"},
	QUEST_STRING_4 = {type = "assassinate", name = "naboo_privateer_tier1_4a"},

	-- Tier 1 Duty Quest Strings
	QUEST_STRING_DUTY_4_1 = {type = "destroy_duty", name = "naboo_privateer_6"},
	QUEST_STRING_DUTY_4_2 = {type = "escort_duty", name = "naboo_privateer_7"},
}

registerScreenPlay("RsfSquadronScreenplay", false)

function RsfSquadronScreenplay:start()
end

-- Mission 1: Patrol

patrol_naboo_privateer_1 = SpacePatrolScreenplay:new {
	className = "patrol_naboo_privateer_1",

	questName = "naboo_privateer_1",
	questType = "patrol",

	questZone = "space_naboo",

	creditReward = 100,

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestName = "naboo_privateer_1",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 2,
	sideQuestDelay = 20,

	-- Screenplay Specific Variables
	patrolPoints = {
		{patrolPointName = "privateer_patrol_1", x = 752, z = 659, y = -2444, patrolNumber = 1, radius = 150},
		{patrolPointName = "privateer_patrol_2", x = 2031, z = 887, y = -1759, patrolNumber = 2, radius = 150},
		{patrolPointName = "privateer_patrol_3", x = 2466, z = 854, y = -505, patrolNumber = 3, radius = 150},
	},
}

registerScreenPlay("patrol_naboo_privateer_1", true)

destroy_surpriseattack_naboo_privateer_1 = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_naboo_privateer_1",

	questName = "naboo_privateer_1",
	questType = "destroy_surpriseattack",

	questZone = "space_naboo",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "patrol_naboo_privateer_1",
	parentQuestType = "patrol",
	parentQuestName = "naboo_privateer_1",

	-- Screenplay Specific Variables
	surpriseAttackShips = {
		zone = "space_naboo",
		spawns = {{count = 1, shipName = "blacksun_fighter_s02_tier1"}, {count = 3, shipName = "blacksun_fighter_s01_tier1"}},
	},
}

registerScreenPlay("destroy_surpriseattack_naboo_privateer_1", true)

-- Mission 2: Destroy

destroy_naboo_privateer_2 = SpaceDestroyScreenplay:new {
	className = "destroy_naboo_privateer_2",

	questName = "naboo_privateer_2",
	questType = "destroy",

	questZone = "space_naboo",

	creditReward = 200,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	killsRequired = 4,

	shipLocations = {
		{patrolPointName = "privateer_patrol_1", x = 752, z = 659, y = -2444},
		{patrolPointName = "privateer_patrol_2", x = 2031, z = 887, y = -1759},
		{patrolPointName = "privateer_patrol_3", x = 2466, z = 854, y = -505},
	},

	shipTypes = {
		"blacksun_ace_s04_tier1", "blacksun_ace_s04_tier2", "blacksun_aggressor_tier1", "blacksun_aggressor_tier2",
		"blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s02_tier1", "blacksun_bomber_s02_tier2",
		"blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s02_tier1", "blacksun_fighter_s02_tier2",
		"blacksun_fighter_s03_tier1", "blacksun_fighter_s03_tier2", "blacksun_gunship_tier1", "blacksun_gunship_tier2",
	},
}

registerScreenPlay("destroy_naboo_privateer_2", true)

-- Mission 3: Patrol with Escort side quest

patrol_naboo_privateer_3 = SpacePatrolScreenplay:new {
	className = "patrol_naboo_privateer_3",

	questName = "naboo_privateer_3",
	questType = "patrol",

	questZone = "space_naboo",

	creditReward = 500,
	itemReward = {
		{species = {SPECIES_ITHORIAN}, item = "object/tangible/wearables/bandolier/ith_mercenary_bandolier.iff"},
		{species = {-1}, item = "object/tangible/wearables/bandolier/mercenary_bandolier.iff"},
	},

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestName = "naboo_privateer_3",
	sideQuestSplitType = SpaceQuestLogic.SIDE_QUEST_SPLIT_TYPES.PATROL_POINT,

	sideQuestPatrolStart = 2,
	sideQuestDelay = 20,

	-- Screenplay Specific Variables
	patrolPoints = {
		{patrolPointName = "privateer_security_patrol_1", x = 2479, z = -500, y = 1187, patrolNumber = 1, radius = 150},
		{patrolPointName = "privateer_security_patrol_2", x = 3251, z = -414, y = 2349, patrolNumber = 2, radius = 150},
		{patrolPointName = "privateer_security_patrol_3", x = 3039, z = -499, y = 3761, patrolNumber = 3, radius = 150},
		{patrolPointName = "privateer_security_patrol_4", x = 2500, z = -400, y = 4500, patrolNumber = 4, radius = 150},
	},
}

registerScreenPlay("patrol_naboo_privateer_3", true)

escort_naboo_privateer_3 = SpaceEscortScreenplay:new {
	className = "escort_naboo_privateer_3",

	questName = "naboo_privateer_3",
	questType = "escort",

	questZone = "space_naboo",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "patrol_naboo_privateer_3",
	parentQuestType = "patrol",
	parentQuestName = "naboo_privateer_3",

	-- Screenplay Specific Variables
	escortShips = {"freighterheavy_tier1"},

	escortPoints = {
		{patrolPointName = "privateer_escort_1", zoneName = "space_naboo", x = 3200, z = -400, y = 2600, escortNumber = 1, radius = 250},
		{patrolPointName = "privateer_escort_2", zoneName = "space_naboo", x = 2800, z = -450, y = 3200, escortNumber = 2, radius = 250},
		{patrolPointName = "privateer_escort_3", zoneName = "space_naboo", x = 2400, z = -400, y = 4000, escortNumber = 3, radius = 250},
		{patrolPointName = "privateer_escort_4", zoneName = "space_naboo", x = 2000, z = -350, y = 4800, escortNumber = 4, radius = 250},
	},

	attackDelay = 90,

	attackShips = {
		{"blacksun_fighter_s02_tier1", "blacksun_fighter_s03_tier1", "blacksun_fighter_s02_tier1"},
	}
}

registerScreenPlay("escort_naboo_privateer_3", true)

-- Mission 4: Assassinate

assassinate_naboo_privateer_tier1_4a = SpaceAssassinateScreenplay:new {
	className = "assassinate_naboo_privateer_tier1_4a",

	questType = "assassinate",
	questName = "naboo_privateer_tier1_4a",

	questZone = "space_naboo",

	creditReward = 1000,
	itemReward = {
		{species = {-1}, item = "object/tangible/ship/components/weapon/wpn_mission_reward_neutral_mandal_light_blaster.iff"},
	},

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	arrivalDelay = 6,
	failTimer = 20,

	assassinateTarget = {
		zone = "space_naboo",
		ship = "blacksun_ace_s04_tier1",
		x = 1500, z = 500, y = -1000,
	},

	assassinateWingmen = {
		zone = "space_naboo",
		spawns = {{count = 2, shipName = "blacksun_fighter_s02_tier1"}},
	},
}

registerScreenPlay("assassinate_naboo_privateer_tier1_4a", true)

-- Tier 1 Duty Missions

destroy_duty_naboo_privateer_6 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_naboo_privateer_6",

	questName = "naboo_privateer_6",
	questType = "destroy_duty",

	questZone = "space_naboo",

	creditReward = 50,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	dutyMissionLevel = 1,

	shipLocations = {
		{patrolPointName = "privateer_patrol_1", x = 752, z = 659, y = -2444},
		{patrolPointName = "privateer_patrol_2", x = 2031, z = 887, y = -1759},
		{patrolPointName = "privateer_patrol_3", x = 2466, z = 854, y = -505},
	},

	shipTypes = {
		"blacksun_fighter_s01_tier1", "blacksun_fighter_s02_tier1", "blacksun_fighter_s03_tier1",
		"blacksun_bomber_s01_tier1", "blacksun_bomber_s02_tier1",
	},
}

registerScreenPlay("destroy_duty_naboo_privateer_6", true)

escort_duty_naboo_privateer_7 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_naboo_privateer_7",

	questName = "naboo_privateer_7",
	questType = "escort_duty",

	questZone = "space_naboo",

	creditReward = 75,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	dutyMissionLevel = 1,

	escortShips = {"freighterheavy_tier1", "freighterlight_tier1"},

	escortPoints = {
		{patrolPointName = "stn_rori_rsf_escort_duty_1", zoneName = "space_naboo", x = 832, z = 2355, y = -6460, escortNumber = 1, radius = 250},
		{patrolPointName = "stn_rori_rsf_escort_duty_2", zoneName = "space_naboo", x = 5504, z = 1267, y = -4332, escortNumber = 2, radius = 250},
		{patrolPointName = "stn_rori_rsf_escort_duty_3", zoneName = "space_naboo", x = 6352, z = -220, y = 1363, escortNumber = 3, radius = 250},
	},

	attackShips = {
		{"blacksun_fighter_s01_tier1", "blacksun_fighter_s02_tier1"},
		{"blacksun_fighter_s01_tier1", "blacksun_fighter_s02_tier1", "blacksun_fighter_s03_tier1"},
	}
}

registerScreenPlay("escort_duty_naboo_privateer_7", true)
