local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsReflex2 = ScreenPlay:new {}

function FsReflex2:startQuest(pPlayer)
	self:setFetchCount(pPlayer, 0)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00)
	FsReflex2Goto:start(pPlayer)
end

function FsReflex2:startNextFetch(pPlayer)
	self:resetFetchStatus(pPlayer)
	FsReflex2Theater:finish(pPlayer)
	FsReflex2Goto:start(pPlayer)
end

function FsReflex2:restartQuest(pPlayer)
	deleteData(SceneObject(pPlayer):getObjectID() .. ":failedWhipPhase2")

	self:resetTasks(pPlayer)

	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00)
	FsReflex2Goto:start(pPlayer)
end

function FsReflex2:failQuest(pPlayer)
	writeData(SceneObject(pPlayer):getObjectID() .. ":failedWhipPhase2", 1)
	FsReflex2Theater:finish(pPlayer)
	self:removeSupplyCrate(pPlayer)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_01)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_02)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03)
	dropObserver(OBJECTDESTRUCTION, "FsReflex2Theater", "onPlayerKilled", pPlayer)
end

function FsReflex2:resetFetchStatus(pPlayer)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_01)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_02)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03)
end

function FsReflex2:resetTasks(pPlayer)
	if (FsReflex2Goto:hasTaskStarted(pPlayer)) then
		FsReflex2Goto:finish(pPlayer)
	end
	if (FsReflex2Theater:hasTaskStarted(pPlayer)) then
		FsReflex2Theater:finish(pPlayer)
	end
	if (FsReflex2GoBack:hasTaskStarted(pPlayer)) then
		FsReflex2GoBack:finish(pPlayer)
	end

	self:removeSupplyCrate(pPlayer)
	dropObserver(OBJECTDESTRUCTION, "FsReflex2Theater", "onPlayerKilled", pPlayer)
end

function FsReflex2:hasActiveFetch(pPlayer)
	return (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_01) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_02) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)) and not
		QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)
end

function FsReflex2:removeSupplyCrate(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory ~= nil then
		local pSupplies = getContainerObjectByTemplate(pInventory, "object/tangible/item/quest/force_sensitive/fs_reflex_supply_crate.iff", false)

		if (pSupplies ~= nil) then
			SceneObject(pSupplies):destroyObjectFromWorld()
			SceneObject(pSupplies):destroyObjectFromDatabase()
		end
	end
end

function FsReflex2:completeSupplyFetch(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local count = self:getFetchCount(pPlayer) + 1

	self:setFetchCount(pPlayer, count)

	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03)
	self:resetTasks(pPlayer)

	if (count == 6) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_finished")
		VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_enhanced_reflexes_vehicle_control")
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00)
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)
		VillageJediManagerCommon.setCompletedQuestThisPhase(pPlayer)

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pBuffItem = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_buff_item.iff", -1, true)

			if (pBuffItem == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
			else
				local buffItem = LuaFsBuffItem(pBuffItem)
				buffItem:setBuffAttribute(0)
				buffItem:setReuseTime(259200000)
				buffItem:setBuffValue(2000)
				buffItem:setBuffDuration(7200)
			end
		end

	else
		local messageString = LuaStringIdChatParameter("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_continue")
		messageString:setDI(6 - count)
		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	end
end

function FsReflex2:getFetchCount(pPlayer)
	local count = readScreenPlayData(pPlayer, "VillageJediProgression", "FsReflex2Fetches")

	if (count == "") then
		count = 0
	end

	return tonumber(count)
end

function FsReflex2:setFetchCount(pPlayer, count)
	writeScreenPlayData(pPlayer, "VillageJediProgression", "FsReflex2Fetches", count)
end

function FsReflex2:doPhaseChangeFail(pPlayer)
	if (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00) or not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00)) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_fail_phase_done");

	for i = 0, 6, 1 do
		local questName = "fs_reflex_fetch_quest_0" .. i
		local questID = getPlayerQuestID(questName)

		QuestManager.resetQuest(pPlayer, questID)
	end

	FsReflex2:resetTasks(pPlayer)
	deleteData(SceneObject(pPlayer):getObjectID() .. ":failedWhipPhase2")
end

return FsReflex2
