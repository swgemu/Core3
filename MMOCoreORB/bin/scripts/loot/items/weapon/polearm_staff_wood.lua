
polearm_staff_wood = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/polearm/lance_staff_wood_s1.iff",
	craftingValues = {
		{"mindamage",25,46,0},
		{"maxdamage",56,104,0},
		{"attackspeed",5.8,4,1},
		{"woundchance",3,7,0},
		{"hitpoints",750,1500,0},
		{"zerorangemod",14,26,0},
		{"maxrangemod",14,26,0},
		{"midrange",3,3,0},
		{"midrangemod",14,26,0},
		{"maxrange",5,5,0},		
		{"attackhealthcost",20,11,0},
		{"attackactioncost",49,27,0},
		{"attackmindcost",20,11,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 500,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("polearm_staff_wood", polearm_staff_wood)
