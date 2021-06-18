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

empiredayCaretaker_convo_handler = conv_handler:new {}

function empiredayCaretaker_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (screenID == "Response_01" or "Response_02")then
		if pGhost ~= nil then


			EmpireDay:setQuestStatus(pPlayer, ":empiredayRebStatus", 6)
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

                empireday:grantReward(pPlayer)
                createEvent(5000, "empireday", "cleanUp", pPlayer, "")
            end
		end
    end
	return pConvScreen
end

function empiredayCaretaker_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerID = SceneObject(pPlayer):getObjectID()
	local empiredayRebStatus = getQuestStatus(playerID .. ":empiredayRebStatus")
	local empiredayHelperStatus = getQuestStatus(playerID .. ":empiredayHelper")

	if (empiredayRebStatus == nil) then
		empiredayRebStatus = "0"
	end

	if (playerFaction == FACTIONIMPERIAL or empiredayHelperStatus == "2") then
		return convoTemplate:getScreen("Deny_Faction")
	end

	if empiredayRebStatus == "6" then
		return convoTemplate:getScreen("Response_Accepted")
	elseif (empiredayRebStatus == "3" or empiredayRebStatus == "4" or empiredayRebStatus == "1" or empiredayRebStatus == "2") then
		return convoTemplate:getScreen("Service_Noted")
	end

	return convoTemplate:getScreen("InitialConvo")

end