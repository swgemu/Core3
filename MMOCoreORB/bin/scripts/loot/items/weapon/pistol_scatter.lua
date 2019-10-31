pistol_scatter = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/pistol/pistol_scatter.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",43,87,0},
		{"maxdamage",59,102,0},
		{"attackspeed",5.4,3.9,1},
		{"woundchance",10,24,1},
		{"zerorangemod",17,17,0},
		{"midrangemod",-30,-30,0},
		{"maxrangemod",-90,-90,0},
		{"midrange",7,7,0},
		{"maxrange",64,64,0},
		{"attackhealthcost",24,12,0},
		{"attackactioncost",63,35,0},
		{"attackmindcost",24,12,0},

	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55

}

addLootItemTemplate("pistol_scatter", pistol_scatter)
