melee_vibroknuckler = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/special/vibroknuckler.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",7,13,0},
		{"maxdamage",60,111,0},
		{"attackspeed",3.6,2.5,1},
		{"woundchance",14,26,1},
		{"zerorangemod",7,7,0},
		{"midrangemod",7,7,0},
		{"maxrangemod",7,7,0},
		{"midrange",1,1,0},
		{"maxrange",3,3,0},
		{"attackhealthcost",36,18,0},
		{"attackactioncost",54,30,0},
		{"attackmindcost",36,18,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55

}

addLootItemTemplate("melee_vibroknuckler", melee_vibroknuckler)
