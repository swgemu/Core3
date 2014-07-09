local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")
require("utils.helpers")


-- Pulled from "quest/force_sensitive/utils.stf"
local unlockableFSBranches =
	{{"Combat Prowess -- Ranged Accuracy",
		"Combat Prowess -- Ranged Speed",
		"Combat Prowess -- Melee Accuracy",
		"Combat Prowess -- Melee Speed"},

	{"Crafting Mastery -- Experimentation",
		"Crafting Mastery -- Assembly",
		"Crafting Mastery -- Repair",
		"Crafting Mastery -- Technique"},

	{"Enhanced Reflexes -- Ranged Defense",
		"Enhanced Reflexes -- Melee Defense",
		"Enhanced Reflexes -- Vehicle Control",
		"Enhanced Reflexes -- Survival"},

	{"Heightened Senses -- Healing",
		"Heightened Senses -- Surveying",
		"Heightened Senses -- Persuasion",
		"Heightened Senses -- Luck"}}
ExperienceConverter = Object:new {
	}

-- See if the player qualifies for the conversion.
-- @param pPlayerObject pointer to the player object of the player.
-- @return a boolean.
function ExperienceConverter.qualifiesForConversation(pCreatureObject)
	-- TODO: Research why Paemos wouldn't converse with player.
	return true
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
		local branchType = v[1]
		local branchNumber = v[2]
		local unlockableBranchesLookup = unlockableFSBranches[branchType]
		local unlockableBranchesInsertString = unlockableBranchesLookup[branchNumber]
		table.insert(theStringsToReturn, unlockableBranchesInsertString)
		Logger:log("Inserted " .. unlockableBranchesInsertString .. " to the return string.", LT_INFO)
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
		ObjectManager.withPlayerObject(creatureObject:getPlayerObject(), function(playerObject)
			ufString = playerObject:getExperienceForType(pType)
			foreach(ufString, function(formattedString)
				local insertionStringFormatted = "@exp_n:" .. formattedString
				table.insert(baseString, insertionStringFormatted)
				Logger:log("Inserted " .. insertionStringFormatted, LT_INFO)
			end)
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
		experienceType = playerObject:getExperienceType(selection)
		amount = playerObject:getExperience(experienceType)
	end)

	return amount
end

return ExperienceConverter
