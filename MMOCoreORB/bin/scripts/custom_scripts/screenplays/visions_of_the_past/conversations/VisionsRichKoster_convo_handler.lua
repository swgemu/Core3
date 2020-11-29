local ObjectManager = require("managers.object.object_manager")

--[[ Visions Screenplay States
0 - Not spoken with Informant
1 - Accepted to speak with manager on Yavin
2 - Spoken with mannager of faction on yavin and accepted to find items

3 - Turned in Items for rewards

]]

VisionsRichKoster_convo_handler = conv_handler:new {}

function VisionsRichKoster_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (screenID == "Branch_Response_01" or screenID == "Branch_Response_02") then
		if pGhost ~= nil then
			local visionsWpID_1 = PlayerObject(pGhost):addWaypoint("yavin4", "ISB Officer", "ISB Officer", -6988, -5748, WAYPOINT_COLOR_PURPLE, true, true, 0)
			local playerID = SceneObject(pPlayer):getObjectID()

			writeData(playerID .. ":visionsState", 1)
			writeData(playerID .. ":visionsWpID_1:", visionsWpID_1)
			writeData(playerID .. ":visionsImperialHelper", 1)
		end
	end
	return pConvScreen
end

function VisionsRichKoster_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerFaction = CreatureObject(pPlayer):getFaction()
	local visionsState = readData(SceneObject(pPlayer):getObjectID() .. ":visionsState")

	if (visionsState == nil) then
		visionsState = 0
	end

	if (playerFaction == FACTIONREBEL) then
		return convoTemplate:getScreen("Deny_Faction")
	end

	if visionsState == 1 then
		return convoTemplate:getScreen("Response_Accepted")
	elseif (visionsState == 2 or visionsState == 3) then
		return convoTemplate:getScreen("Service_Noted")
	end

	return convoTemplate:getScreen("InitialConvo")
end
