
one_handed_sword = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/sword/sword_01.iff",
	craftingValues = {
		{"mindamage",14,26,0},
		{"maxdamage",63,117,0},
		{"attackspeed",4.6,3.2,1},
		{"woundchance",9,18,0},
		{"hitpoints",750,1500,0},
		{"zerorangemod",5,15,0},
		{"maxrangemod",5,15,0},
		{"midrange",3,3,0},
		{"midrangemod",5,15,0},
		{"maxrange",4,4,0},		
		{"attackhealthcost",27,15,0},
		{"attackactioncost",29,15,0},
		{"attackmindcost",29,15,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("one_handed_sword", one_handed_sword)
