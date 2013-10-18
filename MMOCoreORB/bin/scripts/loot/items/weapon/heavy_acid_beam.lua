heavy_acid_beam = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/heavy/heavy_acid_beam.iff",
	craftingValues = {
		{"mindamage",833,1057,0},
		{"maxdamage",1500,3700,0},
		{"attackspeed",8.7,4.4,1},
		{"woundchance",19,35,0},
		{"hitpoints",1000,1000,0},
		{"zerorangemod",0,10,0},
		{"maxrange",64,64,0},
		{"maxrangemod",-125,-95,0},
		{"midrange",16,16,0},
		{"midrangemod",20,30,0},
		{"attackhealthcost",78,42,0},
		{"attackactioncost",78,42,0},
		{"attackmindcost",20,10,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 1000,
	junkDealerTypeNeeded = JUNKWEAPONS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("heavy_acid_beam", heavy_acid_beam)
