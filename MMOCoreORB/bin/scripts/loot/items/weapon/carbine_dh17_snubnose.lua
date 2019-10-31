carbine_dh17_snubnose = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/carbine/carbine_dh17_snubnose.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",28,52,0},
		{"maxdamage",81,150,0},
		{"attackspeed",4.5,3.1,1},
		{"woundchance",6,12,1},
		{"zerorangemod",-25,-25,0},
		{"midrangemod",0,0,0},
		{"maxrangemod",-80,-80,0},
		{"midrange",25,25,0},
		{"maxrange",64,64,0},
		{"attackhealthcost",29,15,0},
		{"attackactioncost",31,17,0},
		{"attackmindcost",16,8,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("carbine_dh17_snubnose", carbine_dh17_snubnose)
