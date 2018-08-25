local ObjectManager = require("managers.object.object_manager")

indigoSiyanConvoHandler = conv_handler:new {}

function indigoSiyanConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()

	if (BestineElection:hasJoinedCampaign(pPlayer, BestineElection.SEAN)) then
		return convoTemplate:getScreen("init_joined_sean")
	elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_QUEST) == BestineElection.SEAN_RIVAL_QUEST_ACCEPTED) then
		return convoTemplate:getScreen("init_on_rival_quest")
	elseif (curPhase == BestineElection.OFFICE_PHASE) then
		return convoTemplate:getScreen("init_sean_not_in_office")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end
