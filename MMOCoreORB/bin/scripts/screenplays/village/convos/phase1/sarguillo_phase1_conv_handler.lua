local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageSarguilloPhase1ConvoHandler = conv_handler:new {}

function villageSarguilloPhase1ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local playerID = SceneObject(pPlayer):getObjectID()
	local completedCount = tonumber(QuestManager.getStoredVillageValue(pPlayer, "FsPatrolCompletedCount"))
	local completedLastPoint = readData(playerID .. ":completedCurrentPoint") == 1
	local failedPatrol = readData(playerID .. ":failedPatrol") == 1
	local currentQuestID = QuestManager.getCurrentQuestID(pPlayer)
	local reachedAllWaypoints = readData(playerID .. ":patrolWaypointsReached") == 8

	if (VillageJediManagerTownship:getCurrentPhase() ~= 1 or not VillageJediManagerCommon.isVillageEligible(pPlayer)) then
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
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_hasotherquest")
	elseif (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_noteligible")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageSarguilloPhase1ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local playerID = SceneObject(pPlayer):getObjectID()
	local completedLastPoint = readData(playerID .. ":completedCurrentPoint") == 1
	local completedCount = tonumber(QuestManager.getStoredVillageValue(pPlayer, "FsPatrolCompletedCount"))
	local failedPatrol = readData(playerID .. ":failedPatrol") == 1
	local reachedAllWaypoints = readData(playerID .. ":patrolWaypointsReached") == 8

	if (screenID == "all_eight_points") then
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE1_SARGUILLO)
		QuestManager.setCurrentQuestID(pPlayer, QuestManager.quests.FS_PATROL_QUEST_1)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_PATROL_QUEST_START)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_PATROL_QUEST_1)
		QuestManager.setStoredVillageValue(pPlayer, "FsPatrolCompletedCount", 0)
		FsPatrol:start(pPlayer)
	elseif (screenID == "you_know_the_drill") then
		QuestManager.setCurrentQuestID(pPlayer, QuestManager.quests.FS_PATROL_QUEST_11)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_PATROL_QUEST_11)
		FsPatrol:start(pPlayer)
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
		self:completeCurrentPatrol(pPlayer)
	elseif (screenID == "need_data_asap" or screenID == "worried_about_performance" or screenID == "data_is_incomplete") then
		FsPatrol:resetFsPatrol(pPlayer)
	elseif (screenID == "intro_completedfirstset" or screenID == "intro_completedsecondset") then
		self:completeCurrentPatrol(pPlayer)
	end

	return pConvScreen
end

function villageSarguilloPhase1ConvoHandler:completeCurrentPatrol(pPlayer)
	local completedCount = tonumber(QuestManager.getStoredVillageValue(pPlayer, "FsPatrolCompletedCount")) + 1
	FsPatrol:completeFsPatrol(pPlayer)
	QuestManager.setStoredVillageValue(pPlayer, "FsPatrolCompletedCount", completedCount)

	if (completedCount == 10) then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_PATROL_QUEST_10)
		VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_combat_prowess_ranged_accuracy")
	elseif (completedCount == 20) then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_PATROL_QUEST_20)
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_PATROL_QUEST_FINISH)
		QuestManager.setCurrentQuestID(pPlayer, 0)
		VillageJediManagerCommon.setCompletedQuestThisPhase(pPlayer)

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pPole = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_village_bannerpole_s01.iff", -1, true)

			if (pPole == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
			end
		end
	else
		local questID = QuestManager.getCurrentQuestID(pPlayer)
		QuestManager.completeQuest(pPlayer, questID)
		questID = questID + 1
		QuestManager.setCurrentQuestID(pPlayer, questID)
		QuestManager.activateQuest(pPlayer, questID)
		FsPatrol:start(pPlayer)
	end
end
