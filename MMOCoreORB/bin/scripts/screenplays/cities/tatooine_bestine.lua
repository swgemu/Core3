TatooineBestineScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineBestineScreenPlay",

	planet = "tatooine",

	gcwMobs = {
		-- Imperial Mini Base -1136 -3901
		{"imperial_sergeant", -2.3, 0, -3.9, 13, 1279924, "npc_imperial"},
		{"imperial_first_lieutenant", 3.0, 0.1, 0.5, 164, 1279924, "npc_imperial"},
		{"imperial_recruiter", -1138, 98, -3897, 0, 0, "npc_imperial"},
		-- Imperial Npc's Outside
		{"command_security_guard", -1278.5, 12.5279, -3643.1, 165.005, 0, "", true},
		{"command_security_guard", -1243.9, 12, -3550.55, 301.01, 0, "", true},
		{"command_security_guard", -1277.1, 12, -3533.8, 301.01, 0, "", true},
		{"command_security_guard", -1150.5, 12, -3547.1, 26, 0, "", true},
		{"command_security_guard", -1097, 12, -3525.3, 121.004, 0, ""},
		{"dark_trooper", -1430.36, 12, -3728.58, 141.26, 0, "npc_imperial"},
		{"dark_trooper", -1004.6, 12, -3710.8, 132, 0, "npc_imperial", true},
		{"dark_trooper", -1428.52, 12, -3730.88, 141.264, 0, "npc_imperial"},
		{"dark_trooper", -1453, 12, -3646.95, 42.076, 0, "", true},
		{"dark_trooper", -1002.9, 12, -3705.4, -55, 0, "npc_imperial", true},
		{"elite_sand_trooper", -1284, 12, -3486, 180, 0, ""},
		{"elite_sand_trooper", -1368.48, 12, -3725.42, 268.991, 0, "npc_imperial"},
		{"elite_sand_trooper", -1276, 12, -3487, 180, 0, ""},
		{"elite_sand_trooper", -1348.2, 12, -3712.7, 315, 0, "npc_imperial"},
		{"elite_sand_trooper", -1429.92, 12, -3731.49, 141.268, 0, "npc_imperial", true},
		{"elite_sand_trooper", -1275, 12, -3507.5, 315, 0, "", true},
		{"elite_sand_trooper", -1378.4, 12, -3712.53, 119.74, 0, "npc_imperial", true},
		{"elite_sand_trooper", -984.262, 12, -3742.5, 126.391, 0, "npc_imperial", true},
		{"elite_sand_trooper", -1454.87, 12, -3651.05, 45.2754, 0, ""},
		{"elite_sand_trooper", -1455.96, 12, -3650.25, 42.1254, 0, ""},
		{"elite_sand_trooper", -1058.39, 12, -3671.09, 222.747, 0, "npc_imperial", true},
		{"elite_sand_trooper", -1049.04, 12, -3660.19, 249.5, 0, "npc_imperial"},
		{"sand_trooper", -983.8, 12, -3746.5, 116.003, 0, ""},
		{"sand_trooper", -980.4, 12, -3742.8, 119, 0, ""},
		{"sand_trooper", -1169.8, 12, -3692.1, 235.007, 0, ""},
		{"sand_trooper", -1283.8, 12, -3480.4, 306.486, 0, "", true},
		{"sand_trooper", -1275.6, 12, -3479.9, 0, 0, ""},
		{"sand_trooper", -1016.9, 12, -3741.2, 97.0029, 0, "", true},
		{"sand_trooper", -1018.3, 12, -3736.2, 272.008, 0, ""},
		{"sand_trooper", -1089.8, 12, -3704.2, 116.003, 0, "", true},
		{"sand_trooper", -1154.1, 12, -3650, -111, 0, "", true},
		-- Guards near city hall and shuttleport entryway
		{"sand_trooper", -1083.6, 12, -3594.2, 169.005, 0, "", true},
		{"sand_trooper", -1092.1, 12, -3595.4, 169.005, 0, ""},
		-- Guards by guildhall exits
		{"sand_trooper", -1181.3, 12, -3537.9, 198.006, 0, ""},
		{"sand_trooper", -1181.3, 12, -3542.5, 198.006, 0, "", true},
		{"storm_commando", -1231.81, 12, -3605.85, 127.312, 0, ""},
		{"storm_commando", -1292.8, 12, -3585.5, 133.004, 0, ""},
		{"stormtrooper_sniper", -1093.7, 14, -3660.2, 41.0012, 0, ""},
		-- In front of city hall
		{"elite_sand_trooper", -1093.52, 12, -3647.32, 308.036, 0, "npc_imperial"},
		-- Black stormtrooper by hutt informant
		{"storm_commando", -1115.14, 12, -3639.18, 263.058, 0, "npc_imperial", true},
	},

	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_tatooine_patrol", "commoner_technician_patrol", "explorer_patrol", "gambler_patrol", "noble_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"cll8_1", "cll8_binary_load_lifter", -1402, 9, -3756, 140, 0, "", false},
		{"r2_1", "r2", -15.8, 1.0, 1.5, 93, 1223851, "", false},
		{"r3_1", "r3", -3.4, -4.0, -4.8, 128, 1528401, "", false},
		{"r4_1", "r4", -1068, 12, -3600, -145, 0, "", false},

		--NPCs
		{"npc_1", "patrolNpc", -1291, 12, -3618, 244, 0, "", false},
		{"npc_2", "patrolNpc", -1283, 12,- 3559, 341, 0, "", false},
		{"npc_3", "patrolNpc", -1311, 12, -3674, 26, 0, "", false},
		{"npc_4", "patrolNpc", -1320, 12, -3633, 186, 0, "", false},
		{"npc_5", "patrolNpc", -1216, 12, -3549, 41, 0, "", false},
		{"npc_6", "patrolNpc", -1077, 12, -3513, 10, 0, "", false},
		{"npc_7", "patrolNpc", -1047, 12, -3665, 279, 0, "", false},
		{"npc_8", "patrolNpc", -1026, 12, -3725, 331, 0, "", false},
		{"npc_9", "patrolNpc", -1068, 12, -3690, 281, 0, "", false},
		{"npc_10", "patrolNpc", -1076, 12, -3657, 310, 0, "", false},
		{"npc_11", "patrolNpc", -1200, 12, -3631, 28, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		cll8_1 = {{-1402, 9, -3756, 0, false}, {-1398, 9.8, -3749, 0, false}, {-1385.2, 10, -3734.9, 0, true}, {-1394, 12, -3721, 0, false}, {-1385, 10, -3734.9, 0, false}, {-1398, 9, -3749, 0, false}},
		r2_1 = {{-15.8, 1.0, 1.5, 1223851, false}, {-15.9, 1.0, -9.3, 1223852, false}, {-11.6, 1.0, 5.1, 1223851, false}, {0.8, 1.0, 6.8, 1223849, false}, {7.1, 1.0, 0.7, 1223849, false}, {0.8, 1.0, 6.8, 1223849, false}},
		r3_1 = {{-3.4, -4.0, -4.8, 1528401, false}, {-4.1, -4.0, -9.7, 1528401, false}, {-0.6, -4.0, -6.9, 1528401, true}, {-0.6, -4.0, 0.6, 1528401, false}},
		r4_1 = {{-1068, 12, -3600, 0, false}, {-1074.7, 12, -3608.6, 0, true}, {-1035.7, 12, -3643.1, 0, false}, {-1074.7, 12, -3608.6, 0, false}, {-1086.9, 12, -3600.3, 0, true}, {-1089.4, 12, -3585.6, 0, false}, {-1086.9, 12, -3600.3, 0, false}},

		npc_1 = {{-1291, 12, -3618, 0, true}, {-1302, 12, -3632, 0, true}, {-1278, 12, -3623, 0, true}, {-1267, 12, -3614, 0, true}, {-1259, 12, -3622, 0, true}},
		npc_2 = {{-1283, 12,- 3559, 0, true}, {-1278, 12, -3605, 0, true}, {-1285, 12, -3540, 0, true}},
		npc_3 = {{-1311, 12, -3674, 0, true}, {-1318, 12, -3660, 0, true}, {-1337, 12, -3666, 0, true}, {-1323, 12, -3681, 0, true}},
		npc_4 = {{-1320, 12, -3633, 0, true}, {-1331, 12, -3652, 0, true}, {-1315, 12, -3652, 0, true}, {-1312, 12, -3625, 0, true}},
		npc_5 = {{ -1216, 12, -3549, 0, true}, {-1198, 12, -3548, 0, true}, {-1221, 12, -3540, 0, true}, {-1203, 12, -3554, 0, true}, {-1209, 12, -3566, 0, true}},
		npc_6 = {{-1077, 12, -3513, 0, true}, {-1096, 12, -3548, 0, true}, {-1100, 12, -3566, 0, true}, {-1100, 12, -3535, 0, true}},
		npc_7 = {{-1047, 12, -3665, 0, true}, {-1024, 12, -3682, 0, true}, {-1013, 12, -3701, 0, true}, {-1028, 12, -3687, 0, true}},
		npc_8 = {{-1026, 12, -3725, 0, true}, {-1048, 12, -3713, 0, true}, {-1042, 12, -3709, 0, true}, {-1024, 12, -3734, 0, true}},
		npc_9 = {{-1068, 12, -3690, 0, true}, {-1055, 12, -3695, 0, true}, {-1070, 12, -3680, 0, true}, {-1054, 12, -3711, 0, true}},
		npc_10 = {{-1076, 12, -3657, 0, true}, {-1088, 12, -3650, 0, true}, {-1078, 12, -3645, 0, true}, {-1072, 12, -3651, 0, true}, {-1099, 12, -3633, 0, true}},
		npc_11 = {{-1200, 12, -3631, 0, true}, {-1227, 12, -3627, 0, true}, {-1216, 12, -3630, 0, true}, {-1231, 12, -3647, 0, true}, {-1213, 12, -3627, 0, true}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old", "commoner_tatooine"},
	stationaryNpcs = {"artisan", "bodyguard", "bothan_diplomat", "bounty_hunter", "businessman", "commoner_technician", "contractor", "criminal", "entertainer", "explorer", "farmer", "farmer_rancher", "fringer",
			"gambler", "info_broker", "medic", "mercenary", "miner", "noble", "official", "pilot", "rancher", "scavenger", "scientist", "slicer"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, -1268.02, 12, -3531.37, 119, 0, ""}, {1, -987.119, 12, -3729.33, 40, 0, ""}, {1, -1145.13, 12, -3507.53, 221, 0, ""}, {1, -1358.9, 12, -3504.1, 76, 0, ""},
		{1, -1066.46, 12, -3668.09, 306, 0, ""}, {1, -1162.65, 12, -3646.5, 113, 0, ""}, {1, -1464.81, 12, -3561.05, 198, 0, ""}, {1, -1142.23, 12, -3672.51, 283, 0, ""},
		{1, -1080.55, 12, -3696.41, 132, 0, ""}, {1, -1157.39, 12, -3666.66, 339, 0, ""}, {1, -1429, 12, -3628.03, 236, 0, ""}, {1, -1404.76, 12, -3636.5, 34, 0, ""},
		{1, -1033.88, 12, -3644.68, 209, 0, ""}, {1, -1010.28, 12, -3728.59, 85, 0, ""}, {1, -1257.34, 12, -3539.31, 207, 0, ""}, {1, -983.47, 10, -3538.5, 142, 0, ""},
		{1, -1250.18, 12, -3545.35, 279, 0, ""}, {1, -1023.25, 12, -3746.26, 261, 0, ""}, {1, -1093.32, 12, -3509.11,  63, 0, ""}, {1, -1099.89, 12, -3506.87, -175, 0, ""},
		{1, -1271.82, 12, -3601.08, 5, 0, ""}, {1, -1012.31, 12, -3748.5, 10, 0, ""}
	},

	mobiles = {
		--Cantina
		{"bartender",60,-11.1901,-0.894992,1.50145,33.4278,1028647, ""},

		--starport interior
		{"trainer_shipwright",60,-3.2,0.6,67.9,144,1026828, "neutral"},
		{"chassis_dealer",60,5.2,0.6,79.0,-70,1026825, "neutral"},

		--Med Center
		{"trainer_medic",0,-8.7,0.2,0.1,91,4005383, ""},

		--Guild Hall -1239 -3580
		{"trainer_scout", 0, -11.6, 1.1, 4.6, 174, 1028550, ""},
		{"brawler",300,-14.01,1.13306,-8.53,120.004,1028553, ""},
		{"trainer_brawler",0,-11,1.1,-14,0,1028553, ""},
		{"trainer_marksman",0,0,1.13306,-13,0,1028552, ""},
		{"businessman",60,3.32,1.13306,-8.49,228.007,1028552, ""},
		{"junk_dealer", 0, -14.5, 1.1, 2.8, 111, 1028550, ""},

		--Guild Hall -1241 -3524
		{"trainer_architect",0,11,1.133,-14.5,0,1028581, ""},
		{"trainer_armorsmith",0,-12.8138,1.13306,3.64955,176,1028580, ""},
		{"trainer_droidengineer",0,-11.6346,1.13306,-13.252,2,1028583, ""},
		{"trainer_weaponsmith",0,-3,1.13306,-8.3,91,1028582, ""},
		{"trainer_merchant",0,12,1.13306,6,180,1028579, ""},

		--Guild Hall -1187 -3515
		{"contractor",60,-3.69,1.13306,-6,11.0003,1028558, ""},
		{"trainer_artisan",0,-0.0507306,1.13306,-13.747,0,1028562, ""},
		{"mercenary",300,3.29,1.13306,-9.58,249.007,1028562, ""},

		--Guild Hall -1130 -3540
		{"akal_colzet",60,0.436469,1.75,-14.4381,0,1212359, "npc_imperial"},

		--Guild Hall -1093 -3660
		{"businessman",60,-10.4,1.0,9.2,174,1028169, "sad"},
		{"bounty_hunter",300,-10.2,1.0,7.1,-7,1028169, "npc_accusing"},

		--east Tavern -1074 -3640
		{"commoner_technician",300,4.6,1.0,7.5,90,1528396, "npc_use_terminal_high"},
		{"chiss_female",60,10.2,0.4,-4.5,0,1528397, "npc_angry"},
		{"chiss_male",60,10.3,0.4,-5.6,90,1528397, "sad"},
		{"patron_ithorian",60,1.6,0.4,-6.0,90,1528397, "npc_sitting_ground"},
		{"entertainer",60,3.8,0.4,-6.0,-90,1528397, "npc_sitting_ground"},
		{"commoner",60,2.0,0.4,-2.6,165,1528397, "entertained"},
		{"rancher",60,4.1,0.4,-2.7,-173,1528397, "happy"},
		{"commoner_old",60,6.4,0.4,-2.9,-132,1528397, "npc_sitting_chair"},
		{"commoner_naboo",60,-0.6,0.4,-2.8,134,1528397, "npc_sitting_chair"},
		{"ishitib_male",60,3.0,0.4,-9.3,0,1528397, "npc_sitting_chair"},
		{"commoner_fat",60,-9.4,1.0,9.3,-80,1528398, "npc_standing_drinking"},
		{"mercenary",300,-10.6,0.4,-2.3,90,1528397, "threaten"},
		{"mercenary",300,-10.7,-1.4,-10.4,44,1528400, "threaten"},
		{"mercenary",300,0.2,-4.0,-10.4,-47,1528401, "threaten"},
		{"mercenary",300,-11.2,-9.5,1.8,135,1528404, "threaten"},
		{"seeker",240,-1.0,-9.5,1.8,-123,1528404, ""},
		{"twilek_slave",60,-1.9,-9.5,-2.4,130,1528407, "nervous"},
		{"devaronian_male",60,-0.4,-9.5,-3.9,-44,1528407, "accusing"},
		{"mercenary",300,-0.5,-9.5,-2.4,-90,1528407, "threaten"},
		{"mercenary",300,-1.9,-9.5,-3.6,-16,1528407, "threaten"},
		{"probot",60,2.7,-9.5,1.1,-100,1528407, ""},

		--Tavern -1009 -3544
		{"noble",60,-3.6,0.4,-0.2,209,1028491, "npc_sitting_chair"},
		{"contractor",300,-1.05454,0.408271,-5.70312,360.011,1028491, "conversation"},
		{"info_broker",60,-1.05454,0.408271,-4.40312,180.006,1028491, "conversation"},
		{"trainer_chef",0,-9.4,1.0,7.1,85,1028492, ""},

		--Hotel
		{"crix_yarrow",60,7.39833,1.00001,-7.63485,360.011,1223849, "calm"},
		{"scientist",300,-2.76865,0.999996,-0.495484,180.008,1223849, "conversation"},
		{"medic",300,-2.76865,0.999998,-1.49548,0,1223849, "conversation"},
		{"freelance_pilot",60,1.36242,0.999987,4.17823,16.6163,1223849, "neutral"},
		{"commoner_tatooine",60,-14.8302,1.00067,0.571647,270.007,1223851, "conversation"},
		{"commoner_tatooine",60,-16.8302,1.00087,0.571647,90.0019,1223851, "conversation"},
		{"farmer",60,20.4356,1.28309,-1.59068,180.009,1223850, "conversation"},
		{"gil_burtin",60,20.5073,1.56616,12.9718,218.196,1223850, "neutral"},
		{"info_broker",60,20.4356,1.28309,-2.59068,0,1223850, "conversation"},
		{"trainer_chef",0,24,1.3,7,217,1223850, ""},
		{"ty_vila",60,15.3218,1.28309,9.00139,113.449,1223850, "neutral"},

		--Capitol
		{"oberhaur",60,-21.8614,3.22324,26.9177,183.918,926480, "npc_imperial"},
		{"rancher",60,-2.63337,0.3,2.46637,180.004,926475, "conversation"},
		{"arosp_eslykewa",60,-22.8506,1.29946,6.24726,180.009,926475, "conversation"},
		{"info_broker",60,-22.8506,1.2998,5.24726,360.011,926475, "conversation"},
		{"comm_operator",60,7.4,0.3,-0.7,-81,926475, "npc_imperial"},
		{"medic",60,-2.63337,0.3,1.46637,0,926475, "conversation"},
		{"noble",60,18.4,1.3,5.2,80,926475, "npc_accusing"},
		{"businessman",60,19.5,1.3,5.2,236,926475, "angry"},

		--Outside
		{"junk_dealer", 0, -1026.22, 10, -3559.1, 8, 0, ""},
		{"junk_dealer", 0, -1392, 18, -3847.9, 8, 0, ""},
		{"informant_npc_lvl_1",0,-1449,12,-3558,270,0, ""},
		{"informant_npc_lvl_1",0,-1450,12,-3566,270,0, ""},
		{"informant_npc_lvl_1",0,-1332,12,-3700,0,0, ""},
		{"informant_npc_lvl_1",0,-1053,12,-3726,90,0, ""},
		{"informant_npc_lvl_1",0,-1023,12,-3677,225,0, ""},
		{"informant_npc_lvl_1",0,-1220,12,-3560,45,0, ""},
		{"gert_talnin",60,-1287.3,12,-3587.16,169.676,0, ""},
		{"gunham",60,-1125.07,12.1959,-3622.83,83.2544,0, ""},
		{"sol_windtide",60,-1203.12,12,-3612.74,236.494,0, ""},
		{"trainer_architect",0,-1255,12,-3567,-47,0, ""},
		{"trainer_artisan",0,-1266,12,-3559,227,0, ""},
		{"trainer_bioengineer",0,-1444.06,10,-3749.08,90,0, ""},
		{"trainer_brawler",0,-1278.75,12,-3540.47,79,0, ""},
		{"trainer_chef",0,-1216,12,-3601,153,0, ""},
		{"trainer_entertainer",0,-1273.4,12,-3629.5,-42,0, ""},
		{"trainer_marksman",0,-1272,12,-3538,180,0, ""},
		{"trainer_politician",0,-1125,12.2,-3616,130,0, ""},
		{"trainer_scout",0,-1295.83,12,-3563.27,51,0, ""},
		{"trainer_squadleader",0,-1019,10,-3532,180,0, ""},
		{"trainer_tailor",0,-1348,12,-3677,180,0, ""},
		{"valarian_swooper_leader",300,-1158.7,12,-3661.7,270,0, ""},
		{"valarian_swooper_leader",300,-1161,12,-3662,90,0, ""},
		{"valarian_swooper_leader",300,-1161.6,12,-3647.1,-61,0, ""},
		{"wlinc_tchrr",60,-1288.15,12,-3588.42,276.296,0, "neutral"},

		{"imperial_recruiter",60,-1072.7,12,-3594,220,0, ""},
		{"imperial_recruiter",60,-1275.75,12,-3594.28,-73,0, ""}
	}
}

registerScreenPlay("TatooineBestineScreenPlay", true)

function TatooineBestineScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
		self:spawnSceneObjects()
		self:spawnGcwMobiles()
	end
end

function TatooineBestineScreenPlay:spawnSceneObjects()
	--outside starport
	spawnSceneObject(self.planet, "object/tangible/crafting/station/public_space_station.iff", -1306.04, 12, -3616.23, 0, math.rad(130) )

	--east Tavern
	spawnSceneObject(self.planet, "object/tangible/furniture/decorative/basket_closed.iff", -2.9, 0.4, -5.9, 1528397, math.rad(-90) )
	spawnSceneObject(self.planet, "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", -0.7, -4.0, 1.7, 1528401, math.rad(0) )
end

function TatooineBestineScreenPlay:spawnMobiles()
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

	local pNpc = spawnMobile(self.planet, "junk_dealer", 0, -1136.25, 12, -3683.56, 40, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerArmsConvoTemplate")
	end
	pNpc = spawnMobile(self.planet, "junk_dealer", 0, -1117.39, 12, -3686.64, -144, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerFineryConvoTemplate")
	end

	--Creatures
	--[[
	spawnMobile(self.planet, "lesser_desert_womp_rat",300,-1062.1,23.7,-3451.8,-110,0)
	spawnMobile(self.planet, "lesser_desert_womp_rat",300,-1068.2,23.2,-3452.5,98,0)
	spawnMobile(self.planet, "lesser_desert_womp_rat",300,-1064.3,22.7,-3455.2,27,0)
	spawnMobile(self.planet, "lesser_desert_womp_rat",300,-1057.7,23.8,-3452.7,-92,0)

	spawnMobile(self.planet, "minor_worrt",300,-927.86,27.7005,-3784.58,229.599,0)
	spawnMobile(self.planet, "minor_worrt",300,-922.653,26.6572,-3778.35,225.778,0)
	spawnMobile(self.planet, "minor_worrt",300,-923.222,25.6505,-3774.92,187.309,0)
	spawnMobile(self.planet, "minor_worrt",300,-910.093,26.277,-3783.93,117.558,0)
	spawnMobile(self.planet, "minor_worrt",300,-913.601,27.1392,-3784.15,69.6335,0)
	spawnMobile(self.planet, "minor_worrt",300,-912.848,25.8267,-3794.42,276.507,0)
	spawnMobile(self.planet, "worrt",300,-930.225,29.785,-3796.81,106.152,0)
	spawnMobile(self.planet, "worrt",300,-939.612,24.6046,-3781.1,308.507,0)

	spawnMobile(self.planet, "minor_worrt",300,-1150.79,22.8276,-3410.77,286.41,0)
	spawnMobile(self.planet, "minor_worrt",300,-1148.52,28.0683,-3402.47,295.148,0)
	spawnMobile(self.planet, "minor_worrt",300,-1158.11,29.9266,-3393.44,290.62,0)
	spawnMobile(self.planet, "minor_worrt",300,-1152.38,31.805,-3390,28.2254,0)
	spawnMobile(self.planet, "minor_worrt",300,-1144.7,30.4,-3395.4,-121,0)
	spawnMobile(self.planet, "minor_worrt",300,-1158.7,26.2,-3403.5,68,0)

	spawnMobile(self.planet, "rill",300,-907.188,18.3242,-3573.35,360.011,0)
	spawnMobile(self.planet, "rill",300,-901.808,18.7395,-3570.88,360.011,0)
	spawnMobile(self.planet, "rill",300,-908.624,18.0014,-3571.89,0,0)
	spawnMobile(self.planet, "rill",300,-903.859,19.9334,-3579.55,0,0)
	spawnMobile(self.planet, "rockmite",300,-895.802,10.7364,-3546.49,145.129,0)
	spawnMobile(self.planet, "rockmite",300,-904.8,14.6023,-3552.38,322.681,0)

	spawnMobile(self.planet, "worrt",300,-1337.3,16.2,-3430.4,-152,0)
	spawnMobile(self.planet, "worrt",300,-1340.4,16,-3431.5,-152,0)
	spawnMobile(self.planet, "worrt",300,-1341.43,15.3175,-3434.23,284.1,0)
	spawnMobile(self.planet, "worrt",300,-1337.28,15.0418,-3434.8,360.011,0)
	]]
end
