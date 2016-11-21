trialsPadawanArtist02ConvoHandler = conv_handler:new {}

function trialsPadawanArtist02ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(2, "JediPadawanTrialArtistScreenPlay") == 1) then
		return convoTemplate:getScreen("intro")
	else
		return convoTemplate:getScreen("no_quest")
	end

end

function trialsPadawanArtist02ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "continued_final") then
		CreatureObject(pPlayer):setScreenPlayState(4, "JediPadawanTrialArtistScreenPlay")
		createEvent(60 * 1000, "JediPadawanTrialArtistScreenPlay", "despawnNPC02", pNpc)
		CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_return_to_npc") -- Return to the person who gave you your trial task.
	end

	return pConvScreen
end
