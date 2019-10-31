polearm_lance = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/polearm/lance_controllerfp.iff",
	craftingValues = {		
		{"hitpoints",750,750,0},
		{"mindamage",7,13,0},
		{"maxdamage",133,247,0},
		{"attackspeed",7,4,1},
		{"woundchance",9,18,1},
		{"zerorangemod",7,7,0},
		{"midrangemod",7,7,0},
		{"maxrangemod",7,7,0},
		{"midrange",3,3,0},
		{"maxrange",5,5,0},
		{"attackhealthcost",26,14,0},
		{"attackactioncost",59,32,0},
		{"attackmindcost",29,15,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 500,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("polearm_lance", polearm_lance)
