local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

require("utils.helpers")

FsSad1Theater5 = GoToTheater:new {
	-- Task properties
	taskName = "FsSad1Theater5",
	-- GoToTheater properties
	minimumDistance = 1000,
	maximumDistance = 2200,
	theater = {
		{ template = "object/static/structure/dathomir/mtn_clan_hut_s01.iff", xDiff = 0.896, zDiff = 0.236, yDiff = -0.272, heading = 0 },
		{ template = "object/static/structure/general/camp_campfire_logs_smoldering_s01.iff", xDiff = 0.089, zDiff = 0.008, yDiff = 0.682, heading = -16.464 },
		{ template = "object/static/structure/general/prp_junk_s8.iff", xDiff = 0.513, zDiff = 0.247, yDiff = -2.335, heading = 0 },
		{ template = "object/static/structure/general/camp_stool_short_s01.iff", xDiff = 0.400, zDiff = -0.0404, yDiff = 1.733, heading = 0 },
		{ template = "object/static/structure/general/camp_stool_short_s01.iff", xDiff = -1.521, zDiff = -0.209, yDiff = 0.653, heading = 0 },
		{ template = "object/static/structure/general/camp_stool_short_s01.iff", xDiff = -0.376, zDiff = -0.241, yDiff = -0.460, heading = 0 },
	},
	mobileList = {
		{ template = "sith_shadow_pirate", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_pirate", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_pirate", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_pirate", minimumDistance = 7, maximumDistance = 12, referencePoint = 0 }
	},
	createWaypoint = true,
	waypointDescription = "@quest/quest_journal/fs_quests_sad:task5",
	activeAreaRadius = 16,
	flattenLayer = true
}

function FsSad1Theater5:onObjectsSpawned(pPlayer, spawnedMobileList)
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

function FsSad1Theater5:onTheaterCreated(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pTheater = self:getTheaterObject(pPlayer)

	if (pTheater ~= nil) then
		SuiRadiationSensor:setLocation(pPlayer, SceneObject(pTheater):getWorldPositionX(), SceneObject(pTheater):getWorldPositionY(), SceneObject(pTheater):getZoneName())
	end
end

function FsSad1Theater5:notifyKilledMobile(pVictim, pAttacker)
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
		QuestManager.completeQuest(pOwner, QuestManager.quests.FS_QUESTS_SAD_TASK5)
		QuestManager.activateQuest(pOwner, QuestManager.quests.FS_QUESTS_SAD_RETURN5)
		deleteData(ownerID .. self.taskName .. ":killableCount", numEnemies)

		local pGhost = CreatureObject(pOwner):getPlayerObject()

		if (pGhost ~= nil) then
			PlayerObject(pGhost):addWaypoint("dathomir", "@quest/quest_journal/fs_quests_sad:return5", "", 5238, -4189, WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)
		end
	end

	deleteData(mobileID .. self.taskName .. "ownerID")
	return 1
end

return FsSad1Theater5
