local ObjectManager = require("managers.object.object_manager")

--[[ empireday imperial Screenplay Status
0 - Not spoken with TK626
1 - Accepted to speak with Carkor
2 - Spoken with Carkor and accepted to hunt down Peety
3 - Dealt with Peety
4 - Accepted from Carkor to speak with Aldric
5 - Spoken with Aldric and accepted to hunt down Puprus
6 - Dealt with Puprus
7 - Accepted to speak with Alrez-Rin
8 - Turned in Quest for rewards from Alrez-Rin

Helper Status
1 - rebel
2 - imperial
]]

EmpireDayPeetyJoe_convo_handler = conv_handler:new {}

function EmpireDayPeetyJoe_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if screenID == "Response_Accepted" then
		if pGhost ~= nil then
			local empiredayImpWpID_3 = PlayerObject(pGhost):addWaypoint("tatooine", "Return to Captain Carkor", "Return to Captain Carkor", -1198.0,-3560, WAYPOINT_COLOR_PURPLE, true, true, 0)

			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpStatus", 3)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpWpID_3", empiredayImpWpID_3)

			local playerID = SceneObject(pPlayer):getObjectID()
			local wpID_2 = getQuestStatus(playerID .. ":empiredayImpWpID_2")

			if wpID_2 ~= nil then
				PlayerObject(pGhost):removeWaypoint(wpID_2, true)
				removeQuestStatus(playerID .. ":empiredayImpWpID_2")
			end
		end
	end

	if screenID == "Response_Agressive" then
		if pGhost ~= nil then
			local empiredayImpWpID_3 = PlayerObject(pGhost):addWaypoint("tatooine", "Return to Captain Carkor", "Return to Captain Carkor", -1198.0,-3560, WAYPOINT_COLOR_PURPLE, true, true, 0)

			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpStatus", 3)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpWpID_3", empiredayImpWpID_3)

			CreatureObject(pNpc):setPvpStatusBitmask(4)
			AiAgent(pNpc):setDefender(pPlayer)

			local playerID = SceneObject(pPlayer):getObjectID()
			local wpID_2 = getQuestStatus(playerID .. ":empiredayImpWpID_2")

			if wpID_2 ~= nil then
				PlayerObject(pGhost):removeWaypoint(wpID_2, true)
				removeQuestStatus(playerID .. ":empiredayImpWpID_2")
			end
		end
	end
	return pConvScreen
end

function EmpireDayPeetyJoe_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (pPlayer == nil) then
		return
	end

	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerID = SceneObject(pPlayer):getObjectID()
	local empiredayImpStatus = tonumber(getQuestStatus(playerID .. ":empiredayImpStatus"))
	local empiredayHelperStatus = getQuestStatus(playerID .. ":empiredayHelper")

	if (empiredayImpStatus == nil) then
		empiredayImpStatus = 0
	end

	if (playerFaction == FACTIONREBEL or empiredayHelperStatus == "1") then
		return convoTemplate:getScreen("Deny_Faction")
	end

	if empiredayImpStatus >= 3 then
		return convoTemplate:getScreen("Response_Dismiss")
	end

	return convoTemplate:getScreen("InitialConvo")
end