padawan_old_musician_03_conv_handler = conv_handler:new {}

function padawan_old_musician_03_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not JediTrials:isOnPadawanTrials(pPlayer)) then
		return convoTemplate:getScreen("not_on_quest")
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local trialData = padawanTrialQuests[trialNumber]

	if (trialData == nil or trialData.trialName ~= "old_musician" or readData(playerID .. ":JediTrials:spokeToTarget02") == 1 or readData(playerID .. ":JediTrials:spokeToTarget01") ~= 1) then
		return convoTemplate:getScreen("not_on_quest")
	end

	return convoTemplate:getScreen("intro")
end

function padawan_old_musician_03_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "gave_ring") then
		writeData(playerID .. ":JediTrials:spokeToTarget02", 1)
		PadawanTrials:createMainLocation(pPlayer)
	end

	return pConvScreen
end
