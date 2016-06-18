local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageChiefEngineerPhase4ConvoHandler = {  }

function villageChiefEngineerPhase4ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 4) then
		return convoTemplate:getScreen("intro_wrong_phase")
	elseif (VillageJediManagerCommon.hasUnlockedBranch(pPlayer, "force_sensitive_crafting_mastery_repair")) then
		return convoTemplate:getScreen("intro_already_completed")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_07)) then
		return convoTemplate:getScreen("intro_quest7")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_06)) then
		return convoTemplate:getScreen("intro_quest6")
	elseif (self:isOnQuestOneThroughFive(pPlayer) and not VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_continue")
	elseif (self:isOnQuestOneThroughFive(pPlayer)) then
		return convoTemplate:getScreen("intro_quest1to5")
	elseif (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_not_eligible")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageChiefEngineerPhase4ConvoHandler:isOnQuestOneThroughFive(pPlayer)
	return QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_01) or QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_02) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_03) or QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_04) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_05)
end

function villageChiefEngineerPhase4ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "get_you_started") then
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")

		if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_4136c2df", "no_space_for_reward")
		else
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_4136c2df", "present_statue")
		end

		VillageJediManagerCommon.unlockBranch(conversingPlayer, "force_sensitive_combat_prowess_ranged_accuracy")
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_06)
		FsCrafting4:removeCore(conversingPlayer)
	elseif (screenID == "no_space_for_reward") then
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_07)
	elseif (screenID == "present_statue") then
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_00)
		if (QuestManager.hasActiveQuest(conversingPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_07)) then
			QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_07)
		end
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_FINISH)
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_FINISH)
		VillageJediManagerCommon.setCompletedQuestThisPhase(conversingPlayer)

		local pInventory = SceneObject(conversingPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pStatue = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_sculpture_2.iff", -1, true)

			if (pStatue == nil) then
				CreatureObject(conversingPlayer):sendSystemMessage("Error: Unable to generate item.")
			end
		end
	elseif (screenID == "intro_quest1to5") then
		local curQuestNum = FsCrafting4:getActiveQuestNum(conversingPlayer)

		if (curQuestNum == 1) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_a2e520b8", "location_reminder")
		elseif (curQuestNum == 2) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_c7baf80c", "build_device")
		elseif (curQuestNum == 3) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_bab2829b", "go_to_droid")
		elseif (curQuestNum == 4) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_7496bddd", "activate_device")
		elseif (curQuestNum == 5) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_e3e36f42", "interface_needs_modified")
		end

		clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_a69082f1", "good_come_back")
	elseif (screenID == "intro_quest6") then
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pCore = getContainerObjectByTemplate(pInventory, "object/tangible/item/quest/force_sensitive/fs_crafting4_computer_core.iff", true)

			if (pCore ~= nil) then
				clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_121666b3", "get_you_started")
			else
				clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_121666b3", "dont_have_it")
			end
		end
		clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_4294034a", "please_hurry")
	elseif (screenID == "intro_quest7") then
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")

		if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_6516bd5a", "no_space_for_reward")
		else
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_6516bd5a", "present_statue")
		end
	elseif (screenID == "intro") then
		if (VillageJediManagerCommon.hasActiveQuestThisPhase(conversingPlayer)) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_59f5cee6", "very_kind")
		else
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_59f5cee6", "yes_there_is")
		end
		clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_5542b04b", "quite_alright")
	elseif (screenID == "excellent_continue") then
		VillageJediManagerCommon.setActiveQuestThisPhase(conversingPlayer)
	elseif (screenID == "waypoint_keren") then
		ObjectManager.withCreaturePlayerObject(conversingPlayer, function(playerObject)
			playerObject:addWaypoint("naboo", "Keren - Gadget Specialist", "", 1215, 2740, WAYPOINTYELLOW, true, true, 0)
		end)
		FsCrafting4:activateQuest(conversingPlayer)
	elseif (screenID == "waypoint_coronet") then
		ObjectManager.withCreaturePlayerObject(conversingPlayer, function(playerObject)
			playerObject:addWaypoint("corellia", "Coronet - Gadget Specialist", "", 19, -4775, WAYPOINTYELLOW, true, true, 0)
		end)
		FsCrafting4:activateQuest(conversingPlayer)
	elseif (screenID == "waypoint_mos_entha") then
		ObjectManager.withCreaturePlayerObject(conversingPlayer, function(playerObject)
			playerObject:addWaypoint("tatooine", "Mos Entha - Gadget Specialist", "", 1209, 2923, WAYPOINTYELLOW, true, true, 0)
		end)
		FsCrafting4:activateQuest(conversingPlayer)
	elseif (screenID == "return_to_me") then
		FsCrafting4:activateQuest(conversingPlayer)
	end

	return conversationScreen
end

function villageChiefEngineerPhase4ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
