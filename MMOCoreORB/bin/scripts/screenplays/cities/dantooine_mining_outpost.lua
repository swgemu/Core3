DantooineMiningOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DantooineMiningOutpostScreenPlay",

	planet = "dantooine",

	combatPatrol = {"commando", "mercenary", "miner", "sharpshooter"},
	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"r2_1", "r2", -635.747, 3, 2503.81, 354, 0, "", false},
		{"r4_1", "r4", -643.739, 3, 2506.86, 129, 0, "", false},
		{"r4_2", "r4", -666.582, 3, 2494.33, 121, 0, "", false},

		--NPCs

		{"npc_1", "patrolNpc", -602, 3, 2506, 285, 0, "", false},
		{"npc_2", "patrolNpc", -647, 3, 2449, 73, 0, "", false},
		{"npc_3", "combatPatrol", -616, 3, 2509, 314, 0, "", true},
		{"npc_4", "combatPatrol", -562, 3, 2512, 108, 0, "", true},
		{"npc_5", "combatPatrol", -658, 3, 2480, 334, 0, "", true},
		{"npc_6", "combatPatrol", -665, 3, 2465, 120, 0, "", true},
		{"npc_7", "combatPatrol", -665, 3, 2462, 261, 0, "", true},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		r2_1 = {{-635, 3, 2503, 0, true}, {-627, 3, 2494, 0, false}, {-600, 3, 2494, 0, true}, {-611, 3, 2483, 0, false}, {-622, 3, 2484, 0, false}},
		r4_1 = {{-643, 3, 2506, 0, true}, {-648, 3, 2510, 0, true}, {-655, 3, 2498, 0, true}, {-643, 3, 2508, 0, false}},
		r4_2 = {{-666, 3, 2494, 0, false}, {-638, 3, 2456, 0, false}, {-658, 3, 2442, 0, false}, {-658, 3, 2465, 0, false}, {-649, 3, 2484, 0, false}},

		npc_1 = {{-602, 3, 2506, 0, true}, {-595, 3, 2521, 0, true}, {-604, 3, 2499, 0, true}, {-570, 3, 2512, 0, true}},
		npc_2 = {{-647, 3, 2449, 0, true}, {-656, 3, 2429, 0, true}, {-664, 3, 2433, 0, true}, {-653, 3, 2453, 0, true}},
		npc_3 = {{-616, 3, 2509, 0, true}, {-612, 3, 2530, 0, true}, {-600, 3, 2511, 0, true}, {-621, 3, 2503, 0, true}},
		npc_4 = {{-562, 3, 2512, 0, true}, {-572, 3, 2520, 0, true}, {-551, 1, 2510, 0, true}, {-566, 2, 2500, 0, true}, {-572, 3, 2509, 0, true}},
		npc_5 = {{-658, 3, 2480, 0, true}, {-646, 3, 2465, 0, true}, {-655, 3, 2470, 0, true}},
		npc_6 = {{-665, 3, 2465, 0, true}, {-680, 3, 2480, 0, true}, {-692, 3, 2477, 0, true}, {-676, 3, 2475, 0, true}, {-663, 3, 2470, 0, true}},
		npc_7 = {{-665, 3, 2462, 0, true}, {-654, 3, 2453, 0, true}, {-659, 3, 2425, 0, true}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old"},
	stationaryNpcs = {"bodyguard", "bounty_hunter", "businessman", "commoner_technician", "contractor", "entertainer", "explorer", "fringer", "gambler", "medic", "mercenary", "miner", "noble", "pilot", "scientist", "slicer"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, -603, 3, 2485, 345, 0, ""},
		{1, -647, 3, 2456, 181, 0, ""},
		{1, -636, 3, 2507, 155, 0, ""},
		{1, -575, 3, 2503, 36, 0, ""},
		{1, -627, 3, 2531, 81, 0, ""},
		{1, -600, 3, 2548, 16, 0, ""},
		{1, -580, 3, 2530, 29, 0, ""},
		{1, -628, 3, 2509, 149, 0, ""},
		{1, -641, 3, 2472, 264, 0, ""},
		{1, -662, 3, 2482, 92, 0, ""},
		{1, -631, 3, 2463, 302, 0, ""},
		{1, -611, 3, 2488, 311, 0, ""},
	},

	mobiles = {
		--In The Cantina
		{"artisan",60,8.8,0.6,-4.9,-93,6205567, "sad"},
		{"businessman", 60, -8, 0.6, -6, 83, 6205566, ""},
		{"adwan_turoldine",60,-9.37871,0.625,2.98841,82.9313,6205565, "neutral"},

		--Outside
		{"criminal", 300, -620, 3, 2450, 281, 0, ""},
		{"kess_yarrow",60,-623.484,3,2481.77,149.192,0, "neutral"},
		{"rane_yarrow",60,-625.457,3,2479.41,86.8842,0, "neutral"},
		{"fern_yarrow",60,-625.684,3,2481.19,119.665,0, "neutral"},
		{"planet_record_keeper_dantooine", 60, -604.016, 3, 2538.15, 200.426, 0, ""}
	}
}

registerScreenPlay("DantooineMiningOutpostScreenPlay", true)

function DantooineMiningOutpostScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
	end
end

function DantooineMiningOutpostScreenPlay:spawnMobiles()
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
end
