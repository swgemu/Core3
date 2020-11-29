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

VisionsJohnRoy_convo_handler = conv_handler:new {}

function VisionsJohnRoy_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end
		
	if (screenID == "Response_01" or screenID == "Response_02") then
		local visionsWpID_2 = PlayerObject(pGhost):addWaypoint("yavin4", "Deathstar Wreckage", "Deathstar Wreckage", 1921, -3040, WAYPOINT_COLOR_PURPLE, true, true, 0)

		if visionsWpID_2 ~= nil then
			VisionsOfThePast:setQuestStatus(pPlayer, ":visionsWpID_2", visionsWpID_2)
			VisionsOfThePast:setQuestStatus(pPlayer, ":visionsStatus", 2)
		end
	end

	if (screenID == "Turnin_Response_01" or screenID == "Turnin_Response_02") then
		if VisionsOfThePast:hasCollectionItem(pPlayer) then
			local clonedConversation = LuaConversationScreen(pConvScreen)
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			local playerID = SceneObject(pPlayer):getObjectID()

			if pInventory == nil then
				return
			end

			if SceneObject(pInventory):isContainerFullRecursive() then
				CreatureObject(pPlayer):sendSystemMessage("Your inventory is full and you are unable to receive your reward!")
				return 0
			end

			local wpID_1 = getQuestStatus(playerID .. ":visionsWpID_1")
			local wpID_2 = getQuestStatus(playerID .. ":visionsWpID_2")

			PlayerObject(pGhost):removeWaypoint(wpID_1, true)
			PlayerObject(pGhost):removeWaypoint(wpID_2, true)

			VisionsOfThePast:setQuestStatus(pPlayer, ":visionsStatus", 3)
			ThemeParkLogic:giveFaction(pPlayer, "rebel", 2000)
			VisionsOfThePast:grantReward(pPlayer)
			createEvent(5000, "VisionsOfThePast", "cleanUp", pPlayer, "")
		end
	end
	return pConvScreen
end

function VisionsJohnRoy_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerID = SceneObject(pPlayer):getObjectID()
	local visionsStatus = getQuestStatus(playerID .. ":visionsStatus")
	local visionsHelperStatus = getQuestStatus(playerID .. ":visionsHelper")

	if (playerFaction == FACTIONIMPERIAL or visionsHelperStatus == "2") then
		return convoTemplate:getScreen("Deny_Faction")
	end

	if visionsStatus == "3" then
		return convoTemplate:getScreen("Service_Noted")
	elseif (visionsStatus == "2" and VisionsOfThePast:hasCollectionItem(pPlayer) == true) then
		return convoTemplate:getScreen("TurnIn")
	elseif visionsStatus == "2" then
		return convoTemplate:getScreen("Time_Wasted")
	elseif visionsStatus == "1" then
		return convoTemplate:getScreen("InitialConvo")
	end
	return convoTemplate:getScreen("No_Quest")
end
