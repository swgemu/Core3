local ObjectManager = require("managers.object.object_manager")

deathWatchRescueScientistConvoHandler = {  }

function deathWatchRescueScientistConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function deathWatchRescueScientistConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function deathWatchRescueScientistConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		if (player:hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest")) then
			return convoTemplate:getScreen("return_thanks")
		elseif (player:hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest")) then
			player:setScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
			player:sendSystemMessageWithDI("@theme_park/messages:theme_park_credits_pp", "487")
			player:addCashCredits(487, true)
			return convoTemplate:getScreen("thanks1")
		elseif (playerObject:isOnLeave() or not player:isRebel()) then
			return convoTemplate:getScreen("thanks2")
		else
			return convoTemplate:getScreen("thanks3")
		end
	end)
end

function deathWatchRescueScientistConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end