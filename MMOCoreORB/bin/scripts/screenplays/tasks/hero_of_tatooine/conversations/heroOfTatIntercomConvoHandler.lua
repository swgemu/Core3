local ObjectManager = require("managers.object.object_manager")

heroOfTatIntercomConvoHandler = {  }

function heroOfTatIntercomConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local pConversationSession = player:getConversationSession()
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
	end)
end

function heroOfTatIntercomConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	local playerID = CreatureObject(pPlayer):getObjectID()
	local inProgressID = readData("hero_of_tat_ranch_player_id")
	if (inProgressID ~= 0 and inProgressID ~= playerID) then
		return convoTemplate:getScreen("intro_noquest")
	elseif (readData(playerID .. ":hero_of_tat_honor:accepted") == 1) then
		if (readData(playerID .. ":hero_of_tat_honor:distract_wife") == 1) then
			return convoTemplate:getScreen("intro_alreadytalked")
		else
			return convoTemplate:getScreen("intro")
		end
	else
		return convoTemplate:getScreen("intro_noquest")
	end
end

function heroOfTatIntercomConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "blast_it" or screenID == "go_talk_to_her") then
		writeData(CreatureObject(conversingPlayer):getObjectID() .. ":hero_of_tat_honor:distracting_wife", 1)
	end

	return conversationScreen
end