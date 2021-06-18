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
1 - Impel
2 - imperial
]]

EmpireDayCaptainCarkor_convo_handler = conv_handler:new {}

function EmpireDayCaptainCarkor_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)



	local screenID = screen:getScreenID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if screenID == "Response_Accepted" then
		if pGhost ~= nil then
			local empiredayImpWpID_2 = PlayerObject(pGhost):addWaypoint("tatooine", "Confront the suspected terrorist", "Confront the suspected terrorist", -1349,-4003, WAYPOINT_COLOR_PURPLE, true, true, 0)

			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpStatus", 2)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpWpID_2", empiredayImpWpID_2)

			local playerID = SceneObject(pPlayer):getObjectID()
			local wpID_1 = getQuestStatus(playerID .. ":empiredayImpWpID_1")

			if wpID_1 ~= nil then
				PlayerObject(pGhost):removeWaypoint(wpID_1, true)
				removeQuestStatus(playerID .. ":empiredayImpWpID_1")
			end
		end
	end

	if screenID == "Turnin_Accepted" then
		if pGhost ~= nil then
			local empiredayImpWpID_4 = PlayerObject(pGhost):addWaypoint("naboo", "Speak with General Aldric", "Speak with General Aldric", -5496, 4451, WAYPOINT_COLOR_PURPLE, true, true, 0)

			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpStatus", 4)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpWpID_4", empiredayImpWpID_4)

			local playerID = SceneObject(pPlayer):getObjectID()
 			local wpID_3 = getQuestStatus(playerID .. ":empiredayImpWpID_3")

			 if wpID_3 ~= nil then
				PlayerObject(pGhost):removeWaypoint(wpID_3, true)
				removeQuestStatus(playerID .. ":empiredayImpWpID_3")
			end
		end
	end
	return pConvScreen
end

function EmpireDayCaptainCarkor_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	if empiredayImpStatus == 2 then
		return convoTemplate:getScreen("Awaiting_Completion")
	elseif empiredayImpStatus == 3 then
		return convoTemplate:getScreen("TurnInConvo")
	elseif empiredayImpStatus >= 4 then
		return convoTemplate:getScreen("TurninResponse_Dismiss")
	end

	return convoTemplate:getScreen("InitialConvo")
end