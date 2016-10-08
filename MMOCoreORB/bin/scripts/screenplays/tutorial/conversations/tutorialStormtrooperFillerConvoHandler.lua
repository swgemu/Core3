local ObjectManager = require("managers.object.object_manager")

tutorialStormtrooperFillerConvoHandler = conv_handler:new {}

function tutorialStormtrooperFillerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "moveAlong") then
		CreatureObject(pNpc):doAnimation("wave_on_directing")
	end

	return pConvScreen
end

function tutorialStormtrooperFillerConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption, pNpc)
	return self:getInitialScreen(pPlayer, pNpc, pConvTemplate)
end
