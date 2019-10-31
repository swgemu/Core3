heavy_particle_beam = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/heavy/heavy_particle_beam.iff",
	craftingValues = {
		{"hitpoints",1000,1000,0},
		{"mindamage",1860,2000,0},
		{"maxdamage",2700,3700,0},
		{"attackspeed",9.1,4.0,1},
		{"woundchance",10,20,1},
		{"zerorangemod",-125,-125,0},
		{"midrangemod",0,0,0},
		{"maxrangemod",-125,-125,0},
		{"midrange",48,48,0},
		{"maxrange",64,64,0},
		{"attackhealthcost",33,17,0},
		{"attackactioncost",110,59,0},
		{"attackmindcost",33,17,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("heavy_particle_beam", heavy_particle_beam)
