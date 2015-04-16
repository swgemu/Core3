
local ObjectManager = require("managers.object.object_manager")

local CRYSTAL_OBJECT = "object/tangible/loot/quest/force_sensitive/force_crystal.iff"

elder_conv_handler = Object:new {}

function elder_conv_handler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function elder_conv_handler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("cs_jsPlumb_1_1")
end

function elder_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	local screenID = screen:getScreenID()

	if screenID == "cs_jsPlumb_1_42" then
		-- If they need a crystal...
		ObjectManager.withCreatureObject(pConversingPlayer, function(creatureObject)
			local pInventory = creatureObject:getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pInvItem = getContainerObjectByTemplate(pInventory, CRYSTAL_OBJECT, true)

				-- If they DO NOT have a crystal.
				if (pInvItem == nil) then
					giveItem(pInventory, CRYSTAL_OBJECT, -1)
				else -- They have one already.
					pConversationScreen = conversationTemplate:getScreen("cs_jsPlumb_1_161")
				end
			end
		end)
	end
	return pConversationScreen
end
