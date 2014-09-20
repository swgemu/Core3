local ObjectManager = require("managers.object.object_manager")

lifeDayAnarraConvoHandler = Object:new {}

function lifeDayAnarraConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, ghost)
		if readScreenPlayData(pPlayer, "lifeDay", "complete") == "1" or readData(player:getObjectID() .. ":lifeDayAnarra") == 1 then
			return convoTemplate:getScreen("tell_again")
		elseif readData(player:getObjectID() .. ":lifeDayState") == 2 then
			return convoTemplate:getScreen("renewel")
		else
			return convoTemplate:getScreen("elder_first")
		end
	end)
end

function lifeDayAnarraConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local screen = LuaConversationScreen(conversationScreen)
		local screenID = screen:getScreenID()
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)

		if screenID == "appreciate_freedom" then
			if TangibleObject(conversingPlayer):isImperial() == true then
				clonedConversation:addOption("@conversation/lifeday04c:s_b8b7ef2b", "work_for_empire") -- Yes. Go on.
			else
				clonedConversation:addOption("@conversation/lifeday04c:s_b8b7ef2b", "share_our_tale") -- Yes. Go on.
			end
		elseif screenID == "hope_you_will" or screenID == "thank_you" then
			writeData(player:getObjectID() .. ":lifeDayAnarra", 1)
			if readData(player:getObjectID() .. ":lifeDayRadrrl") == 1 and readData(player:getObjectID() .. ":lifeDayTebeurra") == 1 then
				writeData(player:getObjectID() .. ":lifeDayState", 3)
			end
		end
		return conversationScreen
	end)
end

function lifeDayAnarraConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
