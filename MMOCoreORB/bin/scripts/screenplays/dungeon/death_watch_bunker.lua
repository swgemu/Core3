DWB = ScreenPlay:new {
	numberOfActs = 1
}

registerScreenPlay("DWB", true);

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
		return
	end
	
	local bunkerObject = LuaBuildingObject(bunker)
	
	createObserver(ENTEREDBUILDING, "DWB", "onEnterDWB", bunker)
end

function DWB:onEnterDWB(sceneObject, creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	printf("entered dwb\n")
end