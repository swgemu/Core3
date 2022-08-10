grenade_fragmentation = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/grenade/grenade_fragmentation.iff",
	craftingValues = {
		{"mindamage",200,296,0},
		{"maxdamage",400,1450,0},
		{"attackspeed",4.5,3.5,1},
		{"woundchance",7,13,1},
		{"hitpoints",1000,1000,0},
		{"zerorange",0,0,0},
		{"zerorangemod",-10,-10,0},
		{"midrange",20,20,0},
		{"midrangemod",10,10,0},
		{"maxrange",32,32,0},
		{"maxrangemod",-30,-30,0},
		{"attackhealthcost",104,56,0},
		{"attackactioncost",104,56,0},
		{"attackmindcost",20,11,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("grenade_fragmentation", grenade_fragmentation)
