conv_handler = Object:new {}

function conv_handler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption, pNpc)
	local convsession = CreatureObject(pPlayer):getConversationSession()

	local lastConvScreen = nil

	if (convsession ~= nil) then
		local session = LuaConversationSession(convsession)
		lastConvScreen = session:getLastConversationScreen()
	end

	local conv = LuaConversationTemplate(pConvTemplate)

	local nextConvScreen

	if (lastConvScreen ~= nil) then
		local luaLastConvScreen = LuaConversationScreen(lastConvScreen)

		--Get the linked screen for the selected option.
		local optionLink = luaLastConvScreen:getOptionLink(selectedOption)

		nextConvScreen = conv:getScreen(optionLink)

		if nextConvScreen == nil then
			nextConvScreen = self:getInitialScreen(pPlayer, pNpc, pConvTemplate)
		end
	else
		nextConvScreen = self:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	end

	return nextConvScreen
end

function conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convTemplate = LuaConversationTemplate(pConvTemplate)
	return convTemplate:getInitialScreen()
end

function conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	return pConvScreen
end
