padawan_bad_cat_01_conv_handler = conv_handler:new {}

function padawan_bad_cat_01_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	local giverTrialNum = JediTrials:getTrialNumByName(pPlayer, "bad_cat")
	local trialState = JediTrials:getTrialStateName(pPlayer, giverTrialNum)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, trialState)) then
		return convoTemplate:getScreen("quest_completed")
	elseif (readData(playerID .. ":JediTrials:killedTarget") == 1) then
		return convoTemplate:getScreen("intro_target_killed")
	elseif (readData(playerID .. ":JediTrials:acceptedTask") == 1) then
		return convoTemplate:getScreen("intro_in_progress")
	else
		return convoTemplate:getScreen("intro")
	end
end

function padawan_bad_cat_01_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "oh_dear" or screenID == "dont_know_what_to_do") then
		PadawanTrials:failTrial(pPlayer)
	elseif (screenID == "glad_its_over") then
		PadawanTrials:passTrial(pPlayer)
	elseif (screenID == "last_location" or screenID == "uploaded_coordinates") then
		writeData(playerID .. ":JediTrials:acceptedTask", 1)
		writeData(SceneObject(pNpc):getObjectID() .. ":destroyNpcOnExit", 1)
		PadawanTrials:createSecondLocation(pPlayer)
	end

	return pConvScreen
end
