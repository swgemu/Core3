local ObjectManager = require("managers.object.object_manager")

victorQuestnCapitolConvoHandler = Object:new {
		themePark = nil
}

function victorQuestnCapitolConvoHandler:alreadyHasEvidence(pPlayer)
 if (pPlayer == nil) then
    return false
  end
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	return (pInventory ~= nil) and (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_hlist.iff" , true))
end

function victorQuestnCapitolConvoHandler:hasNoRoomVar(pPlayer)
 if (pPlayer == nil) then
    return false
  end
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	playerCampaign = readData(playerID..":bestine_election:victor_capitol_noroom")
	if (playerCampaign ~= nil) then 
		return (playerCampaign >= electionNum)
	end
	return false
end

function victorQuestnCapitolConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if (BestineElectionScreenPlay:getCurrentPhase()) == 1 then
	if seanTrenwellConvoHandler:seanNegQuest(pPlayer) then
		if victorQuestnCapitolConvoHandler:alreadyHasEvidence(pPlayer) then
			return convoTemplate:getScreen("already_has_evidence")
		elseif victorQuestnCapitolConvoHandler:hasNoRoomVar(pPlayer) then
			return convoTemplate:getScreen("noroom_returned")
		else
			return convoTemplate:getScreen("convo_start")
		end
	end
 end
	if (BestineElectionScreenPlay:getCurrentPhase()) == 2 then
		return convoTemplate:getScreen("no_election")
	end
	return convoTemplate:getScreen("no_business")
end



function victorQuestnCapitolConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local playerID = CreatureObject(conversingPlayer):getObjectID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "convo_start") then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_496168b6","no_room") --i need your help...
		else
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_496168b6","give_list") --i need your help...
		end
		clonedConversation:addOption("@conversation/victor_questn_capitol:s_e50dbfc0","im_leaving") --fine, im leaving
	elseif (screenID == "give_list") then
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			giveItem(pInventory,"object/tangible/loot/quest/victor_questn_hlist.iff", -1)
			deleteData(playerID..":bestine_election:victor_capitol_noroom")
		end
	elseif (screenID == "noroom_returned") then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_62bf3631","noroom_returned_fullinv") --No, I haven't made room yet.
		else
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_90ec63e0","noroom_returned_givelist") --Yes, I do.
		end
	elseif (screenID == "no_room") then
		writeData(playerID..":bestine_election:victor_capitol_noroom",electionNum)
	end
	return conversationScreen
end

function victorQuestnCapitolConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
