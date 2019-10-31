polearm_staff_metal = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/polearm/lance_staff_metal.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",56,90,0},
		{"maxdamage",95,143,0},
		{"attackspeed",6,4.2,1},
		{"woundchance",7,7,1},
		{"zerorangemod",0,0,0},
		{"midrangemod",0,0,0},
		{"maxrangemod",0,0,0},
		{"midrange",3,3,0},
		{"maxrange",5,5,0},
		{"attackhealthcost",9,4,0},
		{"attackactioncost",66,36,0},
		{"attackmindcost",39,21,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 500,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("polearm_staff_metal", polearm_staff_metal)
