-- imperial officer 6
imperial_officer_6_handler = {  }
 
function imperial_officer_6_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	local lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
	
	local conversation = LuaConversationTemplate(conversationTemplate)
	
	local nextConversationScreen
	
	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
		
		if (nextLuaConversationScreen:getScreenID() == "convoscreen2") then
			writeData(creature:getObjectID() .. ":tutorial:officer6flag", 1)
		end
	else
		
		--Get the initial screen.
		officer5flag = readData(creature:getObjectID() .. ":tutorial:officer5flag")
		
		if (officer5flag == 0) then
			nextConversationScreen = conversation:getScreen("convoscreen3")
		else
			nextConversationScreen = conversation:getInitialScreen()
			
			terminal = readData(creature:getObjectID() .. ":tutorial:travelTerminal")
			local travelTerminal = getSceneObject(terminal)
			setAuthorizationState(travelTerminal, true)		
		end
	end
	return nextConversationScreen

end

function imperial_officer_6_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end