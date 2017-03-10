padawan_the_ring_02_conv_handler = conv_handler:new {}

function padawan_the_ring_02_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	return convoTemplate:getScreen("intro")
end

function padawan_the_ring_02_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "good_choice") then
		writeData(playerID .. ":JediTrials:spokeToTarget01", 1)
		CreatureObject(pNpc):setPvpStatusBitmask(0)
		CreatureObject(pNpc):setOptionsBitmask(0)
		PadawanTrials:createMainLocation(pPlayer)
		writeData(SceneObject(pNpc):getObjectID() .. ":destroyNpcOnExit", 1)
	elseif (screenID == "we_will_see") then
		PadawanTrials:removeNpcDestroyActiveArea(pPlayer)
		CreatureObject(pNpc):engageCombat(pPlayer)
	end

	return pConvScreen
end