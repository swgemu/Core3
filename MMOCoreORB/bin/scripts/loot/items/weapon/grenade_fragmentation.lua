grenade_fragmentation = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/grenade/grenade_fragmentation.iff",
	craftingValues = {
		{"mindamage",200,296,0},
		{"maxdamage",400,1450,0},
		{"attackspeed",4.5,3.5,1},
		{"woundchance",7,13,0},
		{"hitpoints",1000,1000,0},
		{"zerorangemod",-16,14,0},
		{"maxrange",64,64,0},
		{"maxrangemod",-45,15,0},
		{"midrange",0,30,0},
		{"midrangemod",10,30,0},
		{"attackhealthcost",104,56,0},
		{"attackactioncost",104,56,0},
		{"attackmindcost",20,11,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 1000,
	junkDealerTypeNeeded = JUNKWEAPONS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("grenade_fragmentation", grenade_fragmentation)
