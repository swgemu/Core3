local SpawnMobiles = require("utils.spawn_mobiles")
local realSpawnMobiles
local realDespawnMobiles

local SpawnMobilesMocks = SpawnMobiles
SpawnMobilesMocks.mocks = {}

function SpawnMobilesMocks.mocks.setup()
	realSpawnMobiles = SpawnMobiles.spawnMobiles
	realDespawnMobiles = SpawnMobiles.despawnMobiles
end

function SpawnMobilesMocks.mocks.teardown()
	SpawnMobiles.spawnMobiles = realSpawnMobiles
	SpawnMobiles.despawnMobiles = realDespawnMobiles
end

function SpawnMobilesMocks.mocks.before_each()
	SpawnMobiles.spawnMobiles = spy.new(function() end)
	SpawnMobiles.despawnMobiles = spy.new(function() end)
end

function SpawnMobilesMocks.mocks.after_each()
end

return SpawnMobilesMocks
