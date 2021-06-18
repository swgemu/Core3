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

EmpireDayPuprusLi_convo_handler = conv_handler:new {}

function EmpireDayPuprusLi_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if screenID == "Response_Accepted" then
		if pGhost ~= nil then
			local empiredayImpWpID_6 = PlayerObject(pGhost):addWaypoint("naboo", "Speak with General Aldric", "Speak with General Aldric", -5496.1, 4451.1, WAYPOINT_COLOR_PURPLE, true, true, 0)

			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpStatus", 6)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpWpID_6", empiredayImpWpID_6)

			CreatureObject(pNpc):setPvpStatusBitmask(4)
			AiAgent(pNpc):setDefender(pPlayer)

			local playerID = SceneObject(pPlayer):getObjectID()
			local wpID_5 = getQuestStatus(playerID .. ":empiredayImpWpID_5")

			if wpID_5 ~= nil then
				PlayerObject(pGhost):removeWaypoint(wpID_5, true)
				removeQuestStatus(playerID .. ":empiredayImpWpID_5")
			end
		end
	end
	return pConvScreen
end

function EmpireDayPuprusLi_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	if empiredayImpStatus < 5 then
		return convoTemplate:getScreen("Response_Dismiss")
	end

	return convoTemplate:getScreen("InitialConvo")
end