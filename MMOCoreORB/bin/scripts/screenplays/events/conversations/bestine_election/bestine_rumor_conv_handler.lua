local ObjectManager = require("managers.object.object_manager")

bestineRumorConvoHandler = Object:new {
	themePark = nil
}

function bestineRumorConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function bestineRumorConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local Phase = BestineElectionScreenPlay:getCurrentPhase()

	if Phase == 1 then
		return convoTemplate:getScreen("election_started")
	end

	if Phase == 2 then
		return convoTemplate:getScreen("election_ended")
	end
end

function bestineRumorConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()
	local npcName = SceneObject(conversingNPC):getObjectName()
	local playerID = SceneObject(conversingPlayer):getObjectID()
	return conversationScreen
end

function bestineRumorConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
