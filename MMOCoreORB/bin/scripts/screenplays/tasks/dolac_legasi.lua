dolac_legasi_screenplay = ScreenPlay:new {
	numberOfActs = 1
}

registerScreenPlay("dolac_legasi_screenplay", true)

function dolac_legasi_screenplay:start()
	local loc = self:getEscapedPrisonerLocation()
	local activeAreaPointer = spawnSceneObject("dathomir", "object/active_area.iff", loc.x, loc.z, loc.y, 0, 0, 0, 0, 0)
	local activeArea = LuaActiveArea(activeAreaPointer)
	activeArea:setRadius(50)
	createObserver(ENTEREDAREA, "dolac_legasi_screenplay", "spawnEscapedPrisoner", activeAreaPointer)
end

function dolac_legasi_screenplay:getEscapedPrisonerLocation()
	return {x = -5866, z = 129, y = 809}
end

function dolac_legasi_screenplay:spawnEscapedPrisoner(sceneObjectPointer, longArg2)
	local sceneObject = LuaSceneObject(sceneObjectPointer)
	
	if (not sceneObject:isCreatureObject()) then
		return
	end
	
	local creatureObject = LuaCreatureObject(sceneObjectPointer)
	
	if (creatureObject:hasScreenPlayState(1, "dolac_legasi") == 1) then
		printf("creature has the state\n")
	end 
end

dolac_legasi_handler = Object:new {
}

function dolac_legasi_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption, conversingNPC)
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

function dolac_legasi_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	
	local screenID = screen:getScreenID()
	
	local player = LuaCreatureObject(conversingPlayer)
	local playerObjectPointer = player:getPlayerObject()
	
	if (screenID == "npc_2_1") then
		self:beginEscortQuest(player)
	elseif (screenID == "npc_reset") then
		self:resetQuest(player)
	end
	
	return conversationScreen
end

function dolac_legasi_handler:beginEscortQuest(player)
	local playerObjectPointer = player:getPlayerObject()
	local playerObject = LuaPlayerObject(playerObjectPointer)
	
	player:setScreenPlayState(1, "dolac_legasi")
	
	local loc = dolac_legasi_screenplay:getEscapedPrisonerLocation()
	playerObject:addWaypoint("dathomir", loc.x, loc.y, true)
end

function dolac_legasi_handler:resetQuest(player)
	player:removeScreenPlayState(1, "dolac_legasi")
end

function dolac_legasi_handler:getInitialScreen(play, npc, conversationTemplate)
	local convoTemplate = LuaConversationTemplate(conversationTemplate)
	local conversingPlayer = LuaCreatureObject(play)
	local faction = conversingPlayer:getFaction()
	local playerObjectPointer = conversingPlayer:getPlayerObject()
	
	if (playerObjectPointer == nil) then
		return nil
	end
	
	local playerObject = LuaPlayerObject(playerObjectPointer)
	
	if (conversingPlayer:hasScreenPlayState(1, "dolac_legasi") == 1) then
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