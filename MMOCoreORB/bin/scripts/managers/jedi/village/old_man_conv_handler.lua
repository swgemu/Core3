OLD_MAN_CONVERSATION_ENDED_DESPAWN_TIME = 10 * 1000 -- 10 seconds

old_man_conv_handler = Object:new {
}
 
function old_man_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption)
	local creature = LuaCreatureObject(pConversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end

	local conversation = LuaConversationTemplate(pConversationTemplate)

	local nextConversationScreen

	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
		else
			nextConversationScreen = conversation:getScreen("init")
		end
	else
		nextConversationScreen = conversation:getScreen("init")
	end
	return nextConversationScreen
end

function old_man_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	
	local screenID = screen:getScreenID()

	if screenID == "init" then
		pConversationScreen = old_man_conv_handler.handleInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "village_give_crystal" or screenID == "village_another_time" or screenID == "village_another_time2" or screenID == "mellichae_later" then
		OldMan.scheduleDespawnOfOldMan(pConversingPlayer, OLD_MAN_CONVERSATION_ENDED_DESPAWN_TIME)
	end

	return pConversationScreen
end

function old_man_conv_handler.handleInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	local nextScreen = "not_you"

	if OldMan.oldManBelongsToThePlayer(pConversingPlayer, pConversingNpc) then
		if VillageJediManager.isGlowing(pConversingPlayer) then
			nextScreen = "village_intro"
		elseif VillageJediManager.readyForMellichae(pConversingPlayer) then
			nextScreen = "mellichae_intro"
		end
	end	

	return conversationTemplate:getScreen(nextScreen)
end
