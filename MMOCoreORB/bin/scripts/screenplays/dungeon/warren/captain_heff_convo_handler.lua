CaptainHeffConversationHandler = Object:new {
}

function CaptainHeffConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()
	
	if (screenID == "heff_1") then
		local conversingPlayer = LuaSceneObject(pConversingPlayer)
		
		if (conversingPlayer:isPlayerCreature()) then
			local pPlayerObject = conversingPlayer:getSlottedObject("ghost")
			if (pPlayerObject ~= nil) then
				local playerObject = LuaPlayerObject(pPlayerObject)
				playerObject:awardBadge(39)
			end
		end
	end
	
	return pConversationScreen
end

function CaptainHeffConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	
	local player = LuaSceneObject(pPlayer)
	local pPlayerObject = player:getSlottedObject("ghost")
	
	if (player:isPlayerCreature()) and (pPlayerObject ~= nil) then
		local playerObject = LuaPlayerObject(pPlayerObject)
		
		if (playerObject:hasBadge(39)) then
			return convoTemplate:getScreen("heff_done")
		else
			local pDatapad = player:getSlottedObject("datapad")
			
			if (pDatapad ~= nil) then
				local pEvidence1 = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_evidence_01.iff", false)
				local pEvidence2 = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_evidence_02.iff", false)
				local pEvidence3 = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_evidence_03.iff", false)
				local pEvidence4 = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_evidence_04.iff", false)
				local pEvidence5 = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_encryption_key.iff", false)
				
				if (pEvidence1 ~= nil) and (pEvidence2 ~= nil) and (pEvidence3 ~= nil) and (pEvidence4 ~= nil) and (pEvidence5 ~= nil) then
					return convoTemplate:getScreen("heff_start")
				end
			end
		end
	end
	
	return convoTemplate:getScreen("heff_bye")
end

function CaptainHeffConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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