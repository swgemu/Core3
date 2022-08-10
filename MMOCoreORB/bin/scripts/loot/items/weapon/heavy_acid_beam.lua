heavy_acid_beam = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/heavy/heavy_acid_beam.iff",
	craftingValues = {
		{"mindamage",833,1057,0},
		{"maxdamage",1500,3700,0},
		{"attackspeed",8.7,4.4,1},
		{"woundchance",19,35,1},
		{"roundsused",30,65,0},
		{"hitpoints",1000,1000,0},
		{"zerorange",0,0,0},
		{"zerorangemod",0,0,0},
		{"midrange",16,16,0},
		{"midrangemod",20,20,0},
		{"maxrange",48,48,0},
		{"maxrangemod",-125,-125,0},
		{"charges",25,50,0},
		{"attackhealthcost",78,42,0},
		{"attackactioncost",78,42,0},
		{"attackmindcost",20,10,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("heavy_acid_beam", heavy_acid_beam)
