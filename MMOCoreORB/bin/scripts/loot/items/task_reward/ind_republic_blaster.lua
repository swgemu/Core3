ind_republic_blaster = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/pistol/pistol_republic_blaster.iff",
	craftingValues = {
		{"mindamage",21,39,0},
		{"maxdamage",98,182,0},
		{"attackspeed",4.6,3.1,1},
		{"woundchance",10,20,1},
		{"hitpoints",750,1500,0},
		{"zerorange",0,0,0},
		{"zerorangemod",0,0,0},
		{"midrange",10,10,0},
		{"midrangemod",-40,-40,0},
		{"maxrange",64,64,0},
		{"maxrangemod",-70,-70,0},
		{"attackhealthcost",20,10,0},
		{"attackactioncost",52,28,0},
		{"attackmindcost",20,10,0},
	},
	customizationStringNames = {},
	customizationValues = {},
	skillMods = {

	},

	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 30,
	junkMaxValue = 55
}

addLootItemTemplate("ind_republic_blaster", ind_republic_blaster)