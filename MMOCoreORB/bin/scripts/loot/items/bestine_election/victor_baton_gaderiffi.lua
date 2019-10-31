victor_baton_gaderiffi = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/baton/victor_baton_gaderiffi.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",49,91,0},
		{"maxdamage",98,182,0},
		{"attackspeed",5.9,4,1},
		{"woundchance",11,21,1},
		{"zerorangemod",-13,-13,0},
		{"midrangemod",-13,-13,0},
		{"maxrangemod",-13,-13,0},
		{"midrange",3,3,0},
		{"maxrange",5,5,0},
		{"attackhealthcost",58,30,0},
		{"attackactioncost",31,15,0},
		{"attackmindcost",10,4,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45
}

addLootItemTemplate("victor_baton_gaderiffi", victor_baton_gaderiffi)
