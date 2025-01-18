require("screenplays.screenplay")
local ObjectManager = require("managers.object.object_manager")

SpaceQuestLogic = ScreenPlay:new {
	className = "SpaceQuestLogic",

	questName = "",
	questType = "",

	questZone = "",

	sideQuest = false,
	sideQuestType = "",
	sideQuestStart = 0, -- Patrol Point Number
	sideQuestDelay = 0, -- Time in seconds to wait to trigger side quest

	parentQuest = "",
	parentQuestType = "", -- Quest type of parent quest, used for completing tasks
	completeParentTask = false,
	parentTaskToComplete = -1,
}

registerScreenPlay("SpaceQuestLogic", false)

function SpaceQuestLogic:start()
end