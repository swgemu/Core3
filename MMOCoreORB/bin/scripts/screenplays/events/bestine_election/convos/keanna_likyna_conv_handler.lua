local ObjectManager = require("managers.object.object_manager")

keannaLikynaConvoHandler = conv_handler:new {}

function keannaLikynaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()

	if (BestineElection:hasJoinedCampaign(pPlayer, BestineElection.VICTOR)) then
		return convoTemplate:getScreen("init_joined_campaign")
	elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_QUEST) == BestineElection.SEAN_RIVAL_QUEST_ACCEPTED) then
		return convoTemplate:getScreen("init_on_rival_quest")
	elseif (curPhase == BestineElection.OFFICE_PHASE) then
		return convoTemplate:getScreen("init_office_phase")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end
