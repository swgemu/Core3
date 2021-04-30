local ObjectManager = require("managers.object.object_manager")

--[[ Anniversary Screenplay Status
0 - Not spoken with the Grandmaster Baker
1 - Accepted to speak with Information Broker on Tatooine
2 - Spoken with Information on Tatooine and accepted to find thiefs
3 - Spoken with disaster of desserts and confronted him
4 - Turn in item to Grandmaster Baker
]]

AnniversarySnoopStewart_convo_handler = conv_handler:new {}

function AnniversarySnoopStewart_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	if (screenID == "Response_01" or screenID == "Response_02") then
		local anniversaryWpID_1 = PlayerObject(pGhost):addWaypoint("tatooine", "Information Broker", "Information Broker", 3274, -4904, 2, true, true, 0)

		if anniversaryWpID_1 ~= nil then
			BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryWpID_1", anniversaryWpID_1)
			BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryStatus", 1)
		end
	end

	if (screenID == "TurnIn_Response_01" or screenID == "TurnIn_Response_02") then
		if BasiliskAnniversary:hasCollectionItem(pPlayer) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			local playerID = SceneObject(pPlayer):getObjectID()

			if pInventory == nil then
				return
			end

			if SceneObject(pInventory):isContainerFullRecursive() then
				CreatureObject(pPlayer):sendSystemMessage("Your inventory is full and you are unable to receive your reward!")
				return 0
			end

			local wpID_2 = tonumber(getQuestStatus(playerID .. ":anniversaryWpID_2"))
			local wpID_3 = tonumber(getQuestStatus(playerID .. ":anniversaryWPID_3"))

			if wpID_2 ~= 0 and wpID_3 ~= 0 then
				PlayerObject(pGhost):removeWaypoint(wpID_2, true)
				PlayerObject(pGhost):removeWaypoint(wpID_3, true)
			end

			BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryStatus", 4)
			BasiliskAnniversary:grantReward(pPlayer)
			createEvent(5000, "BasiliskAnniversary", "cleanUp", pPlayer, "")
		end
	end
	return pConvScreen
end

function AnniversarySnoopStewart_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerID = SceneObject(pPlayer):getObjectID()
	local anniversaryStatus = getQuestStatus(playerID .. ":anniversaryStatus")

	if anniversaryStatus == "4" then
		return convoTemplate:getScreen("Service_Noted")
	elseif (anniversaryStatus == "3" and BasiliskAnniversary:hasCollectionItem(pPlayer) == true) then
		return convoTemplate:getScreen("TurnInConvo")
	elseif anniversaryStatus == "2" or anniversaryStatus == "1" then
		return convoTemplate:getScreen("Time_Wasted")
	end
		return convoTemplate:getScreen("InitialConvo")
end