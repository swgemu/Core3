-- Foreman Quest
death_watch_foreman_handler = {  }
 
function death_watch_foreman_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

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
		
	else
		
		--finished_quest = creature:hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
		--spoken_to_lutin = creature:hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest")
				
		--if (finished_quest == 1) then
		--	nextConversationScreen = conversation:getScreen("convoscreen2")
		--elseif (spoken_to_lutin == 1) then
			nextConversationScreen = conversation:getInitialScreen()
		--	creature:setScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
		--	creature:addCashCredits(487, true)
		--else
		--	nextConversationScreen = conversation:getScreen("convoscreen3")
		--end
	end
	return nextConversationScreen

end

function death_watch_foreman_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end


-- Rescue Scientist: Rebel Sidequest
death_watch_rescue_scientist_handler = {  }
 
function death_watch_rescue_scientist_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

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
		
	else
		
		finished_quest = creature:hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
		spoken_to_lutin = creature:hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest")
				
		if (finished_quest == 1) then
			nextConversationScreen = conversation:getScreen("convoscreen2")
		elseif (spoken_to_lutin == 1) then
			nextConversationScreen = conversation:getInitialScreen()
			creature:setScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
			creature:addCashCredits(487, true)
		else
			nextConversationScreen = conversation:getScreen("convoscreen3")
		end
	end
	return nextConversationScreen

end

function death_watch_rescue_scientist_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

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
			nextConversationScreen = conversation:getScreen("return_successful")
		elseif (spoken_to_lutin == 1) then
			nextConversationScreen = conversation:getScreen("return_unsuccessful")
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

-- Commander D'krn: Imperial Sidequest
commander_dkrn_handler = {  }
 
function commander_dkrn_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

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
		
		if (nextLuaConversationScreen:getScreenID() == "rightaway" or nextLuaConversationScreen:getScreenID() == "location") then
			creature:setScreenPlayState(1, "death_watch_bunker_imperial_sidequest")--gain entry permission
		elseif (nextLuaConversationScreen:getScreenID() == "quit") then
			creature:removeScreenPlayState(1, "death_watch_bunker_imperial_sidequest")
		end
		
	else
		
		finished_quest_before = creature:hasScreenPlayState(2, "death_watch_bunker_imperial_sidequest")
		spoken_to_dkrn = creature:hasScreenPlayState(1, "death_watch_bunker_imperial_sidequest")

		pSample = creature:getContainerObjectByTemplate("object/tangible/loot/dungeon/death_watch_bunker/blood_vial.iff")

		if (pSample ~= nil) then
			finished_quest = true
		else
			finished_quest = false
		end

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
			if (not playerObject:isOnLeave() and creature:isImperial()) then
				factionmatch = 1
			end
		end  
		
				
		if (finished_quest == true and finished_quest_before == 0) then
			nextConversationScreen = conversation:getScreen("return_successful")
			local sample = LuaSceneObject(pSample)
			sample:destroyObjectFromWorld()
			creature:setScreenPlayState(2, "death_watch_bunker_imperial_sidequest")
		elseif (finished_quest == true and finished_quest_before == 1) then
			nextConversationScreen = conversation:getScreen("more_samples")
		elseif (spoken_to_dkrn == 1) then
			nextConversationScreen = conversation:getScreen("return_unsuccessful")
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

function commander_dkrn_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
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
		
		--TESTING!! REMOVE THIS ONCE JABBA'S THEMEPARK IS IN!
		jabba_themepark_completed = 1
				
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