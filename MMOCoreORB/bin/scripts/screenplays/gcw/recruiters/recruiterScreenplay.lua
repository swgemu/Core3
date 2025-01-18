local ObjectManager = require("managers.object.object_manager")
includeFile("gcw/recruiters/factionPerkData.lua")

recruiterScreenplay = Object:new {
	allowPveBases = true,
	covertOvertResignTime = 15, -- In Minutes

	minimumFactionStanding = 200,

	factionHashCode = { rebel = 370444368, imperial = 3679112276 },

	errorCodes =  {
		SUCCESS = 0, INVENTORYFULL = 1,  NOTENOUGHFACTION = 2, GENERALERROR = 3, ITEMCOST = 4, INVENTORYERROR = 5,
		TEMPLATEPATHERROR = 6, GIVEERROR = 7, DATAPADFULL = 8, DATAPADERROR = 9, TOOMANYHIRELINGS = 10, SCHEMATICERROR = 11,
	}
}

function recruiterScreenplay:getFactionHashCode(faction)
	if (faction == "rebel") then
		return self.factionHashCode.rebel
	elseif (faction == "imperial") then
		return self.factionHashCode.imperial
	else
		return nil
	end
end

function recruiterScreenplay:getFactionFromHashCode(hash)
	if (hash == self.factionHashCode.rebel) then
		return "rebel"
	elseif (hash == self.factionHashCode.imperial) then
		return "imperial"
	else
		return nil
	end
end

function recruiterScreenplay:getRecruiterFactionHashCode(pNpc)
	local faction = self:getRecruiterFaction(pNpc)
	if (faction == "rebel") then
		return self.factionHashCode.rebel
	elseif (faction == "imperial") then
		return self.factionHashCode.imperial
	else
		return nil
	end
end

function recruiterScreenplay:getRecruiterFaction(pNpc)
	if pNpc == nil then
		return nil
	end

	return self:getFactionFromHashCode(TangibleObject(pNpc):getFaction())
end

function recruiterScreenplay:getRecruiterEnemyFaction(pNpc)
	if (self:getRecruiterFaction(pNpc) == "rebel") then
		return self:getFactionHashCode("imperial")
	elseif (self:getRecruiterFaction(pNpc) == "imperial") then
		return self:getFactionHashCode("rebel")
	end
	return nil
end

function recruiterScreenplay:getRecruiterEnemyFactionHashCode(pNpc)
	if (self:getRecruiterFaction(pNpc) == "rebel") then
		return self.factionHashCode.imperial
	elseif (self:getRecruiterFaction(pNpc) == "imperial") then
		return self.factionHashCode.rebel
	end
	return nil
end

function recruiterScreenplay:grantBribe(pRecruiter, pPlayer, cost, factionPoints)
	if (pRecruiter == nil or pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (CreatureObject(pPlayer):getCashCredits() >= cost) then
		CreatureObject(pPlayer):subtractCashCredits(cost)
		PlayerObject(pGhost):increaseFactionStanding(self:getRecruiterFaction(pRecruiter), factionPoints)
	end
end

function recruiterScreenplay:getFactionDataTable(faction)
	if (faction == "rebel") then
		return rebelRewardData
	elseif (faction == "imperial") then
		return imperialRewardData
	else
		return nil
	end
end

function recruiterScreenplay:getMinimumFactionStanding()
	return self.minimumFactionStanding
end

function recruiterScreenplay:isWeapon(faction, strItem)
	local factionRewardData = self:getFactionDataTable(faction)
	return factionRewardData.weaponsArmor[strItem] ~= nil and factionRewardData.weaponsArmor[strItem].type == factionRewardType.weapon
end

function recruiterScreenplay:isArmor(faction, strItem)
	local factionRewardData = self:getFactionDataTable(faction)
	return factionRewardData.weaponsArmor[strItem] ~= nil and factionRewardData.weaponsArmor[strItem].type == factionRewardType.armor
end


function recruiterScreenplay:isUniform(faction, strItem)
	if faction == "rebel" then
		return false
	end
	local factionRewardData = self:getFactionDataTable(faction)
	return factionRewardData.uniforms[strItem] ~= nil
end

function recruiterScreenplay:isHireling(faction, strItem)
	local factionRewardData = self:getFactionDataTable(faction)
	return factionRewardData.hirelings[strItem] ~= nil
end

function recruiterScreenplay:isFurniture(faction, strItem)
	local factionRewardData = self:getFactionDataTable(faction)
	return factionRewardData.furniture[strItem] ~= nil
end

function recruiterScreenplay:isContainer(faction, strItem)
	local factionRewardData = self:getFactionDataTable(faction)
	return factionRewardData.furniture[strItem] ~= nil and factionRewardData.furniture[strItem].type == factionRewardType.container
end

function recruiterScreenplay:isTerminal(faction, strItem)
	local factionRewardData = self:getFactionDataTable(faction)
	return factionRewardData.furniture[strItem] ~= nil and factionRewardData.furniture[strItem].type == factionRewardType.terminal
end

function recruiterScreenplay:isInstallation(faction, strItem)
	local factionRewardData = self:getFactionDataTable(faction)
	return factionRewardData.installations[strItem] ~= nil and factionRewardData.installations[strItem].type == factionRewardType.installation
end

function recruiterScreenplay:isSchematic(faction, strItem)
	local factionRewardData = self:getFactionDataTable(faction)
	return factionRewardData.schematic[strItem] ~= nil
end

function recruiterScreenplay:getWeaponsArmorOptions(faction, gcwDiscount, smugglerDiscount)
	local optionsTable = { }
	local factionRewardData = self:getFactionDataTable(faction)
	for k,v in pairs(factionRewardData.weaponsArmorList) do
		if ( factionRewardData.weaponsArmor[v] ~= nil and factionRewardData.weaponsArmor[v].display ~= nil and factionRewardData.weaponsArmor[v].cost ~= nil ) then
			local option = {self:generateSuiString(factionRewardData.weaponsArmor[v].display, math.ceil(factionRewardData.weaponsArmor[v].cost * gcwDiscount * smugglerDiscount)), 0}
			table.insert(optionsTable, option)
		end
	end
	return optionsTable
end

function recruiterScreenplay:getFurnitureOptions(faction, gcwDiscount, smugglerDiscount)
	local optionsTable = { }
	local factionRewardData = self:getFactionDataTable(faction)
	for k,v in pairs(factionRewardData.furnitureList) do
		if ( factionRewardData.furniture[v] ~= nil and factionRewardData.furniture[v].display ~= nil and factionRewardData.furniture[v].cost ~= nil ) then
			local option = {self:generateSuiString(factionRewardData.furniture[v].display, math.ceil(factionRewardData.furniture[v].cost * gcwDiscount * smugglerDiscount)), 0}
			table.insert(optionsTable, option)
		end
	end
	return optionsTable
end

function recruiterScreenplay:getInstallationsOptions(faction, gcwDiscount, smugglerDiscount)
	local optionsTable = { }
	local factionRewardData = self:getFactionDataTable(faction)
	local covertOvert = useCovertOvert()

	for k,v in pairs(factionRewardData.installationsList) do
		if (factionRewardData.installations[v] ~= nil and factionRewardData.installations[v].display ~= nil and factionRewardData.installations[v].cost ~= nil) then
			if ((not covertOvert) and (factionRewardData.installationsList[k] == "covert_detector_32m")) then
				goto skip
			end

			if ((not self.allowPveBases) and (factionRewardData.installations[v].status ~= nil) and (factionRewardData.installations[v].status == COVERT)) then
				goto skip
			end

			local option = {self:generateSuiString(factionRewardData.installations[v].display, math.ceil(factionRewardData.installations[v].cost * gcwDiscount * smugglerDiscount)), 0}
			table.insert(optionsTable, option)

			::skip::
		end
	end
	return optionsTable
end

function recruiterScreenplay:getHirelingsOptions(faction, gcwDiscount, smugglerDiscount)
	local optionsTable = { }
	local factionRewardData = self:getFactionDataTable(faction)
	for k,v in pairs(factionRewardData.hirelingList) do
		if ( factionRewardData.hirelings[v] ~= nil and factionRewardData.hirelings[v].display ~= nil and factionRewardData.hirelings[v].cost ~= nil ) then
			local option = {self:generateSuiString(factionRewardData.hirelings[v].display, math.ceil(factionRewardData.hirelings[v].cost * gcwDiscount * smugglerDiscount)), 0}
			table.insert(optionsTable, option)
		end
	end
	return optionsTable
end

function recruiterScreenplay:getSchematicOptions(faction, gcwDiscount, smugglerDiscount)
	local optionsTable = { }
	local factionRewardData = self:getFactionDataTable(faction)
	local coaWinningFaction = tonumber(CriesOfAlderaan:getWinningFaction())
	local winningFactionString

	if (coaWinningFaction == self.factionHashCode.imperial) then
		winningFactionString = "imperial"
	elseif (coaWinningFaction == self.factionHashCode.rebel) then
		winningFactionString = "rebel"
	else
		winningFactionString = ""
	end

	for k,v in pairs(factionRewardData.schematicList) do
		if (factionRewardData.schematic[v] ~= nil and factionRewardData.schematic[v].display ~= nil and factionRewardData.schematic[v].cost ~= nil) then

			if ((faction ~= winningFactionString) and (factionRewardData.schematicList[k] == "dead_eye_prototype")) then
				goto skip
			end

			local option = {self:generateSuiString(factionRewardData.schematic[v].display, math.ceil(factionRewardData.schematic[v].cost * gcwDiscount * smugglerDiscount)), 0}
			table.insert(optionsTable, option)

			::skip::
		end
	end
	return optionsTable
end

function recruiterScreenplay:getUniformsOptions(faction, gcwDiscount, smugglerDiscount)
	local optionsTable = { }
	local factionRewardData = self:getFactionDataTable(faction)
	for k,v in pairs(factionRewardData.uniformList) do
		if ( factionRewardData.uniforms[v] ~= nil and factionRewardData.uniforms[v].display ~= nil and factionRewardData.uniforms[v].cost ~= nil ) then
			local option = {self:generateSuiString(factionRewardData.uniforms[v].display, math.ceil(factionRewardData.uniforms[v].cost * gcwDiscount * smugglerDiscount)), 0}
			table.insert(optionsTable, option)
		end
	end
	return optionsTable
end

function recruiterScreenplay:generateSuiString(item, cost)
	return getStringId(item) .. " (Cost: " .. cost .. ")"
end

function recruiterScreenplay:getItemCost(faction, itemString)
	local factionRewardData = self:getFactionDataTable(faction)
	if self:isWeapon(faction, itemString) or self:isArmor(faction, itemString)  and factionRewardData.weaponsArmor[itemString] ~= nil and factionRewardData.weaponsArmor[itemString].cost ~= nil then
		return factionRewardData.weaponsArmor[itemString].cost
	elseif self:isUniform(faction, itemString) and factionRewardData.uniforms[itemString].cost ~= nil then
		return factionRewardData.uniforms[itemString].cost
	elseif self:isFurniture(faction, itemString) and factionRewardData.furniture[itemString].cost ~= nil then
		return factionRewardData.furniture[itemString].cost
	elseif self:isInstallation(faction, itemString) and factionRewardData.installations[itemString].cost ~= nil then
		return factionRewardData.installations[itemString].cost
	elseif self:isHireling(faction, itemString) and factionRewardData.hirelings[itemString].cost ~= nil then
		return factionRewardData.hirelings[itemString].cost
	elseif self:isSchematic(faction, itemString) and factionRewardData.schematic[itemString].cost ~= nil then
		return factionRewardData.schematic[itemString].cost
	end
	return nil
end

function recruiterScreenplay:getTemplatePath(faction, itemString)
	local factionRewardData = self:getFactionDataTable(faction)
	if self:isWeapon(faction, itemString) or self:isArmor(faction, itemString) then
		return factionRewardData.weaponsArmor[itemString].item
	elseif self:isUniform(faction, itemString) then
		return factionRewardData.uniforms[itemString].item
	elseif self:isFurniture(faction, itemString) then
		return factionRewardData.furniture[itemString].item
	elseif self:isInstallation(faction, itemString) then
		return factionRewardData.installations[itemString].item
	elseif self:isHireling(faction, itemString) then
		return factionRewardData.hirelings[itemString].item
	elseif self:isSchematic(faction, itemString) then
		return factionRewardData.schematic[itemString].item
	end
	return nil
end

function recruiterScreenplay:getDisplayName(faction, itemString)
	local factionRewardData = self:getFactionDataTable(faction)
	if self:isWeapon(faction, itemString) or self:isArmor(faction, itemString) then
		return factionRewardData.weaponsArmor[itemString].display
	elseif self:isUniform(faction, itemString) then
		return factionRewardData.uniforms[itemString].display
	elseif self:isFurniture(faction, itemString) then
		return factionRewardData.furniture[itemString].display
	elseif self:isInstallation(faction, itemString) then
		return factionRewardData.installations[itemString].display
	elseif self:isHireling(faction, itemString) then
		return factionRewardData.hirelings[itemString].display
	end
	return nil
end


function recruiterScreenplay:getGeneratedObjectTemplate(faction, itemString)
	local factionRewardData = self:getFactionDataTable(faction)
	if self:isInstallation(faction, itemString) and factionRewardData.installations[itemString].generatedObjectTemplate ~= nil then
		return factionRewardData.installations[itemString].generatedObjectTemplate
	end
	return nil
end

function recruiterScreenplay:getControlledObjectTemplate(faction, itemString)
	local factionRewardData = self:getFactionDataTable(faction)
	if self:isHireling(faction, itemString) and factionRewardData.hirelings[itemString].controlledObjectTemplate ~= nil then
		return factionRewardData.hirelings[itemString].controlledObjectTemplate
	end
	return nil
end

function recruiterScreenplay:getBonusItems(faction, itemString)
	if (not self.allowPveBases) then
		return nil
	end

	local factionRewardData = self:getFactionDataTable(faction)
	if self:isInstallation(faction, itemString) and factionRewardData.installations[itemString].bonus ~= nil then
		return factionRewardData.installations[itemString].bonus
	end
	return nil
end

function recruiterScreenplay:getBonusItemCount(faction, itemString)
	local factionRewardData = self:getFactionDataTable(faction)
	if self:isInstallation(faction, itemString) and factionRewardData.installations[itemString].bonus ~= nil then
		return #factionRewardData.installations[itemString].bonus
	end
	return 0
end

function recruiterScreenplay:sendPurchaseSui(pNpc, pPlayer, screenID, gcwDiscount)
	if (pNpc == nil or pPlayer == nil) then
		return
	end

	local faction = self:getRecruiterFaction(pNpc)
	local smugglerDiscount = self:getSmugglerDiscount(pPlayer)

	local playerID = CreatureObject(pPlayer):getObjectID()

	writeStringData(playerID .. ":faction_purchase", screenID)
	writeStringData(playerID .. ":faction_purchase:gcwDiscount:", gcwDiscount)

	local suiManager = LuaSuiManager()
	local options = { }
	if screenID == "fp_furniture" then
		options = self:getFurnitureOptions(faction, gcwDiscount, smugglerDiscount)
	elseif screenID == "fp_weapons_armor" then
		options = self:getWeaponsArmorOptions(faction, gcwDiscount, smugglerDiscount)
	elseif screenID == "fp_installations" then
		options = self:getInstallationsOptions(faction, gcwDiscount, smugglerDiscount)
	elseif screenID == "fp_uniforms" then
		options = self:getUniformsOptions(faction, gcwDiscount, smugglerDiscount)
	elseif screenID == "fp_hirelings" then
		options = self:getHirelingsOptions(faction, gcwDiscount, smugglerDiscount)
	elseif screenID == "fp_schematics" then
		options = self:getSchematicOptions(faction, gcwDiscount, smugglerDiscount)
	end

	suiManager:sendListBox(pNpc, pPlayer, "@faction_recruiter:faction_purchase", "@faction_recruiter:select_item_purchase", 2, "@cancel", "", "@ok", "recruiterScreenplay", "handleSuiPurchase", 32, options)
end

function recruiterScreenplay:handleSuiPurchase(pCreature, pSui, eventIndex, arg0)
	local cancelPressed = (eventIndex == 1)

	if pCreature == nil then
		return
	end

	local playerID = SceneObject(pCreature):getObjectID()

	if cancelPressed then
		deleteStringData(playerID .. ":faction_purchase")
		deleteStringData(playerID .. ":faction_purchase:gcwDiscount:")
		return
	end

	local purchaseCategory = readStringData(playerID .. ":faction_purchase")
	local gcwDiscount = tonumber(readStringData(playerID .. ":faction_purchase:gcwDiscount:"))

	deleteStringData(playerID .. ":faction_purchase")
	deleteStringData(playerID .. ":faction_purchase:gcwDiscount:")

	if purchaseCategory == "" then
		return
	end

	local purchaseIndex = arg0 + 1
	local faction = self:getFactionFromHashCode(CreatureObject(pCreature):getFaction())
	local dataTable = self:getFactionDataTable(faction)
	local itemListTable = self:getItemListTable(faction, purchaseCategory)
	local itemString = itemListTable[purchaseIndex]

	local awardResult = nil

	if (self:isHireling(faction, itemString)) then
		awardResult = self:awardData(pCreature, faction, itemString, gcwDiscount)
	elseif (self:isSchematic(faction, itemString)) then
		awardResult = self:awardSchematic(pCreature, faction, itemString, gcwDiscount)
	else
		awardResult = self:awardItem(pCreature, faction, itemString, gcwDiscount)
	end

	if (awardResult == self.errorCodes.SUCCESS) then
		return
	elseif (awardResult == self.errorCodes.INVENTORYFULL) then
		CreatureObject(pCreature):sendSystemMessage("@dispenser:inventory_full") -- Your inventory is full. You must make some room before you can purchase.
	elseif (awardResult == self.errorCodes.DATAPADFULL) then
		CreatureObject(pCreature):sendSystemMessage("@faction_recruiter:datapad_full") -- Your datapad is full. You must first free some space.
	elseif (awardResult == self.errorCodes.TOOMANYHIRELINGS) then
		CreatureObject(pCreature):sendSystemMessage("@faction_recruiter:too_many_hirelings") -- You already have too much under your command.
	elseif (awardResult == self.errorCodes.NOTENOUGHFACTION) then
		local messageString = LuaStringIdChatParameter("@faction_recruiter:not_enough_standing_spend")
		messageString:setDI(self.minimumFactionStanding)
		messageString:setTO(self:toTitleCase(faction))
		CreatureObject(pCreature):sendSystemMessage(messageString:_getObject()) -- You do not have enough faction standing to spend. You must maintain at least %DI to remain part of the %TO faction.
	elseif (awardResult == self.errorCodes.ITEMCOST) then
		CreatureObject(pCreature):sendSystemMessage("Error determining cost of item. Please post a bug report regarding the item you attempted to purchase.")
	elseif (awardResult == self.errorCodes.INVENTORYERROR or awardResult == self.DATAPADERROR) then
		CreatureObject(pCreature):sendSystemMessage("Error finding location to put item. Please post a report.")
	elseif (awardResult == self.errorCodes.TEMPLATEPATHERROR) then
		CreatureObject(pCreature):sendSystemMessage("Error determining data for item. Please post a bug report regarding the item you attempted to purchase..")
	elseif (awardResult == self.errorCodes.SCHEMATICERROR) then
		CreatureObject(pCreature):sendSystemMessage("@loot_schematic:already_have_schematic")
	end
end

function recruiterScreenplay:awardItem(pPlayer, faction, itemString, gcwDiscount)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return self.errorCodes.INVENTORYERROR
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return self.errorCodes.INVENTORYERROR
	end

	local factionStanding = PlayerObject(pGhost):getFactionStanding(faction)
	local itemCost = self:getItemCost(faction, itemString)

	if itemCost == nil then
		return self.errorCodes.ITEMCOST
	end

	local bothanDiscount = 1.0

	if (CreatureObject(pPlayer):getSpecies() == SPECIES_BOTHAN) then
		bothanDiscount = 0.9;
	end

	local smugglerDiscount = self:getSmugglerDiscount(pPlayer)

	itemCost = math.ceil(itemCost * gcwDiscount * smugglerDiscount * bothanDiscount)

	if (factionStanding < (itemCost + self.minimumFactionStanding)) then
		return self.errorCodes.NOTENOUGHFACTION
	end

	local slotsremaining = SceneObject(pInventory):getContainerVolumeLimit() - SceneObject(pInventory):getCountableObjectsRecursive()

	local bonusItemCount = self:getBonusItemCount(faction, itemString)

	if (not self.allowPveBases) then
		bonusItemCount = 0
	end

	if (slotsremaining < (1 + bonusItemCount)) then
		return self.errorCodes.INVENTORYFULL
	end

	local transferResult =  self:transferItem(pPlayer, pInventory, faction, itemString)

	if (transferResult ~= self.errorCodes.SUCCESS) then
		return transferResult
	end

	PlayerObject(pGhost):decreaseFactionStanding(faction, itemCost)

	local messageString = LuaStringIdChatParameter("@faction_recruiter:item_purchase_complete") -- Your requisition of %TT is complete.
	messageString:setTT(self:getDisplayName(faction, itemString))
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

	if bonusItemCount then
		local bonusItems = self:getBonusItems(faction, itemString)
		if bonusItems ~= nil then
			messageString = LuaStringIdChatParameter("@faction_perk:given_extra_bases") -- Congratulations! In addition to the base that you purchased, we have given you two additional bases. They are:
			CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

			for k, v in pairs(bonusItems) do
				transferResult = self:transferItem(pPlayer, pInventory, faction, v)
				if(transferResult ~= self.errorCodes.SUCCESS) then
					return transferResult
				end

				messageString = LuaStringIdChatParameter("@faction_perk:bonus_base_name") -- You received a: %TO
				messageString:setTO(self:getDisplayName(faction, v))
				CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
			end
		end
	end

	return self.errorCodes.SUCCESS
end

function recruiterScreenplay:toTitleCase(str)
	local buf = {}
	for word in string.gmatch(str, "%S+") do
		local first, rest = string.sub(word, 1, 1), string.sub(word, 2)
		table.insert(buf, string.upper(first) .. string.lower(rest))
	end
	return table.concat(buf, " ")
end

function recruiterScreenplay:getUseCount(faction, itemString)
	local factionRewardData = self:getFactionDataTable(faction)

	if self:isSchematic(faction, itemString) and factionRewardData.schematic[itemString].useCount ~= nil then
		return factionRewardData.schematic[itemString].useCount
	end

	return nil
end

function recruiterScreenplay:awardSchematic(pPlayer, faction, itemString, gcwDiscount)
	if (pPlayer == nil) then
		return self.errorCodes.GENERALERROR
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return self.errorCodes.DATAPADERROR
	end

	local factionStanding = PlayerObject(pGhost):getFactionStanding(faction)
	local itemCost = self:getItemCost(faction, itemString)

	if itemCost == nil then
		return self.errorCodes.ITEMCOST
	end

	itemCost = math.ceil(itemCost * gcwDiscount * self:getSmugglerDiscount(pPlayer))

	if factionStanding < (itemCost + self.minimumFactionStanding) then
		return self.errorCodes.NOTENOUGHFACTION
	end

	local templatePath = self:getTemplatePath(faction, itemString)

	local useCount = self:getUseCount(faction, itemString)

	if (useCount == nil) then
		useCount = 1
	end

	-- add schematic
	local transferSchem = PlayerObject(pGhost):addRewardedSchematic(tostring(templatePath), 2, useCount, true)

	if (not transferSchem) then
		return self.errorCodes.SCHEMATICERROR
	end

	local factionRewardData = self:getFactionDataTable(faction)
	local messageString = LuaStringIdChatParameter("@loot_schematic:skill_granted")

	messageString:setTO(getStringId(factionRewardData.schematic[itemString].display))
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

	PlayerObject(pGhost):decreaseFactionStanding(faction, itemCost)

	return self.errorCodes.SUCCESS
end

function recruiterScreenplay:awardData(pPlayer, faction, itemString, gcwDiscount)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return self.errorCodes.DATAPADERROR
	end

	local pDatapad = SceneObject(pPlayer):getSlottedObject("datapad")

	if pDatapad == nil then
		return self.errorCodes.DATAPADERROR
	end

	local factionStanding = PlayerObject(pGhost):getFactionStanding(faction)
	local itemCost = self:getItemCost(faction, itemString)

	if itemCost == nil then
		return self.errorCodes.ITEMCOST
	end

	itemCost = math.ceil(itemCost * gcwDiscount * self:getSmugglerDiscount(pPlayer))

	if factionStanding < (itemCost + self.minimumFactionStanding) then
		return self.errorCodes.NOTENOUGHFACTION
	end

	local slotsRemaining = SceneObject(pDatapad):getContainerVolumeLimit() - SceneObject(pDatapad):getCountableObjectsRecursive()
	local bonusItemCount = self:getBonusItemCount(faction, itemString)

	if (slotsRemaining < (1 + bonusItemCount)) then
		return self.errorCodes.DATAPADFULL
	end

	local transferResult = self:transferData(pPlayer, pDatapad, faction, itemString)

	if(transferResult ~= self.errorCodes.SUCCESS) then
		return transferResult
	end

	PlayerObject(pGhost):decreaseFactionStanding(faction, itemCost)

	local messageString = LuaStringIdChatParameter("@faction_recruiter:hireling_purchase_complete") -- The %TT is now under your command.
	messageString:setTT(self:getDisplayName(faction, itemString))
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

	if bonusItemCount then
		local bonusItems = self:getBonusItems(faction, itemString)
		if bonusItems ~= nil then
			for k, v in pairs(bonusItems) do
				transferResult = self:transferData(pPlayer, pDatapad, faction, v)
				if (transferResult ~= self.errorCodes.SUCCESS) then
					return transferResult
				end
			end
		end
	end

	return self.errorCodes.SUCCESS
end

function recruiterScreenplay:transferData(pPlayer, pDatapad, faction, itemString)
	local pItem
	local templatePath = self:getTemplatePath(faction, itemString)

	if templatePath == nil then
		return self.errorCodes.TEMPLATEPATHERROR
	end

	local genPath = self:getControlledObjectTemplate(faction, itemString)

	if genPath == nil then
		return self.errorCodes.TEMPLATEPATHERROR
	end

	if (self:isHireling(faction, itemString)) then
		if (checkTooManyHirelings(pDatapad)) then
			return self.errorCodes.TOOMANYHIRELINGS
		end

		pItem = giveControlDevice(pDatapad, templatePath, genPath, -1, true)
	else
		pItem = giveControlDevice(pDatapad, templatePath, genPath, -1, false)
	end

	if pItem ~= nil then
		SceneObject(pItem):sendTo(pPlayer)
	else
		return self.errorCodes.GIVEERROR
	end

	return self.errorCodes.SUCCESS
end

function recruiterScreenplay:transferItem(pPlayer, pInventory, faction, itemString)
	local templatePath = self:getTemplatePath(faction, itemString)

	if templatePath == nil then
		return self.errorCodes.TEMPLATEPATHERROR
	end

	local pItem = giveItem(pInventory, templatePath, -1)

	if (pItem == nil) then
		return self.errorCodes.GIVEERROR
	end

	if (self:isInstallation(faction, itemString)) then
		SceneObject(pItem):setObjectName("deed", itemString, true)
		local deed = LuaDeed(pItem)
		local genPath = self:getGeneratedObjectTemplate(faction, itemString)

		if genPath == nil then
			return self.errorCodes.TEMPLATEPATHERROR
		end

		deed:setGeneratedObjectTemplate(genPath)

		if (faction == "imperial") then
			TangibleObject(pItem):setFaction(FACTIONIMPERIAL)
		elseif (faction == "rebel") then
			TangibleObject(pItem):setFaction(FACTIONREBEL)
		end
	end

	return self.errorCodes.SUCCESS
end


function recruiterScreenplay:getItemListTable(faction, screenID)
	local dataTable = self:getFactionDataTable(faction)
	if screenID == "fp_furniture" then
		return dataTable.furnitureList
	elseif screenID == "fp_weapons_armor" then
		return dataTable.weaponsArmorList
	elseif screenID == "fp_installations" then
		local list = dataTable.installationsList
		local covertOvert = useCovertOvert()

		local table = {}

		for i = 1, #list, 1 do
			local itemString = list[i]

			if ((not self.allowPveBases) and (string.find(itemString, "hq_")) and (not string.find(itemString, "_pvp_"))) then
				goto skip
			elseif ((not covertOvert) and (string.find(itemString, "covert_detector_32m"))) then
				goto skip
			end

			table[#table + 1] = itemString

			::skip::
		end

		return table
	elseif screenID == "fp_uniforms" then
		return dataTable.uniformList
	elseif screenID == "fp_hirelings" then
		return dataTable.hirelingList
	elseif screenID == "fp_schematics" then
		return dataTable.schematicList
	end
end

function recruiterScreenplay:getSmugglerDiscount(pPlayer)
	if CreatureObject(pPlayer):hasSkill("combat_smuggler_master") then
		return .75
	elseif CreatureObject(pPlayer):hasSkill("combat_smuggler_underworld_01") then
		return .90
	end
	return 1.0
end

function recruiterScreenplay:handleGoOnLeave(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (CreatureObject(pPlayer):hasSkill("force_rank_light_novice") or CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) then
		CreatureObject(pPlayer):sendSystemMessage("@faction_recruiter:jedi_cant_resign")
		return
	end

	deleteData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus")
	CreatureObject(pPlayer):setFactionStatus(0)
end

function recruiterScreenplay:handleGoCovert(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (CreatureObject(pPlayer):hasSkill("force_rank_light_novice") or CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) then
		CreatureObject(pPlayer):sendSystemMessage("@faction_recruiter:jedi_cant_go_covert")
		return
	end

	deleteData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus")
	CreatureObject(pPlayer):setFactionStatus(1)
end

function recruiterScreenplay:handleGoOvert(pPlayer)
	deleteData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus")
	CreatureObject(pPlayer):setFactionStatus(2)
end

function recruiterScreenplay:handleResign(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (CreatureObject(pPlayer):hasSkill("force_rank_light_novice") or CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) then
		CreatureObject(pPlayer):sendSystemMessage("@faction_recruiter:jedi_cant_resign")
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	deleteData(playerID .. ":changingFactionStatus")
	local oldFaction = CreatureObject(pPlayer):getFaction()
	local oldFactionName = self:getFactionFromHashCode(oldFaction)
	local covertOvert = useCovertOvert()

	if (covertOvert) then
		CreatureObject(pPlayer):setFactionRank(0)
		CreatureObject(pPlayer):setFactionStatus(0)
		CreatureObject(pPlayer):setFaction(0)

		TangibleObject(pPlayer):broadcastPvpStatusBitmask()
	else
		CreatureObject(pPlayer):setFactionRank(0)
		CreatureObject(pPlayer):setFaction(0)
		CreatureObject(pPlayer):setFactionStatus(0)
	end

	PlayerObject(pGhost):decreaseFactionStanding(oldFactionName, 0)
end
