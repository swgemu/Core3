polearm_staff_janta = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/polearm/lance_staff_janta.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",41,52,0},
		{"maxdamage",86,111,0},
		{"attackspeed",5.8,4,1},
		{"woundchance",4,8,1},
		{"zerorangemod",14,14,0},
		{"midrangemod",14,14,0},
		{"maxrangemod",14,14,0},
		{"midrange",3,3,0},
		{"maxrange",5,5,0},
		{"attackhealthcost",28,14,0},
		{"attackactioncost",38,27,0},
		{"attackmindcost",15,11,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 500,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 20,
	junkMaxValue = 60

}

addLootItemTemplate("polearm_staff_janta", polearm_staff_janta)
