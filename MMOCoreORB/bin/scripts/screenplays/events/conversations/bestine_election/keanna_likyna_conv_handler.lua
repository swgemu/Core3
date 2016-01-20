local ObjectManager = require("managers.object.object_manager")

keannaLikynaConvoHandler = Object:new {
		themePark = nil
}


function keannaLikynaConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function keannaLikynaConvoHandler:hasCampaignVar(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:VictorCampaign"))
		if  (playerCampaign == electionNum) then
			return true
		end
	end
	return false
end

function keannaLikynaConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	
	if BestineElectionScreenPlay:getCurrentPhase() == 1 then
		if (self:hasCampaignVar(pPlayer)) then
			return convoTemplate:getScreen("in_campaign")
		end
		
		if victorVisalisConvoHandler:hasNQuestVar(pPlayer) then
			return convoTemplate:getScreen("nquest_start")
		end
		return convoTemplate:getScreen("no_election")
	else
		return convoTemplate:getScreen("next_election")
	end
end
function keannaLikynaConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	return conversationScreen
end

function keannaLikynaConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

