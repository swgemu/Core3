grenade_cryoban = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/grenade/grenade_cryoban.iff",
	craftingValues = {
		{"hitpoints",1000,1000,0},
		{"mindamage",190,270,0},
		{"maxdamage",320,650,0},
		{"attackspeed",6.5,3,1},
		{"woundchance",7,13,1},
		{"zerorangemod",-10,-10,0},
		{"midrangemod",10,10,0},
		{"maxrangemod",-30,-30,0},
		{"midrange",10,10,0},
		{"maxrange",32,32,0},
		{"attackhealthcost",52,28,0},
		{"attackactioncost",130,70,0},
		{"attackmindcost",20,11,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("grenade_cryoban", grenade_cryoban)
