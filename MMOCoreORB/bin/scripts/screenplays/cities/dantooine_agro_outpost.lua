DantooineAgroOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DantooineAgroOutpostScreenPlay",

	planet = "dantooine",

	combatPatrol = {"commando", "pirate", "sharpshooter"},
	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "noble_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"cll8_1", "cll8_binary_load_lifter", 1573, 4, -6412, 313, 0, "", false},
		{"r2_1", "r2", 1583.12, 4, -6407.59, 69, 0, "", false},
		{"r3_1", "r3", 1592.98, 4, -6400.58, 80, 0, "", false},

		--NPCs
		{"npc_1", "combatPatrol", 1539, 4, -6407, 34, 0, "", true},
		{"npc_2", "combatPatrol", 1556, 4, -6411, 188, 0, "", true},
		{"npc_3", "patrolNpc", 1547, 4, -6398, 43, 0, "", false},
		{"npc_4", "patrolNpc", 1605, 4, -6377, 55, 0, "", false},
		{"npc_5", "patrolNpc", 1635, 4, -6397, 57, 0, "", false},
		{"npc_6", "patrolNpc", 1614, 4, -6428, 192, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		cll8_1 = {{1573, 4, -6412, 0, false}, {1562, 4, -6417, 0, false}, {1564, 4, -6433, 0, false}, {1560, 4, -6400, 0, true}, {1565, 4, -6400, 0, false}, {1545, 4, -6389, 0, false}, {1564, 4, -6415, 0, false}},
		r2_1 = {{1583, 4, -6407, 0, false}, {1576, 4, -6401, 0, false}, {1581, 4, -6397, 0, false}, {1596, 4, -6405, 0, false}},
		r3_1 = {{1592, 4, -6400, 0, false}, {1581, 4, -6374, 0, false}, {1619, 4, -6368, 0, false}, {1607, 4, -6392, 0, false}, {1596, 4, -6390, 0, false}},

		npc_1 = {{1539, 4, -6407, 0, true}, {1531, 4, -6414, 0, true}, {1532, 3, -6401, 0, true}, {1545, 4, -6402, 0, true}},
		npc_2 = {{1556, 4, -6411, 0, true}, {1544, 4, -6410, 0, true}, {1557, 4, -6418, 0, true}, {1562, 4, -6404, 0, true}},
		npc_3 = {{1547, 4, -6398, 0, true}, {1532, 4, -6387, 0, true}, {1565, 4, -6382, 0, true}, {1555, 4, -6404, 0, true}},
		npc_4 = {{1605, 4, -6377, 0, true}, {1591, 4, -6374, 0, true}, {1604, 4, -6386, 0, true}, {1597, 4, -6380, 0, true}},
		npc_5 = {{1635, 4, -6397, 0, true}, {1646, 4, -6405, 0, true}, {1624, 4, -6412, 0, true}, {1629, 4, -6386, 0, true}},
		npc_6 = {{1614, 4, -6428, 0, true}, {1622, 4, -6434, 0, true}, {1623, 4, -6418, 0, true}, {1610, 4, -6434, 0, true}, {1609, 4, -6421, 0, true}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old"},
	stationaryNpcs = {"artisan", "bodyguard", "bounty_hunter", "businessman", "commoner_technician", "contractor", "entertainer", "explorer", "farmer", "farmer_rancher", "fringer", "gambler", "info_broker", "medic", "mercenary", "miner", "noble",  "pilot", "rancher", "scientist", "slicer"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, 1580, 4,-6439, 200, 0, ""},
		{1, 1571, 4, -6397, 303, 0, ""},
		{1, 1597, 4, -6416, 208, 0, ""},
		{1, 1586, 4, -6398, 189, 0, ""},
		{1, 1575, 4, -6396, 324, 0, ""},
		{1, 1570, 4, -6370, 178, 0, ""},
		{1, 1545, 4, -6370, 287, 0, ""},
		{1, 1558, 4, -6429, 106, 0, ""},
		{1, 1600, 4, -6402, 245, 0, ""},
		{1, 1629, 4, -6370, 225, 0, ""},
		{1, 1558, 4, -6367, 143, 0, ""},
		{1, 1583, 4, -6439, 7, 0, ""},
	},

	mobiles = {
		--In the Cantina
		{"chiss_male",60,3.0,0.6,0.8,-42,6205496, "npc_sitting_chair"},
		{"patron_devaronian",60,-7.5,0.6,5.7,-95,6205497, "npc_standing_drinking"},
		{"bartender",60,-9.1,0.6,5.3,85,6205497, "conversation"},
		{"businessman", 60, 8.90672, 0.625, -2.94252, 244, 6205499, ""},
		{"entertainer",60,-7.77368,0.624999,-5.2158,188,6205498, "happy"},

		--Outside
		{"criminal", 300, 1601, 4, -6367, 109, 0, ""},
		{"ytzosh", 60, 1636.98, 4, -6402.56, 322, 0, ""},
		{"ussox", 60, 1635.07, 4, -6402.37, 322, 0, ""},
		{"yras_shen_jen",60,1572.26,4,-6417.06,75.0582,0, "neutral"},
		{"junk_quich", 0, 1579.04, 4, -6374.52, 48, 0, ""}
	}
}

registerScreenPlay("DantooineAgroOutpostScreenPlay", true)

function DantooineAgroOutpostScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
	end
end

function DantooineAgroOutpostScreenPlay:spawnMobiles()
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
