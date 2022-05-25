local ObjectManager = require("managers.object.object_manager")

coa3LeiaConvoHandler = conv_handler:new {}

function coa3LeiaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil) then
		return convoTemplate:getScreen("init_default")
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)





	return convoTemplate:getScreen("init_default")
end

function coa3LeiaConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	local append = "_w"

	if (CriesOfAlderaan:getWinningFaction() == FACTIONIMPERIAL) then
		append = "_l"
	end



	return pConvScreen
end