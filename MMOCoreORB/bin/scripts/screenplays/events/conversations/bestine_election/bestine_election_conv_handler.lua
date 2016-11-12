local ObjectManager = require("managers.object.object_manager")

bestineElectionConvoHandler = conv_handler:new {
}

function bestineElectionConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local npcID = SceneObject(pNpc):getTemplateObjectPath()

	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return convoTemplate:getScreen("default_greeting")
	end

	if BestineElectionScreenPlay:getCurrentPhase() == 1 then
		if (string.find(npcID, "likyna", 1) ~= nil and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "victor")) or
			(string.find(npcID, "siyan", 1) ~= nil and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "sean")) then
			return convoTemplate:getScreen("nquest_start")
		elseif (string.find(npcID, "likyna", 1) ~= nil) and BestineElectionScreenPlay:joinedCampaign(pPlayer, "victor") then
			return convoTemplate:getScreen("in_campaign")
		elseif (string.find(npcID, "siyan", 1) ~= nil) and BestineElectionScreenPlay:joinedCampaign(pPlayer, "sean") then
			return convoTemplate:getScreen("in_campaign")
		elseif (string.find(npcID, "capitol", 1) ~= nil or string.find(npcID, "rumor", 1) ~= nil) then
			return convoTemplate:getScreen("election_started")
		end
	elseif BestineElectionScreenPlay:getCurrentPhase() == 2 then
		if (string.find(npcID, "likyna", 1) ~= nil or string.find(npcID, "siyan", 1) ~= nil) then
			return convoTemplate:getScreen("next_election")
		end
	end

	return convoTemplate:getScreen("default_greeting")
end


function bestineElectionConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	return pConvScreen
end
