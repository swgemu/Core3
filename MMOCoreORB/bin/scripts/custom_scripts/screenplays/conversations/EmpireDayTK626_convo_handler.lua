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

EmpireDayTK626_convo_handler = conv_handler:new {}

function EmpireDayTK626_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if screenID == "Response_Accepted" then
		if pGhost ~= nil then
			local empiredayImpWpID_1 = PlayerObject(pGhost):addWaypoint("tatooine", "Speak with Captain Carkor", "Speak with Captain Carkor", -1198.0,-3560, WAYPOINT_COLOR_PURPLE, true, true, 0)

			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpStatus", 1)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayHelper", 2)
			EmpireDay:setQuestStatus(pPlayer, ":empiredayImpWpID_1", empiredayImpWpID_1)
		end
	elseif screenID == "Response_Declined" then
		if pGhost ~= nil then
			return convoTemplate:getScreen("Response_Refused")
		end
	end
	return pConvScreen
end

function EmpireDayTK626_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerID = SceneObject(pPlayer):getObjectID()
	local empiredayImpStatus = getQuestStatus(playerID .. ":empiredayImpStatus")
	local empiredayHelperStatus = getQuestStatus(playerID .. ":empiredayHelper")

	if (empiredayImpStatus == nil) then
		empiredayImpStatus = "0"
	end

	if (playerFaction == FACTIONREBEL or empiredayHelperStatus == "1") then
		return convoTemplate:getScreen("Deny_Faction")
	end

	if empiredayImpStatus == "0" then
		return convoTemplate:getScreen("InitialConvo")
	elseif empiredayImpStatus == "1" then
		return convoTemplate:getScreen("Response_Accepted")
	else
		return convoTemplate:getScreen("Service_Noted")
	end
end