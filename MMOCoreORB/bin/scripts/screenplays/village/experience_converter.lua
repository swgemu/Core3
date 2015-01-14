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

-- See if the player qualifies for the conversion.
-- @param pPlayerObject pointer to the player object of the player.
-- @return a boolean.
function ExperienceConverter.qualifiesForConversation(pCreatureObject)
	-- TODO: Research why Paemos wouldn't converse with player.
	return true
end

-- Get the next unlockable branches that the player qualifies for.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return table of strings of the branches ready to unlock.
function ExperienceConverter:getNextUnlockableBranches(pCreatureObject)

	local trees = {}
	local insertion = nil

	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		ObjectManager.withPlayerObject(creatureObject:getPlayerObject(), function(playerObject)
			local checkTrees = playerObject:getForceSensitiveUnlockedBranches()
			foreach(unlockableFSBranches, function(theTable)
				local state = ExperienceConverter:getHighestScreenPlayState(pCreatureObject, theTable.state)
				if ((state) and (not ExperienceConverter:contains(checkTrees, theTable.topBox))) then
					table.insert(trees, theTable.unlockString)
				end
			end)
		end)
	end)

	if (table.getn(trees) > 0) then
		return trees
	else
		return nil
	end

end

-- Get the screenplay states specified.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param pScreenPlayState string pointer to the screenplay state requested.
-- @param pUnlockNumber int pointer to the number unlocked (1-4).
-- @return an boolean that it is unlockable.
function ExperienceConverter:getHighestScreenPlayState(pCreatureObject, pScreenPlayState)

	local check = pScreenPlayState
	local state = ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return (creatureObject:hasScreenPlayState(1, check) == 1)
	end) == true
	return state

end

function ExperienceConverter:getExperienceForConversion(pPlayer, pType)
	local baseString = {}
	local ufString = nil

	ObjectManager.withCreatureObject(pPlayer, function(creatureObject)
		ObjectManager.withPlayerObject(creatureObject:getPlayerObject(), function(playerObject)
			ufString = playerObject:getExperienceForType(pType)
			foreach(ufString, function(formattedString)
				local insertionStringFormatted = "@exp_n:" .. formattedString
				table.insert(baseString, insertionStringFormatted)
			end)
		end)
	end)

	return baseString
end

-- Get the experience amount for the selected experience type.
function ExperienceConverter:getExperienceAmount(pPlayer, pSelection)
	local amount = nil
	-- Unformat string for retrieval.
	ObjectManager.withCreaturePlayerObject(pPlayer, function(playerObject)
		local experienceType = playerObject:getExperienceType(pSelection)
		amount = playerObject:getExperience(experienceType)
	end)

	return amount
end

function ExperienceConverter:getExperienceRatio(pPlayer, pSelection)
	local experienceType = nil
	local ratio = nil
	ObjectManager.withCreaturePlayerObject(pPlayer, function(playerObject)
		experienceType = playerObject:getExperienceType(pSelection)
		ratio = playerObject:getExperienceRatio(experienceType)
	end)

	return ratio
end

-- Get the highest box from the tables above for the trainer.
function ExperienceConverter:getHighestBoxForTrainer(pSelection)
	local boxName = nil

	foreach(unlockableFSBranches, function(theTable)
		local theString = theTable.unlockString
		if (theString == pSelection) then
			boxName = theTable.topBox
		end
	end)

	return boxName
end

-- Remove corresponding state they just learned the branch for.
function ExperienceConverter:removeScreenPlayState(pCreature, pNameForState)

	foreach(unlockableFSBranches, function(theTable)
		if (theTable.unlockString == pNameForState) then
			ObjectManager.withCreatureObject(pCreature, function(creatureObject)
				creatureObject:setScreenPlayState(0, theTable.state)
			end)
		end
	end)

end

-- Generic search function.
function ExperienceConverter:contains(table, element)
	for _, value in pairs(table) do
		if value == element then
			return true
		end
	end
	return false
end

return ExperienceConverter
