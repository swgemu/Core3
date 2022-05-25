local ObjectManager = require("managers.object.object_manager")

coa3InfoOfficerConvoHandler = conv_handler:new {}

function coa3InfoOfficerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local stateKey = Coa3Screenplay:getStateKey(CreatureObject(pNpc):getFaction())

	local creatureFaction = CreatureObject(pNpc):getFaction()

	print("Npc faction: " .. creatureFaction .. " Winning faction = " .. CriesOfAlderaan:getWinningFaction())
	print("statekey: " .. stateKey .. ", state: " .. CriesOfAlderaan:getState(pPlayer, stateKey))

	local append = "_w"

	if (CriesOfAlderaan:getWinningFaction() ~= creatureFaction) then
		append = "_l"
	end

	if (CriesOfAlderaan:getState(pPlayer, stateKey) == Coa3Screenplay.PRE_INFO_OFFICER) then
		return convoTemplate:getScreen("init_sent_by_coordinator" .. append)
	elseif (CriesOfAlderaan:getState(pPlayer, stateKey) == Coa3Screenplay.PRE_RETURN) then
		return convoTemplate:getScreen("sent_briefings" .. append)
	else
		return convoTemplate:getScreen("init_default")
	end
end

function coa3InfoOfficerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local stateKey = Coa3Screenplay:getStateKey(CreatureObject(pNpc):getFaction())

	local append = "_w"

	if (CriesOfAlderaan:getWinningFaction() == FACTIONIMPERIAL) then
		append = "_l"
	end

	if (screenID == ("situation_is_bad" .. append) or screenID == ("situation_is_good" .. append)) then
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.PRE_RETURN)
	end

	return pConvScreen
end
