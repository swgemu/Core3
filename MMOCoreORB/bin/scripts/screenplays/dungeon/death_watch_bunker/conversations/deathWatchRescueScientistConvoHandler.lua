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
		if (player:hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest") == 1) then
			return convoTemplate:getScreen("return_thanks")
		elseif (player:hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest") == 1) then
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
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player, playerObject)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "good_now_go") then
			player:setScreenPlayState(1, "death_watch_bunker_imperial_sidequest")
		elseif (screenID == "return_intro") then
			local pInventory =  player:getSlottedObject("inventory")

			if (pInventory ~= nil) then
				local pSample = getContainerObjectByTemplate(pInventory, "object/tangible/loot/dungeon/death_watch_bunker/blood_vial.iff", true)
				if (pSample ~= nil) then
					clonedConversation:addOption("@conversation/death_watch_imperial_herald:s_4f1e472e", "excellent_reward")
				end
			end
			clonedConversation:addOption("@conversation/death_watch_imperial_herald:s_dc839e59", "very_well_be_quick")
			clonedConversation:addOption("@conversation/death_watch_imperial_herald:s_55aa1278", "more_info")
			clonedConversation:addOption("@conversation/death_watch_imperial_herald:s_f70821a3", "sorry_to_hear")
		elseif (screenID == "sorry_to_hear") then
			player:removeScreenPlayState(1, "death_watch_bunker_imperial_sidequest")
		elseif (screenID == "excellent_reward") then
			playerObject:increaseFactionStanding("imperial", 500)
			player:setScreenPlayState(2, "death_watch_bunker_imperial_sidequest")
		end

		return conversationScreen
	end)
end