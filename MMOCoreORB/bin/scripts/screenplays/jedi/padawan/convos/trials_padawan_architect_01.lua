trialsPadawanArchitect01ConvoHandler = conv_handler:new {}

function trialsPadawanArchitect01ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(8, "JediPadawanTrialArchitectScreenPlay")) then
		return convoTemplate:getScreen("over_sour_success")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(4, "JediPadawanTrialArchitectScreenPlay")) then
		return convoTemplate:getScreen("done_with_task")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(2, "JediPadawanTrialArchitectScreenPlay")) then
		return convoTemplate:getScreen("not_yet_done")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "JediPadawanTrialArchitectScreenPlay")) then
		return convoTemplate:getScreen("intro")
	else
		return convoTemplate:getScreen("not_yet_done")
	end

end

function trialsPadawanArchitect01ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "done_with_task") then
		local killedGungan = readScreenPlayData(pPlayer, "JediPadawanTrial", "KilledGungan")

		if (killedGungan == 1) then
			clonedConversation:addOption("@conversation/padawan_architect_01:s_f0d9878f", "yes_kill_fail")
		else
			clonedConversation:addOption("@conversation/padawan_architect_01:s_88ac3394", "back_chose_success")
		end
	elseif (screenID == "yes_kill_fail" or screenID == "no_decline") then
		deleteScreenPlayData(pPlayer, "JediPadawanTrial", "KilledGungan")
		JediPadawanTrialArchitectScreenPlay:failCurrentTrial(pPlayer)
	elseif (screenID == "back_chose_success") then
		JediPadawanTrialArchitectScreenPlay:passCurrentTrial(pPlayer)
	elseif (screenID == "yes_accept") then
		JediPadawanTrialArchitectScreenPlay:startPart2(pPlayer)
	end

	return pConvScreen
end
