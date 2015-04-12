CorelliaCoronetScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CorelliaCoronetScreenPlay"
}

registerScreenPlay("CorelliaCoronetScreenPlay", true)

function CorelliaCoronetScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
	end
end

function CorelliaCoronetScreenPlay:spawnMobiles()

	--Anything dashed out will need to be added here and removed from spawn manager once the spawnMobiles command is extended.

	--Starport
	--{"bothan_diplomat",60,56.669,-0.521137,33.7689,180.017,1855678, "conversation", ""},
	spawnMobile("corellia", "bothan_diplomat",60,8.5,0.6,74.4,-93,1855672)
	--{"corsec_cadet",300,37.163,0.639417,40.7061,180.01,1855678, "conversation", ""},
	--{"gambler",60,-4.61669,0.639424,67.8263,180.012,1855675, "conversation", ""},
	--{"hunter",300,8.65132,0.639421,75.5483,256.69,1855672, "calm", ""},
	--{"miner",60,37.163,0.639417,39.6061,0,1855678, "conversation", ""},
	--{"scientist",60,56.669,-0.521137,32.6689,360.011,1855678, "conversation", ""},
	--{"slicer",60,-4.61669,0.639424,66.7263,0,1855675, "conversation", ""},
	--{"farmer",60,-62.7673,2.63942,40.6604,360.011,1855683, "conversation", ""},
	--{"mercenary",300,-62.7673,2.63942,41.7604,179.995,1855683, "conversation", ""},

	--Guild Hall -275 -4700
	--{"bodyguard",300,-9.42234,1.75,-18.7259,180.005,1855484, "conversation", ""},
	--{"corsec_agent",300,-10.5223,1.75,-18.7259,134.999,1855484, "conversation", ""},
	--{"farmer",60,-9.42234,1.75,-19.8259,0,1855484, "conversation", ""},
	spawnMobile("corellia", "farmer",60,11.9421,1.75,-18.7404,129.059,1855484)
	--{"noble",60,11.9421,1.75,-19.8404,0,1855484, "conversation", ""},
	spawnMobile("corellia", "rikkh",60,0.180826,1.75,-21.4842,28.861,1855484)
	spawnMobile("corellia", "rhea",60,1.70956,1.75,-14.1406,4.76848,1855483)
	--{"brawler",60,16.2045,2.25,19.3968,135.003,1855477, "conversation", ""},
	--{"corsec_cadet",300,17.3045,2.25,19.3968,180.006,1855477, "conversation", ""},
	--{"explorer",60,17.3045,2.25,18.2968,360.011,1855477, "conversation", ""},

	--Hotel
	--{"corellia_times_investigator",60,7.44572,1.00001,-8.00652,0,1855548, "conversation", ""},
	--{"corsec_agent",300,7.44572,1.00001,-6.90652,179.997,1855548, "conversation", ""},
	--{"artisan",60,17.2826,1.28309,-11.8404,179.994,1855549, "conversation", ""},
	--{"bodyguard",300,24.3471,1.28309,10.0336,180.007,1855549, "conversation", ""},
	--{"corsec_sergeant",300,24.3471,1.28309,8.93357,360.011,1855549, "conversation", ""},
	spawnMobile("corellia", "grobber",60,-15.4768,1,-8.20706,245.925,1855551)
	spawnMobile("corellia", "zekka_thyne",60,-22.3764,1.6,-15.0418,86.3112,1855554)
	--{"commoner",60,-24,1.6,-4,160,1855554, "calm", "Pex (an elite storyteller vendor)"},

	--Cantina
	spawnMobile("corellia", "bartender",60,7.60649,-0.894992,1.42464,324.005,8105496)
	--{"bodyguard",300,3.61201,-0.894992,-8.73417,135.006,8105496, "conversation", ""},
	--{"bodyguard",300,2.80432,-0.894991,10.6543,180.012,8105496, "conversation", ""}
	--{"businessman",60,-7.91375,-0.894992,-4.88587,179.995,8105496, "conversation", ""},
	--{"corsec_major",300,-7.91375,-0.894992,-5.88587,0,8105496, "conversation", ""},
	--{"rogue_corsec_trooper",300,4.71201,-0.894992,-8.73417,180.01,8105496, "conversation", ""},
	--{"entertainer",60,2.80432,-0.894991,9.55434,360.011,8105496, "conversation", ""},
	--{"farmer_rancher",60,4.71201,-0.894992,-9.83418,360.011,8105496, "conversation", ""},
	--{"criminal",60,-5.02826,-0.894991,-21.3375,60.6357,8105501, "calm", ""},
	spawnMobile("corellia", "businessman",60,0.978477,-0.894992,21.4841,311.517,8105500)
	spawnMobile("corellia", "rebel_recruiter",60,-28.3633,-0.894984,0.335875,171.796,8105504)

	--Guild Hall -243 -4389
	spawnMobile("corellia", "trainer_brawler",0,-11,1.13306,-14,0,1855508)
	spawnMobile("corellia", "trainer_marksman",0,0,1.13306,-14,0,1855507)
	spawnMobile("corellia", "trainer_scout",0,-12,1.13306,5.5,180,1855505)
	--{"junk_dealer",0,-14.5,1.1,2.5,88,1855505, "", "",JUNKWEAPONS,JUNKCONVARMS},

	--Guilg Hall -177 -4390
	spawnMobile("corellia", "trainer_artisan",0,0,1.13306,-14,0,1855517)

	--Med Center
	spawnMobile("corellia", "surgical_droid_21b",60,-25.52,0.26,-3.48,357.849,1855535)
	spawnMobile("corellia", "trainer_combatmedic",0,26.676,0.26,5.41823,85,1855531)
	spawnMobile("corellia", "trainer_doctor",0,-25.2731,0.26,-5,13,1855535)
	spawnMobile("corellia", "trainer_medic",0,-17.7359,0.26,-0.58142,137,1855535)
	spawnMobile("corellia", "trainer_medic",0,14.2688,0.26,4.66124,159,1855531)
	--3rd floor
	--{"corellia_times_investigator",60,21.5803,14.26,-8.84205,360.011,1855541, "conversation", ""},
	--{"artisan",60,21.5803,14.26,-7.84205,180.006,1855541, "conversation", ""},

	--Guild Hall 24 -4400
	spawnMobile("corellia", "trainer_architect",0,11,1.13306,-14,0,1855526)
	spawnMobile("corellia", "trainer_armorsmith",0,-12,1.1,5,180,1855525)
	spawnMobile("corellia", "trainer_droidengineer",0,-11,1.13306,-14,0,1855528)
	spawnMobile("corellia", "trainer_merchant",0,12.1,1.1,5.8,177,1855524)
	spawnMobile("corellia", "trainer_weaponsmith",0,-2.5,1.13306,-8.4,91,1855527)

	--Capitol
	--{"bothan_diplomat",60,5.22842,0.3,2.91677,0,1855463, "conversation", ""},
	--{"bothan_information_broker",60,5.22842,0.3,4.01677,180.005,1855463, "conversation", ""},
	--{"bothan_information_broker",60,5.43518,2.27819,-27.0615,344.925,1855463, "conversation", ""},
	--{"brantlee_spondoon",60,-24.7,1.3,-0.5,124,1855463, "calm", ""}, Task dont add this
	--{"daclif_gallamby",60,-35.6875,1.29422,-1.70805,88.4786,1855467, "calm", ""}, Task dont add this
	--{"brawler",60,16.2045,2.25,19.3968,135.003,1855477, "conversation", ""},
	--{"brawler",60,-1.72746,7.9,-32.175,0,1855463, "conversation", ""},
	--{"corsec_agent",300,-0.332123,0.3,-2.90219,134.998,1855463, "conversation", ""},
	--{"entertainer",60,0.767877,0.3,-2.90219,180.005,1855463, "conversation", ""},
	--{"farmer",60,-18.6014,1.30259,-11.3146,360.011,1855463, "conversation", ""},
	--{"farmer",60,0.767877,0.3,-4.00219,0,1855463, "conversation", ""},
	--{"medic",60,-0.332123,0.3,-4.00219,45.0054,1855463, "conversation", ""},
	--{"medic",60,5.18395,2.27819,-26.1292,164.924,1855463, "conversation", ""},
	--{"noble",60,4.12842,0.3,4.01677,134.998,1855463, "conversation", ""},
	--{"scientist",60,-1.72746,7.9,-31.075,180.005,1855463, "conversation", ""},
	--{"slicer",60,-18.6014,1.30292,-10.2146,180.006,1855463, "conversation", ""},
	--{"corsec_detective",300,-20.2743,3.22324,22.781,180.005,1855468, "conversation", ""},
	--{"farmer",60,-20.2743,3.22324,21.681,0,1855468, "conversation", ""},
	--{"info_broker",60,21.8079,3.22324,26.617,180.006,1855469, "conversation", ""},
	--{"corsec_lieutenant",300,21.8079,3.22324,25.517,360.011,1855469, "conversation", ""},
	--{"farmer",60,37.1168,1.29422,-4.41488,0,1855470, "conversation", ""},
	--{"businessman",60,37.1168,1.29422,-3.41488,180.005,1855470, "conversation", ""},

	--Guild Hall/Theater -207 -4133
	--{"fringer",300,3.66172,0.6,-2.64185,180.005,2365392, "conversation", ""},
	--{"commoner",60,2.56172,0.6,-2.64185,135,2365392, "conversation", ""},
	--{"bothan_information_broker",60,22.2962,0.688613,43.2884,180.006,2365397, "conversation", ""},
	--{"businessman",60,-6.12488,2.6,13.0431,0,2365397, "conversation", ""},
	--{"corsec_commissioner",300,22.2962,0.788717,42.1976,5.2426,2365397, "conversation", ""},
	--{"explorer",60,-6.12488,2.6,14.1431,180.005,2365397, "conversation", ""},
	--{"farmer",60,-17.5041,0.887194,41.0759,180.006,2365397, "conversation", ""},
	--{"info_broker",60,-17.5041,0.992207,39.9855,5.50246,2365397, "conversation", ""},
	--{"scientist",60,-7.22488,2.6,14.1431,135.008,2365397, "conversation", ""},
	--{"slicer",60,-18.6041,0.887072,41.0759,134.784,2365397, "conversation", ""},
	spawnMobile("corellia", "noble",60,28.93,2.12878,58.19,222.007,2365398)
	spawnMobile("corellia", "noble",60,19.26,2.12847,56.13,266.008,2365399)
	--{"explorer",60,26.5189,2.12846,71.9319,0,2365399, "conversation", ""},
	--{"slicer",60,26.5189,2.12858,73.0319,180.005,2365399, "conversation", ""},
	spawnMobile("corellia", "trainer_dancer",0,18.5885,2.12869,53.9366,0,2365399)
	spawnMobile("corellia", "trainer_musician",0,21.8947,2.12814,63.5,0,2365399)
	--{"farmer_rancher",60,-20.3488,2.12878,65.9854,180.006,2365400, "conversation", ""},
	spawnMobile("corellia", "trainer_imagedesigner",0,-21.4483,2.12878,74.4461,185,2365400)

	--Outside Misc
	spawnMobile("corellia", "businessman",60,-306.34,28,-4620.82,67.4368,0)
	spawnMobile("corellia", "businessman",60,-312.404,28,-4646.51,242.881,0)
	spawnMobile("corellia", "businessman",60,-135.995,28,-4745.63,251.824,0)
	spawnMobile("corellia", "cll8_binary_load_lifter",60,-146.217,28,-4738.99,346.392,0)
	spawnMobile("corellia", "commoner",60,-306.539,28,-4546.52,95.6639,0)
	spawnMobile("corellia", "commoner",60,-306.061,28,-4600.68,146.312,0)
	spawnMobile("corellia", "commoner",60,-258.479,28,-4620,198.098,0)
	spawnMobile("corellia", "commoner",60,-350.892,28,-4219.92,244.079,0)
	spawnMobile("corellia", "commoner",60,-357.932,28,-4267.81,39.6745,0)
	spawnMobile("corellia", "commoner",60,-350.452,28,-4287.73,88.2402,0)
	spawnMobile("corellia", "commoner",60,-350.998,28,-4250.76,129.539,0)
	spawnMobile("corellia", "commoner",60,-302.182,28,-4300.76,29.3627,0)
	spawnMobile("corellia", "commoner",60,-282.189,28,-4343.57,319.557,0)
	spawnMobile("corellia", "commoner",60,-239.932,28,-4522.15,78.2005,0)
	--{"commoner",60,-202.143,28,-4504.32,203.539,0, "calm", "CorSec Agent"},
	spawnMobile("corellia", "commoner",60,-163.792,28,-4606.3,8.06951,0)
	spawnMobile("corellia", "commoner",60,-163.751,28,-4552.14,55.4278,0)
	spawnMobile("corellia", "commoner",60,-168.38,28,-4515.61,103.857,0)
	spawnMobile("corellia", "commoner",60,-158.666,28,-4526.31,289.183,0)
	spawnMobile("corellia", "commoner",60,-106.79,28,-4528.6,277.086,0)
	spawnMobile("corellia", "commoner",60,-26.0533,28,-4558.43,310.059,0)
	spawnMobile("corellia", "commoner",60,-54.9984,28,-4530.84,320.833,0)
	spawnMobile("corellia", "commoner",60,-37.2537,28,-4476.76,289.212,0)
	spawnMobile("corellia", "commoner",60,-92.217,28,-4471.14,34.4098,0)
	spawnMobile("corellia", "commoner",60,-14.9281,28,-4451.64,343.833,0)
	spawnMobile("corellia", "commoner",60,40.5453,28,-4416.63,80.7447,0)
	spawnMobile("corellia", "commoner",60,14.4606,28,-4407.11,38.4825,0)
	spawnMobile("corellia", "commoner",60,-15.4515,28,-4415.25,54.8457,0)
	spawnMobile("corellia", "commoner",60,-64.8198,28,-4398.56,247.888,0)
	spawnMobile("corellia", "commoner",60,-78.7157,28,-4286.4,22.2156,0)
	spawnMobile("corellia", "commoner",60,-71.0095,28,-4325.21,60.8559,0)
	spawnMobile("corellia", "commoner",60,-87.6481,28,-4302.16,97.3912,0)
	spawnMobile("corellia", "commoner",60,-112.646,28,-4310.7,151.383,0)
	spawnMobile("corellia", "commoner",60,-118.993,28,-4285.29,181.854,0)
	spawnMobile("corellia", "commoner",60,-54.3716,28,-4304.72,97.2405,0)
	spawnMobile("corellia", "commoner",60,-56.7639,28,-4229.33,47.6277,0)
	spawnMobile("corellia", "commoner",60,-103.047,28,-4182.61,84.8143,0)
	spawnMobile("corellia", "commoner",60,-163.872,28,-4181.48,294.873,0)
	spawnMobile("corellia", "commoner",60,-122.156,28,-4392.8,270.52,0)
	spawnMobile("corellia", "commoner",60,-195.909,28,-4451.7,186.379,0)
	spawnMobile("corellia", "commoner",60,-181.008,28,-4505.08,109.502,0)
	spawnMobile("corellia", "commoner",60,71.9271,28,-4568.97,267.444,0)
	spawnMobile("corellia", "commoner",60,10.3286,28,-4633.8,159.984,0)
	spawnMobile("corellia", "commoner",60,88.4953,28,-4727.94,340.398,0)
	spawnMobile("corellia", "commoner",60,55.6269,28,-4782.24,123.611,0)
	spawnMobile("corellia", "commoner",60,101.283,28,-4554.86,358.797,0)
	--{"commoner",60,-51.7918,28,-4662.65,360.011,0, "calm", "Hunter Javeezo"},

	--Corsec Outside
	spawnMobile("corellia", "corsec_deserter",300,-671.712,6.15933,-4169.03,37.6923,0)
	spawnMobile("corellia", "corsec_detective",300,-526.1,28,-4702,-41,0)
	spawnMobile("corellia", "corsec_master_sergeant",300,-172.8,28,-4167.1,0,0)
	spawnMobile("corellia", "renegade_corsec_trooper",300,-662.805,9.26289,-4182.05,196.426,0)
	spawnMobile("corellia", "corsec_traitor",300,-672.123,5.60327,-4164.83,340.354,0)
	spawnMobile("corellia", "corsec_trooper",300,-240.2,28,-4450.9,94,0)
	spawnMobile("corellia", "corsec_trooper",300,-172.8,28.0929,-4165.5,179,0)
	spawnMobile("corellia", "corsec_trooper",300,-528.144,28,-4699.89,132.784,0)
	spawnMobile("corellia", "corsec_trooper",300,0.3,28,-4464.5,-87,0)
	spawnMobile("corellia", "corsec_trooper",300,-1.67932,28,-4464.42,93.3597,0)
	spawnMobile("corellia", "corsec_trooper",300,-60,28.5,-4597.2,-96,0)
	spawnMobile("corellia", "corsec_trooper",300,-344.9,28,-4444.3,-48,0)
	spawnMobile("corellia", "corsec_trooper",300,-347.5,28,-4442.6,123,0)

	--Imperial Npc's Outside
	--{"command_security_guard",300,-175.887,28,-4765.95,86.2823,0, "npc_imperial", ""},
	spawnMobile("corellia", "dark_trooper",400,-574.2,28,-4247,333.01,0)
	spawnMobile("corellia", "dark_trooper",400,-303.8,28,-4144.4,304.009,0)
	spawnMobile("corellia", "dark_trooper",400,111.5,28,-4464.9,26.0008,0)
	--{"dark_trooper",400,141.3,28,-4540.1,138,0, "npc_imperial", ""},
	spawnMobile("corellia", "dark_trooper",400,-76.6,28.5179,-4625.3,215.006,0)
	spawnMobile("corellia", "dark_trooper",400,-124.2,28,-4798.7,116,0)
	--{"elite_sand_trooper",400,-2.3,28,-4512.6,91,0, "npc_imperial", ""},
	spawnMobile("corellia", "dark_trooper",400,-458,28,-4590.8,262.008,0)
	--{"dark_trooper",400,-175.3,28,-4837.9,-179,0, "npc_imperial", ""},
	--{"imperial_army_captain",400,-157.7,28,-4832.6,-130,0, "npc_imperial", ""},
	--{"imperial_army_captain",400,-177.7,28,-4766.5,86,0, "npc_imperial", ""},
	spawnMobile("corellia", "imperial_colonel",400,158.9,28,-4707.2,137.004,0)
	spawnMobile("corellia", "imperial_corporal",400,-289.2,28,-4416.3,-94,0)
	--{"imperial_first_lieutenant",400,-336.602,28,-4791.97,283.938,0, "npc_imperial", ""},
	--{"imperial_first_lieutenant",400,-206.6,28,-4063.8,0,0, "npc_imperial", ""},
	spawnMobile("corellia", "imperial_medic",400,-439.1,28,-4144.4,335.01,0)
	--{"imperial_medic",400,-561.9,28,-4234.3,-54,0, "npc_imperial", ""},
	spawnMobile("corellia", "imperial_warrant_officer_ii",400,-404.7,28,-4430.7,-45,0)
	--{"imperial_warrant_officer_ii",400,-541.2,28,-4628.5,176,0, "npc_imperial", ""},
	spawnMobile("corellia", "scout_trooper",400,-593.7,28,-4322,-98,0)
	spawnMobile("corellia", "scout_trooper",400,-547.3,28,-4668.3,151,0)
	spawnMobile("corellia", "scout_trooper",400,141,28,-4692.8,76,0)
	spawnMobile("corellia", "scout_trooper",400,100.5,28,-4668.1,-127,0)
	spawnMobile("corellia", "scout_trooper",400,-192.6,28,-4833.5,134,0)
	spawnMobile("corellia", "scout_trooper",400,-201.2,28.6,-4122,20.0006,0)
	spawnMobile("corellia", "specialist_noncom",400,-171.8,28,-4418,-88,0)
	spawnMobile("corellia", "storm_commando",400,48.8,28,-4569.3,34,0)
	spawnMobile("corellia", "stormtrooper",400,-557.5,28,-4230.3,266.008,0)
	spawnMobile("corellia", "stormtrooper",400,-517.9,28,-4213.9,303.009,0)
	spawnMobile("corellia", "stormtrooper",400,19.3,28,-4366.5,-176,0)
	spawnMobile("corellia", "stormtrooper",400,-64,28,-4255.2,55,0)
	spawnMobile("corellia", "stormtrooper",400,96.6,28,-4394.9,91.0027,0)
	spawnMobile("corellia", "stormtrooper",400,168.1,28,-4698.4,145.004,0)
	spawnMobile("corellia", "stormtrooper",400,-306.7,28,-4785.9,187.006,0)
	spawnMobile("corellia", "stormtrooper",400,-446.5,28,-4744,226.007,0)
	spawnMobile("corellia", "stormtrooper",400,-526.1,28,-4675.8,252.007,0)
	spawnMobile("corellia", "stormtrooper",400,-593.7,28,-4502.9,272.008,0)
	spawnMobile("corellia", "stormtrooper",400,-462.4,28,-4569.3,178,0)
	spawnMobile("corellia", "stormtrooper",400,-42.2,28,-4500.6,44.0013,0)
	spawnMobile("corellia", "stormtrooper",400,-35.4,28.5179,-4573.8,49.0014,0)
	spawnMobile("corellia", "stormtrooper",400,-249.8,28,-4412.7,96,0)
	spawnMobile("corellia", "stormtrooper",400,-215.7,29.185,-4509.8,1.00017,0)
	spawnMobile("corellia", "stormtrooper",400,-204.7,29.185,-4509.8,1.00017,0)
	--{"stormtrooper",400,-569.2,28,-4242.5,-43,0, "npc_imperial", ""},
	spawnMobile("corellia", "stormtrooper",400,-276.7,28,-4535.2,230.415,0)
	spawnMobile("corellia", "stormtrooper",400,-148.6,28,-4660.7,202.006,0)
	spawnMobile("corellia", "stormtrooper",400,-159.2,28,-4660.7,161.005,0)
	spawnMobile("corellia", "stormtrooper",400,-216.9,28.6,-4121.1,339.01,0)
	--{"stormtrooper",400,110.8,28,-4496.5,99,0, "npc_imperial", ""},
	--{"stormtrooper",400,25.8,28,-4239.9,-6,0, "npc_imperial", ""},
	spawnMobile("corellia", "stormtrooper",400,-221.1,28,-4798.1,237.007,0)
	spawnMobile("corellia", "stormtrooper",400,-531.8,28,-4628.7,-165,0)
	--{"stormtrooper_bombardier",400,-547.026,28,-4669.14,331.925,0, "npc_imperial", ""},
	spawnMobile("corellia", "stormtrooper_captain",400,19.7,28,-4282.5,-4,0)
	--{"stormtrooper_captain",400,-338.2,28,-4791.5,110,0, "npc_imperial", ""},
	spawnMobile("corellia", "stormtrooper_rifleman",400,-118.7,28,-4204.6,16.0005,0)
	spawnMobile("corellia", "stormtrooper_rifleman",400,-526.1,28,-4670.1,290.009,0)
	spawnMobile("corellia", "stormtrooper_rifleman",400,-193.7,28,-4401.6,-90,0)
	spawnMobile("corellia", "stormtrooper_rifleman",400,-316.4,28.6,-4635.8,172,0)
	spawnMobile("corellia", "stormtrooper_rifleman",400,-223.2,28,-4078,9.00022,0)
	spawnMobile("corellia", "stormtrooper_rifleman",400,-188.9,28,-4076.8,336.01,0)
	spawnMobile("corellia", "stormtrooper_sniper",400,96.6,28,-4407.1,91.0027,0)
	spawnMobile("corellia", "stormtrooper_sniper",400,-295.9,28,-4786.4,194.006,0)
	spawnMobile("corellia", "stormtrooper_sniper",400,-593.7,28,-4483.1,270.008,0)
	spawnMobile("corellia", "stormtrooper_sniper",400,-59.1,28,-4260.1,47.0014,0)
	spawnMobile("corellia", "stormtrooper_sniper",400,-275.4,28,-4614.6,256.27,0)
	--{"stormtrooper_sniper",400,-533.523,28,-4632.07,270.284,0, "npc_imperial", ""},
	spawnMobile("corellia", "stormtrooper_squad_leader",400,-226.3,28,-4378.4,90,0)
	spawnMobile("corellia", "stormtrooper_squad_leader",400,-12.4,28.6,-4404.7,181.005,0)
	--{"stormtrooper_squad_leader",400,-175.938,28,-4767.14,86.307,0, "npc_imperial", ""},

	--More Misc	
	spawnMobile("corellia", "gadget_specialist",60,19.7425,28,-4775.49,27.4957,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-33,28,-4825,45,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-86,28,-4829,0,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-172,28,-4442,270,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-172,28,-4410,225,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-212,28,-4465,0,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-250,28,-4430,90,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-428,28,-4751,225,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-477,28,-4553,180,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-566,28,-4361,90,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-508,28,-4367,45,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-359,28,-4210,270,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-293,28,-4251,315,0)
	spawnMobile("corellia", "informant_npc_lvl_1",0,-184,28,-4342,90,0)
	spawnMobile("corellia", "io_tsomcren",60,-140.701,28,-4719.16,44.0418,0)
	--{"junk_dealer",0,-118.2,28,-4792.9,-144,0, "", "",JUNKGENERIC,JUNKCONVGENERIC},

	--Meatlump's outside
	spawnMobile("corellia", "meatlump_buffoon",300,-145,28.9,-4959.8,63,0)
	spawnMobile("corellia", "meatlump_buffoon",300,-54.3,28.2,-4963.4,-90,0)
	spawnMobile("corellia", "meatlump_buffoon",300,-20.1,28,-4922.2,109,0)
	spawnMobile("corellia", "meatlump_buffoon",300,266.9,28.5,-4656.5,-109,0)
	spawnMobile("corellia", "meatlump_buffoon",300,284.5,29,-4541.7,-175,0)
	spawnMobile("corellia", "meatlump_buffoon",300,258.2,28,-4424.1,-5,0)
	spawnMobile("corellia", "meatlump_buffoon",300,-365.3,28,-4658.5,26,0)
	spawnMobile("corellia", "meatlump_buffoon",300,-270.1,28,-4923,-97,0)
	spawnMobile("corellia", "meatlump_clod",300,-130.2,31.1,-4993.8,72,0)
	spawnMobile("corellia", "meatlump_clod",300,-11.4,28,-4920.5,63,0)
	spawnMobile("corellia", "meatlump_clod",300,93.4,27.1,-4865,60,0)
	spawnMobile("corellia", "meatlump_cretin",300,-89.4,30.3,-4985.2,33,0)
	spawnMobile("corellia", "meatlump_cretin",300,188.1,27.1,-4770.2,-99,0)
	spawnMobile("corellia", "meatlump_cretin",300,287.1,29.3,-4558,-95,0)
	spawnMobile("corellia", "meatlump_cretin",300,-236.2,28.4,-4947.9,-16,0)
	spawnMobile("corellia", "meatlump_fool",300,172.6,27.9,-4773,-87,0)
	spawnMobile("corellia", "meatlump_fool",300,277.9,28.6,-4545.9,-99,0)
	spawnMobile("corellia", "meatlump_fool",300,266.6,28,-4408.9,68,0)
	spawnMobile("corellia", "meatlump_fool",300,-361.8,28,-4655,164,0)
	spawnMobile("corellia", "meatlump_fool",300,-297.3,28,-4918.8,-86,0)
	spawnMobile("corellia", "meatlump_fool",300,-257,30,-4968.4,24,0)
	spawnMobile("corellia", "meatlump_loon",300,-163,28.2,-49493,102,0)
	spawnMobile("corellia", "meatlump_loon",300,176,27.3,-4763.6,-7,0)
	spawnMobile("corellia", "meatlump_oaf",300,-136,28.8,-4958.5,83,0)
	spawnMobile("corellia", "meatlump_oaf",300,-72,28,-4973.1,-77,0)
	spawnMobile("corellia", "meatlump_oaf",300,97.6,26.6,-4867.1,101,0)
	spawnMobile("corellia", "meatlump_oaf",300,255,28.3,-4666.8,-51,0)
	spawnMobile("corellia", "meatlump_oaf",300,249.6,28,-4418.9,92,0)
	spawnMobile("corellia", "meatlump_oaf",300,-366,28,-4655,148,0)
	spawnMobile("corellia", "meatlump_oaf",300,-308,28,-4897.9,64,0)
	spawnMobile("corellia", "meatlump_stooge",300,-133.5,28.2,-4946,72,0)
	spawnMobile("corellia", "meatlump_stooge",300,-12.6,27.9,-4931.6,-19,0)
	spawnMobile("corellia", "meatlump_stooge",300,90.7,26.6,-4872.1,73,0)
	spawnMobile("corellia", "meatlump_stooge",300,252.9,28.3,-4657.7,-3,0)
	spawnMobile("corellia", "meatlump_stooge",300,293.9,29.7,-4552.4,-93,0)

	--Misc
	--{"r2",60,-13.4312,1.6,-15.4443,7.68027,1935827, "calm", "R2-P9"},
	--{"r3",60,-149.754,28,-4785.34,297.928,0, "calm", "R3-E4"},
	--{"r3",60,-182.479,28,-4731.42,293.019,0, "calm", "R3-S1"},

	--Ragtag's outside
	spawnMobile("corellia", "ragtag_kook",300,-217.315,28,-4927.23,40.3799,0)
	spawnMobile("corellia", "ragtag_kook",300,-213.219,28,-4926.08,204.867,0)
	spawnMobile("corellia", "ragtag_kook",300,-225.238,28,-4931.01,254.658,0)
	spawnMobile("corellia", "ragtag_kook",300,-212.993,28,-4922.77,38.0909,0)
	spawnMobile("corellia", "ragtag_kook",300,-712.063,5.13106,-4304.96,315.72,0)
	spawnMobile("corellia", "ragtag_kook",300,-719.18,4.19027,-4309.55,164.033,0)
	spawnMobile("corellia", "ragtag_kook",300,-703.067,2.97988,-4657.98,93.9451,0)
	spawnMobile("corellia", "ragtag_kook",300,-711.002,2.29761,-4657.71,82.4599,0)
	spawnMobile("corellia", "ragtag_loon",300,-396.754,28,-4869.82,8.29735,0)
	spawnMobile("corellia", "ragtag_loon",300,-397.655,28,-4875.17,8.04579,0)
	spawnMobile("corellia", "ragtag_loon",300,227.709,28,-4494.78,296.837,0)
	spawnMobile("corellia", "ragtag_loon",300,229.296,28,-4484.62,54.5993,0)
	spawnMobile("corellia", "ragtag_loon",300,234.249,28,-4490.03,258.204,0)
	spawnMobile("corellia", "ragtag_loon",300,227.363,28,-4490.61,140.577,0)
	spawnMobile("corellia", "ragtag_loon",300,177.412,28,-4413.68,227.101,0)
	spawnMobile("corellia", "ragtag_loon",300,177.412,28,-4411.68,159.855,0)
	spawnMobile("corellia", "ragtag_loon",300,-205.027,28.3091,-3998.32,80.3182,0)
	spawnMobile("corellia", "ragtag_loon",300,-208.5,29.2,-3999.9,191.197,0)
	spawnMobile("corellia", "ragtag_loon",300,-205.027,29.2182,-4001.32,192.016,0)
	spawnMobile("corellia", "ragtag_loon",300,-201.8,28.6,-4000.2,-122,0)
	spawnMobile("corellia", "ragtag_loon",300,-525.124,5.82557,-4079.84,207.519,0)
	spawnMobile("corellia", "ragtag_loon",300,-534.124,6.67109,-4078.84,149.496,0)
	spawnMobile("corellia", "ragtag_maniac",300,-691.483,7.08209,-4227.75,29.5129,0)
	spawnMobile("corellia", "ral_mundi",60,-138.975,28,-4718.86,10.0036,0)
	spawnMobile("corellia", "tarth_jaxx",60,-137.464,28,-4718.83,342.825,0)

	--Trainers Outside
	spawnMobile("corellia", "trainer_architect",0,-161,28,-4698,-95,0)
	spawnMobile("corellia", "trainer_artisan",0,-187,28,-4700,92,0)
	spawnMobile("corellia", "trainer_bioengineer",0,-424.092,28,-4651.85,94,0)
	spawnMobile("corellia", "trainer_brawler",0,-164,30.9,-4754,88,0)
	spawnMobile("corellia", "trainer_combatmedic",0,-33.9759,28,-4435.08,95,0)
	spawnMobile("corellia", "trainer_creaturehandler",0,-55,28,-4566,0,0)
	spawnMobile("corellia", "trainer_entertainer",0,-173,28,-4739,0,0)
	spawnMobile("corellia", "trainer_entertainer",0,-228,28.6,-4118,0,0)
	spawnMobile("corellia", "trainer_marksman",0,-165,28,-4746,92,0)
	spawnMobile("corellia", "trainer_marksman",0,-35,28,-4372,269,0)
	spawnMobile("corellia", "trainer_medic",0,-33,28,-4422,72,0)
	spawnMobile("corellia", "trainer_medic",0,-172,28,-4691,0,0)
	spawnMobile("corellia", "trainer_merchant",0,-369,28,-4533,92,0)
	spawnMobile("corellia", "trainer_politician",0,-218,28,-4500,0,0)
	spawnMobile("corellia", "trainer_ranger",0,-505,28,-4633,180,0)
	spawnMobile("corellia", "trainer_scout",0,-169.45,28,-4712.58,134,0)
	
	-- Chassis dealer.
	spawnMobile("corellia", "chassis_dealer", 0, 0.1, 0.6, 72.9, -4, 1855672)
end
