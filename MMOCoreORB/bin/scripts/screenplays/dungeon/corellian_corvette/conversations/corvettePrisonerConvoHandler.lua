local ObjectManager = require("managers.object.object_manager")

corvettePrisonerConvoHandler = conv_handler:new {}

function corvettePrisonerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	return convoTemplate:getScreen("not_rescued")
end