grenade_imperial_detonator = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/grenade/grenade_imperial_detonator.iff",
	craftingValues = {
		{"hitpoints",1000,1000,0},
		{"mindamage",645,989,0},
		{"maxdamage",1300,2000,0},
		{"attackspeed",6,2.5,1},
		{"woundchance",7,13,1},
		{"zerorangemod",-10,-10,0},
		{"midrangemod",20,20,0},
		{"maxrangemod",-30,-30,0},
		{"midrange",10,10,0},		
		{"maxrange",32,32,0},
		{"attackhealthcost",163,88,0},
		{"attackactioncost",163,88,0},
		{"attackmindcost",65,35,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("grenade_imperial_detonator", grenade_imperial_detonator)
