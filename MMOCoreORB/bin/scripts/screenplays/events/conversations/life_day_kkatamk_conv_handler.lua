local ObjectManager = require("managers.object.object_manager")

lifeDayKkatamkConvoHandler = Object:new {}

function lifeDayKkatamkConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	return ObjectManager.withCreatureObject(pPlayer, function(player)
		if readScreenPlayData(pPlayer, "lifeDay", "complete") == "1" then
			return convoTemplate:getScreen("return_complete")
		elseif readData(player:getObjectID() .. ":lifeDayState") == 1 then
			return convoTemplate:getScreen("return_incomplete")
		elseif player:getSpecies() == 4 then
			return convoTemplate:getScreen("greetings_wookiee")
		else
			return convoTemplate:getScreen("greetings")
		end
	end)
end

function lifeDayKkatamkConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if screenID == "waypoint" or screenID == "waypoint_wookiee" or screenID == "new_waypoint" then
		lifeDayScreenplay:giveWaypoint(conversingPlayer)
	end
	return conversationScreen
end

function lifeDayKkatamkConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
