CorelliaDoabaGuerfelScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CorelliaDoabaGuerfelScreenPlay"
}

registerScreenPlay("CorelliaDoabaGuerfelScreenPlay", true)

function CorelliaDoabaGuerfelScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function CorelliaDoabaGuerfelScreenPlay:spawnSceneObjects()
 
	-- Shuttleport
    spawnSceneObject("corellia", "object/static/particle/particle_distant_ships.iff", 3078, 500, 4995, 0, 1, 0, 0, 0)
	-- Starport
    spawnSceneObject("corellia", "object/static/particle/particle_distant_ships.iff", 3340, 500, 5534, 0, 1, 0, 0, 0)    

end

function CorelliaDoabaGuerfelScreenPlay:spawnMobiles()

	--Anything dashed out will need to be added here and removed from spawn manager once the spawnMobiles command is extended.

		--Starport
	spawnMobile("corellia", "commoner", 60,3357.46,308,5639.47,212.301,0)
	spawnMobile("corellia", "commoner", 60,3414.81,308,5624.67,237.948,0)
	spawnMobile("corellia", "noble", 60,47.5747,0.974633,22.0108,238.024,9665365)
	spawnMobile("corellia", "businessman", 60,52.3124,0.639417,48.2148,107.997,9665359)
	--{"bothan_diplomat",60,36.7068,0.639417,40.446,180.001,9665359, "conversation", ""},
	spawnMobile("corellia", "farmer", 60,36.7068,0.639417,39.346,0,9665359)
	--{"brawler",60,-4.68154,0.639424,60.9856,180.005,9665356, "conversation", ""},
	--{"corsec_commissioner",300,-4.68154,0.639424,59.8856,360.011,9665356, "conversation", ""},
	--{"slicer",60,1.28595,0.639421,66.8733,0,9665356, "conversation", ""},
	--{"explorer",60,-62.5737,2.63942,41.0043,180.004,9665364, "conversation", ""},
	--{"farmer",60,-62.5737,2.63942,40.0043,360.011,9665364, "conversation", ""},
	--{"chassis_broker",60,-56.6993,0.974563,8.57384,27.5028,9665366, "neutral", ""},

		--Guild Hall/Theater
	--{"bothan_information_broker",60,-1.72179,0.6,-2.95766,180.016,4395396, "conversation", ""},
	--{"bothan_information_broker",60,-23.9134,0.6,-4.15254,360.011,4395397, "conversation", ""},
	--{"artisan",60,-1.72179,0.6,-4.05766,360.011,4395396, "conversation", ""}
	--{"farmer_rancher",60,-23.9134,0.6,-3.15254,179.996,4395397, "conversation", ""},
	--{"artisan",60,-0.629707,2.6,3.43132,180.013,4395401, "conversation", ""},
	--{"commoner",60,25.4426,0.655075,43.6577,180.006,4395401, "conversation", ""},
	--{"corsec_master_sergeant",300,-14.8394,2.41844,24.4443,5.24424,4395401, "conversation", ""},
	--{"entertainer",60,15.2654,2.37968,24.8667,180.002,4395401, "conversation", ""},
	--{"farmer",60,-17.5346,0.765493,42.402,354.765,4395401, "conversation", ""},
	--{"farmer",60,-17.5346,0.665389,43.4928,180.009,4395401, "conversation", ""},
	--{"farmer",60,25.4426,0.746078,42.666,5.24364,4395401, "conversation", ""},
	--{"info_broker",60,-14.8394,2.32744,25.4359,180.013,4395401, "conversation", ""},
	--{"mercenary",300,-0.629707,2.6,2.33132,360.011,4395401, "conversation", ""},
	--{"noble",60,15.2654,2.47978,23.7759,5.24424,4395401, "conversation", ""},
	spawnMobile("corellia", "noble", 60,28.93,2.12878,58.19,222.007,4395402)
	spawnMobile("corellia", "noble", 60,19.26,2.12847,56.13,266.008,4395403)
	--{"corsec_trooper",300,3.96145,2.12878,75.4149,0,4395403, "conversation", ""},
	--{"farmer",60,3.96145,2.12878,76.4149,180.002,4395403, "conversation", ""},
	spawnMobile("corellia", "trainer_dancer", 0,17.7541,2.12875,53.6699,1,4395403)
	spawnMobile("corellia", "trainer_entertainer", 0,30.358,2.12878,73.5895,265,4395403)
	spawnMobile("corellia", "trainer_imagedesigner", 0,-2.51106,2.12878,70.8023,2,4395403)
	spawnMobile("corellia", "trainer_musician", 0,22.0995,2.12823,63.5054,0,4395403)
	--{"artisan",60,-20.4229,2.12878,65.9439,180.013,4395404, "conversation", ""},
	--{"bodyguard",300,-20.4229,2.12878,64.9439,0,4395404, "conversation", ""},
	--{"fringer",300,-21.8263,2.12878,74.8963,179.999,4395404, "conversation", ""},
	--{"hunter",300,-21.8263,2.12878,73.7963,0,4395404, "conversation", ""},
	--{"mercenary",300,-22.9263,2.12878,74.8963,134.998,4395404, "conversation", ""},

		--Med Center
	--{"bothan_information_broker",60,-3.23192,0.184067,-5.20004,360.011,4345354, "conversation", ""},
	--{"corsec_sergeant",300,-3.23192,0.184067,-4.20004,180.012,4345354, "conversation", ""},
	spawnMobile("corellia", "surgical_droid_21b", 60,-1.19,0.184067,-1.89,230.753,4345354)
	spawnMobile("corellia", "trainer_1hsword", 0,3.5,0.2,-8.7,4,4345354)
	spawnMobile("corellia", "trainer_combatmedic", 0,8.00847,0.184067,5.47322,87,4345354)
	spawnMobile("corellia", "trainer_doctor", 0,-3.95652,0.184067,0.467273,171,4345354)
	--{"stormtrooper",400,-13,0.2,-7.7,60,4345354, "npc_imperial", ""},

		--Cantina
	--{"bartender",60,-4.00542,-0.894992,-2.41,166.23,3075429, "neutral", ""},
	--{"bothan_diplomat",60,-42.098,0.105009,-23.0786,180.012,3075441, "conversation", ""},
	--{"bounty_hunter",300,-42.098,0.105009,-24.1786,0,3075441, "conversation", ""},
	--{"corsec_commissioner",300,21.878,-0.894997,-15.7126,0,3075430, "conversation", ""},
	--{"corsec_investigator",300,40.8822,0.104999,2.22818,0,3075427, "conversation", ""},
	--{"corsec_sergeant",300,8.35364,-0.894992,6.38149,360.011,3075429, "conversation", ""},
	--{"entertainer",60,21.878,-0.894997,-14.6126,179.999,3075430, "conversation", ""},
	--{"farmer_rancher",60,8.35364,-0.894992,7.38149,179.999,3075429, "conversation", ""},
	--{"slicer",60,40.8822,0.104999,3.32819,180.003,3075427, "conversation", ""},
	
		--Guild Hall 3122 5268
	spawnMobile("corellia", "trainer_architect", 0,11,1.13306,-14,0,3075412)
	spawnMobile("corellia", "trainer_armorsmith", 0,-12,1.1,5,180,3075411)
	spawnMobile("corellia", "trainer_droidengineer", 0,-11,1.13306,-14,0,3075414)
	spawnMobile("corellia", "trainer_merchant", 0,12,1.13306,6,180,3075410)
	spawnMobile("corellia", "trainer_weaponsmith", 0,-2.5,1.13306,-8.4,91,3075413)

		--Guild Hall 3182 5240
	spawnMobile("corellia", "businessman", 60,3.32,1.13306,-8.49,228.007,3075360)
	spawnMobile("corellia", "hunter", 300,-14.01,1.13306,-8.53,120.004,3075361)
	--{"junk_dealer",0,-14.5,1.1,2.5,88,3075358, "", "",JUNKWEAPONS,JUNKCONVARMS},
	spawnMobile("corellia", "trainer_brawler", 0,-11,1.13306,-14,0,3075361)
	spawnMobile("corellia", "trainer_marksman", 0,0,1.13306,-14,0,3075360)
	spawnMobile("corellia", "trainer_scout", 0,-12,1.13306,5.5,180,3075358)

		--Guild Hall 3160 5012
	spawnMobile("corellia", "miner", 60,3.29,1.13306,-9.58,249.007,3055771)
	spawnMobile("corellia", "trainer_artisan", 0,0,1.13306,-14,0,3055771)

		--Hotel
	--{"bounty_hunter",300,17.1745,1.28309,-13.1361,0,3075367, "conversation", ""},
	--{"commoner",60,-24,1.6,-4,246.374,3075372, "calm", "An Event Promoter"},
	--{"corellia_times_investigator",60,-4.31306,0.999956,6.26959,180,3075366, "conversation", ""},
	--{"corsec_commissioner",300,7.8197,1.00001,-5.9104,180.001,3075366, "conversation", ""},
	--{"corsec_deserter",300,-5.41306,0.999953,6.26959,134.998,3075366, "conversation", ""},
	--{"corsec_investigator",300,17.1745,1.28309,-12.0361,179.995,3075367, "conversation", ""},
	--{"rogue_corsec_trooper",300,7.8197,1.00001,-7.0104,0,3075366, "conversation", ""},
	--{"medic",60,-4.31306,0.999965,5.16959,0,3075366, "conversation", ""},
	--{"willham_burke",60,0.861081,0.999995,2.33215,346.259,3075366, "neutral", ""},
	--{"zo_ssa",60,-1.1331,0.999991,1.50214,21.773,3075366, "neutral", ""},

		--Outside
	--{"bothan_information_broker",60,3202.28,290,4989.06,180.005,0, "conversation", ""},
	spawnMobile("corellia", "commoner", 60,3139.88,300,5247.41,171.321,0)
	spawnMobile("corellia", "commoner", 60,3179.26,300,5213.19,233.367,0)
	spawnMobile("corellia", "commoner", 60,3117.25,300,5194.73,153.311,0)
	spawnMobile("corellia", "commoner", 60,3108.26,300,5229.01,219.942,0)
	spawnMobile("corellia", "commoner", 60,3162.05,290,4966.73,255.989,0)
	spawnMobile("corellia", "commoner", 60,3190.76,300,5269.61,131.093,0)
	spawnMobile("corellia", "commoner", 60,3103.05,300,5164.17,50.255,0)
	spawnMobile("corellia", "commoner", 60,3192.45,302.606,5113.34,189.527,0)
	spawnMobile("corellia", "commoner", 60,3159.78,300,5397.22,81.297,0)
	spawnMobile("corellia", "commoner", 60,3199.22,300,5449.92,146.634,0)
	spawnMobile("corellia", "commoner", 60,3277.95,300,5438.73,232.081,0)
	spawnMobile("corellia", "commoner", 60,3240.99,300,5415.5,249.458,0)
	spawnMobile("corellia", "commoner", 60,3204.19,290,5003.32,222.69,0)
	spawnMobile("corellia", "commoner", 60,3202.3,290,5034.41,29.3152,0)
	spawnMobile("corellia", "commoner", 60,3296.88,324,5760.95,196.788,0)
	--{"commoner",60,3300.28,308,5495.49,0,0, "conversation", ""},
	spawnMobile("corellia", "commoner", 60,3316.17,308,5496.71,3.31657,0)
	spawnMobile("corellia", "commoner", 60,3308.36,300,5396.79,274.041,0)
	spawnMobile("corellia", "commoner", 60,3320.73,324,5709.36,340.725,0)
	spawnMobile("corellia", "commoner", 60,3307.64,308.031,5618.18,225.888,0)
	spawnMobile("corellia", "commoner", 60,3385.33,308,5699.29,242.976,0)
	spawnMobile("corellia", "commoner", 60,3322.09,308,5484.42,146.419,0)
	spawnMobile("corellia", "commoner", 60,3303.05,300,5351.87,319.052,0)
	spawnMobile("corellia", "commoner", 60,3411.89,308,5515.19,208.425,0)
	spawnMobile("corellia", "commoner", 60,3431.28,308,5563.41,159.884,0)
	--{"corsec_chief",300,3154.04,300,5173.07,180.005,0, "conversation", ""},
	spawnMobile("corellia", "corsec_chief",360,3121,285,5006.4,-161,0)
	--{"corsec_master_sergeant",300,3300.28,308,5496.49,180.005,0, "conversation", ""},
	--{"corsec_sergeant",300,3154.04,300,5172.07,0,0, "conversation", ""},
	spawnMobile("corellia", "corsec_trooper", 360,3119.2,285,5002.2,20,0)
	--{"comm_operator",300,3308,308,5485.8,45,0, "npc_imperial", ""},
	--{"dark_trooper",400,3173.3,300,5302.5,-155,0, "npc_imperial", ""},
	--{"dark_trooper",400,3181,302.9,5099.8,175,0, "npc_imperial", ""},
	--{"elite_sand_trooper",400,3142.5,300,5169.9,179,0, "npc_imperial", ""},
	--{"elite_sand_trooper",400,3319.3,308,5523.9,25,0, "npc_imperial", ""},
	--{"imperial_corporal",400,3310.8,308,5482.9,45,0, "npc_imperial", ""},
	spawnMobile("corellia", "imperial_noncom", 400,3327.5,308,5518.6,25,0)
	spawnMobile("corellia", "storm_commando", 400,3181.3,300,5298.6,-147,0)
	--{"stormtrooper",400,3171.4,301.9,5100.1,175,0, "npc_imperial", ""},
	--{"stormtrooper",400,3141.3,290,4984.9,-89,0, "npc_imperial", ""},
	--{"stormtrooper_rifleman",400,3133.4,300,5169.9,178,0, "npc_imperial", ""},
	--{"stormtrooper_squad_leader",400,3141.1,290,4975.7,-95,0, "npc_imperial", ""},
	--{"farmer_rancher",60,3196.61,295.033,5073.8,350.188,0, "conversation", ""},
	--{"farmer_rancher",60,3196.61,295.206,5074.8,180.005,0, "conversation", ""},
	--{"gambler",60,3184.22,300,5162.04,0,0, "conversation", ""},
	--{"gambler",60,3184.22,300,5163.04,180.005,0, "conversation", ""},
	--{"hunter",300,3145.1,290,4995.55,180.005,0, "conversation", ""},
	spawnMobile("corellia", "informant_npc_lvl_1", 0,3100,300,5224,90,0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0,3123,300,5188,0,0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0,3145,300,5148,90,0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0,3165,295.7,5077,180,0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0,3078,280,5014,270,0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0,3210,300,5440,100,0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0,3311,300,5386,300,0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0,3293,300,5401,90,0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0,3297,308,5514,70,0)
	--{"junk_dealer",0,3402.4,308,5679,5,0, "", "",JUNKGENERIC,JUNKCONVGENERIC},
	spawnMobile("corellia", "noble", 60,3158.95,300,5352.24,80.7765,0)
	--{"pilot",60,3202.28,290,4988.06,0,0, "conversation", ""},
	spawnMobile("corellia", "scolex_grath", 60,3347.39,308,5490.74,251.277,0)
	spawnMobile("corellia", "trainer_artisan", 0,3311,308,5530,83,0)
	spawnMobile("corellia", "trainer_brawler", 0,3334,308,5517,0,0)
	spawnMobile("corellia", "trainer_chef", 0,3070,300,5260,180,0)
	spawnMobile("corellia", "trainer_creaturehandler",0,3162,300,5191,0,0)
	spawnMobile("corellia", "trainer_entertainer", 0,3305,308,5525,151,0)
	spawnMobile("corellia", "trainer_marksman", 0,3338,308,5516,0,0)
	spawnMobile("corellia", "trainer_medic", 0,3341,308,5517,47,0)
	spawnMobile("corellia", "trainer_scout", 0,3330.01,308,5512.46,204,0)
	spawnMobile("corellia", "trainer_tailor", 0,3077,300,5251,0,0)

end
