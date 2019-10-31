carbine_ee3 = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/carbine/carbine_ee3.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",35,65,0},
		{"maxdamage",91,169,0},
		{"attackspeed",4.7,3.2,1},
		{"radius",3.0,4.0,1},
		{"woundchance",5,9,1},
		{"zerorangemod",-25,-25,0},
		{"midrangemod",0,0,0},
		{"maxrangemod",-80,-80,0},
		{"midrange",27,27,0},
		{"maxrange",64,64,0},
		{"attackhealthcost",44,24,0},
		{"attackactioncost",36,20,0},
		{"attackmindcost",20,11,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("carbine_ee3", carbine_ee3)
