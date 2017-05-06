local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

require("utils.helpers")

FsCrafting4Theater = GoToTheater:new {
	-- Task properties
	taskName = "FsCrafting4Theater",
	-- GoToTheater properties
	minimumDistance = 60,
	maximumDistance = 100,
	theater = {
		{ template = "object/tangible/item/quest/force_sensitive/fs_crafting4_downed_satellite.iff", xDiff = 0, zDiff = 1, yDiff = 0, heading = 0 },
	},
	waypointDescription = "Downed Satellite",
	mobileList = {},
	activeAreaRadius = 32
}

return FsCrafting4Theater
