padawan_pannaqa_01_conv_handler = conv_handler:new {}

function padawan_pannaqa_01_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not JediTrials:isOnPadawanTrials(pPlayer)) then
		return convoTemplate:getScreen("not_on_quest")
	end

	local giverTrialNum = JediTrials:getTrialNumByName(pPlayer, "pannaqa")
	local trialState = JediTrials:getTrialStateName(pPlayer, giverTrialNum)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, trialState)) then
		return convoTemplate:getScreen("completed_quest")
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	local trialData = padawanTrialQuests[trialNumber]

	if (trialData.trialName ~= "pannaqa") then
		return convoTemplate:getScreen("not_on_quest")
	end

	if (readData(playerID .. ":JediTrials:spokeToTarget02") == 1) then
		return convoTemplate:getScreen("intro_spoke_to_second_npc")
	elseif (readData(playerID .. ":JediTrials:spokeToTarget01") == 1) then
		return convoTemplate:getScreen("intro_spoke_to_first_npc")
	elseif (readData(playerID .. ":JediTrials:acceptedTask") == 1) then
		return convoTemplate:getScreen("intro_in_progress")
	else
		return convoTemplate:getScreen("intro")
	end

end

function padawan_pannaqa_01_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "sorry_for_bothering" or screenID == "find_your_way") then
		PadawanTrials:failTrial(pPlayer)
	elseif (screenID == "gardens_in_shape") then
		PadawanTrials:passTrial(pPlayer)
	elseif (screenID == "ill_be_here") then
		writeData(playerID .. ":JediTrials:acceptedTask", 1)
		PadawanTrials:createTargetLocation(pPlayer)
	end

	return pConvScreen
end
