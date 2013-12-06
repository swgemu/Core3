local SpawnMobiles = require("utils.spawn_mobiles")
local realSpawnMobiles
local realDespawnMobiles
local realGetSpawnedMobiles

local SpawnMobilesMocks = SpawnMobiles
SpawnMobilesMocks.mocks = {}

function SpawnMobilesMocks.mocks.setup()
	realSpawnMobiles = SpawnMobiles.spawnMobiles
	realDespawnMobiles = SpawnMobiles.despawnMobiles
	realGetSpawnedMobiles = SpawnMobiles.getSpawnedMobiles
end

function SpawnMobilesMocks.mocks.teardown()
	SpawnMobiles.spawnMobiles = realSpawnMobiles
	SpawnMobiles.despawnMobiles = realDespawnMobiles
	SpawnMobiles.getSpawnedMobiles = realGetSpawnedMobiles
end

function SpawnMobilesMocks.mocks.before_each()
	SpawnMobiles.spawnMobiles = spy.new(function() return nil end)
	SpawnMobiles.despawnMobiles = spy.new(function() end)
	SpawnMobiles.getSpawnedMobiles = spy.new(function() return nil end)
end

function SpawnMobilesMocks.mocks.after_each()
end

return SpawnMobilesMocks
