CorelliaCitySpawners = InterestAreaSpawner:new {
	debug = false,

	screenplayName = "CorelliaCitySpawners",
	zoneName = "corellia",

	-- Chance out of 100 that a spawner has to be activate upon server start. 100 is always activated
	activationChance = 65,

	-- Timer to use for mobile respawn
	respawnTimer = 240,

	-- Force Despawn in minutes (used on mobiles still in combat during spawner removal)
	forceDespawn = 3,

	-- {x, z, y, direction, activeMin, activeMax, inactiveMin, inactiveMax, {{"spawnsTable1", numToSpawn}, {"spawnsTable2", numToSpawn}},
	spawnerData = {
		-- Coronet
		{-24, 28, -4937, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{267, 29, -4656, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{168, 28, -4267, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-237, 7, -3959, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-693, 7, -4259, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-705, 4, -4632, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-496, 27, -4840, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-219.2, 28.1, -4943.2, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-652.7, 2.9, -4791.1, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-653.4, 22.8, -4421.2, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-531.5, 26.6, -4160.8, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-292.2, 27.9, -4077.5, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-101.0, 28.0, -4093.2, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{241.0, 28.0, -4473.8, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{138.6, 16.1, -4872.5, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},

		-- Tyrena
		{-5012, 14, -2747, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-4933, 24.7, -2126, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-5456, 9, -2480, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-4862.1, 11.4, -2449.1, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-5227.9, 30.2, -2186.7, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-5686.1, 21.1, -2634.4, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-5545.6, 11.4, -2922.1, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
		{-5311.8, 3.0, -2831.4, 0, 20, 60, 10, 90, {{"meatlump1", 4}, {"meatlump2", 4}, {"meatlump3", 3}, {"meatlump4", 3}, {"ragtag1", 4}, {"ragtag2", 4}, {"ragtag3", 3}, {"ragtag4", 3}}},
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

registerScreenPlay("CorelliaCitySpawners", true)

function CorelliaCitySpawners:start()
	if (not isZoneEnabled(self.zoneName)) then
		return
	end

	if (self.debug) then
		print(self.screenplayName .. " called start() ")
	end

	self:createSpawners()

	if (self.debug) then
		createEvent(20 * 1000, "CorelliaCitySpawners", "activateSpawners", nil, "")
	else
		-- delay to start spawners
		createEvent(self.startDelay * 60 * 1000, "CorelliaCitySpawners", "activateSpawners", nil, "")
	end
end