local ObjectManager = require("managers.object.object_manager")

deathWatchCommanderDkrnConvoHandler = {  }

function deathWatchCommanderDkrnConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function deathWatchCommanderDkrnConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		if (playerObject:isOnLeave() or not player:isImperial()) then
			return convoTemplate:getScreen("wrong_faction")
		elseif (player:hasScreenPlayState(2, "death_watch_bunker_imperial_sidequest")) then
			return convoTemplate:getScreen("quest_already_completed")
		elseif (player:hasScreenPlayState(1, "death_watch_bunker_imperial_sidequest")) then
			return convoTemplate:getScreen("return_intro")
		else
			return convoTemplate:getScreen("intro")
		end
	end)
end

function deathWatchCommanderDkrnConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
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