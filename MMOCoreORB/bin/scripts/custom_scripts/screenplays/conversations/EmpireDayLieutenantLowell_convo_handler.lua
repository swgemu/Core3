local ObjectManager = require("managers.object.object_manager")

--[[ empiredayReb Screenplay Status
0 - Not spoken with Lowell
1 - Accepted to speak with Scarface
2 - Spoken with Scarface and accepted to speak with Edwards
3 - Spoken with Edwards and accepted to speak with Zuvord
4 - Spoken with Zuvord and accepted to speak with Lowell
5 - Spoken again with Lowell and accepted to speak with Caretaker
6 - Turned in Quest for rewards from Caretaker

Helper Status
1 - rebel
2 - imperial
]]

EmpireDayLieutenantLowell_convo_handler = conv_handler:new {}

function EmpireDayLieutenantLowell_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if screenID == "Response_Accepted" then
		if pGhost ~= nil then
			local empiredayRebWpID_1 = PlayerObject(pGhost):addWaypoint("dantooine", "Speak with and assist Master Seargent Scarface", "Speak with and assist Master Seargent Scarface", -6634, 5522, WAYPOINT_COLOR_PURPLE, true, true, 0)

			EmpireDay:setQuestStatus(pPlayer, ":empiredayRebStatus", 1)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayHelper", 1)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayRebWpID_1", empiredayRebWpID_1)
		end
	end

	if screenID == "TurninResponse_Accepted" then
		if pGhost ~= nil then
			local empiredayRebWpID_5 = PlayerObject(pGhost):addWaypoint("naboo", "Speak with this mysterious caretaker", "Speak with this mysterious caretaker", 4138, 3211, WAYPOINT_COLOR_PURPLE, true, true, 0)

			EmpireDay:setQuestStatus(pPlayer, ":empiredayRebStatus", 5)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayRebWpID_5", empiredayRebWpID_5)

			local playerID = SceneObject(pPlayer):getObjectID()
			local wpID_4 = getQuestStatus(playerID .. ":empiredayRebWpID_4")

			if wpID_4 ~= nil then
				PlayerObject(pGhost):removeWaypoint(wpID_4, true)
				removeQuestStatus(playerID .. ":empiredayRebWpID_4")
			end
		end
	end
	return pConvScreen
end

function EmpireDayLieutenantLowell_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (pPlayer == nil) then
		return
	end

	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerID = SceneObject(pPlayer):getObjectID()
	local empiredayRebStatus = tonumber(getQuestStatus(playerID .. ":empiredayRebStatus"))
	local empiredayHelperStatus = getQuestStatus(playerID .. ":empiredayHelper")

	if (empiredayRebStatus == nil) then
		empiredayRebStatus = 0
	end

	if (playerFaction == FACTIONIMPERIAL or empiredayHelperStatus == 2) then
		return convoTemplate:getScreen("Deny_Faction")
	end

	printf(" rebel status = " .. empiredayRebStatus .. "\n")

	if empiredayRebStatus == 4 then
		return convoTemplate:getScreen("TurnInConvo")
	elseif empiredayRebStatus >= 5 then
		return convoTemplate:getScreen("TurninResponse_Dismiss")
	elseif tonumber(empiredayRebStatus) > 0 then
		return convoTemplate:getScreen("Response_Dismiss")
	end

	return convoTemplate:getScreen("InitialConvo")
end