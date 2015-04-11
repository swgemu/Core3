local ObjectManager = require("managers.object.object_manager")

heroOfTatMotherConvoHandler = {  }

function heroOfTatMotherConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function heroOfTatMotherConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		if (player:hasScreenPlayState(1, "hero_of_tatooine_altruism") and not player:hasScreenPlayState(2, "hero_of_tatooine_altruism")) then
			return convoTemplate:getScreen("intro")
		else
			return convoTemplate:getScreen("intro_noquest")
		end
	end)
end

function heroOfTatMotherConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "right_behind_you") then
			local daughterID = readData("hero_of_tat:farmerChildId")
			local pDaughter = getSceneObject(daughterID)

			if (pDaughter == nil or not SceneObject(pDaughter):isAiAgent() or not SceneObject(conversingNPC):isAiAgent()) then
				player:sendSystemMessage("Error initiating escort. Please submit a bug report.")
				return
			end

			AiAgent(pDaughter):setFollowObject(conversingNPC)
			AiAgent(pDaughter):setAiTemplate("follow")
			CreatureObject(conversingNPC):setOptionsBitmask(128)
			AiAgent(conversingNPC):setFollowObject(conversingPlayer)
			AiAgent(conversingNPC):setAiTemplate("follow")
			writeData("hero_of_tat:altruismEscortStatus", 1)
			writeData("hero_of_tat:altruismEscorterID", SceneObject(conversingPlayer):getObjectID())
			createEvent(2000, "HeroOfTatooineScreenPlay", "escortRangeCheckEvent", conversingPlayer)
		end

		return conversationScreen
	end)
end