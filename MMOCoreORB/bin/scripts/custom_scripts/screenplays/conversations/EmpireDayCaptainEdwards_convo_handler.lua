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

EmpireDayCaptainEdwards_convo_handler = conv_handler:new {}

function EmpireDayCaptainEdwards_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if screenID == "Response_Accepted" then
		if pGhost ~= nil then
			local empiredayRebWpID_3 = PlayerObject(pGhost):addWaypoint("naboo", "Speak to and Assist Corporal Zuvord", "Speak to and Assist Corporal Zuvord", 4955, -4704, WAYPOINT_COLOR_PURPLE, true, true, 0)

			EmpireDay:setQuestStatus(pPlayer, ":empiredayRebStatus", 3)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayRebWpID_3", empiredayRebWpID_3)

			local playerID = SceneObject(pPlayer):getObjectID()
			local wpID_2 = getQuestStatus(playerID .. ":empiredayRebWpID_2")

			if wpID_2 ~= nil then
				PlayerObject(pGhost):removeWaypoint(wpID_2, true)
				removeQuestStatus(playerID .. ":empiredayRebWpID_2")
			end
		end
	end
	return pConvScreen
end

function EmpireDayCaptainEdwards_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	if (playerFaction == FACTIONIMPERIAL or empiredayHelperStatus == "2") then
		return convoTemplate:getScreen("Deny_Faction")
	end

	if empiredayRebStatus < 2 then
		return convoTemplate:getScreen("Response_Dismiss")
	elseif empiredayRebStatus >= 3 then
		return convoTemplate:getScreen("Service_Noted")
	end

	return convoTemplate:getScreen("InitialConvo")
end