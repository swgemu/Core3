local Logger = require("utils.logger")

--[[

	RSF Squadron Missions

]]

--[[
	Tier 1 -- Dinge Main Missions
]]

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

--[[
	Tier 2 -- Captain Kaydine Main Missions
]]

-- Mission 1: Destroy (5 kills)

destroy_naboo_privateer_13a = SpaceDestroyScreenplay:new {
	className = "destroy_naboo_privateer_13a",

	questName = "naboo_privateer_13a",
	questType = "destroy",

	questZone = "space_naboo",

	creditReward = 5000,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	killsRequired = 5,

	shipLocations = {},

	shipTypes = {
		"blacksun_ace_s04_tier2", "blacksun_ace_s04_tier3", "blacksun_aggressor_tier2", "blacksun_aggressor_tier3",
		"blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier3", "blacksun_bomber_s02_tier2", "blacksun_bomber_s02_tier3",
		"blacksun_fighter_s01_tier2", "blacksun_fighter_s01_tier3", "blacksun_fighter_s02_tier2", "blacksun_fighter_s02_tier3",
		"blacksun_fighter_s03_tier2", "blacksun_fighter_s03_tier3", "blacksun_gunship_tier2", "blacksun_gunship_tier3",
	},
}

registerScreenPlay("destroy_naboo_privateer_13a", true)

-- Mission 2: Escort

escort_naboo_privateer_14 = SpaceEscortScreenplay:new {
	className = "escort_naboo_privateer_14",

	questName = "naboo_privateer_14",
	questType = "escort",

	questZone = "space_naboo",

	creditReward = 6000,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	escortShips = {"freighterheavy_tier3"},

	escortPoints = {
		{patrolPointName = "rsf_tier2_escort_1", zoneName = "space_naboo", x = 3500, z = 500, y = -2000, escortNumber = 1, radius = 250},
		{patrolPointName = "rsf_tier2_escort_2", zoneName = "space_naboo", x = 4200, z = 300, y = -500, escortNumber = 2, radius = 250},
		{patrolPointName = "rsf_tier2_escort_3", zoneName = "space_naboo", x = 5000, z = 100, y = 1000, escortNumber = 3, radius = 250},
		{patrolPointName = "rsf_tier2_escort_4", zoneName = "space_naboo", x = 5500, z = -200, y = 2500, escortNumber = 4, radius = 250},
	},

	attackDelay = 180,

	attackShips = {
		{"blacksun_fighter_s02_tier2", "blacksun_fighter_s02_tier2", "blacksun_fighter_s03_tier2", "blacksun_bomber_s01_tier2"},
	}
}

registerScreenPlay("escort_naboo_privateer_14", true)

-- Mission 3: Inspect

inspect_naboo_privateer_15 = SpaceInspectScreenplay:new {
	className = "inspect_naboo_privateer_15",

	questName = "naboo_privateer_15",
	questType = "inspect",

	questZone = "space_naboo",

	creditReward = 7000,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	inspectTargets = {"blacksun_gunship_tier2"},
	inspectCargo = "shipment_orders",

	targetLocation = {x = 2500, z = 400, y = -3000},
}

registerScreenPlay("inspect_naboo_privateer_15", true)

-- Mission 4: Assassinate

assassinate_naboo_privateer_tier2_4a = SpaceAssassinateScreenplay:new {
	className = "assassinate_naboo_privateer_tier2_4a",

	questType = "assassinate",
	questName = "naboo_privateer_tier2_4a",

	questZone = "space_naboo",

	creditReward = 10000,
	itemReward = {
		{species = {-1}, item = "object/tangible/ship/components/weapon/wpn_mission_reward_neutral_mandal_light_blaster.iff"},
	},

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	arrivalDelay = 7,
	failTimer = 20,

	assassinateSpawns = {
		target = "blacksun_ace_s04_tier3",
		escorts = {"blacksun_fighter_s02_tier2", "blacksun_fighter_s02_tier2", "blacksun_bomber_s01_tier2", "blacksun_bomber_s01_tier2", "blacksun_fighter_s03_tier3"},
	},

	targetPatrols = {
		{patrolPointName = "rsf_tier2_assassinate_1", x = 1500, z = 600, y = -1500},
		{patrolPointName = "rsf_tier2_assassinate_2", x = 2000, z = 400, y = -2000},
	},
}

registerScreenPlay("assassinate_naboo_privateer_tier2_4a", true)

-- Tier 2 Duty Missions

destroy_duty_naboo_privateer_9 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_naboo_privateer_9",

	questName = "naboo_privateer_9",
	questType = "destroy_duty",

	questZone = "space_naboo",

	creditReward = 100,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	dutyMissionLevel = 2,

	shipLocations = {
		{patrolPointName = "rsf_duty_patrol_1", x = 752, z = 659, y = -2444},
		{patrolPointName = "rsf_duty_patrol_2", x = 2031, z = 887, y = -1759},
		{patrolPointName = "rsf_duty_patrol_3", x = 2466, z = 854, y = -505},
	},

	shipTypes = {
		"blacksun_fighter_s01_tier2", "blacksun_fighter_s02_tier2", "blacksun_fighter_s03_tier2",
		"blacksun_bomber_s01_tier2", "blacksun_bomber_s02_tier2",
	},
}

registerScreenPlay("destroy_duty_naboo_privateer_9", true)

escort_duty_naboo_privateer_10 = SpaceDutyEscortScreenplay:new {
	className = "escort_duty_naboo_privateer_10",

	questName = "naboo_privateer_10",
	questType = "escort_duty",

	questZone = "space_naboo",

	creditReward = 150,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	dutyMissionLevel = 2,

	escortShips = {"freighterheavy_tier2", "freighterlight_tier2"},

	escortPoints = {
		{patrolPointName = "rsf_tier2_duty_escort_1", zoneName = "space_naboo", x = 1000, z = 500, y = -3000, escortNumber = 1, radius = 250},
		{patrolPointName = "rsf_tier2_duty_escort_2", zoneName = "space_naboo", x = 2500, z = 300, y = -1500, escortNumber = 2, radius = 250},
		{patrolPointName = "rsf_tier2_duty_escort_3", zoneName = "space_naboo", x = 4000, z = 100, y = 500, escortNumber = 3, radius = 250},
	},

	attackShips = {
		{"blacksun_fighter_s01_tier2", "blacksun_fighter_s02_tier2"},
		{"blacksun_fighter_s01_tier2", "blacksun_fighter_s02_tier2", "blacksun_fighter_s03_tier2"},
	}
}

registerScreenPlay("escort_duty_naboo_privateer_10", true)

destroy_duty_naboo_privateer_11 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_naboo_privateer_11",

	questName = "naboo_privateer_11",
	questType = "destroy_duty",

	questZone = "space_naboo",

	creditReward = 125,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	dutyMissionLevel = 2,

	shipLocations = {
		{patrolPointName = "rsf_duty_patrol_4", x = 3500, z = 400, y = -1000},
		{patrolPointName = "rsf_duty_patrol_5", x = 4000, z = 200, y = 500},
		{patrolPointName = "rsf_duty_patrol_6", x = 4500, z = -100, y = 2000},
	},

	shipTypes = {
		"blacksun_fighter_s02_tier2", "blacksun_fighter_s03_tier2",
		"blacksun_bomber_s01_tier2", "blacksun_aggressor_tier2",
	},
}

registerScreenPlay("destroy_duty_naboo_privateer_11", true)

-- Note: Recovery duty not fully implemented in base code
recovery_duty_naboo_privateer_12 = SpaceDutyDestroyScreenplay:new {
	className = "recovery_duty_naboo_privateer_12",

	questName = "naboo_privateer_12",
	questType = "recovery_duty",

	questZone = "space_naboo",

	creditReward = 175,

	sideQuest = false,
	sideQuestType = "",

	-- Screenplay Specific Variables
	dutyMissionLevel = 2,

	shipLocations = {
		{patrolPointName = "rsf_recovery_1", x = 2000, z = 300, y = -2500},
		{patrolPointName = "rsf_recovery_2", x = 3000, z = 500, y = -1500},
	},

	shipTypes = {
		"blacksun_fighter_s01_tier2", "blacksun_fighter_s02_tier2",
	},
}

registerScreenPlay("recovery_duty_naboo_privateer_12", true)

--[[
	RSF Squadron Screenplay
]]

RsfSquadronScreenplay = ScreenPlay:new {
	screenplayName = "RsfSquadronScreenplay",

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

	-- Tier 2 Quest Strings
	TIER2_QUEST_STRING_1 = {type = "destroy", name = "naboo_privateer_13a"},
	TIER2_QUEST_STRING_2 = {type = "escort", name = "naboo_privateer_14"},
	TIER2_QUEST_STRING_3 = {type = "inspect", name = "naboo_privateer_15"},
	TIER2_QUEST_STRING_4 = {type = "assassinate", name = "naboo_privateer_tier2_4a"},

	-- Tier 2 Duty Quest Strings
	TIER2_QUEST_STRING_DUTY_1 = {type = "destroy_duty", name = "naboo_privateer_9"},
	TIER2_QUEST_STRING_DUTY_2 = {type = "escort_duty", name = "naboo_privateer_10"},
	TIER2_QUEST_STRING_DUTY_3 = {type = "destroy_duty", name = "naboo_privateer_11"},
	TIER2_QUEST_STRING_DUTY_4 = {type = "recovery_duty", name = "naboo_privateer_12"},
}

registerScreenPlay("RsfSquadronScreenplay", false)

function RsfSquadronScreenplay:start()
end

function RsfSquadronScreenplay:resetDingeQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):setPilotTier(1)

	-- Mission 1
	patrol_naboo_privateer_1:resetQuest(pPlayer)
	destroy_surpriseattack_naboo_privateer_1:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, false)

	-- Mission 2
	destroy_naboo_privateer_2:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, false)

	-- Mission 3
	patrol_naboo_privateer_3:resetQuest(pPlayer)
	escort_naboo_privateer_3:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_3_SIDE.type, self.QUEST_STRING_3_SIDE.name, false)

	-- Mission 4
	assassinate_naboo_privateer_tier1_4a:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_4.type, self.QUEST_STRING_4.name, false)

	-- Duty Missions
	destroy_duty_naboo_privateer_6:resetQuest(pPlayer)
	escort_duty_naboo_privateer_7:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_DUTY_4_1.type, self.QUEST_STRING_DUTY_4_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_DUTY_4_2.type, self.QUEST_STRING_DUTY_4_2.name, false)
end

function RsfSquadronScreenplay:resetKaydineQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	PlayerObject(pGhost):setPilotTier(2)

	-- Mission 1
	destroy_naboo_privateer_13a:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_1.type, self.TIER2_QUEST_STRING_1.name, false)

	-- Mission 2
	escort_naboo_privateer_14:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_2.type, self.TIER2_QUEST_STRING_2.name, false)

	-- Mission 3
	inspect_naboo_privateer_15:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_3.type, self.TIER2_QUEST_STRING_3.name, false)

	-- Mission 4
	assassinate_naboo_privateer_tier2_4a:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_4.type, self.TIER2_QUEST_STRING_4.name, false)

	-- Duty Missions
	destroy_duty_naboo_privateer_9:resetQuest(pPlayer)
	escort_duty_naboo_privateer_10:resetQuest(pPlayer)
	destroy_duty_naboo_privateer_11:resetQuest(pPlayer)
	recovery_duty_naboo_privateer_12:resetQuest(pPlayer)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_DUTY_1.type, self.TIER2_QUEST_STRING_DUTY_1.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_DUTY_2.type, self.TIER2_QUEST_STRING_DUTY_2.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_DUTY_3.type, self.TIER2_QUEST_STRING_DUTY_3.name, false)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.TIER2_QUEST_STRING_DUTY_4.type, self.TIER2_QUEST_STRING_DUTY_4.name, false)

	-- Clear quest status tracking
	removeQuestStatus(playerID .. self.TIER2_QUEST_STRING_1.name .. ":attempted")
	removeQuestStatus(playerID .. self.TIER2_QUEST_STRING_2.name .. ":attempted")
	removeQuestStatus(playerID .. self.TIER2_QUEST_STRING_3.name .. ":attempted")
	removeQuestStatus(playerID .. self.TIER2_QUEST_STRING_4.name .. ":attempted")
	removeQuestStatus(playerID .. self.TIER2_QUEST_STRING_1.name .. ":reward")
	removeQuestStatus(playerID .. self.TIER2_QUEST_STRING_2.name .. ":reward")
	removeQuestStatus(playerID .. self.TIER2_QUEST_STRING_3.name .. ":reward")
	removeQuestStatus(playerID .. self.TIER2_QUEST_STRING_4.name .. ":reward")
end
