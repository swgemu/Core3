local ObjectManager = require("managers.object.object_manager")

tutorialQuartermasterConvoHandler = Object:new { }

function tutorialQuartermasterConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "you_may_leave") then
		ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player, playerObject)
			local waypointID = readData(player:getObjectID() .. ":tutorial:releaseDocsWaypointID")
			if (waypointID ~= 0) then
				playerObject:removeWaypoint(waypointID, true)
			end

			writeData(player:getObjectID() .. ":tutorial:hasTurnedInDocs", 1)

			local terminalID = readData(player:getObjectID() .. ":tutorial:travelTerminal")
			local pTerminal = getSceneObject(terminalID)
			if (pTerminal ~= nil) then
				setAuthorizationState(pTerminal, true)
			end
		end)
	end

	return conversationScreen
end

function tutorialQuartermasterConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local waypointID = readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:releaseDocsWaypointID")
	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint == nil) then
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