local ObjectManager = require("managers.object.object_manager")

heroOfTatPirateLeaderConvoHandler = {  }

function heroOfTatPirateLeaderConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function heroOfTatPirateLeaderConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("intro")
end

function heroOfTatPirateLeaderConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "made_me_happy" or screenID == "be_quick") then
		HeroOfTatooineScreenPlay:giveHonorWaypoint(conversingPlayer)
		CreatureObject(conversingPlayer):setScreenPlayState(1, "hero_of_tatooine_honor")
		HeroOfTatooineScreenPlay:doGiverDespawn(conversingNPC)
	elseif (screenID == "lets_get_em" or screenID == "is_that_so" or screenID == "teach_a_lesson") then
		HeroOfTatooineScreenPlay:spawnAggroLeader(conversingNPC, conversingPlayer, screenID)
	end

	return conversationScreen
end