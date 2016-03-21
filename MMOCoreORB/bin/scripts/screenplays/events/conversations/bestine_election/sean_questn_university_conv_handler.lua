local ObjectManager = require("managers.object.object_manager")

seanQuestnUniversityConvoHandler = Object:new {
		themePark = nil
}

function seanQuestnUniversityConvoHandler:alreadyHasEvidence(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	return (pInventory ~= nil) and (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questn_gpapers.iff" , true))
end

function seanQuestnUniversityConvoHandler:hasNoRoomVar(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	playerCampaign = readData(playerID..":bestine_election:sean_university_noroom")
	return (playerCampaign ~= nil) and (playerCampaign >= electionNum)
end


function seanQuestnUniversityConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local playerID = CreatureObject(pPlayer):getObjectID()
	if BestineElectionScreenPlay:getCurrentPhase() == 1 then
		if seanQuestnUniversityConvoHandler:alreadyHasEvidence(pPlayer) then
			return convoTemplate:getScreen("already_has_evidence")
		elseif seanQuestnUniversityConvoHandler:hasNoRoomVar(pPlayer) then
			return convoTemplate:getScreen("noroom_returned")
		elseif victorVisalisConvoHandler:hasNQuestVar(pPlayer) then
			return convoTemplate:getScreen("convo_start")
		end
	end
	return convoTemplate:getScreen("no_business")
end

function seanQuestnUniversityConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local playerID = CreatureObject(conversingPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()

	if (screenID == "convo_start2") then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_questn_university:s_5ec23736","no_room")
		else
			clonedConversation:addOption("@conversation/sean_questn_university:s_5ec23736","heres_paper")
		end

	elseif (screenID == "heres_paper") then
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			giveItem(pInventory,"object/tangible/loot/quest/sean_questn_gpapers.iff", -1)
			deleteData(playerID..":bestine_election:victor_university_noroom")
		end
	elseif (screenID == "noroom_returned") then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_questn_university:s_7e78bf8f","no_inventory_space")
		else
			clonedConversation:addOption("@conversation/sean_questn_university:s_7e78bf8f","heres_paper")
		end
		clonedConversation:addOption("@conversation/sean_questn_university:s_7291fe2e","havent_made_room")

	elseif (screenID == "no_room") then
		writeData(playerID..":bestine_election:sean_university_noroom",electionNum)
	end
	return conversationScreen
end

function seanQuestnUniversityConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
