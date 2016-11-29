local Logger = require("utils.logger")
require("utils.helpers")
local ChassisDealer = require("screenplays.space.chassis_dealer")

chassis_dealer_conv_handler = conv_handler:new {}

function chassis_dealer_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if (screenID == "chassis_dealer_buy_chassis") then
		local suiManager = LuaSuiManager()
		local options = ChassisDealer:getValidBlueprints(pPlayer)

		if (#options <= 0) then
			pConvScreen = screen:cloneScreen()
			local clonedConversation = LuaConversationScreen(pConvScreen)
			clonedConversation:setDialogTextTO("@chassis_npc:no_deeds")
			return pConvScreen
		end
		suiManager:sendListBox(pPlayer, pPlayer, "@chassis_npc:buy_ship_title", "@chassis_npc:buy_ship_prompt", 2, "@cancel", "", "@ok", "chassis_dealer_conv_handler", "purchaseChassisConfirmation", 32, options)
	elseif (screenID == "chassis_dealer_sell_components") then
		-- TODO: Get looted components...
		pConvScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(pConvScreen)
		clonedConversation:setDialogTextTO("@conversation/chassis_npc:s_3310c404")
		return pConvScreen
	end

	return pConvScreen
end

function chassis_dealer_conv_handler:purchaseChassisConfirmation(pPlayer, pSui, eventIndex, arg0)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
	local suiManager = LuaSuiManager()
	local selection = arg0 + 1

	-- TODO CHECKS: Too many ships, no money, too many POB ships, inventory full.

	local possibleBlueprints = ChassisDealer:getValidBlueprints(pPlayer)
	local selectedBluePrint = possibleBlueprints[selection][1]
	local path = ChassisDealer:getPathByName(selectedBluePrint)

	if (path == nil or pInventory == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@chassis_npc:failed")
	else
		local pBlueprint = getContainerObjectByTemplate(pInventory, path, true)
		suiManager:sendMessageBox(pBlueprint, pPlayer, "@chassis_npc:confirm_transaction", "@chassis_npc:can_use", "@chassis_npc:btn_buy", "chassis_dealer_conv_handler", "purchaseChassis")
	end

	-- TODO: Add in certs...
end

function chassis_dealer_conv_handler:purchaseChassis(pPlayer, pSui, eventIndex, arg0)
	local cancelPressed = (eventIndex == 1)

	if (pPlayer == nil or pSui == nil or cancelPressed) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()

	if (pUsingObject == nil) then
		return
	end

	local deedPath = SceneObject(pUsingObject):getTemplateObjectPath()
	local chassis = ChassisDealer:getChassisFromBlueprint(deedPath)

	if (chassis ~= nil) then
		local pChassis = giveItem(pInventory, chassis, -1)

		if (pChassis ~= nil) then
			SceneObject(pChassis):sendTo(pPlayer)
			CreatureObject(pPlayer):sendSystemMessage("@chassis_npc:bought_chassis")
		end

		SceneObject(pUsingObject):destroyObjectFromWorld()
		SceneObject(pUsingObject):destroyObjectFromDatabase()
	end
end
