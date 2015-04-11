local ObjectManager = require("managers.object.object_manager")

heroOfTatBountyHunterConvoHandler = {  }

-- 1 - Started farmer quest, 2 - Completed farmer quest

function heroOfTatBountyHunterConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function heroOfTatBountyHunterConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local npcId = CreatureObject(pNpc):getObjectID()
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		if (player:hasScreenPlayState(2, "hero_of_tatooine_intellect")) then
			return convoTemplate:getScreen("intro_completed")
		elseif (readData(player:getObjectID() .. ":hero_of_tat:failedIntellect") == npcId) then
			return convoTemplate:getScreen("already_failed")
		elseif (player:hasScreenPlayState(1, "hero_of_tatooine_intellect")) then
			return convoTemplate:getScreen("intro_hasquest")
		else
			return convoTemplate:getScreen("intro")
		end
	end)
end

function heroOfTatBountyHunterConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "give_it_a_shot") then
		CreatureObject(conversingPlayer):setScreenPlayState(1, "hero_of_tatooine_intellect")
	elseif (screenID == "thats_great") then
		HeroOfTatooineScreenPlay:sendImplicateSui(conversingPlayer, conversingNPC)
	end

	return conversationScreen
end