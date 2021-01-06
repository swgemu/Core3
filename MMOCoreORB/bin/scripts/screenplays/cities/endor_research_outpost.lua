EndorResearchOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "EndorResearchOutpostScreenPlay",

	planet = "endor",

	patrolMobiles = {
		--{patrolPoints, template, level, x, z, y, direction, cell, mood},
		{"cll8_1", "cll8_binary_load_lifter", 60, 3250.85, 24, -3463.83, 330.752, 0, ""},
		{"r3_1", "r3", 60, 3250.85, 24, -3464.83, 263.893, 0, "calm"},
		{"r5_1", "r5", 60, 3249.85, 24, -3464.83, 180.771, 0, "calm"},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}} 1 = no delay 0 = delay}
		cll8_1 = {{3251, 24, -3462, 0, 0}, {3258, 24, -3452, 0, 1}, {3216, 24, -3457, 0, 1}, {3182, 24, -3455, 0, 1}, {3181, 24, -3466, 0, 0}, {3200, 24, -3470, 0, 1}},
		r3_1 = {{3251, 24, -3466, 0, 1}, {3267, 24, -3450, 0, 1}, {3269, 24, -3431, 0, 1}, {3278, 24, -3442, 0, 1}, {3273, 24, -3443, 0, 1}},
		r5_1 = {{3250, 24, -3467, 0, 1}, {3249, 24, -3493, 0, 1}, {3244, 24, -3497, 0, 1}, {3227, 24, -3493, 0, 1}, {3222, 24, -3493, 0, 1}, {3204, 24, -3489, 0, 1}, {3208, 24, -3480, 0, 1}},
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
	spawnMobile("endor", "businessman", 60, 3209.65, 24, -3493.64, 217.211, 0)

	spawnMobile("endor", "commando", 300, 3196.77, 24, -3483.16, 359.892, 0)
	spawnMobile("endor", "commando", 300, 3166, 24, -3454, 130, 0)
	spawnMobile("endor", "commoner", 60, 3176.73, 24, -3512.02, 187.645, 0)
	spawnMobile("endor", "commoner", 60, 3188.73, 24, -3482.54, 277.835, 0)
	spawnMobile("endor", "commoner", 60, 3186.49, 24, -3459.94, 189.74, 0)
	spawnMobile("endor", "commoner", 60, 3171.1, 24,- 3504.6, 196.748, 0)
	spawnMobile("endor", "commoner", 60, 3272.55, 24, -3438.99, 185.321, 0)
	spawnMobile("endor", "commoner", 60, 3255.57, 24, -3483.66, 195.741, 0)
	spawnMobile("endor", "commoner", 60, 3271.4, 24, -3502.14, 322.22, 0)
	spawnMobile("endor", "commoner", 60, 3201.34, 24, -3509.29, 348.067, 0)
	spawnMobile("endor", "commoner", 60, 3221.86, 24, -3473.87, 251.839, 0)
	spawnMobile("endor", "mercenary", 60, 3277, 24, -3484, -80, 0)
	spawnMobile("endor", "mercenary", 60, 3233, 24, -3451, 170, 0)
	spawnMobile("endor", "mercenary", 60, 3201, 24, -3463, 170, 0)
	spawnMobile("endor", "noble", 60, 3228.48, 24, -3510.48, 15.5858, 0)

end
