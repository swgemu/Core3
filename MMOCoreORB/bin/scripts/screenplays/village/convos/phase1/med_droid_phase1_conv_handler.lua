local ObjectManager = require("managers.object.object_manager")
local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")
local FsMedicPuzzle = require("managers.jedi.village.phase1.fs_medic_puzzle")
local QuestManager = require("managers.quest.quest_manager")

villageMedicalDroidPhase1ConvoHandler = {  }

function villageMedicalDroidPhase1ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03) and
		not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02) and
		not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01) then
		return convoTemplate:getScreen("intro_no_quest")
	elseif (FsMedicPuzzle:hasAnySymptoms(pPlayer, pNpc)) then
		return convoTemplate:getScreen("intro_has_symptoms")
	end

	return convoTemplate:getScreen("intro")
end

function villageMedicalDroidPhase1ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "intro_has_symptoms" or screenID == "currently_suffering_from") then
		if (screenID == "currently_suffering_from") then
			FsMedicPuzzle:giveSymptoms(conversingPlayer, conversingNPC)
		end
		local symptoms = FsMedicPuzzle:getSymptoms(conversingPlayer, conversingNPC)
		clonedConversation:setDialogTextTO(symptoms)
	end

	return conversationScreen
end

function villageMedicalDroidPhase1ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
