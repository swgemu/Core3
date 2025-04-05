RoriCitySpawners = InterestAreaSpawner:new {
	debug = false,

	screenplayName = "RoriCitySpawners",
	zoneName = "rori",

	-- Chance out of 100 that a spawner has to be activate upon server start. 100 is always activated
	activationChance = 65,

	-- Timer to use for mobile respawn
	respawnTimer = 240,

	-- Force Despawn in minutes (used on mobiles still in combat during spawner removal)
	forceDespawn = 3,

	-- {x, z, y, direction, activeMin, activeMax, inactiveMin, inactiveMax, {{"spawnsTable1", numToSpawn}, {"spawnsTable2", numToSpawn}},
	spawnerData = {
		-- Restuss
	},

	-- A table of different groups of spawns availabe to be assigned to a spawner
	spawnGroups = {
		-- Creatures

	},
}

registerScreenPlay("RoriCitySpawners", true)

function RoriCitySpawners:start()
	if (not isZoneEnabled(self.zoneName)) then
		return
	end

	if (self.debug) then
		print(self.screenplayName .. " called start() ")
	end

	self:createSpawners()

	if (self.debug) then
		createEvent(20 * 1000, "RoriCitySpawners", "activateSpawners", nil, "")
	else
		-- delay to start spawners
		createEvent(self.startDelay * 60 * 1000, "RoriCitySpawners", "activateSpawners", nil, "")
	end
end
