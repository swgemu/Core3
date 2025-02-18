local Logger = require("utils.logger")

--[[

	Corsec Squadron Quests

]]

-- Sgt Rhea Main Quests

patrol_corellia_privateer_1 = SpacePatrolScreenplay:new {
	className = "patrol_corellia_privateer_1",

	questName = "corellia_privateer_1",
	questType = "patrol",

	questZone = "space_corellia",

	creditReward = 100,

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestStart = 2, -- Patrol Point Number
	sideQuestDelay = 20, -- Time in seconds to wait to trigger side quest

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
	sideQuestStart = 2,
	sideQuestDelay = 20, -- Time in seconds to wait to trigger side quest

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

	escortShip = "freighterheavy_tier1",

	escortPoints = {
		{name = "privateer_security_escort_1", zoneName = "space_corellia", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{name = "privateer_security_escort_2", zoneName = "space_corellia", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{name = "privateer_security_escort_3", zoneName = "space_corellia", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{name = "privateer_security_escort_4", zoneName = "space_corellia", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
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

-- Sgt Rhea Duty Quests

destroy_duty_corellia_privateer_6 = SpaceDutyDestroyScreenplay:new {
	className = "destroy_duty_corellia_privateer_6",

	questName = "corellia_privateer_6",
	questType = "destroy_duty",

	questZone = "space_corellia",

	creditReward = 100,

	sideQuest = false,
	sideQuestType = "",

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

	escortShips = {"freighterheavy_tier1", "freighterlight_tier1", "freightermedium_tier1"},

	escortPoints = {
		{name = "privateer_security_escort_1", zoneName = "space_corellia", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 250},
		{name = "privateer_security_escort_2", zoneName = "space_corellia", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 250},
		{name = "privateer_security_escort_3", zoneName = "space_corellia", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 250},
		{name = "privateer_security_escort_4", zoneName = "space_corellia", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 250},
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

-- Captain Rikkh Main Quests


--[[

	CorsecSquadronScreenplay

]]

CorsecSquadronScreenplay = ScreenPlay:new {
	screenplayName = "CorsecSquadronScreenplay",

	DEBUG_CORSEC = false,

	QUEST_STRING_1 = {type = "patrol", name = "corellia_privateer_1"},
	QUEST_STRING_1_SIDE = {type = "destroy_surpriseattack", name = "corellia_privateer_1"},
	QUEST_STRING_2 = {type = "destroy", name = "corellia_privateer_2"},
	QUEST_STRING_3 = {type = "patrol", name = "corellia_privateer_3"},
	QUEST_STRING_3_SIDE = {type = "escort", name = "corellia_privateer_3"},
	QUEST_STRING_4 = {type = "assassinate", name = "corellia_privateer_tier1_4a"},
	QUEST_STRING_DUTY_5 = {type = "destroy_duty", name = "corellia_privateer_6"},
	QUEST_STRING_DUTY_6 = {type = "escort_duty", name = "corellia_privateer_7"},
}

registerScreenPlay("CorsecSquadronScreenplay", false)

function CorsecSquadronScreenplay:start()
end

function CorsecSquadronScreenplay:resetRheaQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

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
