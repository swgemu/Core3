local ObjectManager = require("managers.object.object_manager")

bestineElectionConvoHandler = conv_handler:new {
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

function bestineElectionConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
--function bestineElectionConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local npcID = self:getNpcName(pNpc)

	if BestineElectionScreenPlay:getCurrentPhase() == 1 then

		if (npcID == "likyna" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Victor")) or (npcID == "siyan" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Sean")) then
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


function bestineElectionConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
--function bestineElectionConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return pConvScreen
end
