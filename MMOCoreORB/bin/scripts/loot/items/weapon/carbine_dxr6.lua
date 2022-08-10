
carbine_dxr6 = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/carbine/carbine_dxr6.iff",
	craftingValues = {
		{"mindamage",63,90,0},
		{"maxdamage",91,143,0},
		{"attackspeed",6,4.1,1},
		{"woundchance",10,20,1},
		{"roundsused",30,65,0},
		{"hitpoints",750,1500,0},
		{"zerorange",0,0,0},
		{"zerorangemod",-30,-30,0},
		{"midrange",60,60,0},
		{"midrangemod",45,45,0},
		{"maxrange",64,64,0},
		{"maxrangemod",-85,-85,0},
		{"attackhealthcost",33,18,0},
		{"attackactioncost",52,28,0},
		{"attackmindcost",25,13,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55

}

addLootItemTemplate("carbine_dxr6", carbine_dxr6)
