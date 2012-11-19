

bile_soaked_rancor_tooth = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Bile Soaked Rancor Tooth",
	directObjectTemplate = "object/tangible/component/weapon/rancor_tooth_quest.iff",
	craftingValues = {
		{"mindamage",15,15,0},
		{"maxdamage",65,65,0},
		{"attackspeed",0.3,0.3,1},
		{"woundchance",25,25,0},
		{"attackhealthcost",30,30,0},
		{"attackactioncost",25,25,0},
		{"attackmindcost",25,25,0},
		{"useCount",2,10,0},
	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("bile_soaked_rancor_tooth", bile_soaked_rancor_tooth)