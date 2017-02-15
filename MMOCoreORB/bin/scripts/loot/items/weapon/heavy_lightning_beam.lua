heavy_lightning_beam = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/heavy/heavy_lightning_beam.iff",
	craftingValues = {
		{"mindamage",936,1340,0},
		{"maxdamage",1550,3400,0},
		{"attackspeed",9.6,5.4,1},
		{"woundchance",13,23,0},
		{"hitpoints",1000,1000,0},
		{"zerorangemod",-45,-35,0},
		{"maxrange",64,64,0},
		{"maxrangemod",-125,-95,0},
		{"midrange",32,32,0},
		{"midrangemod",0,40,0},
		{"attackhealthcost",45,24,0},
		{"attackactioncost",97,52,0},
		{"attackmindcost",26,14,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("heavy_lightning_beam", heavy_lightning_beam)
