carbine_e11 = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/carbine/carbine_e11.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",28,52,0},
		{"maxdamage",67,124,0},
		{"attackspeed",4.3,3,1},
		{"woundchance",7,13,1},
		{"zerorangemod",-40,-40,0},
		{"midrangemod",0,0,0},
		{"maxrangemod",-80,-80,0},
		{"midrange",30,30,0},
		{"maxrange",64,64,0},
		{"attackhealthcost",33,18,0},
		{"attackactioncost",42,22,0},
		{"attackmindcost",20,11,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("carbine_e11", carbine_e11)
