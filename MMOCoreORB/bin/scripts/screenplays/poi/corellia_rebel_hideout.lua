local ObjectManager = require("managers.object.object_manager")

RebelHideoutScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "RebelHideoutScreenPlay",

	turrets = {
		{ template = "object/installation/turret/turret_tower_large.iff", x = -6559.3, z = 404, y = 5965.1 },
		{ template = "object/installation/turret/turret_tower_large.iff", x = -6536.3, z = 404, y = 5942.1 },
		{ template = "object/installation/turret/turret_tower_large.iff", x = -6510.0, z = 404, y = 5931.7 },
		{ template = "object/installation/turret/turret_tower_large.iff", x = -6474.8, z = 404, y = 5938.6 },
		{ template = "object/installation/turret/turret_tower_large.iff", x = -6443.1, z = 404, y = 5999.0 },
		{ template = "object/installation/turret/turret_tower_large.iff", x = -6457.1, z = 404, y = 6031.5 },
	},

}

registerScreenPlay("RebelHideoutScreenPlay", true)

function RebelHideoutScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function RebelHideoutScreenPlay:spawnSceneObjects()
	for i = 1, 6, 1 do
		local turretData = self.turrets[i]
		local pTurret = spawnSceneObject("corellia", turretData.template, turretData.x, turretData.z, turretData.y, 0, 0.707107, 0, 0.707107, 0)

		if pTurret ~= nil then
			local turret = TangibleObject(pTurret)
			turret:setFaction(FACTIONREBEL)
			turret:setPvpStatusBitmask(1)
		end

		writeData(SceneObject(pTurret):getObjectID() .. ":rebel_hideout:turret_index", i)
		createObserver(OBJECTDESTRUCTION, "RebelHideoutScreenPlay", "notifyTurretDestroyed", pTurret)
	end
	
end

function RebelHideoutScreenPlay:notifyTurretDestroyed(pTurret, pPlayer)
	ObjectManager.withSceneObject(pTurret, function(turret)
		local turretData = self.turrets[readData(turret:getObjectID() .. ":rebel_hideout:turret_index")]
		turret:destroyObjectFromWorld()
		createEvent(1800000, "RebelHideoutScreenPlay", "respawnTurret", pTurret)
	end)
	CreatureObject(pPlayer):clearCombatState(1)
	return 0
end

function RebelHideoutScreenPlay:respawnTurret(pTurret)
	TangibleObject(pTurret):setConditionDamage(0, false)
	local turretData = self.turrets[readData(SceneObject(pTurret):getObjectID() .. ":rebel_hideout:turret_index")]
	local pZone = getZoneByName("corellia")
	SceneObject(pZone):transferObject(pTurret, -1, true)
end

function RebelHideoutScreenPlay:spawnMobiles()

	--South Entrance
	spawnMobile("corellia", "rebel_first_lieutenant", 300, -6565.580, 405.006, 5923.700, 143.563, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6560.940, 405.000, 5927.760, 138.910, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6563.200, 405.000, 5925.570, 120.821, 0)
	
	--South Barricade
	spawnMobile("corellia", "rebel_first_lieutenant", 300, -6548.290, 405.000, 5926.740, -103.284, 0)
	spawnMobile("corellia", "rebel_army_captain", 300, -6548.200, 405.000, 5928.340, -129.786, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6502.670, 405.000, 5909.410, 175.100, 0)
	spawnMobile("corellia", "rebel_corporal", 300, -6503.990, 405.000, 5911.760, 27.118, 0)
	spawnMobile("corellia", "rebel_medic", 300, -6503.130, 405.000, 5912.200, 68.721, 0)
	spawnMobile("corellia", "rebel_master_sergeant", 300, -6543.650, 405.000, 5920.500, -124.500, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6542.400, 405.000, 5918.670, 145.313, 0)
	spawnMobile("corellia", "rebel_corporal", 300, -6534.340, 405.000, 5909.920, -166.802, 0)
	spawnMobile("corellia", "rebel_corporal", 300, -6529.080, 405.000, 5908.170, -159.830, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6519.640, 405.000, 5907.710, 144.610, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6513.880, 405.000, 5909.050, -175.920, 0)	
	
	-- South East Entrance
	spawnMobile("corellia", "rebel_trooper", 300, -6482.090, 405.168, 5901.830, 68.976, 0)
	spawnMobile("corellia", "rebel_first_lieutenant", 300, -6482.890, 405.000, 5907.930, 79.267, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6482.180, 405.000, 5905.760, 163.796, 0)
	
	--Wall Patrol #1
	spawnMobile("corellia", "rebel_commando", 300, -6447.450, 405.000, 5929.710, 38.208, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6445.180, 405.000, 5928.150, 35.316, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6444.260, 405.000, 5930.650, 19.903, 0)
	
	--Wall Patrol #2
	spawnMobile("corellia", "rebel_trooper", 300, -6423.140, 405.000, 6001.140, 7.939, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6419.490, 405.000, 6001.510, 90.132, 0)
	
	--North Entrance
	spawnMobile("corellia", "rebel_commando", 300, -6428.810, 405.000, 6032.930, -108.869, 0)
	spawnMobile("corellia", "rebel_first_lieutenant", 300, -6423.450, 405.002, 6036.610, 25.600, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6425.940, 405.000, 6034.360, 50.529, 0)
	
	--Wall Patrol #3
	spawnMobile("corellia", "rebel_trooper", 300, -6463.840, 405.000, 6066.600, 59.420, 0)
	spawnMobile("corellia", "rebel_master_sergeant", 300, -6462.740, 405.000, 6071.330, 53.659, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6466.890, 405.000, 6073.040, 63.546, 0)
	spawnMobile("corellia", "rebel_corporal", 300, -6470.990, 405.000, 6069.880, 70.154, 0)
	
	--Wall Patrol #4
	spawnMobile("corellia", "rebel_commando", 300, -6551.150, 405.000, 6066.900, -128.616, 0)
	spawnMobile("corellia", "rebel_corporal", 300, -6551.660, 405.000, 6066.480, -128.647, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6555.700, 405.000, 6063.690, 39.408, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6561.750, 405.000, 6059.500, -142.099, 0)
	
	--Wall Patrol #5
	spawnMobile("corellia", "rebel_commando", 300, -6592.180, 405.000, 5977.550, 171.341, 0)
	spawnMobile("corellia", "rebel_corporal", 300, -6598.610, 404.396, 5975.050, -172.328, 0)
	spawnMobile("corellia", "rebel_corporal", 300, -6594.390, 404.997, 5970.980, 154.120, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6591.050, 405.000, 5964.250, 85.091, 0)
	
	-- Forward Patrols
	spawnMobile("corellia", "rebel_scout", 300, -6550.790, 398.098, 5879.210, -134.828, 0)
	spawnMobile("corellia", "rebel_specforce_sergeant", 300, -6554.250, 397.741, 5877.160, -137.742, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6589.460, 407.842, 5868.430, -154.996, 0)
	spawnMobile("corellia", "rebel_scout", 300, -6594.440, 406.481, 5868.690, 143.249, 0)
	spawnMobile("corellia", "rebel_scout", 300, -6541.190, 397.559, 5852.590, -140.247, 0)
	spawnMobile("corellia", "rebel_scout", 300, -6523.350, 403.544, 5863.080, -154.540, 0)
	
	-- South Ramp
	spawnMobile("corellia", "rebel_corporal", 300, -6561.680, 405.000, 5940.370, -140.616, 0)
	
	--South Stairs
	spawnMobile("corellia", "rebel_corporal", 300, -6546.770, 398.000, 5956.870, 52.042, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6541.760, 398.000, 5953.480, 35.992, 0)
	
	--South East Stairs
	spawnMobile("corellia", "rebel_trooper", 300, -6492.260, 398.000, 5939.580, 11.765, 0)
	spawnMobile("corellia", "rebel_first_lieutenant", 300, -6498.480, 398.000, 5938.420, 10.799, 0)
	
	--Southeast Ramp
	spawnMobile("corellia", "rebel_trooper", 300, -6489.260, 405.000, 5916.220, 162.333, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6493.550, 405.000, 5915.540, 163.230, 0)
	
	--Main Building Entrance
	spawnMobile("corellia", "rebel_major", 300, -6530.480, 398.000, 5973.650, -136.004, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6522.890, 398.000, 5965.850, 133.708, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6517.160, 398.000, 5963.470, 12.022, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6516.800, 398.000, 5965.590, -143.274, 0)
	
	-- South Building
	spawnMobile("corellia", "rebel_trooper", 300, -6500.960, 398.000, 5951.110, 2.598, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6498.560, 398.000, 5951.120, 66.456, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6489.680, 398.000, 5969.860, 81.557, 0)
	
	--East Building
	spawnMobile("corellia", "rebel_trooper", 300, -6472.870, 398.000, 5967.040, 21.978, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6475.130, 398.000, 5967.190, 62.918, 0)
	
	--East Shuttle Pad
	spawnMobile("corellia", "rebel_pilot", 300, -6463.900, 398.000, 5959.650, -171.915, 0)
	spawnMobile("corellia", "rebel_pilot", 300, -6460.170, 398.000, 5948.910, 43.707, 0)
	spawnMobile("corellia", "rebel_army_captain", 300, -6444.160, 398.000, 5970.670, -147.901, 0)
	spawnMobile("corellia", "rebel_medic", 300, -6447.130, 398.000, 5973.380, 46.885, 0)
	
	--North Stairs
	spawnMobile("corellia", "rebel_trooper", 300, -6455.630, 398.000, 6015.340, 153.865, 0)
	
	--North Ramp
	spawnMobile("corellia", "rebel_commando", 300, -6435.710, 405.000, 6025.170, 60.815, 0)
	spawnMobile("corellia", "rebel_corporal", 300, -6434.130, 405.000, 6021.730, 132.782, 0)
	
	--North Terminal
	spawnMobile("corellia", "rebel_corporal", 300, -6481.820, 398.000, 6012.120, 40.388, 0)
	
	--North Building
	spawnMobile("corellia", "rebel_trooper", 300, -6482.900, 398.000, 6030.100, 137.700, 0)
	spawnMobile("corellia", "rebel_major", 300, -6482.670, 398.000, 6032.300, -20.057, 0)
	
	--North West Building
	spawnMobile("corellia", "rebel_trooper", 300, -6495.350, 398.000, 6037.590, 64.533, 0)
	
	--West Shuttle Pad
	spawnMobile("corellia", "rebel_pilot", 300, -6520.390, 398.000, 6040.800, 39.000, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6518.020, 398.000, 6041.320, -140.642, 0)
	spawnMobile("corellia", "rebel_major_general", 300, -6508.990, 398.000, 6049.510, 84.004, 0)
	
	--West Building
	spawnMobile("corellia", "rebel_trooper", 300, -6555.870, 398.000, 6024.350, 132.165, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6554.090, 398.000, 6021.700, 143.914, 0)
	
	--South West Building
	spawnMobile("corellia", "rebel_trooper", 300, -6553.450, 398.000, 5997.370, -130.451, 0)
	spawnMobile("corellia", "rebel_sergeant", 300, -6551.510, 398.000, 6006.530, 104.969, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6553.990, 398.000, 6014.380, 108.643, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6552.290, 398.000, 6013.850, 108.056, 0)
	
	--Power Generator
	spawnMobile("corellia", "rebel_scout", 300, -6533.410, 398.000, 6002.590, 98.259, 0)
	spawnMobile("corellia", "rebel_army_captain", 300, -6537.930, 398.000, 5997.470, -177.213, 0)
	
	--Stairs to Roof
	spawnMobile("corellia", "rebel_trooper", 300, -6495.300, 398.000, 6023.640, 60.714, 0)
	spawnMobile("corellia", "rebel_warrant_officer_i", 300, -6497.560, 398.000, 6021.480, 58.871, 0)
	
	--Roof Patrol #1
	spawnMobile("corellia", "rebel_trooper", 300, -6483.280, 405.000, 5997.160, 43.988, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6481.750, 405.001, 5998.750, 53.122, 0)
	spawnMobile("corellia", "rebel_sergeant", 300, -6510.910, 405.000, 6015.780, -134.845, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6508.950, 405.000, 6013.350, -136.068, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6511.240, 405.000, 6012.820, -139.432, 0)
	
	--Roof Office Entrance
	spawnMobile("corellia", "rebel_commando", 300, -6528.640, 405.000, 5985.940, -132.847, 0)
	spawnMobile("corellia", "rebel_commando", 300, -6523.550, 405.000, 5980.830, -146.243, 0)
	
	--Roof Patrol #2
	spawnMobile("corellia", "rebel_trooper", 300, -6496.670, 405.001, 5969.600, 45.137, 0)
	spawnMobile("corellia", "rebel_first_lieutenant", 300, -6498.130, 405.001, 5970.740, 50.765, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6495.280, 405.001, 5971.140, 52.500, 0)
	
	--Drill
	spawnMobile("corellia", "rebel_trooper", 300, -6560.5, 398.000, 5987.1, 90.000, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6560.5, 398.000, 5988.1, 90.000, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6560.5, 398.000, 5989.1, 90.000, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6561.5, 398.000, 5987.1, 90.000, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6561.5, 398.000, 5988.1, 90.000, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6561.5, 398.000, 5989.1, 90.000, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6562.5, 398.000, 5987.1, 90.000, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6562.5, 398.000, 5988.1, 90.000, 0)
	spawnMobile("corellia", "rebel_trooper", 300, -6562.5, 398.000, 5989.1, 90.000, 0)
	spawnMobile("corellia", "rebel_sergeant", 300, -6554.020, 398.000, 5986.700, -90.000, 0)
	
	-- West Building Interior
	spawnMobile("corellia", "rebel_first_lieutenant", 300, 3.1, 0.1, 2.0, 84, 8285398)
	spawnMobile("corellia", "rebel_sergeant", 300, 5.4, 0.1, 2.3, -93, 8285398)
	spawnMobile("corellia", "rebel_major", 300, 3.2, 0.1, 3.6, -153, 8285398)
	spawnMobile("corellia", "rebel_staff_sergeant", 300, 4.1, 0.1, -3.6, 101, 8285399)
	spawnMobile("corellia", "rebel_medic", 300, -2.9, 0.1, -4.0, -74, 8285400)
	spawnMobile("corellia", "rebel_commando", 300, -5.0, 0.1, -2.1, 119, 8285400)
	
	-- North West Building Interior
	spawnMobile("corellia", "rebel_first_lieutenant", 300, 3.1, 0.1, 2.0, 84, 8205777)
	spawnMobile("corellia", "rebel_sergeant", 300, 5.4, 0.1, 2.3, -93, 8205777)
	spawnMobile("corellia", "rebel_major", 300, 3.2, 0.1, 3.6, -153, 8205777)
	spawnMobile("corellia", "rebel_staff_sergeant", 300, 4.1, 0.1, -3.6, 101, 8205778)
	spawnMobile("corellia", "rebel_medic", 300, -2.9, 0.1, -4.0, -74, 8205779)
	spawnMobile("corellia", "rebel_commando", 300, -5.0, 0.1, -2.1, 119, 8205779)	
	
	-- North Building Interior
	spawnMobile("corellia", "rebel_first_lieutenant", 300, 3.1, 0.1, 2.0, 84, 8205784)
	spawnMobile("corellia", "rebel_sergeant", 300, 5.4, 0.1, 2.3, -93, 8205784)
	spawnMobile("corellia", "rebel_major", 300, 3.2, 0.1, 3.6, -153, 8205784)
	spawnMobile("corellia", "rebel_staff_sergeant", 300, 4.1, 0.1, -3.6, 101, 8205785)
	spawnMobile("corellia", "rebel_medic", 300, -2.9, 0.1, -4.0, -74, 8205786)
	spawnMobile("corellia", "rebel_commando", 300, -5.0, 0.1, -2.1, 119, 8205786)	
	
	-- North East Building Interior
	spawnMobile("corellia", "rebel_first_lieutenant", 300, 3.1, 0.1, 2.0, 84, 8205791)
	spawnMobile("corellia", "rebel_sergeant", 300, 5.4, 0.1, 2.3, -93, 8205791)
	spawnMobile("corellia", "rebel_major", 300, 3.2, 0.1, 3.6, -153, 8205791)
	spawnMobile("corellia", "rebel_staff_sergeant", 300, 4.1, 0.1, -3.6, 101, 8205792)
	spawnMobile("corellia", "rebel_medic", 300, -2.9, 0.1, -4.0, -74, 8205793)
	spawnMobile("corellia", "rebel_commando", 300, -5.0, 0.1, -2.1, 119, 8205793)	
	
	-- East Building Interior
	spawnMobile("corellia", "rebel_first_lieutenant", 300, 3.1, 0.1, 2.0, 84, 8285405)
	spawnMobile("corellia", "rebel_sergeant", 300, 5.4, 0.1, 2.3, -93, 8285405)
	spawnMobile("corellia", "rebel_major", 300, 3.2, 0.1, 3.6, -153, 8285405)
	spawnMobile("corellia", "rebel_staff_sergeant", 300, 4.1, 0.1, -3.6, 101, 8285406)
	spawnMobile("corellia", "rebel_medic", 300, -2.9, 0.1, -4.0, -74, 8285407)
	spawnMobile("corellia", "rebel_commando", 300, -5.0, 0.1, -2.1, 119, 8285407)	
	
	-- South East Building Interior
	spawnMobile("corellia", "rebel_first_lieutenant", 300, 3.1, 0.1, 2.0, 84, 8285412)
	spawnMobile("corellia", "rebel_sergeant", 300, 5.4, 0.1, 2.3, -93, 8285412)
	spawnMobile("corellia", "rebel_major", 300, 3.2, 0.1, 3.6, -153, 8285412)
	spawnMobile("corellia", "rebel_staff_sergeant", 300, 4.1, 0.1, -3.6, 101, 8285413)
	spawnMobile("corellia", "rebel_medic", 300, -2.9, 0.1, -4.0, -74, 8285414)
	spawnMobile("corellia", "rebel_commando", 300, -5.0, 0.1, -2.1, 119, 8285414)
	
	-- Main Building Interior
	spawnMobile("corellia", "rebel_colonel", 300, 5.9, 7.01, 9.92, 0, 8555482)
	spawnMobile("corellia", "rebel_trooper", 300, -12.94, 7.00974, 9.54, 0, 8555481)
	spawnMobile("corellia", "rebel_trooper", 300, -6.44793, 7.00977, 6.53793, 0, 8555481)
	spawnMobile("corellia", "rebel_trooper", 300, -2.37, 7.0096, 6.54, 0, 8555481)
	spawnMobile("corellia", "rebel_corporal", 300, -3.45, 7.00966, 12.62, 0, 8555481)
	spawnMobile("corellia", "rebel_corporal", 300, 0.02, 7.00964, 12.81, 0, 8555481)
	spawnMobile("corellia", "rebel_trooper", 300, 5.59, 7.00978, -0.3, 0, 8555480)
	spawnMobile("corellia", "rebel_trooper", 300, 12.29, 7.00978, -9.11, 0, 8555480)
	spawnMobile("corellia", "rebel_trooper", 300, -13, 1.01, -19, 0, 8555478)
	spawnMobile("corellia", "rebel_corporal", 300, -4, 1.01, -20.94, 0, 8555477)
	spawnMobile("corellia", "rebel_trooper", 300, -3.47, 1.01, -19.22, 0, 8555477)
	spawnMobile("corellia", "rebel_second_lieutenant", 300, -0.55, 1.01, -19.07, 0, 8555477)
	spawnMobile("corellia", "rebel_first_lieutenant", 300, 12.73, 1.01, 1.77, 0, 8555475)
	spawnMobile("corellia", "rebel_scout", 300, 13.18, 1.01, -6.59, 0, 8555475)
	spawnMobile("corellia", "rebel_corporal", 300, -20.12, 1.01, 19.27, 0, 8555474)
	spawnMobile("corellia", "rebel_staff_corporal", 300, -15.73, 1.01, 14.19, 0, 8555474)
	spawnMobile("corellia", "rebel_first_lieutenant", 300, -15.8, 1.01, 18.62, 0, 8555474)
	spawnMobile("corellia", "rebel_staff_corporal", 300, -17.95, 1.01, 14.48, 0, 8555474)
	spawnMobile("corellia", "rebel_corporal", 300, 19.51, 1.01, 17.45, 0, 8555473)
	spawnMobile("corellia", "rebel_corporal", 300, 19.49, 1.01, 19.96, 0, 8555473)
	spawnMobile("corellia", "rebel_first_lieutenant", 300, 16.9, 1.01, 18.54, 0, 8555473)
	spawnMobile("corellia", "rebel_trooper", 300, 4.5, 1.01, 16.86, 0, 8555471)
	spawnMobile("corellia", "rebel_corporal", 300, 0.93, 2.01, 5.74, 0, 8555472)
	spawnMobile("corellia", "rebel_trooper", 300, 17.39, 1.01, -11.38, 0, 8555472)
end

