local ObjectManager = require("managers.object.object_manager")

heroOfTatHermitConvoHandler = {  }

--[[
1 - Started squill quest
2 - Completed squill quest
4 - Completed Altruism
8 - Completed Intellect
16 - Completed Courage
32 - Completed Honor
64 - Completed Mark of Hero
]]

function heroOfTatHermitConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function heroOfTatHermitConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		if (player:hasScreenPlayState(2, "hero_of_tatooine") == 1) then
			return convoTemplate:getScreen("you_have_returned")
		elseif (player:hasScreenPlayState(1, "hero_of_tatooine") == 1) then
			return convoTemplate:getScreen("return_intro")
		else
			return convoTemplate:getScreen("intro")
		end
	end)
end

function heroOfTatHermitConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "go_then") then
			player:setScreenPlayState(1, "hero_of_tatooine")
		elseif (screenID == "return_intro") then
			local pInventory =  player:getSlottedObject("inventory")

			if (pInventory ~= nil) then
				local pSkull = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/hero_of_tatooine/squill_skull.iff", true)

				if (pSkull ~= nil) then
					clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_af540d0", "proven_worthy")
				end
			end
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_da196589", "as_you_wish")
		elseif (screenID == "proven_worthy") then
			local pInventory = player:getSlottedObject("inventory")

			if (pInventory ~= nil) then
				local pSkull = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/hero_of_tatooine/squill_skull.iff", true)

				if (pSkull == nil) then
					return 0
				end

				SceneObject(pSkull):destroyObjectFromWorld()
				SceneObject(pSkull):destroyObjectFromDatabase()
				player:setScreenPlayState(2, "hero_of_tatooine")
			end
		end

		return conversationScreen
	end)
end