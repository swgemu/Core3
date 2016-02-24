local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageQuharekPhase1ConvoHandler = {  }

function villageQuharekPhase1ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 1) then
		return convoTemplate:getScreen("intro_wrong_phase")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_03)) then
		return convoTemplate:getScreen("intro_completed_quest")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00)) then
		return convoTemplate:getScreen("intro_inprogress")
	elseif (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_completed_other_quest")
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_other_quest")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageQuharekPhase1ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "get_to_work") then
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00)
		VillageJediManagerCommon.setActiveQuestThisPhase(conversingPlayer)
		FsCrafting1Goto1:start(conversingPlayer)
	end

	return conversationScreen
end

function villageQuharekPhase1ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
