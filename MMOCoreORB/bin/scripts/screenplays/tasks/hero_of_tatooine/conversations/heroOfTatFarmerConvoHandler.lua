local ObjectManager = require("managers.object.object_manager")

heroOfTatFarmerConvoHandler = {  }

-- 1 - Started farmer quest, 2 - Completed farmer quest

function heroOfTatFarmerConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function heroOfTatFarmerConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		if (player:hasScreenPlayState(2, "hero_of_tatooine_altruism") == 1) then
			return convoTemplate:getScreen("intro_completed")
		elseif (player:hasScreenPlayState(1, "hero_of_tatooine_altruism") == 1) then
			return convoTemplate:getScreen("intro_has_quest")
		elseif (readData(CreatureObject(pNpc):getObjectID() .. ":gaveQuest") == 1) then
			return convoTemplate:getScreen("intro_someone_else_started")
		else
			return convoTemplate:getScreen("intro")
		end
	end)
end

function heroOfTatFarmerConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "in_your_debt") then
		CreatureObject(conversingPlayer):sendSystemMessage("@quest/hero_of_tatooine/system_messages:altruism_quest_fail")
		writeData(CreatureObject(conversingNPC):getObjectID() .. ":gaveQuest", 1)
		CreatureObject(conversingPlayer):subtractCashCredits(10000)
		HeroOfTatooineScreenPlay:doGiverDespawn(conversingNPC)
	elseif (screenID == "sincerest_gratitude") then
		HeroOfTatooineScreenPlay:giveAltruismWaypoint(conversingPlayer)
		writeData(CreatureObject(conversingNPC):getObjectID() .. ":gaveQuest", 1)
		CreatureObject(conversingPlayer):setScreenPlayState(1, "hero_of_tatooine_altruism")
		HeroOfTatooineScreenPlay:doGiverDespawn(conversingNPC)
	elseif (screenID == "here_is_loc_again") then
		HeroOfTatooineScreenPlay:giveAltruismWaypoint(conversingPlayer)
	elseif (screenID == "a_lot_of_money") then
		if(CreatureObject(conversingPlayer):getCashCredits() >= 10000) then
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_5cdaed70", "in_your_debt")
		else
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_2e1d6626", "ill_go_myself")
		end
		clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_d5adc7c6", "very_dangerous")
		clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_2fdb8fbd", "ill_go_myself")
	elseif (screenID == "thanks_for_offering") then
		CreatureObject(conversingPlayer):removeScreenPlayState(1, "hero_of_tatooine_altruism")
	end

	return conversationScreen
end