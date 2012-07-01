ManxTryConversationHandler = Object:new {
}

function ManxTryConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	return pConversationScreen
end

function ManxTryConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	
	if (readData("warren:reactor:active") == 0) then
		return convoTemplate:getScreen("researcher_2")
	end
	
	local player = LuaSceneObject(pPlayer)
	local pInventory = player:getSlottedObject("inventory")
	
	if (pInventory ~= nil) then
		local pRod1 = getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_core_control_rod_s01.iff", true)
		local pRod2 = getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_core_control_rod_s02.iff", true)
		
		if (pRod1 ~= nil) and (pRod2 ~= nil) then
			return convoTemplate:getScreen("researcher_3")
		end
	end
	
	return convoTemplate:getScreen("researcher_start")
end

function ManxTryConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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