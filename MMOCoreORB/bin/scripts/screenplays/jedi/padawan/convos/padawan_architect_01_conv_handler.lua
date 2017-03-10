padawan_architect_01_conv_handler = conv_handler:new {}

function padawan_architect_01_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local trialOwnerID = readData(SceneObject(pNpc):getObjectID() .. ":ownerID")
	local playerID = SceneObject(pPlayer):getObjectID()

	if (trialOwnerID ~= playerID) then
		return convoTemplate:getScreen("not_quest_owner")
	end

	if (not JediTrials:isOnPadawanTrials(pPlayer)) then
		writeData(SceneObject(pNpc):getObjectID() .. ":destroyNpcOnExit", 1)
		return convoTemplate:getScreen("not_quest_owner")
	end

	local giverTrialNum = JediTrials:getTrialNumByName(pPlayer, "architect")
	local trialState = JediTrials:getTrialStateName(pPlayer, giverTrialNum)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, trialState)) then
		return convoTemplate:getScreen("completed_quest")
	elseif (readData(playerID .. ":JediTrials:acceptedTask") == 1) then
		return convoTemplate:getScreen("done_with_task")
	else
		return convoTemplate:getScreen("intro")
	end

end

function padawan_architect_01_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "done_with_task") then
		if (readData(playerID .. ":JediTrials:killedTarget") == 1) then
			clonedConversation:addOption("@conversation/padawan_architect_01:s_f0d9878f", "yes_kill_fail")
		elseif (readData(playerID .. ":JediTrials:spokeToTarget01") == 1) then
			clonedConversation:addOption("@conversation/padawan_architect_01:s_88ac3394", "back_chose_success")
		else
			clonedConversation:setStopConversation(true)
		end
	elseif (screenID == "yes_kill_fail" or screenID == "no_decline") then
		PadawanTrials:failTrial(pPlayer)
	elseif (screenID == "back_chose_success") then
		PadawanTrials:passTrial(pPlayer)
	elseif (screenID == "yes_accept") then
		writeData(playerID .. ":JediTrials:acceptedTask", 1)
		writeData(SceneObject(pNpc):getObjectID() .. ":destroyNpcOnExit", 1)
		PadawanTrials:createTargetLocation(pPlayer)
	end

	return pConvScreen
end
