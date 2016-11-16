trialsPadawanArchitect01ConvoHandler = conv_handler:new {}

function trialsPadawanArchitect01ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, "JediPadawanTrialArchitectScreenPlay") == true) then
		return convoTemplate:getScreen("intro")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(2, "JediPadawanTrialArchitectScreenPlay") == true) then
		return convoTemplate:getScreen("not_yet_done")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(4, "JediPadawanTrialArchitectScreenPlay") == true) then
		return convoTemplate:getScreen("done_with_task")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(8, "JediPadawanTrialArchitectScreenPlay") == true) then
		return convoTemplate:getScreen("over_sour_success")
	end
end

function trialsPadawanArchitect01ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "yes_kill_fail" or screenID == "no_decline") then
		JediPadawanTrial:failCurrentTrial(pPlayer)
	elseif (screenID == "back_chose_success") then
		JediPadawanTrial:passCurrentTrial(pPlayer, pNpc, 1)
	elseif (screenID == "yes_accept") then
		CreatureObject(pConversingPlayer):setScreenPlayState(2, "JediPadawanTrialArchitectScreenPlay")
		JediPadawanTrialArchitectScreenPlay:startPart2(pPlayer)
	end

	return pConvScreen
end
