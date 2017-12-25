local ObjectManager = require("managers.object.object_manager")

bestineRumorConvoHandler = conv_handler:new {}

function bestineRumorConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()

	if (not BestineElection:isElectionEnabled() or curPhase == BestineElection.OFFICE_PHASE) then
		return convoTemplate:getScreen("init_office_phase")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end
