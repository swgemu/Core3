grenade_imperial_detonator = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/grenade/grenade_imperial_detonator.iff",
	craftingValues = {
		{"mindamage",645,989,0},
		{"maxdamage",1300,2000,0},
		{"attackspeed",6,2.5,1},
		{"woundchance",7,13,0},
		{"hitpoints",1000,1000,0},
		{"zerorangemod",-16,14,0},
		{"maxrange",64,64,0},
		{"maxrangemod",-45,-15,0},
		{"midrange",0,30,0},
		{"midrangemod",10,30,0},
		{"attackhealthcost",163,88,0},
		{"attackactioncost",163,88,0},
		{"attackmindcost",65,35,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 1000,
	junkDealerTypeNeeded = JUNKWEAPONS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("grenade_imperial_detonator", grenade_imperial_detonator)
