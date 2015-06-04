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
		
		local waypointID = readData(playerID .. ":tutorial:releaseDocsWaypointID")
		
		if pGhost ~= nil and pQuartermaster ~= nil and waypointID == 0 then
			waypointID = PlayerObject(pGhost):addWaypoint("default", "@newbie_tutorial/system_messages:release_docs", "", SceneObject(pQuartermaster):getWorldPositionX(), SceneObject(pQuartermaster):getWorldPositionY(), WAYPOINTBLUE, true, true, 0, 0)
			writeData(playerID .. ":tutorial:releaseDocsWaypointID", waypointID)
		end
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