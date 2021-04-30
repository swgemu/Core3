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

	if pPlayer == nil or pNpc == nil then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if screenID == "Response_Accepted" then
		local playerID = SceneObject(pPlayer):getObjectID()
		local pInventory = SceneObject(pNpc):getSlottedObject("inventory")

		if (pInventory == nil) then
			return
		end

		SceneObject(pInventory):setContainerOwnerID(playerID)
		createLoot(pInventory, "anniversary_quest_loot_group", 0, true)

		local anniversaryWpID_3 = PlayerObject(pGhost):addWaypoint("naboo", "Return The Ingredient", "Return The Ingredient", -5086, 4104, 2, true, true, 0)

		BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryStatus", 3)
		BasiliskAnniversary:setQuestStatus(pPlayer, ":anniversaryWpID_3", anniversaryWpID_3)

		CreatureObject(pNpc):setPvpStatusBitmask(4)
		AiAgent(pNpc):setDefender(pPlayer)

		local wpID_2 = getQuestStatus(playerID .. ":anniversaryWpID_2")

		if wpID_2 ~= nil then
			PlayerObject(pGhost):removeWaypoint(wpID_2, true)
			removeQuestStatus(playerID .. ":anniversaryWpID_2")
		end
	end
	return pConvScreen
end

function AnniversaryAltonFlay_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if pPlayer == nil then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local anniversaryStatus = getQuestStatus(playerID .. ":anniversaryStatus")

	if (anniversaryStatus == nil) then
		anniversaryStatus = "0"
	end

	if anniversaryStatus == "2" then
		return convoTemplate:getScreen("InitialConvo")
	end

	return convoTemplate:getScreen("Response_Dismiss")
end