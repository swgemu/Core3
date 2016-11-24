trialsPadawanArtist02ConvoHandler = conv_handler:new {}

function trialsPadawanArtist02ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(2, "JediPadawanTrialArtistScreenPlay")) then
		return convoTemplate:getScreen("intro")
	else
		return convoTemplate:getScreen("no_quest")
	end

end

function trialsPadawanArtist02ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (screenID == "continued_final") then
		CreatureObject(pPlayer):setScreenPlayState(4, "JediPadawanTrialArtistScreenPlay")
		createEvent(60 * 1000, "JediPadawanTrialArtistScreenPlay", "despawnNPC02", pNpc)
		CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_return_to_npc") -- Return to the person who gave you your trial task.
		if (pGhost ~= nil) then
			-- {"naboo", "sathme_forr", 4983, 78, 6634, 240}
			PlayerObject(pGhost):addWaypoint("naboo", "Jedi Trials", "@jedi_trials:padawan_trials_return_to_npc", 4983, 6634, WAYPOINT_COLOR_BLUE, true, true, WAYPOINTQUESTTASK)
		end
	end

	return pConvScreen
end
