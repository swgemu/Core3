CorelliaKorVellaScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CorelliaKorVellaScreenPlay",

	planet = "corellia",

	gcwMobs = {
		--swap spawns for imp base near starport at outskirts of city limits
		{"stormtrooper", "rebel_trooper", -3001.5, 31.0, 2930.4, 180, 0, "", ""},
		{"stormtrooper", "rebel_trooper", -3003.5, 31.0, 2930.4, 180, 0, "", ""},
		{"stormtrooper", "rebel_trooper", -3007.5, 31.0, 2930.4, 180, 0, "", ""},
		{"stormtrooper", "rebel_trooper", -3003.5, 31.0, 2926.4, 180, 0, "", ""},
		{"stormtrooper", "rebel_trooper", -3007.5, 31.0, 2926.4, 180, 0, "", ""},
		{"stormtrooper", "rebel_trooper", -3003.5, 31.0, 2922.4, 180, 0, "", ""},
		{"stormtrooper", "rebel_trooper", -2992.1, 30.9, 2913.5, -125, 0, "", ""},
		{"stormtrooper", "rebel_trooper", -2992.1, 30.9, 2903.5, -55, 0, "", ""},
		{"stormtrooper", "rebel_trooper", 3.7, 0.3, 1.1, 0, 1331934, "", ""},
		{"stormtrooper", "rebel_trooper", 3.7, 0.3, -2.3, 0, 1331934, "", ""},
		{"stormtrooper", "rebel_trooper", -3.4, -3.3, 5.2, 180, 1331936, "", ""},
		{"stormtrooper", "rebel_trooper", 1.3, -6.7, -6.0, 45, 1331937, "", ""},
		{"stormtrooper", "rebel_trooper", 7.3, -6.7, -6.0, -45, 1331937, "", ""},
		{"stormtrooper", "rebel_trooper", -5.1, -13.7, 7.5, 180, 1331939, "", ""},
		{"stormtrooper", "rebel_trooper", -1.9, -13.7, 7.5, 180, 1331939, "", ""},
		{"stormtrooper_medic", "rebel_medic", -5.7, -13.8, 13.8, -33, 1331940, "", ""},
		{"imperial_second_lieutenant", "rebel_second_lieutenant", 16.0, -13.8, 9.6, 180, 1331941, "", ""},
		{"imperial_trooper", "rebel_crewman", 17.0, -13.8, -2.5, -45, 1331941, "", ""},
		{"imperial_major_general", "rebel_major_general", 15.1, -11.5, -20.8, 0, 1331942, "", ""},
		{"stormtrooper_medic", "rebel_medic", 0.2, 0.1, -5.1, 0, 1331946, "", ""},
		{"imperial_major", "rebel_major", 4.6, 0.1, -2.1, -135, 1331948, "", ""},
		{"stormtrooper", "rebel_trooper", -0.2, 0.1, 1.3, -90, 1331953, "", ""},
		{"imperial_colonel", "rebel_colonel", 4.6, 0.1, -2.1, -135, 1331955, "", ""},

		--faction swap spawns for in the city itself
		{"imperial_noncom", "specforce_interrogator", -3660.31, 86, 3103.26, 39.0513, 0, "", ""},
		{"dark_trooper", "rebel_commando", -3773.66, 86, 3203.13, 22.9816, 0, "", ""},
		{"imperial_private", "rebel_corporal", -3387, 86, 2960, 95, 0, "", ""},
		{"imperial_private", "rebel_corporal", -3404.35, 74, 3347.14, 188, 0, "", ""},
		{"imperial_first_lieutenant", "rebel_first_lieutenant", -3662.58, 86, 3090.82, 101, 0, "", "", true},
		{"imperial_first_lieutenant", "rebel_first_lieutenant", -3074, 31, 2825, 235, 0, "", ""},
		{"imperial_first_lieutenant", "rebel_first_lieutenant", -3674.98, 86, 3104.95, 180, 0, "", "", true},
		{"imperial_sergeant", "rebel_sergeant", -3435, 86, 3034, 90, 0, "", ""},
		{"imperial_sergeant", "rebel_sergeant", -3424, 86, 3018, 30, 0, "", ""},
		{"imperial_sergeant", "rebel_sergeant", -3368.45, 86, 3242.5, 216, 0, "", "", true},
		{"imperial_sergeant", "rebel_sergeant", -3366, 86, 3232, 166, 0, "", ""},
		{"imperial_sergeant", "rebel_sergeant", -3582, 86, 3143, 333, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3621.27, 86, 3142.55, 28.2333, 0, "", "", true},
		{"stormtrooper", "rebel_crewman", -3631.32, 86, 3136.46, 252.779, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3410.43, 86, 3142.78, 151.613, 0, "", "", true},
		{"stormtrooper", "rebel_crewman", -3406.24, 86, 3137.43, 204.684, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3395.4, 86, 3017.79, 72.2994, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3395.16, 86, 3023.07, 57.428, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3344.8, 80.6241, 3240.26, 200.272, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3343.2, 81.762, 3240.54, 177.569, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3767.99, 86, 3180.85, 154.813, 0, "", "", true},
		{"stormtrooper", "rebel_crewman", -3761.11, 86, 3190.17, 63.2948, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3411.64, 74, 3344.7, 179.356, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3416.53, 74, 3346.57, 326.897, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3157.47, 31, 2797.69, 352.434, 0, "", "", true},
		{"stormtrooper", "rebel_crewman", -3155.56, 31, 2792.15, 348.853, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3425, 86, 3034, 90, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3368.29, 86, 2949.6, 170.619, 0, "", "", true},
		{"stormtrooper", "rebel_crewman", -3420, 86, 3034, 90, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3430, 86, 3070, 0, 0, "", "", true},
		{"stormtrooper", "rebel_crewman", -3430, 86, 3065, 0, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3430, 86, 3060, 0, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3430, 86, 3050, 0, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3381.8, 86, 3298.1, -79, 0, "", "", true},
		{"stormtrooper", "rebel_crewman", -3719.35, 86, 3175.2, 326.578, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3595.9, 86, 3172.4, 152, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3619.55, 86, 3121.89, 113.533, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3612.9, 86, 3130.8, 95, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3726.46, 86, 3185.97, 120.721, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3754, 86, 3172, -30, 0, "", ""},
		{"stormtrooper", "rebel_crewman", -3774.9, 86, 3203.38, 281.283, 0, "", "", true},
		{"stormtrooper", "rebel_crewman", -3774.65, 86, 3204.62, 22.9721, 0, "", ""},
		{"stormtrooper_medic", "rebel_medic", -3112, 31, 2814, 168, 0, "", ""},
		{"stormtrooper_medic", "rebel_medic", -3386, 86, 2992, 354.507, 0, "", ""},
		{"stormtrooper_sniper", "rebel_scout", -3093, 31.0391, 2803, 347.01, 0, "", ""},
		{"stormtrooper_sniper", "rebel_scout", -3460.41, 78, 3112.21, 232.636, 0, "", ""},
		{"stormtrooper_sniper", "rebel_scout", -3430, 86, 3055, 0, 0, "", ""},
		{"stormtrooper_sniper", "rebel_scout", -3318.03, 86, 3230.13, 115.958, 0, "", ""},
		{"stormtrooper_sniper", "rebel_scout", -3326.35, 86, 3231.94, 52.9842, 0, "", ""},
		{"stormtrooper_sniper", "rebel_scout", -3602.47, 86, 3214.02, 44.6678, 0, "", "", true},
		{"stormtrooper_sniper", "rebel_scout", -3613.06, 86, 3212.07, 47.9151, 0, "", ""},
		{"stormtrooper_sniper", "rebel_scout", -3715.75, 86.0549, 3169.75, 326.9, 0, "", ""},
		{"corsec_detective", "corsec_detective", -3408.26, 86, 3049.35, 180, 0, "", ""},
		{"corsec_investigator", "corsec_investigator", -3520.73, 78, 3125.57, 0, 0, "", ""},
		{"corsec_investigator", "corsec_investigator", -3102.24, 31, 2988.47, 266, 0, "", ""},
		{"corsec_lieutenant", "corsec_lieutenant", -3587.81, 86, 3135.7, 180, 0, "", ""},
		{"corsec_lieutenant", "corsec_lieutenant", -3450.64, 78, 3031.31, 180, 0, "", ""},
		{"corsec_sergeant", "corsec_sergeant", -3149.45, 31, 2771.7, 282.9, 0, "", ""},
		{"corsec_agent", "corsec_agent", -3151.32, 31, 2772.13, 282.871, 0, "", ""},
		{"corsec_trooper", "corsec_trooper", -3103.98, 31, 2988.38, 266.9, 0, "", ""},
		{"corsec_trooper", "corsec_trooper", -3102.95, 31, 2989.56, 266.9, 0, "", ""},
		{"corsec_major", "corsec_major", -3150.16, 31.1, 2773.0, 282, 0, "", ""},
	},

	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "noble_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"r2_1", "r2", -3697.43, 86.1, 3141.62, 327.074, 0, "", false},
		{"r3_1", "r3", -3423.05, 78.15, 3333.75, 253.023, 0, "", false},
		{"r3_2", "r3", -3327.95, 86, 3233.64, 315.946, 0, "", false},
		{"r3_3", "r3", -3157, 31, 2802, 265.951, 0, "", false},
		{"r5_1", "r5", -3094.48, 31, 2972.63, 268.321, 0, "", false},
		{"r5_2", "r5", -3134.32, 31, 2801.71, 82.3858, 0, "", false},
		{"cll8_1", "cll8_binary_load_lifter", -3654.48, 86, 3081.81, 26.971, 0, "", false},
		{"cll8_2", "cll8_binary_load_lifter", -3449, 78, 3378, 359.013, 0, "", false},
		{"cll8_3", "cll8_binary_load_lifter", -3038, 31, 2988, 81.028, 0, "", false},
		{"eg6_1", "eg6_power_droid", -3766.44, 86, 3180.9, 54.4, 0, "", false},

		--NPCs
		{"npc_1", "patrolNpc", -3200, 30, 2786, 349, 0, "", false},
		{"npc_2", "patrolNpc", -3115, 31, 2800, 30, 0, "", false},
		{"npc_3", "patrolNpc", -3066, 31, 2925, 132, 0, "", false},
		{"npc_4", "patrolNpc", -3131, 31, 2995, 134, 0, "", false},
		{"npc_5", "patrolNpc", -3296, 66, 2877, 186, 0, "", false},
		{"npc_6", "patrolNpc", -3384, 86, 2958, 11, 0, "", false},
		{"npc_7", "patrolNpc", -3393, 86, 3007, 286 ,0, "", false},
		{"npc_8", "patrolNpc", -3426, 86, 3134, 343, 0, "", false},
		{"npc_9", "patrolNpc", -3378, 86, 3173, 240, 0, "", false},
		{"npc_10", "patrolNpc", -3351, 86, 3303, 24, 0, "", false},
		{"npc_11", "patrolNpc", -3572, 70, 3208, 214, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		r2_1 = {{-3699, 86, 3140, 0, false}, {-3720, 86, 3180, 0, false}, {-3723, 86, 3178, 0, false}, {-3686, 86, 3115, 0, true}, {-3685, 86, 3104, 0, false}, {-3686, 86, 3115, 0, true}},
		r3_1 = {{-3423, 78, 3333, 0, false}, {-3428, 78, 3323, 0, true}, {-3436, 78, 3247, 0, false}, {-3428, 78, 3323, 0, true}},
		r3_2 = {{-3328, 86, 3235, 0, false}, {-3336, 86, 3210, 0, false}, {-3370, 85, 3215, 0, false}, {-3371, 86, 3272, 0, true}, {-3370, 85, 3215, 0, true}, {-3336, 86, 3210, 0, true}},
		r3_3 = {{-3157, 31, 2802, 0, true}, {-3176, 31, 2797, 0, false}, {-3165, 31, 2809, 0, false}},
		r5_1 = {{-3094, 31, 2972, 0, false}, {-3150, 31, 2998, 0, false}},
		r5_2 = {{-3142, 31, 2805, 0, false}, {-3137, 31, 2809, 0, false}, {-3113, 31, 2804, 0, false}, {-3048, 30, 2832, 0, false}, {-3113, 31, 2804, 0, false}},
		cll8_1 = {{-3654, 86, 3081, 0, false}, {-3641, 86, 3126, 0, true}, {-3591, 86, 3157, 0, false}, {-3641, 86, 3126, 0, false}},
		cll8_2 = {{-3453, 78, 3350, 0, false}, {-3436, 78, 3479, 0, false}},
		cll8_3 = {{-3038, 31, 2988, 0, false}, {-3021, 31, 2908, 0, false}, {-3038, 31, 2988, 0, false}, {-3054, 31, 2985, 0, true}, {-3091, 31, 2975, 0, false}},
		eg6_1 = {{-3766, 86, 3180, 0, false}, {-3770, 86, 3192, 0, false}, {-3755, 86, 3220, 0, false}, {-3745, 86, 3198, 0, false}},

		npc_1 = {{-3200, 30, 2786, 0, true}, {-3249, 36, 2819, 0, true}, {-3272, 53, 2855, 0, true}, {-3193, 30, 2772, 0, true}},
		npc_2 = {{-3115, 31, 2800, 0, true}, {-3112, 31, 2785, 0, true}, {-3078, 31, 2813, 0, true}, {-3119, 31, 2795, 0, true}},
		npc_3 = {{-3066, 31, 2925, 0, true}, {-3072, 31, 2941, 0, true}, {-3052, 31, 2918, 0, true}, {-3062, 31, 2888, 0, true}},
		npc_4 = {{-3131, 31, 2995, 0, true}, {-3094, 31, 2991, 0, true}, {-3099, 31, 2982, 0, true}, {-3141, 31, 3009, 0, true}},
		npc_5 = {{-3296, 66, 2877, 0, true}, {-3299, 66, 2875, 0, true}, {-3315, 70, 2899, 0, true}, {-3342, 71, 2913, 0, true}, {-3307, 69, 2887, 0, true}},
		npc_6 = {{ -3384, 86, 2958, 0, true}, {-3381, 86, 2973, 0, true}, {-3390, 86, 2986, 0, true}},
		npc_7 = {{-3393, 86, 3007, 0, true}, {-3407, 86, 3017, 0, true}, {-3407, 86, 3040, 0, true}, {-3420, 86, 3050, 0, true}},
		npc_8 = {{-3426, 86, 3134, 0, true}, {-3431, 86, 3118, 0, true}, {-3436, 86, 3103, 0, true}, {-3452, 86, 3138, 0, true}, {-3448, 86, 3154, 0, true}, {-3439, 86, 3134, 0, true}},
		npc_9 = {{-3378, 86, 3173, 0, true}, {-3388, 86, 3163, 0, true}, {-3279, 86, 3114, 0, false}, {-3364, 86, 3151, 0, true}},
		npc_10 = {{-3351, 86, 3303, 0, true}, {-3367, 86, 3296, 0, true}, {-3354, 86, 3294, 0, true}, {-3343, 86, 3308, 0, true}, {-3350, 86, 3307, 0, true}},
		npc_11 = {{ -3572, 70, 3208, 0, true}, {-3548, 70, 3219, 0, true}, {-3528, 70, 3233, 0, true}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old"},
	stationaryNpcs = {"artisan", "bodyguard", "bothan_diplomat", "bounty_hunter", "businessman", "commoner_technician", "contractor", "entertainer", "explorer", "farmer", "farmer_rancher", "fringer", "gambler", "info_broker", "medic", "mercenary", "miner", "noble", "official", "pilot", "rancher", "scientist", "slicer"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, -3587.81, 86, 3134.7, 0, 0, ""},
		{1, -3162.17, 31, 2902.28, 0, 0, ""},
		{1, -3088.9, 31, 2902.08, 0, 0, ""},
		{1, -3557.49, 86, 3158.11, 180.005, 0, ""},
		{1, -3459.55, 78, 3226.02, 180, 0, ""},
		{1, -3591.74, 86, 3180.01, 180, 0, ""},
		{1, -3159.35, 31, 2813.02, 0, 0, ""},
		{1, -3152.32, 31, 2971.71, 0, 0, ""},
		{1, -3522.13, 70, 3234.57, 298, 0, ""},
		{1, -3509.45, 78, 3148.97, 307, 0, ""},
		{1, -3447.57, 78, 3219.08, 209, 0, ""},
		{1, -3455.84, 78, 3343.36, 116, 0, ""},
		{1, -3427.62, 86, 3029.21, 95, 0, ""},
		{1, -3423.54, 86, 3043.61, 131, 0, "conversation"},
		{1, -3403.44, 86, 2997.65, 182, 0, ""},
		{1, -3403.21, 86, 3111.2, 47, 0, "conversation"},
		{1, -3402.2, 86, 3111.9, 225, 0, "conversation"},
		{1, -3459.9, 86, 3156.7, 255, 0, "conversation"},
		{1, -3422, 86, 3042, 318, 0, "conversation"},
		{1, -3458.31, 78, 3027.47, 275, 0, ""},
		{1, -3461.07, 86, 3156, 54, 0, "conversation"},
		{1, -3421.3, 86, 3104.47, 296, 0, ""},
		{1,-3361.13,86,3217.26,124.012,0, ""},
		{1,-3324.59,86,3261.86,293.486,0, ""},
		{1,-3322.1,86,3230.47,113.222,0, ""},
		{1,-3342.65,86,3268.3,214.421,0, ""},
		{1,-3365.89,86,3284.68,46.8022,0, ""},
		{1,-3374.97,86,3265.02,47.337,0, ""},
		{1, -3332.16,86,3307.2,264.653,0, ""},
		{1,-3322.3,86,3283.63,275.608,0, ""},
		{1,-3378.96,86,2985.53,285.729,0, ""},
		{1,-3311.8,69.6204,2886.94,40.0687,0, ""},
		{1,-3396.89,86,3131.64,45,0, "conversation"},
		{1,-3395.09, 86, 3131.9, 231, 0, "conversation"},
		{1,-3225.11,32.2567,2816.51,180,0, ""},
		{1,-3276.7,86,3089.82,195.888,0, ""},
		{1,-3256,86,3124.3,90.73,0, ""},
		{1,-3272.53,86,3071.96, 315, 0, ""},
		{1,-3177.4, 30, 2775.1, 285,0, ""},
		{1, -3178.84, 31, 2775.92, 100, 0, ""},
		{1,-3157.04,101,3077.75,219.742,0, ""},
		{1,-3191.67,101,3052.4,294.559,0, ""},
		{1,-3190.54,101,3073.46,88.2138,0, ""},
		{1, -3185.75,101,3104.64,308.461,0, ""},
		{1,-3153.75,101,3112.41,31.6067,0, ""},
		{1,-3188.79,101,3156.71,306.911,0, ""},
		{1,-3068.52,30.6373,2772.26,154.712,0, ""},
		{1,-3028.15,29.9485,2793.83,126.824,0, ""},
		{1,-3087.72,31,2984.93,5.4138,0, ""},
		{1, -3172.38, 31, 2881.95, 180, 0, ""},
		{1, -3101.09, 31, 2904.87, 0, 0, ""},
		{1, -3713.14, 86, 3105.66, 0, 0, ""},
		{1, -3610.27, 86, 3198.4, 0, 0, ""},
		{1, -3163.27, 31, 2903.38, 135.0, 0, ""},
		{1, -3159.35, 31, 2814.02, 180, 0, ""},
		{1, -3713.14, 86, 3106.66, 180.0, 0, ""},
		{1, -3408.26, 86, 3048.35, 0, 0, ""},
		{1, -3090, 31, 2903.18, 135.0, 0, ""},
		{1, -3520.73, 78, 3126.57, 180, 0, ""},
		{1, -3162.17, 31, 2903.38, 180, 0, ""},
		{1, -3163.27, 31, 2902.28, 45, 0, ""},
		{1, -3610.27, 86, 3199.4, 180, 0, ""},
		{1, -3459.55, 78, 3225.02, 0, 0, ""},
		{1, -3095.48, 31, 2971.63, 0, 0, ""},
		{1, -3384.54, 86, 3008.15, 180, 0, ""},
		{1, -3450.64, 78, 3030.31, 0, 0, ""},
		{1, -3384.54, 86, 3007.15, 0, 0, ""},
		{1, -3152.32, 31, 2972.71, 180, 0, ""},
		{1, -3088.9, 31, 2903.18, 180, 0, ""},
	},

	mobiles = {
		--side starport room
		{"bounty_hunter",60,-33.5,1.6,49.2,-88,4255428, "sad"},
		--starport interior
		{"trainer_shipwright",60,-0.1,0.6,67.4,176,4255423, "neutral"},

		--corsec not in buildings
		{"chiss_male", 360, -3101.09, 31, 2905.97, 180, 0, ""},
		{"corellia_times_reporter", 360, -3100.88, 31, 2890.25, 180, 0, ""},
		{"ithorian_male", 360, -3177.78, 31, 2889.93, 0, 0, ""},
		{"medic", 360, -3172.38, 31, 2880.85, 0, 0, ""},
		{"rogue_corsec_trooper", 360, -3340.49, 86, 3292.76, 100.151, 0, ""},
		{"rogue_corsec_trooper", 360, -3332.89, 86, 3303.69, 68.6738, 0, ""},
		{"rogue_corsec_trooper", 360, -3330.1, 86, 3290.98, 104.099, 0, ""},
		{"sullustan_male", 360, -3177.78, 31, 2891.03, 180, 0, ""},

		--misc
		{"informant_npc_lvl_1", 10, -3563, 86, 3138, 60, 0, ""},
		{"informant_npc_lvl_1", 10, -3571, 86, 3176, 60, 0, ""},
		{"informant_npc_lvl_1", 10, -3574, 86, 3154, 315, 0, ""},
		{"informant_npc_lvl_1", 10, -3604, 86, 3172, 90, 0, ""},
		{"informant_npc_lvl_1", 10, -3665, 86, 3139, 170, 0, ""},
		{"informant_npc_lvl_1", 10, -3375, 86, 3281, 90, 0, ""},
		{"informant_npc_lvl_1", 10, -3358, 86, 3307, 140, 0, ""},
		{"informant_npc_lvl_1", 10, -3315, 86, 3234, 270, 0, ""},
		{"informant_npc_lvl_1", 10, -3386, 85.6, 3184, 90, 0, ""},
		{"informant_npc_lvl_1", 10, -3444, 78, 3231, 225, 0, ""},
		{"informant_npc_lvl_1", 10, -3458, 85.9, 3165, 90, 0, ""},
		{"informant_npc_lvl_1", 10, -3416, 86, 3078, 0, 0, ""},
		{"informant_npc_lvl_1", 10, -3401, 86, 3034, 270, 0, ""},
		{"informant_npc_lvl_1", 10, -3124, 31, 2808, 180, 0, ""},
		{"informant_npc_lvl_1", 10, -3128, 31, 3008, 180, 0, ""},
		{"medic", 60, -3591.74, 86, 3179.01, 0, 0, ""},
		{"junk_dealer", 10, -3130.41, 31, 2973.96, 0, 0, ""},

		--commoners
		{"entertainer", 60, -16.9034, 1.6, 11.8646, 180, 3005672, ""},
		{"entertainer", 60, -3602.67, 86, 3221.17, 0, 0, ""},
		{"entertainer", 60, -3100.88, 31, 2889.15, 0, 0, ""},

		--Trainers not in buildings
		{"trainer_1hsword", 1, -3320, 86, 3220, 0, 0, ""},
		{"trainer_2hsword", 1, -3374, 86, 3285, 87, 0, ""},
		{"trainer_artisan", 1, -3164, 31, 2791, 0, 0, ""},
		{"trainer_brawler", 1, -3124, 31, 2791, 0, 0, ""},
		{"trainer_brawler", 1, -3193, 31, 2799, -129, 0, ""},
		{"trainer_chef", 1, -3147, 31, 2792, 0, 0, ""},
		{"trainer_commando", 1, -3344, 86, 3292, 0, 0, ""},
		{"trainer_entertainer", 1, -3152, 31, 2807, 178, 0, ""},
		{"trainer_marksman", 1, -3130, 31, 2791, 0, 0, ""},
		{"trainer_medic", 1, -3139, 31, 2792, 0, 0, ""},
		{"trainer_polearm", 1, -3412, 86, 3084, 0, 0, ""},
		{"trainer_scout", 1, -3164.42, 31, 2802.08, 78, 0, ""},
		{"trainer_unarmed", 1, -3570, 86, 3146, 233, 0, ""},

		--named npc's
		{"dac_axfow", 60, -3143.7, 31, 2803.73, 233.156, 0, ""},
		{"eryk_chinn", 60, -3145.32, 31, 2803.95, 208.286, 0, ""},
		{"logro_elsin", 60, -3144.67, 31, 2806.06, 174, 0, ""},

		--Building Interiors
		--Starport
		{"contractor", 60, 0.68378, 0.639421, 62.1666, 180, 4255423, ""},
		{"sullustan_male", 60, 45.99, -0.52, 35.85, 180, 4255426, ""},
		{"medic", 60, 45.99, -0.52, 34.75, 0, 4255426, ""},
		{"mercenary", 300, 44.8927, -0.52, 35.85, 135, 4255426, ""},
		{"medic", 60, -62.23, 2.64, 40.83, 180, 4255431, ""},
		{"corellia_times_reporter", 300, -62.23, 2.64, 39.73, 0.19, 4255431, ""},
		{"chassis_dealer", 60, -56.71, 0.97, 8.33, 12.61, 4255433, ""},
		{"gambler", 60, 0.68378, 0.639421, 61.0666, 268.449, 4255423, "calm"},

		--Hotel
		{"zhanks", 60, 1.25, 1.0, 6.9, 340, 3005670, ""},
		{"ta_667", 60, -0.52, 1.0, 6.4, 13.75, 3005670, ""},
		{"commoner", 1, 20.5, 1.28, 10, 135, 3005671, ""},
		{"entertainer", 60, 21.6, 1.28, 8.94, 0, 3005671, ""},
		{"farmer_rancher", 60, 21.6, 1.28, 10.04, 180, 3005671, ""},

		--Cantina
		{"comm_operator", 400, 48.13, 0.1, 2.47, 292, 3005397, ""},
		{"artisan", 60, 34.4, 0.1, -8.04, 0, 3005398, ""},
		{"mercenary", 300, 34.4, 0.1, -6.9, 180, 3005398, ""},
		{"trainer_entertainer", 1, 26.2, -0.9, 10.25, 260, 3005399, ""},
		{"bartender", 60, 6.4, -0.9, -2.3, 156, 3005399, ""},
		{"corellia_times_investigator", 300, 20.6, -0.9, -18.6, 180, 3005400, ""},
		{"commoner_technician", 300, 20.6, -0.9, -19.6, 0, 3005400, ""},
		{"brawler", 60, 22.6, -0.9, 19.6, 0, 3005401, ""},
		{"commoner", 60, 21.5, -0.9, 20.7, 135, 3005401, ""},
		{"farmer_rancher", 300, 22.6, -0.9, 20.7, 180, 3005401, ""},
		{"farmer", 60, 10.9, -0.9, -13.9, 180, 3005402, ""},
		{"mercenary", 300, 10.9, -0.9, -15.0, 0, 3005402, ""},
		{"brawler", 60, -2.4, -0.9, 24.5, 180, 3005405, ""},
		{"shadowy_figure", 60, -2.4, -0.9, 23.4, 0, 3005405, ""},
		{"commoner_tatooine", 300, -25.7, -0.5, 10.5, 0, 3005409, ""},
		{"bounty_hunter", 60, -25.7, -0.5, 11.5, 180, 3005409, ""},
		{"commoner_naboo", 300, -45.2, 0.1, -20.7, 180, 3005411, ""},
		{"commoner", 60, -45.2, 0.1, -21.7, 0, 3005411, ""},

		--Guild Hall (-3435,3196, ""},
		{"trainer_tailor", 0, 11, 1.1, -14, 0, 2955415, ""},
		{"mercenary", 300, 3.29, 1.1, -9.58, 249, 2955416, ""},
		{"trainer_artisan", 0, 0, 1.1, -14, 0, 2955416, ""},
		{"trainer_chef", 0, -11, 1.1, -14, 0, 2955417, ""},

		--Guild Hall (-3412,3364, ""},
		{"trainer_scout", 0, -12, 1.13, 5.5, 180, 2955424, ""},
		{"trainer_marksman", 0, 0, 1.13, -14, 0, 2955426, ""},
		{"trainer_brawler", 0, -11, 1.13, -14, 0, 2955427, ""},
		{"junk_dealer", 0, -14.5, 1.1, 2.5, 88, 2955424, ""},
		--Cloning Facility
		{"info_broker", 60, 4.47, -0.05, 2.9, 135, 3005428, ""},
		{"medic", 60, 5.57, -0.05, 2.9, 180, 3005428, ""},
		{"medic", 300, 3.9, -0.05, -3.15, 0, 3005428, ""},
		{"scientist", 60, 5.57, -0.05, 1.84, 0, 3005428, ""},
		{"farmer", 60, 3.98, -0.05, -2.04, 180, 3005428, ""},
		{"contractor", 60, 3.19, -5.5, -6.32, 180, 3005430, ""},
		{"brawler", 60, 2.09, -5.5, -6.32, 135, 3005430, ""},
		{"businessman", 60, 3.19, -5.5, -7.42, 0, 3005430, ""},
		{"artisan", 300, -5.69, -5.5, -9.21, 180, 3005430, ""},
		{"farmer_rancher", 60, -5.69, -5.5, -10.31, 0, 3005430, ""},

		--Guild Hall (-3680,3081, ""},
		{"trainer_merchant", 0, 12, 1.13, 6, 180, 2955398, ""},
		{"trainer_armorsmith", 0, -12, 1.1, 5, 180, 2955399, ""},
		{"trainer_architect", 0, 11, 1.13, -14, 0, 2955400, ""},
		{"trainer_weaponsmith", 0, -2.5, 1.13, -8.4, 91, 2955401, ""},
		{"trainer_droidengineer", 0, -11, 1.13, -14, 0, 2955402, ""},

		--Medical Center
		{"trainer_doctor", 0, 12, 0.18, -1, 0, 3375392, ""},
		{"trainer_medic", 0, -12.65, 0.18, 2.17, 111, 3375392, ""},
		{"commoner", 60, -0.84, 0.18, 1.59, 270, 3375392, ""},
		{"medic", 60, -2.84, 0.18, 1.59, 90, 3375392, ""},
		{"twilek_slave", 300, 0.28, 0.18, 7.39, 0, 3375392, ""},
		{"chiss_female", 60, 0.28, 0.18, 8.39, 180, 3375392, ""},
		{"commoner_old", 400, -11.7, 0.18, -13.7, 90, 3375393, ""},
		{"ithorian_male", 400, -9.9, 0.18, -13.1, 168, 3375393, ""},
		{"r2", 60, -1.84202, 0.184067, 2.59886, 22.229, 3375392, "calm"}
	}
}

registerScreenPlay("CorelliaKorVellaScreenPlay", true)

function CorelliaKorVellaScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnSceneObjects()
		self:spawnGcwMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
	end
end

function CorelliaKorVellaScreenPlay:spawnSceneObjects()
	--outside starport
	spawnSceneObject(self.planet, "object/tangible/crafting/station/public_space_station.iff", -3118.55, 31, 2783.4, 0, math.rad(90) )
end

function CorelliaKorVellaScreenPlay:spawnMobiles()
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

	--thugs
	spawnMobile(self.planet, "ragtag_kook", 300, -3816.4, 86, 3114.2, 103, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3814.6, 86, 3109.6, 58, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3809.9, 86, 3111.1, -46, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3809.5, 86, 3117.4, -115, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3801.2, 86, 3251.2, 12, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3797.2, 86, 3251.1, 67, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3793.2, 86, 3255.3, -73, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3797.9, 86, 3259.9, -170, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3717.2, 86, 3074.9, 29, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3712.6, 86, 3073.8, 104, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3711.0, 86, 3077.6, -38, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3714.8, 86, 3079.9, 19, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3602.3, 86, 3105.7, -69, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3602.5, 86, 3107.6, 2, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3598.4, 86, 3107.5, -90, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3599.5, 86, 3112.2, 132, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3602.1, 86, 3115.1, -170, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3632.6, 86, 3232.5, 51, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3630.2, 86, 3236.7, 104, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3630.0, 86, 3232.6, -57, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3500.5, 78, 3148.0, 107, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3500.8, 78, 3145.0, 114, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3494.1, 78, 3140.4, -53, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3495.8, 78, 3146.1, -88, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3496.7, 78, 3138.3, 2, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3499.1, 70, 3239.0, 1, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3495.3, 70, 3240.8, 8, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3495.8, 70, 3243.1, -100, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3497.5, 70, 3245.9, -83, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3501.7, 70, 3244.5, 162, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3467.7, 85.6, 3182.2, 74, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3467.6, 85.9, 3175.1, 15, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3461.5, 85.4, 3179.1, -53, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3462.3, 85.1, 3186.0, 18, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3309.4, 86, 3285.4, -141, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3309.9, 86, 3281.3, -103, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3309.5, 86, 3276.9, -99, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3314.0, 86, 3277.9, 16, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3631.5, 86, 3117.4, -67, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3637.5, 86, 3114.4, 22, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3634.5, 86, 3119.4, -167, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3630.5, 86, 3119.4, -30, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3162.3, 31, 2999.6, 64, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3160.5, 31, 3001.3, 47, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3157.2, 31, 2999.4, 145, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3158.8, 31, 2994.4, -29, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3161.8, 31, 2991.5, -109, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3417.7, 86, 3118.9, 112, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3421.1, 86, 3120.9, 157, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3424.7, 86, 3115.9, -25, 0)
	spawnMobile(self.planet, "ragtag_kook", 300, -3420.1, 86, 3112.9, 148, 0)

	--Creatures
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3286, 101,getRandomNumber(10) + 2986, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3286, 101,getRandomNumber(10) + 2986, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3286, 101,getRandomNumber(10) + 2986, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3286, 101,getRandomNumber(10) + 2986, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3286, 101,getRandomNumber(10) + 2986, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3286, 101,getRandomNumber(10) + 2986, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3177, 101,getRandomNumber(10) + 3084, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3177, 101,getRandomNumber(10) + 3084, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3177, 101,getRandomNumber(10) + 3084, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3177, 101,getRandomNumber(10) + 3084, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3177, 101,getRandomNumber(10) + 3084, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3177, 101,getRandomNumber(10) + 3084, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3249, 101, getRandomNumber(10) + 3308, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3249, 101, getRandomNumber(10) + 3308, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3249, 101, getRandomNumber(10) + 3308, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3249, 101, getRandomNumber(10) + 3308, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3249, 101, getRandomNumber(10) + 3308, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3249, 101, getRandomNumber(10) + 3308, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3335, 101, getRandomNumber(10) + 3383, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3335, 101, getRandomNumber(10) + 3383, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3335, 101, getRandomNumber(10) + 3383, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3335, 101, getRandomNumber(10) + 3383, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3335, 101, getRandomNumber(10) + 3383, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3335, 101, getRandomNumber(10) + 3383, getRandomNumber(360), 0)
	spawnMobile(self.planet, "verne", 300, getRandomNumber(10) + -3389, 37, getRandomNumber(10) + 3531, getRandomNumber(360), 0)
	spawnMobile(self.planet, "verne", 300, getRandomNumber(10) + -3389, 37, getRandomNumber(10) + 3531, getRandomNumber(360), 0)
	spawnMobile(self.planet, "verne", 300, getRandomNumber(10) + -3389, 37, getRandomNumber(10) + 3531, getRandomNumber(360), 0)
	spawnMobile(self.planet, "verne", 300, getRandomNumber(10) + -3389, 37, getRandomNumber(10) + 3531, getRandomNumber(360), 0)
	spawnMobile(self.planet, "verne", 300, getRandomNumber(10) + -3389, 37, getRandomNumber(10) + 3531, getRandomNumber(360), 0)
	spawnMobile(self.planet, "verne", 300, getRandomNumber(10) + -3389, 37, getRandomNumber(10) + 3531, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3519, 101, getRandomNumber(10) + 3469, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3519, 101, getRandomNumber(10) + 3469, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3519, 101, getRandomNumber(10) + 3469, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3519, 101, getRandomNumber(10) + 3469, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3519, 101, getRandomNumber(10) + 3469, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3519, 101, getRandomNumber(10) + 3469, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3698, 101, getRandomNumber(10) + 3397, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3698, 101, getRandomNumber(10) + 3397, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3698, 101, getRandomNumber(10) + 3397, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3698, 101, getRandomNumber(10) + 3397, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3698, 101, getRandomNumber(10) + 3397, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3698, 101, getRandomNumber(10) + 3397, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3677, 101,getRandomNumber(10) + 3294, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3677, 101,getRandomNumber(10) + 3294, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3677, 101,getRandomNumber(10) + 3294, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3677, 101,getRandomNumber(10) + 3294, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3677, 101,getRandomNumber(10) + 3294, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_gubbur", 300, getRandomNumber(10) + -3677, 101,getRandomNumber(10) + 3294, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3808, 101,getRandomNumber(10) + 3347, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3808, 101,getRandomNumber(10) + 3347, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3808, 101,getRandomNumber(10) + 3347, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3808, 101,getRandomNumber(10) + 3347, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3808, 101,getRandomNumber(10) + 3347, getRandomNumber(360), 0)
	spawnMobile(self.planet, "durni", 300, getRandomNumber(10) + -3808, 101,getRandomNumber(10) + 3347, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3797, 101, getRandomNumber(10) + 2958, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3797, 101, getRandomNumber(10) + 2958, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3797, 101, getRandomNumber(10) + 2958, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3797, 101, getRandomNumber(10) + 2958, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3797, 101, getRandomNumber(10) + 2958, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -3797, 101, getRandomNumber(10) + 2958, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3659, 101, getRandomNumber(10) + 2855, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3659, 101, getRandomNumber(10) + 2855, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3659, 101, getRandomNumber(10) + 2855, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3659, 101, getRandomNumber(10) + 2855, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3659, 101, getRandomNumber(10) + 2855, getRandomNumber(360), 0)
	spawnMobile(self.planet, "vrelt", 300, getRandomNumber(10) + -3659, 101, getRandomNumber(10) + 2855, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3532, 101, getRandomNumber(10) + 2821, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3532, 101, getRandomNumber(10) + 2821, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3532, 101, getRandomNumber(10) + 2821, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3532, 101, getRandomNumber(10) + 2821, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3532, 101, getRandomNumber(10) + 2821, getRandomNumber(360), 0)
	spawnMobile(self.planet, "paralope", 300, getRandomNumber(10) + -3532, 101, getRandomNumber(10) + 2821, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, -3217.9, 29.2, 2732.2, 87, 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, -3220.2, 29.2, 2731.6, -111, 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, -3220.7, 29.2, 2735.2, 1, 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, -3217.6, 29.3, 2737.8, 57, 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, -3219.4, 29.4, 2742.1, -50, 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, -3223.1, 29.3, 2742.4, -87, 0)
	spawnMobile(self.planet, "minor_gubbur", 300, -3005.4, 25.5, 2731.1, 60, 0)
	spawnMobile(self.planet, "minor_gubbur", 300, -3001.2, 25.8, 2728.8, 118, 0)
	spawnMobile(self.planet, "minor_gubbur", 300, -2998.3, 25.9, 2732.4, -18, 0)
	spawnMobile(self.planet, "minor_gubbur", 300, -3001.0, 25.7, 2734.2, -60, 0)
	spawnMobile(self.planet, "minor_gubbur", 300, -2996.4, 25.9, 2735.7, 77, 0)
	spawnMobile(self.planet, "minor_gubbur", 300, -2994.2, 26.2, 2730.8, 177, 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -2981, 31, getRandomNumber(10) + 2988, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -2981, 31, getRandomNumber(10) + 2988, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -2981, 31, getRandomNumber(10) + 2988, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -2981, 31, getRandomNumber(10) + 2988, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -2981, 31, getRandomNumber(10) + 2988, getRandomNumber(360), 0)
	spawnMobile(self.planet, "corellian_butterfly_drone", 300, getRandomNumber(10) + -2981, 31, getRandomNumber(10) + 2988, getRandomNumber(360), 0)
end
