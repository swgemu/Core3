

weapon_scope_quest = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/tangible/component/weapon/scope_weapon_advanced_quest.iff",
	craftingValues = {
		{"mindamage",50,95,0},
		{"maxdamage",50,95,0},
		{"attackspeed",0.5,0,1},
		{"woundchance",12,20,0},
		{"hitpoints",100,300,0},
		{"zerorangemod",-6,4,0},
		{"maxrangemod",-6,4,0},
		{"midrangemod",-6,4,0},
		{"attackhealthcost",15,8,0},
		{"attackactioncost",15,8,0},
		{"attackmindcost",15,8,0},
		{"useCount",5,5,0},
	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("weapon_scope_quest", weapon_scope_quest)