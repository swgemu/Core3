local ObjectManager = require("managers.object.object_manager")
seansHistorianConvoHandler = Object:new {	}

function seansHistorianConvoHandler:hasHistoryQuest(pPlayer)
	if (pPlayer ~= nil) then
		return getQuestStatus("bestine_election:electionWinner") == "Sean" and CreatureObject(pPlayer):hasScreenPlayState(2, "bestine_history_quest")
	end
	return false
end

function seansHistorianConvoHandler:hasHistoryDisk(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		local pHistoryDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff", true)
		return(pHistoryDisk ~= nil)
	end
	return false
end

function seansHistorianConvoHandler:foundSomething(pPlayer)
	if (pPlayer ~= nil) then
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			local playerID = CreatureObject(pPlayer):getObjectID()
			local wayID = readData(playerID .. ":bestine_election:historyWaypointID")
			PlayerObject(pPlayerObj):removeWaypoint(wayID, true)
			deleteData(playerID .. ":bestine_election:historyWaypointID")
		end
	end
end

function seansHistorianConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	
	if getQuestStatus("bestine_election:electionWinner") ~= "Sean" then
		return convoTemplate:getScreen("sean_notinOffice")
	elseif CreatureObject(pPlayer):hasScreenPlayState(4, "bestine_history_quest") or CreatureObject(pPlayer):hasScreenPlayState(8, "bestine_history_quest") then
		return convoTemplate:getScreen("hquest_find")
	elseif self:hasHistoryQuest(pPlayer) then
		return convoTemplate:getScreen("has_historyQuest")
	elseif (getQuestStatus("bestine_election:electionWinner") == "Sean")then
		return convoTemplate:getScreen("sean_inOffice")
	end
	return convoTemplate:getScreen("sean_notinOffice")
end

function seansHistorianConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "tellme_history_3") then
	CreatureObject(conversingPlayer):removeScreenPlayState(2,"bestine_history_quest")
		CreatureObject(conversingPlayer):setScreenPlayState(4,"bestine_history_quest")
	elseif (screenID == "hquest_find") then
		if self:hasHistoryDisk(conversingPlayer) then
			clonedConversation:addOption("@conversation/seans_historian:s_b30bd73c","found_something")--Yes, I did.
		else
			clonedConversation:addOption("@conversation/seans_historian:s_9c1a8dd7","keep_looking") --No, let me keep looking.
		end
	elseif (screenID == "found_something") then
		self:foundSomething(conversingPlayer)
		CreatureObject(conversingPlayer):removeScreenPlayState(4,"bestine_history_quest")
		CreatureObject(conversingPlayer):setScreenPlayState(8,"bestine_history_quest")
	end
	
	return conversationScreen
end

function seansHistorianConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
