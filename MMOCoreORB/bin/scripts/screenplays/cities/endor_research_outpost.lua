EndorResearchOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "EndorResearchOutpostScreenPlay",

	planet = "endor",

	combatPatrol = {"commando", "commoner_technician", "mercenary", "sharpshooter"},
	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "noble_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, level, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"cll8_1", "cll8_binary_load_lifter", 1, 3250, 24, -3463, 330, 0, "", false},
		{"r3_1", "r3", 1, 3250.85, 24, -3464.83, 263.893, 0, "calm", false},
		{"r5_1", "r5", 1, 3249.85, 24, -3464.83, 180.771, 0, "calm", false},

		--NPCs
		{"npc_1", "combatPatrol", 60, 3166, 24, -3454, 130, 0, "", true},
		{"npc_2", "combatPatrol", 60, 3201, 24, -3463, 170, 0, "", true},
		{"npc_3", "combatPatrol", 60, 3196, 24, -3483, 359, 0, "", true},
		{"npc_4", "combatPatrol", 60, 3235, 24, -3451, 170, 0, "", true},
		{"npc_5", "combatPatrol", 60, 3277, 24, -3484, -80, 0, "", true},
		{"npc_6", "patrolNpc", 60, 3186, 24, -3459, 189, 0, "", false},
		{"npc_7", "patrolNpc", 60, 3188, 24, -3482, 277, 0, "", false},
		{"npc_8", "patrolNpc", 60, 3171, 24, -3504, 196, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		cll8_1 = {{3251, 24, -3462, 0, true}, {3258, 24, -3452, 0, false}, {3216, 24, -3457, 0, false}, {3209, 24, -3468, 0, false}, {3181, 24, -3466, 0, true}, {3200, 24, -3470, 0, false}},
		r3_1 = {{3251, 24, -3466, 0, false}, {3267, 24, -3450, 0, false}, {3269, 24, -3431, 0, false}, {3278, 24, -3442, 0, false}, {3273, 24, -3443, 0, false}},
		r5_1 = {{3250, 24, -3467, 0, false}, {3249, 24, -3493, 0, false}, {3244, 24, -3497, 0, false}, {3227, 24, -3493, 0, false}, {3222, 24, -3493, 0, false}, {3204, 24, -3489, 0, false}, {3208, 24, -3480, 0, false}},

		npc_1 = {{3166, 24, -3454, 0, true}, {3174, 24, -3456, 0, true}, {3171, 24, -3482, 0, true}, {3164, 24, -3483, 0, true}, {3173, 24, -3463, 0, true}},
		npc_2 = {{3201, 24, -3463, 0, true}, {3194, 24, -3468, 0, true}, {3213, 24, -3461, 0, true}, {3194, 24, -3453, 0, true}},
		npc_3 = {{3196, 24, -3483, 0, true}, {3197, 24, -3501, 0, true}, {3201, 24, -3498, 0, true}, {3190, 24, -3490, 0, true}},
		npc_4 = {{3235, 24, -3451, 0, true}, {3236, 24, -3429, 0, true}, {3203, 24, -3430, 0, true}, {3249, 24, -3430, 0, true}, {3235, 24, -3431, 0, true}},
		npc_5 = {{3277, 24, -3484, 0, true}, {3270, 24, -3468, 0, true}, {3283, 24, -3467, 0, true}, {3275, 24, -3459, 0, true}, {3273, 24, -3470, 0, true}},
		npc_6 = {{3186, 24, -3459, 0, true}, {3180, 24, -3466, 0, true}, {3196, 24, -3457, 0, true}, {3180, 24, -3451, 0, true}, {3186, 24, -3466, 0, true}},
		npc_7 = {{3188, 24, -3482, 0, true}, {3186, 24, -3492, 0, true}, {3180, 24, -3493, 0, true}, {3180, 24, -3472, 0, true}, {3192, 24, -3474, 0, true}},
		npc_8 = {{3171, 24, -3504, 0, true}, {3177, 24, -3512, 0, true}, {3175, 24, -3498, 0, true}, {3166, 24, -3504, 0, true}},
	},
}

registerScreenPlay("EndorResearchOutpostScreenPlay", true)

function EndorResearchOutpostScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
	end
end

function EndorResearchOutpostScreenPlay:spawnMobiles()

	--tavern building
	pNpc = spawnMobile("endor", "kilnstrider",60,-3.44448,0.624999,-6.82681,331.362,9925367)
	self:setMoodString(pNpc, "npc_imperial")

	--outside
	spawnMobile("endor", "businessman", 60, 3175.37, 24, -3490.78, 156.98, 0)
	spawnMobile("endor", "businessman", 60, 3190.35, 24, -3434.93, 256.64, 0)
	spawnMobile("endor", "businessman", 60, 3239.41, 24, -3432.75, 321.916, 0)
	spawnMobile("endor", "businessman", 60, 3270.48, 24, -3452.45, 289.69, 0)
	spawnMobile("endor", "businessman", 60, 3246.59, 24, -3500.57, 28.4927, 0)
	spawnMobile("endor", "businessman", 60, 3209.65, 24, -3493.64, 0, 0)
	spawnMobile("endor", "commoner", 60, 3272.55, 24, -3438.99, 185.321, 0)
	spawnMobile("endor", "commoner", 60, 3255.57, 24, -3483.66, 195.741, 0)
	spawnMobile("endor", "commoner", 60, 3271.4, 24, -3502.14, 322.22, 0)
	spawnMobile("endor", "commoner", 60, 3201.34, 24, -3509.29, 348.067, 0)
	spawnMobile("endor", "commoner", 60, 3221.86, 24, -3473.87, 251.839, 0)
	spawnMobile("endor", "noble", 60, 3228.48, 24, -3510.48, 15.5858, 0)

end
