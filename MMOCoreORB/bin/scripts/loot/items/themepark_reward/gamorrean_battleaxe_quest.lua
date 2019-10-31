
gamorrean_battleaxe_quest = {
	minimumLevel = 0,
	maximumLevel = 0,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/2h_sword/2h_sword_battleaxe_quest.iff",
	craftingValues = {
		{"hitpoints",1000,1000,0},
		{"mindamage",86,86,0},
		{"maxdamage",144,144,0},
		{"attackspeed",4.5,4.5,1},
		{"woundchance",19,19,1},
		{"zerorangemod",7,7,0},
		{"midrangemod",7,7,0},
		{"maxrangemod",7,7,0},
		{"midrange",3,3,0},
		{"maxrange",4,4,0},
		{"attackhealthcost",33,33,0},
		{"attackactioncost",11,11,0},
		{"attackmindcost",6,6,0},
	},
	customizationStringNames = {},
	customizationValues = {},
	skillMods = {{"block", 5}},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = -1,

	-- staticDotChance: The chance of this weapon object dropping with a static dot on it. Higher number means less chance. Set to 0 to always have a static dot.
	staticDotChance = 0,

	-- staticDotType: 1 = Poison, 2 = Disease, 3 = Fire, 4 = Bleed
	staticDotType = 2,

	-- staticDotValues: Object map that can randomly or statically generate a dot (used for weapon objects.)
	staticDotValues = {
		{"attribute", 6, 6}, -- See CreatureAttributes.h in src for numbers.
		{"strength", 50, 50},
		{"duration", 400, 400},
		{"potency", 60, 60},
		{"uses", 9999, 9999}
	}

}

addLootItemTemplate("gamorrean_battleaxe_quest", gamorrean_battleaxe_quest)
