local GoToTheater = require("quest.tasks.go_to_theater")
local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

require("utils.helpers")

FsReflex1Theater = GoToTheater:new {
	-- Task properties
	taskName = "FsReflex1Theater",
	-- GoToTheater properties
	minimumDistance = 64,
	maximumDistance = 128,
	theater = "object/static/structure/naboo/poi_nboo_tent_small.iff",
	waypointDescription = "@quest/quest_journal/fs_quests_reflex1:s_02",
	mobileList = {
		{ template = "fs_reflex1_prisoner", minimumDistance = 2, maximumDistance = 4, referencePoint = 0 },
		{ template = "sith_shadow_pirate", minimumDistance = 6, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_thug", minimumDistance = 6, maximumDistance = 12, referencePoint = 0 }
	},
	despawnTime = 20 * 60 * 1000, -- 20 minutes
	activeAreaRadius = 32,
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil
}

function FsReflex1Theater:onEnteredActiveArea(pCreatureObject, mobileList)
	if (pCreatureObject == nil) then
		return
	end

	self:removeTheaterWaypoint(pCreatureObject)
	QuestManager.completeQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_01)
	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_02)
end

function FsReflex1Theater:onSuccessfulSpawn(pCreatureObject, mobileList)
	if (pCreatureObject == nil) then
		return
	end

	if (mobileList[1] ~= nil) then
		writeData(SceneObject(mobileList[1]):getObjectID() .. ":ownerID", SceneObject(pCreatureObject):getObjectID())
		CreatureObject(mobileList[1]):setPvpStatusBitmask(0)
	end

	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pCreatureObject)
end

function FsReflex1Theater:onPlayerKilled(pCreatureObject, pKiller, nothing)
	if (pCreatureObject == nil or pKiller == nil) then
		return 0
	end

	if (QuestManager.hasActiveQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)) then
		return 1
	end

	CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_01_quest_fail_incap");
	Logger:log("Player was killed.", LT_INFO)
	self:finish(pCreatureObject)
	FsReflex1:failQuest(pCreatureObject)

	return 1
end

return FsReflex1Theater
