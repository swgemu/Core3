padawan_old_musician_02_conv_handler = conv_handler:new {}

function padawan_old_musician_02_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not JediTrials:isOnPadawanTrials(pPlayer)) then
		return convoTemplate:getScreen("not_on_quest")
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local trialData = padawanTrialQuests[trialNumber]

	if (trialData.trialName ~= "old_musician" or readData(playerID .. ":JediTrials:spokeToTarget01") == 1 or readData(playerID .. ":JediTrials:acceptedTask") ~= 1) then
		return convoTemplate:getScreen("not_on_quest")
	end

	return convoTemplate:getScreen("intro")
end

function padawan_old_musician_02_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "never_been_here" or screenID == "makes_any_difference" or screenID == "whatever_you_say") then
		PadawanTrials:failTrial(pPlayer)
	elseif (screenID == "moved_to_lok") then
		writeData(playerID .. ":JediTrials:spokeToTarget01", 1)
		PadawanTrials:createTargetLocation(pPlayer, true)
	end

	return pConvScreen
end
