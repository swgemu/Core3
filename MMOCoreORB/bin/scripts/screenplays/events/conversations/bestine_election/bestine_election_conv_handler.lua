local ObjectManager = require("managers.object.object_manager")

bestineElectionConvoHandler = Object:new {
	}

function bestineElectionConvoHandler:getNpcName(pNpc)
	if (pNpc == nil) then
		return nil
	end
	local tmpstr = string.sub(SceneObject(pNpc):getTemplateObjectPath(),0,-5)
	local start = 0
	local splitStart,splitEnd = string.find(tmpstr, "_", start)
	while splitStart do
		start = splitEnd+1
		splitStart, splitEnd = string.find(tmpstr, "_", start)
	end
	return string.sub(tmpstr,start)
end

function bestineElectionConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local npcID = self:getNpcName(pNpc)

	if BestineElectionScreenPlay:getCurrentPhase() == 1 then
		if (npcID == "likyna") and (victorVisalisConvoHandler:victorNegQuest(pPlayer)) or (npcID == "siyan") and (seanTrenwellConvoHandler:seanNegQuest(pPlayer)) then
			return convoTemplate:getScreen("nquest_start")
		elseif (npcID == "likyna" and BestineElectionScreenPlay:joinedCampaign(pPlayer, "Victor")) then
			return convoTemplate:getScreen("in_campaign")
		elseif (npcID == "siyan" and BestineElectionScreenPlay:joinedCampaign(pPlayer, "Sean")) then
			return convoTemplate:getScreen("in_campaign")
		elseif (string.find(npcID,"capitol",1) ~= nil or string.find(npcID,"rumor",1) ~= nil) then
			return convoTemplate:getScreen("election_started")
		end
	elseif BestineElectionScreenPlay:getCurrentPhase() == 2 then
		if (npcID == "likyna" or npcID == "siyan") then
			return convoTemplate:getScreen("next_election")
		elseif (string.find(npcID,"capitol",1) ~= nil or string.find(npcID,"rumor",1) ~= nil) then
			return convoTemplate:getScreen("election_ended")
		end
	end
	return convoTemplate:getScreen("default_greeting")
end

function bestineElectionConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function bestineElectionConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
