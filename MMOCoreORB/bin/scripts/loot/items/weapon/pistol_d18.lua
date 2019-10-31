pistol_d18 = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/pistol/pistol_d18.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",7,17,0},
		{"maxdamage",36,72,0},
		{"attackspeed",4.7,3.2,1},
		{"woundchance",3.4,7.2,1},
		{"zerorangemod",0,0,0},
		{"midrangemod",24,24,0},
		{"maxrangemod",-60,-60,0},
		{"midrange",15,15,0},
		{"maxrange",64,64,0},
		{"attackhealthcost",19,11,0},
		{"attackactioncost",43,23,0},
		{"attackmindcost",20,12,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 20,
	junkMaxValue = 40

}

addLootItemTemplate("pistol_d18", pistol_d18)
