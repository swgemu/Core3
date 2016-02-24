local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageSurveyorConvoHandler = {  }

function villageSurveyorConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local phase = VillageJediManagerTownship:getCurrentPhase()

	if (phase ~= 2 and phase ~= 3) then
		return convoTemplate:getScreen("intro_wrong_phase")
	elseif (not CreatureObject(pPlayer):hasSkill("crafting_artisan_novice")) then
		return convoTemplate:getScreen("intro_no_skill")
	elseif (phase == 2 and VillageJediManagerCommon.hasUnlockedBranch(pPlayer, "force_sensitive_heightened_senses_surveying")) then
		return convoTemplate:getScreen("intro_completed_current_phase")
	elseif (phase == 3 and VillageJediManagerCommon.hasUnlockedBranch(pPlayer, "force_sensitive_heightened_senses_luck")) then
		return convoTemplate:getScreen("intro_completed_current_phase")
	end

	local hasQuest = FsSurvey:hasSurveyorQuest(pPlayer, phase)

	if (hasQuest ~= "") then
		return convoTemplate:getScreen("intro_in_progress")
	end

	if (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_other_quest")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageSurveyorConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	local phase = VillageJediManagerTownship:getCurrentPhase()

	if (screenID == "intro_in_progress") then
		local hasQuest = FsSurvey:hasSurveyorQuest(conversingPlayer, phase)

		if (hasQuest == "") then
			clonedConversation:setDialogTextStringId("@quest/force_sensitive/fs_survey:wrong_phase")
			return conversationScreen
		end
		local pQuest = getQuestInfo(hasQuest)

		local questTarget = LuaQuestInfo(pQuest):getQuestTarget()
		clonedConversation:setDialogTextStringId("@quest/force_sensitive/fs_survey:sample_for_" .. questTarget)
	elseif (screenID == "special_answer") then
		clonedConversation:setDialogTextStringId("@quest/force_sensitive/fs_survey:special_answer_" .. phase)
		clonedConversation:addOption("@quest/force_sensitive/fs_survey:yes_task", "sample_phase_" .. phase)
		clonedConversation:addOption("@quest/force_sensitive/fs_survey:no_task", "sorry_to_hear_that")
	elseif (screenID == "sample_phase_2") then
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.SURVEY_PHASE2_MAIN)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.SURVEY_PHASE2_01)
		VillageJediManagerCommon.setActiveQuestThisPhase(conversingPlayer)
		createObserver(SAMPLE, "FsSurvey", "sampleEventHandler", conversingPlayer, 1)
	elseif (screenID == "sample_phase_3") then
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.SURVEY_PHASE3_MAIN)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.SURVEY_PHASE3_01)
		VillageJediManagerCommon.setActiveQuestThisPhase(conversingPlayer)
		createObserver(SAMPLE, "FsSurvey", "sampleEventHandler", conversingPlayer, 1)
	end

	return conversationScreen
end

function villageSurveyorConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
