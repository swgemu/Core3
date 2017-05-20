local ObjectManager = require("managers.object.object_manager")

corvetteRepairDroidConvoHandler = Object:new{  }

function corvetteRepairDroidConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local pCorvette = SceneObject(SceneObject(pPlayer):getParent()):getParent()
	local droidFixed = readData(BuildingObject(pCorvette):getObjectID() .. ":DroidFixed")

	if (droidFixed == 1) then
		return convoTemplate:getScreen("pdroid_excellent")	
	else
		return convoTemplate:getScreen("pdroid_instructions")
	end
end

function corvetteRepairDroidConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function corvetteRepairDroidConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()

	local pLastConversationScreen = nil

	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)

		return conversationTemplate:getScreen(optionLink)
	end

	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end