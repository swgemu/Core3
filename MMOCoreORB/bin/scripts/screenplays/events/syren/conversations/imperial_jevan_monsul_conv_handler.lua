local ObjectManager = require("managers.object.object_manager")

imperialJevanMonsulConvoHandler = conv_handler:new {}

function imperialJevanMonsulConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "s_169" then
		CreatureObject(pPlayer):sendSystemMessage("GoTo RORI!!!!!")
	end

	return pConvScreen
end
