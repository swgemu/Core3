trialsPadawanArchitect02ConvoHandler = conv_handler:new {}

function trialsPadawanArchitect02ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local state = CreatureObject(pPlayer):getScreenPlayState("JediPadawanTrialArchitechScreenPlay")
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(2, "JediPadawanTrialArchitectScreenPlay") == 1) then
		return convoTemplate:getScreen("intro")
	else
		return convoTemplate:getScreen("noquest_player_talk")
	end

end

function trialsPadawanArchitect02ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "nice_away") then
		CreatureObject(pPlayer):setScreenPlayState(4, "JediPadawanTrialArchitectScreenPlay")
		createEvent(60 * 1000, "JediPadawanTrialArchitectScreenPlay", "despawnNPC02", pNpc)
		CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_return_to_npc") -- Return to the person who gave you your trial task.
	elseif (screenID == "initiate_attack_fail") then
		JediPadawanTrial:failCurrentTrial(pPlayer)
		createEvent(10 * 1000, "JediPadawanTrialArchitectScreenPlay", "despawnNPC02", pNpc)
	end

	return pConvScreen
end
