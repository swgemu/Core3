local ObjectManager = require("managers.object.object_manager")

neutralTylaJinnConvoHandler = conv_handler:new {}

function neutralTylaJinnConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "s_390" then
		CreatureObject(pPlayer):sendSystemMessage("GoTo RORI!!!!!")
	end

	return pConvScreen
end
