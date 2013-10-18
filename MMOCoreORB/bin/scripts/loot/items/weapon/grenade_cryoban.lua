grenade_cryoban = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/grenade/grenade_cryoban.iff",
	craftingValues = {
		{"mindamage",190,270,0},
		{"maxdamage",320,650,0},
		{"attackspeed",6.5,3,1},
		{"woundchance",7,13,0},
		{"hitpoints",1000,1000,0},
		{"zerorangemod",-14,16,0},
		{"maxrange",64,64,0},
		{"maxrangemod",-45,-15,0},
		{"midrange",0,30,0},
		{"midrangemod",10,30,0},
		{"attackhealthcost",52,28,0},
		{"attackactioncost",130,70,0},
		{"attackmindcost",20,11,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 1000,
	junkDealerTypeNeeded = JUNKWEAPONS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("grenade_cryoban", grenade_cryoban)
