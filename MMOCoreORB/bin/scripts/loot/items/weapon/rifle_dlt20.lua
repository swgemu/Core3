rifle_dlt20 = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/rifle/rifle_dlt20.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",61,87,0},
		{"maxdamage",94,149,0},
		{"attackspeed",8.4,6.1,1},
		{"woundchance",4.3,11.2,1},
		{"zerorangemod",-70,-70,0},
		{"midrangemod",21,21,0},
		{"maxrangemod",-50,-50,0},
		{"midrange",60,60,0},
		{"midrange",64,64,0},
		{"attackhealthcost",22,14,0},
		{"attackactioncost",43,23,0},
		{"attackmindcost",47,21,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 20,
	junkMaxValue = 40

}

addLootItemTemplate("rifle_dlt20", rifle_dlt20)
