bestine_quest_sword = {
	minimumLevel = 0,
	maximumLevel = 0,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/sword/bestine_quest_sword.iff",
	craftingValues = {
		{"mindamage",25,46,0},
		{"maxdamage",98,182,0},
		{"attackspeed",6.5,4.5,1},
		{"woundchance",11,20,1},
		{"hitpoints",750,1500,0},
		{"zerorange",0,0,0},
		{"zerorangemod",-5,-5,0},
		{"midrange",3,3,0},
		{"midrangemod",-5,-5,0},
		{"maxrange",4,4,0},
		{"maxrangemod",-5,-5,0},
		{"attackhealthcost",78,42,0},
		{"attackactioncost",40,22,0},
		{"attackmindcost",13,7,0},
	},
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 20,
	junkMaxValue = 60,
}

addLootItemTemplate("bestine_quest_sword", bestine_quest_sword)
