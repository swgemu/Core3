trialsPadawanArtist01ConvoHandler = conv_handler:new {}

function trialsPadawanArtist01ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(8, "JediPadawanTrialArtistScreenPlay")) then
		return convoTemplate:getScreen("helped_success")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(4, "JediPadawanTrialArtistScreenPlay")) then
		return convoTemplate:getScreen("back_done")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(2, "JediPadawanTrialArtistScreenPlay")) then
		return convoTemplate:getScreen("back_not_done")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "JediPadawanTrialArtistScreenPlay")) then
		return convoTemplate:getScreen("intro")
	else
		return convoTemplate:getScreen("noquest_player_talks")
	end

end

function trialsPadawanArtist01ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "choose_hate") then
		JediPadawanTrialArtistScreenPlay:failCurrentTrial(pPlayer)
	elseif (screenID == "helped_but_too" or screenID == "helped_success") then
		JediPadawanTrialArtistScreenPlay:passCurrentTrial(pPlayer)
	elseif (screenID == "choose_help_too") then
		CreatureObject(pPlayer):setScreenPlayState(2, "JediPadawanTrialArtistScreenPlay")
		JediPadawanTrialArtistScreenPlay:startPart2(pPlayer)
	end

	return pConvScreen
end
