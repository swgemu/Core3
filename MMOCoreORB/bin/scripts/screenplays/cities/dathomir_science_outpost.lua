DathomirScienceOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DathomirScienceOutpostScreenPlay",

	planet = "dathomir",

	combatPatrol = {"commando", "commoner_technician", "mercenary", "miner", "sharpshooter"},
	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, level, x, z, y, direction, cell, mood, combatPatrol},
		--Droids
		{"cll8_1", "cll8_binary_load_lifter", 1, -107.307, 18, -1603.07, 275.094, 0, "", false},
		{"r3_1", "r3", 1, -78.3142, 18, -1629.93, 144.919, 0, "", false},
		{"r4_1", "r4", 1, -134.195, 18, -1599.14, 45.5678, 0, "", false},

		--NPCs
		{"npc_1", "combatPatrol", 60, -93, 18, -1578, 0, 0, "", true},
		{"npc_2", "combatPatrol", 60, -88, 18, -1606, 350, 0, 0, "", true},
		{"npc_3", "combatPatrol", 60, -74, 18, -1637, 345, 0, 0, "", true},
		{"npc_4", "combatPatrol", 60, -114, 18, -1630, 300, 0, 0, "", true},
		{"npc_5", "combatPatrol", 60, -86, 18, -1555, 219, 0, 0, "", true},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		cll8_1 = {{-107, 18, -1603, 0, true}, {-128, 18, -1589, 0, false}, {-107, 18, -1603, 0, true}, {-95, 18, -1630, 0, false}},
		r3_1 = {{-78, 18, -1629, 0, false}, {-68, 18, -1607, 0, false}, {-91, 18, -1587, 0, false}, {-80, 18, -1573, 0, false}, {-51, 18, -1596, 0, true}},
		r4_1 = {{-134.8, 18, -1599.1, 0, true}, {-122, 18, -1610, 0, false}, {-134.8, 18, -1599.1, 0, true}, {-134, 18, -1588, 0, false}},

		npc_1 = {{-93, 18, -1578, 0, true}, {-77, 18, -1579, 0, true}, {-90, 18, -1570, 0, true}, {-78, 18, -1567, 0, true}},
		npc_2 = {{-88, 18, -1606, 0, true}, {-80, 18, -1623, 0, true}, {-98, 18, -1605, 0, true}, {-77, 18, -1604, 0, true}},
		npc_3 = {{-74, 18, -1637, 0, true}, {-75, 18, -1633, 0, true}, {-82, 18, -1629, 0, true}, {-71, 18, -1638, 0, true}},
		npc_4 = {{-114, 18, -1630, 0, true}, {-90, 18, -1620, 0, true}, {-99, 18, -1606, 0, true}, {-119, 18, -1642, 0, true}},
		npc_5 = {{-86, 18, -1555, 0, true}, {-97, 18, -1564, 0, true}, {-85, 18, -1546, 0, true}, {-91, 18, -1544, 0, true}},
	},
}

registerScreenPlay("DathomirScienceOutpostScreenPlay", true)

function DathomirScienceOutpostScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
	end
end

function DathomirScienceOutpostScreenPlay:spawnMobiles()

	--In a building
	local pNpc = spawnMobile("dathomir", "medic",60,5.1,0.6,-2.2,-51,2835552)
	self:setMoodString(pNpc, "sad")
	pNpc = spawnMobile("dathomir", "contractor",60,6.3,0.6,-6.4,-133,2835573)
	self:setMoodString(pNpc, "nervous")

	--Outside
	spawnMobile("dathomir", "businessman", 60, -70.8878, 18, -1646.08, 315.408, 0)
	spawnMobile("dathomir", "businessman", 60, -64.4958, 18, -1581.42, 63.9635, 0)
	spawnMobile("dathomir", "businessman", 60, -79.6404, 18, -1585.09, 131.623, 0)
	spawnMobile("dathomir", "commoner", 60, -60.7253, 18, -1596.21, 88.2297, 0)
	spawnMobile("dathomir", "commoner", 60, -37.0445, 18, -1587.75, 47.6817, 0)
	spawnMobile("dathomir", "commoner", 60, -78, 18, -1614, 285, 0)
	spawnMobile("dathomir", "commoner", 60, -98.9262, 18, -1590.29, 239.412, 0)
	local pNpc = spawnMobile("dathomir", "explorer", 60, -68.4, 18, -1621.0, 180, 0)
	self:setMoodString(pNpc, "conversation")
	spawnMobile("dathomir", "mercenary", 60, -43.9919, 18, -1585.86, 220.77, 0)
	spawnMobile("dathomir", "scientist", 60, -136.034, 18, -1592.07, 62.5196, 0)
	local pNpc = spawnMobile("dathomir", "commoner_technician", 60, -69.1, 18, -1622.1, 45, 0)
	self:setMoodString(pNpc, "conversation")
	spawnMobile("dathomir", "informant_npc_lvl_3", 0,-68,18,-1565,270,0)

	pNpc = spawnMobile("dathomir", "arnecio_ulvaw_op",60,4.06465,0.624999,2.34456,30.9406,2835570)
	self:setMoodString(pNpc, "neutral")

end
