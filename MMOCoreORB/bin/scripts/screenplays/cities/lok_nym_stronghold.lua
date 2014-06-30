LokNymStrongholdScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "LokNymStrongholdScreenPlay"
}

registerScreenPlay("LokNymStrongholdScreenPlay", true)

function LokNymStrongholdScreenPlay:start()
	if (isZoneEnabled("lok")) then
		self:spawnMobiles()
	end
end

function LokNymStrongholdScreenPlay:spawnMobiles()
	--thugs
	spawnMobile("lok", "nym_surveyer",300,484.493,11.9154,5091.56,180.005,0)
	spawnMobile("lok", "nym_guard_weak",300,551.4,12,5169.8,200,0)
	spawnMobile("lok", "nym_guard_weak",300,535.7,11.9,5105.3,90,0)
	spawnMobile("lok", "nym_guard_weak",300,331.611,11.9777,4898.94,14.0896,0)
	spawnMobile("lok", "nym_guard_weak",300,322.8,12.1,5050,216,0)
	spawnMobile("lok", "nym_guard_weak",300,343.53,12.5909,4902.71,356.744,0)
	spawnMobile("lok", "nym_guard_weak",300,348.219,12.1248,4940.84,19.7209,0)
	spawnMobile("lok", "nym_guard_elite",300,381.62,12,5013.95,350,0)
	spawnMobile("lok", "nym_guard_elite",300,381.4,12,5015.13,170,0)
	spawnMobile("lok", "nym_guard_elite",300,384.094,11.9992,4996.7,286.256,0)
	spawnMobile("lok", "nym_guard_elite",300,550.517,11.7979,5167.25,10.2375,0)
	spawnMobile("lok", "nym_guard_elite",300,518.4,12,5100.5,300,0)
	spawnMobile("lok", "nym_guard_elite",300,405,12.5,5032,230,0)
	spawnMobile("lok", "nym_guard_elite",300,435.932,12.5279,5024.65,247.747,0)
	spawnMobile("lok", "nym_guard_elite",300,389.1,12,5034.2,260,0)
	spawnMobile("lok", "nym_guard_elite",300,441,12.5,5025,90,0)
	spawnMobile("lok", "nym_guard_strong",300,405.3,12.5,5030,349,0)
	spawnMobile("lok", "nym_guard_strong",300,537.325,11.9367,5112.7,290,0)
	spawnMobile("lok", "nym_guard_strong",300,540.129,12.073,5124.46,348.152,0)
	spawnMobile("lok", "nym_guard_strong",300,538.5,11.9,5102.6,45,0)
	spawnMobile("lok", "nym_guard_strong",300,406.311,11.8705,4991.53,286.282,0)
	spawnMobile("lok", "nym_guard_strong",300,334.572,11.9605,4892.89,349.707,0)
	spawnMobile("lok", "nym_guard_strong",300,350.446,12.0004,4975.94,216.027,0)
	spawnMobile("lok", "nym_guard_weak",300,400.5,12.5,5047.2,90,0)
	spawnMobile("lok", "nym_guard_weak",300,520.4,12,5128.8,180,0)

	spawnMobile("lok", "nym_guard_weak",300,18.98,2.29948,10.51,181.005,6595511)
	spawnMobile("lok", "nym_guard_weak",300,-20.26,2.29947,-18.62,3.00005,6595511)
	spawnMobile("lok", "nym_guard_strong",300,-18.91,2.29916,9.74,178.005,6595511)
	spawnMobile("lok", "nym_bodyguard",300,5.86,1.3,-5.04,283.008,6595511)
	spawnMobile("lok", "nym_bodyguard",300,-3.58,1.3,4.01,89.0026,6595511)
	spawnMobile("lok", "nym_brawler",300,-8.11,1.3,-1.06,177.005,6595511)
	spawnMobile("lok", "nym_brawler",300,4.17,1.3,-5.62,33.001,6595511)
	spawnMobile("lok", "nym_guard_elite",300,3.12,4.0782,-9.55,359.01,6595511)
	spawnMobile("lok", "nym_guard_elite",300,-3.1239,4.0782,-9.55698,359.01,6595511)
	spawnMobile("lok", "nym_guard_elite",300,1.98,8.9,-30.5,0,6595511)
	spawnMobile("lok", "nym_guard_elite",300,-1.91,8.9,-30.5,360.011,6595511)
	spawnMobile("lok", "nym_destroyer",300,-1.79,1.3,3.94,267.008,6595511)
	spawnMobile("lok", "nym_surveyer",300,-8.05,1.3,-2.3,7.00022,6595511)
	spawnMobile("lok", "nym_surveyer",300,4.39,1.3,-3.87,149.004,6595511)

	spawnMobile("lok", "nym_bodyguard",300,-29.1,2.3,1.5,200,6595515)

	spawnMobile("lok", "nym_pirate_elite",300,37.49,2.29422,-1.17,88.0026,6595518)
	spawnMobile("lok", "nym_pirate_elite",300,36.71,2.29422,-2.92,88.0026,6595518)

	spawnMobile("lok", "nym_surveyer",300,1.83273,-0.894992,-14.2461,180.009,8145381)
	spawnMobile("lok", "nym_surveyer",300,-2.13049,-0.894991,6.9956,360.011,8145378)

	--misc
	spawnMobile("lok", "informant_npc_lvl_3",60,369,11.89,5087,90,0)
	spawnMobile("lok", "informant_npc_lvl_3",60,540,11.92,5072,180,0)



	--quest
	spawnMobile("lok", "nym_fuel_tech",0,374.599,11.9876,4986.77,31.5798,0)
	spawnMobile("lok", "ramna",60,19.5548,-0.894995,-20.1381,20.176,8145379)
	spawnMobile("lok", "warvog_arkon",60,-12.1246,1.6,-16.3553,291.827,8145361)
	spawnMobile("lok", "viopa",60,-2.2483,4.0782,-10.4691,138.087,6595511)

	--trainer
	spawnMobile("lok", "trainer_combatmedic",60,-17.1,0.26,9.2,-100,2745870)
	spawnMobile("lok", "trainer_doctor",60,22.1279,0.26,-6.11676,91,2745866)
	spawnMobile("lok", "trainer_medic",60,-16.0068,0.26,-2.42861,117,2745870)

	--Moving from spawn manager lok.lua

	--Anything dashed out will need to be added here and removed from spawn manager once the spawnMobiles command is extended.

	spawnMobile("lok", "agriculturalist",60,16.74,14.26,-2.05184,56.8997,2745876)
	--{"agriculturalist",60,7.54821,-0.894991,-7.47564,180.006,8145378, "conversation", ""},
	--{"artisan",60,-13.7191,0.26,-9.38652,179.996,2745870, "conversation", ""},
	--{"artisan",60,-29.0395,0.26,8.63541,0,2745870, "conversation", ""},
	--{"artisan",60,-24.251,-0.894991,23.6325,180,8145387, "conversation", ""},
	--{"artisan",60,6.44821,-0.894991,-7.47564,135.005,8145378, "conversation", ""},
	--{"artisan",60,-23.8096,1.6,-5.16968,180.005,8145362, "conversation", ""},
	--{"bapibac",60,14.5598,0.26,3.77176,360.011,2745866, "conversation", "Bapibac One-Oesp"},
	spawnMobile("lok", "bartender",60,-11.2794,-0.894992,1.36624,33.4279,8145378)
	spawnMobile("lok", "bodyguard",300,15.64,14.26,-0.951844,303.334,2745876)
	--{"bodyguard",300,3.95102,7.26,9.58572,179.998,2745872, "conversation", ""},
	--{"bodyguard",300,-1.26922,0.999998,-0.973796,180.006,8145356, "conversation", ""},
	--{"bodyguard",300,4.27638,1.00001,-7.08525,134.999,8145356, "conversation", ""},
	--{"bodyguard",300,-3.37845,0.999947,7.55641,135,8145356, "conversation", ""},
	--{"bodyguard",300,-23.1849,1.58923,0.850721,0.0559546,8145358, "conversation", ""},
	--{"bothan_diplomat",60,18.7783,1.28309,9.1449,135.004,8145357, "conversation", ""},
	--{"bothan_information_broker",60,-0.243796,7.26,-12.1226,135.01,2745872, "conversation", ""},
	--{"bothan_information_broker",60,-25.6603,0.26,-0.532375,135.011,2745870, "conversation", ""},
	--{"bothan_information_broker",60,19.6068,1.28309,-14.4961,180.006,8145357, "conversation", ""},
	--{"bothan_information_broker",60,-11.545,1,-3.99877,45.0052,8145358, "conversation", ""},
	spawnMobile("lok", "bounty_hunter",300,16.74,14.26,-0.951844,283.416,2745876)
	--{"bounty_hunter",300,29.0555,0.26,7.22789,360.011,2745866, "conversation", ""},
	--{"brawler",60,4.19353,13.5019,8.75924,180,2745876, "conversation", ""},
	--{"brawler",60,32.2156,14.26,-9.06471,0.0395659,2745876, "conversation", ""},
	--{"brawler",60,9.48372,0.26,-7.07547,135.009,2745866, "conversation", ""},
	--{"brawler",60,-4.95629,-0.894992,-6.53149,360.011,8145378, "conversation", ""},
	--{"brawler",60,5.37638,1,-8.18525,360.011,8145356, "conversation", ""},
	spawnMobile("lok", "businessman",60,372.58,12.0976,5003.43,336.419,0)
	spawnMobile("lok", "businessman",60,514.113,11.4851,5196.38,105.024,0)
	--{"businessman",60,-2.13049,-0.894991,8.0956,179.998,8145378, "conversation", ""},
	--{"businessman",60,19.8783,1.28309,8.0449,360.011,8145357, "conversation", ""},
	--{"ciwi_mosregri",60,31.1714,7.25,12.3841,180.018,2745874, "conversation", "Ciwi Mo-sregri"},
	--{"comm_operator",60,432.639,12,5219.48,180.005,0, "conversation", ""},
	--{"commoner",60,31.1714,7.25,11.2841,0,2745874, "conversation", ""},
	--{"commoner",60,29.0555,0.26,8.32789,179.999,2745866, "conversation", ""},
	spawnMobile("lok", "commoner",60,618.591,11.8421,5013.77,225.688,0)
	--{"commoner",60,6.78896,1.00001,8.59957,0,8145356, "conversation", ""},
	--{"commoner",60,-11.545,1.00022,-2.89877,134.998,8145358, "conversation", ""},
	spawnMobile("lok", "commoner_fat",60,562.914,11.8302,5171.75,43.747,0)
	--{"commoner_fat",60,11.63,-0.894992,-16.56,277.008,8145381, "neutral", "Choster (Retired Engineer)"},
	--{"commoner_fat",60,6.44821,-0.894991,-8.57564,45.0004,8145378, "conversation", ""},
	spawnMobile("lok", "commoner_naboo",60,360.315,11.9448,4966.58,287.085,0)
	spawnMobile("lok", "commoner_naboo",60,371.229,12.06,5167.84,53.0347,0)
	spawnMobile("lok", "commoner_naboo",60,545.596,11.959,5081.45,126.924,0)
	spawnMobile("lok", "commoner_naboo",60,449.967,12,5141.31,112.766,0)
	spawnMobile("lok", "commoner_old",60,535.709,11.9925,5135.86,230.158,0)
	spawnMobile("lok", "commoner_old",60,522.568,11.8075,4964.65,304.378,0)
	--{"commoner_old",60,-36.21,0.10501,-13.93,87.0026,8145389, "neutral", "Sergeant Moore (Retired)"},
	--{"commoner_old",60,43.6331,0.104999,1.36432,180.09,8145376, "conversation", ""},
	spawnMobile("lok", "commoner_tatooine",60,280.329,11.9265,5027.91,218.008,0)
	spawnMobile("lok", "commoner_tatooine",60,285.432,11.9758,5117.33,85.567,0)
	spawnMobile("lok", "commoner_tatooine",60,332.33,12.0215,5159.29,135.281,0)
	spawnMobile("lok", "commoner_tatooine",60,356.668,12.0208,4918.65,342.78,0)
	spawnMobile("lok", "commoner_tatooine",60,342.313,11.9993,5024.26,97.0775,0)
	spawnMobile("lok", "commoner_tatooine",60,462.534,11.8294,5148.35,23.6115,0)
	spawnMobile("lok", "commoner_tatooine",60,462.685,11.9861,5192.39,127.19,0)
	spawnMobile("lok", "commoner_tatooine",60,429.839,13,5136.92,340.915,0)
	--{"commoner_tatooine",60,14.3,-0.9,23.3,181,8145380, "npc_sitting_chair", "Berema"},
	--{"commoner_tatooine",60,-2.27845,0.999959,6.45641,0,8145356, "conversation", ""},
	--{"commoner_technician",60,0.856204,7.26,-13.2226,0,2745872, "conversation", ""},
	spawnMobile("lok", "criminal",300,226.672,12.0826,4954.08,267.001,0)
	spawnMobile("lok", "criminal",300,221.718,11.9626,4987.57,135.742,0)
	spawnMobile("lok", "criminal",300,525.319,11.8584,5156.53,159.79,0)
	--{"entertainer",60,30.0714,7.25,12.3841,135.011,2745874, "conversation", ""},
	--{"entertainer",60,-30.1395,0.25801,9.73541,135.01,2745870, "conversation", ""},
	--{"entertainer",60,-5.72977,-0.894994,22.9507,180.008,8145384, "conversation", ""},
	--{"entertainer",60,-6.82977,-0.894994,22.9507,135.007,8145384, "conversation", ""},
	--{"entertainer",60,18.2791,-0.894996,-13.3794,180.008,8145379, "conversation", ""},
	--{"entertainer",60,6.78896,1.00001,9.69957,180.005,8145356, "conversation", ""},
	--{"evathm",60,4.84117,-0.894992,20.6966,45.0006,8145382, "conversation", "Evathm Av'Tvo"},
	--{"explorer",60,-24.5603,0.26,-1.63238,0,2745870, "conversation", ""},
	--{"explorer",60,23.1893,-0.894994,8.7231,0,8145378, "conversation", ""},
	--{"explorer",60,19.6068,1.28309,-15.5961,360.011,8145357, "conversation", ""},
	--{"farmer",60,391.143,12,5057.74,180.005,0, "conversation", ""},
	--{"farmer",60,29.5658,13.25,10.7188,180.002,2745876, "conversation", ""},
	--{"farmer",60,-2.27845,0.999949,7.55641,180.005,8145356, "conversation", ""},
	--{"farmer",60,-14.6521,1.0008,7.50857,0,8145358, "conversation", ""},
	--{"farmer",60,484.493,11.8719,5090.56,2.49081,0, "conversation", ""},
	spawnMobile("lok", "farmer_rancher",60,18.1642,-0.894992,19.3991,79.3056,8145380)
	--{"fringer",300,10.5837,0.26,-7.07547,180.014,2745866, "conversation", ""},
	--{"gambler",60,0.856204,7.26,-12.1226,180.015,2745872, "conversation", ""},
	--{"gambler",60,43.6314,0.104999,0.264886,0.0791317,8145376, "conversation", ""},
	--{"gambler",60,19.8783,1.28309,9.1449,180.006,8145357, "conversation", ""},
	--{"gambler",60,-10.445,1.00009,-2.89877,180.006,8145358, "conversation", ""},
	--{"idhak_ipath",60,28.4658,13.25,10.7188,135.001,2745876, "conversation", "Idhak Ipath"},
	--{"ifoja_lico",60,552.494,11.89,5111.84,180.005,0, "conversation", "Ifoja Lico"},
	--{"info_broker",60,-15.7521,1.00122,8.60857,134.998,8145358, "conversation", ""},
	spawnMobile("lok", "lok_herald_01",60,371.717,11.8618,5179.1,286.408,0)
	spawnMobile("lok", "lok_herald_02",60,221.864,17.0919,5154.99,342.34,0)
	--{"medic",60,32.2166,14.26,-7.96455,180.055,2745876, "conversation", ""},
	--{"medic",60,-29.0395,0.26,9.73541,180.016,2745870, "conversation", ""},
	--{"medic",60,14.5598,0.26,4.87176,180.004,2745866, "conversation", ""},
	--{"medic",60,552.494,11.89,5110.84,0,0, "conversation", ""},
	--{"medic",60,-3.23049,-0.894991,8.0956,134.996,8145378, "conversation", ""},
	--{"medic",60,-1.26922,1,-2.0738,360.011,8145356, "conversation", ""},
	--{"medic",60,-10.445,1,-3.99877,360.011,8145358, "conversation", ""},
	--{"melo",60,32.2502,7.25,-2.56477,360.011,2745874, "conversation", "Melo"},
	--{"mercenary",60,25.7848,-0.894993,-8.75091,180.009,8145378, "conversation", ""},
	--{"mercenary",60,24.6848,-0.894992,-8.75091,135.009,8145378, "conversation", ""},
	--{"mercenary",60,432.639,12,5218.48,0,0, "conversation", ""},
	--{"weak_mercenary",300,5.94117,-0.894992,21.7966,180.007,8145382, "conversation", ""},
	--{"weak_mercenary",300,23.1893,-0.894993,9.8231,180.01,8145378, "conversation", ""},
	--{"miner",60,4.19353,13.5019,7.65925,360.011,2745876, "conversation", ""},
	--{"miner",60,-13.7191,0.26,-10.4865,360.011,2745870, "conversation", ""},
	--{"miner",60,-14.4486,0.26,6.76362,134.998,2745870, "conversation", ""},
	--{"noble",60,-24.5603,0.26,-0.532375,180.016,2745870, "conversation", ""},
	--{"noble",60,5.94117,-0.894992,20.6966,0,8145382, "conversation", ""},
	--{"noble",60,-14.6521,1.00101,8.60857,180.005,8145358, "conversation", ""},
	--{"nym",60,0,3.27819,-22.9,0,6595511, "npc_sitting_chair", ""},
	--{"nym_kusak_guardian",60,-3.62,3.27819,-25.44,39.0011,6595511, "calm", "Scourge"},
	--{"nym_kusak_guardian",60,3.62,3.27819,-25.44,325.01,6595511, "bored", "Razor"},
	--{"pilot",60,31.1166,14.26,-9.06455,44.9979,2745876, "conversation", ""},
	--{"pilot",60,18.2791,-0.894996,-14.4794,0,8145379, "conversation", ""},
	--{"pilot",60,-23.8096,1.6,-6.26968,0,8145362, "conversation", ""},
	--{"junk_dealer",60,367,12,5202.8,-178,0,"","",JUNKGENERIC,JUNKCONVGENERIC},
	--{"junk_reggi",60,443.925,12,4879.41,69.9891,0,"","Reggi Tirver",JUNKWEAPONS,JUNKCONVREGGINYM},
	--{"rifea_eicik",60,-23.1848,1.58812,1.95072,180.005,8145358, "conversation", "Rifea Eicik"},
	--{"rorha_wahe",60,7.54821,-0.894991,-8.57564,0,8145378, "conversation", "Rorha Wahe"},
	spawnMobile("lok", "scientist",60,363.384,11.8774,5104.73,315.983,0)
	--{"scientist",60,-13.3486,0.26,5.66362,360.011,2745870, "conversation", ""},
	--{"scientist",60,25.7848,-0.894993,-9.85091,0,8145378, "conversation", ""},
	--{"scientist",60,5.37638,1.00001,-7.08525,180.006,8145356, "conversation", ""},
	--{"scoundrel",60,-30.1395,0.259061,8.63541,45.0015,2745870, "conversation", ""},
	--{"scoundrel",60,-24.251,-0.894991,22.5325,360.011,8145387, "conversation", ""},
	--{"smuggler",300,3.95102,7.26,8.48572,360.011,2745872, "conversation", ""},
	--{"smuggler",300,10.5837,0.26,-8.17547,0,2745866, "conversation", ""},
	--{"smuggler",300,4.84117,-0.894992,21.7966,135.006,8145382, "conversation", ""},
	--{"smuggler",300,-4.95629,-0.894992,-5.43149,179.998,8145378, "conversation", ""},
	--{"spacer",60,391.143,12,5056.74,0,0, "conversation", ""},
	--{"spacer",60,31.1166,14.26,-7.96455,135.032,2745876, "conversation", ""},
	--{"spacer",60,-13.3486,0.26,6.76362,179.996,2745870, "conversation", ""},
	--{"spacer",60,9.48372,0.26,-8.17547,45.0031,2745866, "conversation", ""},
	--{"spacer",60,1.83273,-0.894992,-15.3461,0,8145381, "conversation", ""},
	--{"spacer",60,-5.72977,-0.894996,21.8507,0,8145384, "conversation", ""},
	--{"spacer",60,-3.37845,0.999956,6.45641,44.9954,8145356, "conversation", ""},
	--{"vendor",60,29.5658,13.25,9.61881,360.011,2745876, "conversation", ""},
	--{"vendor",60,32.2502,7.25,-1.46477,179.999,2745874, "conversation", ""},
	--{"vixur_webb",60,-13.2,-0.9,-20.2,22,8145383, "npc_sitting_chair", "Vixur Webb (a musician)"},
end
