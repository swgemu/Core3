SpaceDutyPatrolScreenplay = SpacePatrolScreenplay:new {
	className = "SpaceDutyPatrolScreenplay",

	questName = "",
	questType = "",

	questZone = "",

	DEBUG_SPACE_PATROL = false,

	sideQuest = false,
	sideQuestType = "",
	sideQuestName = "",
	sideQuestSplitType = 0,

	sideQuestPatrolStart = 0, -- Patrol Point Number
	sideQuestDelay = 0, -- Time in seconds to wait to trigger side quest

	patrolPoints = {},
}

registerScreenPlay("SpaceDutyPatrolScreenplay", false)

--[[

		Space Duty Patrol Quest Functions

--]]