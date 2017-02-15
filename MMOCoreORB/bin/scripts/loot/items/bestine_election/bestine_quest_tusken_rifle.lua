bestine_quest_tusken_rifle = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/rifle/rifle_victor_tusken.iff",
	craftingValues = {
		{"mindamage",40,150,0},
		{"maxdamage",80,320,0},
		{"attackspeed",9.4,6.7,1},
		{"woundchance",4.8,12.3,0},
		{"hitpoints",750,750,0},
		{"attackhealthcost",21,12,0},
		{"attackactioncost",32,19,0},
		{"attackmindcost",77,42,0},
		{"roundsused",30,65,0},
		{"zerorangemod",-80,-40,0},
		{"maxrangemod",10,30,0},
		{"midrange",54,54,0},
		{"midrangemod",45,70,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 750,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 20,
	junkMaxValue = 60
}

addLootItemTemplate("bestine_quest_tusken_rifle", bestine_quest_tusken_rifle)
