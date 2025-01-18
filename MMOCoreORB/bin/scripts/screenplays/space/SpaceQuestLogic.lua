require("screenplays.screenplay")
local ObjectManager = require("managers.object.object_manager")

SpaceQuestLogic = ScreenPlay:new {
	className = "SpaceQuestLogic",

	questName = "",
	questType = "",

	questScreenplay = "",
	questZone = "",

	sideQuest = false,
	sideQuestType = "",
}
