local ObjectManager = require("managers.object.object_manager")

tutorialQuartermasterConvoHandler = Object:new { }

function tutorialQuartermasterConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "you_may_leave") then
		ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player, playerObject)
			local playerID = player:getObjectID()

			local pInventory = player:getSlottedObject("inventory")

			if pInventory == nil then
				return conversationScreen
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
				TutorialScreenPlay:markRoomComplete(conversingPlayer, "r11")
			end
		end)
		CreatureObject(conversingNPC):setOptionsBitmask(128)
	end

	return conversationScreen
end

function tutorialQuartermasterConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	
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

function tutorialQuartermasterConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()
	local pLastConversationScreen = nil
	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)
		return conversationTemplate:getScreen(optionLink)
	end
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end
