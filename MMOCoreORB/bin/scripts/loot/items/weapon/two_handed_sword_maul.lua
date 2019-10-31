two_handed_sword_maul = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/2h_sword/2h_sword_maul.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",53,98,0},
		{"maxdamage",235,436,0},
		{"attackspeed",8.5,5.8,1},
		{"woundchance",11,20,1},
		{"zerorangemod",-45,-45,0},
		{"midrangemod",-45,-45,0},
		{"maxrangemod",-45,-45,0},
		{"midrange",5,5,0},
		{"maxrange",5,5,0},
		{"attackhealthcost",120,63,0},
		{"attackactioncost",30,15,0},
		{"attackmindcost",16,7,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55

}

addLootItemTemplate("two_handed_sword_maul", two_handed_sword_maul)
