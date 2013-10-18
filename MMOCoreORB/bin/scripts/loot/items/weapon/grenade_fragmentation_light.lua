grenade_fragmentation_light = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/grenade/grenade_fragmentation_light.iff",
	craftingValues = {
		{"mindamage",130,170,0},
		{"maxdamage",220,760,0},
		{"attackspeed",5.5,2.5,1},
		{"woundchance",7,13,0},
		{"hitpoints",1000,1000,0},
		{"zerorangemod",-16,14,0},
		{"maxrange",64,64,0},
		{"maxrangemod",-45,-15,0},
		{"midrange",0,30,0},
		{"midrangemod",10,30,0},
		{"attackhealthcost",75,35,0},
		{"attackactioncost",65,25,0},
		{"attackmindcost",13,7,0},
	},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 1000,
	junkDealerTypeNeeded = JUNKWEAPONS,
	junkMinValue = 20,
	junkMaxValue = 40
}

addLootItemTemplate("grenade_fragmentation_light", grenade_fragmentation_light)
