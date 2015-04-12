local Logger = require("utils.logger")
require("utils.helpers")
local ObjectManager = require("managers.object.object_manager")

local CRYSTAL_OBJECT = "object/tangible/loot/quest/force_sensitive/force_crystal.iff"

elder_conv_handler = Object:new {}

function elder_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption)
	local creature = LuaCreatureObject(pConversingPlayer)
	local convosession = creature:getConversationSession()

	local lastConversationScreen = nil

	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end

	local conversation = LuaConversationTemplate(pConversationTemplate)

	local nextConversationScreen

	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)

		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)

		nextConversationScreen = conversation:getScreen(optionLink)

		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
		else
			nextConversationScreen = conversation:getScreen("cs_jsPlumb_1_1")
		end
	else
		nextConversationScreen = conversation:getScreen("cs_jsPlumb_1_1")
	end
	return nextConversationScreen
end

function elder_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	local screenID = screen:getScreenID()

	local pInv = LuaSceneObject(pConversingPlayer)

	if screenID == "cs_jsPlumb_1_42" then
		-- If they need a crystal...
		ObjectManager.withCreatureObject(pConversingPlayer, function(creatureObject)
			local pInventory = creatureObject:getSlottedObject("inventory")
			local pInvItem = getContainerObjectByTemplate(pInventory, CRYSTAL_OBJECT, true)

			-- If they DO have a crystal.
			if (pInvItem == nil) then
				giveItem(pInventory, CRYSTAL_OBJECT, -1)
			else
				pConversationScreen = conversationTemplate:getScreen("cs_jsPlumb_1_161")
			end
		end)
	end
	return pConversationScreen
end
