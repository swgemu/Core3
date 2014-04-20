mine_anti_vehicle = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/mine/wp_mine_anti_vehicle.iff",
	craftingValues = {
		{"mindamage",70,130,0},
		{"maxdamage",210,390,0},
		{"attackspeed",13,9,1},
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
	randomDotChance = 1000,
	junkDealerTypeNeeded = JUNKWEAPONS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("mine_anti_vehicle", mine_anti_vehicle)
