local ObjectManager = require("managers.object.object_manager")

corvetteRepairDroidConvoHandler = conv_handler:new {}

function corvetteRepairDroidConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local pCorvette = SceneObject(SceneObject(pPlayer):getParent()):getParent()
	local droidFixed = readData(BuildingObject(pCorvette):getObjectID() .. ":repairDroidComplete")

	if (droidFixed == 1) then
		return convoTemplate:getScreen("pdroid_excellent")
	else
		return convoTemplate:getScreen("pdroid_instructions")
	end
end
