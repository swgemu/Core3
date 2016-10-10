local ObjectManager = require("managers.object.object_manager")

record_keeper_conv_handler = conv_handler:new {
	keeper = nil
}

function record_keeper_conv_handler:setThemePark(keeperNew)
	self.keeper = keeperNew
end

function record_keeper_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	-- is this a factionol record keeper?
	if self.keeper == nil then
		return convoTemplate:getScreen("init")
	end

	-- has this player used this keeper before?
	if self.keeper:available(pPlayer) then
		if self.keeper:needsFaction() then
			if not self.keeper:hasFaction(self.keeper.faction, pPlayer) then
				return convoTemplate:getScreen("not_faction")
			end
		end

		if not self.keeper:hasStartedPark(pPlayer) then
			return convoTemplate:getScreen("not_started")
		end

		return convoTemplate:getScreen("start")
	else
		-- keeper used up
		return convoTemplate:getScreen("completed")
	end
end

function record_keeper_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()

	local objectID = CreatureObject(pPlayer):getObjectID()

	if screenID == "reset" then
		self.keeper:wipeQuests(pPlayer)
		-- goto next screen
	end

	if screenID == "continue" then
		self.keeper:resetQuests(pPlayer)
		-- goto next screen
	end

	return conversationScreen
end
