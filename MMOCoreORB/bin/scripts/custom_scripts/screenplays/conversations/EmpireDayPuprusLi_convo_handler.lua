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

empiredayPuprusLi_convo_handler = conv_handler:new {}

function empiredayPuprusLi_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (screenID == "Response_01" or screenID == "Response_02")then
		if pGhost ~= nil then
			local empiredayImpWpID_6 = PlayerObject(pGhost):addWaypoint("naboo", "Speak with Captain Alrez-Rin", "Speak with Captain Alrez-Rin", -1198.0,-3560, WAYPOINT_COLOR_PURPLE, true, true, 0)

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

function empiredayPuprusLi_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	if empiredayImpStatus == "6" then
		return convoTemplate:getScreen("Response_Accepted")
	elseif (empiredayImpStatus == "1" or empiredayImpStatus == "2" or empiredayImpStatus == "3" or empiredayImpStatus == "4" or empiredayImpStatus == "5" or empiredayImpStatus == "6" or empiredayImpStatus == "7" or empiredayImpStatus == "8") then
		return convoTemplate:getScreen("Response_Dismiss")
	end

	return convoTemplate:getScreen("InitialConvo")

end