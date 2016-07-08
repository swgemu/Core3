raceDroidConvoHandler = Object:new {}

function raceDroidConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (readData(SceneObject(pPlayer):getObjectID() .. ":eventPerkRace:currentlyRacing") == 1) then
		return convoTemplate:getScreen("intro_current_racer")
	else
		return convoTemplate:getScreen("intro")
	end
end

function raceDroidConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "start_race") then
		raceDroidEventPerk:startRace(conversingNPC, conversingPlayer)
	elseif (screenID == "displaying_data") then
		raceDroidEventPerk:displayLeader(conversingNPC, conversingPlayer)
	elseif (screenID == "as_you_wish") then
		raceDroidEventPerk:doCleanup(conversingPlayer)
	end

	return conversationScreen
end

function raceDroidConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()

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
