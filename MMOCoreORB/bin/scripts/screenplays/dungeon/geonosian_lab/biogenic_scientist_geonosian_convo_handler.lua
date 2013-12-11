biogenic_scientist_geonosian_ConversationHandler = Object:new {
}

function biogenic_scientist_geonosian_ConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local player = LuaCreatureObject(pConversingPlayer)
	local pPlayerObject = player:getPlayerObject()
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if screenID == "biogen_geo_random" then
		local val = math.random(2)
	
		if (val == 1) then
			return convoTemplate:getScreen("biogen_geo_nono")
		else
			return convoTemplate:getScreen("biogen_geo_doubt")
		end
	end

	if screenID == "biogen_geo_good_bye" then
		
		if (pPlayerObject) then
			local playerObject = LuaPlayerObject(pPlayerObject)
		player:setScreenPlayState(geonosian_labscreenplay.states.datapad.done, "geonosian_lab");
		geonosian_labscreenplay:giveGeoDatapad(pConversingPlayer)

		end
	end
	
	return pConversationScreen
end

function biogenic_scientist_geonosian_ConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaCreatureObject(pPlayer)
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")

	if (conversingPlayer:hasScreenPlayState(geonosian_labscreenplay.states.datapad.done, "geonosian_lab") == 1) then
		return convoTemplate:getScreen("biogen_geo_done")
	
	end
		
	return convoTemplate:getScreen("biogen_geo_start")
end

function biogenic_scientist_geonosian_ConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
