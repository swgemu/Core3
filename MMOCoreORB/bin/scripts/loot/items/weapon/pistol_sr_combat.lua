pistol_sr_combat = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/pistol/pistol_srcombat.iff",
	craftingValues = {
		{"hitpoints",750,750,0},
		{"mindamage",28,55,0},
		{"maxdamage",63,122,0},
		{"attackspeed",5.7,4.3,1},
		{"woundchance",6,13,1},
		{"zerorangemod",0,0,0},
		{"midrangemod",-20,-20,0},
		{"maxrangemod",-80,-80,0},
		{"midrange",12,12,0},
		{"maxrange",48,48,0},
		{"attackhealthcost",36,20,0},
		{"attackactioncost",54,29,0},
		{"attackmindcost",23,12,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("pistol_sr_combat", pistol_sr_combat)
