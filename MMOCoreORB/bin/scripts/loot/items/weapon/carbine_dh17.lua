carbine_dh17 = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/carbine/carbine_dh17.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",28,52,0},
		{"maxdamage",81,150,0},
		{"attackspeed",4.5,3.1,1},
		{"woundchance",6,12,1},
		{"zerorangemod",-40,-40,0},
		{"midrangemod",10,10,0},
		{"maxrangemod",-60,-60,0},
		{"midrange",35,35,0},
		{"maxrange",64,64,0},
		{"attackhealthcost",25,13,0},
		{"attackactioncost",35,19,0},
		{"attackmindcost",16,8,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 20,
	junkMaxValue = 40

}

addLootItemTemplate("carbine_dh17", carbine_dh17)
