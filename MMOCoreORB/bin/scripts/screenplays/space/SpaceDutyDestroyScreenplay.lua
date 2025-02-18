SpaceDutyDestroyScreenplay = SpaceQuestLogic:new {
	className = "SpaceDutyDestroyScreenplay",

	questName = "",
	questType = "",

	questZone = "",

	creditReward = 0,
	itemReward = {
		--{species = {}, item = ""},
	},

	DEBUG_SPACE_DUTY_DESTROY = false,

	dutyMission = false,

	sideQuest = false,
	sideQuestType = "",
	sideQuestStart = 0, -- Kill Number
	sideQuestDelay = 0, -- Time in seconds to wait to trigger side quest

	parentQuest = "",
	parentQuestType = "", -- Quest type of parent quest, used for completing tasks

	-- Screenplay Specific Variables
	killsRequired = 0,

	shipLocations = {},
	shipTypes = {},
}

registerScreenPlay("SpaceDutyDestroyScreenplay", false)

--[[

		Space Duty Destroy Quest Functions

--]]