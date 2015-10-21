local ObjectManager = require("managers.object.object_manager")
local Reflex1Escort = require("managers.jedi.village.phase1.fs_reflex1_escort")
local QuestManager = require("managers.quest.quest_manager")

villageFsReflex1PrisonerConvoHandler = {  }

function villageFsReflex1PrisonerConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()

	if (readData(npcID .. ":ownerID") ~= playerID) then
		return convoTemplate:getScreen("intro_wrongplayer")
	elseif (readData(npcID .. ":safe") == 1) then
		return convoTemplate:getScreen("intro_rescued")
	elseif (CreatureObject(pNpc):isInCombat()) then
		return convoTemplate:getScreen("intro_incombat")
	elseif (readData(playerID .. ":failedWhipPhase1") == 1) then
		return convoTemplate:getScreen("intro_failedquest")
	elseif (readData(playerID .. ":escortInProgress") == 1) then
		return convoTemplate:getScreen("intro_inprogress")
	end
	return convoTemplate:getScreen("intro")
end

function villageFsReflex1PrisonerConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "intro") then
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_02)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_03)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)
		Reflex1Escort:start(conversingPlayer, conversingNPC)
	end

	return conversationScreen
end

function villageFsReflex1PrisonerConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
