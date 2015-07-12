local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")
require("utils.helpers")
require("screenplays.screenplay")


-- Pulled from "quest/force_sensitive/utils.stf"
local unlockableFSBranches = {
	FSCombatProwess1 = {state = "FSCombatProwess1", unlockString = "Combat Prowess -- Ranged Accuracy", topBox = "force_sensitive_combat_prowess_ranged_accuracy_04"},
	FSCombatProwess2 = {state = "FSCombatProwess2", unlockString = "Combat Prowess -- Ranged Speed", topBox = "force_sensitive_combat_prowess_ranged_speed_04"},
	FSCombatProwess3 = {state = "FSCombatProwess3", unlockString = "Combat Prowess -- Melee Accuracy", topBox = "force_sensitive_combat_prowess_melee_accuracy_04"},
	FSCombatProwess4 = {state = "FSCombatProwess4", unlockString = "Combat Prowess -- Melee Speed", topBox = "force_sensitive_combat_prowess_melee_speed_04"},
	FSCraftingMastery1 = {state = "FSCraftingMastery1", unlockString = "Crafting Mastery -- Experimentation", topBox = "force_sensitive_crafting_mastery_experimentation_04"},
	FSCraftingMastery2 = {state = "FSCraftingMastery2", unlockString = "Crafting Mastery -- Assembly", topBox = "force_sensitive_crafting_mastery_assembly_04"},
	FSCraftingMastery3 = {state = "FSCraftingMastery3", unlockString = "Crafting Mastery -- Repair", topBox = "force_sensitive_crafting_mastery_repair_04"},
	FSCraftingMastery4 = {state = "FSCraftingMastery4", unlockString = "Crafting Mastery -- Technique", topBox = "force_sensitive_crafting_mastery_technique_04"},
	FSEnhancedReflexes1 = {state = "FSEnhancedReflexes1", unlockString = "Enhanced Reflexes -- Ranged Defense", topBox = "force_sensitive_enhanced_reflexes_ranged_defense_04"},
	FSEnhancedReflexes2 = {state = "FSEnhancedReflexes2", unlockString = "Enhanced Reflexes -- Melee Defense", topBox = "force_sensitive_enhanced_reflexes_melee_defense_04"},
	FSEnhancedReflexes3 = {state = "FSEnhancedReflexes3", unlockString = "Enhanced Reflexes -- Vehicle Control", topBox = "force_sensitive_enhanced_reflexes_vehicle_control_04"},
	FSEnhancedReflexes4 = {state = "FSEnhancedReflexes4", unlockString = "Enhanced Reflexes -- Survival", topBox = "force_sensitive_enhanced_reflexes_survival_04"},
	FSHeightenedSenses1 = {state = "FSHeightenedSenses1", unlockString = "Heightened Senses -- Healing", topBox = "force_sensitive_heightened_senses_healing_04"},
	FSHeightenedSenses2 = {state = "FSHeightenedSenses2", unlockString = "Heightened Senses -- Surveying", topBox = "force_sensitive_heightened_senses_surveying_04"},
	FSHeightenedSenses3 = {state = "FSHeightenedSenses3", unlockString =	"Heightened Senses -- Persuasion", topBox = "force_sensitive_heightened_senses_persuasion_04"},
	FSHeightenedSenses4 = {state = "FSHeightenedSenses4", unlockString =	"Heightened Senses -- Luck", topBox = "force_sensitive_heightened_senses_luck_04"}
}

-- These are the 3 types of FS experience for regex searches, full strings not needed for each type, just least specific.
local XpCombat =
	{
		{"combat_general", 3},
		{"squadleader", 90},
		{"bountyhunter", 1},
		{"combat_melee", 30},
		{"combat_ranged", 30}
	}

local XpSenses =
	{
		{"bio_engineer_dna_harvesting", 3},
		{"political", 3},
		{"slicing",  3},
		{"merchant",  4},
		{"resource_harvesting_inorganic",  5},
		{"imagedesigner", 7},
		{"scout",  8},
		{"creaturehandler",  9},
		{"dance",  10},
		{"music",  10},
		{"entertainer_healing",  10},
		{"camp",  10},
		{"medical",  10},
		{"trapping",  25},
	}

local XpCrafting =
	{
		{"crafting_bio_engineer_creature",  4},
		{"crafting_bio_engineer_tissue",  5},
		{"crafting_c", 5},
		{"crafting_d", 5},
		{"crafting_f", 5},
		{"crafting_m", 5},
		{"crafting_sc", 5},
		{"crafting_sp", 5},
		{"crafting_w", 5},
		{"crafting_general", 8},
		{"crafting_structure_general", 35}
	}

ExperienceConverter = Object:new {}

-- Since the logic flow of the conversation calls set always before get, it should work, but just in case...
function ExperienceConverter:setSuiTransferExperienceSelection(var, oid)
	if (readStringData("suiTransferExperienceSelection:" .. oid) ~= nil) then
		deleteStringData("suiTransferExperienceSelection:"  .. oid)
	end
	if (var ~= nil) then
		writeStringData("suiTransferExperienceSelection:"  .. oid, var)
	end
end

function ExperienceConverter:getSuiTransferExperienceSelection(oid)
	return readStringData("suiTransferExperienceSelection:"  .. oid)
end

function ExperienceConverter:deleteSuiTransferExperienceSelection(oid)
	return deleteStringData("suiTransferExperienceSelection:"  .. oid)
end


function ExperienceConverter:setSuiTransferExperienceType(var, oid)
	if (readData("suiTransferExperienceType:" .. oid) ~= nil) then
		deleteData("suiTransferExperienceType:"  .. oid)
	end
	if (var ~= nil) then
		writeData("suiTransferExperienceType:"  .. oid, var)
	end
end

function ExperienceConverter:getSuiTransferExperienceType(oid)
	return readData("suiTransferExperienceType:"  .. oid)
end

function ExperienceConverter:deleteSuiTransferExperienceType(oid)
	return deleteData("suiTransferExperienceType:"  .. oid)
end

-- See if the player qualifies for the conversion.
-- @param pPlayerObject pointer to the player object of the player.
-- @return a boolean.
function ExperienceConverter.qualifiesForConversation(pCreatureObject)
	-- TODO: Research why Paemos wouldn't converse with player.
	if (pCreatureObject == nil) then
		return false
	end

	return true
end

-- Get the next unlockable branches that the player qualifies for.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return table of strings of the branches ready to unlock.
function ExperienceConverter:getNextUnlockableBranches(pCreatureObject)
	if (pCreatureObject == nil) then
		return nil
	end

	local trees = {}
	local insertion = nil


	foreach(unlockableFSBranches, function(theTable)
		local checkTrees = getQuestStatus(CreatureObject(pCreatureObject):getObjectID() .. ":" .. theTable.state)
		if (checkTrees ~= nil and checkTrees ~= "trained") then
			table.insert(trees, theTable.unlockString)
		end
	end)

	if (table.getn(trees) > 0) then
		return trees
	else
		return nil
	end
end

function ExperienceConverter:setBranchTrained(oid, branchBox)
	foreach(unlockableFSBranches, function(theTable)
		if (theTable.topBox == branchBox) then
			setQuestStatus(oid .. ":" .. theTable.state, "trained")
		end
	end)
end

-- Get the highest box from the tables above for the trainer.
function ExperienceConverter:getHighestBoxForTrainer(selection)
	local boxName = nil

	foreach(unlockableFSBranches, function(theTable)
		local theString = theTable.unlockString
		if (theString == selection) then
			boxName = theTable.topBox
		end
	end)

	return boxName
end

function ExperienceConverter:getExperienceForConversion(pCreature, theType)

	if (pCreature == nil) then
		return nil
	end

	local returnTable = {}

	local inputTable = {}

	if (theType == 0 or theType == 3) then
		inputTable = XpCombat
	elseif (theType == 1) then
		inputTable = XpSenses
	elseif (theType == 2) then
		inputTable = XpCrafting
	end

	local expList = {}

	ObjectManager.withCreaturePlayerObject(pCreature, function(playerObject)
		expList = playerObject:getExperienceList()
	end)

	if (expList == nil) then
		return nil
	end

	for i = 1, #expList do
		if (self:containsKey(inputTable, expList[i])) then
			table.insert(returnTable, "@exp_n:" .. expList[i])
		end
	end

	return returnTable

end

function ExperienceConverter:getExperienceRatio(experienceType, theType)

	local returnAmount = nil

	local inputTable = {}

	if (theType == 0 or theType == 3) then
		inputTable = XpCombat
	elseif (theType == 1) then
		inputTable = XpSenses
	elseif (theType == 2) then
		inputTable = XpCrafting
	end


	returnAmount = self:getValue(inputTable, experienceType)

	if (returnAmount == nil) then
		return 0
	end

	return returnAmount
end


-- Generic search function for the strings in the tables above.
function ExperienceConverter:containsKey(table, element)
	for i = 1, #table do
		if (string.find(element, table[i][1]) ~= nil) then
			return true
		end
	end
	return false
end

-- Generic search function for the ratio in the tables above.
function ExperienceConverter:getValue(table, element)
	for i = 1, #table do
		if (string.find(element, table[i][1]) ~= nil) then
			return table[i][2]
		end
	end
end

return ExperienceConverter
