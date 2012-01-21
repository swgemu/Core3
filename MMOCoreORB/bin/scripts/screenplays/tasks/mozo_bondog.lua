mozo_bondog_handler = Object:new {
}

function mozo_bondog_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption, conversingNPC)
	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
		
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	--printf("last conv screen " .. lastConversationScreen .. "\n")
	
	if (lastConversationScreen ~= nil) then	
		--Get the linked screen for the selected option.
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		--printf("optionLink " .. optionLink .. "\n")
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if (nextConversationScreen == nil) then
			printf("nextConversationScreen nill for option link = " .. optionLink .. "\n")
		end
	else
		nextConversationScreen = self:getInitialScreen(conversingPlayer, conversingNPC, conversationTemplate)
	end
	
	return nextConversationScreen
end

function mozo_bondog_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	
	local screenID = screen:getScreenID()

	printf("Screen ID: " .. screenID .. "\n")
	printf("Selected option: " .. selectedOption .. "\n")
	
	local player = LuaCreatureObject(conversingPlayer)
	local playerObjectPointer = player:getPlayerObject()
	
	if (screenID == "npc_2_1") then
		self:beginEscortQuest(player)
	elseif (screenID == "npc_reset") then
		self:resetQuest(player)
	end
	
	return conversationScreen
end

function mozo_bondog_handler:beginEscortQuest(player)
	local playerObjectPointer = player:getPlayerObject()
	local playerObject = LuaPlayerObject(playerObjectPointer)
	
	playerObject:addWaypoint("dathomir", 500, 500, 1)
end

function mozo_bondog_handler:resetQuest(player)
	player:removeScreenPlayState(1, "mozo_bondog")
end

function mozo_bondog_handler:getInitialScreen(play, npc, conversationTemplate)
	local convoTemplate = LuaConversationTemplate(conversationTemplate)
	local conversingPlayer = LuaCreatureObject(play)
	local faction = conversingPlayer:getFaction()
	local playerObjectPointer = conversingPlayer:getPlayerObject()
	
	if (playerObjectPointer == nil) then
		return nil
	end
	
	local playerObject = LuaPlayerObject(playerObjectPointer)
	
	if (conversingPlayer:hasScreenPlayState(1, "mozo_bondog") == 1) then
		return convoTemplate:getScreen("npc_work_1")
	end
	
	--Check if they are Imperial
	if (faction ~= 3679112276) then
		local val = math.random(2)
		
		if (val == 1) then
			return convoTemplate:getScreen("dontknowyou_1")
		else
			return convoTemplate:getScreen("dontknowyou_3")
		end
	end
	
	return convoTemplate:getScreen("npc_1_1")
end