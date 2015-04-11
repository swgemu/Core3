MirlaConversationHandler = Object:new {
}

function MirlaConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	
	local screenID = screen:getScreenID()
	
	if (screenID == "mirla_password") then
		local screen = LuaConversationScreen(pConversationScreen)
		local code = readStringData("warren:mirla:password")
		screen:setDialogTextTO(code)
	elseif (screenID == "mirla_2") then
		local player = LuaCreatureObject(pConversingPlayer)
		local pPlayerObject = player:getPlayerObject()
		
		if (pPlayerObject) then
			local playerObject = LuaPlayerObject(pPlayerObject)
			playerObject:awardBadge(38) --Warren Compassion
			player:setScreenPlayState(WarrenScreenPlay.states.mirla.started, "warren");
		end
	end
	
	return pConversationScreen
end

function MirlaConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")
	
	local player = LuaCreatureObject(pPlayer)
	
	if (player:hasScreenPlayState(WarrenScreenPlay.states.mirla.done, "warren")) then
		return convoTemplate:getScreen("mirla_done")
	elseif (player:hasScreenPlayState(WarrenScreenPlay.states.mirla.started, "warren")) then
		return convoTemplate:getScreen("mirla_get_teraud")
	end
	
	return convoTemplate:getScreen("mirla_start")
end

function MirlaConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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