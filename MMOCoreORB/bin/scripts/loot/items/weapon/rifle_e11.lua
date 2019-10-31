rifle_e11 = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/rifle/rifle_e11.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",36,73,0},
		{"maxdamage",76,144,0},
		{"attackspeed",7.4,5.1,1},
		{"woundchance",14,36,1},
		{"zerorangemod",-70,-70,0},
		{"midrangemod",21,21,0},
		{"maxrangemod",-50,-50,0},
		{"midrange",50,50,0},
		{"maxrange",64,64,0},
		{"attackhealthcost",19,12,0},
		{"attackactioncost",31,23,0},
		{"attackmindcost",47,28,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("rifle_e11", rifle_e11)
