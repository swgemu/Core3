local ObjectManager = require("managers.object.object_manager")
seansHistorianConvoHandler = conv_handler:new {
}

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


function seansHistorianConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "tellme_history_3") then
	CreatureObject(pPlayer):removeScreenPlayState(2,"bestine_history_quest")
		CreatureObject(pPlayer):setScreenPlayState(4,"bestine_history_quest")
	elseif (screenID == "hquest_find") then
		if self:hasHistoryDisk(pPlayer) then
			clonedConversation:addOption("@conversation/seans_historian:s_b30bd73c","found_something")--Yes, I did.
		else
			clonedConversation:addOption("@conversation/seans_historian:s_9c1a8dd7","keep_looking") --No, let me keep looking.
		end
	elseif (screenID == "found_something") then
		self:foundSomething(pPlayer)
		CreatureObject(pPlayer):removeScreenPlayState(4,"bestine_history_quest")
		CreatureObject(pPlayer):setScreenPlayState(8,"bestine_history_quest")
	end
	
	return pConvScreen
end

function seansHistorianConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	
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