padawan_pannaqa_03_conv_handler = conv_handler:new {}

function padawan_pannaqa_03_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local trialOwnerID = readData(SceneObject(pNpc):getObjectID() .. ":ownerID")
	local playerID = SceneObject(pPlayer):getObjectID()

	if (trialOwnerID ~= playerID or readData(playerID .. ":JediTrials:spokeToTarget02") == 1) then
		return convoTemplate:getScreen("not_quest_owner")
	end

	if (not JediTrials:isOnPadawanTrials(pPlayer)) then
		writeData(SceneObject(pNpc):getObjectID() .. ":destroyNpcOnExit", 1)
		return convoTemplate:getScreen("not_quest_owner")
	end

	return convoTemplate:getScreen("intro")
end

function padawan_pannaqa_03_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "take_part_for_me" or screenID == "drinking_and_wandering") then
		writeData(playerID .. ":JediTrials:spokeToTarget02", 1)
		writeData(SceneObject(pNpc):getObjectID() .. ":destroyNpcOnExit", 1)
		PadawanTrials:createMainLocation(pPlayer)
	end

	return pConvScreen
end
