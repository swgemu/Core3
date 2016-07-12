polearm_smc_vhaunda = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/polearm/lance_vibrolance.iff",

	craftingValues = {
		{"mindamage",17,17,0},
		{"maxdamage",184,184,0},
		{"attackspeed",3.5,6.0,1},
		{"woundchance",24,30,0},
		{"zerorangemod",3,3,0},
		{"midrangemod",3,3,0},
		{"maxrangemod",3,3,0},
		{"midrange",3,3,0},
		{"maxrange",7,7,0},
		{"attackhealthcost",18,60,0},
		{"attackactioncost",43,85,0},
		{"attackmindcost",22,30,0},
	},
	customizationStringNames = {},
	customizationValues = {},
}

addLootItemTemplate("polearm_smc_vhaunda", polearm_smc_vhaunda)
