local ObjectManager = require("managers.object.object_manager")

heroOfTatIntellectLiarConvoHandler = {  }

function heroOfTatIntellectLiarConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function heroOfTatIntellectLiarConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		if (player:hasScreenPlayState(1, "hero_of_tatooine_intellect") == 1 and player:hasScreenPlayState(2, "hero_of_tatooine_intellect") ~= 1) then
			return convoTemplate:getScreen("init")
		else
			return convoTemplate:getScreen("init_noquest")
		end
	end)
end

function heroOfTatIntellectLiarConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "init" or screenID == "init_noquest") then
			clonedConversation:setDialogTextStringId("@quest/hero_of_tatooine/intellect_liar:greeting_" .. getRandomNumber(11))
		elseif (screenID == "equipment") then
			clonedConversation:setDialogTextStringId("@quest/hero_of_tatooine/intellect_liar:equipment_" .. getRandomNumber(11))
		elseif (screenID == "smugglers") then
			local liarId = readData(SceneObject(conversingNPC):getObjectID() .. ":liarId")

			if (liarId == 0) then
				CreatureObject(conversingPlayer):sendSystemMessage("Unable to find Mark of Intellect smuggler data. Please file a bug report.")
				return conversationScreen
			end

			liarId = liarId - 1

			clonedConversation:setDialogTextStringId("@quest/hero_of_tatooine/intellect_liar:others_" .. liarId .. "_" .. getRandomNumber(2))
			if (liarId == 1) then
				clonedConversation:setDialogTextTO(HeroOfTatooineScreenPlay:getIntellectLiarName(5))
			elseif (liarId == 2) then
				clonedConversation:setDialogTextTT(HeroOfTatooineScreenPlay:getIntellectLiarName(1))
				clonedConversation:setDialogTextTO(HeroOfTatooineScreenPlay:getIntellectLiarName(3))
			elseif (liarId == 3) then
				clonedConversation:setDialogTextTT(HeroOfTatooineScreenPlay:getIntellectLiarName(1))
				clonedConversation:setDialogTextTO(HeroOfTatooineScreenPlay:getIntellectLiarName(2))
			elseif (liarId == 4) then
				clonedConversation:setDialogTextTT(HeroOfTatooineScreenPlay:getIntellectLiarName(3))
				clonedConversation:setDialogTextTO(HeroOfTatooineScreenPlay:getIntellectLiarName(1))
				clonedConversation:setDialogTextTU(HeroOfTatooineScreenPlay:getIntellectLiarName(2))
			elseif (liarId == 5) then
				clonedConversation:setDialogTextTO(HeroOfTatooineScreenPlay:getIntellectLiarName(4))
			end

		elseif (screenID == "bye") then
			clonedConversation:setDialogTextStringId("@quest/hero_of_tatooine/intellect_liar:bye" .. getRandomNumber(11))
		end

		return conversationScreen
	end)
end