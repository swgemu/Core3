local ObjectManager = require("managers.object.object_manager")

tutorialQuartermasterConvoHandler = conv_handler:new {}

function tutorialQuartermasterConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "you_may_leave") then
		local playerID = CreatureObject(pPlayer):getObjectID()

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if pInventory == nil then
			return pConvScreen
		end

		local pInvItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/dungeon/death_watch_bunker/viewscreen_s2.iff", false)

		if (pInvItem ~= nil) then
			SceneObject(pInvItem):destroyObjectFromWorld()
			SceneObject(pInvItem):destroyObjectFromDatabase()
		end

		local terminalID = readData(playerID .. ":tutorial:travelTerminal")
		local pTerminal = getSceneObject(terminalID)
		if (pTerminal ~= nil) then
			setAuthorizationState(pTerminal, true)
			TutorialScreenPlay:markRoomComplete(pPlayer, "r11")
		end

		CreatureObject(pNpc):clearOptionBit(CONVERSABLE)
	elseif (screenID == "intro_nodocs") then
		local giverID = readData(CreatureObject(pPlayer):getObjectID() .. ":tutorial:roomTenMissionGiver")
		
		local pMissionGiver = getSceneObject(giverID)
		
		if (pMissionGiver ~= nil) then
			CreatureObject(pMissionGiver):setOptionBit(CONVERSABLE)
		end
	end

	return pConvScreen
end

function tutorialQuartermasterConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return convoTemplate:getScreen("intro_nodocs")
	end

	local pInvItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/dungeon/death_watch_bunker/viewscreen_s2.iff", false)

	if (pInvItem == nil) then
		return convoTemplate:getScreen("intro_nodocs")
	else
		return convoTemplate:getScreen("intro")
	end
end
