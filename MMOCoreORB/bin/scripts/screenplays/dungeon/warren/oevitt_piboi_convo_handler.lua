OevittPiboiConversationHandler = Object:new {
}

function OevittPiboiConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	
	local screenID = screen:getScreenID()
	
	if (screenID == "escapee_2") then
		WarrenScreenPlay:givePasskey1(pConversingPlayer)
	end
	
	return pConversationScreen
end

function OevittPiboiConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")
	
	if (pInventory ~= nil) then
		local pPasskey = getContainerObjectByTemplate(pInventory, WarrenScreenPlay.entranceKey, true)
		
		if (pPasskey ~= nil) then
			return convoTemplate:getScreen("escapee_haskey")
		end
	end
	
	return convoTemplate:getScreen("escapee_start")
end

function OevittPiboiConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local player = LuaCreatureObject(pPlayer)
	local pConversationSession = player:getConversationSession()
	
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
