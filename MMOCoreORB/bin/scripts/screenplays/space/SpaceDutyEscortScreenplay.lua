SpaceDutyEscortScreenplay = SpaceEscortScreenplay:new {
	className = "SpaceDutyEscortScreenplay",

	questName = "",
	questType = "",

	questZone = "",

	creditReward = 0,

	itemReward = {
		--{species = {}, item = ""},
	},

	sideQuest = false,
	sideQuestType = "",

	DEBUG_SPACE_ESCORT_DUTY = false,

	dutyMission = true,

	escortRange = 1000,
	escortShip = "",

	escortPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	spawnAttackWaves = true,
	checkPlayerDistance = true,

	attackDelay = 90, -- In Seconds

	totalAttackGroups = 2,

	attackGroups = {
		{},
		{},
	},

	creditKillBonus = 100,
}

registerScreenPlay("SpaceDutyEscortScreenplay", false)

--[[

		Space Escort Duty Quest Functions

--]]
