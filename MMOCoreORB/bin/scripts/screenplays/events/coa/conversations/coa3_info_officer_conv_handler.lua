local ObjectManager = require("managers.object.object_manager")

coa3InfoOfficerConvoHandler = conv_handler:new {}

function coa3InfoOfficerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local creatureFaction = CreatureObject(pNpc):getFaction()
	local stateKey = Coa3Screenplay:getStateKey(creatureFaction)
	local winningFaction = tonumber(CriesOfAlderaan:getWinningFaction())

	local append = "_w"

	if (winningFaction ~= creatureFaction) then
		append = "_l"
	end

	local state = CriesOfAlderaan:getState(pPlayer, stateKey)

	if (state == Coa3Screenplay.PRE_INFO_OFFICER) then
		return convoTemplate:getScreen("init_sent_by_coordinator" .. append)
	elseif (state == Coa3Screenplay.PRE_RETURN) then
		return convoTemplate:getScreen("sent_briefings" .. append)
	else
		return convoTemplate:getScreen("init_default")
	end
end

function coa3InfoOfficerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local stateKey = Coa3Screenplay:getStateKey(CreatureObject(pNpc):getFaction())

	if (screenID == ("situation_is_bad_l") or screenID == ("situation_is_good_w")) then
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.PRE_RETURN)
	end

	return pConvScreen
end
