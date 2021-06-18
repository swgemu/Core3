local ObjectManager = require("managers.object.object_manager")

--[[ empiredayReb Screenplay Status
0 - Not spoken with Lowell
1 - Accepted to speak with Scarface
2 - Spoken with Scarface and accepted to speak with Edwards
3 - Spoken with Edwards and accepted to speak with Zuvord
4 - Spoken with Zuvord and accepted to speak with Lowell
5 - Spoken again with Lowell and accepted to speak with Caretaker
6 - Turned in Quest for rewards from Caretaker

Helper Status
1 - rebel
2 - imperial
]]

EmpireDayCaretaker_convo_handler = conv_handler:new {}

function EmpireDayCaretaker_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (pPlayer == nil) then
		return
	end

	if screenID == "Response_Accepted" then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		local playerID = SceneObject(pPlayer):getObjectID()

		if pInventory == nil then
			return
		end

		if SceneObject(pInventory):isContainerFullRecursive() then
			CreatureObject(pPlayer):sendSystemMessage("Your inventory is full and you are unable to receive your reward!")
			return
		end

		EmpireDay:grantReward(pPlayer)
		EmpireDay:setQuestStatus(pPlayer, ":empiredayRebStatus", 6)
		createEvent(5000, "EmpireDay", "cleanUp", pPlayer, "")

		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if pGhost ~= nil then
			PlayerObject(pGhost):addWaypoint("naboo", "Remembrance Day Memorial", "Remembrance Day Memorial", 4138, 3211, WAYPOINT_COLOR_PURPLE, true, true, 0)

			local wpID_5 = getQuestStatus(playerID .. ":empiredayRebWpID_5")

			if wpID_5 ~= nil then
				PlayerObject(pGhost):removeWaypoint(wpID_5, true)
				removeQuestStatus(playerID .. ":empiredayRebWpID_5")
			end
		end
	end

	return pConvScreen
end

function EmpireDayCaretaker_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (pPlayer == nil) then
		return
	end

	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerID = SceneObject(pPlayer):getObjectID()
	local empiredayRebStatus = tonumber(getQuestStatus(playerID .. ":empiredayRebStatus"))
	local empiredayHelperStatus = getQuestStatus(playerID .. ":empiredayHelper")

	if (empiredayRebStatus == nil) then
		empiredayRebStatus = 0
	end

	if (playerFaction == FACTIONIMPERIAL or empiredayHelperStatus == "2") then
		return convoTemplate:getScreen("Deny_Faction")
	end

	if empiredayRebStatus < 5 then
		return convoTemplate:getScreen("General_Greeting")
	elseif empiredayRebStatus == 6 then
		return convoTemplate:getScreen("Service_Noted")
	end

	return convoTemplate:getScreen("InitialConvo")
end