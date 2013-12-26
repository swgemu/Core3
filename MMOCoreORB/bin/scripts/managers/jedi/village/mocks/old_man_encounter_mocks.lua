local OldManEncounter = require("managers.jedi.village.old_man_encounter")

local realStart
local realDoesOldManBelongToThePlayer
local realScheduleDespawnOfOldMan
local realGiveForceCrystalToPlayer

local OldManMocks = OldManEncounter
OldManMocks.mocks = {}

function OldManMocks.mocks.setup()
	realStart = OldManEncounter.createSpawnOldManEvent
	realDoesOldManBelongToThePlayer = OldManEncounter.doesOldManBelongToThePlayer
	realScheduleDespawnOfOldMan = OldManEncounter.scheduleDespawnOfOldMan
	realGiveForceCrystalToPlayer = OldManEncounter.giveForceCrystalToPlayer
end

function OldManMocks.mocks.teardown()
	OldManEncounter.createSpawnOldManEvent = realStart
	OldManEncounter.doesOldManBelongToThePlayer = realDoesOldManBelongToThePlayer
	OldManEncounter.scheduleDespawnOfOldMan = realScheduleDespawnOfOldMan
	OldManEncounter.giveForceCrystalToPlayer = realGiveForceCrystalToPlayer
end

function OldManMocks.mocks.before_each()
	OldManEncounter.start = spy.new(function() end)
	OldManEncounter.doesOldManBelongToThePlayer = spy.new(function() return false end)
	OldManEncounter.scheduleDespawnOfOldMan = spy.new(function() end)
	OldManEncounter.giveForceCrystalToPlayer = spy.new(function() end)
end

function OldManMocks.mocks.after_each()
end

return OldManMocks
