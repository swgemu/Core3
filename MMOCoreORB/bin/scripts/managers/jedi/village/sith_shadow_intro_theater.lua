local GoToTheater = require("quest.tasks.go_to_theater")
local ObjectManager = require("managers.object.object_manager")
require("utils.helpers")

SithShadowIntroTheater = GoToTheater:new {
	-- Task properties
	taskName = "SithShadowIntroTheater",
	-- GoToTheater properties
	minimumDistance = 1024,
	maximumDistance = 1536,
	theater = "object/building/poi/anywhere_fs_intro_camp.iff",
	waypointDescription = "@quest/force_sensitive/intro:theater_sum",
	mobileList = {
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 }
	},
	despawnTime = 2 * 60* 60* 1000, -- 2 hours
	activeAreaRadius = 64,
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil
}

function SithShadowIntroTheater:onEnteredActiveArea(pCreatureObject, spawnedMobilesList)
	foreach(spawnedMobilesList, function(pMobile)
		ObjectManager.withCreatureAiAgent(pMobile, function(mobile)
			mobile:setFollowObject(pCreatureObject)
		end)
	end)
end

return SithShadowIntroTheater
