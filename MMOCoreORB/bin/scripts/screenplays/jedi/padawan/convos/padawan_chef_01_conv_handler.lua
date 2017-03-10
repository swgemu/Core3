padawan_chef_01_conv_handler = conv_handler:new {}

function padawan_chef_01_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	local giverTrialNum = JediTrials:getTrialNumByName(pPlayer, "chef")
	local trialState = JediTrials:getTrialStateName(pPlayer, giverTrialNum)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, trialState)) then
		return convoTemplate:getScreen("not_quest_owner")
	elseif (readData(playerID .. ":JediTrials:killedTarget") == 1) then
		return convoTemplate:getScreen("intro_killed_target")
	elseif (readData(playerID .. ":JediTrials:spokeToTarget01") == 1) then
		return convoTemplate:getScreen("intro_spoke_to_target")
	elseif (readData(playerID .. ":JediTrials:acceptedTask") == 1) then
		return convoTemplate:getScreen("intro_has_quest")
	else
		return convoTemplate:getScreen("intro")
	end

end

function padawan_chef_01_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "my_hero" or screenID == "just_cruel") then
		PadawanTrials:failTrial(pPlayer)
	elseif (screenID == "pay_next_time" or screenID == "want_my_revenge" or screenID == "my_sweet_revenge") then
		PadawanTrials:passTrial(pPlayer)
	elseif (screenID == "chased_thug") then
		writeData(playerID .. ":JediTrials:acceptedTask", 1)
		writeData(SceneObject(pNpc):getObjectID() .. ":destroyNpcOnExit", 1)
		PadawanTrials:createTargetLocation(pPlayer)
	end

	return pConvScreen
end
