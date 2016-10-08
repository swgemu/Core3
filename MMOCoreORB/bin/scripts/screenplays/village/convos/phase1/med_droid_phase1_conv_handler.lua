local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageMedicalDroidPhase1ConvoHandler = conv_handler:new {}

function villageMedicalDroidPhase1ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03) and
		not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02) and
		not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01) then
		return convoTemplate:getScreen("intro_no_quest")
	elseif (FsMedicPuzzle:hasAnySymptoms(pPlayer, pNpc)) then
		return convoTemplate:getScreen("intro_has_symptoms")
	end

	return convoTemplate:getScreen("intro")
end

function villageMedicalDroidPhase1ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "intro_has_symptoms" or screenID == "currently_suffering_from") then
		if (screenID == "currently_suffering_from") then
			FsMedicPuzzle:giveSymptoms(pPlayer, pNpc)
		end
		local symptoms = FsMedicPuzzle:getSymptoms(pPlayer, pNpc)
		clonedConversation:setDialogTextTO(symptoms)
	end

	return pConvScreen
end
