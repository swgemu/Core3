DantooineAgroOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	planet = "dantooine",

	combatPatrol = {"commando", "pirate", "sharpshooter"},
	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "noble_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, level, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"cll8_1", "cll8_binary_load_lifter", 60, 1573, 4, -6412, 313, 0, "", false},
		{"r2_1", "r2", 60, 1583.12, 4, -6407.59, 69, 0, "", false},
		{"r3_1", "r3", 60, 1592.98, 4, -6400.58, 80, 0, "", false},

		--NPCs
		{"npc_1", "combatPatrol", 300, 1539, 4, -6407, 34, 0, "", true},
		{"npc_2", "combatPatrol", 300, 1556, 4, -6411, 188, 0, "", true},
		{"npc_3", "patrolNpc", 1, 1547, 4, -6398, 43, 0, "", false},
		{"npc_4", "patrolNpc", 1, 1605, 4, -6377, 55, 0, "", false},
		{"npc_5", "patrolNpc", 1, 1635, 4, -6397, 57, 0, "", false},
		{"npc_6", "patrolNpc", 1, 1614, 4, -6428, 192, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}} 1 = no delay 0 = delay
		cll8_1 = {{1573, 4, -6412, 0, 1}, {1562, 4, -6417, 0, 1}, {1564, 4, -6433, 0, 1}, {1560, 4, -6400, 0, 0}, {1565, 4, -6400, 0, 1}, {1545, 4, -6389, 0, 1}, {1564, 4, -6415, 0, 1}},
		r2_1 = {{1583, 4, -6407, 0, 1}, {1576, 4, -6401, 0, 1}, {1581, 4, -6397, 0, 1}, {1596, 4, -6405, 0, 1}},
		r3_1 = {{1592, 4, -6400, 0, 1}, {1581, 4, -6374, 0, 1}, {1619, 4, -6368, 0, 1}, {1607, 4, -6392, 0, 1}, {1596, 4, -6390, 0, 1}},

		npc_1 = {{1539, 4, -6407, 0, 0}, {1531, 4, -6414, 0, 0}, {1532, 3, -6401, 0, 0}, {1545, 4, -6402, 0, 0}},
		npc_2 = {{1556, 4, -6411, 0, 0}, {1544, 4, -6410, 0, 0}, {1557, 4, -6418, 0, 0}, {1562, 4, -6404, 0, 0}},
		npc_3 = {{1547, 4, -6398, 0, 0}, {1532, 4, -6387, 0, 0}, {1565, 4, -6382, 0, 0}, {1555, 4, -6404, 0, 0}},
		npc_4 = {{1605, 4, -6377, 0, 0}, {1591, 4, -6374, 0, 0}, {1604, 4, -6386, 0, 0}, {1597, 4, -6380, 0, 0}},
		npc_5 = {{1635, 4, -6397, 0, 0}, {1646, 4, -6405, 0, 0}, {1624, 4, -6412, 0, 0}, {1629, 4, -6386, 0, 0}},
		npc_6 = {{1614, 4, -6428, 0, 0}, {1622, 4, -6434, 0, 0}, {1623, 4, -6418, 0, 0}, {1610, 4, -6434, 0, 0}, {1609, 4, -6421, 0, 0}},
	},

	screenplayName = "DantooineAgroOutpostScreenPlay"
}

registerScreenPlay("DantooineAgroOutpostScreenPlay", true)

function DantooineAgroOutpostScreenPlay:start()
	if (isZoneEnabled("dantooine")) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
	end
end

function DantooineAgroOutpostScreenPlay:spawnMobiles()

	--In the Cantina
	local pNpc = spawnMobile("dantooine", "chiss_male",60,3.0,0.6,0.8,-42,6205496)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("dantooine", "patron_devaronian",60,-7.5,0.6,5.7,-95,6205497)
	self:setMoodString(pNpc, "npc_standing_drinking")
	pNpc = spawnMobile("dantooine", "bartender",60,-9.1,0.6,5.3,85,6205497)
	self:setMoodString(pNpc, "conversation")
	spawnMobile("dantooine", "businessman", 60, 8.90672, 0.625, -2.94252, 244, 6205499)
	pNpc = spawnMobile("dantooine", "entertainer",60,-7.77368,0.624999,-5.2158,188,6205498)
	self:setMoodString(pNpc, "happy")

	--Outside
	spawnMobile("dantooine", "businessman", 60, 1580, 4,-6439, 200, 0)
	spawnMobile("dantooine", "businessman", 60, 1571, 4, -6397, 303, 0)
	spawnMobile("dantooine", "businessman", 60, 1597, 4, -6416, 208, 0)
	spawnMobile("dantooine", "commoner", 60, 1586, 4, -6398, 189, 0)
	spawnMobile("dantooine", "commoner", 60, 1575, 4, -6396, 324, 0)
	spawnMobile("dantooine", "commoner", 60, 1570, 4, -6370, 178, 0)
	spawnMobile("dantooine", "commoner", 60, 1545, 4, -6370, 287, 0)
	spawnMobile("dantooine", "commoner", 60, 1558, 4, -6429, 106, 0)
	spawnMobile("dantooine", "commoner", 60, 1600, 4, -6402, 245, 0)
	spawnMobile("dantooine", "commoner", 60, 1629, 4, -6370, 225, 0)
	spawnMobile("dantooine", "criminal", 300, 1601, 4, -6367, 109, 0)
	spawnMobile("dantooine", "noble", 60, 1558, 4, -6367, 143, 0)
	spawnMobile("dantooine", "scientist", 60, 1583, 4, -6439, 7, 0)
	spawnMobile("dantooine", "ytzosh", 60, 1636.98, 4, -6402.56, 322, 0)
	spawnMobile("dantooine", "ussox", 60, 1635.07, 4, -6402.37, 322, 0)
	pNpc = spawnMobile("dantooine", "yras_shen_jen",60,1572.26,4,-6417.06,75.0582,0)
	self:setMoodString(pNpc, "neutral")
	spawnMobile("dantooine", "junk_quich", 0, 1579.04, 4, -6374.52, 48, 0)
end
