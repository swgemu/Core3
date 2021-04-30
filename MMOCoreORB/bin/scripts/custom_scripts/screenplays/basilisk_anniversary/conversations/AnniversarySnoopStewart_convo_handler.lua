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

	if pPlayer == nil then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if screenID == "Response_Accepted" then
		local anniversaryWpID_1 = PlayerObject(pGhost):addWaypoint("tatooine", "Information Broker", "Information Broker", 3274, -4904, 2, true, true, 0)

		if anniversaryWpID_1 ~= nil then
			BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryWpID_1", anniversaryWpID_1)
			BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryStatus", 1)
		end
	end

	if screenID == "Reset_Response" then
		local anniversaryWpID_2 = PlayerObject(pGhost):addWaypoint("corellia", "Culprit's last known location.", "Culprit's last known location.", -474, -4652, 2, true, true, 0)

		BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryStatus", 2)
		BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryWpID_2", anniversaryWpID_2)

		local playerID = SceneObject(pPlayer):getObjectID()
		local wpID_3 = getQuestStatus(playerID .. ":anniversaryWpID_3")

		if wpID_3 ~= nil then
			PlayerObject(pGhost):removeWaypoint(wpID_3, true)
			removeQuestStatus(playerID .. ":anniversaryWpID_3")
		end

	end

	if screenID == "TurnInResponse_Accepted" then
		if BasiliskAnniversary:hasCollectionItem(pPlayer) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			local playerID = SceneObject(pPlayer):getObjectID()

			if pInventory == nil then
				return
			end

			if SceneObject(pInventory):isContainerFullRecursive() then
				CreatureObject(pPlayer):sendSystemMessage("Your inventory is full and you are unable to receive your reward!")
				return
			end

			local wpID_3 = getQuestStatus(playerID .. ":anniversaryWpID_3")

			if wpID_3 ~= nil then
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

	if pPlayer == nil then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local anniversaryStatus = getQuestStatus(playerID .. ":anniversaryStatus")

	if anniversaryStatus == nil then
		anniversaryStatus = 0
		BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryStatus", 0)
	end

	if anniversaryStatus == "4" then
		return convoTemplate:getScreen("Service_Noted")
	elseif anniversaryStatus == "3" and BasiliskAnniversary:hasCollectionItem(pPlayer) then
		return convoTemplate:getScreen("TurnInConvo")
	elseif anniversaryStatus == "3" and BasiliskAnniversary:hasCollectionItem(pPlayer) == false then
		return convoTemplate:getScreen("NoItem")
	elseif anniversaryStatus == "1" or anniversaryStatus == "2" then
		return convoTemplate:getScreen("Time_Wasted")
	end

	return convoTemplate:getScreen("InitialConvo")
end