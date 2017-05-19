TatooineWayfarScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineWayfarScreenPlay",

	planet = "tatooine",

	gcwMobs = {
		{"sand_trooper", "rebel_trooper", -5033.0,75.0,-6623.2,90,0, "", ""},
		{"sand_trooper", "rebel_trooper", -5030.3,75.0,-6605.0,90,0, "", ""},
		{"stormtrooper_squad_leader", "rebel_lieutenant_general", -5031.1,75.0,-6610.1,90,0, "", ""},
		{"dark_trooper", "rebel_sergeant_major", -5102.9,75.0,-6617.5,90,0, "", ""},
		{"dark_trooper", "rebel_sergeant_major", -5125.8,75.0,-6576.9,125,0, "", ""},
		{"scout_trooper", "rebel_trooper", -5211.3,75.0,-6611.2,-130,0, "", ""},
		{"stormtrooper_bombardier", "rebel_surface_marshall", -5207.2,75.0,-6603.6,111,0, "", ""},
		{"dark_trooper", "rebel_scout", -5221.7,75.0,-6595.2,-60,0, "", ""},
		{"stormtrooper_medic", "rebel_medic", -5248.3,75.0,-6529.9,0,0, "", ""},
		{"stormtrooper_groupleader", "rebel_high_general", -5287.5,75.0,-6594.4,-145,0, "", ""},
		{"sand_trooper", "rebel_trooper", -5295.0,75.0,-6590.2,-145,0, "", ""},
	},
}

registerScreenPlay("TatooineWayfarScreenPlay", true)

function TatooineWayfarScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnSceneObjects()
		self:spawnGcwMobiles()
	end
end

function TatooineWayfarScreenPlay:spawnSceneObjects()

	--Tavern
	spawnSceneObject(self.planet, "object/tangible/furniture/all/frn_all_plant_potted_lg_s4.iff", -0.8, -4.0, 1.7, 1499423, math.rad(180) )
end

function TatooineWayfarScreenPlay:spawnMobiles()

	--Tavern -5106 -6615
	local pNpc = spawnMobile(self.planet, "info_broker",60,4.7,1.0,4.6,-148,1499418)
	self:setMoodString(pNpc, "sad")
	pNpc = spawnMobile(self.planet, "entertainer",60,6.82411,0.40827,-8.7422,0,1499419)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "brawler",300,6.82411,0.408269,-7.6422,180,1499419)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile(self.planet, "commoner_technician",60,5.72411,0.408269,-7.6422,135.001,1499419)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "trainer_medic",0,-8.4035,1.00421,8.19643,110,1499420)
	spawnMobile(self.planet, "brawler",300,-7.85116,-3.96617,6.43429,272.53,1499424)
	pNpc = spawnMobile(self.planet, "devaronian_male",60,-2.4,0.4,-10.1,176,1499419)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile(self.planet, "commoner_fat",60,-8.9,0.4,2.2,179,1499419)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile(self.planet, "entertainer",60,-10.2,-4.0,6.5,-90,1499424)
	self:setMoodString(pNpc, "sad")

	--Guild Hall
	pNpc = spawnMobile(self.planet, "artisan",60,11.9085,0.991253,-0.950462,0,1134533)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "noble",60,-9.6227,0.995934,-0.745972,360.011,1134533)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "commoner_old",60,-9.6227,0.995934,0.354028,180.009,1134533)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "farmer_rancher",60,11.9085,0.991375,0.149539,180.01,1134533)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "businessman",60,-20.9216,-3.99571,2.67462,119.091,1718359)
	pNpc = spawnMobile(self.planet, "chiss_female",300,14.8335,-3.99038,5.61296,180.016,1718360)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "mercenary",60,14.8335,-3.99038,4.51296,0,1718360)
	self:setMoodString(pNpc, "npc_accusing")

	--Cantina
	pNpc = spawnMobile(self.planet, "artisan",60,34.4931,0.104999,-6.47601,180,1134559)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "bounty_hunter",300,34.4931,0.104999,-7.576,0,1134559)
	self:setMoodString(pNpc, "sad")
	pNpc = spawnMobile(self.planet, "artisan",60,-3.85346,-0.894991,6.73775,0,1134560)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "bartender",60,-11.0018,-0.894992,1.78678,213.433,1134560)
	spawnMobile(self.planet, "businessman",60,4.86041,-0.894992,6.38401,249.175,1134560)
	spawnMobile(self.planet, "noble",60,-5.69909,-0.894992,-10.4035,79.4873,1134560)
	pNpc = spawnMobile(self.planet, "osweri_hepa",60,11.3838,-0.894992,-2.63465,180.006,1134560)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "medic",300,11.3838,-0.894992,-3.73465,0,1134560)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "mercenary",300,10.2838,-0.894992,-2.63465,135.005,1134560)
	self:setMoodString(pNpc, "calm")
	pNpc = spawnMobile(self.planet, "commoner_fat",300,-3.85346,-0.894991,7.83775,180.003,1134560)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "stanic_wavingstar",60,17.9368,-0.894992,22.6329,180,1134562)
	self:setMoodString(pNpc, "calm")
	spawnMobile(self.planet, "trainer_bountyhunter",0,19,-0.894,-17,0,1134561)
	pNpc = spawnMobile(self.planet, "farmer",60,-25.6583,-0.894991,24.4065,134.995,1134569)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "informant_npc_lvl_1",0,-5216,75,-6563,270,0)
	spawnMobile(self.planet, "informant_npc_lvl_3",0,-31.4241,-0.894991,19.0307,70,1134569)
	pNpc = spawnMobile(self.planet, "comm_operator",300,-24.5583,-0.894991,23.3065,360.011,1134569)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile(self.planet, "contractor",300,-24.5583,-0.894991,24.4065,179.993,1134569)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "mercenary",300,-25.6591,-0.519991,10.6171,15.7251,1134570)

	--Outside
	spawnMobile(self.planet, "cll8_binary_load_lifter",60,-5204.46,75,-6481.04,153.365,0)
	spawnMobile(self.planet, "cll8_binary_load_lifter",60,-5106.7,75,-6484.28,160.531,0)
	spawnMobile(self.planet, "commoner",60,-5095.19,75,-6527.76,255.369,0)
	spawnMobile(self.planet, "commoner_fat",60,-5213.66,75,-6474.22,51.4178,0)
	spawnMobile(self.planet, "commoner_naboo",60,-5249.25,75,-6516.55,22.2881,0)
	spawnMobile(self.planet, "commoner_naboo",60,-5214.19,75,-6460.12,331.513,0)
	spawnMobile(self.planet, "commoner_naboo",60,-5217.62,75,-6578.64,291.256,0)
	spawnMobile(self.planet, "commoner_naboo",60,-5216.58,75,-6494.05,1.52676,0)
	spawnMobile(self.planet, "commoner_naboo",60,-5182,75,-6496.33,222.017,0)
	spawnMobile(self.planet, "commoner_naboo",60,-5155.11,75,-6488.89,3.13805,0)
	spawnMobile(self.planet, "commoner_naboo",60,-5133.39,75,-6492.64,280.032,0)
	spawnMobile(self.planet, "commoner_naboo",60,-5128.78,75,-6542.42,217.665,0)
	spawnMobile(self.planet, "commoner_old",60,-5219.65,75,-6548.3,63.534,0)
	spawnMobile(self.planet, "commoner_tatooine",60,-5260.24,75,-6510.64,241.382,0)
	spawnMobile(self.planet, "commoner_tatooine",60,-5251.85,75,-6499.93,200.386,0)
	spawnMobile(self.planet, "commoner_tatooine",60,-5277.28,75,-6558.48,121.257,0)
	spawnMobile(self.planet, "commoner_tatooine",60,-5193.47,75,-6490.09,341.866,0)
	spawnMobile(self.planet, "commoner_tatooine",60,-5155.04,75,-6500.75,115.651,0)
	spawnMobile(self.planet, "commoner_tatooine",60,-5176.26,75,-6611.98,128.905,0)
	spawnMobile(self.planet, "commoner_tatooine",60,-5120.75,75,-6594.69,212.419,0)
	spawnMobile(self.planet, "criminal",300,-5210.29,75,-6570.98,235.683,0)
	spawnMobile(self.planet, "informant_npc_lvl_2",0,-5205,75,-6503,315,0)
	spawnMobile(self.planet, "jabba_enforcer",360,-5233.49,75,-6571.71,339.496,0)
	spawnMobile(self.planet, "jabba_enforcer",360,-5248.39,75,-6549.52,120.944,0)
	spawnMobile(self.planet, "jabba_enforcer",360,-5273.74,75,-6518.97,98.1445,0)
	spawnMobile(self.planet, "jabba_enforcer",360,-5115.15,75,-6550.13,182.917,0)
	spawnMobile(self.planet, "jabba_enforcer",360,-5115.97,75,-6548.43,188.285,0)
	spawnMobile(self.planet, "jabba_enforcer",360,-5184.2,75,-6538,79,0)
	spawnMobile(self.planet, "jabba_enforcer",360,-5048.57,75,-6571.22,148.847,0)
	spawnMobile(self.planet, "jabba_enforcer",360,-5232.15,75,-6575.29,339.495,0)
	spawnMobile(self.planet, "jabba_enforcer",360,-5050.32,75,-6570.58,148.833,0)
	spawnMobile(self.planet, "jabba_henchman",360,-5282.79,75,-6521.67,116.926,0)
	spawnMobile(self.planet, "jabba_henchman",360,-5232.74,75,-6573.71,339.487,0)
	spawnMobile(self.planet, "jawa",360,-5242.73,75,-6503.24,231.558,0)
	spawnMobile(self.planet, "jawa",360,-5062.65,75,-6596.72,44.1352,0)
	spawnMobile(self.planet, "jawa",360,-5258.59,75,-6504.38,232.79,0)
	spawnMobile(self.planet, "jawa",360,-5061.61,75,-6597.5,31.812,0)
	spawnMobile(self.planet, "jawa",360,-5059.34,75,-6594.17,29.6942,0)
	spawnMobile(self.planet, "jawa_engineer",360,-5108.37,75,-6492.24,199.616,0)
	spawnMobile(self.planet, "jawa_healer",360,-5247.3,75,-6503.9,260,0)
	spawnMobile(self.planet, "jawa_smuggler",360,-5206.91,75,-6490.08,86.0945,0)
	spawnMobile(self.planet, "jawa_smuggler",360,-5128.63,75,-6489.39,118.658,0)
	spawnMobile(self.planet, "jawa_smuggler",360,-5051.74,75,-6606.62,334.538,0)
	spawnMobile(self.planet, "jawa_thief",360,-5248.59,75,-6504.38,83.8473,0)
	spawnMobile(self.planet, "jawa_thief",360,-5053.6,75,-6625.89,176.389,0)
	spawnMobile(self.planet, "jawa_warlord",360,-5245.66,75,-6521.01,177.159,0)
	spawnMobile(self.planet, "jawa_warlord",360,-5248.59,75,-6514.38,140.997,0)
	spawnMobile(self.planet, "jawa_warlord",360,-5066.64,75,-6600.84,318.437,0)
	spawnMobile(self.planet, "jawa_warlord",360,-5054.39,75,-6602.99,341.563,0)
	spawnMobile(self.planet, "noble",60,-5161.6,75,-6532.3,24,0)
	pNpc = spawnMobile(self.planet, "r3",60,-5129.45,75,-6483.77,250.023,0)
	self:setMoodString(pNpc, "calm")
	pNpc = spawnMobile(self.planet, "r5",60,-5105.84,75,-6486.52,161.488,0)
	self:setMoodString(pNpc, "calm")
	pNpc = spawnMobile(self.planet, "r5",60,-5126.31,75,-6491.03,294.68,0)
	self:setMoodString(pNpc, "calm")
	spawnMobile(self.planet, "rebel_recruiter",60,-5295.7,75,-6527.99,39.2298,0)
	spawnMobile(self.planet, "scientist",60,-5260.46,75,-6556.07,247.019,0)
	pNpc = spawnMobile(self.planet, "smuggler_pilot",60,-5868.38,90,-6199.5,65.5014,0)
	self:setMoodString(pNpc, "neutral")
	spawnMobile(self.planet, "trainer_artisan",0,-5274,75,-6547,139,0)
	spawnMobile(self.planet, "trainer_commando",0,-5038,75,-6609,226,0)
	spawnMobile(self.planet, "trainer_scout",0,-5051.46,75,-6629.48,7,0)
	pNpc = spawnMobile(self.planet, "trainer_unarmed",0,-5055,75,-6633,310,0)
	self:setMoodString(pNpc, "npc_sitting_ground")
	spawnMobile(self.planet, "junk_dealer", 1, -5242.27, 75, -6495.05, 138, 0)
	spawnMobile(self.planet, "junk_dealer", 1, -5132.78, 75, -6585.28, 72, 0)
end
