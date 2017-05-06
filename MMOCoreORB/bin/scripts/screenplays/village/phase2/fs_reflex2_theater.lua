local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

require("utils.helpers")

FsReflex2Theater = GoToTheater:new {
	-- Task properties
	taskName = "FsReflex2Theater",
	-- GoToTheater properties
	minimumDistance = 64,
	maximumDistance = 160,
	theater = {
		{ template = "object/static/structure/general/transport_debris_01.iff", xDiff = -0.65, zDiff = -1.38, yDiff = 4.53, heading = 0 },
		{ template = "object/static/particle/particle_smoke.iff", xDiff = 2.51, zDiff = 2.25, yDiff = -17.23, heading = 0 }
	},
	waypointDescription = "@quest/quest_journal/fs_quests_reflex2:s_02",
	mobileListWithLoc = {
		{ template = "sith_shadow_pirate", x = 9.75, y = -3.63 },
		{ template = "sith_shadow_pirate", x = -11.14, y = -7.26 },
		{ template = "sith_shadow_thug", x = -2.57, y = 12.67 }
	},
	activeAreaRadius = 16
}

function FsReflex2Theater:onEnteredActiveArea(pPlayer, mobileList)
	if (pPlayer == nil) then
		return
	end

	self:removeTheaterWaypoint(pPlayer)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_02)

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local pPole = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_reflex_supply_crate.iff", -1, true)

		if (pPole == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
		else
			CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_got_crate");
		end
	end

	FsReflex2GoBack:start(pPlayer)
end

function FsReflex2Theater:onTheaterCreated(pPlayer)
	if (pPlayer == nil) then
		return
	end

	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_01)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_02)
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pPlayer)
end

function FsReflex2Theater:onTheaterFinished(pPlayer)
	if (pPlayer == nil) then
		return
	end

	dropObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pPlayer)
end

function FsReflex2Theater:onPlayerKilled(pPlayer, pKiller, nothing)
	if (pPlayer == nil or pKiller == nil) then
		return 0
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)) then
		return 1
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_fail_incap");
	Logger:log("Player was killed.", LT_INFO)
	self:finish(pPlayer)
	FsReflex2:failQuest(pPlayer)

	return 1
end

return FsReflex2Theater
