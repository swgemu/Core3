baton_stun = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/baton/baton_stun.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",28,52,0},
		{"maxdamage",53,98,0},
		{"attackspeed",4.2,2.9,1},
		{"woundchance",1,3,1},
		{"zerorangemod",-5,-5,0},
		{"midrangemod",-5,-5,0},
		{"maxrangemod",-5,-5,0},
		{"midrange",2,2,0},
		{"maxrange",4,4,0},
		{"attackhealthcost",10,4,0},
		{"attackactioncost",45,24,0},
		{"attackmindcost",39,19,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("baton_stun", baton_stun)
