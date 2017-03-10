padawan_artist_02_conv_handler = conv_handler:new {}

function padawan_artist_02_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local trialOwnerID = readData(SceneObject(pNpc):getObjectID() .. ":ownerID")
	local playerID = SceneObject(pPlayer):getObjectID()

	if (trialOwnerID ~= playerID or readData(playerID .. ":JediTrials:spokeToTarget01") == 1) then
		return convoTemplate:getScreen("no_active_quest")
	end

	return convoTemplate:getScreen("intro")
end

function padawan_artist_02_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "okay_thanks") then
		writeData(playerID .. ":JediTrials:spokeToTarget01", 1)
		PadawanTrials:createMainLocation(pPlayer)
		writeData(SceneObject(pNpc):getObjectID() .. ":destroyNpcOnExit", 1)
	end

	return pConvScreen
end
