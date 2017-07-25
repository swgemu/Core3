local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageChiefEngineerPhase4ConvoHandler = conv_handler:new {}

function villageChiefEngineerPhase4ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 4) then
		return convoTemplate:getScreen("intro_wrong_phase")
	elseif (VillageJediManagerCommon.hasUnlockedBranch(pPlayer, "force_sensitive_crafting_mastery_repair")) then
		return convoTemplate:getScreen("intro_already_completed")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_07)) then
		return convoTemplate:getScreen("intro_quest7")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_06)) then
		return convoTemplate:getScreen("intro_quest6")
	elseif (self:isOnQuestOneThroughFive(pPlayer) and not VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer) and not VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_continue")
	elseif (self:isOnQuestOneThroughFive(pPlayer) and VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer) and not VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer) and VillageJediManagerCommon.getActiveQuestIdThisPhase(pPlayer) ~= VILLAGE_PHASE4_ENGINEER) then
		return convoTemplate:getScreen("intro_not_eligible")
	elseif (self:isOnQuestOneThroughFive(pPlayer)) then
		return convoTemplate:getScreen("intro_quest1to5")
	elseif (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer) or VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer) or not VillageJediManagerCommon.isVillageEligible(pPlayer)) then
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

function villageChiefEngineerPhase4ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "get_you_started") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_4136c2df", "no_space_for_reward")
		else
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_4136c2df", "present_statue")
		end

		VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_crafting_mastery_repair")
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_06)
		FsCrafting4:removeCore(pPlayer)
	elseif (screenID == "no_space_for_reward") then
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_07)
	elseif (screenID == "present_statue") then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_00)
		if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_07)) then
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_07)
		end
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_FINISH)
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_FINISH)
		VillageJediManagerCommon.setCompletedQuestThisPhase(pPlayer)

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pStatue = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_sculpture_2.iff", -1, true)

			if (pStatue == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
			end
		end
	elseif (screenID == "intro_quest1to5") then
		local curQuestNum = FsCrafting4:getActiveQuestNum(pPlayer)

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
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

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
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_6516bd5a", "no_space_for_reward")
		else
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_6516bd5a", "present_statue")
		end
	elseif (screenID == "intro") then
		if (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_59f5cee6", "very_kind")
		else
			clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_59f5cee6", "yes_there_is")
		end
		clonedConversation:addOption("@conversation/fs_phase4_chief_engineer:s_5542b04b", "quite_alright")
	elseif (screenID == "excellent_continue") then
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE4_ENGINEER)
	elseif (screenID == "waypoint_keren") then
		PlayerObject(pGhost):addWaypoint("naboo", "Keren - Gadget Specialist", "", 1215, 2740, WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)
		FsCrafting4:activateQuest(pPlayer)
	elseif (screenID == "waypoint_coronet") then
		PlayerObject(pGhost):addWaypoint("corellia", "Coronet - Gadget Specialist", "", 19, -4775, WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)
		FsCrafting4:activateQuest(pPlayer)
	elseif (screenID == "waypoint_mos_entha") then
		PlayerObject(pGhost):addWaypoint("tatooine", "Mos Entha - Gadget Specialist", "", 1209, 2923, WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)
		FsCrafting4:activateQuest(pPlayer)
	elseif (screenID == "return_to_me") then
		FsCrafting4:activateQuest(pPlayer)
	end

	return pConvScreen
end
