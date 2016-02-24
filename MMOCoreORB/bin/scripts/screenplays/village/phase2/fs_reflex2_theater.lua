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
	despawnTime = 20 * 60 * 1000, -- 20 minutes
	activeAreaRadius = 16,
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil
}

function FsReflex2Theater:onEnteredActiveArea(pCreatureObject, mobileList)
	if (pCreatureObject == nil) then
		return
	end

	self:removeTheaterWaypoint(pCreatureObject)
	QuestManager.completeQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_FETCH_QUEST_02)

	local pInventory = SceneObject(pCreatureObject):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local pPole = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_reflex_supply_crate.iff", -1, true)

		if (pPole == nil) then
			CreatureObject(pCreatureObject):sendSystemMessage("Error: Unable to generate item.")
		else
			CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_got_crate");
		end
	end

	FsReflex2GoBack:start(pCreatureObject)
end

function FsReflex2Theater:onSuccessfulSpawn(pCreatureObject, mobileList)
	if (pCreatureObject == nil) then
		return
	end

	QuestManager.completeQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_FETCH_QUEST_01)
	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_FETCH_QUEST_02)
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pCreatureObject)
end

function FsReflex2Theater:onPlayerKilled(pCreatureObject, pKiller, nothing)
	if (pCreatureObject == nil or pKiller == nil) then
		return 0
	end

	if (QuestManager.hasActiveQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)) then
		return 1
	end

	CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_fail_incap");
	Logger:log("Player was killed.", LT_INFO)
	self:finish(pCreatureObject)
	FsReflex2:failQuest(pCreatureObject)

	return 1
end

function FsReflex2Theater:onLoggedIn(pCreatureObject)
	if (not self:hasTaskStarted(pCreatureObject)) then
		return 1
	end
	
	if (VillageJediManagerTownship:getCurrentPhase() ~= 2) then
		FsReflex2:doPhaseChangeFail(pCreatureObject)
	else
		if (not QuestManager.hasCompletedQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)) then
			CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_fail_phase_done"); -- No logged out error message in string files, using phase change error instead
			FsReflex2:failQuest(pCreatureObject)
		end
		self:finish(pCreatureObject)
	end

	return 1
end

return FsReflex2Theater
