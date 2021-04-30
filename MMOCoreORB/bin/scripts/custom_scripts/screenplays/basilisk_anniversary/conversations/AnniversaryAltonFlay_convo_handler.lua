local ObjectManager = require("managers.object.object_manager")

--[[ Anniversary Screenplay Status
0 - Not spoken with the Grandmaster Baker
1 - Accepted to speak with Information Broker on Tatooine
2 - Spoken with Information on Tatooine and accepted to find thiefs
3 - Spoken with disaster of desserts and confronted him
4 - Turn in item to Grandmaster Baker
]]


AnniversaryAltonFlay_convo_handler = conv_handler:new {}

function AnniversaryAltonFlay_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (screenID == "Response_01" or screenID == "Response_02") then
		if pGhost ~= nil then

			local anniversaryWpID_3 = PlayerObject(pGhost):addWaypoint("naboo", "Return The Ingrediant", "Return The Ingrediant", -260, 4875, WAYPOINT_COLOR_PURPLE, true, true, 0)
            CreatureObject(pNpc):setPvpStatusBitmask(1)

			BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryStatus", 3)
			BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryWpID_3", anniversaryWpID_3)
		end
	end
	return pConvScreen
end

function AnniversaryAltonFlay_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerID = SceneObject(pPlayer):getObjectID()
	local anniversaryStatus = getQuestStatus(playerID .. ":anniversaryStatus")

	if (anniversaryStatus == nil) then
		anniversaryStatus = "0"
	end

	if anniversaryStatus == "3" then
		return convoTemplate:getScreen("Response_Accepted")
	elseif (anniversaryStatus == "1" or anniversaryStatus == "0") then
		return convoTemplate:getScreen("Responce_Dismiss")
	end
	return convoTemplate:getScreen("InitialConvo")
end