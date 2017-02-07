local ObjectManager = require("managers.object.object_manager")

SuiFsCrafting1Analyzer = {
	terminalComponents = { "@quest_item_n:fs_craft_puzzle_config_processor", "@quest_item_n:fs_craft_puzzle_gyro_receiver",
		"@quest_item_n:fs_craft_puzzle_signal_amp", "@quest_item_n:fs_craft_puzzle_solid_state_array" },

	componentTemplates =  { "object/tangible/item/quest/force_sensitive/fs_craft_puzzle_config_processor.iff", "object/tangible/item/quest/force_sensitive/fs_craft_puzzle_gyro_receiver.iff",
		"object/tangible/item/quest/force_sensitive/fs_craft_puzzle_signal_amp.iff", "object/tangible/item/quest/force_sensitive/fs_craft_puzzle_solid_state_array.iff" },

	componentSchematics = { "object/draft_schematic/item/quest_item/fs_craft_puzzle_config_processor.iff", "object/draft_schematic/item/quest_item/fs_craft_puzzle_gyro_receiver.iff",
		"object/draft_schematic/item/quest_item/fs_craft_puzzle_signal_amp.iff", "object/draft_schematic/item/quest_item/fs_craft_puzzle_solid_state_array.iff"};
}

function SuiFsCrafting1Analyzer:openAnalyzer(pPlayer, pAnalyzer)
	if (pPlayer == nil or pAnalyzer == nil) then
		return
	end

	-- Run function once to set values if they do not exist when sui is opened
	local analyzed = self:getAnalyzedTable(pPlayer)

	local sui = SuiListBox.new("SuiFsCrafting1Analyzer", "analyzerCallback")
	sui.setTitle("@quest/force_sensitive/fs_crafting:sui_analyzer_title")
	sui.setPrompt("@quest/force_sensitive/fs_crafting:sui_analyzer_prompt0")
	sui.setForceCloseDistance(10)
	sui.setTargetNetworkId(SceneObject(pAnalyzer):getObjectID())

	sui.add("@quest/force_sensitive/fs_crafting:sui_analyzer_analyze_component", "")
	sui.add("@quest/force_sensitive/fs_crafting:sui_analyzer_get_schematic", "")

	sui.sendTo(pPlayer)
end

function SuiFsCrafting1Analyzer:noCallback(pPlayer, pSui, eventIndex)
end

function SuiFsCrafting1Analyzer:analyzerCallback(pPlayer, pSui, eventIndex, rowIndex)
	if (eventIndex == 1) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local analyzerID = suiPageData:getTargetNetworkId()
	local pAnalyzer = getSceneObject(analyzerID)

	if (pAnalyzer == nil) then
		printLuaError("SuiFsCrafting1Analyzer:analyzerCallback, pAnalyzer nil.")
		return
	end

	rowIndex = tonumber(rowIndex)

	if (rowIndex == -1) then
		self:openAnalyzer(pPlayer, pAnalyzer)
		return
	elseif (rowIndex == 0) then
		self:doAnalyzeComponent(pPlayer, pAnalyzer)
	elseif (rowIndex == 1) then
		self:doAccessSchematic(pPlayer, pAnalyzer)
	end
end

function SuiFsCrafting1Analyzer:doAnalyzeComponent(pPlayer, pAnalyzer)
	local analyzed = self:getAnalyzedTable(pPlayer)
	local componentsInInv = { }

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error locating inventory, please try again.")
		return
	end

	for i = 1, 4, 1 do
		local pComponent = getContainerObjectByTemplate(pInventory, self.componentTemplates[i], true)

		if (analyzed[i] == 0 and pComponent ~= nil) then
			table.insert(componentsInInv, i)
		end
	end

	if (#componentsInInv == 0) then
		local sui = SuiMessageBox.new("SuiFsCrafting1Analyzer", "noCallback")
		sui.setTitle("@quest/force_sensitive/fs_crafting:sui_analyzer_title")
		sui.setPrompt("@quest/force_sensitive/fs_crafting:sui_analyzer_no_comp")
		sui.setTargetNetworkId(SceneObject(pAnalyzer):getObjectID())
		sui.setForceCloseDistance(10)
		sui.sendTo(pPlayer)
		return
	end

	local sui = SuiListBox.new("SuiFsCrafting1Analyzer", "analyzeComponentCallback")
	sui.setTitle("@quest/force_sensitive/fs_crafting:sui_analyzer_title")
	sui.setPrompt("@quest/force_sensitive/fs_crafting:sui_analyzer_prompt1")
	sui.setForceCloseDistance(10)
	sui.setTargetNetworkId(SceneObject(pAnalyzer):getObjectID())

	for i = 1, #componentsInInv, 1 do
		sui.add(self.terminalComponents[componentsInInv[i]], "")
	end

	sui.sendTo(pPlayer)
end

function SuiFsCrafting1Analyzer:getAnalyzedTable(pPlayer)
	local analyzed = { 0, 0, 0, 0 }

	for i = 1, 4, 1 do
		local tempVal = readScreenPlayData(pPlayer, "SuiFsCrafting1Analyzer", "componentAnalyzed" .. i)

		if (tempVal == "") then
			writeScreenPlayData(pPlayer, "SuiFsCrafting1Analyzer", "componentAnalyzed" .. i, "0")
			tempVal = "0"
		end

		analyzed[i] = tonumber(tempVal)
	end

	return analyzed
end

function SuiFsCrafting1Analyzer:analyzeComponentCallback(pPlayer, pSui, eventIndex, rowIndex)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (eventIndex == 1) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local analyzerID = suiPageData:getTargetNetworkId()
	local pAnalyzer = getSceneObject(analyzerID)

	if (pAnalyzer == nil) then
		printLuaError("SuiFsCrafting1Analyzer:analyzeComponentCallback, pAnalyzer nil.")
		return
	end

	if (rowIndex == -1) then
		self:doAnalyzeComponent(pPlayer, pAnalyzer)
		return
	end

	rowIndex = rowIndex + 1

	local analyzed = self:getAnalyzedTable(pPlayer)
	local componentsInInv = { }

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error locating inventory, please try again.")
		self:doAnalyzeComponent(pPlayer, pAnalyzer)
		return
	end

	for i = 1, 4, 1 do
		local pComponent = getContainerObjectByTemplate(pInventory, self.componentTemplates[i], true)

		if (analyzed[i] == 0 and pComponent ~= nil) then
			table.insert(componentsInInv, pComponent)
		end
	end

	local pComponent = componentsInInv[rowIndex]

	if (pComponent == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error getting component, please report.\n")
		self:doAnalyzeComponent(pPlayer, pAnalyzer)
		return
	end

	local compTemplate = SceneObject(pComponent):getTemplateObjectPath()
	local componentNum = 0

	for i = 1, 4, 1 do
		if (compTemplate == self.componentTemplates[i]) then
			componentNum = i
		end
	end

	if (componentNum == 0) then
		CreatureObject(pPlayer):sendSystemMessage("Error identifying component, please report.")
		self:doAnalyzeComponent(pPlayer, pAnalyzer)
		return
	end

	writeScreenPlayData(pPlayer, "SuiFsCrafting1Analyzer", "componentAnalyzed" .. componentNum, 1)
	SceneObject(pComponent):destroyObjectFromWorld()
	SceneObject(pComponent):destroyObjectFromDatabase()
	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:phase1_msg_component_analyzed")

	PlayerObject(pGhost):addRewardedSchematic(self.componentSchematics[componentNum], 2, 1, true)
end

function SuiFsCrafting1Analyzer:doAccessSchematic(pPlayer, pAnalyzer)
	local analyzed = self:getAnalyzedTable(pPlayer)

	local totalAnalyzed = 0

	for i = 1, 4, 1 do
		if (analyzed[i] == 1) then
			totalAnalyzed = totalAnalyzed + 1
		end
	end

	if (totalAnalyzed == 0) then
		local sui = SuiMessageBox.new("SuiFsCrafting1Analyzer", "noCallback")
		sui.setTitle("@quest/force_sensitive/fs_crafting:sui_analyzer_title")
		sui.setPrompt("@quest/force_sensitive/fs_crafting:sui_analyzer_no_schematic")
		sui.setTargetNetworkId(SceneObject(pAnalyzer):getObjectID())
		sui.setForceCloseDistance(10)
		sui.sendTo(pPlayer)
		return
	end

	local sui = SuiListBox.new("SuiFsCrafting1Analyzer", "accessSchematicCallback")
	sui.setTitle("@quest/force_sensitive/fs_crafting:sui_analyzer_title")
	sui.setPrompt("@quest/force_sensitive/fs_crafting:sui_analyzer_prompt2")
	sui.setForceCloseDistance(10)
	sui.setTargetNetworkId(SceneObject(pAnalyzer):getObjectID())

	for i = 1, 4, 1 do
		if (analyzed[i] == 1) then
			sui.add(self.terminalComponents[i], "")
		end
	end

	sui.sendTo(pPlayer)
end

function SuiFsCrafting1Analyzer:accessSchematicCallback(pPlayer, pSui, eventIndex, rowIndex)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (eventIndex == 1) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local analyzerID = suiPageData:getTargetNetworkId()
	local pAnalyzer = getSceneObject(analyzerID)

	if (pAnalyzer == nil) then
		printLuaError("SuiFsCrafting1Analyzer:accessSchematicCallback, pAnalyzer nil.")
		return
	end

	if (rowIndex == -1) then
		self:doAccessSchematic(pPlayer, pAnalyzer)
		return
	end

	rowIndex = rowIndex + 1

	local analyzed = self:getAnalyzedTable(pPlayer)
	local schemList = { }

	for i = 1, 4, 1 do
		if (analyzed[i] == 1) then
			table.insert(schemList, i)
		end
	end

	local selectedSchem = self.componentSchematics[schemList[rowIndex]]

	if (PlayerObject(pGhost):hasSchematic(selectedSchem)) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:phase1_msg_schematic_already_loaded")
	else
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:phase1_msg_schematic_loaded")
		PlayerObject(pGhost):addRewardedSchematic(selectedSchem, 2, 1, true)
	end

	self:doAccessSchematic(pPlayer, pAnalyzer)
end
