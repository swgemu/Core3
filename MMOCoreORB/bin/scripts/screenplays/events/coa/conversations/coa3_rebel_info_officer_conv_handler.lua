local ObjectManager = require("managers.object.object_manager")

coa3RebelInfoOfficerConvoHandler = conv_handler:new {}

function coa3RebelInfoOfficerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CriesOfAlderaan:getState(pPlayer, "rebel_coa3") >= Coa3Screenplay.M1_INFO_OFFICER) then
		return convoTemplate:getScreen("init_sent_by_coordinator")
	else
		return convoTemplate:getScreen("init_default")
	end
end

function coa3RebelInfoOfficerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "situation_is_good" and CriesOfAlderaan:getState(pPlayer, "rebel_coa3") == Coa3Screenplay.M1_INFO_OFFICER then
		CriesOfAlderaan:setState(pPlayer, "rebel_coa3", Coa3Screenplay.M1_RETURN)
	end

	return pConvScreen
end
