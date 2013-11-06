local realCreateSpawnOldManEvent
local realOldManBelongsToThePlayer
local realScheduleDespawnOfOldMan
local realGiveForceCrystalToPlayer

local OldManMocks = {}

function OldManMocks.setup()
	realCreateSpawnOldManEvent = OldMan.createSpawnOldManEvent
	realOldManBelongsToThePlayer = OldMan.oldManBelongsToThePlayer
	realScheduleDespawnOfOldMan = OldMan.scheduleDespawnOfOldMan
	realGiveForceCrystalToPlayer = OldMan.giveForceCrystalToPlayer
end

function OldManMocks.teardown()
	OldMan.createSpawnOldManEvent = realCreateSpawnOldManEvent
	OldMan.oldManBelongsToThePlayer = realOldManBelongsToThePlayer
	OldMan.scheduleDespawnOfOldMan = realScheduleDespawnOfOldMan
	OldMan.giveForceCrystalToPlayer = realGiveForceCrystalToPlayer
end

function OldManMocks.before_each()
	OldMan.createSpawnOldManEvent = spy.new(function() end)
	OldMan.oldManBelongsToThePlayer = spy.new(function() return false end)
	OldMan.scheduleDespawnOfOldMan = spy.new(function() end)
	OldMan.giveForceCrystalToPlayer = spy.new(function() end)
end

function OldManMocks.after_each()
end

return OldManMocks
