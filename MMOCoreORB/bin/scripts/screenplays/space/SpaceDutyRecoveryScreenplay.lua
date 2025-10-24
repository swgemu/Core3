SpaceDutyRecoveryScreenplay = SpaceRecoveryScreenplay:new {
	className = "SpaceDutyRecoveryScreenplay",

	-- Screenplay Specific Variables

	DEBUG_SPACE_DUTY_RECOVERY = false,

	arrivalDelay = 5, -- In Seconds

	recoverShip = "",
	recoveryConversationMobile = "",

	preRecoveryPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	recoveryPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	escortSpeed = 20,
	testEscortSpeed = 40,

	attackDelay = 30, -- In Seconds

	attackShips = {
		{},
	},

	recoveryDelay = 5,

	tauntData = {
		panicCount = 5,
		thanksCount = 5,
	},
}

registerScreenPlay("SpaceDutyRecoveryScreenplay", false)

--[[

		Space Duty Recovery Quest Functions

--]]
