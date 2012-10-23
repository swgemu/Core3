

projectile_pistol_barrel_quest = {
	minimumLevel = 0,
	maximumLevel = 0,
	customObjectName = "Enhanced Projectile Pistol Barrel",
	directObjectTemplate = "object/tangible/component/weapon/projectile_pistol_barrel_quest.iff",
	craftingValues = {
		{"mindamage",20,25,0},
		{"maxdamage",25,25,0},
		{"attackspeed",-0.7,-0.7,1},
		{"hitpoints",0,100,0},
		{"zerorangemod",0,0,0},
		{"maxrangemod",0,0,0},
		{"midrangemod",12,12,0},
		{"useCount",5,5,0},
	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("projectile_pistol_barrel_quest", projectile_pistol_barrel_quest)