local ObjectManager = require("managers.object.object_manager")

victorQuestnCantinaConvoHandler = Object:new {
		themePark = nil
}


function victorQuestnCantinaConvoHandler:hasEnoughMoney(pPlayer)
if (pPlayer == nil) then
  return false
end

	if(CreatureObject(pPlayer):getCashCredits() >= 200) then
		return true
	end
	return false
end

function victorQuestnCantinaConvoHandler:alreadyHasEvidence(pPlayer)
  if (pPlayer == nil) then
    return false
  end
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	return getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_dseal.iff" , true)
end

function victorQuestnCantinaConvoHandler:hasNoRoomVar(pPlayer)
 if (pPlayer == nil) then
    return false
  end
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	playerCampaign = readData(playerID..":bestine_election:victor_cantina_noroom")
	return (playerCampaign ~= nil) and (playerCampaign >= electionNum)
end



function victorQuestnCantinaConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if BestineElectionScreenPlay:getCurrentPhase() == 1 then
	if seanTrenwellConvoHandler:seanNegQuest(pPlayer) then
		if victorQuestnCantinaConvoHandler:alreadyHasEvidence(pPlayer) then
			return convoTemplate:getScreen("already_has_evidence")
		elseif victorQuestnCantinaConvoHandler:hasNoRoomVar(pPlayer) then
			return convoTemplate:getScreen("noroom_returned")
		elseif seanTrenwellConvoHandler:hasNQuestVar(pPlayer) then
			return convoTemplate:getScreen("convo_start")
		end
	end
	end
	return convoTemplate:getScreen("no_business")
end


function victorQuestnCantinaConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	
	if (screenID == "convo_start") then
		if self:hasEnoughMoney(conversingPlayer) then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_51ac4991","no_room") --Hmm. Here you go.
			else
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_51ac4991","heres_paper") --Hmm. Here you go.
			end
		else
			clonedConversation:addOption("@conversation/victor_questn_cantina:s_19d90991","no_money") -- I don't have that kind of money.
		end
	elseif (screenID == "heres_paper") then
		CreatureObject(conversingPlayer):subtractCashCredits(200)
		CreatureObject(conversingPlayer):sendSystemMessage("You successfully make a payment of 200 credits.")
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			giveItem(pInventory,"object/tangible/loot/quest/victor_questn_dseal.iff", -1)
			deleteData(playerID..":bestine_election:victor_cantina_noroom")
		end

	elseif (screenID == "noroom_returned") then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/victor_questn_cantina:s_62bf3631","havent_made_room") --No, I haven't made room yet.
			else
			clonedConversation:addOption("@conversation/victor_questn_cantina:s_90ec63e0","heres_paper") --Yes, I do.
		end
	elseif (screenID == "no_room") then
		writeData(playerID..":bestine_election:victor_cantina_noroom",electionNum)
	end
	return conversationScreen
end

function victorQuestnCantinaConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
