local ObjectManager = require("managers.object.object_manager")
local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")
local FsPatrol = require("managers.jedi.village.phase1.fs_patrol")
local QuestManager = require("managers.quest.quest_manager")

villageSarguilloPhase1ConvoHandler = {  }

function villageSarguilloPhase1ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	local playerID = SceneObject(pPlayer):getObjectID()
	local completedCount = tonumber(QuestManager.getStoredVillageValue(pPlayer, "FsPatrolCompletedCount"))
	local completedLastPoint = readData(playerID .. ":completedCurrentPoint") == 1
	local failedPatrol = readData(playerID .. ":failedPatrol") == 1
	local currentQuestID = QuestManager.getCurrentQuestID(pPlayer)
	local reachedAllWaypoints = readData(playerID .. ":patrolWaypointsReached") == 8

	if (VillageJediManagerTownship:getCurrentPhase() ~= 1) then
		return convoTemplate:getScreen("intro_noteligible")
	elseif (completedCount == 20) then
		return convoTemplate:getScreen("intro_didallpatrols")
	elseif (completedCount == 9 and reachedAllWaypoints and completedLastPoint and not failedPatrol) then
		return convoTemplate:getScreen("intro_completedfirstset")
	elseif (completedCount == 19 and reachedAllWaypoints and completedLastPoint and not failedPatrol) then
		return convoTemplate:getScreen("intro_completedsecondset")
	elseif (completedCount == 10 and currentQuestID == 90) then
		-- Player has not taken patrol 11
		return convoTemplate:getScreen("intro_startsecondset")
	elseif (currentQuestID >= 81 and currentQuestID <= 90) then
		return convoTemplate:getScreen("intro_firstsetinprogress")
	elseif (currentQuestID >= 91 and currentQuestID <= 100) then
		return convoTemplate:getScreen("intro_secondsetinprogress")
	end
	return convoTemplate:getScreen("intro")
end

function villageSarguilloPhase1ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local playerID = SceneObject(conversingPlayer):getObjectID()
	local completedLastPoint = readData(playerID .. ":completedCurrentPoint") == 1
	local completedCount = tonumber(QuestManager.getStoredVillageValue(conversingPlayer, "FsPatrolCompletedCount"))
	local failedPatrol = readData(playerID .. ":failedPatrol") == 1
	local reachedAllWaypoints = readData(playerID .. ":patrolWaypointsReached") == 8

	if (screenID == "all_eight_points") then
		QuestManager.setCurrentQuestID(conversingPlayer, QuestManager.quests.FS_PATROL_QUEST_1)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_PATROL_QUEST_START)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_PATROL_QUEST_1)
		QuestManager.setStoredVillageValue(conversingPlayer, "FsPatrolCompletedCount", 0)
		FsPatrol:start(conversingPlayer)
	elseif (screenID == "you_know_the_drill") then
		QuestManager.setCurrentQuestID(conversingPlayer, QuestManager.quests.FS_PATROL_QUEST_11)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_PATROL_QUEST_11)
		FsPatrol:start(conversingPlayer)
	elseif (screenID == "intro_firstsetinprogress") then
		if (reachedAllWaypoints and completedLastPoint and not failedPatrol) then
			clonedConversation:addOption("@conversation/fs_patrol_quest_start:s_6d3ed33b", "you_know_routine")
		else
			clonedConversation:addOption("@conversation/fs_patrol_quest_start:s_6d3ed33b", "worried_about_performance")
		end
		clonedConversation:addOption("@conversation/fs_patrol_quest_start:s_d33566f3", "are_you_sure")
	elseif (screenID == "intro_secondsetinprogress") then
		if (reachedAllWaypoints and completedLastPoint and not failedPatrol) then
			clonedConversation:addOption("@conversation/fs_patrol_quest_start:s_6d3ed33b", "get_to_it")
		else
			clonedConversation:addOption("@conversation/fs_patrol_quest_start:s_6d3ed33b", "data_is_incomplete")
		end
		clonedConversation:addOption("@conversation/fs_patrol_quest_start:s_d33566f3", "are_you_sure")
	elseif (screenID == "you_know_routine" or screenID == "get_to_it") then
		local questID = QuestManager.getCurrentQuestID(conversingPlayer)
		QuestManager.completeQuest(conversingPlayer, questID)
		questID = questID + 1
		QuestManager.setCurrentQuestID(conversingPlayer, questID)
		QuestManager.activateQuest(conversingPlayer, questID)
		QuestManager.setStoredVillageValue(conversingPlayer, "FsPatrolCompletedCount", completedCount + 1)
		FsPatrol:completeFsPatrol(conversingPlayer)
		FsPatrol:start(conversingPlayer)
	elseif (screenID == "need_data_asap" or screenID == "worried_about_performance" or screenID == "data_is_incomplete") then
		FsPatrol:resetFsPatrol(conversingPlayer)
	elseif (screenID == "intro_completedfirstset") then
		FsPatrol:completeFsPatrol(conversingPlayer)
		QuestManager.setStoredVillageValue(conversingPlayer, "FsPatrolCompletedCount", completedCount + 1)
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_PATROL_QUEST_10)
		VillageJediManagerCommon.unlockBranch(conversingPlayer, "force_sensitive_combat_prowess_ranged_accuracy")
	elseif (screenID == "intro_completedsecondset") then
		FsPatrol:completeFsPatrol(conversingPlayer)
		QuestManager.setStoredVillageValue(conversingPlayer, "FsPatrolCompletedCount", completedCount + 1)
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_PATROL_QUEST_20)
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_PATROL_QUEST_FINISH)
		QuestManager.setCurrentQuestID(conversingPlayer, 0)

		local pInventory = SceneObject(conversingPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pPole = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_village_bannerpole_s01.iff", -1, true)

			if (pPole == nil) then
				CreatureObject(conversingPlayer):sendSystemMessage("Error: Unable to generate item.")
			end
		end
	end

	return conversationScreen
end

function villageSarguilloPhase1ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()
	local pLastConversationScreen = nil
	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)
		return conversationTemplate:getScreen(optionLink)
	end
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end

