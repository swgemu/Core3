local ObjectManager = require("managers.object.object_manager")

record_keeper_conv_handler = Object:new {
	keeper = nil
}

function record_keeper_conv_handler:setThemePark(keeperNew)
	self.keeper = keeperNew
end

function record_keeper_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pConversingPlayer):getConversationSession()
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
	return self:getInitialScreen(pConversingPlayer, pConversationTemplate)
end

function record_keeper_conv_handler:getInitialScreen(pConversingPlayer, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	-- is this a factionol record keeper?
	if self.keeper == nil then
		return convoTemplate:getScreen("init")
	end

	-- has this player used this keeper before?
	if self.keeper:available(pConversingPlayer) then
		if self.keeper:needsFaction() then
			if not self.keeper:hasFaction(self.keeper.faction,pConversingPlayer) then
				return convoTemplate:getScreen("not_faction")
			end
		end

		if not self.keeper:hasStartedPark(pConversingPlayer) then
			return convoTemplate:getScreen("not_started")
		end

		return convoTemplate:getScreen("start")
	else
		-- keeper used up
		return convoTemplate:getScreen("completed")
	end
end

function record_keeper_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()

	local objectID = CreatureObject(pConversingPlayer):getObjectID()

	if screenID == "reset" then
		self.keeper:wipeQuests(pConversingPlayer)
		-- goto next screen
	end

	if screenID == "continue" then
		self.keeper:resetQuests(pConversingPlayer)
		-- goto next screen
	end

	return conversationScreen
end
