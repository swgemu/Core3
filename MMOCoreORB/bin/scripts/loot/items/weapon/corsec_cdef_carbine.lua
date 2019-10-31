corsec_cdef_carbine = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/carbine/carbine_cdef_corsec.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",17,32,0},
		{"maxdamage",35,65,0},
		{"attackspeed",4.6,3.2,1},
		{"woundchance",4,5,1},
		{"zerorangemod",20,20,0},
		{"midrangemod",47,47,0},
		{"maxrangemod",-80,-80,0},
		{"midrange",35,35,0},
		{"maxrange",64,64,0},
		{"attackhealthcost",10,7,0},
		{"attackactioncost",22,15,0},
		{"attackmindcost",10,7,0},	
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS + JUNKCORSEC,
	junkMinValue = 20,
	junkMaxValue = 60

}

addLootItemTemplate("corsec_cdef_carbine", corsec_cdef_carbine)
