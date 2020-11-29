local ObjectManager = require("managers.object.object_manager")

--[[ Visions Screenplay Status
0 - Not spoken with Informant
1 - Accepted to speak with manager on Yavin
2 - Spoken with mannager of faction on yavin and accepted to find items
3 - Turned in Items for rewards

Helper Status
1 - rebel
2 - imperial
]]

VisionsSheriRay_convo_handler = conv_handler:new {}

function VisionsSheriRay_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (screenID == "Response_01" or screenID == "Response_02") then
		if pGhost ~= nil then
			local visionsWpID_1 = PlayerObject(pGhost):addWaypoint("yavin4", "SpecForce Procurement Specialist", "SpecForce Procurement Specialist", -260, 4875, WAYPOINT_COLOR_PURPLE, true, true, 0)

			VisionsOfThePast:setQuestStatus(pPlayer, ":visionsStatus", 1)
			VisionsOfThePast:setQuestStatus(pPlayer, ":visionsHelper", 1)
			VisionsOfThePast:setQuestStatus(pPlayer, ":visionsWpID_1", visionsWpID_1)
		end
	end
	return pConvScreen
end

function VisionsSheriRay_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerID = SceneObject(pPlayer):getObjectID()
	local visionsStatus = getQuestStatus(playerID .. ":visionsStatus")
	local visionsHelperStatus = getQuestStatus(playerID .. ":visionsHelper")

	if (visionsStatus == nil) then
		visionsStatus = "0"
	end

	if (playerFaction == FACTIONIMPERIAL or visionsHelperStatus == "2") then
		return convoTemplate:getScreen("Deny_Faction")
	end

	if visionsStatus == "1" then
		return convoTemplate:getScreen("Response_Accepted")
	elseif (visionsStatus == "2" or visionsStatus == "3") then
		return convoTemplate:getScreen("Service_Noted")
	end
	return convoTemplate:getScreen("InitialConvo")
end
