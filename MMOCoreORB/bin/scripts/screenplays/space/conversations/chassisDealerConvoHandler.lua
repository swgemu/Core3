local Logger = require("utils.logger")
require("utils.helpers")

chassisDealerConvoHandler = conv_handler:new {}

function chassisDealerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()

	local screenID = screen:getScreenID()
	local suiManager = LuaSuiManager()

	if (ChassisDealer.CHASSIS_DEBUG) then
		print("chassisDealerConvoHandler:runScreenHandlers -- Screen ID: " .. screenID)
	end

	-- Ship Chassis Purchase
	if (screenID == "chassis_dealer_buy_chassis") then
		local shipOptions = ChassisDealer:getValidBlueprints(pPlayer)

		if (#shipOptions <= 0) then
			local clonedConversation = LuaConversationScreen(pConvScreen)

			clonedConversation:setDialogTextTO("@chassis_npc:no_deeds")

			return pConvScreen
		end

		suiManager:sendListBox(pNpc, pPlayer, "@chassis_npc:buy_ship_title", "@chassis_npc:buy_ship_prompt", 2, "@cancel", "", "@ok", "chassisDealerConvoHandler", "purchaseChassisConfirmation", 32, shipOptions)
	-- Ship Components Sale
	elseif (screenID == "chassis_dealer_sell_components") then
		local componentTable = ChassisDealer:getShipComponents(pPlayer)

		if (#componentTable <= 0) then
			local clonedConversation = LuaConversationScreen(pConvScreen)
			clonedConversation:setDialogTextTO("@conversation/chassis_npc:s_3310c404")

			clonedConversation:setDialogTextTO("@chassis_npc:no_deeds")

			return pConvScreen
		end

		suiManager:sendListBox(pNpc, pPlayer, "@chassis_npc:buy_ship_title", "@chassis_npc:buy_ship_prompt", 2, "@cancel", "", "@ok", "chassisDealerConvoHandler", "sellComponentCallback", 32, componentTable)
	end

	return pConvScreen
end

function chassisDealerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil or pConvTemplate == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local npcID = SceneObject(pNpc):getObjectID()

	return convoTemplate:getScreen("chassis_dealer_greeting")
end

function chassisDealerConvoHandler:sellComponentCallback(pPlayer, pSui, eventIndex, arg0)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	--local suiManager = LuaSuiManager()
	local selection = arg0 + 1

	local componentTable = ChassisDealer:getValidBlueprints(pPlayer)
	local componentID = componentTable[selection][2]

	if (ChassisDealer.CHASSIS_DEBUG) then
		print("sellComponentCallback - Selected Component ID: " .. componentID)
	end

	local suiBox = LuaSuiBox(pSui)
	local pNpc = suiBox:getUsingObject()

	if (pNpc == nil) then
		return
	end




	-- TODO - Finish component sale


end

function chassisDealerConvoHandler:purchaseChassisConfirmation(pPlayer, pSui, eventIndex, arg0)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local suiManager = LuaSuiManager()
	local selection = arg0 + 1

	local blueprintTable = ChassisDealer:getValidBlueprints(pPlayer)

	local chassisName = blueprintTable[selection][1]
	local chassisID = blueprintTable[selection][2]

	local pBlueprint = getSceneObject(chassisID)

	if (pBlueprint == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@chassis_npc:failed")
		return
	end

	if (ChassisDealer.CHASSIS_DEBUG) then
		print("purchaseChassisConfirmation - Selected BluePrint: " .. chassisName .. " Chassis Object ID: " .. chassisID)
	end

	local suiBox = LuaSuiBox(pSui)
	local pNpc = suiBox:getUsingObject()

	if (pNpc == nil) then
		return
	end

	writeData(SceneObject(pPlayer):getObjectID() .. ":ChassisDealer:BlueprintID:", chassisID)

	if (ChassisDealer:checkCertification(pPlayer, SceneObject(pBlueprint):getObjectName())) then
		suiManager:sendMessageBox(pNpc, pPlayer, "@chassis_npc:confirm_transaction", "@chassis_npc:can_use", "@chassis_npc:btn_buy", "chassisDealerConvoHandler", "purchaseChassis")
	else
		local noCertMsg = LuaStringIdChatParameter("@chassis_npc:not_certified")
		spatialChat(pNpc, noCertMsg:_getObject())

		suiManager:sendMessageBox(pNpc, pPlayer, "@chassis_npc:confirm_transaction", "@chassis_npc:cannot_use", "@chassis_npc:btn_buy", "chassisDealerConvoHandler", "purchaseChassis")
	end
end

function chassisDealerConvoHandler:purchaseChassis(pPlayer, pSui, eventIndex, arg0)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local chassisID = readData(playerID .. ":ChassisDealer:BlueprintID:")
	deleteData(playerID .. ":ChassisDealer:BlueprintID:")

	local pBlueprint = getSceneObject(chassisID)

	if (pBlueprint == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@chassis_npc:failed")
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (pSui == nil or cancelPressed) then
		return
	end

	if (ChassisDealer.CHASSIS_DEBUG) then
		local chassisName = SceneObject(pBlueprint):getObjectName()
		print("purchaseChassis -- for chassis name: " .. chassisName)
	end

	local suiBox = LuaSuiBox(pSui)
	local pNpc = suiBox:getUsingObject()

	if (pNpc == nil or not SceneObject(pNpc):isCreatureObject()) then
		return
	end

	-- Generates the Deed, sets values, deducts credits and transfers to player
	if (generateShipDeed(pPlayer, pBlueprint, pNpc)) then
		local boughtMsg = LuaStringIdChatParameter("@chassis_npc:bought_chassis")
		spatialChat(pNpc, boughtMsg:_getObject())
	end
end
