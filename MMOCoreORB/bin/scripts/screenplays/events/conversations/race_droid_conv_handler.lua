raceDroidConvoHandler = conv_handler:new {}

function raceDroidConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (readData(SceneObject(pPlayer):getObjectID() .. ":eventPerkRace:currentlyRacing") == 1) then
		return convoTemplate:getScreen("intro_current_racer")
	else
		return convoTemplate:getScreen("intro")
	end
end

function raceDroidConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "start_race") then
		raceDroidEventPerk:startRace(pNpc, pPlayer)
	elseif (screenID == "displaying_data") then
		raceDroidEventPerk:displayLeader(pNpc, pPlayer)
	elseif (screenID == "as_you_wish") then
		raceDroidEventPerk:doCleanup(pPlayer)
	end

	return pConvScreen
end
