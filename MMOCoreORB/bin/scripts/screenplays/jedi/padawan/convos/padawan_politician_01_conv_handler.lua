padawan_politician_01_conv_handler = conv_handler:new {}

function padawan_politician_01_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	local giverTrialNum = JediTrials:getTrialNumByName(pPlayer, "politician")
	local trialState = JediTrials:getTrialStateName(pPlayer, giverTrialNum)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, trialState)) then
		return convoTemplate:getScreen("quest_completed")
	elseif (readData(playerID .. ":JediTrials:killedTarget") == 1) then
		return convoTemplate:getScreen("intro_killed_target")
	elseif (readData(playerID .. ":JediTrials:acceptedTask") == 1) then
		return convoTemplate:getScreen("intro_in_progress")
	else
		return convoTemplate:getScreen("intro")
	end
end

function padawan_politician_01_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "real_shame") then
		PadawanTrials:failTrial(pPlayer)
	elseif (screenID == "thank_you") then
		PadawanTrials:passTrial(pPlayer)
	elseif (screenID == "uploaded_waypoint") then
		writeData(playerID .. ":JediTrials:acceptedTask", 1)
		writeData(SceneObject(pNpc):getObjectID() .. ":destroyNpcOnExit", 1)
		PadawanTrials:createTargetLocation(pPlayer)
	end

	return pConvScreen
end
