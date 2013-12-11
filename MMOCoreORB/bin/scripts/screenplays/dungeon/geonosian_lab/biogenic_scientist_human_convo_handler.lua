biogenic_scientist_human_ConversationHandler = Object:new {
}

function biogenic_scientist_human_ConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local player = LuaCreatureObject(pConversingPlayer)
	local pPlayerObject = player:getPlayerObject()
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if screenID == "biogen_human_pleasure" then
		
		if (pPlayerObject) then
			local playerObject = LuaPlayerObject(pPlayerObject)
		player:removeScreenPlayState(geonosian_labscreenplay.states.tenloss.noreward, "geonosian_lab");
		player:setScreenPlayState(geonosian_labscreenplay.states.tenloss.done, "geonosian_lab");
		geonosian_labscreenplay:giveGeoTenloss(pConversingPlayer)
		
		end

	end				
	
	if screenID == "biogen_human_second" then
				
		if (pPlayerObject) then
			local playerObject = LuaPlayerObject(pPlayerObject)
		player:setScreenPlayState(geonosian_labscreenplay.states.tenloss.noreward, "geonosian_lab");
		
		end

	end
	return pConversationScreen
end

function biogenic_scientist_human_ConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaCreatureObject(pPlayer)
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")

	if (conversingPlayer:hasScreenPlayState(geonosian_labscreenplay.states.tenloss.done, "geonosian_lab") == 1) then
		return convoTemplate:getScreen("biogen_human_done")

	elseif (conversingPlayer:hasScreenPlayState(geonosian_labscreenplay.states.tenloss.noreward, "geonosian_lab") == 1) then
		return convoTemplate:getScreen("biogen_human_returnno")
	end
	
	return convoTemplate:getScreen("biogen_human_start")
end

function biogenic_scientist_human_ConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
