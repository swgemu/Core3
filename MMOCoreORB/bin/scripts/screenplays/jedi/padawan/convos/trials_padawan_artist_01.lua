trialsPadawanArtist01ConvoHandler = conv_handler:new {}

function trialsPadawanArtist01ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, "JediPadawanTrialArtistScreenPlay") == 1) then
		return convoTemplate:getScreen("intro")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "JediPadawanTrialArtistScreenPlay") == 0) then
		return convoTemplate:getScreen("noquest_player_talks")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(2, "JediPadawanTrialArtistScreenPlay") == 1) then
		return convoTemplate:getScreen("back_not_done")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(4, "JediPadawanTrialArtistScreenPlay") == 1) then
		return convoTemplate:getScreen("back_done")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(8, "JediPadawanTrialArtistScreenPlay") == 1) then
		return convoTemplate:getScreen("helped_success")
	end

end

function trialsPadawanArtist01ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "choose_hate") then
		JediPadawanTrial:failCurrentTrial(pPlayer)
	elseif (screenID == "helped_but_too" or screenID == "helped_success") then
		JediPadawanTrial:passCurrentTrial(pPlayer, pNpc, 1)
	elseif (screenID == "choose_help_too") then
		CreatureObject(pPlayer):setScreenPlayState(2, "JediPadawanTrialArtistScreenPlay")
		JediPadawanTrialArtistScreenPlay:startPart2(pPlayer)
	end

	return pConvScreen
end
