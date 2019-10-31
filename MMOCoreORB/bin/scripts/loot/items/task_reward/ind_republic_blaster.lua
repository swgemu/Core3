ind_republic_blaster = {
	minimumLevel = 0,
	maximumLevel = 0,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/pistol/pistol_republic_blaster.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",17,17,0},
		{"maxdamage",79,79,0},
		{"attackspeed",5.1,5.1,1},
		{"woundchance",8,8,1},
		{"zerorangemod",0,0,0},
		{"midrangemod",-40,-40,0},
		{"maxrangemod",-70,-70,0},
		{"midrange",10,10,0},
		{"maxrange",64,64,0},
		{"attackhealthcost",23,23,0},
		{"attackactioncost",57,57,0},
		{"attackmindcost",23,23,0},
	},
	customizationStringNames = {},
	customizationValues = {},
	skillMods = {

	},

	randomDotChance = -1,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("ind_republic_blaster", ind_republic_blaster)