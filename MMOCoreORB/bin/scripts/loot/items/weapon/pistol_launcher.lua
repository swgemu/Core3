
pistol_launcher = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/pistol/pistol_launcher.iff",
	craftingValues = {
		{"mindamage",17,33,0},
		{"maxdamage",91,169,0},
		{"attackspeed",5.5,3.7,1},
		{"woundchance",13,23,1},
		{"roundsused",1,3,0},
		{"hitpoints",750,750,0},
		{"zerorange",0,0,0},
		{"zerorangemod",0,0,0},
		{"midrange",15,15,0},
		{"midrangemod",-15,-15,0},
		{"maxrange",64,64,0},
		{"maxrangemod",-70,-70,0},
		{"attackhealthcost",20,10,0},
		{"attackactioncost",58,31,0},
		{"attackmindcost",20,10,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55

}

addLootItemTemplate("pistol_launcher", pistol_launcher)
