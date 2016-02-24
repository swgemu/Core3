local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

require("utils.helpers")

FsSad1Theater8 = GoToTheater:new {
	-- Task properties
	taskName = "FsSad1Theater8",
	-- GoToTheater properties
	minimumDistance = 800,
	maximumDistance = 1200,
	theater = {
		{ template = "object/static/structure/general/trash_pile_s01.iff", xDiff = -0.90, zDiff = -0.10, yDiff = 0.959, heading = 0	},
		{ template = "object/static/structure/corellia/corl_tent_hut_s01.iff", xDiff = -1.39, zDiff = 0.01, yDiff = 2.875, heading = 0 },
		{ template = "object/static/structure/general/camp_lawn_chair_s01.iff", xDiff = -0.20, zDiff = -0.145, yDiff = -1.389, heading = -145.14 },
		{ template = "object/static/structure/general/campfire_smoldering.iff", xDiff = 2.03, zDiff = 0.303, yDiff = -3.361, heading = 0 },
		{ template = "object/static/structure/general/camp_cot_s01.iff", xDiff = 0.47, zDiff = -0.066, yDiff = 0.915, heading = 123.76 },
	},
	mobileList = {
		{ template = "sith_shadow_pirate", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_pirate", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_taskmaster", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_taskmaster", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
	},
	createWaypoint = false,
	despawnTime = 20 * 60 * 1000, -- 20 minutes
	activeAreaRadius = 16,
}

function FsSad1Theater8:onSuccessfulSpawn(pCreatureObject, spawnedMobileList)
	if (pCreatureObject == nil) then
		return
	end

	local playerID = SceneObject(pCreatureObject):getObjectID()
	writeData(playerID .. self.taskName .. ":killableCount", #spawnedMobileList)

	for i = 1, #spawnedMobileList, 1 do
		if (spawnedMobileList[i] ~= nil) then
			writeData(SceneObject(spawnedMobileList[i]):getObjectID() .. self.taskName .. "ownerID", playerID)
			createObserver(OBJECTDESTRUCTION, self.taskName, "notifyKilledMobile", spawnedMobileList[i])
		end
	end

	local theaterId = readData(playerID .. self.taskName .. "theaterId")
	local pTheater = getSceneObject(theaterId)

	if (pTheater ~= nil) then
		SuiRadiationSensor:setLocation(pCreatureObject, SceneObject(pTheater):getWorldPositionX(), SceneObject(pTheater):getWorldPositionY(), SceneObject(pTheater):getZoneName())
	end
end

function FsSad1Theater8:notifyKilledMobile(pVictim, pAttacker)
	local mobileID = SceneObject(pVictim):getObjectID()
	local ownerID = readData(mobileID .. self.taskName .. "ownerID")
	local numEnemies = readData(ownerID .. self.taskName .. ":killableCount")

	numEnemies = numEnemies - 1
	writeData(ownerID .. self.taskName .. ":killableCount", numEnemies)

	local pOwner = getSceneObject(ownerID)

	if (pOwner == nil) then
		self:finish()
	end

	if (numEnemies <= 0) then
		QuestManager.completeQuest(pOwner, QuestManager.quests.FS_QUESTS_SAD_TASK8)
		QuestManager.activateQuest(pOwner, QuestManager.quests.FS_QUESTS_SAD_RETURN8)
		deleteData(ownerID .. self.taskName .. ":killableCount", numEnemies)
	end

	deleteData(mobileID .. self.taskName .. "ownerID")
	return 1
end

return FsSad1Theater8
