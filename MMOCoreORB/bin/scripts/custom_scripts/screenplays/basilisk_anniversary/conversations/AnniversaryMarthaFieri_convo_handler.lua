local ObjectManager = require("managers.object.object_manager")

--[[ Anniversary Screenplay Status
0 - Not spoken with the Grandmaster Baker
1 - Accepted to speak with Information Broker on Tatooine
2 - Spoken with Information on Tatooine and accepted to find thiefs
3 - Spoken with disaster of desserts and confronted him
4 - Turn in item to Grandmaster Baker
]]


AnniversaryMarthaFieri_convo_handler = conv_handler:new {}

function AnniversaryMarthaFieri_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (screenID == "Response_01" or screenID == "Response_02") then
		if pGhost ~= nil then
			local visionsWpID_2 = PlayerObject(pGhost):addWaypoint("corellia", "Culprit's last known location.", "Culprit's last known location.", -474, -4652, WAYPOINT_COLOR_PURPLE, true, true, 0)

			BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryStatus", 2)
			BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryWpID_2", anniversaryWpID_2)
		end
	end
	return pConvScreen
end

function AnniversaryMarthaFieri_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerID = SceneObject(pPlayer):getObjectID()
	local anniversaryStatus = getQuestStatus(playerID .. ":anniversaryStatus")

	if (anniversaryStatus == nil) then
		anniversaryStatus = "0"
	end

	if anniversaryStatus == "2" then
		return convoTemplate:getScreen("Response_Accepted")
	elseif (anniversaryStatus == "3" or anniversaryStatus == "4") then
		return convoTemplate:getScreen("Service_Noted")
	elseif (anniversaryStatus == "1") then
		return convoTemplate:getScreen("InitialConvo")
	end
	return convoTemplate:getScreen("Responce_Dismiss")
end