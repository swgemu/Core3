local ObjectManager = require("managers.object.object_manager")

coa3VeersConvoHandler = conv_handler:new {}

function coa3VeersConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil) then
		return convoTemplate:getScreen("init_default")
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)





	return convoTemplate:getScreen("init_default")
end

function coa3VeersConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local faction = CreatureObject(pNpc):getFaction()
	local factionString = Coa3Screenplay:getFactionString(pNpc)
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)
	local playerID = SceneObject(pPlayer):getObjectID()
	local winningFaction = tonumber(CriesOfAlderaan:getWinningFaction())

	local append = "_w"

	if (winningFaction == FACTIONIMPERIAL) then
		append = "_l"
	end



	return pConvScreen
end