TatooineMosEnthaScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineMosEnthaScreenPlay"
}

registerScreenPlay("TatooineMosEnthaScreenPlay", true)

function TatooineMosEnthaScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function TatooineMosEnthaScreenPlay:spawnSceneObjects()
	--just outside starport
	spawnSceneObject("tatooine", "object/tangible/crafting/station/public_space_station.iff", 1304.5, 7, 3098.54, 0, math.rad(80) )
	--Lower Floor
	spawnSceneObject("tatooine", "object/tangible/terminal/terminal_elevator_down.iff", -3.5, 9, -21.4, 1153524, 1, 0, 0, 0) --Middle
	spawnSceneObject("tatooine", "object/tangible/terminal/terminal_elevator_up.iff", -3.5, 0, -21.4, 1153524, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/terminal/terminal_elevator_down.iff", .5, 9, -21.4, 1153525, 1, 0, 0, 0) --Left side
	spawnSceneObject("tatooine", "object/tangible/terminal/terminal_elevator_up.iff", .5, 0, -21.4, 1153525, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/terminal/terminal_elevator_down.iff", -7.5, 9, -21.4, 1153523, 1, 0, 0, 0) --Right side
	spawnSceneObject("tatooine", "object/tangible/terminal/terminal_elevator_up.iff", -7.5, 0, -21.4, 1153523, 1, 0, 0, 0)
	--Upper Floor
	spawnSceneObject("tatooine", "object/tangible/terminal/terminal_elevator_up.iff", 13.5, 7, -17.95, 1153526, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/terminal/terminal_elevator_down.iff", 13.5, 15, -17.95, 1153526, 1, 0, 0, 0)
end

function TatooineMosEnthaScreenPlay:spawnMobiles()

	--Anything dashed out will need to be added here and removed from spawn manager once the spawnMobiles command is extended.

	--Starport	
	--{"dim_u_priestess",300,53.5956,-0.521137,38.1243,135.004,4005523, "conversation", ""},
	--{"hermit",60,54.6956,-0.521137,37.0243,360.011,4005523, "conversation", ""},
	--{"mercenary",60,54.6956,-0.521137,38.1243,180.008,4005523, "conversation", ""},
	--{"mos_entha_police_officer",300,41.2,-0.5,29.7,63,4005523, "npc_sitting_chair", ""},
	--{"chassis_broker",60,2.14833,0.639422,67.5897,224.216,4005520, "neutral", ""},
	--{"moisture_farmer",300,-36.1846,1.63942,64.2406,180.002,4005525, "conversation", ""},
	--{"scavenger",300,-36.1846,1.63942,63.1406,360.011,4005525, "conversation", ""},
	--{"rodian_clan_medic",300,-53.137,2.63942,38.7938,180.007,4005528, "conversation", ""},
	--{"smuggler",300,-53.137,2.63942,37.6938,360.011,4005528, "conversation", ""},
	--{"squatter",300,-54.237,2.63942,38.7938,135.003,4005528, "conversation", ""},

	--Guild Hall 1377 3011
	spawnMobile("tatooine", "trainer_brawler",0,-11,1.1,-14,0,1153566)
	spawnMobile("tatooine", "trainer_marksman",0,0,0,-13,0,1153565)
	spawnMobile("tatooine", "trainer_scout",0,-13,1.1,4.8,180,1153563)
	spawnMobile("tatooine", "hunter",300,-14.01,1.13306,-8.53,120.004,1153566)
	spawnMobile("tatooine", "businessman",60,3.32,1.13306,-8.49,228.007,1153565)

	--House 1447 2982
	spawnMobile("tatooine", "jabba_scout",300,3.6,0.3,5.2,21,1156906)
	spawnMobile("tatooine", "jabba_scout",300,0.4,-0.4,-3.5,-87,1156915)
	spawnMobile("tatooine", "jabba_scout",300,-1.9,-0.4,-3.4,91,1156915)

	--Tavern 1613 2962
	spawnMobile("tatooine", "scientist",60,1.7,1,5.3,90,1153626)

	--Guild Hall 1560 3046
	spawnMobile("tatooine", "contractor",60,-3.69,1.13306,-6,11.0003,1153489)
	spawnMobile("tatooine", "miner",60,3.29,1.13306,-9.58,249.007,1153493)
	spawnMobile("tatooine", "trainer_artisan",0,-0.0475945,1.13306,-14.1102,0,1153493)

	--Fallen Star Cantina
	--{"artisan",60,-3.4032,7.01,5.99576,180,1153497, "conversation", ""},
	--{"smuggler",300,-3.4032,7.01,4.89576,360.011,1153497, "conversation", ""},
	spawnMobile("tatooine", "businessman",60,-25.2156,9.01,-0.754679,77.0153,1153499)
	--{"commoner_tatooine",60,-24.5917,9.01,2.41044,135.004,1153499, "conversation", ""},
	--{"spacer",300,-23.4917,9.01,1.31044,0,1153499, "conversation", ""},
	--{"squatter",300,-23.4917,9.01,2.41044,180.008,1153499, "conversation", ""},
	--{"bodyguard",300,17.1949,7.01,1.93821,135.005,1153501, "conversation", ""},
	--{"rodian_clan_warchief",300,18.2949,7.01,0.838211,0,1153501, "conversation", ""},
	--{"squatter",300,18.2949,7.01,1.93821,180.006,1153501, "conversation", ""},
	spawnMobile("tatooine", "criminal",300,4.3863,7.01,12.7119,95.2452,1153503)
	--Lower Floor
	--{"commoner_naboo",60,-14.2049,-0.255725,-12.4673,270.07,1153507, "conversation", ""},
	--{"commoner_tatooine",60,-16.1968,-0.255725,-12.4652,90.0645,1153507, "conversation", ""},
	--{"r5",60,-15.2049,-0.255725,-11.4673,64.6561,1153507, "calm", "R5-N0"},
	--{"nomad",60,-11.7551,0.0100002,-1.23478,180.012,1153512, "conversation", ""},
	--{"tatooine_militiaman",300,-11.7551,0.0100002,-2.33478,360.011,1153512, "conversation", ""},
	--{"entertainer",60,29.3646,-0.255725,-0.43765,45.001,1153522, "conversation", ""},
	--{"rodian_clan_medic",300,30.4646,-0.255725,-0.43765,360.011,1153522, "conversation", ""},
	--{"scavenger",300,29.3646,-0.255725,0.66235,135.003,1153522, "conversation", ""},
	--{"tatooine_militiaman",300,30.4646,-0.255725,0.66235,180,1153522, "conversation", ""},
	--{"bounty_hunter",300,12.7978,-0.255725,9.20473,180.002,1153520, "conversation", ""},
	--{"dim_u_abbot",300,12.7978,-0.255725,8.10473,360.011,1153520, "conversation", ""},
	--{"commoner_tatooine",60,18.4,-0.3,-10.5,24,1153518, "conversation", ""},
	--{"commoner_tatooine",60,19.3,-0.3,-9,-132,1153518, "conversation", ""},
	--{"r2",60,20.3,-0.3,-11.3,-44,1153518, "calm", "R2-C6"},

	--Med Center
	spawnMobile("tatooine", "surgical_droid_21b",60,-25.52,0.26,-3.48,142.122,1153586)
	spawnMobile("tatooine", "trainer_combatmedic",0,-16.4794,0.26,9.71928,162,1153586)
	spawnMobile("tatooine", "trainer_doctor",0,-24.6019,0.26,-3.96049,212,1153586)
	spawnMobile("tatooine", "trainer_medic",0,-17.0194,0.26,-1.8269,149,1153586)
	spawnMobile("tatooine", "trainer_combatmedic",0,28,0.26,6.3,227,1153582)
	spawnMobile("tatooine", "trainer_doctor",0,20,0.26,-5.6,87,1153582)
	spawnMobile("tatooine", "trainer_medic",0,14.1436,0.26,4.6585,190,1153582)

	--Tavern 1366 3224
	spawnMobile("tatooine", "businessman",60,-1.9,1,6.8,-95,1153936)

	--Guild Hall 1319 3380
	spawnMobile("tatooine", "trainer_architect",0,11,1.133,-14.5,0,1154183)
	spawnMobile("tatooine", "trainer_armorsmith",0,-12.6959,1.13306,3.59178,153,1154182)
	spawnMobile("tatooine", "trainer_droidengineer",0,-11.2719,1.13306,-13.4562,0,1154185)
	spawnMobile("tatooine", "trainer_merchant",0,12,1.13306,6,180,1154181)
	spawnMobile("tatooine", "trainer_weaponsmith",0,-3.1,1.1,-8.4,95,1154184)

	--Guild Hall/Theater
	--{"farmer_rancher",60,25.1612,2.6,17.6257,180.006,1153601, "conversation", ""},
	--{"info_broker",60,-17.046,2.6,18.3264,180.006,1153601, "conversation", ""},
	--{"dim_u_monk",300,29.2773,2.12878,57.8777,180.278,1153602, "conversation", ""},
	--{"medic",60,29.2719,2.12878,56.7798,0.27412,1153602, "conversation", ""},
	spawnMobile("tatooine", "noble",60,28.93,2.12878,58.19,222.007,1153602)
	spawnMobile("tatooine", "noble",60,19.26,2.12847,56.13,266.008,1153603)
	--{"slicer",60,28.1719,2.12878,57.8798,135.001,1153602, "conversation", ""},
	--{"brawler",60,3.25667,2.12878,71.8841,360.011,1153603, "conversation", ""},
	spawnMobile("tatooine", "theater_manager",60,21.99,2.12804,64.05,4.00007,1153603)
	--{"thivauwrai_aphereef",60,3.25667,2.12878,72.8841,180.009,1153603, "conversation", "Thivauwrai Aphereef"},
	spawnMobile("tatooine", "trainer_dancer",0,17.812,2.12873,53.8433,1,1153603)
	spawnMobile("tatooine", "trainer_entertainer",0,29.9638,2.12878,73.0406,88,1153603)
	spawnMobile("tatooine", "trainer_imagedesigner",0,-21.3524,2.12878,74.1456,164,1153604)

	--Outside
	--{"agriculturalist",60,1356.66,7,3413.13,0,0, "conversation", ""},
	spawnMobile("tatooine", "businessman",60,1303.42,7,3113.38,42.5733,0)
	spawnMobile("tatooine", "businessman",60,1606.53,7,3357.48,234.979,0)
	spawnMobile("tatooine", "commoner",60,1187.85,7,2996.69,61.1413,0)
	spawnMobile("tatooine", "commoner",60,1420.16,7,3089.99,188.698,0)
	spawnMobile("tatooine", "commoner",60,1723.47,7,3130.73,52.9966,0)
	spawnMobile("tatooine", "commoner",60,1752.63,7,3163.33,292.898,0)
	spawnMobile("tatooine", "commoner_fat",60,1448.18,7,2974.11,175.638,0)
	spawnMobile("tatooine", "commoner_fat",60,1326.19,7,3409.97,355.137,0)
	spawnMobile("tatooine", "commoner_naboo",60,1294.55,7,3002.8,111.166,0)
	spawnMobile("tatooine", "commoner_naboo",60,1389.06,7.5,3162.26,1.64759,0)
	--{"commoner_naboo",60,1328.4,7,3028.17,238.827,0, "conversation", ""},
	spawnMobile("tatooine", "commoner_naboo",60,1450.08,7,3202.92,223.221,0)
	spawnMobile("tatooine", "commoner_naboo",60,1448.7,7,3183.32,42.471,0)
	spawnMobile("tatooine", "commoner_naboo",60,1495.58,7,3177.88,278.103,0)
	spawnMobile("tatooine", "commoner_naboo",60,1609.53,10.9973,3163.55,239.286,0)
	spawnMobile("tatooine", "commoner_naboo",60,1636.62,7,3124.11,33.7288,0)
	spawnMobile("tatooine", "commoner_naboo",60,1624.1,7,2929.75,185.957,0)
	spawnMobile("tatooine", "commoner_naboo",60,1647.95,7,2957,97.7955,0)
	spawnMobile("tatooine", "commoner_naboo",60,1639.18,7,3070.97,82.98,0)
	spawnMobile("tatooine", "commoner_old",60,1184.74,7,3106.09,161.401,0)
	spawnMobile("tatooine", "commoner_old",60,1288.86,7,3208.83,321.512,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1169.4,7,3063.85,171.962,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1197.96,7,2937.67,46.5906,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1312.96,7,3028.24,216.261,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1340.32,7,3068.23,51.271,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1378.9,7,3087.88,171.156,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1391.32,7.5,3202.54,15.2442,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1302.38,7,3357.34,93.6624,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1242.3,7,3321.72,32.6955,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1225.63,7,2970.92,264.35,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1449.68,7,3159.65,96.9033,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1449.89,7,3138,131.557,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1516.09,7,3164.73,72.0873,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1619.54,11,3228.91,330.791,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1615.17,7,3313.63,227.564,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1556.48,7,3324.92,237.451,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1583.89,7,3429.16,52.5515,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1554.59,15,3500.85,259.137,0)
	spawnMobile("tatooine", "commoner_tatooine",60,1508.04,15,3486.27,274.387,0)
	--{"coris_mao",60,1538.55,7,3105.42,79.0161,0, "calm", "Coris Mao"},
	spawnMobile("tatooine", "criminal",300,1276.88,7,3180.3,164.363,0)
	spawnMobile("tatooine", "criminal",300,1621.79,7,3319.3,202.393,0)
	spawnMobile("tatooine", "criminal",300,1621.1,7,3317.4,18,0)
	--{"dim_u_monastery_nun",300,1326.93,7,3164.39,180.005,0, "conversation", ""},
	spawnMobile("tatooine", "eg6_power_droid",60,1332.45,7.90682,3237.09,8.18614,0)
	spawnMobile("tatooine", "informant_npc_lvl_1",0,1266,7,3184,225,0)
	spawnMobile("tatooine", "informant_npc_lvl_1",0,1727,7,3093,225,0)
	--{"junk_dealer",0,1308.1,7,3085.2,1,0, "", "",JUNKGENERIC,JUNKCONVGENERIC},
	--{"kolka_zteht",60,1521.78,7,3259.81,184.256,0, "neutral", ""},
	--{"miner",60,1326.44,7,3119.75,0,0, "conversation", ""},
	--{"moisture_farmer",300,1191.8,7,2957,180.005,0, "conversation", ""},
	--{"noble",60,1191.8,7,2955.7,360.011,0, "conversation", ""},
	spawnMobile("tatooine", "noble",60,1455.33,7,3335.99,114.201,0)
	--{"ovo",60,1744.45,7,3057.53,0,0, "conversation", "Ovo"},
	spawnMobile("tatooine", "quest_gadget_specialist",60,1209.57,7,2923.54,58.9701,0)
	--{"r3",60,1242.26,7,3155.65,78.1127,0, "calm", "R3-Q5"},
	--{"r4",60,1456.33,7,3336.99,338.919,0, "calm", "R4-D2"},
	--{"r4",60,1565.89,7,3111.38,272.874,0, "calm", "R4-Y3"},
	--{"r4",60,1583.75,7,3113.82,97.4626,0, "calm", "R4-G0"},
	--{"r5",60,1332.83,11,3233.94,186.564,0, "calm", "R5-X9"},
	--{"r5",60,1614.51,7,3127.01,256.31,0, "calm", "R5-T9"},
	--{"rodian_clan_medic",300,1190.5,7,2957,135.004,0, "conversation", ""},
	--{"rodian_clan_medic",300,1744.45,7,3058.83,180.005,0, "conversation", ""},
	--{"scientist",60,1326.93,7,3163.39,359.931,0, "conversation", ""},
	--{"settler",300,1326.44,7,3120.75,180.005,0, "conversation", ""},
	--{"settler",300,1355.36,7,3414.43,135.004,0, "conversation", ""},
	--{"smuggler",300,1356.66,7,3414.43,180.005,0, "conversation", ""},
	spawnMobile("tatooine", "trainer_armorsmith",0,1247,4,3248,16,0)
	spawnMobile("tatooine", "trainer_artisan",0,1276.55,7,3153.11,160,0)
	spawnMobile("tatooine", "trainer_artisan",0,1324,7,3141,250,0)
	spawnMobile("tatooine", "trainer_artisan",0,1335,7,3487,140,0)
	spawnMobile("tatooine", "trainer_brawler",0,1310,7,3088,0,0)
	spawnMobile("tatooine", "trainer_brawler",0,1741,7,3117,0,0)
	spawnMobile("tatooine", "trainer_carbine",0,1158,7,3110,180,0)
	spawnMobile("tatooine", "trainer_commando",0,1551.92,7,3334.86,56,0)
	spawnMobile("tatooine", "trainer_creaturehandler",0,1374,7,3262,180,0)
	spawnMobile("tatooine", "trainer_doctor",0,1370,7,3164,180,0)
	spawnMobile("tatooine", "trainer_entertainer",0,1287,7,3163,85,0)
	spawnMobile("tatooine", "trainer_marksman",0,1321,7,3105,180,0)
	spawnMobile("tatooine", "trainer_medic",0,1325,7,3148,269,0)
	spawnMobile("tatooine", "trainer_merchant",0,1273,7,3151,160,0)
	spawnMobile("tatooine", "trainer_musician",0,1481,7,3267,0,0)
	spawnMobile("tatooine", "trainer_ranger",0,1240,7,3356,0,0)
	spawnMobile("tatooine", "trainer_scout",0,1303,7,3199,180,0)
	spawnMobile("tatooine", "trainer_weaponsmith",0,1210,7.4,3273,170,0)
	spawnMobile("tatooine", "trainer_weaponsmith",0,1394,7,3447,95,0)
	spawnMobile("tatooine", "valarian_thug",300,1618.4,11,3283.9,150,0)
	spawnMobile("tatooine", "valarian_thug",300,1618.1,11,3278.5,32,0)
	spawnMobile("tatooine", "valarian_thug",300,1620.8,11,3282,-99,0)

	--Jawa's
	--{"jawa",300,1461.87,7,3223.41,270.008,0, "conversation", ""},
	--{"jawa",300,1459.87,7,3223.41,90.0027,0, "conversation", ""},
	--{"jawa",300,1460.87,7,3222.41,0,0, "conversation", ""},
	spawnMobile("tatooine", "jawa",300,1189.08,7,2993.49,125.726,0)
	spawnMobile("tatooine", "jawa",300,1566.49,7,3337.08,73.205,0)
	spawnMobile("tatooine", "jawa",300,1590.1,7,3339.5,-105,0)
	spawnMobile("tatooine", "jawa",300,1606.37,7,3348.55,244.837,0)
	spawnMobile("tatooine", "jawa",300,1609.44,7,3350.05,72.4758,0)
	spawnMobile("tatooine", "jawa",300,1605.5,7,3347.9,50,0)
	spawnMobile("tatooine", "jawa",300,1610.4,7,3350.3,-102,0)
	spawnMobile("tatooine", "jawa",300,1610.92,7,3318.88,238.788,0)
	spawnMobile("tatooine", "jawa",300,1567.9,7,3337.4,-105,0)
	spawnMobile("tatooine", "jawa",300,1610.2,7,3318.2,49,0)
	spawnMobile("tatooine", "jawa",300,1555.27,7,3333.7,282.519,0)
	spawnMobile("tatooine", "jawa",300,1588.78,7,3339.21,83.5812,0)
	spawnMobile("tatooine", "jawa_engineer",300,1604.2,7,3344.5,-57,0)
	spawnMobile("tatooine", "jawa_engineer",300,1602.4,7,3344.2,44,0)
	spawnMobile("tatooine", "jawa_engineer",300,1608.3,7,3328.9,183.417,0)
	spawnMobile("tatooine", "jawa_healer",300,1578.2,7,3337.93,83.3041,0)
	spawnMobile("tatooine", "jawa_healer",300,1573.4,7,3337.5,-107,0)
	spawnMobile("tatooine", "jawa_healer",300,1606.95,7,3315.18,199.684,0)
	spawnMobile("tatooine", "jawa_smuggler",300,1579.7,7,3338.3,-104,0)
	spawnMobile("tatooine", "jawa_smuggler",300,1603.79,7,3345.6,232.777,0)
	spawnMobile("tatooine", "jawa_thief",300,1606.7,7,3313.6,6,0)
	spawnMobile("tatooine", "jawa_warlord",300,1347.83,7,3060.74,47.0278,0)
	spawnMobile("tatooine", "jawa_warlord",300,1608.4,7,3328.1,-21,0)
	spawnMobile("tatooine", "jawa_warlord",300,1572.44,7,3337.29,83.3917,0)

	--Imp Npc's Outside
	--{"comm_operator",400,1626.03,7.36699,3513.56,31.2213,0, "npc_imperial", ""},
	--{"elite_sand_trooper",400,1618.9,11,3241.7,86.0025,0, "npc_imperial", ""},
	--{"elite_sand_trooper",400,1376.6,7,3267.5,133.004,0, "npc_imperial", ""},
	spawnMobile("tatooine", "elite_sand_trooper",400,1629.95,7.34272,3522.79,42.3654,0)
	--{"imperial_exterminator",400,1593.3,7,3020.2,82.0024,0, "npc_imperial", ""},
	spawnMobile("tatooine", "imperial_exterminator",400,1502.5,7,3156.9,359.01,0)
	--{"imperial_noncom",400,1566.7,11,3230.16,357.031,0, "npc_imperial", ""},
	spawnMobile("tatooine", "imperial_sergeant",400,1602.89,11,3255.09,268.945,0)
	--{"imperial_sharpshooter",400,1538.7,10.866,3219.9,266.008,0, "npc_imperial", ""},
	spawnMobile("tatooine", "sand_trooper",400,1605.71,11,3255.47,290.005,0)
	--{"sand_trooper",400,1600.5,11,3188.98,71.1851,0, "npc_imperial", ""},
	--{"sand_trooper",400,1738.6,7.6,3191.1,178.005,0, "npc_imperial", ""},
	--{"sand_trooper",400,1715.3,7,3147.1,176.005,0, "npc_imperial", ""},
	--{"sand_trooper",400,1688.8,7,3125.2,358.011,0, "npc_imperial", ""},
	--{"sand_trooper",400,1759.6,7,3186.1,78.0023,0, "npc_imperial", ""},
	--{"sand_trooper",400,1663,7,3109.8,147.004,0, "npc_imperial", ""},
	--{"sand_trooper",400,1637.2,7,2980.3,181.005,0, "npc_imperial", ""},
	--{"sand_trooper",400,1557.7,9.5,3045.7,173.005,0, "npc_imperial", ""},
	spawnMobile("tatooine", "sand_trooper",400,1508.1,7,3127.9,174.005,0)
	spawnMobile("tatooine", "sand_trooper",400,1444.6,7,3106.9,90.0027,0)
	spawnMobile("tatooine", "sand_trooper",400,1380.4,9.5,3012.4,181.005,0)
	spawnMobile("tatooine", "sand_trooper",400,1333.6,7,3490,93.0027,0)
	spawnMobile("tatooine", "sand_trooper",400,1286.3,7.7102,2954.7,42.0012,0)
	spawnMobile("tatooine", "sand_trooper",400,1181.3,7,3087.9,281.008,0)
	spawnMobile("tatooine", "sand_trooper",400,1264,7,3159.3,278.008,0)
	spawnMobile("tatooine", "sand_trooper",400,1272.7,7,3255.9,87.0026,0)
	spawnMobile("tatooine", "sand_trooper",400,1431.6,9.5,3372.5,181.005,0)
	spawnMobile("tatooine", "sand_trooper",400,1625.7,7,2978.1,137,0)
	spawnMobile("tatooine", "sand_trooper",400,1626.92,7.34652,3512.12,27.1283,0)
	--{"sand_trooper",400,1598.04,11,3188.15,71.1795,0, "npc_imperial", ""},
	--{"sand_trooper",400,1407.2,7.6,3472.1,175,0, "npc_imperial", ""},
	spawnMobile("tatooine", "sand_trooper",400,1624.2,7.41708,3516.48,81.6028,0)
	--{"scout_trooper",400,1487.2,7,3240.8,318.009,0, "npc_imperial", ""},
	--{"scout_trooper",400,1455.2,7,3232.5,188.006,0, "npc_imperial", ""},
	spawnMobile("tatooine", "scout_trooper",400,1597.4,11,3186.76,74.2722,0)
	--{"storm_commando",400,1289.2,7,3128,26.0008,0, "npc_imperial", ""},
	--{"storm_commando",400,1282.4,7,3133.1,28.0008,0, "npc_imperial", ""},
	spawnMobile("tatooine", "storm_commando",400,1320.9,9.5,3382.9,90.0027,0)
	spawnMobile("tatooine", "stormtrooper",400,1401,7,3094.3,267.747,0)
	spawnMobile("tatooine", "stormtrooper",400,1399.4,7,3094.3,268.154,0)
	spawnMobile("tatooine", "stormtrooper",400,1628.23,7.32035,3512.41,23.9809,0)
	--{"stormtrooper",400,1565.41,11,3235.35,191.674,0, "npc_imperial", ""},
	spawnMobile("tatooine", "stormtrooper",400,1623.03,7.45177,3516.22,42.7463,0)
	spawnMobile("tatooine", "stormtrooper_captain",400,1400.2,7,3090.2,241.546,0)
	spawnMobile("tatooine", "stormtrooper_rifleman",400,1256,7.7102,2954.3,306.009,0)

	spawnMobile("tatooine", "mos_entha_police_officer",300,1625.6,7,3029.5,-179,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1815.9,7,3182,40,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1795.9,7,3213,36,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1576.5,7,3315.1,49,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1448,7,3174.5,174,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1302.3,7,3165.4,28,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1293,7,3263.3,176,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1481.7,7,3065.9,-173,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1388.9,7,3082.9,-88,0)
	--{"mos_entha_police_officer",300,41.2,-0.5,29.7,63,4005523, "npc_sitting_chair", ""},
	spawnMobile("tatooine", "mos_entha_police_officer",300,1526.2,7,3238.6,151,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1424.1,7,3251.1,-70,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1287.6,7.7,2922.1,129,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1570.4,11,3248.28,-141,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1571.71,11,3249.69,-141,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1571.56,11,3247.83,-141,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1632.1,7,3142,122,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1444.9,7,3344.9,-105,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1447.4,7,3346.4,-105,0)
	spawnMobile("tatooine", "mos_entha_police_officer",300,1448.8,7,3344.5,-105,0)

	--Creatures
	spawnMobile("tatooine", "desert_razorback",300,1085.48,5.82507,3065.96,107.775,0)
	spawnMobile("tatooine", "desert_razorback",300,1083.59,6.13166,3075.94,41.0805,0)
	spawnMobile("tatooine", "desert_razorback",300,1094.58,5.57916,3087.09,213.896,0)
	spawnMobile("tatooine", "desert_razorback",300,1203.76,7,2929.8,177.768,0)
	spawnMobile("tatooine", "desert_razorback",300,1208.79,7,2949.24,22.6418,0)
	spawnMobile("tatooine", "giant_sand_beetle",360,1846.71,9.40988,2982.52,304.053,0)
	spawnMobile("tatooine", "giant_sand_beetle",360,1848.87,9.71876,2972.28,198.153,0)
	spawnMobile("tatooine", "kreetle",300,1044.5,7.0287,3032.47,235.314,0)
	spawnMobile("tatooine", "kreetle",300,1049.37,6.92825,3053.45,44.8166,0)
	spawnMobile("tatooine", "kreetle",300,1141.08,29.2815,3442.2,225.319,0)
	spawnMobile("tatooine", "kreetle",300,1159.34,26.0984,3455.89,2.15337,0)
	spawnMobile("tatooine", "kreetle",300,1267.7,8.63449,3561.35,89.6686,0)
	spawnMobile("tatooine", "kreetle",300,1284.04,8.57263,3570.14,42.417,0)
	spawnMobile("tatooine", "kreetle",300,1387.95,7.9817,3558.68,198.042,0)
	spawnMobile("tatooine", "kreetle",300,1381.66,9.90952,3574.83,289.828,0)
	spawnMobile("tatooine", "kreetle",300,1384.58,8.32903,3562.44,60.3494,0)
	spawnMobile("tatooine", "kreetle",300,1385.76,8.10126,3560.41,228.641,0)
	spawnMobile("tatooine", "kreetle",300,1475.43,9.2151,3551.59,342.411,0)
	spawnMobile("tatooine", "kreetle",300,1471.74,9.70389,3555.05,3.28598,0)
	spawnMobile("tatooine", "kreetle",300,1685.87,10.1713,2832.4,275.554,0)
	spawnMobile("tatooine", "kreetle",300,1693.1,10.2439,2830.06,333.897,0)
	spawnMobile("tatooine", "kreetle",300,1694.02,12,3450.08,124.813,0)
	spawnMobile("tatooine", "kreetle",300,1872.92,8.96768,2965.44,91.9334,0)
	spawnMobile("tatooine", "kreetle",300,1859.94,8.77464,2963.42,243.468,0)
	spawnMobile("tatooine", "kreetle",300,1736.14,7.40122,3265.29,238.497,0)
	spawnMobile("tatooine", "kreetle",300,1741.69,8.61579,3276.76,44.2833,0)
	spawnMobile("tatooine", "kreetle",300,1824,6.77883,3233.9,338.908,0)
	spawnMobile("tatooine", "kreetle",300,1834.6,5.40456,3238.51,72.0806,0)
	spawnMobile("tatooine", "kreetle",300,1905.04,14.1019,3085.49,62.9248,0)
	spawnMobile("tatooine", "kreetle",300,1904.71,13.5966,3075.98,152.726,0)
	spawnMobile("tatooine", "kreetle",300,1896.15,12.2618,3089.08,324.915,0)
	spawnMobile("tatooine", "kreetle",300,1897.89,12.4578,3080.4,322.632,0)
	spawnMobile("tatooine", "kreetle",300,1125.1,10.2579,3227.8,188.841,0)
	spawnMobile("tatooine", "kreetle",300,1128.07,13.6707,3250.95,327.357,0)
	spawnMobile("tatooine", "kreetle",300,1109.77,16.1342,3243.99,314.595,0)
	spawnMobile("tatooine", "kreetle",300,1136.03,9.90696,3239.44,67.0593,0)
	spawnMobile("tatooine", "kreetle",300,1113.09,16.5217,3247.43,260.633,0)
	spawnMobile("tatooine", "kreetle",300,1056,7.47361,2942.77,93.8727,0)
	spawnMobile("tatooine", "kreetle",300,1061.3,7.9681,2958.99,164.005,0)
	spawnMobile("tatooine", "kreetle",300,1091.72,7.68251,2909.81,310.6,0)
	spawnMobile("tatooine", "kreetle",300,1085.7,7.64405,2913.73,234.589,0)
	spawnMobile("tatooine", "kreetle",300,1088.35,7.36404,2903.8,301.961,0)
	spawnMobile("tatooine", "kreetle",300,1191.3,7.17686,2848.67,140.25,0)
	spawnMobile("tatooine", "kreetle",300,1193.17,7.38531,2867.31,340.572,0)
	spawnMobile("tatooine", "kreetle",300,1264.36,9.84013,2838.12,116.66,0)
	spawnMobile("tatooine", "kreetle",300,1640.38,6.72345,3534.31,113.55,0)
	spawnMobile("tatooine", "kreetle",300,1633.38,7.78232,3539.31,188.235,0)
	spawnMobile("tatooine", "kreetle",300,1632.38,7.78197,3533.31,310.834,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1139.8,20.1201,3348.82,254.094,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1271.46,7.96205,3555.45,300.241,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1261.56,9.10267,3566,4.12381,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1269.92,8.62089,3562.04,270.234,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1473.29,10.0509,3556.92,34.6749,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1557.92,10.1478,3573.36,113.494,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1557.47,10.275,3569.88,199.46,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1559.86,9.25833,3579.77,214.211,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1554.99,6.26101,2910.7,118.92,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1567.09,6.83359,2921.88,61.2095,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1550.6,7.00186,2902.02,180.965,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1553.41,6.45934,2915.5,11.0788,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1687.02,12,3449.08,52.251,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1852.49,9.74789,2961.32,296.304,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1732.5,9.60921,3291.65,285.18,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1634.85,6.91877,3545.88,331.39,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1125.68,14.2323,3250.64,171.121,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1133.35,12.6027,3255.11,14.7352,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1118.72,14.0502,3239.14,181.525,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1124.25,13.5159,3243.92,147.703,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1085.13,6.61378,3185.82,85.7157,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,1106.19,5.94117,3187.6,354.975,0)
	spawnMobile("tatooine", "minor_worrt",300,1048.15,6.78693,3034.72,125.497,0)
	spawnMobile("tatooine", "minor_worrt",300,1052.19,6.63745,3042.47,49.4436,0)
	spawnMobile("tatooine", "minor_worrt",300,1145.96,28.8096,3450.07,184.995,0)
	spawnMobile("tatooine", "minor_worrt",300,1157.53,26.9318,3453.41,96.5022,0)
	spawnMobile("tatooine", "minor_worrt",300,1154.25,27.7183,3452.09,16.8607,0)
	spawnMobile("tatooine", "minor_worrt",300,1143.38,28.7819,3451.71,240.425,0)
	spawnMobile("tatooine", "minor_worrt",300,1134.66,22.3091,3354.39,53.2405,0)
	spawnMobile("tatooine", "minor_worrt",300,1130.02,22.1785,3341.24,255.212,0)
	spawnMobile("tatooine", "minor_worrt",300,1129.37,23.2358,3348.93,241.138,0)
	spawnMobile("tatooine", "minor_worrt",300,1373.72,22.8537,2912.15,277.837,0)
	spawnMobile("tatooine", "minor_worrt",300,1338.17,14.6409,2847.72,268.243,0)
	spawnMobile("tatooine", "minor_worrt",300,1376.97,7.32279,3555.79,227.135,0)
	spawnMobile("tatooine", "minor_worrt",300,1385.64,9.7947,3570.08,330.128,0)
	spawnMobile("tatooine", "minor_worrt",300,1470.89,9.14934,3551.91,42.0099,0)
	spawnMobile("tatooine", "minor_worrt",300,1713.52,9.79311,2825.23,95.6858,0)
	spawnMobile("tatooine", "minor_worrt",300,1553.18,6.46393,2915.57,3.89496,0)
	spawnMobile("tatooine", "minor_worrt",300,1557.59,6.25528,2908.24,200.587,0)
	spawnMobile("tatooine", "minor_worrt",300,1557.88,6.25405,2908.11,240.618,0)
	spawnMobile("tatooine", "minor_worrt",300,1689.02,12,3443.08,123.862,0)
	spawnMobile("tatooine", "minor_worrt",300,1687.02,12,3453.08,307.365,0)
	spawnMobile("tatooine", "minor_worrt",300,1685.02,12,3445.08,155.332,0)
	spawnMobile("tatooine", "minor_worrt",300,1746.96,10.0292,3284.7,128.519,0)
	spawnMobile("tatooine", "minor_worrt",300,1732.79,8.12792,3282.87,311.169,0)
	spawnMobile("tatooine", "minor_worrt",300,1724.92,7.1876,3273.25,253.983,0)
	spawnMobile("tatooine", "minor_worrt",300,1790.19,6.66465,2878.26,122.144,0)
	spawnMobile("tatooine", "minor_worrt",300,1789.47,7.95745,2890.23,34.2376,0)
	spawnMobile("tatooine", "minor_worrt",300,1805.9,6.94296,2871.32,98.6297,0)
	spawnMobile("tatooine", "minor_worrt",300,1828.47,6.59728,3244.79,322.076,0)
	spawnMobile("tatooine", "minor_worrt",300,1905.32,13.964,3081.04,129.902,0)
	spawnMobile("tatooine", "minor_worrt",300,1642.28,6.52379,3539.28,167.494,0)
	spawnMobile("tatooine", "minor_worrt",300,1339.88,14.8086,2842.88,87.1593,0)
	spawnMobile("tatooine", "minor_worrt",300,1140.5,10.3186,3249.19,94.1046,0)
	spawnMobile("tatooine", "minor_worrt",300,1123.3,14.8199,3250.77,279.351,0)
	spawnMobile("tatooine", "minor_worrt",300,1102.27,6.44548,3176.54,137.826,0)
	spawnMobile("tatooine", "minor_worrt",300,1088.37,6.60356,3183.72,327.561,0)
	spawnMobile("tatooine", "minor_worrt",300,1098.21,5.87219,3173.21,96.5256,0)
	spawnMobile("tatooine", "minor_worrt",300,1091.44,6.54552,3179.32,157.227,0)
	spawnMobile("tatooine", "minor_worrt",300,1047.59,6.90768,2963.04,151.58,0)
	spawnMobile("tatooine", "minor_worrt",300,1051.27,7.32262,2957.95,101.837,0)
	spawnMobile("tatooine", "minor_worrt",300,1045.6,6.79503,2962.48,253.676,0)
	spawnMobile("tatooine", "minor_worrt",300,1051.24,7.32455,2952.14,193.218,0)
	spawnMobile("tatooine", "minor_worrt",300,1184.51,6.74202,2871.48,304.186,0)
	spawnMobile("tatooine", "minor_worrt",300,1184.37,7.08161,2862.06,17.9303,0)
	spawnMobile("tatooine", "minor_worrt",300,1283.68,8.62574,2821.26,92.7292,0)
	spawnMobile("tatooine", "minor_worrt",300,1270.85,9.85368,2833.03,291.059,0)
	spawnMobile("tatooine", "minor_worrt",300,1640.27,6.57107,3539.44,346.945,0)
	spawnMobile("tatooine", "minor_worrt",300,1629.38,7.68618,3532.31,220.917,0)
	spawnMobile("tatooine", "mound_mite",300,1140.86,29.1388,3450.07,288.43,0)
	spawnMobile("tatooine", "mound_mite",300,1484.61,8.0894,3544.36,86.2885,0)
	spawnMobile("tatooine", "mound_mite",300,1698.56,9.80305,2823.97,335.034,0)
	spawnMobile("tatooine", "mound_mite",300,1563.08,8.26132,3583.36,24.8338,0)
	spawnMobile("tatooine", "mound_mite",300,1866.41,9.04205,2967.88,348.823,0)
	spawnMobile("tatooine", "mound_mite",300,1733.21,10.3787,2815.08,334.377,0)
	spawnMobile("tatooine", "mound_mite",300,1744.69,10.1734,2821.79,25.7853,0)
	spawnMobile("tatooine", "mound_mite",300,1124.01,13.4652,3243.27,293.084,0)
	spawnMobile("tatooine", "rill",300,1045.36,7.44404,3043.26,353.239,0)
	spawnMobile("tatooine", "rill",300,1047.33,7.22971,3046.76,216.586,0)
	spawnMobile("tatooine", "rill",300,1104.74,7.2345,2905.93,169.245,0)
	spawnMobile("tatooine", "rill",300,1139.62,29.4759,3443.99,213.674,0)
	spawnMobile("tatooine", "rill",300,1141.26,20.2478,3353.73,240.207,0)
	spawnMobile("tatooine", "rill",300,1261.2,9.14893,3567.29,163.425,0)
	spawnMobile("tatooine", "rill",300,1256.35,8.99928,3577.67,279.633,0)
	spawnMobile("tatooine", "rill",300,1372.52,7.29019,3556.73,318.067,0)
	spawnMobile("tatooine", "rill",300,1472.13,7,3537.17,112.684,0)
	spawnMobile("tatooine", "rill",300,1709.58,10.3179,2835.96,56.1244,0)
	spawnMobile("tatooine", "rill",300,1692.84,9.48024,2820.93,205.281,0)
	spawnMobile("tatooine", "rill",300,1562.12,9.0806,3579.43,38.7698,0)
	spawnMobile("tatooine", "rill",300,1558.79,7.75791,3583.97,303.77,0)
	spawnMobile("tatooine", "rill",300,1551.49,6.59957,2905.19,89.1702,0)
	spawnMobile("tatooine", "rill",300,1689.02,12,3444.08,234.952,0)
	spawnMobile("tatooine", "rill",300,1688.02,12,3442.08,7.2531,0)
	spawnMobile("tatooine", "rill",300,1870.24,9.20984,2966.54,107.762,0)
	spawnMobile("tatooine", "rill",300,1865.24,9.40373,2963.71,239.536,0)
	spawnMobile("tatooine", "rill",300,1743.22,7.82701,3265.36,183.529,0)
	spawnMobile("tatooine", "rill",300,1806.8,6.9809,2878.03,114.829,0)
	spawnMobile("tatooine", "rill",300,1784.51,7.62439,2885.12,294.467,0)
	spawnMobile("tatooine", "rill",300,1825.88,6.71469,3234.62,115.337,0)
	spawnMobile("tatooine", "rill",300,1824.45,6.63692,3238.38,149.541,0)
	spawnMobile("tatooine", "rill",300,1892.9,11.1802,3073.04,282.24,0)
	spawnMobile("tatooine", "rill",300,1119.93,15.3748,3249.16,141.279,0)
	spawnMobile("tatooine", "rill",300,1099.96,6.30891,3178.3,319.459,0)
	spawnMobile("tatooine", "rill",300,1063.48,8.35093,2954.38,22.9979,0)
	spawnMobile("tatooine", "rill",300,1057.78,7.45382,2963.84,323.174,0)
	spawnMobile("tatooine", "rill",300,1266.2,9.90717,2833.11,166.168,0)
	spawnMobile("tatooine", "rill",300,1194.97,7.15298,2848.67,61.3119,0)
	spawnMobile("tatooine", "rill",300,1261.62,9.82242,2831.13,304.142,0)
	spawnMobile("tatooine", "rockmite",300,1062.18,5.83524,3043.72,141.396,0)
	spawnMobile("tatooine", "rockmite",300,1181.18,9.76559,3555.94,245.342,0)
	spawnMobile("tatooine", "rockmite",300,1137.85,20.6419,3348.3,237.883,0)
	spawnMobile("tatooine", "rockmite",300,1438.47,15.7136,3604.36,128.279,0)
	spawnMobile("tatooine", "rockmite",300,1438.96,15.6977,3606.76,42.672,0)
	spawnMobile("tatooine", "rockmite",300,1376.56,6.93198,3548.19,266.629,0)
	spawnMobile("tatooine", "rockmite",300,1691.38,9.48584,2821.22,288.939,0)
	spawnMobile("tatooine", "rockmite",300,1552.99,10.3713,3574.25,306.608,0)
	spawnMobile("tatooine", "rockmite",300,1783.82,7.5651,2884.2,302.472,0)
	spawnMobile("tatooine", "rockmite",300,1819.31,6.57781,3240.37,109.61,0)
	spawnMobile("tatooine", "rockmite",300,1900.72,13.3004,3090.22,79.8598,0)
	spawnMobile("tatooine", "rockmite",300,1936.08,17.7986,3155.67,199.281,0)
	spawnMobile("tatooine", "rockmite",300,1098.6,6.37556,3180.33,37.4932,0)
	spawnMobile("tatooine", "rockmite",300,1088.19,7.39655,2905.09,2.99875,0)
	spawnMobile("tatooine", "rockmite",300,1098.67,7.61899,2907.07,122.347,0)
	spawnMobile("tatooine", "rockmite",300,1179.82,7.11622,2846.43,240.292,0)
	spawnMobile("tatooine", "rockmite",300,1274.94,9.5564,2826.91,283.549,0)
	spawnMobile("tatooine", "rockmite",300,1647.38,6.74919,3521.31,261.582,0)
	spawnMobile("tatooine", "womp_rat",300,1463.72,7,3527.25,202.052,0)
	spawnMobile("tatooine", "womp_rat",300,1486.47,8.07983,3544.04,2.8748,0)
	spawnMobile("tatooine", "womp_rat",300,1694.12,12,3445.83,88.1426,0)
	spawnMobile("tatooine", "womp_rat",300,1781.88,7.42814,2883.16,283.473,0)
	spawnMobile("tatooine", "womp_rat",300,1127.41,14.7718,3256.49,107.418,0)
	spawnMobile("tatooine", "womp_rat",300,1113.96,17.4101,3253.68,287.934,0)
	spawnMobile("tatooine", "worrt",300,1093.85,7.54313,2905.09,271.13,0)
	spawnMobile("tatooine", "worrt",300,1178.92,11.1815,3550.03,74.6936,0)
	spawnMobile("tatooine", "worrt",300,1177.47,10.4286,3561.08,352.574,0)
	spawnMobile("tatooine", "worrt",300,1142.64,19.2634,3347.08,281.135,0)
	spawnMobile("tatooine", "worrt",300,1136.69,21.8977,3355.96,89.2927,0)
	spawnMobile("tatooine", "worrt",300,1414.39,19.1584,3614.59,114.722,0)
	spawnMobile("tatooine", "worrt",300,1416.84,19.1847,3617.66,238.477,0)
	spawnMobile("tatooine", "worrt",300,1739.93,8.81984,3281.18,233.807,0)
	spawnMobile("tatooine", "worrt",300,1800.05,6.80464,2891.47,39.5455,0)
	spawnMobile("tatooine", "worrt",300,1844.89,6.26424,3232.27,46.7083,0)
	spawnMobile("tatooine", "worrt",300,1827.19,6.58123,3242.88,237.129,0)
	spawnMobile("tatooine", "worrt",300,1742.08,10.3631,2819.34,314.877,0)
	spawnMobile("tatooine", "worrt",300,1763.95,10.0345,2821.82,1.54764,0)
	spawnMobile("tatooine", "worrt",300,1930.25,16.8951,3152.15,175.678,0)
	spawnMobile("tatooine", "worrt",300,1113.08,18.0283,3257.68,318.548,0)
	spawnMobile("tatooine", "worrt",300,1191.12,7.30368,2862.36,37.9791,0)
	spawnMobile("tatooine", "worrt",300,1179.97,6.94709,2862.22,304.96,0)
end
