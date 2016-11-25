BiogenicHeraldDealerConvoHandler = conv_handler:new {}

function BiogenicHeraldDealerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if CreatureObject(pPlayer):hasScreenPlayState(1, "BiogenicHeraldDealer") then
		return convoTemplate:getScreen("intro_back")
	end

	return convoTemplate:getScreen("intro")
end

function BiogenicHeraldDealerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if screenID == "here_is_loc" or screenID == "dont_believe" then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			local pWaypoint = PlayerObject(pGhost):getWaypointAt(-6488, -417, "yavin4")

			if pWaypoint ~= nil then
				local waypoint = LuaWaypointObject(pWaypoint)

				if not waypoint:isActive() then
					waypoint:setActive(1)
					PlayerObject(pGhost):updateWaypoint(SceneObject(pWaypoint):getObjectID())
				end
			else
				PlayerObject(pGhost):addWaypoint("yavin4", "Mysterious Cave", "", -6488, -417, WAYPOINTBLUE, true, true, 0)
			end

			CreatureObject(pPlayer):setScreenPlayState(1, "BiogenicHeraldDealer")
		end
	elseif screenID == "what_you_have" then
		--TODO: send relic purchase sui
	end

	return pConvScreen
end
