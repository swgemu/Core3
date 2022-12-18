TatooineAnchorheadScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineAnchorheadScreenPlay",

	planet = "tatooine",

	gcwMobs = {
		{"specforce_technician", 65.685, 52, -5349.49, -4, 0, "", true},
		{"specforce_technician", 49.2, 52, -5351, 350, 0, "", true},
		{"specforce_technician", 125.5, 52, -5416, 279.008, 0, "", true},
		{"specforce_technician", 55.2, 52.6, -5332.5, 184.005, 0, "", true},
		{"specforce_heavy_weapons_specialist", 68, 52, -5382, 67, 0, "", true},
		{"rebel_specforce_captain", 67, 52, -5366.5, 95, 0, "", true},
		{"rebel_specforce_captain", 31.4, 51.1006, -5350.3, 203.975, 0, "", true},
		{"rebel_specforce_pathfinder", 31, 51.9725, -5337, 270.008, 0, "", true},
		{"rebel_specforce_pathfinder", 76.5, 52, -5361.1, 329.737, 0, "", true},
		{"rebel_specforce_pathfinder", 135.1, 52, -5374.9, 83.0024, 0, "", true},
		{"rebel_specforce_pathfinder", 123.6, 52, -5368, 235, 0, "", true},
		{"rebel_specforce_pathfinder", 89.9, 52, -5393.8, 313.009, 0, "", true},
		{"rebel_specforce_pathfinder", 151, 52, -5316, 37.8685, 0, "", true},
		{"rebel_specforce_pathfinder", 159, 52, -5320, 331.012, 0, "", true},
	},

	patrolNpcs = {"commoner_fat_patrol", "commoner_old_patrol", "commoner_tatooine_patrol", "commoner_technician_patrol", "explorer_patrol", "gambler_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"r3_1", "r3", -180, 65, -5314, 96, 0, "", false},
		{"r3_2", "r3", 116, 52, -5341, 2, 0, "", false},
		{"r4_1", "r4", 75, 52, -5355, 178, 0, "", false},

		--NPCs
		{"npc_1", "patrolNpc", 73, 52, -5329, 324, 0, "", false},
		{"npc_2", "patrolNpc", 39, 52, -5345, 179, 0, "", false},
		{"npc_3", "patrolNpc", 134, 52, -5333, 67, 0, "", false},
		{"npc_4", "patrolNpc", 123, 52, -5377, 88, 0, "", false},
		{"npc_5", "patrolNpc", 83, 52, -5390, 61, 0, "", false},
		{"npc_6", "patrolNpc", -144, 65, -5301, 250, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		r3_1 = {{-180, 65, -5314, 0, false}, {-184, 65, -5306, 0, true}, {-179, 65, -5298, 0, true}, {-231, 65, -5295, 0, false}, {-201, 65, -5305, 0, false}},
		r3_2 = {{116, 52, -5341, 0, false}, {116, 52, -5365, 0, false}, {124, 52, -5397, 0, false}, {116, 52, -5365, 0, false}, {113.1, 52, -5359.2, 0, true}, {78.6, 52, -5358.7, 0, false}, {113.1, 52, -5359.2, 0, false}},
		r4_1 = {{75, 52, -5355, 0, false}, {74, 52, -5345, 0, true}, {67, 52, -5344, 0, false}, {44, 52, -5344, 0, false}, {41, 52, -5337.3, 0, false}, {68, 52, -5337, 0, false}},

		npc_1 = {{73, 52, -5329, 0, true}, {65, 52, -5315, 0, true}, {79, 52, -5327, 0, true}, {74, 52, -5312, 0, true}, {73, 52, -5336, 0, true}},
		npc_2 = {{39, 52, -5345, 0, true}, {28, 51, -5344, 0, true}, {42, 52, -5338, 0, true}, {56, 52, -5245, 0, true}, {46, 52, -5348, 0, true}},
		npc_3 = {{134, 52, -5333, 0, true}, {153, 52, -5330, 0, true}, {153, 52, -5322, 0, false}, {143, 52, -5330, 0, true}},
		npc_4 = {{123, 52, -5377, 0, true}, {129, 52, -5371, 0, true}, {124, 52, -5387, 0, true}, {119, 52, -5395, 0, true}},
		npc_5 = {{83, 52, -5390, 0, true}, {79, 52, -5377, 0, true}, {76, 52, -5388, 0, true}, {87, 52, -5391, 0, true}, {82, 52, -5397, 0, true}},
		npc_6 = {{-144, 65, -5301, 0, true}, {-136, 65, -5313, 0, true}, {-113, 65, -5309, 0, true}, {-124, 65, -5323, 0, true}, {-132, 65, -5302, 0, true}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old", "commoner_tatooine"},
	stationaryNpcs = {"artisan", "bodyguard", "bothan_diplomat", "bounty_hunter", "businessman", "commoner_technician", "contractor", "entertainer", "explorer", "farmer", "farmer_rancher", "fringer",
			"gambler", "info_broker", "medic", "mercenary", "miner", "noble", "official", "pilot", "rancher", "scavenger", "scientist", "slicer"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{ 1, 74.6127, 52, -5382.24, 106, 0, ""}, {1, 150.383, 52, -5327.33, 143, 0, ""}, {1, 114.69, 52, -5404.19, 89, 0, ""}, { 1, -108.399, 65, -5298.05, 0, 0, "conversation"},
		{ 1, -162.748,65,-5312.84, 0, 0, "conversation"}, {1, -108.399, 65, -5297.05, 180, 0, "conversation"}, { 1, -162.748, 65, -5311.84, 180, 0, "conversation"}, { 1, -143.907, 65, -5335.05, 0, 0, "conversation"},
		{ 1, -143.907, 65, -5334.05, 180, 0, "conversation"},
	},

	mobiles = {
		--Tavern
		{"borra_setas", 60, 9.51111, 0.408271, -0.736723, 320.12, 1213345, "worried"},
		{"commoner_tatooine", 60, -9.4, 0.4, 2.0, 161, 1213345, "npc_standing_drinking"},
		{"trainer_doctor", 0, 1.53792, 1.00421, 6.82596, 265, 1213346, ""},
		{"rebel_recruiter", 60, -6.22005, -3.96617, -6.58904, 194.653, 1213349, ""},

		--Tavern west
		{"bounty_hunter", 60, 7.7, -4.0, -4.0, 138, 3355393, "angry"},
		{"businessman", 60, 8.5, -4.0, -5.3, -37, 3355393, "worried"},
		{"commoner_technician", 60, 8.4, 0.4, -9.5, 126, 3355387, "neutral"},
		{"commoner_fat", 60, -8.8, 1.0, 6.5, -99, 3355388, "happy"},

		--Outside
		{"junk_dealer", 0, 110.87, 52, -5428.19, 53, 0, ""}
	}
}

registerScreenPlay("TatooineAnchorheadScreenPlay", true)

function TatooineAnchorheadScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
		self:spawnSceneObjects()
		self:spawnGcwMobiles()
	end
end

function TatooineAnchorheadScreenPlay:spawnSceneObjects()

	--Tavern
	spawnSceneObject("tatooine", "object/mobile/le_repair_droid.iff", -0.3, -4.0, -3.7, 1213349, math.rad(90) )
end

function TatooineAnchorheadScreenPlay:spawnMobiles()
	local mobiles = self.mobiles

	for i = 1, #mobiles, 1 do
		local mob = mobiles[i]

		-- {template, respawn, x, z, y, direction, cell, mood}
		local pMobile = spawnMobile(self.planet, mob[1], mob[2], mob[3], mob[4], mob[5], mob[6], mob[7])

		if (pMobile ~= nil) then
			if mob[8] ~= "" then
				CreatureObject(pMobile):setMoodString(mob[8])
			end

			AiAgent(pMobile):addCreatureFlag(AI_STATIC)

			if CreatureObject(pMobile):getPvpStatusBitmask() == 0 then
				CreatureObject(pMobile):clearOptionBit(AIENABLED)
			end
		end
	end

	--Outside
	--[[spawnMobile("tatooine", "bantha",300,216.9,11.7,-5425.4,-121,0)
	spawnMobile("tatooine", "cu_pa",300,75.5625,88.9439,-5217.41,276.531,0)
	spawnMobile("tatooine", "cu_pa",300,81.1976,85.0672,-5200.6,174.759,0)
	spawnMobile("tatooine", "cu_pa",300,14.564,23.6794,-5543.66,99.0125,0)
	spawnMobile("tatooine", "cu_pa",300,26.8762,12.236,-5564.46,284.743,0)
	spawnMobile("tatooine", "cu_pa",300,163.943,12.072,-5473.22,272.381,0)
	spawnMobile("tatooine", "cu_pa",300,210.837,16.4247,-5464.01,32.0514,0)
	spawnMobile("tatooine", "cu_pa",300,188.14,9.71503,-5485.52,63.2364,0)
	spawnMobile("tatooine", "cu_pa",300,186.305,14.9233,-5467.36,145.471,0)
	spawnMobile("tatooine", "cu_pa",300,166.736,4.42212,-5483.28,304.088,0)
	spawnMobile("tatooine", "rebel_recruiter",60,69.6872,52,-5349.47,360.011,0)
	spawnMobile("tatooine", "rill",300,3.34558,86.6525,-5245.25,82.0905,0)
	spawnMobile("tatooine", "rill",300,-26.4483,85.5717,-5227.67,257.612,0)
	spawnMobile("tatooine", "rill",300,-4.51558,88.9463,-5226.49,314.221,0)
	spawnMobile("tatooine", "rill",300,16.8025,87.749,-5249.62,280.51,0)
	spawnMobile("tatooine", "zucca_boar",300,176.37,29.6614,-5228.44,23.7572,0)
	spawnMobile("tatooine", "zucca_boar",300,177.37,29.3367,-5227.44,202.645,0)
	spawnMobile("tatooine", "zucca_boar",300,171.993,33.695,-5229.99,181.173,0)
	spawnMobile("tatooine", "zucca_boar",300,-35.6792,30,-5439.35,11.3066,0)]]
end
