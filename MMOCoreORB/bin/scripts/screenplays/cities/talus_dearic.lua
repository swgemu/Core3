TalusDearicScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TalusDearicScreenPlay",

	planet = "talus",

	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "noble_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, level, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"eg6_1", "eg6_power_droid", 1, 505.449, 6, -3025.94, 180.005, 0, "", false},
		{"eg6_2", "eg6_power_droid", 1, 380.738, 6, -3030.24, 268.183, 0, "", false},
		{"r2_1", "r2", 1, 207.078, 6, -2800.53, 272.222, 0, "", false},
		{"r2_2", "r2", 1, 504.449, 6, -3026.94, 180.006, 0, "", false},
		{"r3_1", "r3", 1, 459.915, 6, -3089.68, 182.021, 0, "", false},
		{"r3_2", "r3", 1, 457.915, 6, -3090.68, 270.018, 0, "", false},
		{"r3_3", "r3", 1, 664.839, 6, -3061.96, 180.006, 0, "", false},
		{"r5_1", "r5", 1, 411.254, 6, -2862.25, 208.889, 0, "", false},
		{"r5_2", "r5", 1, 407.095, 6, -3036.31, 310.529, 0, '', false},

		--NPCs
		{"npc_1", "patrolNpc", 1, 319, 6, -3001, 222, 0, "", false},
		{"npc_2", "patrolNpc", 1, 397, 6, -2971, 265, 0, "", false},
		{"npc_3", "patrolNpc", 1, 363, 6, -3101, 116, 0, "", false},
		{"npc_4", "patrolNpc", 1, 315, 6, -3159, 102, 0, "", false},
		{"npc_5", "patrolNpc", 1, 410, 6, -3168, 248, 0, "", false},
		{"npc_6", "patrolNpc", 1, 414, 6, -3135, 92, 0, "", false},
		{"npc_7", "patrolNpc", 1, 446, 6, -3185, 340, 0, "", false},
		{"npc_8", "patrolNpc", 1, 485, 6, -3155, 35, 0, "", false},
		{"npc_9", "patrolNpc", 1, 443, 6, -3086, 280, 0, "", false},
		{"npc_10", "patrolNpc", 1, 529, 6, -3025, 345, 0, "", false},
		{"npc_11", "patrolNpc", 1, 616, 6, -2977, 273, 0, "", false},
		{"npc_12", "patrolNpc", 1, 659, 6, -3064, 165, 0, "", false},
		{"npc_13", "patrolNpc", 1, 481, 6, -2854, 110, 0, "", false},
		{"npc_14", "patrolNpc", 1, 394, 6, -2881, 326,0, "", false},
		{"npc_15", "patrolNpc", 1, 445, 6, -2804, 34, 0, "", false},
		{"npc_16", "patrolNpc", 1, 396, 6, -2766, 177, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		eg6_1 = {{505, 6, 3025, 0, false}, {505, 6, -2955, 0, false}, {587, 6, -2953, 0, false}},
		eg6_2 = {{380, 6, -3030, 0, false}, {304, 6, -3031, 0, false}, {380, 6, -3030, 0, false}, {388, 6, -3081, 0, false}, {388, 6, -3097, 0, false}, {388, 6, -3081, 0, false}},
		r2_1 = {{207, 6, -2800, 0, false}, {132, 6, -2794, 0, false}, {207, 6, -2800, 0, false}, {282, 6, -2795, 0, false}, {285, 6, -2754, 0, false}, {282, 6, -2795, 0, false}},
		r2_2 = {{504, 6, -3026, 0, false}, {530, 6, -3034, 0, false}, {582, 6, -3034, 0, false}, {600, 6, -3007, 0, false}, {557, 6, -3031, 0, false}},
		r3_1 = {{459, 6, -3089, 0, false}, {438, 6, -3058, 0, false}, {454, 6, -3040, 0, false}, {455, 6, -2997, 0, false}, {454, 6, -3040, 0, false}, {440, 6, -3061, 0, false}},
		r3_2 = {{457, 6, -3089, 0, false}, {424, 6, -3067, 0, false}, {409, 6, -3031, 0, false}, {415, 6, -3043, 0, false}},
		r3_3 = {{663, 6, -3061, 0, false}, {633, 6, -3049, 0, false}, {634, 6.2, -3034.1, 0, false}, {696.1, 6.2, -3033.9, 0, false}, {696, 6, -3043, 0, false}, {681, 6, -3043, 0, false}},
		r5_1 = {{417, 6, -2837, 0, false}, {436, 6, -2837, 0, false}, {465, 6, -2850, 0, false}, {449, 6, -2861, 0, false}},
		r5_2 = {{407, 6, -3034, 0, false}, {406, 6, -2968, 0, false}, {341, 6, -2953, 0, false}, {390, 6, -2963, 0, false}, {484, 6, -2963, 0, false}, {407, 6, -2967, 0, false}},

		npc_1 = {{319, 6, -3001, 0, true}, {299, 6, -3008, 0, true}, {310, 6, -2974, 0, true}, {334, 6, -2974, 0, true}, {333, 6, -2956, 0, true}},
		npc_2 = {{397, 6, -2971, 0, true}, {401, 6, -2985, 0, true}, {400, 6, -3018, 0, true}, {387, 6, -3023, 0, false}, {400, 6, -3005, 0, true}},
		npc_3 = {{363, 6, -3101, 0, true}, {356, 6, -3112, 0, true}, {361, 6, -3097, 0, true}, {375, 6, -3109, 0, true}},
		npc_4 = {{315, 6, -3159, 0, true}, {287, 6, -3152, 0, true}, {299, 6, -3164, 0, true}, {328, 6, -3170, 0, true}},
		npc_5 = {{410, 6, -3168, 0, true}, {427, 6, -3141, 0, true}, {413, 6, -3156, 0, true}, {428, 6, -3168, 0, true}},
		npc_6 = {{414, 6, -3135, 0, true}, {341, 6, -3136, 0, true}, {342, 6, -3123, 0, true}, {341, 6, -3136, 0, true}},
		npc_7 = {{446, 6, -3185, 0, true}, {476, 6, -3190, 0, true}, {483, 6, -3181, 0, true}, {462, 6, -3184, 0, true}, {442, 6, -3190, 0, true}},
		npc_8 = {{485, 6, -3155, 0, true}, {478, 6, -3130, 0, true}, {484, 6, -3127, 0, true}, {491, 6, -3182, 0, true}},
		npc_9 = {{443, 6, -3086, 0, true}, {454, 6, -3095, 0, true}, {434, 6, -3076, 0, true}, {420, 6, -3072, 0, true}, {434, 6, -3076, 0, true}},
		npc_10 = {{529, 6, -3025, 0, true}, {513, 6, -3022, 0, true}, {566, 6, -3026, 0, true}, {563, 6, -3021, 0, true}},
		npc_11 = {{616, 6, -2977, 0, true}, {621, 6, -2966, 0, true}, {613, 6, -3000, 0, true}, {604, 6, -3015, 0, true}, {615, 6, -3023, 0, true}},
		npc_12 = {{659, 6, -3064, 0, true}, {671, 6, -3055, 0, true}, {678, 6, -3077, 0, true}, {650, 6, -3062, 0, true}},
		npc_13 = {{481, 6, -2854, 0, true}, {496, 6, -2869, 0, true}, {483, 6, -2873, 0, true}, {492, 6, -2843, 0, true}, {470, 6, -2843, 0, true}},
		npc_14 = {{394, 6, -2881, 0, true}, {375, 6, -2868, 0, true}, {401, 6, -2861, 0, true}, {402, 6, -2891, 0, true}, {388, 6, -2896, 0, true}},
		npc_15 = {{445, 6, -2804, 0, true}, {452, 6, -2829, 0, true}, {561, 6, -2831, 0, true}, {454, 6, -2824, 0, true}, {442, 6, -2746, 0, true}},
		npc_16 = {{396, 6, -2766, 0, true}, {403, 6, -2810, 0, true}, {394, 6, -2812, 0, true}, {403, 6, -2751, 0, true}, {392, 6, -2746, 0, true}},
	},
}

registerScreenPlay("TalusDearicScreenPlay", true)

function TalusDearicScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnSceneObjects()
	end
end

function TalusDearicScreenPlay:spawnSceneObjects()

	--outside starport
	spawnSceneObject(self.planet, "object/tangible/crafting/station/public_space_station.iff", 318.301, 6, -2896.49, 0, math.rad(95) )
end

function TalusDearicScreenPlay:spawnMobiles()

	--added Capitol building
	local pNpc = spawnMobile(self.planet, "seeker",60,-3.5,7.9,-30.5,4,6255467)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile(self.planet, "judge",60,24.5,3.2,19.3,-89,6255473)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile(self.planet, "chiss_female",60,-20.4,3.2,21.7,90,6255472)
	self:setMoodString(pNpc, "npc_consoling")

	--thugs
	spawnMobile(self.planet, "chunker_nitwit", 300, 152, 6, -3013, 146, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 157, 6, -3017, 192, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 161, 6, -3007, 2, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 163, 6, -3016, 314, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 21, 6, -2826, 268, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 24, 6, -2823, 37, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 28, 6, -2823, 337, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 31, 6, -2836, 89, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 461, 6, -3112, 226, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 464, 6, -3106, 80, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 470, 6, -3110, 48, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 471, 6, -3106, 223, 0)
	spawnMobile(self.planet, "chunker_punk", 300, 202, 6, -2860, 129, 0)
	spawnMobile(self.planet, "chunker_punk", 300, 206, 6, -2867, 80, 0)
	spawnMobile(self.planet, "chunker_punk", 300, 208, 6, -2860, 137, 0)
	spawnMobile(self.planet, "chunker_punk", 300, 209, 6, -2864, 97, 0)
	spawnMobile(self.planet, "chunker_punk", 300, 763, 6, -3279, 244, 0)
	spawnMobile(self.planet, "chunker_punk", 300, 777, 6, -3285, 269, 0)
	spawnMobile(self.planet, "chunker_punk", 300, 778, 6, -3287, 175, 0)
	spawnMobile(self.planet, "chunker_punk", 300, 780, 6, -3286, 172, 0)
	spawnMobile(self.planet, "chunker_swindler", 300, 101, 9, -3210, 232, 0)
	spawnMobile(self.planet, "chunker_swindler", 300, 104, 8, -3206, 110, 0)
	spawnMobile(self.planet, "chunker_swindler", 300, 113, 7, -3197, 15, 0)
	spawnMobile(self.planet, "criminal", 300, 146, 6, -3066, 303, 0)
	spawnMobile(self.planet, "criminal", 300, 155, 6, -3032, 72, 0)
	spawnMobile(self.planet, "criminal", 300, 287, 6, -3055, 265, 0)
	spawnMobile(self.planet, "criminal", 300, 373, 6, -2764, 333, 0)
	spawnMobile(self.planet, "criminal", 300, 470, 6, -3222, 220, 0)
	spawnMobile(self.planet, "criminal", 300, 636, 6, -2979, 141, 0)
	spawnMobile(self.planet, "fed_dub_captain", 300, 286, 6, -3106, 318, 0)
	spawnMobile(self.planet, "fed_dub_captain", 300, 718, 6, -2859, 171, 0)
	spawnMobile(self.planet, "fed_dub_captain", 300, 730, 6, -3198, 179, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 138, 6, -2978, 113, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 283, 6, -3109, 179, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 500, 6, -3192, 357, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 517, 6, -3170, 152, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 537, 6, -3197, 85, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 539, 6, -3202, 115, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 563, 6, -2911, 10, 0)
	spawnMobile(self.planet, "fed_dub_investigator", 300, 198, 6, -2794, 71, 0)
	spawnMobile(self.planet, "fed_dub_investigator", 300, 201, 6, -3099, 318, 0)
	spawnMobile(self.planet, "fed_dub_investigator", 300, 376, 6, -2923, 271, 0)
	spawnMobile(self.planet, "fed_dub_investigator", 300, 390, 6, -3184, 180, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 144, 6, -3098, 134, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 200, 6, -2794, 88, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 200, 6, -3099, 275, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 201, 6, -2796, 225, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 202, 6, -3099, 359, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 287, 6, -3107, 218, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 287, 6, -3135, 184, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 287, 6, -3136, 10, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 289, 6, -2794, -96, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 377, 6, -2923, 267, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 532, 6, -3196, 146, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 541, 6, -2994, 270, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 586, 6, -3193, 271, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 635, 6, -3182, 85, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 715, 6, -2844, 180, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 716, 6, -2866, 318, 0)

	--misc
	spawnMobile(self.planet, "informant_npc_lvl_1",0,286,6,-3101,180,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,342,6,-2896,270,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,409,6,-2867,315,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,411,6,-3056,90,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,434,6,-2821,180,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,555,6,-2958,0,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,568,6,-3173,30,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,653,6,-2850,90,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,683,6,-2898,45,0)
	spawnMobile(self.planet, "informant_npc_lvl_2",0,147,6,-2812,270,0)
	spawnMobile(self.planet, "informant_npc_lvl_2",0,203,6,-2979,180,0)
	spawnMobile(self.planet, "informant_npc_lvl_2",0,258.3,6,-3008.4,135,0)
	spawnMobile(self.planet, "informant_npc_lvl_3",0,255,6,-3024,270,0)
	spawnMobile(self.planet, "informant_npc_lvl_3",0,265,6,-2974,315,0)
	spawnMobile(self.planet, "informant_npc_lvl_3",0,682,13,-3219,180,0)
	spawnMobile(self.planet, "rebel_recruiter",60,-26,0,0,90,3175399)
	spawnMobile(self.planet, "rebel_recruiter",60,17,3,-36,0,6255475)
	spawnMobile(self.planet, "junk_dealer", 0, 183.6, 6, -3065.1, 87, 0)
	spawnMobile(self.planet, "junk_dealer", 0, 146.55, 6, -2852.41, 87, 0)
	spawnMobile(self.planet, "junk_dealer", 0, -14.4, 1.1, 2.9, 133, 3175374)
	pNpc = spawnMobile(self.planet, "junk_dealer", 0, 598.26, 6, -2949.30, -72, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerArmsConvoTemplate")
	end

	--trainers
	spawnMobile(self.planet, "trainer_1hsword",1,549,6,-2865,180,0)
	spawnMobile(self.planet, "trainer_2hsword",1,552,6,-2865,180,0)
	spawnMobile(self.planet, "trainer_architect",1,11,1,-14,0,3175561)
	spawnMobile(self.planet, "trainer_armorsmith",1,-15,1,0,90,3175560)
	spawnMobile(self.planet, "trainer_armorsmith",1,351,6,-2877,2,0)
	spawnMobile(self.planet, "trainer_artisan",1,0,1,-14,0,3175386)
	spawnMobile(self.planet, "trainer_brawler",1,-11,1,-14,0,3175377)
	spawnMobile(self.planet, "trainer_carbine",1,583,6,-2873,0,0)
	spawnMobile(self.planet, "trainer_chef",1,-11,1.1,-14,0,3175387)
	spawnMobile(self.planet, "trainer_commando",1,-3,1,-9,90,3175376)
	spawnMobile(self.planet, "trainer_dancer",1,18.0588,2.12871,53.9528,1,3175572)
	spawnMobile(self.planet, "trainer_droidengineer",1,-11,1,-13,0,3175563)
	spawnMobile(self.planet, "trainer_entertainer",1,29.7,2,73,270,3175572)
	spawnMobile(self.planet, "trainer_imagedesigner",1,-21,2,73.5,90,3175573)
	spawnMobile(self.planet, "trainer_marksman",1,0,1,-14,0,3175376)
	spawnMobile(self.planet, "trainer_marksman",1,586,6,-2873,0,0)
	spawnMobile(self.planet, "trainer_medic",1,-1.8295,0.184067,0.51949,87,3305354)
	spawnMobile(self.planet, "trainer_merchant",1,12,1,6,180,3175559)
	spawnMobile(self.planet, "trainer_merchant",1,331.5,6,-2914.5,90,0)
	spawnMobile(self.planet, "trainer_musician",1,21.6,2.1,76.0,180,3175572)
	spawnMobile(self.planet, "trainer_pistol",1,583,6,-2871,10,0)
	spawnMobile(self.planet, "trainer_polearm",1,523,6,-2934,180,0)
	spawnMobile(self.planet, "trainer_rifleman",1,587,6,-2870,0,0)
	spawnMobile(self.planet, "trainer_scout",1,-12,1,5,180,3175374)
	spawnMobile(self.planet, "trainer_scout",1,700,6,-2911,180,0)
	spawnMobile(self.planet, "trainer_smuggler",1,167,6,-2892,263,0)
	spawnMobile(self.planet, "trainer_smuggler",60,3,1,-8.5,270,3175376)
	spawnMobile(self.planet, "trainer_squadleader",1,588,6,-2934,90,0)
	spawnMobile(self.planet, "trainer_tailor",1,11,1.1,-14,45,3175385)
	spawnMobile(self.planet, "trainer_tailor",1,-12,1,6,180,3175560)
	spawnMobile(self.planet, "trainer_tailor",1,370.2,6,-2877.2,0,0)
	spawnMobile(self.planet, "trainer_unarmed",1,-22,-0.9,24,180,3175400)
	spawnMobile(self.planet, "trainer_weaponsmith",1,0,1,-14,0,3175562)
	spawnMobile(self.planet, "trainer_weaponsmith",1,519,6,-2913.5,180,0)

	--More Outside Misc
	spawnMobile(self.planet, "businessman",60,168.921,6,-2923.67,107.531,0)
	spawnMobile(self.planet, "businessman",60,212.446,6,-2833.26,295.679,0)
	spawnMobile(self.planet, "businessman",60,330.621,6,-2942.68,46.1291,0)
	spawnMobile(self.planet, "businessman",60,319.846,6,-3145.97,109.968,0)
	spawnMobile(self.planet, "businessman",60,446.267,6,-3130.33,249.001,0)
	spawnMobile(self.planet, "businessman",60,420.006,6,-2986.86,200.69,0)
	spawnMobile(self.planet, "businessman",60,504.641,6,-3046.27, 18,0)
	spawnMobile(self.planet, "businessman",60,595.655,6,-3108.96,298.007,0)
	spawnMobile(self.planet, "commoner",60,127.174,6,-2798.56,170.604,0)
	spawnMobile(self.planet, "commoner",60,161.414,6,-2868.57,162.125,0)
	spawnMobile(self.planet, "commoner",60,163.969,6,-2835.69,126.296,0)
	spawnMobile(self.planet, "commoner",60,127.295,6,-2995.11,290.038,0)
	spawnMobile(self.planet, "commoner",60,133.107,6,-3092.87,277.887,0)
	spawnMobile(self.planet, "commoner",60,156.527,6,-2960.7,69.2032,0)
	spawnMobile(self.planet, "commoner",60,197.748,6,-3065.09,200.164,0)
	spawnMobile(self.planet, "commoner",60,172.678,6,-3031.56,224.267,0)
	spawnMobile(self.planet, "commoner",60,149.764,6,-3061.44,326.219,0)
	spawnMobile(self.planet, "commoner",60,147.109,6,-3073.94,77.2345,0)
	spawnMobile(self.planet, "commoner",60,212.011,6,-2937.69,234.669,0)
	spawnMobile(self.planet, "commoner",60,280.418,6,-2806.91,62.6086,0)
	spawnMobile(self.planet, "commoner",60,221.275,6,-2803.13,196.629,0)
	spawnMobile(self.planet, "commoner",60,204.603,6,-2849.75,245.847,0)
	spawnMobile(self.planet, "commoner",60,290.803,6,-3074.21,94.2295,0)
	spawnMobile(self.planet, "commoner",60,237.39,6,-3077.78,201.248,0)
	spawnMobile(self.planet, "commoner",60,371.949,6,-3059.95,126.195,0)
	spawnMobile(self.planet, "commoner",60,353.709,6,-3051.79,286.987,0)
	spawnMobile(self.planet, "commoner",60,386.941,6,-3047.4,106.431,0)
	spawnMobile(self.planet, "commoner",60,367.172,6,-3173.12,183.221,0)
	spawnMobile(self.planet, "commoner",60,300.998,6,-2834.76,229.521,0)
	spawnMobile(self.planet, "commoner",60,461.645,6,-3102.23,29.1923,0)
	spawnMobile(self.planet, "commoner",60,465.773,6,-3227.29,259.579,0)
	spawnMobile(self.planet, "commoner",60,441.088,6,-3236.19,203.513,0)
	spawnMobile(self.planet, "commoner",60,496.362,6,-3235.3,345.662,0)
	spawnMobile(self.planet, "commoner",60,490.398,6,-3116.09,342.67,0)
	spawnMobile(self.planet, "commoner",60,414.592,6,-3050.06,165.662,0)
	spawnMobile(self.planet, "commoner",60,428.685,6,-3062.96,186.141,0)
	spawnMobile(self.planet, "commoner",60,401.557,6,-3077.13,306.839,0)
	spawnMobile(self.planet, "commoner",60,486.25,6,-3086.37,147.836,0)
	spawnMobile(self.planet, "commoner",60,496.245,6,-3023.32,306.267,0)
	spawnMobile(self.planet, "commoner",60,452.123,6,-2852.21,99.4841,0)
	spawnMobile(self.planet, "commoner",60,502.633,6,-3188.62,344.156,0)
	spawnMobile(self.planet, "commoner",60,577.79,6,-3188.06,96.2207,0)
	spawnMobile(self.planet, "commoner",60,591.985,6,-3160.63,229.416,0)
	spawnMobile(self.planet, "commoner",60,590.621,6,-3084.82,277.167,0)
	spawnMobile(self.planet, "commoner",60,583.781,6,-3122.28,36.377,0)
	spawnMobile(self.planet, "commoner",60,591.708,6,-2922.8,165,0)
	spawnMobile(self.planet, "commoner",60,582.058,6,-2861.59,201.249,0)
	spawnMobile(self.planet, "commoner",60,580.14,6,-2963.53,62.328,0)
	spawnMobile(self.planet, "commoner",60,574.069,6,-2915.3,346.28,0)
	spawnMobile(self.planet, "commoner",60,579.516,6,-3023.72,48.1011,0)
	spawnMobile(self.planet, "commoner",60,503.439,6,-2948.04,199.091,0)
	spawnMobile(self.planet, "commoner",60,628.7,6,-3182.04,146.936,0)
	spawnMobile(self.planet, "commoner",60,618.663,6,-3101.85,207.963,0)
	spawnMobile(self.planet, "commoner",60,616.017,6,-3121.62,86.0319,0)
	spawnMobile(self.planet, "commoner",60,673,6,-3098.71,244.435,0)
	spawnMobile(self.planet, "commoner",60,649.197,6,-2940.29,14.1284,0)
	spawnMobile(self.planet, "commoner",60,615.01,6,-2920.76,355.079,0)
	spawnMobile(self.planet, "commoner",60,616.103,6,-2959.56,96.5293,0)
	spawnMobile(self.planet, "commoner",60,692.188,6,-2861.6,143.991,0)
	spawnMobile(self.planet, "commoner",60,620.471,6,-2861.4,170.911,0)
	spawnMobile(self.planet, "commoner",60,639.942,6,-2913.13,154.28,0)
	spawnMobile(self.planet, "commoner",60,709.053,6,-3036.35,323.442,0)
	spawnMobile(self.planet, "commoner",60,721.819,6,-2892.41,331.474,0)
	spawnMobile(self.planet, "commoner",60,709.441,6,-2967.7,167.877,0)
	spawnMobile(self.planet, "noble",60,367.974,6,-2892.77,10.4074,0)
	spawnMobile(self.planet, "noble",60,498.882,6,-3108.57,95.7697,0)
	spawnMobile(self.planet, "noble",60,624.779,6,-2923.53,258.421,0)
	spawnMobile(self.planet, "scientist",60,426.774,6,-2863.5,106.169,0)
	spawnMobile(self.planet, "scientist",60,629.722,6,-3048.65,343.583,0)

	--Starport
	pNpc = spawnMobile(self.planet, "commoner",60,0.904988,0.639421,56.083,180.007,3175356)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "farmer",60,-1.32019,0.639422,60.6488,180.001,3175356)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "mercenary",60,-0.186001,0.639421,56.083,135.241,3175356)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "devaronian_male",60,-1.32019,0.639422,59.6488,0,3175356)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "shadowy_figure",60,0.904988,0.639421,54.983,360.011,3175356)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "businessman",60,-32.0259,1.63942,62.9678,180.006,3175361)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "farmer",60,-32.0259,1.63942,61.8678,360.011,3175361)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "noble",60,-61.2565,2.63942,40.4022,0,3175364)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "vendor",60,-61.2565,2.63942,41.5022,180.005,3175364)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "commoner_naboo",60,-62.3565,2.63942,41.5022,135.004,3175364)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "chassis_dealer",60,-56.7086,0.974563,8.24108,43.5461,3175366)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile(self.planet, "trainer_shipwright",60,0.1,0.6,73.0,0,3175353)
	self:setMoodString(pNpc, "neutral")

	--Cantina
	spawnMobile(self.planet, "bartender",60,7.8,-0.9,-1.4,119,3175391)
	spawnMobile(self.planet, "businessman",60,-5.0724,-0.894996,21.4966,284.21,3175397)
	pNpc = spawnMobile(self.planet, "medic",60,-44.5373,0.105009,-20.8963,0,3175403)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "pilot",60,-44.5373,0.104709,-19.7963,180.005,3175403)
	self:setMoodString(pNpc, "npc_consoling")
	pNpc = spawnMobile(self.planet, "agriculturalist",60,12.85,-0.894992,1.20077,360.011,3175391)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "mercenary",300,12.85,-0.894992,2.30077,180.005,3175391)
	self:setMoodString(pNpc, "npc_accusing")
	pNpc = spawnMobile(self.planet, "commoner_technician",60,18.5617,-0.894992,17.5882,360.011,3175393)
	self:setMoodString(pNpc, "nervous")
	pNpc = spawnMobile(self.planet, "vendor",60,18.5617,-0.894992,18.6882,180.006,3175393)
	self:setMoodString(pNpc, "npc_consoling")
	pNpc = spawnMobile(self.planet, "bounty_hunter",60,34.3579,0.105,2.70668,135.004,3175390)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "businessman",60,35.4579,0.105,2.70668,180.005,3175390)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "farmer",60,43.6156,0.104999,0.752079,0,3175389)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "ithorian_male",300,43.6156,0.104999,1.85208,180.005,3175389)
	self:setMoodString(pNpc, "conversation")

	--Guild Hall
	pNpc = spawnMobile(self.planet, "info_broker",60,-2.33557,1.75,-12.7738,180.008,3175434)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "brawler",60,-2.33557,1.75,-13.8738,360.011,3175434)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile(self.planet, "farmer",60,-1.18159,2.25,6.74,180.013,3175434)
	self:setMoodString(pNpc, "conversation")

	--Guild Hall/Theater
	pNpc = spawnMobile(self.planet, "chiss_male",60,-2.83063,2.6,9.88899,180.005,3175570)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "chiss_female",60,-2.9,2.6,8.2,0,3175570)
	self:setMoodString(pNpc, "happy")
	spawnMobile(self.planet, "noble",60,28.93,2.12878,58.19,222.007,3175571)
	spawnMobile(self.planet, "noble",60,19.26,2.12847,56.13,266.008,3175572)
	spawnMobile(self.planet, "theater_manager",1,22.0619,2.12821,63.5,1,3175572)

	--Hotel
	pNpc = spawnMobile(self.planet, "bounty_hunter",300,-10.227,1.00006,-2.52106,360.011,3175594)
	self:setMoodString(pNpc, "npc_accusing")
	pNpc = spawnMobile(self.planet, "brawler",60,-10.227,1.00005,-1.42106,180.007,3175594)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile(self.planet, "commoner",60,25.6926,1.28309,6.24509,0,3175593)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "contractor",60,21.574,1.28309,-2.39703,0,3175593)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "commoner_tatooine",60,21.574,1.28309,-1.29703,180.005,3175593)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "pilot",60,20.474,1.28309,-1.29703,135.003,3175593)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "scientist",60,25.6926,1.28309,7.24509,180.001,3175593)
	self:setMoodString(pNpc, "conversation")

	--Capital
	pNpc = spawnMobile(self.planet, "farmer_rancher",60,9.32783,0.3,-0.595898,180.007,6255467)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "businessman",60,8.22783,0.3,-0.595898,135.005,6255467)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile(self.planet, "sullustan_male",300,9.32783,0.3,-1.6959,360.011,6255467)
	self:setMoodString(pNpc, "conversation")
	spawnMobile(self.planet, "noble",60,22.4751,3.22324,19.4502,107.651,6255473)
	spawnMobile(self.planet, "businessman",60,-18.8153,3.22324,21.6509,252.41,6255472)

	--newb grind starter spawns
	spawnMobile(self.planet, "minor_sludge_panther", 300, getRandomNumber(10) + 83.9, 6.0, getRandomNumber(10) + -2729.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_sludge_panther", 300, getRandomNumber(10) + 83.9, 6.0, getRandomNumber(10) + -2729.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_sludge_panther", 300, getRandomNumber(10) + 83.9, 6.0, getRandomNumber(10) + -2729.6, getRandomNumber(360), 0)

	spawnMobile(self.planet, "clipped_fynock", 300, getRandomNumber(10) + 58.0, 6.0, getRandomNumber(10) + -2967, getRandomNumber(360), 0)
	spawnMobile(self.planet, "clipped_fynock", 300, getRandomNumber(10) + 58.0, 6.0, getRandomNumber(10) + -2967, getRandomNumber(360), 0)
	spawnMobile(self.planet, "clipped_fynock", 300, getRandomNumber(10) + 58.0, 6.0, getRandomNumber(10) + -2967, getRandomNumber(360), 0)
	spawnMobile(self.planet, "clipped_fynock", 300, getRandomNumber(10) + 58.0, 6.0, getRandomNumber(10) + -2967, getRandomNumber(360), 0)
	spawnMobile(self.planet, "clipped_fynock", 300, getRandomNumber(10) + 58.0, 6.0, getRandomNumber(10) + -2967, getRandomNumber(360), 0)

	spawnMobile(self.planet, "song_rasp", 300, getRandomNumber(10) + 78.7, 5.9, getRandomNumber(10) + -3059, getRandomNumber(360), 0)
	spawnMobile(self.planet, "song_rasp", 300, getRandomNumber(10) + 78.7, 5.9, getRandomNumber(10) + -3059, getRandomNumber(360), 0)
	spawnMobile(self.planet, "song_rasp", 300, getRandomNumber(10) + 78.7, 5.9, getRandomNumber(10) + -3059, getRandomNumber(360), 0)
	spawnMobile(self.planet, "song_rasp", 300, getRandomNumber(10) + 78.7, 5.9, getRandomNumber(10) + -3059, getRandomNumber(360), 0)

	spawnMobile(self.planet, "docile_kahmurra", 300, getRandomNumber(10) + 225.8, 6.0, getRandomNumber(10) + -3157, getRandomNumber(360), 0)
	spawnMobile(self.planet, "docile_kahmurra", 300, getRandomNumber(10) + 225.8, 6.0, getRandomNumber(10) + -3157, getRandomNumber(360), 0)
	spawnMobile(self.planet, "docile_kahmurra", 300, getRandomNumber(10) + 225.8, 6.0, getRandomNumber(10) + -3157, getRandomNumber(360), 0)
	spawnMobile(self.planet, "docile_kahmurra", 300, getRandomNumber(10) + 225.8, 6.0, getRandomNumber(10) + -3157, getRandomNumber(360), 0)
end
