local ObjectManager = require("managers.object.object_manager")

deathWatchCommanderDkrnConvoHandler = {  }

function deathWatchCommanderDkrnConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()
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
end

function deathWatchCommanderDkrnConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("intro")
	end

	if (PlayerObject(pGhost):isOnLeave() or not CreatureObject(pPlayer):isImperial()) then
		return convoTemplate:getScreen("wrong_faction")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(2, "death_watch_bunker_imperial_sidequest")) then
		return convoTemplate:getScreen("quest_already_completed")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "death_watch_bunker_imperial_sidequest")) then
		return convoTemplate:getScreen("return_intro")
	else
		return convoTemplate:getScreen("intro")
	end
end

function deathWatchCommanderDkrnConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local pGhost = CreatureObject(conversingPlayer):getPlayerObject()

	if (pGhost == nil) then
		return conversationScreen
	end

	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	if (screenID == "good_now_go") then
		CreatureObject(conversingPlayer):setScreenPlayState(1, "death_watch_bunker_imperial_sidequest")
	elseif (screenID == "return_intro") then
		local pInventory =  CreatureObject(conversingPlayer):getSlottedObject("inventory")

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
		CreatureObject(conversingPlayer):removeScreenPlayState(1, "death_watch_bunker_imperial_sidequest")
	elseif (screenID == "excellent_reward") then
		PlayerObject(pGhost):increaseFactionStanding("imperial", 500)
		CreatureObject(conversingPlayer):setScreenPlayState(2, "death_watch_bunker_imperial_sidequest")
	end

	return conversationScreen
end
