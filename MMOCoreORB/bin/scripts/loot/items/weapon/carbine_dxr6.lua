
carbine_dxr6 = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/carbine/carbine_dxr6.iff",
	craftingValues = {
		{"mindamage",63,90,0},
		{"maxdamage",91,143,0},
		{"attackspeed",6,4.1,1},
		{"woundchance",10,20,0},
		{"roundsused",30,65,0},
		{"hitpoints",750,1500,0},
		{"zerorangemod",-20,-20,0},
		{"maxrangemod",-80,-80,0},
		{"midrange",22,22,0},
		{"midrangemod",-5,5,0},
		{"attackhealthcost",33,18,0},
		{"attackactioncost",52,28,0},
		{"attackmindcost",25,13,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 800,
	junkDealerTypeNeeded = JUNKWEAPONS,
	junkMinValue = 30,
	junkMaxValue = 55

}

addLootItemTemplate("carbine_dxr6", carbine_dxr6)
