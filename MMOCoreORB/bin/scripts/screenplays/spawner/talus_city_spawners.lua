TalusCitySpawners = InterestAreaSpawner:new {
	debug = false,

	screenplayName = "TalusCitySpawners",
	zoneName = "talus",

	-- Chance out of 100 that a spawner has to be activate upon server start. 100 is always activated
	activationChance = 65,

	-- Timer to use for mobile respawn
	respawnTimer = 240,

	-- Force Despawn in minutes (used on mobiles still in combat during spawner removal)
	forceDespawn = 3,

	-- {x, z, y, direction, activeMin, activeMax, inactiveMin, inactiveMax, {{"spawnsTable1", numToSpawn}, {"spawnsTable2", numToSpawn}},
	spawnerData = {
	},

	-- A table of different groups of spawns availabe to be assigned to a spawner
	spawnGroups = {
		-- Meatlumps
		meatlump1 = {"meatlump_buffoon"},
		meatlump2 = {"meatlump_fool", "meatlump_stooge"},
		meatlump3 = {"meatlump_clod", "meatlump_cretin"},
		meatlump4 = {"meatlump_oaf", "meatlump_loon"},

		-- Ragtags
		ragtag1 = {"ragtag_kook"},
		ragtag2 = {"ragtag_loon"},
		ragtag3 = {"ragtag_lunatic", "ragtag_maniac"},
		ragtag4 = {"ragtag_mercenary", "ragtag_thug"},
	},
}

registerScreenPlay("TalusCitySpawners", true)

function TalusCitySpawners:start()
	if (not isZoneEnabled(self.zoneName)) then
		return
	end

	if (self.debug) then
		print(self.screenplayName .. " called start() ")
	end

	self:createSpawners()

	if (self.debug) then
		createEvent(20 * 1000, "TalusCitySpawners", "activateSpawners", nil, "")
	else
		-- delay to start spawners
		createEvent(self.startDelay * 60 * 1000, "TalusCitySpawners", "activateSpawners", nil, "")
	end
end