CorelliaDoabaGuerfelScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CorelliaDoabaGuerfelScreenPlay",

	planet = "corellia",

	gcwMobs = {
		{"comm_operator", "specforce_technician", 3308, 308, 5485.8, 45, 0, "npc_imperial", "conversation"},
		{"dark_trooper", "rebel_commando", 3173.3, 300, 5302.5, -155, 0, "npc_imperial", "neutral"},
		{"dark_trooper", "rebel_commando", 3181, 302.9, 5099.8, 175, 0, "npc_imperial", "neutral"},
		{"elite_sand_trooper", "rebel_scout", 3142.5, 300, 5169.9, 179, 0, "npc_imperial", "neutral"},
		{"elite_sand_trooper", "rebel_scout", 3319.3, 308, 5523.9, 25, 0, "npc_imperial", "neutral"},
		{"imperial_corporal", "rebel_corporal", 3310.8, 308, 5482.9, 45, 0, "npc_imperial", "neutral"},
		{"imperial_noncom", "specforce_technician", 3327.5, 308, 5518.6, 25, 0, "", ""},
		{"storm_commando", "rebel_commando", 3181.3, 300, 5298.6, -147, 0, "", ""},
		{"stormtrooper", "rebel_crewman", 3171.4, 301.9, 5100.1, 175, 0, "npc_imperial", "neutral"},
		{"stormtrooper", "rebel_crewman", 3141.3, 290, 4984.9, -89, 0, "npc_imperial", "neutral"},
		{"stormtrooper_rifleman", "rebel_lance_corporal", 3133.4, 300, 5169.9, 178, 0, "npc_imperial", "neutral"},
		{"stormtrooper_squad_leader", "rebel_network_leader", 3141.1, 290, 4975.7, -95, 0, "npc_imperial", "conversation"},
		{"corsec_commissioner", "corsec_commissioner", 3154.04,300,5173.07,180.005,0, "conversation", "conversation"},
		{"corsec_inspector_sergeant", "corsec_inspector_sergeant", 3121,285,5006.4,-161,0, "", ""},
		{"corsec_master_sergeant", "corsec_master_sergeant", 3300.28,308,5496.49,180.005,0, "npc_imperial", "conversation"},
		{"corsec_sergeant", "corsec_sergeant", 3154.04,300,5172.07,0,0, "npc_imperial", "conversation"},
		{"corsec_trooper", "corsec_trooper", 3119.2,285,5002.2,20,0, "", ""},
	},
}

registerScreenPlay("CorelliaDoabaGuerfelScreenPlay", true)

function CorelliaDoabaGuerfelScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnSceneObjects()
		self:spawnGcwMobiles()
	end
end

function CorelliaDoabaGuerfelScreenPlay:spawnSceneObjects()

	--outside starport
	spawnSceneObject(self.planet, "object/tangible/crafting/station/public_space_station.iff", 3327.89, 308, 5534.89, 0, math.rad(-150) )
end

function CorelliaDoabaGuerfelScreenPlay:spawnMobiles()

		--Starport
	local pNpc = spawnMobile(self.planet, "entertainer",60,53.5,0.6,47.8,-80,9665359)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "commoner", 60,3357.46,308,5639.47,212.301,0)
	spawnMobile(self.planet, "commoner", 60,3414.81,308,5624.67,237.948,0)
	spawnMobile(self.planet, "noble", 60,47.5747,0.974633,22.0108,238.024,9665365)
	spawnMobile(self.planet, "businessman", 60,52.3124,0.639417,48.2148,107.997,9665359)
	pNpc = spawnMobile(self.planet, "chiss_male",60,36.7068,0.639417,40.446,180.001,9665359)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "farmer", 60,36.7068,0.639417,39.346,0,9665359)
	pNpc = spawnMobile(self.planet, "brawler",60,-4.68154,0.639424,60.9856,180.005,9665356)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "corellia_times_reporter",300,-4.68154,0.639424,59.8856,360.011,9665356)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "trainer_shipwright",60,1.28595,0.639421,66.8733,180,9665356)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile(self.planet, "contractor",60,-62.5737,2.63942,41.0043,180.004,9665364)
	self:setMoodString(pNpc, "npc_consoling")
	pNpc = spawnMobile(self.planet, "farmer",60,-62.5737,2.63942,40.0043,360.011,9665364)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile(self.planet, "chassis_dealer",60,-56.6993,0.974563,8.57384,27.5028,9665366)
	self:setMoodString(pNpc, "neutral")

		--Guild Hall/Theater
	pNpc = spawnMobile(self.planet, "corellia_times_investigator",60,-1.72179,0.6,-2.95766,180.016,4395396)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "info_broker",60,-23.9134,0.6,-4.15254,360.011,4395397)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "artisan",60,-1.72179,0.6,-4.05766,360.011,4395396)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "farmer_rancher",60,-23.9134,0.6,-3.15254,179.996,4395397)
	pNpc = spawnMobile(self.planet, "artisan",60,-0.629707,2.6,3.43132,180.013,4395401)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "commoner_tatooine",60,25.4426,0.655075,43.6577,180.006,4395401)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "comm_operator",300,24.3,0.6,4.7,180,4395398)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile(self.planet, "entertainer",60,12.8,2.1,76.4,90,4395403)
	self:setMoodString(pNpc, "happy")
	pNpc = spawnMobile(self.planet, "farmer",60,22.8,2.1,58.9,180,4395402)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "farmer_rancher",60,22.8,2.1,56.9,0,4395402)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile(self.planet, "farmer",60,25.4426,0.746078,42.666,5.24364,4395401)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "info_broker",60,24.5,0.6,2.8,0,4395398)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "mercenary",300,-0.629707,2.6,2.33132,360.011,4395401)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile(self.planet, "noble",60,14.3,2.1,76.3,-90,4395403)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "noble", 60,28.93,2.12878,58.19,222.007,4395402)
	spawnMobile(self.planet, "noble", 60,19.26,2.12847,56.13,266.008,4395403)
	pNpc = spawnMobile(self.planet, "corellia_times_reporter",300,3.96145,2.12878,75.4149,0,4395403)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "farmer",60,3.96145,2.12878,76.4149,180.002,4395403)
	self:setMoodString(pNpc, "nervous")
	spawnMobile(self.planet, "trainer_dancer", 0,17.7541,2.12875,53.6699,1,4395403)
	spawnMobile(self.planet, "trainer_entertainer", 0,30.358,2.12878,73.5895,265,4395403)
	spawnMobile(self.planet, "trainer_imagedesigner", 0,-2.51106,2.12878,70.8023,2,4395403)
	spawnMobile(self.planet, "trainer_musician", 0,21.8,2.1,76.4,180,4395403)
	spawnMobile(self.planet, "theater_manager", 0,22.0995,2.12823,63.5054,0,4395403)
	pNpc = spawnMobile(self.planet, "artisan",60,-20.4229,2.12878,65.9439,180.013,4395404)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "businessman",300,-20.4229,2.12878,64.9439,0,4395404)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "commoner_old",300,-21.8263,2.12878,74.8963,179.999,4395404)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile(self.planet, "mercenary",300,-21.8263,2.12878,73.7963,0,4395404)
	self:setMoodString(pNpc, "npc_accusing")
	pNpc = spawnMobile(self.planet, "mercenary",300,-22.9263,2.12878,74.8963,134.998,4395404)
	self:setMoodString(pNpc, "npc_accusing")

		--Med Center
	pNpc = spawnMobile(self.planet, "medic",60,-3.23192,0.184067,-5.20004,360.011,4345354)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "corellia_times_investigator",300,-3.23192,0.184067,-4.20004,180.012,4345354)
	self:setMoodString(pNpc, "calm")
	spawnMobile(self.planet, "surgical_droid_21b", 60,-1.19,0.184067,-1.89,230.753,4345354)
	spawnMobile(self.planet, "trainer_1hsword", 0,3.5,0.2,-8.7,4,4345354)
	spawnMobile(self.planet, "trainer_combatmedic", 0,8.00847,0.184067,5.47322,87,4345354)
	spawnMobile(self.planet, "trainer_doctor", 0,-3.95652,0.184067,0.467273,171,4345354)
	pNpc = spawnMobile(self.planet, "comm_operator",400,-13,0.2,-7.7,60,4345354)
	self:setMoodString(pNpc, "npc_imperial")

		--Cantina
	pNpc = spawnMobile(self.planet, "bartender",60,-4.00542,-0.894992,-2.41,166.23,3075429)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile(self.planet, "noble",60,-42.098,0.105009,-23.0786,180.012,3075441)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "mercenary",300,-42.098,0.105009,-24.1786,0,3075441)
	self:setMoodString(pNpc, "nervous")
	pNpc = spawnMobile(self.planet, "corellia_times_reporter",300,21.878,-0.894997,-15.7126,0,3075430)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "patron_ithorian",300,40.8822,0.104999,2.22818,0,3075427)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "commoner_naboo",300,8.35364,-0.894992,6.38149,360.011,3075429)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "entertainer",60,21.878,-0.894997,-14.6126,179.999,3075430)
	self:setMoodString(pNpc, "entertained")
	pNpc = spawnMobile(self.planet, "farmer_rancher",60,8.35364,-0.894992,7.38149,179.999,3075429)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "contractor",60,40.8822,0.104999,3.32819,180.003,3075427)
	self:setMoodString(pNpc, "worried")

		--Guild Hall 3122 5268
	spawnMobile(self.planet, "trainer_architect", 0,11,1.13306,-14,0,3075412)
	spawnMobile(self.planet, "trainer_armorsmith", 0,-12,1.1,5,180,3075411)
	spawnMobile(self.planet, "trainer_droidengineer", 0,-11,1.13306,-14,0,3075414)
	spawnMobile(self.planet, "trainer_merchant", 0,12,1.13306,6,180,3075410)
	spawnMobile(self.planet, "trainer_weaponsmith", 0,-2.5,1.13306,-8.4,91,3075413)

		--Guild Hall 3182 5240
	spawnMobile(self.planet, "businessman", 60,3.32,1.13306,-8.49,228.007,3075360)
	spawnMobile(self.planet, "bounty_hunter", 300,-14.01,1.13306,-8.53,120.004,3075361)
	spawnMobile(self.planet, "trainer_brawler", 0,-11,1.13306,-14,0,3075361)
	spawnMobile(self.planet, "trainer_marksman", 0,0,1.13306,-14,0,3075360)
	spawnMobile(self.planet, "trainer_scout", 0,-12,1.13306,5.5,180,3075358)
	pNpc = spawnMobile(self.planet, "junk_dealer", 0, -14.5, 1.1, 2.5, 88, 3075358)

		--Guild Hall 3160 5012
	spawnMobile(self.planet, "contractor", 60,3.29,1.13306,-9.58,249.007,3055771)
	spawnMobile(self.planet, "trainer_artisan", 0,0,1.13306,-14,0,3055771)

		--Hotel
	pNpc = spawnMobile(self.planet, "mercenary",300,17.1745,1.28309,-13.1361,0,3075367)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile(self.planet, "corellia_times_investigator",60,-4.31306,0.999956,6.26959,180,3075366)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "ithorian_male",300,7.8197,1.00001,-5.9104,180.001,3075366)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "twilek_slave",300,-5.41306,0.999953,6.26959,134.998,3075366)
	self:setMoodString(pNpc, "nervous")
	pNpc = spawnMobile(self.planet, "info_broker",300,17.1745,1.28309,-12.0361,179.995,3075367)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "commoner_fat",300,7.8197,1.00001,-7.0104,0,3075366)
	self:setMoodString(pNpc, "npc_standing_drinking")
	pNpc = spawnMobile(self.planet, "medic",60,-4.31306,0.999965,5.16959,0,3075366)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "willham_burke",60,0.861081,0.999995,2.33215,346.259,3075366)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile(self.planet, "zo_ssa",60,-1.1331,0.999991,1.50214,21.773,3075366)
	self:setMoodString(pNpc, "neutral")

		--Outside
	pNpc = spawnMobile(self.planet, "info_broker",60,3202.28,290,4989.06,180.005,0)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "commoner", 60,3139.88,300,5247.41,171.321,0)
	spawnMobile(self.planet, "commoner", 60,3179.26,300,5213.19,233.367,0)
	spawnMobile(self.planet, "commoner", 60,3117.25,300,5194.73,153.311,0)
	spawnMobile(self.planet, "commoner", 60,3108.26,300,5229.01,219.942,0)
	spawnMobile(self.planet, "commoner", 60,3162.05,290,4966.73,255.989,0)
	spawnMobile(self.planet, "commoner", 60,3190.76,300,5269.61,131.093,0)
	spawnMobile(self.planet, "commoner", 60,3103.05,300,5164.17,50.255,0)
	spawnMobile(self.planet, "commoner", 60,3192.45,302.606,5113.34,189.527,0)
	spawnMobile(self.planet, "commoner", 60,3159.78,300,5397.22,81.297,0)
	spawnMobile(self.planet, "commoner", 60,3199.22,300,5449.92,146.634,0)
	spawnMobile(self.planet, "commoner", 60,3277.95,300,5438.73,232.081,0)
	spawnMobile(self.planet, "commoner", 60,3240.99,300,5415.5,249.458,0)
	spawnMobile(self.planet, "commoner", 60,3204.19,290,5003.32,222.69,0)
	spawnMobile(self.planet, "commoner", 60,3202.3,290,5034.41,29.3152,0)
	spawnMobile(self.planet, "commoner", 60,3296.88,324,5760.95,196.788,0)
	pNpc = spawnMobile(self.planet, "commoner_technician",60,3300.28,308,5495.49,0,0)
	self:setMoodString(pNpc, "worried")
	spawnMobile(self.planet, "commoner", 60,3316.17,308,5496.71,3.31657,0)
	spawnMobile(self.planet, "commoner", 60,3308.36,300,5396.79,274.041,0)
	spawnMobile(self.planet, "commoner", 60,3320.73,324,5709.36,340.725,0)
	spawnMobile(self.planet, "commoner", 60,3307.64,308.031,5618.18,225.888,0)
	spawnMobile(self.planet, "commoner", 60,3385.33,308,5699.29,242.976,0)
	spawnMobile(self.planet, "commoner", 60,3322.09,308,5484.42,146.419,0)
	spawnMobile(self.planet, "commoner", 60,3303.05,300,5351.87,319.052,0)
	spawnMobile(self.planet, "commoner", 60,3411.89,308,5515.19,208.425,0)
	spawnMobile(self.planet, "commoner", 60,3431.28,308,5563.41,159.884,0)
	pNpc = spawnMobile(self.planet, "farmer_rancher",60,3196.61,295.033,5073.8,350.188,0)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "farmer",60,3196.61,295.206,5074.8,180.005,0)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "businessman",60,3184.22,300,5162.04,0,0)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "scientist",60,3184.22,300,5163.04,180.005,0)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "bounty_hunter",300,3145.1,290,4995.55,180.005,0)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile(self.planet, "farmer", 60, 3145.1, 289.991, 4994.55, 359.489, 0)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "informant_npc_lvl_1", 0,3100,300,5224,90,0)
	spawnMobile(self.planet, "informant_npc_lvl_1", 0,3123,300,5188,0,0)
	spawnMobile(self.planet, "informant_npc_lvl_1", 0,3145,300,5148,90,0)
	spawnMobile(self.planet, "informant_npc_lvl_1", 0,3165,295.7,5077,180,0)
	spawnMobile(self.planet, "informant_npc_lvl_1", 0,3078,280,5014,270,0)
	spawnMobile(self.planet, "informant_npc_lvl_1", 0,3210,300,5440,100,0)
	spawnMobile(self.planet, "informant_npc_lvl_1", 0,3311,300,5386,300,0)
	spawnMobile(self.planet, "informant_npc_lvl_1", 0,3293,300,5401,90,0)
	spawnMobile(self.planet, "informant_npc_lvl_1", 0,3297,308,5514,70,0)
	spawnMobile(self.planet, "noble", 60,3158.95,300,5352.24,80.7765,0)
	pNpc = spawnMobile(self.planet, "pilot",60,3202.28,290,4988.06,0,0)
	self:setMoodString(pNpc, "angry")
	spawnMobile(self.planet, "trainer_artisan", 0,3311,308,5530,83,0)
	spawnMobile(self.planet, "trainer_brawler", 0,3334,308,5517,0,0)
	spawnMobile(self.planet, "trainer_chef", 0,3070,300,5260,180,0)
	spawnMobile(self.planet, "trainer_creaturehandler",0,3162,300,5191,0,0)
	spawnMobile(self.planet, "trainer_entertainer", 0,3305,308,5525,151,0)
	spawnMobile(self.planet, "trainer_marksman", 0,3338,308,5516,0,0)
	spawnMobile(self.planet, "trainer_medic", 0,3341,308,5517,47,0)
	spawnMobile(self.planet, "trainer_scout", 0,3330.01,308,5512.46,204,0)
	spawnMobile(self.planet, "trainer_tailor", 0,3077,300,5251,0,0)
	spawnMobile(self.planet, "junk_dealer", 0, 3402.4, 308, 5679, 5, 0)
	spawnMobile(self.planet, "junk_dealer", 0, 3367.86, 308.6, 5466.07, 0, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerFineryConvoTemplate")
	end

	--newb starter grind spawns
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + 3475, 309.2, getRandomNumber(10) + 5727, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + 3475, 309.2, getRandomNumber(10) + 5727, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + 3475, 309.2, getRandomNumber(10) + 5727, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + 3475, 309.2, getRandomNumber(10) + 5727, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gubbur", 300, getRandomNumber(10) + 3493, 309.8, getRandomNumber(10) + 5703, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gubbur", 300, getRandomNumber(10) + 3493, 309.8, getRandomNumber(10) + 5703, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gubbur", 300, getRandomNumber(10) + 3493, 309.8, getRandomNumber(10) + 5703, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gubbur", 300, getRandomNumber(10) + 3493, 309.8, getRandomNumber(10) + 5703, getRandomNumber(360), 0)
	spawnMobile(self.planet, "meatlump_fool", 300, getRandomNumber(10) + 3450, 309, getRandomNumber(10) + 5712, getRandomNumber(360), 0)
	spawnMobile(self.planet, "meatlump_fool", 300, getRandomNumber(10) + 3450, 309, getRandomNumber(10) + 5712, getRandomNumber(360), 0)
	spawnMobile(self.planet, "meatlump_fool", 300, getRandomNumber(10) + 3450, 309, getRandomNumber(10) + 5712, getRandomNumber(360), 0)

end
