local ObjectManager = require("managers.object.object_manager")

corvetteRescueConvoHandler = conv_handler:new {}

function corvetteRescueConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	return convoTemplate:getScreen("convo_start")
end
