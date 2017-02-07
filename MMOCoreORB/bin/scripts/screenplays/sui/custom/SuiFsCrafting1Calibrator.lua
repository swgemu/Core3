local ObjectManager = require("managers.object.object_manager")

SuiFsCrafting1Calibrator = {
	terminalComponents = { "@quest_item_n:fs_craft_puzzle_config_processor", "@quest_item_n:fs_craft_puzzle_gyro_receiver",
		"@quest_item_n:fs_craft_puzzle_signal_amp", "@quest_item_n:fs_craft_puzzle_solid_state_array" },

	componentTemplates =  { "object/tangible/item/quest/force_sensitive/fs_craft_puzzle_config_processor.iff", "object/tangible/item/quest/force_sensitive/fs_craft_puzzle_gyro_receiver.iff",
		"object/tangible/item/quest/force_sensitive/fs_craft_puzzle_signal_amp.iff", "object/tangible/item/quest/force_sensitive/fs_craft_puzzle_solid_state_array.iff" },
}

function SuiFsCrafting1Calibrator:openCalibrator(pPlayer, pTerminal)
	if (pPlayer == nil or pTerminal == nil) then
		return
	end

	local componentsInInv = { }

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error locating inventory, please try again.")
		return
	end

	for i = 1, 4, 1 do
		local pComponent = getContainerObjectByTemplate(pInventory, self.componentTemplates[i], true)

		if (pComponent ~= nil) then
			local componentStatus = LuaFsCraftingComponentObject(pComponent):getStatus()
			if (componentStatus == 0) then
				table.insert(componentsInInv, i)
			end
		end
	end

	if (#componentsInInv == 0) then
		local sui = SuiMessageBox.new("SuiFsCrafting1Calibrator", "noCallback")
		sui.setTitle("@quest/force_sensitive/fs_crafting:sui_calibrator_title")
		sui.setPrompt("@quest/force_sensitive/fs_crafting:sui_calibrator_no_comp")
		sui.setTargetNetworkId(SceneObject(pTerminal):getObjectID())
		sui.setForceCloseDistance(10)
		sui.sendTo(pPlayer)
		return
	end

	local sui = SuiListBox.new("SuiFsCrafting1Calibrator", "calibratorCallback")
	sui.setTitle("@quest/force_sensitive/fs_crafting:sui_calibrator_title")
	sui.setPrompt("@quest/force_sensitive/fs_crafting:sui_calibrator_prompt")
	sui.setForceCloseDistance(10)
	sui.setTargetNetworkId(SceneObject(pTerminal):getObjectID())

	for i = 1, #componentsInInv, 1 do
		sui.add(self.terminalComponents[componentsInInv[i]], "")
	end

	sui.sendTo(pPlayer)
end

function SuiFsCrafting1Calibrator:calibratorCallback(pPlayer, pSui, eventIndex, rowIndex)
	if (eventIndex == 1) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local terminalID = suiPageData:getTargetNetworkId()
	local pTerminal = getSceneObject(terminalID)

	if (pTerminal == nil) then
		printLuaError("SuiFsCrafting1Calibrator:calibratorCallback, pTerminal nil.")
		return
	end

	local componentsInInv = { }

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error locating inventory, please try again.")
		self:openCalibrator(pPlayer, pTerminal)
		return
	end

	for i = 1, 4, 1 do
		local pComponent = getContainerObjectByTemplate(pInventory, self.componentTemplates[i], true)

		if (pComponent ~= nil) then
			local componentStatus = LuaFsCraftingComponentObject(pComponent):getStatus()

			if (componentStatus == 0) then
				table.insert(componentsInInv, pComponent)
			end
		end
	end

	if (rowIndex == -1) then
		self:openCalibrator(pPlayer, pTerminal)
		return
	end

	rowIndex = rowIndex + 1

	local pComponent = componentsInInv[rowIndex]

	if (pComponent == nil) then
		self:openCalibrator(pPlayer, pTerminal)
		return
	end

	local compTemplate = SceneObject(pComponent):getTemplateObjectPath()
	local componentNum = 0

	for i = 1, 4, 1 do
		if (compTemplate == self.componentTemplates[i]) then
			componentNum = i
		end
	end

	if (componentNum == 1) then
		SuiProcessorPuzzle:openPuzzle(pPlayer, pComponent, pTerminal)
	elseif (componentNum == 2) then
		SuiReceiverPuzzle:openPuzzle(pPlayer, pComponent, pTerminal)
	elseif (componentNum == 3) then
		SuiAmpPuzzle:openPuzzle(pPlayer, pComponent, pTerminal)
	elseif (componentNum == 4) then
		SuiArrayPuzzle:openPuzzle(pPlayer, pComponent, pTerminal)
	end
end

function SuiFsCrafting1Calibrator:noCallback(pPlayer, pSui, eventIndex)
end
