EndorSmugglerOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "EndorSmugglerOutpostScreenPlay",

	planet = "endor",

	combatPatrol = {"smuggler"},
	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "noble_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},

		--Droid
		{"r3_1", "r3", -950.7, 73, 1542.7, 331.8, 0, "neutral", false},

		--NPCs
		{"npc_1", "combatPatrol", -890, 76, 1591, 253, 0, "", true},
		{"npc_2", "combatPatrol", -889, 76, 1591, 182, 0, "", true},
		{"npc_3", "combatPatrol", -889, 76, 1592, 319, 0, "", true},
		{"npc_4", "patrolNpc", -896, 80, 1621, 243, 0, "", false},
		{"npc_5", "patrolNpc", -880, 76, 1604, 30, 0, "", false},
		{"npc_6", "patrolNpc", -880, 76, 1638, 11, 0, "", false},
		{"npc_7", "patrolNpc", -841, 79, 1602, 240, 0, "", false},
		{"npc_8", "patrolNpc", -838, 76, 1574, 333, 0, "", false},
		{"npc_9", "patrolNpc", -851, 80, 1555, 238, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		r3_1 = {{-951, 73, 1542, 0, false}, {-905, 76, 1582, 0, false}, {-902, 77, 1564, 0, false}, {-911, 76, 1573, 0, false}},

		npc_1 = {{-890, 76, 1591, 0, true}, {-893, 76, 1582, 0, true}, {-895, 76, 1590, 0, true}, {-901, 76, 1579, 0, true}},
		npc_2 = {{-889, 76, 1591, 0, true}, {-886, 73, 1591, 0, true}, {-875, 76, 1585, 0, true}},
		npc_3 = {{-889, 76, 1592, 0, true}, {-888, 76, 1597, 0, true}, {-883, 76, 1601, 0, true}, {-884, 76, 1595, 0, true}, {-880, 76, 1593, 0, true}},
		npc_4 = {{-896, 80, 1621, 0, true}, {-905, 80, 1604, 0, true}, {-910, 80, 1595, 0, true}, {-898, 80, 1605, 0, true}, {-897, 80, 1630, 0, true}},
		npc_5 = {{-880, 76, 1604, 0, true}, {-880, 76, 1623, 0, true}, {-871, 76, 1618, 0, true}, {-881, 76, 1613, 0, true}, {-881, 76, 1598, 0, true}},
		npc_6 = {{-880, 76, 1638, 0, true}, {-875, 76, 1636, 0, true}, {-874, 76, 1643, 0, true}, {-867, 75, 1643, 0, true}},
		npc_7 = {{-841, 79, 1602, 0, true}, {-838, 79, 1595, 0, true}, {-833, 80, 1607, 0, true}, {-826, 80, 1602, 0, true}},
		npc_8 = {{-838, 76, 1574, 0, true}, {-848, 76, 1575, 0, true}, {-850, 76, 1583, 0, true}, {-834, 76, 1576, 0, true}},
		npc_9 = {{-851, 80, 1555, 0, true}, {-853, 80, 1568, 0, true}, {-838, 79, 1555, 0, true}, {-841, 80, 1545, 0, true}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old"},
	stationaryNpcs = {"bodyguard", "bounty_hunter", "businessman", "commoner_technician", "contractor", "entertainer", "explorer", "fringer", "gambler", "medic", "mercenary", "miner", "noble", "pilot", "rancher", "scientist", "slicer"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, -899.977, 78, 1548.09, 107.809, 0, ""},
		{1, -828.009, 76, 1573.28, 320.402, 0, ""},
		{1, -864.293, 79.5001, 1598.78, 184.686, 0, ""},
		{1, -875.462, 80.0597, 1571.89, 84.1865, 0, ""},
		{1, -956, 73, 1554, 135, 0, ""},
		{1, -874.656, 80, 1564.76, 270, 0, ""},
		{1, -845.301, 79.5, 1599.49, 197.393, 0, ""},
		{1, -829.243, 76, 1567.61, 95.886, 0, ""},
	},
}

registerScreenPlay("EndorSmugglerOutpostScreenPlay", true)

function EndorSmugglerOutpostScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
	end
end

function EndorSmugglerOutpostScreenPlay:spawnMobiles()
	--mission term building
	local pNpc = spawnMobile("endor", "commoner_technician",60,3.5,0.1,3.9,0,3605972)
	if pNpc ~= nil then
		self:setMoodString(pNpc, "sad")
		CreatureObject(pNpc):setOptionsBitmask(0)
	end

	--tavern
	local pNpc = spawnMobile("endor", "commoner_old",60,1.0,0.7,-4.4,0,6645605)
	if pNpc ~= nil then
		self:setMoodString(pNpc, "npc_sitting_chair")
		CreatureObject(pNpc):setOptionsBitmask(0)
	end
end
