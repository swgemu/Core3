local JunkDealer = require("screenplays.junk_dealer.junk_dealer")

BiogenicHeraldDealerConvoHandler = conv_handler:new {}

function BiogenicHeraldDealerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		local pWaypoint = PlayerObject(pGhost):getWaypointAt(-6488, -417, "yavin4")

		if pWaypoint ~= nil then
			return convoTemplate:getScreen("intro_back")
		end
	end

	return convoTemplate:getScreen("intro")
end

function BiogenicHeraldDealerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

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
		end
	elseif screenID == "knew_it" then
		local junkList = JunkDealer:getEligibleJunk(pPlayer, "geo")

		if #junkList > 0 then
			clonedScreen:addOption("@conversation/biogenic_herald_dealer:s_52beeae8", "what_you_have") -- Yes, I have a few things you might be interested in.
		end

		clonedScreen:addOption("@conversation/biogenic_herald_dealer:s_2b7c5c5a", "thanks_for_checking") -- No, I don't have anything, sorry.
	elseif screenID == "what_you_have" then
		writeStringData(SceneObject(pPlayer):getObjectID() .. ":junkDealerType", "geo")
		JunkDealer:sendSellJunkSelection(pPlayer, pNpc, "geo")
	end

	return pConvScreen
end
