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
		if (HeroOfTatooineScreenPlay:isMissingMark(pPlayer)) then
			return convoTemplate:getScreen("you_have_returned_missing_marks")
		elseif (player:hasScreenPlayState(64, "hero_of_tatooine")) then
			return convoTemplate:getScreen("hero_returns")
		elseif (player:hasScreenPlayState(2, "hero_of_tatooine")) then
			return convoTemplate:getScreen("you_have_returned")
		elseif (player:hasScreenPlayState(1, "hero_of_tatooine")) then
			return convoTemplate:getScreen("return_intro")
		else
			return convoTemplate:getScreen("intro")
		end
	end)
end

function heroOfTatHermitConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player, playerObject)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "go_then") then
			player:setScreenPlayState(1, "hero_of_tatooine")
		elseif (screenID == "you_have_returned_missing_marks") then
			local pInventory = player:getSlottedObject("inventory")

			if (pInventory == nil or SceneObject(pInventory):hasFullContainerObjects()) then
				clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_6441a2a6", "inv_full")
			else
				if (HeroOfTatooineScreenPlay:giveMissingMarks(conversingPlayer)) then
					clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_6441a2a6", "now_have_items")
				else
					clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_6441a2a6", "dont_have_room")
				end
			end
		elseif (screenID == "you_have_returned") then
			if (player:hasScreenPlayState(2, "hero_of_tatooine") and player:hasScreenPlayState(4, "hero_of_tatooine") and player:hasScreenPlayState(8, "hero_of_tatooine")
				and player:hasScreenPlayState(16, "hero_of_tatooine") and player:hasScreenPlayState(32, "hero_of_tatooine")) then
				clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_cd2c070a", "you_bear_marks")
			end
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_503d468c", "which_mark")
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_da196589", "as_you_wish")
		elseif (screenID == "done_great_things") then

			local pInventory = player:getSlottedObject("inventory")

			if (pInventory == nil) then
				return
			end

			if (SceneObject(pInventory):hasFullContainerObjects()) then
				player:setScreenPlayState(16, "hero_of_tatooine_missing_marks") -- 1 - Altruism, 2 - Intellect, 4 - Courage, 8 - Honor, 16 - Ring
				player:sendSystemMessage("@quest/hero_of_tatooine/system_messages:hero_inv_full")
			else
				local pMark = giveItem(pInventory, "object/tangible/wearables/ring/ring_mark_hero.iff", -1)

				if (pMark == nil) then
					player:setScreenPlayState(16, "hero_of_tatooine_missing_marks") -- 1 - Altruism, 2 - Intellect, 4 - Courage, 8 - Honor, 16 - Ring
					player:sendSystemMessage("Error creating object. Please file a bug report.")
				end
			end

			playerObject:awardBadge(11)
			player:setScreenPlayState(64, "hero_of_tatooine")
			CreatureObject(conversingNPC):doAnimation("worship")
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
				CreatureObject(conversingNPC):doAnimation("taken_aback")
			end
		elseif (screenID == "intro") then
			CreatureObject(conversingNPC):doAnimation("greet")
		end

		return conversationScreen
	end)
end