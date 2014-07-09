local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")
require("utils.helpers")

local unlockableFSBranches =
	{{"force_sensitive_combat_prowess_ranged_accuracy",
		"force_sensitive_combat_prowess_ranged_speed",
		"force_sensitive_combat_prowess_melee_accuracy",
		"force_sensitive_combat_prowess_melee_speed"},

	{"force_sensitive_crafting_mastery_experimentation",
		"force_sensitive_crafting_mastery_assembly",
		"force_sensitive_crafting_mastery_repair",
		"force_sensitive_crafting_mastery_technique"},

	{"force_sensitive_enhanced_reflexes_ranged_defense",
		"force_sensitive_enhanced_reflexes_melee_defense",
		"force_sensitive_enhanced_reflexes_ranged_defense",
		"force_sensitive_enhanced_reflexes_ranged_survival"},

	{"force_sensitive_heightened_senses_healing",
		"force_sensitive_heightened_senses_surveying",
		"force_sensitive_heightened_senses_persuasion",
		"force_sensitive_heightened_senses_luck"}}



ExperienceConverter = Object:new {
	}

-- See if the player qualifies for the conversion.
-- @param pPlayerObject pointer to the player object of the player.
-- @return a boolean.
function ExperienceConverter.qualifiesForConversation(pCreatureObject)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		ObjectManager.withPlayerObject(creatureObject:getPlayerObject(), function(playerObject)
			local check = playerObject:getExperienceType(0)
			if (check == nil or check == "") then
				return false
			else
				return true
			end
		end)
	end)
end

-- Get the next unlockable branches that the player qualifies for.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return a string of the branches ready to unlock.
function ExperienceConverter:getNextUnlockableBranches(pCreatureObject)

	local trees = {}
	local returnString = nil

	for i = 1,4 do -- Four boxes per state.
		local combatProwessStates = ExperienceConverter:getHighestScreenPlayState(pCreatureObject, "FSCombatProwess", i)
		if (combatProwessStates == true) then
			table.insert(trees,  {1, i})
		end

		local craftingMasteryStates = ExperienceConverter:getHighestScreenPlayState(pCreatureObject, "FSCraftingMastery", i)
		if (craftingMasteryStates == true) then
			table.insert(trees, {2, i})
		end

		local enhancedReflexesStates = ExperienceConverter:getHighestScreenPlayState(pCreatureObject, "FSEnhancedReflexes", i)
		if (enhancedReflexesStates == true) then
			table.insert(trees, {3 , i})
		end

		local heightenedSensesStates = ExperienceConverter:getHighestScreenPlayState(pCreatureObject, "FSHeightenedSenses", i)
		if (heightenedSensesStates == true) then
			table.insert(trees, {4 , i})
		end
	end
	if (table.getn(trees) > 0) then
		returnString = ExperienceConverter:formatReturnStringForUnlockableBranches(trees)
	end
	return returnString
end

function ExperienceConverter:formatReturnStringForUnlockableBranches(pNumberTable)

	local theStringsToReturn = {}
	for i,v in ipairs(pNumberTable) do
		local theFirstIteration = v[1]
		local theSecondIteration = v[2]
		local unlockableBranchesLookup = unlockableFSBranches[theFirstIteration]
		local unlockableBranchesInsertString = unlockableBranchesLookup[theSecondIteration]
		table.insert(theStringsToReturn, unlockableBranchesInsertString)
	end
	return theStringsToReturn
end

-- Get the screenplay states specified.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param pScreenPlayState string pointer to the screenplay state requested.
-- @param pUnlockNumber int pointer to the number unlocked (1-4).
-- @return an boolean that it is unlockable.
function ExperienceConverter:getHighestScreenPlayState(pCreatureObject, pScreenPlayState, pUnlockNumber)

	local check = pScreenPlayState .. pUnlockNumber
	Logger:log("Checking player for screenplaystate " .. check, LT_INFO)
	local state = ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return (creatureObject:hasScreenPlayState(1, check) == 1)
	end) == true
	return state

end

function ExperienceConverter:getExperienceForConversion(pPlayer, pType)
	local baseString = {}
	local ufString = nil

	ObjectManager.withCreatureObject(pPlayer, function(creatureObject)
		ufString = creatureObject:getExperienceForType(pType)
		foreach(ufString, function(formattedString)
			formattedString = "@exp_n:" .. ufString[i]
			table.insert(baseString, formattedString)
			Logger:log("Inserted " .. formattedString, LT_INFO)
		end)
	end)

	return baseString
end

function ExperienceConverter:getExperienceAmount(pPlayer, pSelection)
	local experienceType = nil
	local amount = nil
	-- Unformat string for retrieval.
	local selection = string.sub(pSelection, 7, string.len(pSelection))
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(creatureObject, playerObject)
		experienceType = creatureObject:getExperienceType(selection)
		amount = playerObject:getExperience(experienceType)
	end)

	return amount
end

return ExperienceConverter
