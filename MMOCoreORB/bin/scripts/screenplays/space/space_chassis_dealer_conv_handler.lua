local Logger = require("utils.logger")
require("utils.helpers")
local ChassisDealer = require("screenplays.space.chassis_dealer")

chassis_dealer_conv_handler = Object:new{ }

function chassis_dealer_conv_handler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

	return conversationTemplate:getScreen("chassis_dealer_greeting")
end

function chassis_dealer_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)

	local screenID = screen:getScreenID()

	if (screenID == "chassis_dealer_buy_chassis") then
		local suiManager = LuaSuiManager()
		local options = ChassisDealer.getValidBlueprints(pConversingPlayer)

		if (table.getn(options) <= 0) then
			pConversationScreen = screen:cloneScreen()
			local clonedConversation = LuaConversationScreen(pConversationScreen)
			clonedConversation:setDialogTextTO("@chassis_npc:no_deeds")
			return pConversationScreen
		end
		suiManager:sendListBox(pConversingPlayer, pConversingPlayer, "@chassis_npc:buy_ship_title", "@chassis_npc:buy_ship_prompt", 2, "@cancel", "", "@ok", "chassis_dealer_conv_handler", "purchaseChassisConfirmation", options)
	elseif (screenID == "chassis_dealer_sell_components") then
		-- TODO: Get looted components...
		pConversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(pConversationScreen)
		clonedConversation:setDialogTextTO("@conversation/chassis_npc:s_3310c404")
		return pConversationScreen
	end

	return pConversationScreen
end

function chassis_dealer_conv_handler:purchaseChassisConfirmation(pCreature, pSui, cancelPressed, arg0)
	if (cancelPressed) then
		return
	end

	local pInventory = SceneObject(pCreature):getSlottedObject("inventory")
	local suiManager = LuaSuiManager()
	local selection = arg0 + 1

	-- TODO CHECKS: Too many ships, no money, too many POB ships, inventory full.

	local possibleBlueprints = ChassisDealer.getValidBlueprints(pCreature)
	local selectedBluePrint = possibleBlueprints[selection]
	local path = ChassisDealer.getPathByName(selectedBluePrint)

	if (path == nil or pInventory == nil) then
		CreatureObject(pCreature):sendSystemMessage("@chassis_npc:failed")
	else
		local pBlueprint = getContainerObjectByTemplate(pInventory, path, true)
		suiManager:sendMessageBox(pBlueprint, pCreature, "@chassis_npc:confirm_transaction", "@chassis_npc:can_use", "@chassis_npc:btn_buy", "chassis_dealer_conv_handler", "purchaseChassis")
	end

	-- TODO: Add in certs...
end

function chassis_dealer_conv_handler:purchaseChassis(pCreature, pSui, cancelPressed, arg0)
	if (pCreature == nil or pSui == nil) then
		return
	end

	local pInventory = SceneObject(pCreature):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()

	if (pUsingObject == nil) then
		return
	end

	local deedPath = SceneObject(pUsingObject):getTemplateObjectPath()
	local chassis = ChassisDealer.getChassisFromBlueprint(deedPath)

	if (chassis ~= nil) then
		local pChassis = giveItem(pInventory, chassis, -1)

		if (pChassis ~= nil) then
			SceneObject(pChassis):sendTo(pCreature)
			CreatureObject(pCreature):sendSystemMessage("@chassis_npc:bought_chassis")
		end

		SceneObject(pUsingObject):destroyObjectFromWorld()
		SceneObject(pUsingObject):destroyObjectFromDatabase()
	end
end
