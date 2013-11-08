
gamorrean_battleaxe_quest = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/melee/2h_sword/2h_sword_battleaxe_quest.iff",
	craftingValues = {
		{"mindamage",53,98,0},
		{"maxdamage",123,228,0},
		{"attackspeed",6.5,4.5,1},
		{"woundchance",6,14,0},
		{"hitpoints",750,1500,0},
		{"zerorangemod",-26,-14,0},
		{"maxrangemod",-26,-14,0},
		{"midrange",3,3,0},
		{"midrangemod",-26,-14,0},
		{"maxrange",7,7,0},
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
