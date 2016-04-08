local ObjectManager = require("managers.object.object_manager")

seansHistorianConvoHandler = Object:new {
	themePark = nil
}

function seansHistorianConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function seansHistorianConvoHandler:historyQuest(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()
	local playerCampaign = readData(playerID .. ":bestine_election:SeanHistoryQuest")

	if (playerCampaign == electionNum) and (getQuestStatus("bestine_election:electionWinner") == "Sean") then
		return true
	end
	return false
end


function seansHistorianConvoHandler:hasHistoryDisk(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return false
	end

	local pHistoryDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff", true)
	return(pHistoryDisk ~= nil)
end

function seansHistorianConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local playerID = CreatureObject(pPlayer):getObjectID()

	if readData(playerID .. ":bestine_election:find") == 1 then
		return convoTemplate:getScreen("hquest_find")
	end

	if self:historyQuest(pPlayer) then
		return convoTemplate:getScreen("has_historyQuest")
	end

	if (getQuestStatus("bestine_election:electionWinner") == "Sean")then
		return convoTemplate:getScreen("sean_inOffice")
	else return convoTemplate:getScreen("sean_notinOffice")
	end
	return convoTemplate:getScreen("sean_notinOffice")
end

function seansHistorianConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local playerID = CreatureObject(conversingPlayer):getObjectID()

	if (screenID == "tellme_history_3") then
		writeData(playerID .. ":bestine_election:find",1)
		deleteData(playerID .. ":bestine_election:SeanHistoryQuest")
	end

	if (screenID == "hquest_find") then
		if self:hasHistoryDisk(conversingPlayer) then
			clonedConversation:addOption("@conversation/seans_historian:s_b30bd73c","found_something")--Yes, I did.
		else
			clonedConversation:addOption("@conversation/seans_historian:s_9c1a8dd7","keep_looking") --No, let me keep looking.
		end
	end

	if (screenID == "found_something") then
		local pGhost = CreatureObject(conversingPlayer):getPlayerObject()
		if (pGhost ~= nil) then
			writeData(playerID .. ":bestine_election:itemFound",1)
			deleteData(playerID .. ":bestine_election:find")
			deleteData(playerID .. ":bestine_election:SeanHistoryQuest")
			local wayID = readData(playerID .. ":bestine_election:historyWaypointID")
			PlayerObject(pGhost):removeWaypoint(wayID, true)
			deleteData(playerID .. ":bestine_election:historyWaypointID")
		end
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