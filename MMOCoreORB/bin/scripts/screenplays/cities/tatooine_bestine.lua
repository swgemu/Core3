TatooineBestineScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineBestineScreenPlay"
}

registerScreenPlay("TatooineBestineScreenPlay", true)

function TatooineBestineScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function TatooineBestineScreenPlay:spawnSceneObjects()

	--outside starport
	spawnSceneObject("tatooine", "object/tangible/crafting/station/public_space_station.iff", -1306.04, 12, -3616.23, 0, math.rad(130) )

end

function TatooineBestineScreenPlay:spawnMobiles()

	--Anything dashed out will need to be added here and removed from spawn manager once the spawnMobiles command is extended.

	--Cantina
	spawnMobile("tatooine", "bartender",60,-11.1901,-0.894992,1.50145,33.4278,1028647)
	--{"quajjifek_coge",60,32.2473,0.105,-7.74246,15.5057,1028646, "neutral", "Quajjif-Ek Coge"},

	--Med Center
	spawnMobile("tatooine", "trainer_medic",0,-8.7,0.2,0.1,91,4005383)
	--{"melious_purl",60,-1.28426,0.184067,0.712487,280.416,4005383, "npc_imperial", "Melious Purl"},

	--Guild Hall -1239 -3580
	--{"coa3_tactical_imperial",60,9.74537,1.13306,0.300803,93.0077,1028549, "npc_imperial", ""},
	spawnMobile("tatooine", "trainer_scout",0,-13,1.1,4.8,180,1028550)
	spawnMobile("tatooine", "hunter",300,-14.01,1.13306,-8.53,120.004,1028553)
	spawnMobile("tatooine", "trainer_brawler",0,-11,1.1,-14,0,1028553)
	spawnMobile("tatooine", "trainer_marksman",0,0,1.13306,-13,0,1028552)
	spawnMobile("tatooine", "businessman",60,3.32,1.13306,-8.49,228.007,1028552)

	--Guild Hall -1241 -3524
	spawnMobile("tatooine", "trainer_architect",0,11,1.133,-14.5,0,1028581)
	spawnMobile("tatooine", "trainer_armorsmith",0,-12.8138,1.13306,3.64955,176,1028580)
	spawnMobile("tatooine", "trainer_droidengineer",0,-11.6346,1.13306,-13.252,2,1028583)
	spawnMobile("tatooine", "trainer_weaponsmith",0,-3,1.13306,-8.3,91,1028582)
	spawnMobile("tatooine", "trainer_merchant",0,12,1.13306,6,180,1028579)

	--Guild Hall -1187 -3515
	spawnMobile("tatooine", "contractor",60,-3.69,1.13306,-6,11.0003,1028558)
	--{"oka_alewame",60,3.72152,1.13306,-4.85162,52.801,1028558, "neutral", "Oka Alewame"},
	spawnMobile("tatooine", "trainer_artisan",0,-0.0507306,1.13306,-13.747,0,1028562)
	spawnMobile("tatooine", "miner",60,3.29,1.13306,-9.58,249.007,1028562)
	--{"coa3_information_imperial",60,14.0299,1.13306,-8.82756,97.6176,1028561, "npc_imperial", ""},

	--Guild Hall -1130 -3540
	--{"akal_colzet",60,0.436469,1.75,-14.4381,0,1212359, "npc_imperial", ""},

	--Imperial Mini Base -1136 -3901
	--{"imperial_sergeant",400,-2.3,0,-3.9,13,1279924, "npc_use_terminal_high", ""},
	--{"imperial_first_lieutenant",400,3.9,0,0.5,180,1279922, "npc_sitting_table", ""},
	spawnMobile("tatooine", "imperial_recruiter",0,-1138,98,-3897,0,0)

	--Inside a House -1346 -3891
	--{"farious_gletch",60,1.7,-0.4,-5.5,315,1278989, "calm", "Farious Gletch"},

	--Tavern -1009 -3544
	--{"noble",60,-3.6,0.4,-0.2,209,1028491, "npc_sitting_chair", ""},
	--{"dim_u_priestess",300,-1.05454,0.408271,-5.70312,360.011,1028491, "conversation", ""}
	--{"bothan_information_broker",60,-1.05454,0.408271,-4.40312,180.006,1028491, "conversation", ""},

	--Hotel
	--{"crix_yarrow",60,7.39833,1.00001,-7.63485,360.011,1223849, "calm", "Crix Yarrow"},
	--{"darklighter_guard",300,-2.76865,0.999996,-0.495484,180.008,1223849, "conversation", ""},
	--{"dim_u_cleric",300,-2.76865,0.999998,-1.49548,0,1223849, "conversation", ""},
	--{"freelance_pilot",60,1.36242,0.999987,4.17823,16.6163,1223849, "neutral", ""},
	--{"r2",60,-15.8302,1.0008,1.57165,93.4669,1223851, "calm", "R2-U6"},
	--{"commoner_tatooine",60,-14.8302,1.00067,0.571647,270.007,1223851, "conversation", ""},
	--{"commoner_tatooine",60,-16.8302,1.00087,0.571647,90.0019,1223851, "conversation", ""},
	--{"commoner_old",60,-24,1.6,-4,343.038,1223855, "calm", "An Event Promoter"},
	--{"farmer",60,20.4356,1.28309,-1.59068,180.009,1223850, "conversation", ""},
	--{"gil_burtin",60,20.5073,1.56616,12.9718,218.196,1223850, "neutral", ""},
	--{"spacer",60,20.4356,1.28309,-2.59068,0,1223850, "conversation", ""},
	spawnMobile("tatooine", "trainer_chef",0,24,1.3,7,217,1223850)
	--{"ty_vila",60,15.3218,1.28309,9.00139,113.449,1223850, "neutral", ""},

	--Guild Hall -1093 -3660
	--{"businessman",60,0.697709,0.50772,-2.44977,360.011,1028169, "conversation", ""},
	--{"rodian_clan_warchief",300,0.697709,0.50772,-1.14977,180.009,1028169, "conversation", ""},
	--{"lilas_dinhint",60,22.6945,0.198179,-0.151074,187.601,1028172, "neutral", "Lilas Dinhint (museum curator)"},

	--Capitol
	--{"ekoarili_eichreemo",60,-2.83709,3.18179,19.5635,187.088,926474, "neutral", "Ek'oarili Eichreemo"},
	--{"indigo_siyan",60,24.6402,3.22324,-30.7135,341.212,926483, "neutral", "Indigo Siyan"},
	--{"sean_trenwell",60,19.4653,3.22324,-35.9776,345,926483, "neutral", "Sean Trenwell"},
	--{"victor_visalis",60,-26.4873,3.22324,20.2943,140.257,926480, "neutral", "Victor Visalis"},
	--{"oberhaur",60,-21.8614,3.22324,26.9177,183.918,926480, "npc_imperial", ""},
	--{"keanna_likyna",60,-18.8886,3.22324,20.608,214.006,926480, "neutral", "Keanna Li`kyna"},
	--{"tour_aryon",60,-37.3031,1.29422,0.713583,123.566,926479, "neutral", "Tour Aryon (governor)"},
	--{"egach_iromn",60,2.2628,7.90008,-37.3821,304.411,926476, "neutral", "Egach Iromn"},
	--{"explorer",60,-2.63337,0.3,2.46637,180.004,926475, "conversation", ""},
	--{"arosp_eslykewa",60,-22.8506,1.29946,6.24726,180.009,926475, "conversation", "Arosp Eslykewa"},
	--{"bothan_information_broker",60,-22.8506,1.2998,5.24726,360.011,926475, "conversation", ""},
	spawnMobile("tatooine", "businessman",60,19.5,1.3,4.1,310,926475)
	spawnMobile("tatooine", "businessman",60,18.4,1.3,4.1,53,926475)
	--{"explorer",60,-2.63337,0.3,2.46637,180.004,926475, "conversation", ""},
	--{"kiosait_eetwaka",60,-3.78237,2.27819,-25.8455,324.158,926475, "neutral", "Kiosait Eetwaka"},
	--{"medic",60,-2.63337,0.3,1.46637,0,926475, "conversation", ""},
	--{"nassa_ei",60,-23.2909,1.29891,-10.3943,67.506,926475, "neutral", "Nassa E'i"},
	--{"noble",60,18.4,1.3,5.2,150,926475, "threaten", ""},
	--{"noble",60,19.5,1.3,5.2,236,926475, "angry", ""},
	--{"tl_017",400,6.1,0.3,-0.49,96.7754,926475, "npc_imperial", "TL-017"},

	--Outside
	--{"afroh_orah",60,-1211.37,12,-3637.48,26.5441,0, "neutral", "Afroh Orah"},
	spawnMobile("tatooine", "businessman",60,-1268.02,12,-3531.37,119.711,0)
	spawnMobile("tatooine", "businessman",60,-987.119,12,-3729.33,40.7756,0)
	spawnMobile("tatooine", "cll8_binary_load_lifter",60,-1402.49,9.99327,-3756.82,140.109,0)
	spawnMobile("tatooine", "commoner_fat",60,-1213.04,12,-3629.94,40.7191,0)
	spawnMobile("tatooine", "commoner_fat",60,-1279.47,12,-3584.64,352.018,0)
	spawnMobile("tatooine", "commoner_fat",60,-1145.13,12,-3507.53,221.73,0)
	spawnMobile("tatooine", "commoner_fat",60,-1358.9,12,-3504.1,76.9298,0)
	spawnMobile("tatooine", "commoner_fat",60,-1066.46,12,-3668.09,306.973,0)
	spawnMobile("tatooine", "commoner_naboo",60,-1162.65,12,-3646.5,113.039,0)
	spawnMobile("tatooine", "commoner_naboo",60,-1311.62,12,-3674.36,26.9034,0)
	spawnMobile("tatooine", "commoner_naboo",60,-1464.81,12,-3561.05,198.861,0)
	spawnMobile("tatooine", "commoner_naboo",60,-1142.23,12,-3672.51,283.648,0)
	spawnMobile("tatooine", "commoner_naboo",60,-1076.36,12,-3657.52,310.468,0)
	spawnMobile("tatooine", "commoner_naboo",60,-1026.76,12,-3725.49,331.101,0)
	spawnMobile("tatooine", "commoner_naboo",60,-1060.23,12,-3704.2,289.169,0)
	spawnMobile("tatooine", "commoner_naboo",60,-1068.17,12,-3690.99,281.417,0)
	spawnMobile("tatooine", "commoner_naboo",60,-1080.55,12,-3696.41,132.802,0)
	spawnMobile("tatooine", "commoner_old",60,-1157.39,12,-3666.66,339.829,0)
	spawnMobile("tatooine", "commoner_old",60,-1283.53,12,-3559.37,341.069,0)
	spawnMobile("tatooine", "commoner_old",60,-1095.68,12,-3640.98,39.1732,0)
	spawnMobile("tatooine", "commoner_old",60,-1077.51,12,-3513.92,10.0573,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1106.31,12,-3697.59,58.4608,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1145.53,12,-3656.31,48.131,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1174.92,12,-3635.8,200.868,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1200.16,12,-3631.89,28.4494,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1216.2,12,-3549.61,41.2597,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1347.58,12,-3695.99,31.1935,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1291.57,12,-3618.78,244.46,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1429,12,-3628.03,236.879,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1404.76,12,-3636.5,34.8111,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1320.46,12,-3633.41,186.254,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1226.87,12,-3628.59,257.373,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1047.35,12,-3665.81,279.108,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1085.53,12,-3647.54,201.255,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1039.09,12,-3723.55,303.987,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1041.87,12,-3711.58,273.462,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1033.88,12,-3644.68,209.933,0)
	spawnMobile("tatooine", "commoner_tatooine",60,-1010.28,12,-3728.59,85.9413,0)
	spawnMobile("tatooine", "criminal",300,-1257.34,12,-3539.31,207.196,0)
	spawnMobile("tatooine", "criminal",300,-983.47,10,-3538.5,142.826,0)
	--{"gerak_vurtimis",60,-1252.5,12,-3617.35,278.1,0, "calm", "Gerak Vurtimis"},
	--{"gert_talnin",60,-1287.3,12,-3587.16,169.676,0, "neutral", ""},
	--{"ihatha_hawit",60,-1291.36,12,-3634.94,301.333,0, "neutral", "Ihatha Hawit"},
	--{"gunham",60,-1125.07,12.1959,-3622.83,83.2544,0, "npc_imperial", ""},
	--{"imi_eficoaw",60,-1013.14,12,-3695.87,233.295,0, "neutral", "Imi Eficoaw"},
	spawnMobile("tatooine", "informant_npc_lvl_1",0,-1449,12,-3558,270,0)
	spawnMobile("tatooine", "informant_npc_lvl_1",0,-1450,12,-3566,270,0)
	spawnMobile("tatooine", "informant_npc_lvl_1",0,-1332,12,-3700,0,0)
	spawnMobile("tatooine", "informant_npc_lvl_1",0,-1053,12,-3726,90,0)
	spawnMobile("tatooine", "informant_npc_lvl_1",0,-1023,12,-3677,225,0)
	spawnMobile("tatooine", "informant_npc_lvl_1",0,-1220,12,-3560,45,0)
	--{"issirx",60,-1074.37,12,-3676.69,21.1437,0, "neutral", "Issirx"},
	--{"isuss",60,-1294.3,12,-3500.88,45.8365,0, "neutral", "Isuss"},
	--{"junk_dealer",0,-1392,185,-3847.9,8,0, "", "",JUNKGENERIC,JUNKCONVGENERIC},
	spawnMobile("tatooine", "noble",60,-1250.18,12,-3545.35,279.206,0)
	spawnMobile("tatooine", "noble",60,-1023.25,12,-3746.26,261.847,0)
	--{"oohiani",60,-1120.21,12,-3639.71,204.893,0, "neutral", "Oohiani"},
	--{"owaitacyg_amafie",60,-1205.68,12,-3539.64,80.1199,0, "neutral", "Owaitacyg Amafie"},
	--{"r4",60,-1065.54,12,-3599.21,310.993,0, "calm", "R4-K1"},
	spawnMobile("tatooine", "scientist",60,-1271.82,12,-3601.08,5.92405,0)
	spawnMobile("tatooine", "scientist",60,-1012.31,12,-3748.5,10.8572,0)
	--{"siarafont_cakrod",60,-1104.12,12,-3705.29,199.904,0, "neutral", "Siarafont Cakrod"},
	--{"sol_windtide",60,-1203.12,12,-3612.74,236.494,0, "calm", "Sol Windtide"},
	--{"tegou_howy",60,-1005.68,12,-3716.81,181.862,0, "neutral", "Tegou Howy"},
	spawnMobile("tatooine", "trainer_architect",0,-1255,12,-3567,-47,0)
	spawnMobile("tatooine", "trainer_artisan",0,-1266,12,-3559,227,0)
	spawnMobile("tatooine", "trainer_bioengineer",0,-1444.06,10,-3749.08,90,0)
	spawnMobile("tatooine", "trainer_brawler",0,-1278.75,12,-3540.47,79,0)
	spawnMobile("tatooine", "trainer_chef",0,-1216,12,-3601,153,0)
	spawnMobile("tatooine", "trainer_entertainer",0,-1266,12,-3626,22,0)
	spawnMobile("tatooine", "trainer_marksman",0,-1272,12,-3538,180,0)
	spawnMobile("tatooine", "trainer_politician",0,-1125,12.2,-3616,130,0)
	spawnMobile("tatooine", "trainer_scout",0,-1295.83,12,-3563.27,51,0)
	spawnMobile("tatooine", "trainer_squadleader",0,-1019,10,-3532,180,0)
	spawnMobile("tatooine", "trainer_tailor",0,-1348,12,-3677,180,0)
	spawnMobile("tatooine", "valarian_swooper_leader",300,-1158.7,12,-3661.7,270,0)
	spawnMobile("tatooine", "valarian_swooper_leader",300,-1161,12,-3662,90,0)
	spawnMobile("tatooine", "valarian_swooper_leader",300,-1161.6,12,-3647.1,-61,0)
	--{"viconya_tili",60,-1001.04,10,-3550.02,271.672,0, "calm", "Vi`conya T`ili"},
	--{"wlinc_tchrr",60,-1288.15,12,-3588.42,276.296,0, "neutral", ""},

	--Imperial Npc's Outside
	--{"coa2_imperial_coordinator",60,-1131.72,12,-3660.15,18.1873,0, "npc_imperial", ""},
	--{"commander_dkrn",60,-1157.74,12,-3525.5,200.331,0, "npc_imperial", "Commander D`krn"},
	spawnMobile("tatooine", "command_security_guard",400,-1278.5,12.5279,-3643.1,165.005,0)
	spawnMobile("tatooine", "command_security_guard",400,-1243.9,12,-3550.55,301.01,0)
	spawnMobile("tatooine", "command_security_guard",400,-1150.5,12,-3547.1,26,0)
	spawnMobile("tatooine", "command_security_guard",400,-1097,12,-3525.3,121.004,0)
	--{"dark_trooper",400,-1430.36,12,-3728.58,141.26,0, "npc_imperial", ""},
	--{"dark_trooper",400,-1004.6,12,-3710.8,132,0, "npc_imperial", ""},
	--{"dark_trooper",400,-1428.52,12,-3730.88,141.264,0, "npc_imperial", ""},
	--{"dark_trooper",400,-983.59,12,-3748.85,33.65,0, "npc_imperial", ""},
	spawnMobile("tatooine", "dark_trooper",400,-1453,12,-3646.95,42.076,0)
	spawnMobile("tatooine", "dark_trooper",400,-1133.2,12.1958,-3614.6,125.004,0)
	spawnMobile("tatooine", "dark_trooper",400,-1130.9,12.1964,-3611.6,125.004,0)
	--{"dark_trooper",400,-1428.52,12,-3730.88,141.264,0, "npc_imperial", ""},
	--{"dark_trooper",400,-1002.9,12,-3705.4,-55,0, "npc_imperial", ""},
	spawnMobile("tatooine", "elite_sand_trooper",400,-1284,12,-3486,180,0)
	--{"elite_sand_trooper",400,-1368.48,12,-3725.42,268.991,0, "npc_imperial", ""},
	spawnMobile("tatooine", "elite_sand_trooper",400,-1276,12,-3487,180,0)
	--{"elite_sand_trooper",400,-1348.2,12,-3712.7,315,0, "npc_imperial", ""},
	--{"elite_sand_trooper",400,-1429.92,12,-3731.49,141.268,0, "npc_imperial", ""},
	spawnMobile("tatooine", "elite_sand_trooper",400,-1275,12,-3507.5,315,0)
	--{"elite_sand_trooper",400,-1378.4,12,-3712.53,119.74,0, "npc_imperial", ""},
	--{"elite_sand_trooper",400,-984.262,12,-3742.5,126.391,0, "npc_imperial", ""},
	spawnMobile("tatooine", "elite_sand_trooper",400,-1454.87,12,-3651.05,45.2754,0)
	spawnMobile("tatooine", "elite_sand_trooper",400,-1455.96,12,-3650.25,42.1254,0)
	--{"elite_sand_trooper",400,-1058.39,12,-3671.09,222.747,0, "npc_imperial", ""},
	--{"elite_sand_trooper",400,-1093.52,12,-3647.32,308.036,0, "npc_imperial", ""},
	--{"elite_sand_trooper",400,-1049.04,12,-3660.19,249.5,0, "npc_imperial", ""},
	spawnMobile("tatooine", "sand_trooper",400,-983.8,12,-3746.5,116.003,0)
	spawnMobile("tatooine", "sand_trooper",400,-980.4,12,-3742.8,119,0)
	spawnMobile("tatooine", "sand_trooper",400,-1169.8,12,-3692.1,235.007,0)
	spawnMobile("tatooine", "sand_trooper",400,-1283.8,12,-3480.4,306.486,0)
	spawnMobile("tatooine", "sand_trooper",400,-1275.6,12,-3479.9,0,0)
	spawnMobile("tatooine", "sand_trooper",400,-1016.9,12,-3741.2,97.0029,0)
	spawnMobile("tatooine", "sand_trooper",400,-1018.3,12,-3736.2,272.008,0)
	spawnMobile("tatooine", "sand_trooper",400,-1089.8,12,-3704.2,116.003,0)
	spawnMobile("tatooine", "sand_trooper",400,-1154.1,12,-3650,-111,0)
	spawnMobile("tatooine", "sand_trooper",400,-1083.6,12,-3594.2,169.005,0)
	spawnMobile("tatooine", "sand_trooper",400,-1181.3,12,-3537.9,198.006,0)
	spawnMobile("tatooine", "storm_commando",400,-1231.81,12,-3605.85,127.312,0)
	spawnMobile("tatooine", "storm_commando",400,-1292.8,12,-3585.5,133.004,0)
	spawnMobile("tatooine", "storm_commando",400,-1115.14,12,-3639.18,263.058,0)
	spawnMobile("tatooine", "stormtrooper_sniper",400,-1093.7,14,-3660.2,41.0012,0)
	--{"imperial_army_captain",400,-1307.46,12,-3662.44,218.566,0, "npc_imperial", ""},
	spawnMobile("tatooine", "imperial_recruiter",60,-1072.7,12,-3594,220,0)
	spawnMobile("tatooine", "imperial_recruiter",60,-1275.75,12,-3594.28,-73,0)
	--{"lt_sabol",60,-1291.67,12,-3539,118,0, "npc_imperial", "Lt. Sabol"},
	--{"tk_471",400,-1048.04,12,-3699.53,275.497,0, "npc_imperial", "TK-471"},

	--Creatures
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,-1062.1,23.7,-3451.8,-110,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,-1068.2,23.2,-3452.5,98,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,-1064.3,22.7,-3455.2,27,0)
	spawnMobile("tatooine", "lesser_desert_womp_rat",300,-1057.7,23.8,-3452.7,-92,0)

	spawnMobile("tatooine", "minor_worrt",300,-927.86,27.7005,-3784.58,229.599,0)
	spawnMobile("tatooine", "minor_worrt",300,-922.653,26.6572,-3778.35,225.778,0)
	spawnMobile("tatooine", "minor_worrt",300,-923.222,25.6505,-3774.92,187.309,0)
	spawnMobile("tatooine", "minor_worrt",300,-910.093,26.277,-3783.93,117.558,0)
	spawnMobile("tatooine", "minor_worrt",300,-913.601,27.1392,-3784.15,69.6335,0)
	spawnMobile("tatooine", "minor_worrt",300,-912.848,25.8267,-3794.42,276.507,0)
	spawnMobile("tatooine", "worrt",300,-930.225,29.785,-3796.81,106.152,0)
	spawnMobile("tatooine", "worrt",300,-939.612,24.6046,-3781.1,308.507,0)

	spawnMobile("tatooine", "minor_worrt",300,-1150.79,22.8276,-3410.77,286.41,0)
	spawnMobile("tatooine", "minor_worrt",300,-1148.52,28.0683,-3402.47,295.148,0)
	spawnMobile("tatooine", "minor_worrt",300,-1158.11,29.9266,-3393.44,290.62,0)
	spawnMobile("tatooine", "minor_worrt",300,-1152.38,31.805,-3390,28.2254,0)
	spawnMobile("tatooine", "minor_worrt",300,-1144.7,30.4,-3395.4,-121,0)
	spawnMobile("tatooine", "minor_worrt",300,-1158.7,26.2,-3403.5,68,0)

	spawnMobile("tatooine", "rill",300,-907.188,18.3242,-3573.35,360.011,0)
	spawnMobile("tatooine", "rill",300,-901.808,18.7395,-3570.88,360.011,0)
	spawnMobile("tatooine", "rill",300,-908.624,18.0014,-3571.89,0,0)
	spawnMobile("tatooine", "rill",300,-903.859,19.9334,-3579.55,0,0)
	spawnMobile("tatooine", "rockmite",300,-895.802,10.7364,-3546.49,145.129,0)
	spawnMobile("tatooine", "rockmite",300,-904.8,14.6023,-3552.38,322.681,0)

	spawnMobile("tatooine", "worrt",300,-1337.3,16.2,-3430.4,-152,0)
	spawnMobile("tatooine", "worrt",300,-1340.4,16,-3431.5,-152,0)
	spawnMobile("tatooine", "worrt",300,-1341.43,15.3175,-3434.23,284.1,0)
	spawnMobile("tatooine", "worrt",300,-1337.28,15.0418,-3434.8,360.011,0)
end
