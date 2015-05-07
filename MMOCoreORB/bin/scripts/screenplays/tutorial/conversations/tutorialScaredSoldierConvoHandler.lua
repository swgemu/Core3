local ObjectManager = require("managers.object.object_manager")

tutorialScaredSoldierConvoHandler = Object:new { }

function tutorialScaredSoldierConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "need_weapon") then
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")

		if (pInventory == nil) then
			return
		end

		addStartingWeaponsInto(conversingPlayer, pInventory)
		writeData(SceneObject(conversingPlayer):getObjectID() .. ":tutorial:givenWeapon", 1)
		CreatureObject(conversingPlayer):sendSystemMessage("@newbie_tutorial/system_messages:receive_weapon")
	end

	return conversationScreen
end

function tutorialScaredSoldierConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if (readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:givenWeapon") == 1) then
		return convoTemplate:getScreen("intro_repeat")
	else
		return convoTemplate:getScreen("intro")
	end
end

function tutorialScaredSoldierConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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