local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

require("utils.helpers")

FsSad2Theater7 = GoToTheater:new {
	-- Task properties
	taskName = "FsSad2Theater7",
	-- GoToTheater properties
	minimumDistance = 800,
	maximumDistance = 2000,
	theater = {
		{ template = "object/static/structure/corellia/corl_tent_small.iff", xDiff = 1.438, zDiff = 0.392, yDiff = 1.875, heading = 0 },
		{ template = "object/static/structure/general/all_banner_generic_s01.iff", xDiff = -2.134, zDiff = -1.061, yDiff = -1.731, heading = 0 },
		{ template = "object/static/structure/general/atst_debris_01.iff", xDiff = -2.842, zDiff = 0.147, yDiff = 1.744, heading = 0 },
		{ template = "object/static/structure/general/camp_stool_tall_s01.iff", xDiff = 1.984, zDiff = 0.273, yDiff = 0.146, heading = 0 },
		{ template = "object/static/structure/general/camp_stool_tall_s01.iff", xDiff = 0.811, zDiff = 0.287, yDiff = 1.061, heading = 0 },
		{ template = "object/static/structure/general/camp_campfire_logs_smoldering_s01.iff", xDiff = 0.743, zDiff = -0.038, yDiff = -3.091, heading = 0 },
	},
	mobileList = {
		{ template = "sith_shadow_outlaw", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_outlaw", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_outlaw", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_pirate", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_taskmaster", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
	},
	waypointDescription = "@quest/quest_journal/fs_quests_sad2:task7",
	createWaypoint = true,
	activeAreaRadius = 16,
	flattenLayer = true
}

function FsSad2Theater7:onObjectsSpawned(pPlayer, spawnedMobileList)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	writeData(playerID .. self.taskName .. ":killableCount", #spawnedMobileList)

	for i = 1, #spawnedMobileList, 1 do
		if (SpawnMobiles.isValidMobile(spawnedMobileList[i])) then
			writeData(SceneObject(spawnedMobileList[i]):getObjectID() .. self.taskName .. "ownerID", playerID)
			createObserver(OBJECTDESTRUCTION, self.taskName, "notifyKilledMobile", spawnedMobileList[i])
		end
	end
end

function FsSad2Theater7:onTheaterCreated(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pTheater = self:getTheaterObject(pPlayer)

	if (pTheater ~= nil) then
		SuiRadiationSensor:setLocation(pPlayer, SceneObject(pTheater):getWorldPositionX(), SceneObject(pTheater):getWorldPositionY(), SceneObject(pTheater):getZoneName())
	end
end

function FsSad2Theater7:notifyKilledMobile(pVictim, pAttacker)
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
		QuestManager.completeQuest(pOwner, QuestManager.quests.FS_QUESTS_SAD2_TASK7)
		QuestManager.activateQuest(pOwner, QuestManager.quests.FS_QUESTS_SAD2_RETURN7)
		deleteData(ownerID .. self.taskName .. ":killableCount", numEnemies)

		local pGhost = CreatureObject(pOwner):getPlayerObject()

		if (pGhost ~= nil) then
			PlayerObject(pGhost):addWaypoint("dathomir", "@quest/quest_journal/fs_quests_sad2:return7", "", 5238, -4189, WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)
		end
	end

	deleteData(mobileID .. self.taskName .. "ownerID")
	return 1
end

return FsSad2Theater7
