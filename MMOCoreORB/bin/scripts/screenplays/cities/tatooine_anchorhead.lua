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

	patrolMobiles = {
		--{patrolPoints, template, level, x, z, y, direction, cell, mood},
		{"r3_1", "r3", 60, -180.482, 65, -5314.98, 96.2472, 0, 'calm'},
		{"r3_2", "r3", 60, 116.569, 52, -5341.57, 2.26464, 0, "calm"},
		{"r4_1", "r4", 60, 75.9409, 52, -5355.36, 178.447, 0, "calm"},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}} 1 = no delay 0 = delay}
		r3_1 = {{-180, 65, -5314, 0, 1}, {-184, 65, -5306, 0, 0}, {-179, 65, -5298, 0, 0}, {-231, 65, -5295, 0, 1}, {-201, 65, -5305, 0, 1}},
		r3_2 = {{116.569, 52, -5341.57, 0, 1}, {116, 52, -5365, 0, 1}, {124, 52, -5397, 0, 1}, {116, 52, -5365, 0, 1}, {113.1, 52, -5359.2, 0, 0}, {78.6, 52, -5358.7, 0, 1}, {113.1, 52, -5359.2, 0, 1}},
		r4_1 = {{75.9, 52, -5355, 0, 1}, {74, 52, -5345, 0, 0}, {67, 52, -5344, 0, 1}, {44, 52, -5344, 0, 1}, {41.0, 52, -5337.3, 0, 1}, {68, 52, -5337, 0, 1}},
	},
}

registerScreenPlay("TatooineAnchorheadScreenPlay", true)

function TatooineAnchorheadScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnSceneObjects()
		self:spawnGcwMobiles()
	end
end

function TatooineAnchorheadScreenPlay:spawnSceneObjects()

	--Tavern
	spawnSceneObject("tatooine", "object/mobile/le_repair_droid.iff", -0.3, -4.0, -3.7, 1213349, math.rad(90) )
end

function TatooineAnchorheadScreenPlay:spawnMobiles()

	--Tavern
	local pNpc = spawnMobile("tatooine", "borra_setas",60,9.51111,0.408271,-0.736723,320.12,1213345)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile("tatooine", "commoner_tatooine",60,-9.4,0.4,2.0,161,1213345)
	self:setMoodString(pNpc, "npc_standing_drinking")
	spawnMobile("tatooine", "trainer_doctor",0,1.53792,1.00421,6.82596,265,1213346)
	spawnMobile("tatooine", "rebel_recruiter",60,-6.22005,-3.96617,-6.58904,194.653,1213349)

	--Tavern west
	pNpc = spawnMobile("tatooine", "bounty_hunter",60,7.7,-4.0,-4.0,138,3355393)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile("tatooine", "businessman",60,8.5,-4.0,-5.3,-37,3355393)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile("tatooine", "commoner_technician",60,8.4,0.4,-9.5,126,3355387)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("tatooine", "commoner_fat",60,-8.8,1.0,6.5,-99,3355388)
	self:setMoodString(pNpc, "happy")

	--Outside
	spawnMobile("tatooine", "commoner",60,-144.579,65,-5301.04,250.798,0)
	spawnMobile("tatooine", "commoner_naboo",60,134.869,52,-5333.14,67.0208,0)
	spawnMobile("tatooine", "commoner_old",60,73.2491,52,-5329.48,324.6,0)
	spawnMobile("tatooine", "commoner_old",60,70.2339,52,-5316.54,358.449,0)
	spawnMobile("tatooine", "commoner_tatooine",60,83.9686,52,-5390.23,61.1388,0)
	spawnMobile("tatooine", "commoner_tatooine",60,74.6127,52,-5382.24,106.067,0)
	spawnMobile("tatooine", "commoner_tatooine",60,59.0963,52,-5342.29,282.005,0)
	spawnMobile("tatooine", "commoner_tatooine",60,39.6087,52,-5345.06,179.67,0)
	spawnMobile("tatooine", "commoner_tatooine",60,150.383,52,-5327.33,143.663,0)
	spawnMobile("tatooine", "commoner_tatooine",60,123.408,52,-5377.31,88.9686,0)
	spawnMobile("tatooine", "commoner_tatooine",60,114.69,52,-5404.19,89.678,0)
	pNpc = spawnMobile("tatooine", "commoner_technician",60,-108.399,65,-5298.05,0,0)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("tatooine", "bounty_hunter",300,-162.748,65,-5312.84,0,0)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("tatooine", "scavenger",300,-108.399,65,-5297.05,180.005,0)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("tatooine", "mercenary",60,-162.748,65,-5311.84,180.005,0)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("tatooine", "businessman", 60, -143.907, 65, -5335.05, 0, 0)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("tatooine", "pilot", 60, -143.907, 65, -5334.05, 180.005, 0)
	self:setMoodString(pNpc, "conversation")
	spawnMobile("tatooine", "junk_dealer", 0, 110.87, 52, -5428.19, 53, 0)

	spawnMobile("tatooine", "bantha",300,216.9,11.7,-5425.4,-121,0)
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
	spawnMobile("tatooine", "zucca_boar",300,-35.6792,30,-5439.35,11.3066,0)
end
