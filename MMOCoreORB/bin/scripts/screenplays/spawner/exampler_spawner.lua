ExampleSpawners = InterestAreaSpawner:new {
	debug = false,

	screenplayName = "ExampleSpawners",
	zoneName = "example",

	-- Chance out of 100 that a spawner has to be activate upon server start. 100 is always activated
	activationChance = 100,

	-- Timer to use for mobile respawn
	respawnTimer = 300,

	-- Force Despawn in minutes (used on mobiles still in combat during spawner removal)
	forceDespawn = 3,

	-- {x, z, y, direction, activeMin, activeMax, inactiveMin, inactiveMax, {{"spawnsTable1", numToSpawn}, {"spawnsTable2", numToSpawn}},
	spawnerData = {
		-- Spawner
		{-24, 28, -4937, 270, 20, 60, 10, 90, {{"group1", 2}, {"group2", 3}}},
	},

	-- A table of different groups of spawns availabe to be assigned to a spawner
	spawnGroups = {
		group1 = {"dark_jedi_knight"},
		group2 = {"dark_adept"},
	},
}

registerScreenPlay("ExampleSpawners", true)

function ExampleSpawners:start()
	if (not isZoneEnabled(self.zoneName)) then
		return
	end

	if (self.debug) then
		print(self.screenplayName .. " called start() ")
	end

	self:createSpawners()

	if (self.debug) then
		createEvent(20 * 1000, "ExampleSpawners", "activateSpawners", nil, "")
	else
		-- 5 minute delay to start spawners
		createEvent(5 * 60 * 1000, "ExampleSpawners", "activateSpawners", nil, "")
	end
end