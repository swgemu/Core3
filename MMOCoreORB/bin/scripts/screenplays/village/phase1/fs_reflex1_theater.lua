local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

require("utils.helpers")

FsReflex1Theater = GoToTheater:new {
	-- Task properties
	taskName = "FsReflex1Theater",
	-- GoToTheater properties
	minimumDistance = 50,
	maximumDistance = 200,
	theater = {
		{ template = "object/static/structure/military/military_wall_med_imperial_style_01.iff", xDiff = 0.5, zDiff = -0.11, yDiff = 2.12, heading = -14.32 },
		{ template = "object/static/structure/military/military_column_med_imperial_style_01.iff", xDiff = -3.84, zDiff = -0.11, yDiff = 1.098, heading = -14.32 },
		{ template = "object/static/structure/military/military_column_med_imperial_style_01.iff", xDiff = 4.95, zDiff = -0.1, yDiff = 3.24, heading = -14.32 },
		{ template = "object/static/structure/naboo/poi_nboo_tent_small.iff", xDiff = -1.61, zDiff = 0.32, yDiff = -6.46, heading = 14.32 }
	},
	waypointDescription = "@quest/quest_journal/fs_quests_reflex1:s_02",
	mobileListWithLoc = {
		{ template = "fs_reflex1_prisoner", x = 1.146, y = -0.849 },
		{ template = "sith_shadow_pirate", x = 2.42, y = 1.669 },
		{ template = "sith_shadow_thug", x = -0.127, y = -3.36 }
	},
	activeAreaRadius = 32
}

function FsReflex1Theater:onEnteredActiveArea(pPlayer, mobileList)
	if (pPlayer == nil) then
		return
	end

	if (not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_01)) then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_01)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_02)
	end
end

function FsReflex1Theater:onObjectsSpawned(pPlayer, mobileList)
	if (pPlayer == nil) then
		return
	end

	if (SpawnMobiles.isValidMobile(mobileList[1])) then
		writeData(SceneObject(mobileList[1]):getObjectID() .. ":ownerID", SceneObject(pPlayer):getObjectID())
		CreatureObject(mobileList[1]):setPvpStatusBitmask(0)
	end
end

function FsReflex1Theater:onTheaterCreated(pPlayer)
	if (pPlayer == nil) then
		return
	end

	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pPlayer)
end

function FsReflex1Theater:onTheaterFinished(pPlayer)
	if (pPlayer == nil) then
		return
	end

	dropObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pPlayer)
end

function FsReflex1Theater:onPlayerKilled(pPlayer, pKiller, nothing)
	if (pPlayer == nil or pKiller == nil) then
		return 0
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)) then
		return 1
	end

	self:finish(pPlayer)
	FsReflex1:failQuest(pPlayer, "@quest/force_sensitive/fs_reflex:msg_phase_01_quest_fail_incap")

	return 1
end

return FsReflex1Theater
