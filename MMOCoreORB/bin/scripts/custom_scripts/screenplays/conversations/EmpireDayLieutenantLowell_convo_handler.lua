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

empiredayLieutenantLowell_convo_handler = conv_handler:new {}

function empiredayLieutenantLowell_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (screenID == "Response_01" or "Response_02")then
		if pGhost ~= nil then
			local empiredayRebWpID_1 = PlayerObject(pGhost):addWaypoint("rori", "Speak with and assist Master Seargent Scarface", "Speak with and assist Master Seargent Scarface", -6634, 5522, WAYPOINT_COLOR_PURPLE, true, true, 0)

			EmpireDay:setQuestStatus(pPlayer, ":empiredayRebStatus", 1)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayHelper", 1)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayRebWpID_1", empiredayRebWpID_1)
		end
	    elseif (screenID == "Response_03")then
            if pGhost ~= nil then
                return convoTemplate:getScreen("Response_Refused")
        end
	end

    if (screenID == "TurninResponse_01" or "TurninResponse_02")then
        if pGhost ~= nil then
            local empiredRebWpID_5 = PlayerObject(pGhost):addWaypoint("naboo", "Speak with this mysterious caretaker", "Speak with this mysterious caretaker", -0,-0, WAYPOINT_COLOR_PURPLE, true, true, 0)

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

function empiredayLieutenantLowell_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerID = SceneObject(pPlayer):getObjectID()
	local empiredayRebStatus = getQuestStatus(playerID .. ":empiredayRebStatus")
	local empiredayHelperStatus = getQuestStatus(playerID .. ":empiredayHelper")

	if (empiredayRebStatus == nil) then
		empiredayRebStatus = "0"
	end

	if (playerFaction == FACTIONIMPERIAL or empiredayHelperStatus == "2") then
		return convoTemplate:getScreen("Deny_Faction")
	end

	if empiredayRebStatus == "1" then
		return convoTemplate:getScreen("Response_Accepted")
	elseif (empiredayRebStatus == "2" or empiredayRebStatus == "3" or empiredayRebStatus == "5" or empiredayRebStatus == "0") then
		return convoTemplate:getScreen("Response_Dismiss")
    elseif empiredayRebSatus == "6" then
        return convoTemplate:getScreen("TurninResponse_Dismiss")
	end
    if empiredayRebStatus == "4" then
        return convoTemplate:getScreen("TurnInConvo")
    end

	return convoTemplate:getScreen("InitialConvo")

end