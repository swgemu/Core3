local ObjectManager = require("managers.object.object_manager")

tutorialMissionGiverConvoHandler = Object:new { }

function tutorialMissionGiverConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	local playerID = SceneObject(conversingPlayer):getObjectID()
	if (screenID == "get_moving") then
		writeData(playerID .. ":tutorial:hasGottenMission", 1)
		local pGhost = CreatureObject(conversingPlayer):getPlayerObject()
		local quartermasterID = readData(playerID .. ":tutorial:roomElevenQuartermaster")
		local pQuartermaster = getSceneObject(quartermasterID)

		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")

		if pInventory == nil then
			return conversationScreen
		end

		local pInvItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/dungeon/death_watch_bunker/viewscreen_s2.iff", false)

		if pGhost ~= nil and pQuartermaster ~= nil and pInvItem == nil then
			local pItem = giveItem(pInventory, "object/tangible/loot/dungeon/death_watch_bunker/viewscreen_s2.iff", -1)
			
			if (pItem ~= nil) then
				SceneObject(pItem):setCustomObjectName("Release Documents")
			end
		end
		CreatureObject(conversingNPC):setOptionsBitmask(128)
		TutorialScreenPlay:handleRoomTen(conversingPlayer)
	end

	return conversationScreen
end

function tutorialMissionGiverConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	return convoTemplate:getScreen("intro")
end

function tutorialMissionGiverConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
