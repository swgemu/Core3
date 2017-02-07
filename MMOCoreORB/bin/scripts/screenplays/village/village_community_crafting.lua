local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

VillageCommunityCrafting = ScreenPlay:new {
	maxCraftersPerPhase = 200,
	phaseInfo = {
		[2] = {
			schematic = "object/draft_schematic/community_crafting/village_defenses.iff",
			keyName = "village_defenses",
			ingredients = {
				-- Schematic slots
				[1] = {
					stringName = "refined_endrine",
					template = "object/tangible/component/structure/refined_endrine.iff",
					schematic = "object/draft_schematic/community_crafting/component/refined_endrine.iff",
					attributes = { "res_malleability", "res_quality", "res_toughness" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_assembly_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_assembly_5.iff"
					}
				},
				[2] = {
					stringName = "refined_rudic",
					template = "object/tangible/component/structure/refined_rudic.iff",
					schematic = "object/draft_schematic/community_crafting/component/refined_rudic.iff",
					attributes = { "res_conductivity", "res_decay_resist", "res_quality", "res_shock_resistance" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_assembly_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_assembly_5.iff"
					}
				},
				[3] = {
					stringName = "refined_ardanium_ii",
					template = "object/tangible/component/structure/refined_ardanium_ii.iff",
					schematic = "object/draft_schematic/community_crafting/component/refined_ardanium_ii.iff",
					attributes = { "res_potential_energy", "res_quality" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_assembly_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_assembly_5.iff"
					}
				},
				[4] = {
					stringName = "reinforced_wall_module",
					template = "object/tangible/component/structure/reinforced_wall_module.iff",
					schematic = "object/draft_schematic/community_crafting/component/reinforced_wall_module.iff",
					attributes = { "kineticeffectiveness" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_assembly_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_assembly_5.iff"
					}
				},
				[5] = {
					stringName = "lightweight_turret",
					template = "object/tangible/component/structure/lightweight_turret.iff",
					schematic = "object/draft_schematic/community_crafting/component/lightweight_turret.iff",
					attributes = { "accuracy", "speed" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_assembly_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_assembly_5.iff"
					}
				}
			},
			secondarySchematics = {
				"object/draft_schematic/community_crafting/component/lightweight_turret_electronics.iff",
				"object/draft_schematic/community_crafting/component/lightweight_turret_hardware.iff"
			},
			overallPrize = {
				quantity = "object/tangible/crafting/station/jedi_tool_crit_assembly_20.iff",
				quality = "object/tangible/crafting/station/jedi_tool_crit_assembly_20.iff"
			},
			minIngredients = 10,
			ingredientMinValue = 0,
			ingredientMaxValue = 1000
		},
		[3] = {
			schematic = "object/draft_schematic/community_crafting/village_shields.iff",
			keyName = "village_shields",
			ingredients = {
				-- Schematic slots
				[1] = {
					stringName = "endrost",
					template = "object/tangible/component/chemistry/endrost.iff",
					schematic = "object/draft_schematic/community_crafting/component/endrost.iff",
					attributes = { "res_quality", "res_toughness" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff"
					}
				},
				[2] = {
					stringName = "shield_housing",
					template = "object/tangible/component/structure/shield_housing.iff",
					schematic = "object/draft_schematic/community_crafting/component/shield_housing.iff",
					attributes = { "system_redundancy" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff"
					}
				},
				[3] = {
					stringName = "power_supply",
					template = "object/tangible/component/structure/power_supply.iff",
					schematic = "object/draft_schematic/community_crafting/component/power_supply.iff",
					attributes = { "energy_resistance" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff"
					}
				},
				[4] = {
					stringName = "unit_computer",
					template = "object/tangible/component/structure/unit_computer.iff",
					schematic = "object/draft_schematic/community_crafting/component/unit_computer.iff",
					attributes = { "armor_effectiveness" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff"
					}
				},
				[5] = {
					stringName = "regulator",
					template = "object/tangible/component/structure/regulator.iff",
					schematic = "object/draft_schematic/community_crafting/component/regulator.iff",
					attributes = { "power_efficiency" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff"
					}
				},
				[6] = {
					stringName = "connections",
					template = "object/tangible/component/structure/connections.iff",
					schematic = "object/draft_schematic/community_crafting/component/connections.iff",
					attributes = { "grid_stability" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff"
					}
				},
				[7] = {
					stringName = "primary_computer",
					template = "object/tangible/component/structure/primary_computer.iff",
					schematic = "object/draft_schematic/community_crafting/component/primary_computer.iff",
					attributes = { "system_response" },
					prize = {
						quantity = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff",
						quality = "object/tangible/crafting/station/jedi_tool_crit_experiment_5.iff"
					}
				},
			},
			secondarySchematics = {},
			overallPrize = {
				quantity = "object/tangible/crafting/station/jedi_tool_crit_experiment_20.iff",
				quality = "object/tangible/crafting/station/jedi_tool_crit_experiment_20.iff"
			},
			minIngredients = 20,
			ingredientMinValue = 0,
			ingredientMaxValue = 1000
		}
	}
}

function VillageCommunityCrafting:getCurrentActiveCrafters()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local currentCount = tonumber(getQuestStatus("Village:activeCrafters:" .. phaseID))

	if (currentCount == nil) then
		return 0
	end

	return currentCount
end

function VillageCommunityCrafting:getMaxCraftersPerPhase()
	return self.maxCraftersPerPhase
end

function VillageCommunityCrafting:getMinimumIngredients()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	return self.phaseInfo[currentPhase].minIngredients
end

function VillageCommunityCrafting:incrementCurrentActiveCrafters()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local curCount = VillageCommunityCrafting:getCurrentActiveCrafters()
	setQuestStatus("Village:activeCrafters:" .. phaseID, curCount + 1)
end

function VillageCommunityCrafting:createNewActiveCrafterList()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	return createQuestVectorMap("VillageActiveCraftersPhaseID" .. phaseID)
end

function VillageCommunityCrafting:removeActiveCrafterList(phaseID)
	removeQuestVectorMap("VillageActiveCraftersPhaseID" .. phaseID)
end

function VillageCommunityCrafting:getActiveCrafterList(phaseID)
	return getQuestVectorMap("VillageActiveCraftersPhaseID" .. phaseID)
end

function VillageCommunityCrafting:addToActiveCrafterList(pPlayer)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local pMap = VillageCommunityCrafting:getActiveCrafterList(phaseID)

	if (pMap == nil) then
		pMap = VillageCommunityCrafting:createNewActiveCrafterList()
	end

	local crafterMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	if (not crafterMap:hasMapRow(playerID)) then
		crafterMap:addMapRow(playerID, tostring(0))
	else
		printLuaError("Error in crafterMap, attempting to add existing player " .. SceneObject(pPlayer):getCustomObjectName() .. " to active community crafter list.")
	end

end

function VillageCommunityCrafting:removeFromActiveCrafterList(pPlayer)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	local pMap = VillageCommunityCrafting:getActiveCrafterList(phaseID)

	if (pMap == nil) then
		return
	end

	local crafterMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	if (crafterMap:hasMapRow(playerID)) then
		crafterMap:deleteMapRow(playerID)
	end
end

function VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()

	if (currentPhase ~= 2 and currentPhase ~= 3) then
		return false
	end

	local pMap = VillageCommunityCrafting:getActiveCrafterList(phaseID)

	if (pMap == nil) then
		return false
	end

	local crafterMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	return crafterMap:hasMapRow(playerID)
end

function VillageCommunityCrafting:getIngredientsNeededByPlayer(pPlayer)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()

	local pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":quantity")

	if (pMap == nil) then
		printLuaError("VillageCommunityCrafting:getIngredientsNeededByPlayer, unable to get active crafter list.")
		return -1
	end

	local crafterMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	local minIngredients = self.phaseInfo[currentPhase].minIngredients

	if (not crafterMap:hasMapRow(playerID)) then
		return minIngredients
	end

	local curIngredients = tonumber(crafterMap:getMapRow(playerID))

	local neededIngredients = minIngredients - curIngredients

	if (neededIngredients < 0) then
		neededIngredients = 0
	end

	return neededIngredients
end

function VillageCommunityCrafting:isCurrentPhaseIngredient(pObj)
	if (pObj == nil) then
		return false
	end

	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local templatePath = SceneObject(pObj):getTemplateObjectPath()
	local ingredientList = self.phaseInfo[currentPhase].ingredients

	for i = 1, #ingredientList, 1 do
		if ingredientList[i].template == templatePath then
			return true
		end
	end

	return false
end

function VillageCommunityCrafting:getAttributeValueTable(slotNum)
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	return getQuestVectorMap("VillageCCAttributeTable:" .. phaseID .. ":slot" .. slotNum)
end

function VillageCommunityCrafting:createAttributeValueTables()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local ingredients = self.phaseInfo[currentPhase].ingredients

	for i = 1, #ingredients, 1 do
		local pMap = createQuestVectorMap("VillageCCAttributeTable:" .. phaseID .. ":slot" .. i)

		if (pMap == nil) then
			printLuaError("Failed to create vector map in VillageCommunityCrafting:createAttributeValueTables, slot " .. i .. ".")
			return
		end

		local attribMap = LuaQuestVectorMap(pMap)

		for j = 1, #ingredients[i].attributes, 1 do
			attribMap:addMapRow(ingredients[i].attributes[j], tostring(0))
		end
	end
end

function VillageCommunityCrafting:createProjectStatsTables()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local ingredients = self.phaseInfo[currentPhase].ingredients

	local pMap = createQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":overallQuality")

	if (pMap == nil) then
		printLuaError("Failed to create overall quality stats vector map in VillageCommunityCrafting:createProjectStatsTables.")
		return
	end

	for i = 1, #ingredients, 1 do
		local statMap = LuaQuestVectorMap(pMap)
		statMap:addMapRow(tostring(i), tostring(0))
	end

	pMap = createQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":quality")

	if (pMap == nil) then
		printLuaError("Failed to create quality stats vector map in VillageCommunityCrafting:createProjectStatsTables.")
		return
	end

	pMap = createQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":quantity")

	if (pMap == nil) then
		printLuaError("Failed to create quality stats vector map in VillageCommunityCrafting:createProjectStatsTables.")
		return
	end

	pMap = createQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":playerNames")

	if (pMap == nil) then
		printLuaError("Failed to create player name vector map in VillageCommunityCrafting:createProjectStatsTables.")
		return
	end

	for i = 1, #ingredients, 1 do
		pMap = createQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. i .. ":quality")

		if (pMap == nil) then
			printLuaError("Failed to create slot quality stat vector map in VillageCommunityCrafting:createProjectStatsTables, slot " .. i .. ".")
			return
		end

		pMap = createQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. i .. ":quantity")

		if (pMap == nil) then
			printLuaError("Failed to create slot quantity stat vector map in VillageCommunityCrafting:createProjectStatsTables, slot " .. i .. ".")
			return
		end
	end
end

function VillageCommunityCrafting:addDefaultPlayerStatsToStatTables(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local ingredients = self.phaseInfo[currentPhase].ingredients

	local	pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":playerNames")

	if (pMap == nil) then
		printLuaError("Failed to grab player name vector map in VillageCommunityCrafting:addDefaultPlayerStatsToStatTables.")
		return
	end

	local statMap = LuaQuestVectorMap(pMap)
	statMap:addMapRow(tostring(playerID), CreatureObject(pPlayer):getFirstName())

	pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":quality")

	if (pMap == nil) then
		printLuaError("Failed to grab quality stats vector map in VillageCommunityCrafting:addDefaultPlayerStatsToStatTables.")
		return
	end

	statMap = LuaQuestVectorMap(pMap)
	statMap:addMapRow(tostring(playerID), tostring(0))

	pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":quantity")

	if (pMap == nil) then
		printLuaError("Failed to grab quantity stats vector map in VillageCommunityCrafting:addDefaultPlayerStatsToStatTables.")
		return
	end

	statMap = LuaQuestVectorMap(pMap)
	statMap:addMapRow(tostring(playerID), tostring(0))

	for i = 1, #ingredients, 1 do
		pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. i .. ":quality")

		if (pMap == nil) then
			printLuaError("Failed to grab slot quality stat vector map in VillageCommunityCrafting:addDefaultPlayerStatsToStatTables, slot " .. i .. ".")
			return
		end

		statMap = LuaQuestVectorMap(pMap)
		statMap:addMapRow(tostring(playerID), tostring(0))

		pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. i .. ":quantity")

		if (pMap == nil) then
			printLuaError("Failed to grab slot quantity stat vector map in VillageCommunityCrafting:addDefaultPlayerStatsToStatTables, slot " .. i .. ".")
			return
		end

		statMap = LuaQuestVectorMap(pMap)
		statMap:addMapRow(tostring(playerID), tostring(0))
	end
end

function VillageCommunityCrafting:updatePlayerStatTables(pPlayer, value, slot)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	local pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":quality")

	if (pMap == nil) then
		printLuaError("Failed to grab quality stats vector map in VillageCommunityCrafting:updatePlayerStatTables.")
		return
	end

	local statMap = LuaQuestVectorMap(pMap)
	local curValue = statMap:getMapRow(playerID)
	local newValue = tonumber(curValue) + value

	statMap:deleteMapRow(playerID)
	statMap:addMapRow(playerID, tostring(newValue))

	pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":quantity")

	if (pMap == nil) then
		printLuaError("Failed to grab quantity stats vector map in VillageCommunityCrafting:updatePlayerStatTables.")
		return
	end

	statMap = LuaQuestVectorMap(pMap)
	curValue = statMap:getMapRow(playerID)
	newValue = tonumber(curValue) + 1

	statMap:deleteMapRow(playerID)
	statMap:addMapRow(playerID, tostring(newValue))

	pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. slot .. ":quality")

	if (pMap == nil) then
		printLuaError("Failed to grab slot " .. slot .. " quality stats vector map in VillageCommunityCrafting:updatePlayerStatTables.")
		return
	end

	statMap = LuaQuestVectorMap(pMap)
	curValue = statMap:getMapRow(playerID)
	newValue = tonumber(curValue) + value

	statMap:deleteMapRow(playerID)
	statMap:addMapRow(playerID, tostring(newValue))

	pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. slot .. ":quantity")

	if (pMap == nil) then
		printLuaError("Failed to grab slot " .. slot .. " quantity stats vector map in VillageCommunityCrafting:updatePlayerStatTables.")
		return
	end

	statMap = LuaQuestVectorMap(pMap)
	curValue = statMap:getMapRow(playerID)
	newValue = tonumber(curValue) + 1

	statMap:deleteMapRow(playerID)
	statMap:addMapRow(playerID, tostring(newValue))
end

function VillageCommunityCrafting:getPlayerStatTableData(pPlayer, tableType, slotBool, slotNum)
	if (slotBool and (slotNum == nil or slotNum < 0)) then
		printLuaError("Invalid slot number in VillageCommunityCrafting:getPlayerStatTableData.")
		return
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local playerID = tostring(SceneObject(pPlayer):getObjectID())
	local pMap

	if (slotBool) then
		pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. slotNum .. ":" .. tableType)
	else
		pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":" .. tableType)
	end

	if (pMap == nil) then
		if (slotBool) then
			printLuaError("Failed to grab slot " .. slotNum .. " " .. tableType .. " stats vector map in VillageCommunityCrafting:getPlayerStatTableData.")
		else
			printLuaError("Failed to grab " .. tableType .. " stats vector map in VillageCommunityCrafting:getPlayerStatTableData.")
		end

		return
	end

	local statMap = LuaQuestVectorMap(pMap)
	return tonumber(statMap:getMapRow(playerID))
end

function VillageCommunityCrafting:noCallback(pPlayer, pSui, eventIndex, ...)
end

function VillageCommunityCrafting:sendPlayerProjectAttributes(pPlayer, pNpc)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local ingredientList = self.phaseInfo[currentPhase].ingredients

	local sui = SuiListBox.new("VillageCommunityCrafting", "noCallback")

	sui.setTargetNetworkId(SceneObject(pNpc):getObjectID())
	sui.setTitle("@crafting:project_attributes")
	sui.setPrompt("@crafting:attributes_prompt")
	sui.hideCancelButton()

	for i = 1, #ingredientList, 1 do
		local pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":overallQuality")

		if (pMap == nil) then
			printLuaError("Failed to grab quantity stats vector map in VillageCommunityCrafting:sendPlayerProjectAttributes.")
		else
			local statMap = LuaQuestVectorMap(pMap)
			local curValue = tonumber(statMap:getMapRow(i))

			if curValue > 100 then curValue = 100 end

			curValue = math.floor(curValue * 100) / 100

			local attribString = "@community_crafting_n:" .. ingredientList[i].stringName
			sui.add(attribString .. " \\>200" .. curValue, "")
		end
	end

	sui.sendTo(pPlayer)
end

function VillageCommunityCrafting:sendPlayerProjectSlotAttributes(pPlayer, pNpc, type, slot)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local ingredientData = self.phaseInfo[currentPhase].ingredients[slot]

	local pQuantityMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. slot .. ":quantity")

	if (pQuantityMap == nil) then
		printLuaError("Failed to grab quantity stats vector map for slot " .. slot .. " in VillageCommunityCrafting:sendPlayerProjectAttributes.")
		return
	end

	local quantityMap = LuaQuestVectorMap(pQuantityMap)

	local pQualityMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. slot .. ":quality")

	if (pQualityMap == nil) then
		printLuaError("Failed to grab quality stats vector map for slot " .. slot .. " in VillageCommunityCrafting:sendPlayerProjectAttributes.")
		return
	end

	local qualityMap = LuaQuestVectorMap(pQualityMap)

	local pNameMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":playerNames")

	if (pNameMap == nil) then
		printLuaError("Failed to grab player name vector in VillageCommunityCrafting:sendPlayerProjectAttributes.")
		return
	end

	local nameMap = LuaQuestVectorMap(pNameMap)
	local statTable = { }

	local sui = SuiListBox.new("VillageCommunityCrafting", "noCallback")

	sui.setTargetNetworkId(SceneObject(pNpc):getObjectID())
	sui.setTitle("@crafting:player_rankings")
	sui.hideCancelButton()

	local totalPlayers = nameMap:getMapSize()

	if (totalPlayers == 0) then
		sui.setPrompt("@crafting:no_players")
		sui.sendTo(pPlayer)
		return
	elseif (totalPlayers > 50) then
		if (type == "quality") then
			sui.setPrompt("@crafting:quality_prompt_limited")
		elseif (type == "quantity") then
			sui.setPrompt("@crafting:quantity_prompt_limited")
		end
	else
		if (type == "quality") then
			sui.setPrompt("@crafting:quality_prompt")
		elseif (type == "quantity") then
			sui.setPrompt("@crafting:quantity_prompt")
		end
	end

	for i = 1, totalPlayers, 1 do
		local playerID = qualityMap:getMapKeyAtIndex(i - 1)
		local playerName = nameMap:getMapRow(playerID)
		local playerQuality = tonumber(qualityMap:getMapRow(playerID))
		local playerQuantity = tonumber(quantityMap:getMapRow(playerID))
		if (playerQuantity ~= nil and playerQuantity > 0) then
			local dataTable = { playerName, playerQuality, playerQuantity }
			table.insert(statTable, dataTable)
		end
	end

	if (type == "quality") then
		table.sort(statTable, self.qualitySort)
	else
		table.sort(statTable, self.quantitySort)
	end

	local maxList = #statTable
	if (maxList > 50) then maxList = 50 end

	for i = 1, maxList, 1 do
		local	curValue

		if (type == "quality") then
			curValue = math.floor((statTable[i][2] / statTable[i][3]) * 10000) / 100
		else
			curValue = statTable[i][3]
		end
		local curName = statTable[i][1]

		sui.add(curName .. "\\>200" .. curValue, "")
	end

	sui.sendTo(pPlayer)
end

function VillageCommunityCrafting.qualitySort(a,b)
	return b[2] < a[2]
end
function VillageCommunityCrafting.quantitySort(a,b)
	return b[3] < a[3]
end

function VillageCommunityCrafting:calculateIngredientQuality(pObj, pPlayer)
	local ingredientData
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local ingredientList = self.phaseInfo[currentPhase].ingredients
	local templatePath = SceneObject(pObj):getTemplateObjectPath()
	local slotNum = 0

	for i = 1, #ingredientList, 1 do
		if ingredientList[i].template == templatePath then
			ingredientData = ingredientList[i]
			slotNum = i
		end
	end

	if (slotNum == 0) then
		return -1
	end

	local minValue = self.phaseInfo[currentPhase].ingredientMinValue
	local maxValue = self.phaseInfo[currentPhase].ingredientMaxValue
	local attribsFound = 0
	local totalQuality = 0

	local pMap = self:getAttributeValueTable(slotNum)

	if (pMap == nil) then
		printLuaError("Unable to get attribute map in VillageCommunityCrafting:calculateIngredientQuality() for slot " .. slotNum .. ".")
		return -1
	end

	local attribMap = LuaQuestVectorMap(pMap)

	for i = 1, #ingredientData.attributes, 1 do
		local attribName = ingredientData.attributes[i]
		local attribValue

		if (SceneObject(pObj):getGameObjectType() == 4194316) then
			attribValue = LuaCustomIngredient(pObj):getValueOf(attribName)
		else
			attribValue = LuaComponent(pObj):getAttributeValue(attribName)
		end

		if (attribValue > minValue and attribValue < maxValue) then
			attribValue = (attribValue - minValue) / (maxValue - minValue)
			attribValue = attribValue * attribValue

			attribsFound = attribsFound + 1
			totalQuality = totalQuality + attribValue

			local tableValue = attribMap:getMapRow(attribName)

			if (tableValue == "") then
				printLuaError("VillageCommunityCrafting:getIngredientQuality(), table value empty for attribute " .. attribName)
			else
				local newTableValue = tonumber(tableValue) + attribValue
				attribMap:deleteMapRow(attribName)
				attribMap:addMapRow(attribName, tostring(newTableValue))
			end
		end
	end

	if (attribsFound <= 0) then
		return -1
	end

	local finalQuality = totalQuality / attribsFound

	if (finalQuality > 0) then
		local pMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":overallQuality")

		if (pMap == nil) then
			printLuaError("Failed to grab overall quality stats vector map in VillageCommunityCrafting:calculateIngredientQuality.")
			return -1
		end

		local statMap = LuaQuestVectorMap(pMap)
		local curValue = statMap:getMapRow(slotNum)
		local newValue = tonumber(curValue) + finalQuality

		statMap:deleteMapRow(tostring(slotNum))
		statMap:addMapRow(tostring(slotNum), tostring(newValue))

		self:updatePlayerStatTables(pPlayer, finalQuality, slotNum)
	end

	return finalQuality
end

function VillageCommunityCrafting:addIngredient(pPlayer, pObj)
	if (pPlayer == nil or pObj == nil) then
		return false
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	if (not self:isOnActiveCrafterList(pPlayer)) then
		return false
	end

	if (not self:isCurrentPhaseIngredient(pObj)) then
		CreatureObject(pPlayer):sendSystemMessage("@crafting:cc_not_valid_item")
		return false
	end

	if (TangibleObject(pObj):getCraftersName() ~= CreatureObject(pPlayer):getFirstName()) then
		CreatureObject(pPlayer):sendSystemMessage("@crafting:cc_not_item_crafter")
		return false
	end

	local ingredientQuality = self:calculateIngredientQuality(pObj, pPlayer)

	if (ingredientQuality < 0) then
		CreatureObject(pPlayer):sendSystemMessage("@crafting:cc_not_min_quality")
		return false
	end

	return true
end

function VillageCommunityCrafting:giveSchematics(pPlayer)
	if (not VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local ingredientList = self.phaseInfo[currentPhase].ingredients

	for i = 1, #ingredientList, 1 do
		PlayerObject(pGhost):addRewardedSchematic(ingredientList[i].schematic, 2, -1, true)
	end

	local secondaryList = self.phaseInfo[currentPhase].secondarySchematics

	local addSuccess = true
	for i = 1, #secondaryList, 1 do
		local tempSuccess = PlayerObject(pGhost):addRewardedSchematic(secondaryList[i], 2, -1, true)
		
		if (not tempSuccess) then
			addSuccess = false
		end
	end
	
	return addSuccess
end

function VillageCommunityCrafting:removeSchematics(pPlayer, phase)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ingredientList = self.phaseInfo[phase].ingredients

	for i = 1, #ingredientList, 1 do
		PlayerObject(pGhost):removeRewardedSchematic(ingredientList[i].schematic, true)
	end

	local secondaryList = self.phaseInfo[phase].secondarySchematics

	for i = 1, #secondaryList, 1 do
		PlayerObject(pGhost):removeRewardedSchematic(secondaryList[i], true)
	end
end

function VillageCommunityCrafting:doEndOfPhaseCheck()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()

	local pMap = self:getActiveCrafterList(phaseID)

	if (pMap == nil) then
		return
	end

	local crafterMap = LuaQuestVectorMap(pMap)

	local mapSize = crafterMap:getMapSize()

	for i = 0, mapSize - 1, 1 do
		local playerID = crafterMap:getMapKeyAtIndex(i)

		local pPlayer = getCreatureObject(tonumber(playerID))

		if (pPlayer ~= nil) then
			local pGhost = CreatureObject(pPlayer):getPlayerObject()

			if (pGhost ~= nil and PlayerObject(pGhost):isOnline()) then
				if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_MAIN) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_MAIN)) then
					QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_MAIN)
					QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_01)
					QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_02)
				end

				if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_MAIN) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_MAIN)) then
					QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_MAIN)
					QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_01)
					QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_02)
				end

				self:removeSchematics(pPlayer, currentPhase)
			end
		end
	end
end

function VillageCommunityCrafting:doEndOfPhasePrizes()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()

	if (currentPhase ~= 2 and currentPhase ~= 3) then
		return
	end

	local minIngredients = self:getMinimumIngredients()

	local ingredientList = self.phaseInfo[currentPhase].ingredients

	local pNameMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":playerNames")

	if (pNameMap == nil) then
		printLuaError("Failed to grab player name vector in VillageCommunityCrafting:doEndOfPhasePrizes.")
		return
	end

	local nameMap = LuaQuestVectorMap(pNameMap)

	local overallQuality = { }
	local overallQuantity = { }

	local totalPlayers = nameMap:getMapSize()

	if (totalPlayers == 0) then
		return
	end

	for i = 1, totalPlayers, 1 do
		local playerID = tonumber(nameMap:getMapKeyAtIndex(i - 1))
		local defaultAdd = { playerID, 0 }
		table.insert(overallQuality, defaultAdd)
		table.insert(overallQuantity, defaultAdd)
	end

	for i = 1, #ingredientList, 1 do
		local prizeTable = ingredientList[i].prize

		local pQuantityMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. i .. ":quantity")

		if (pQuantityMap == nil) then
			printLuaError("Failed to grab quantity stats vector map for slot " .. i .. " in VillageCommunityCrafting:doEndOfPhasePrizes.")
			return
		end

		local quantityMap = LuaQuestVectorMap(pQuantityMap)

		local pQualityMap = getQuestVectorMap("VillageCCStatsTable:" .. phaseID .. ":slot" .. i .. ":quality")

		if (pQualityMap == nil) then
			printLuaError("Failed to grab quality stats vector map for slot " .. i .. " in VillageCommunityCrafting:doEndOfPhasePrizes.")
			return
		end

		local qualityMap = LuaQuestVectorMap(pQualityMap)

		local statTable = { }

		for i = 1, totalPlayers, 1 do
			local playerID = qualityMap:getMapKeyAtIndex(i - 1)
			local playerQuality = tonumber(qualityMap:getMapRow(playerID))
			local playerQuantity = tonumber(quantityMap:getMapRow(playerID))

			-- Only add player data to reward list if they completed the quest
			if (playerQuantity ~= nil and playerQuantity >= minIngredients) then
				local dataTable = { playerID, playerQuality, playerQuantity }
				table.insert(statTable, dataTable)

				for i = 1, #overallQuality, 1 do
					if (overallQuality[i][1] == tonumber(playerID)) then
						overallQuality[i][2] = overallQuality[i][2] + playerQuality
					end
				end

				for i = 1, #overallQuantity, 1 do
					if (overallQuantity[i][1] == tonumber(playerID)) then
						overallQuantity[i][2] = overallQuantity[i][2] + playerQuantity
					end
				end
			end
		end

		if #statTable ~= 0 then
			table.sort(statTable, self.qualitySort)

			local qualityWinner = statTable[1][1]

			local pQualityWinner = getCreatureObject(qualityWinner)

			if (pQualityWinner ~= nil) then
				local pInventory = CreatureObject(pQualityWinner):getSlottedObject("inventory")

				if pInventory ~= nil then
					local pItem = giveItem(pInventory, prizeTable.quality, -1)
				end
			end


			table.sort(statTable, self.quantitySort)

			local quantityWinner = statTable[1][1]

			local pQuantityWinner = getCreatureObject(quantityWinner)

			if (pQuantityWinner ~= nil) then
				local pInventory = CreatureObject(pQuantityWinner):getSlottedObject("inventory")

				if pInventory ~= nil then
					local pItem = giveItem(pInventory, prizeTable.quantity, -1)
				end
			end
		end
	end


	if (#overallQuality > 0) then
		table.sort(overallQuality, self.prizeSort)

		local overallQualityWinner = overallQuality[1][1]

		local pQualityWinner = getCreatureObject(overallQualityWinner)

		if (pQualityWinner ~= nil) then
			local pInventory = CreatureObject(pQualityWinner):getSlottedObject("inventory")

			if pInventory ~= nil then
				local pItem = giveItem(pInventory, self.phaseInfo[currentPhase].overallPrize.quality, -1)
			end
		end
	end

	if (#overallQuantity > 0) then
		table.sort(overallQuantity, self.prizeSort)

		local overallQuantityWinner = overallQuantity[1][1]

		local pQuantityWinner = getCreatureObject(overallQuantityWinner)

		if (pQuantityWinner ~= nil) then
			local pInventory = CreatureObject(pQuantityWinner):getSlottedObject("inventory")

			if pInventory ~= nil then
				local pItem = giveItem(pInventory, self.phaseInfo[currentPhase].overallPrize.quantity, -1)
			end
		end
	end
end

function VillageCommunityCrafting.prizeSort(a,b)
	return b[2] < a[2]
end

QtQcContainerComponent = {}

function QtQcContainerComponent:transferObject(pContainer, pObj, slot)
	if (pObj == nil) then
		return 0
	end

	local pPlayer = VillageJediManagerTownship:getObjOwner(pObj)

	if (pPlayer == nil or pContainer == nil) then
		return 0
	end

	if (not VillageCommunityCrafting:addIngredient(pPlayer, pObj)) then
		return 0
	end

	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local ingredientsNeeded = VillageCommunityCrafting:getIngredientsNeededByPlayer(pPlayer)

	if (ingredientsNeeded == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@crafting:cc_thank_you_done")

		if (currentPhase == 2 and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_MAIN)) then
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_02)
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_MAIN)
			VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_crafting_mastery_technique")
		elseif (currentPhase == 3 and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_MAIN)) then
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_02)
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_MAIN)
			VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_crafting_mastery_experimentation")
		end
	elseif (ingredientsNeeded == 1) then
		CreatureObject(pPlayer):sendSystemMessage("@crafting:cc_thank_you_one")
	else
		local messageString = LuaStringIdChatParameter("@crafting:cc_thank_you_with_counts")
		messageString:setDI(ingredientsNeeded)
		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	end

	SceneObject(pObj):destroyObjectFromWorld()
	SceneObject(pObj):destroyObjectFromDatabase()

	return 1
end

function QtQcContainerComponent:canAddObject(pContainer, pObj, slot)
	if (pObj == nil or pContainer == nil) then
		return -1
	end

	local pPlayer = VillageJediManagerTownship:getObjOwner(pObj)

	if (pPlayer == nil) then
		return -1
	end

	if (not VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
		CreatureObject(pPlayer):sendSystemMessage("@crafting:cc_not_crafting")
		return -1
	end

	return true
end

function QtQcContainerComponent:removeObject(pContainer, pObj, slot)
	return -1
end
