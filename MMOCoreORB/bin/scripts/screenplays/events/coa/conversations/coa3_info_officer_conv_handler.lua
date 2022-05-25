local ObjectManager = require("managers.object.object_manager")

coa3InfoOfficerConvoHandler = conv_handler:new {}

function coa3InfoOfficerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local stateKey = Coa3Screenplay:getStateKey(CreatureObject(pNpc):getFaction())
	printf("Npc faction: " .. CreatureObject(pNpc):getFaction() .. "\n")
	printf("statekey: " .. stateKey .. ", state: " .. CriesOfAlderaan:getState(pPlayer, stateKey) .. "\n")

	if (CriesOfAlderaan:getState(pPlayer, stateKey) >= Coa3Screenplay.PRE_INFO_OFFICER) then
		return convoTemplate:getScreen("init_sent_by_coordinator")
	else
		return convoTemplate:getScreen("init_default")
	end
end

function coa3InfoOfficerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local stateKey = Coa3Screenplay:getStateKey(CreatureObject(pNpc):getFaction())

	if (screenID == "situation_is_bad" or screenID == "situation_is_good") then
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.PRE_RETURN)
	end

	return pConvScreen
end
