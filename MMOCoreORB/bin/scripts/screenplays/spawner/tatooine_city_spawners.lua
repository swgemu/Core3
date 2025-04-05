TatooineCitySpawners = InterestAreaSpawner:new {
	debug = false,

	screenplayName = "TatooineCitySpawners",
	zoneName = "tatooine",

	-- Chance out of 100 that a spawner has to be activate upon server start. 100 is always activated
	activationChance = 65,

	-- Timer to use for mobile respawn
	respawnTimer = 240,

	-- Force Despawn in minutes (used on mobiles still in combat during spawner removal)
	forceDespawn = 3,

	-- {x, z, y, direction, activeMin, activeMax, inactiveMin, inactiveMax, {{"spawnsTable1", numToSpawn}, {"spawnsTable2", numToSpawn}},
	spawnerData = {
		-- Mos Eisley
		{3260.2, 5.1, -5040.7, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3430.0, 5.0, -5130.2, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3593.6, 5.2, -4988.7, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3748.3, 5.0, -4918.5, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3823.4, 5.0, -4719.6, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3606.2, 5.0, -4614.6, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3333.8, 6.9, -4440.7, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3147.1, 5.1, -4685.8, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3180.2, 4.5, -4987.3, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3319.8, 5.7, -5145.5, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3830.9, 5.0, -4822.1, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3698.0, 5.0, -4649.5, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3495.6, 14.4, -4411.0, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3159.7, 5.6, -4549.4, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{3161.5, 5.0, -4822.2, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},


		-- Mos Espa
		{-2639.0, 5.1, 2439.5, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{-2803.4, 5.6, 2597.5, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{-3130.6, 6.9, 2563.5, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{-3258.8, 5.1, 2198.7, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{-3186.1, 5.0, 1946.6, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{-2939.9, 5.3, 1802.8, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{-2677.0, 5.5, 1860.6, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
		{-2588.5, 5.0, 2219.4, 0, 20, 60, 10, 90, {{"worrt1", 5}, {"worrt2", 4}, {"rill1", 4}, {"rockmite1", 4}, {"womp_rat1", 4}, {"womp_rat2", 5}, {"mound_mite1", 3}, {"dwarf_eopie1", 4}, {"mynock1", 5}}},
	},

	-- A table of different groups of spawns availabe to be assigned to a spawner
	spawnGroups = {
		-- Creatures
		worrt1 = {"minor_worrt"},
		worrt2 = {"worrt"},
		rill1 = {"rill", "rill", "rill", "tempest_rill"},
		rockmite1 = {"rockmite"},
		womp_rat1 = {"womp_rat"},
		womp_rat2 = {"lesser_desert_womp_rat"},
		mound_mite1 = {"mound_mite"},
		dwarf_eopie1 = {"dwarf_eopie"},
		mynock1 = {"tatooine_mynock"},
	},
}

registerScreenPlay("TatooineCitySpawners", true)

function TatooineCitySpawners:start()
	if (not isZoneEnabled(self.zoneName)) then
		return
	end

	if (self.debug) then
		print(self.screenplayName .. " called start() ")
	end

	self:createSpawners()

	if (self.debug) then
		createEvent(20 * 1000, "TatooineCitySpawners", "activateSpawners", nil, "")
	else
		-- delay to start spawners
		createEvent(self.startDelay * 60 * 1000, "TatooineCitySpawners", "activateSpawners", nil, "")
	end
end