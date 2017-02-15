mine_drx55 = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/mine/wp_mine_drx55.iff",
	craftingValues = {
		{"mindamage",35,65,0},
		{"maxdamage",105,195,0},
		{"attackspeed",5,3,1},
		{"woundchance",7,13,0},
		{"hitpoints",1000,1000,0},
		{"zerorangemod",0,0,0},
		{"maxrange",32,32,0},
		{"maxrangemod",0,0,0},
		{"midrange",0,0,0},
		{"midrangemod",0,0,0},
		{"attackhealthcost",0,0,0},
		{"attackactioncost",0,0,0},
		{"attackmindcost",0,0,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45
}

addLootItemTemplate("mine_drx55", mine_drx55)
