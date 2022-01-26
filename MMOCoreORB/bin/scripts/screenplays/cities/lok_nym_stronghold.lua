LokNymStrongholdScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "LokNymStrongholdScreenPlay",

	planet = "lok",

	combatPatrol = {"nym_guard", "nym_guard_strong", "nym_guard_weak"},
	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "commoner_tatooine_patrol", "noble_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},
		--NPCs
		{"npc_1", "combatPatrol", 540, 12, 5124, 348, 0, "", true},
		{"npc_2", "combatPatrol", 384, 11, 4996, 286, 0, "", true},
		{"npc_3", "combatPatrol", 348, 12, 4940, 19, 0, "", true},
		{"npc_4", "combatPatrol", 350, 12, 4975, 216, 0, "", true},
		{"npc_5", "patrolNpc", 462, 11, 5192, 127, 0, "", false},
		{"npc_6", "patrolNpc", 562, 11, 5171, 43, 0, "", false},
		{"npc_7", "patrolNpc", 449, 12, 5141, 112, 0, "", false},
		{"npc_8", "patrolNpc", 618, 11, 5013, 225, 0, "", false},
		{"npc_9", "patrolNpc", 545, 11, 5081, 126, 0, "", false},
		{"npc_10", "patrolNpc", 342, 11, 5024, 97, 0, "", false},
		{"npc_11", "patrolNpc", 280, 11, 5027, 218, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		npc_1 = {{540, 12, 5124, 0, true}, {544, 12, 5132, 0, true}, {548, 12, 5118, 0, true}, {527, 11, 5120, 0, true}, {540, 12, 5117, 0, true}},
		npc_2 = {{384, 11, 4996, 0, true}, {377, 12, 4980, 0, true}, {405, 11, 4996, 0, true}, {403, 12, 4983, 0, true}},
		npc_3 = {{348, 12, 4940, 0, true}, {344, 12, 4963, 0, true}, {331, 12, 4941, 0, true}, {353, 12, 4933, 0, true}, {332, 11, 4914, 0, true}},
		npc_4 = {{350, 12, 4975, 0, true}, {354, 12, 4959, 0, true}, {331, 11, 4991, 0, true}, {338, 12, 5019, 0, true}},
		npc_5 = {{462, 11, 5192, 0, true}, {479, 12, 5183, 0, true}, {447, 11, 5181, 0, false}, {465, 11, 5169, 0, true}, {472, 12, 5155, 0, true}},
		npc_6 = {{562, 11, 5171, 0, true}, {556, 11, 5150, 0, true}, {544, 11, 5146, 0, true}, {538, 11, 5169, 0, true}, {552, 11, 5178, 0, true}},
		npc_7 = {{449, 12, 5141, 0, true}, {462, 12, 5124, 0, true}, {455, 12, 5100, 0, true}, {454, 12, 5136, 0, true}, {428, 12, 5147, 0, true}},
		npc_8 = {{618, 11, 5013, 0, true}, {581, 12, 5016, 0, true}, {552, 12, 4991, 0, true}, {604, 12, 5041, 0, true}, {618, 12, 5028, 0, true}},
		npc_9 = {{545, 11, 5081, 0, true}, {563, 11, 5081, 0, true}, {528, 12, 5031, 0, true}, {481, 11, 5007, 0, true}, {537, 11, 5045, 0, false}, {561, 12, 5075, 0, false}, {544, 11, 5090, 0, true}},
		npc_10 = {{342, 11, 5024, 0, true}, {344, 11, 5001, 0, true}, {324, 12, 5038, 0, true}, {301, 12, 5025, 0, true}},
		npc_11 = {{280, 11, 5027, 0, true}, {276, 12, 4988, 0, true}, {240, 12, 4989, 0, true}, {275, 11, 4988, 0, true}, {277, 12, 4958, 0, true}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old", "commoner_tatooine"},
	stationaryNpcs = {"bodyguard", "bounty_hunter", "businessman", "commoner_technician", "contractor", "entertainer", "explorer", "fringer", "gambler", "medic", "mercenary", "miner", "noble", "pilot", "rancher", "scientist", "slicer"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, 372.58, 12, 5003.4, 336, 0, ""},
		{1, 514.113, 11.4, 5196.38, 105, 0, ""},
		{1, 360.315, 11.9, 4966.58, 287, 0, ""},
		{1, 371.229, 12, 5167.84, 53, 0, ""},
		{1, 535.709, 11.9, 5135.86, 4, 0, ""},
		{1, 522.568, 11.8, 4964.65, 304, 0, ""},
		{1, 285.432, 12, 5117.33, 85, 0, ""},
		{1, 332.33, 12, 5159.29, 135, 0, ""},
		{1, 356.668, 12.0, 4918.65, 342, 0, ""},
		{1, 462.534, 11.8, 5148.35, 23, 0, ""},
		{1, 525.319, 11.8, 5156.53, 159, 0, ""},
		{1, 391.143, 12, 5057.74, 180, 0, "conversation"},
		{1, 484.493, 11.8, 5090.56, 2, 0, "conversation"},
		{1, 552.494, 11.89, 5110.84, 0, 0, "conversation"},
		{1, 432.639, 12, 5218.48, 0, 0, "npc_accusing"},
		{1, 363.384, 11, 5104.73, 315, 0, ""},
		{1, 391.143, 12, 5056.74, 0, 0, "conversation"},
	},

	mobiles = {
		--cantina
		{"businessman",60,-12.2,-0.9,-20.1,-85,8145383, "npc_consoling"},

		--thugs and misc
		{"nym_surveyor",300,484.493,11.9154,5091.56,180.005,0, ""},
		{"nym_guard_weak",300,551.4,12,5169.8,200,0, ""},
		{"nym_guard_weak",300,535.7,11.9,5105.3,90,0, ""},
		{"nym_guard_weak",300, 323.0, 12, 4883.7, 45, 0, ""},
		{"nym_guard_weak",300,322.8,12.1,5050,216,0, ""},
		{"nym_guard_weak",300,343.53,12.5909,4902.71,356.744,0, ""},
		{"nym_guard",300,381.62,12,5013.95,350,0, ""},
		{"nym_guard",300,381.4,12,5015.13,170,0, ""},
		{"nym_guard",300,550.517,11.7979,5167.25,10.2375,0, ""},
		{"nym_guard",300,518.4,12,5100.5,300,0, ""},
		{"nym_guard",300,405,12.5,5032,230,0, ""},
		{"nym_guard",300,435.932,12.5279,5024.65,247.747,0, ""},
		{"nym_guard",300,389.1,12,5034.2,260,0, ""},
		{"nym_guard",300,441,12.5,5025,90,0, ""},
		{"nym_guard_strong",300,405.3,12.5,5030,349,0, ""},
		{"nym_guard_strong",300,537.325,11.9367,5112.7,290,0, ""},
		{"nym_guard_strong",300,538.5,11.9,5102.6,45,0, ""},
		{"nym_guard_strong",300,406.311,11.8705,4991.53,286.282,0, ""},
		{"nym_guard_strong",300, 326.9, 12, 4879.9, 45, 0, ""},
		{"nym_guard_weak",300,400.5,12.5,5047.2,90,0, ""},
		{"nym_guard_weak",300,520.4,12,5128.8,180,0, ""},
		{"mercenary",300,18.98,2.29948,10.51,181.005,6595511, ""},
		{"mouse_droid",300,-20.26,2.29947,-18.62,3.00005,6595511, ""},
		{"commoner_technician",300,-18.91,2.29916,9.74,178.005,6595511, ""},
		{"comm_operator",300,5.86,1.3,-5.04,283.008,6595511, ""},
		{"bounty_hunter",300,-3.58,1.3,4.01,89.0026,6595511, ""},
		{"brawler",300,-8.11,1.3,-1.06,177.005,6595511, ""},
		{"brawler",300,4.17,1.3,-5.62,33.001,6595511, ""},
		{"corellia_times_investigator",300,3.12,4.0782,-9.55,359.01,6595511, ""},
		{"shadowy_figure",300,-3.1239,4.0782,-9.55698,359.01,6595511, ""},
		{"seeker",300,1.98,8.9,-30.5,0,6595511, ""},
		{"bounty_hunter",300,-1.91,8.9,-30.5,360.011,6595511, ""},
		{"mercenary",300,-1.79,1.3,3.94,267.008,6595511, ""},
		{"farmer",300,-8.05,1.3,-2.3,7.00022,6595511, ""},
		{"contractor",300,4.39,1.3,-3.87,149.004,6595511, ""},
		{"devaronian_male",300,-29.1,2.3,1.5,200,6595515, ""},
		{"bounty_hunter",300,37.49,2.29422,-1.17,88.0026,6595518, ""},
		{"mercenary",300,36.71,2.29422,-2.92,88.0026,6595518, ""},
		{"pilot",300,1.83273,-0.894992,-14.2461,180.009,8145381, ""},
		{"farmer_rancher",300,-2.13049,-0.894991,6.9956,360.011,8145378, ""},
		{"informant_npc_lvl_3",60,369,11.89,5087,90,0, ""},
		{"informant_npc_lvl_3",60,540,11.92,5072,180,0, ""},

		--quest
		{"nym_fuel_tech",0,374.599,11.9876,4986.77,31.5798,0, ""},
		{"ramna",60,19.5548,-0.894995,-20.1381,20.176,8145379, ""},
		{"warvog_arkon",60,-12.1246,1.6,-16.3553,291.827,8145361, ""},
		{"viopa",60,-2.2483,4.0782,-10.4691,138.087,6595511, ""},

		--trainer
		{"trainer_combatmedic",60,-17.1,0.26,9.2,-100,2745870, ""},
		{"trainer_doctor",60,22.1279,0.26,-6.11676,91,2745866, ""},
		{"trainer_medic",60,-16.0068,0.26,-2.42861,117,2745870, ""},

		{"agriculturalist",60,16.74,14.26,-2.05184,56.8997,2745876, ""},
		{"agriculturalist",60,7.54821,-0.894991,-7.47564,180.006,8145378, "conversation"},
		{"artisan",60,-13.7191,0.26,-9.38652,179.996,2745870, "conversation"},
		{"artisan",60,-29.0395,0.26,8.63541,0,2745870, "conversation"},
		{"artisan",60,-24.251,-0.894991,23.6325,180,8145387, "conversation"},
		{"artisan",60,6.44821,-0.894991,-7.47564,135.005,8145378, "conversation"},
		{"artisan",60,-23.8096,1.6,-5.16968,180.005,8145362, "conversation"},
		{"bapibac", 60, 14.5598, 0.26, 3.77176, 360.011, 2745866, "conversation"},
		{"bartender",60,-11.2794,-0.894992,1.36624,33.4279,8145378, ""},
		{"bounty_hunter",300,15.64,14.26,-0.951844,303.334,2745876, ""},
		{"mercenary",300,3.95102,7.26,9.58572,179.998,2745872, "conversation"},
		{"mercenary",300,-1.26922,0.999998,-0.973796,180.006,8145356, "conversation"},
		{"mercenary",300,4.27638,1.00001,-7.08525,134.999,8145356, "conversation"},
		{"mercenary",300,-3.37845,0.999947,7.55641,135,8145356, "conversation"},
		{"insurgent",300,-23.1849,1.58923,0.850721,0.0559546,8145358, "angry"},
		{"noble",60,18.7783,1.28309,9.1449,135.004,8145357, "conversation"},
		{"info_broker",60,-0.243796,7.26,-12.1226,135.01,2745872, "conversation"},
		{"info_broker",60,-25.6603,0.26,-0.532375,135.011,2745870, "conversation"},
		{"info_broker",60,19.6068,1.28309,-14.4961,180.006,8145357, "conversation"},
		{"info_broker",60,-11.545,1,-3.99877,45.0052,8145358, "conversation"},
		{"bounty_hunter",300,16.74,14.26,-0.951844,283.416,2745876, ""},
		{"bounty_hunter",300,29.0555,0.26,7.22789,360.011,2745866, "angry"},
		{"brawler",60,4.19353,13.5019,8.75924,180,2745876, "angry"},
		{"brawler",60,32.2156,14.26,-9.06471,0.0395659,2745876, "conversation"},
		{"brawler",60,9.48372,0.26,-7.07547,135.009,2745866, "conversation"},
		{"brawler",60,-4.95629,-0.894992,-6.53149,360.011,8145378, "conversation"},
		{"brawler",60,5.37638,1,-8.18525,360.011,8145356, "conversation"},
		{"businessman",60,-2.13049,-0.894991,8.0956,179.998,8145378, "conversation"},
		{"businessman",60,19.8783,1.28309,8.0449,360.011,8145357, "conversation"},
		{"ciwi_mosregri", 60, 31.1714, 7.25, 12.3841, 180.018, 2745874, "conversation"},
		{"comm_operator",60,432.639,12,5219.48,180.005,0, "conversation"},
		{"commoner",60,31.1714,7.25,11.2841,0,2745874, "conversation"},
		{"commoner",60,29.0555,0.26,8.32789,179.999,2745866, "conversation"},
		{"commoner",60,6.78896,1.00001,8.59957,0,8145356, "conversation"},
		{"commoner",60,-11.545,1.00022,-2.89877,134.998,8145358, "conversation"},
		{"commoner_fat",60,6.44821,-0.894991,-8.57564,45.0004,8145378, "conversation"},
		{"commoner_old",60,43.6331,0.104999,1.36432,180.09,8145376, "conversation"},
		{"commoner_tatooine",60,-2.27845,0.999959,6.45641,0,8145356, "conversation"},
		{"commoner_technician",60,0.856204,7.26,-13.2226,0,2745872, "conversation"},
		{"mercenary",300,226.672,12.0826,4954.08,267.001,0, ""},
		{"insurgent",300,221.718,11.9626,4987.57,135.742,0, ""},
		{"entertainer",60,30.0714,7.25,12.3841,135.011,2745874, "conversation"},
		{"entertainer",60,-30.1395,0.25801,9.73541,135.01,2745870, "conversation"},
		{"entertainer",60,-5.72977,-0.894994,22.9507,180.008,8145384, "conversation"},
		{"entertainer",60,-6.82977,-0.894994,22.9507,135.007,8145384, "conversation"},
		{"entertainer",60,18.2791,-0.894996,-13.3794,180.008,8145379, "conversation"},
		{"entertainer",60,6.78896,1.00001,9.69957,180.005,8145356, "happy"},
		{"evathm", 60, 4.84117, -0.894992, 20.6966, 45.0006, 8145382, "conversation"},
		{"commoner_naboo",60,-24.5603,0.26,-1.63238,0,2745870, "conversation"},
		{"sullustan_male",60,23.1893,-0.894994,8.7231,0,8145378, "conversation"},
		{"ithorian_male",60,19.6068,1.28309,-15.5961,360.011,8145357, "conversation"},
		{"farmer",60,29.5658,13.25,10.7188,180.002,2745876, "conversation"},
		{"farmer",60,-2.27845,0.999949,7.55641,180.005,8145356, "conversation"},
		{"farmer",60,-14.6521,1.0008,7.50857,0,8145358, "conversation"},
		{"farmer_rancher",60,18.1642,-0.894992,19.3991,79.3056,8145380, ""},
		{"medic",300,10.5837,0.26,-7.07547,180.014,2745866, "conversation"},
		{"insurgent",60,0.856204,7.26,-12.1226,180.015,2745872, "conversation"},
		{"contractor",60,43.6314,0.104999,0.264886,0.0791317,8145376, "conversation"},
		{"mercenary",300,19.8783,1.28309,9.1449,180.006,8145357, "conversation"},
		{"corellia_times_reporter",60,-10.445,1.00009,-2.89877,180.006,8145358, "conversation"},
		{"idhak_ipath", 60, 28.4658, 13.25, 10.7188, 135.001, 2745876, "conversation"},
		{"ifoja_lico", 60, 552.494, 11.89, 5111.84, 180.005, 0, "conversation"},
		{"info_broker",60,-15.7521,1.00122,8.60857,134.998,8145358, "conversation"},
		{"corellia_times_investigator",60,32.2166,14.26,-7.96455,180.055,2745876, "conversation"},
		{"medic",60,-29.0395,0.26,9.73541,180.016,2745870, "worried"},
		{"medic",60,14.5598,0.26,4.87176,180.004,2745866, "conversation"},
		{"medic",60,-3.23049,-0.894991,8.0956,134.996,8145378, "conversation"},
		{"medic",60,-1.26922,1,-2.0738,360.011,8145356, "conversation"},
		{"medic",60,-10.445,1,-3.99877,360.011,8145358, "conversation"},
		{"melo", 60, 32.2502, 7.25, -2.56477, 360.011, 2745874, "conversation"},
		{"mercenary",300,25.7848,-0.894993,-8.75091,180.009,8145378, "conversation"},
		{"mercenary",300,24.6848,-0.894992,-8.75091,135.009,8145378, "angry"},
		{"mercenary",300,5.94117,-0.894992,21.7966,180.007,8145382, "conversation"},
		{"shadowy_figure",300,23.1893,-0.894993,9.8231,180.01,8145378, "angry"},
		{"devaronian_male",60,4.19353,13.5019,7.65925,360.011,2745876, "conversation"},
		{"chiss_male",60,-13.7191,0.26,-10.4865,360.011,2745870, "conversation"},
		{"chiss_female",60,-14.4486,0.26,6.76362,134.998,2745870, "conversation"},
		{"noble",60,-24.5603,0.26,-0.532375,180.016,2745870, "conversation"},
		{"noble",60,5.94117,-0.894992,20.6966,0,8145382, "conversation"},
		{"noble",60,-14.6521,1.00101,8.60857,180.005,8145358, "conversation"},


		{"pilot",60,31.1166,14.26,-9.06455,44.9979,2745876, "happy"},
		{"pilot",60,18.2791,-0.894996,-14.4794,0,8145379, "conversation"},
		{"pilot",60,-23.8096,1.6,-6.26968,0,8145362, "conversation"},
		{"junk_dealer", 0, 366, 12, 5202.8, -178, 0, ""},
		{"junk_reggi", 0, 443.925, 12, 4879.41, 145, 0, ""},
		{"rifea_eicik", 60, -23.1848, 1.58812, 1.95072, 180.005, 8145358, "conversation"},
		{"rorha_wahe", 60, 7.54821, -0.894991, -8.57564, 0, 8145378, "conversation"},
		{"scientist",60,-13.3486,0.26,5.66362,360.011,2745870, "conversation"},
		{"scientist",60,25.7848,-0.894993,-9.85091,0,8145378, "conversation"},
		{"scientist",60,5.37638,1.00001,-7.08525,180.006,8145356, "conversation"},
		{"insurgent",60,-30.1395,0.259061,8.63541,45.0015,2745870, "conversation"},
		{"mercenary",300,-24.251,-0.894991,22.5325,360.011,8145387, "conversation"},
		{"comm_operator",300,3.95102,7.26,8.48572,360.011,2745872, "npc_imperial"},
		{"commoner_technician",300,10.5837,0.26,-8.17547,0,2745866, "sad"},
		{"shadowy_figure",300,4.84117,-0.894992,21.7966,135.006,8145382, "angry"},
		{"bounty_hunter",300,-4.95629,-0.894992,-5.43149,179.998,8145378, "npc_accusing"},
		{"commoner_naboo",60,31.1166,14.26,-7.96455,135.032,2745876, "conversation"},
		{"commoner_tatooine",60,-13.3486,0.26,6.76362,179.996,2745870, "conversation"},
		{"corellia_times_reporter",60,9.48372,0.26,-8.17547,45.0031,2745866, "conversation"},
		{"medic",60,1.83273,-0.894992,-15.3461,0,8145381, "npc_consoling"},
		{"contractor",60,-5.72977,-0.894996,21.8507,0,8145384, "worried"},
		{"entertainer",60,-3.37845,0.999956,6.45641,44.9954,8145356, "happy"},
		{"vendor",60,29.5658,13.25,9.61881,360.011,2745876, "nervous"},
		{"vendor",60,32.2502,7.25,-1.46477,179.999,2745874, "conversation"},
		{"vixur_webb", 60, -13.2, -0.9, -20.2, 22, 8145383, "npc_sitting_chair"}
	}
}

registerScreenPlay("LokNymStrongholdScreenPlay", true)

function LokNymStrongholdScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
		self:spawnSceneObjects()
	end
end

function LokNymStrongholdScreenPlay:spawnSceneObjects()

	--outside starport in tent when evidence is found to confirm
	--spawnSceneObject(self.planet, "object/tangible/crafting/station/public_space_station.iff", 456.6, 3.0, 5451.8, 0, math.rad(145) )
end

function LokNymStrongholdScreenPlay:spawnMobiles()
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

	--outside tents near starport when evidence is found to confirm
	--pNpc = spawnMobile(self.planet, "trainer_shipwright",60,466.6,3.0,5446,-90,0)
	--self:setMoodString(pNpc, "conversation")
	--pNpc = spawnMobile(self.planet, "chassis_dealer",60,463.0,3.0,5446.1,90,0)
	--self:setMoodString(pNpc, "conversation")

	local pNpc = spawnMobile(self.planet, "junk_dealer", 0, 345.73, 12, 5139.45, -177, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerFineryConvoTemplate")
	end

	pNpc = spawnMobile(self.planet, "nym_kusak_guardian", 60, -3.62, 3.27819, -25.44, 39.0011, 6595511)
	if pNpc ~= nil then
		self:setMoodString(pNpc, "calm")
		self:setCustomName(pNpc, "Scourge")

		CreatureObject(pNpc):clearOptionBit(AIENABLED)
	end

	pNpc = spawnMobile(self.planet, "nym_kusak_guardian", 60, 3.62, 3.27819, -25.44, 325.01, 6595511)
	if pNpc ~= nil then
		self:setMoodString(pNpc, "bored")
		self:setCustomName(pNpc, "Razor")

		CreatureObject(pNpc):clearOptionBit(AIENABLED)
	end
end
