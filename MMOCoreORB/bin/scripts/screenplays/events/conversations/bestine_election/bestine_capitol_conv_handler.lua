local ObjectManager = require("managers.object.object_manager")

bestineCapitolConvoHandler = Object:new {
	themePark = nil
}

function bestineCapitolConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function bestineCapitolConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local phase = BestineElectionScreenPlay:getCurrentPhase()
	if phase == 1 then
		return convoTemplate:getScreen("election_started")
	end

	if phase == 2 then
		return convoTemplate:getScreen("election_ended")
	end
end

function bestineCapitolConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function bestineCapitolConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
