huff_quest_tusken_king_rifle = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/tangible/loot/quest/rifle_quest_tusken.iff",
	craftingValues = {
		{"mindamage",50,100,0},
		{"maxdamage",100,150,0},
		{"attackspeed",10,7,1},
		{"woundchance",3,8,1},
		{"roundsused",30,65,0},
		{"hitpoints",750,1500,0},
		{"zerorange",0,0,0},
		{"zerorangemod",-80,-80,0},
		{"midrange",60,60,0},
		{"midrangemod",20,20,0},
		{"maxrange",64,64,0},
		{"maxrangemod",-70,-70,0},
		{"attackhealthcost",25,15,0},
		{"attackactioncost",35,20,0},
		{"attackmindcost",75,45,0},
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

addLootItemTemplate("huff_quest_tusken_king_rifle", huff_quest_tusken_king_rifle)
