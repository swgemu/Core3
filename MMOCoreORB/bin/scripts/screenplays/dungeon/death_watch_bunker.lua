DWB = ScreenPlay:new {
	numberOfActs = 1
}

registerScreenPlay("DWB", false);

-- Lutin Nightstalker: Rebel Sidequest
lutin_nightstalker_handler = {  }
 
function lutin_nightstalker_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
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
		
		if (nextLuaConversationScreen:getScreenID() == "excellent" or nextLuaConversationScreen:getScreenID() == "location" or (nextLuaConversationScreen:getScreenID() == "maytheforce" and luaLastConversationScreen:getScreenID() == "convoscreen4")) then
			creature:setScreenPlayState(1, "death_watch_bunker_rebel_sidequest")--gain entry permission
		elseif (nextLuaConversationScreen:getScreenID() == "quit") then
			creature:removeScreenPlayState(1, "death_watch_bunker_rebel_sidequest")
		end
		
	else
		
		finished_quest = creature:hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
		spoken_to_lutin = creature:hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest")

		-- NEED TO FIGURE OUT WHAT KIND OF QUESTS BLOCK EACH OTHER
		--busy = readScreenPlayData(conversingPlayer, "global", "occupied")
		--if busy ~= "death_watch_bunker_rebel_sidequest" and busy ~= "" then
		--	busy = 1
		--else
		--	busy = 0
		--end 

		factionmatch = 0

		local playerObjectPointer = creature:getPlayerObject()
		
		if (playerObjectPointer ~= nil) then
			local playerObject = LuaPlayerObject(playerObjectPointer)
			if (not playerObject:isOnLeave() and creature:isRebel()) then
				factionmatch = 1
			end
		end  
				
		if (finished_quest == 1) then
			nextConversationScreen = conversation:getScreen("return_sucessful")
		elseif (spoken_to_lutin == 1) then
			nextConversationScreen = conversation:getScreen("return_unsucessful")
		--elseif (busy == 1) then
		--	nextConversationScreen = conversation:getScreen("busy")
		elseif (factionmatch == 0) then
			nextConversationScreen = conversation:getScreen("notaligned")
		else
			nextConversationScreen = conversation:getInitialScreen()
		end
	end
	return nextConversationScreen

end

function lutin_nightstalker_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

-- Boba Fett
boba_fett_handler = {  }
 
function boba_fett_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
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
		
		if (nextLuaConversationScreen:getScreenID() == "convoscreen4" or nextLuaConversationScreen:getScreenID() == "convoscreen5") then
			creature:setScreenPlayState(1, "death_watch_bunker")--gain entry permission
		end
	else
		
		jabba_themepark_completed = creature:hasScreenPlayState(1024, "themepark_jabba")
		spoken_to_boba = creature:hasScreenPlayState(1, "death_watch_bunker")
				
		if (jabba_themepark_completed == 0) then
			nextConversationScreen = conversation:getScreen("convoscreen8")
		elseif (spoken_to_boba == 1) then
			nextConversationScreen = conversation:getScreen("convoscreen6")
		else
			nextConversationScreen = conversation:getInitialScreen()
		end
	end
	return nextConversationScreen

end

function boba_fett_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function DWB:start(creatureObject)	
	printf("Initiating Death Watch Bunker\n")
	
	local bunker = getSceneObject(5996314)
	
	if bunker == nil then
		printf("[Death Watch Bunker] Could not initialize. Zone not loaded?\n")
		return 0
	end

	local bunkerObject = LuaBuildingObject(bunker)
	
	createObserver(ENTEREDBUILDING, "DWB", "onEnterDWB", bunker)
end

function DWB:onEnterDWB(sceneObject, creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	printf("entered dwb\n")
	
	return 1
end