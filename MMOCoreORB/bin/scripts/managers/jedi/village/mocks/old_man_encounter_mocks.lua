local OldManEncounter = require("managers.jedi.village.old_man_encounter")

local realStart
local realDoesOldManBelongToThePlayer
local realScheduleDespawnOfOldMan
local realGiveForceCrystalToPlayer
local realRemoveForceCrystalFromPlayer

local OldManEncounterMocks = OldManEncounter
OldManEncounterMocks.mocks = {}

function OldManEncounterMocks.mocks.setup()
	realStart = OldManEncounter.createSpawnOldManEvent
	realDoesOldManBelongToThePlayer = OldManEncounter.doesOldManBelongToThePlayer
	realScheduleDespawnOfOldMan = OldManEncounter.scheduleDespawnOfOldMan
	realGiveForceCrystalToPlayer = OldManEncounter.giveForceCrystalToPlayer
	realRemoveForceCrystalFromPlayer = OldManEncounter.removeForceCrystalFromPlayer
end

function OldManEncounterMocks.mocks.teardown()
	OldManEncounter.createSpawnOldManEvent = realStart
	OldManEncounter.doesOldManBelongToThePlayer = realDoesOldManBelongToThePlayer
	OldManEncounter.scheduleDespawnOfOldMan = realScheduleDespawnOfOldMan
	OldManEncounter.giveForceCrystalToPlayer = realGiveForceCrystalToPlayer
	OldManEncounter.removeForceCrystalFromPlayer = realRemoveForceCrystalFromPlayer
end

function OldManEncounterMocks.mocks.before_each()
	OldManEncounter.start = spy.new(function() end)
	OldManEncounter.doesOldManBelongToThePlayer = spy.new(function() return false end)
	OldManEncounter.scheduleDespawnOfOldMan = spy.new(function() end)
	OldManEncounter.giveForceCrystalToPlayer = spy.new(function() end)
	OldManEncounter.removeForceCrystalFromPlayer = spy.new(function() end)
end

function OldManEncounterMocks.mocks.after_each()
end

return OldManEncounterMocks
