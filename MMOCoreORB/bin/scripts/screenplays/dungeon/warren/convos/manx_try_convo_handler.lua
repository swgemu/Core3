local ObjectManager = require("managers.object.object_manager")

ManxTryConversationHandler = conv_handler:new {}

function ManxTryConversationHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (readData("warren:reactorOverride") == 1) then
		return convoTemplate:getScreen("researcher_2")
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local pRod1 = getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_core_control_rod_s01.iff", true)
		local pRod2 = getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_core_control_rod_s02.iff", true)

		if (pRod1 ~= nil) and (pRod2 ~= nil) then
			return convoTemplate:getScreen("researcher_3")
		end
	end

	return convoTemplate:getScreen("researcher_start")
end
