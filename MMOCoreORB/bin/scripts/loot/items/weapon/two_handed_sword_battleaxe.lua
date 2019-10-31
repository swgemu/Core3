two_handed_sword_battleaxe = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/2h_sword/2h_sword_battleaxe.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",53,98,0},
		{"maxdamage",88,163,0},
		{"attackspeed",5.6,4.1,1},
		{"woundchance",12,22,1},
		{"zerorangemod",3,3,0},
		{"midrangemod",3,3,0},
		{"maxrangemod",3,3,0},
		{"midrange",5,5,0},
		{"maxrange",5,5,0},
		{"attackhealthcost",52,26,0},
		{"attackactioncost",17,8,0},
		{"attackmindcost",10,4,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("two_handed_sword_battleaxe", two_handed_sword_battleaxe)
