ubese_armor_bandolier = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Ubese Armor Bandolier",
	directObjectTemplate = "object/tangible/wearables/armor/ubese/armor_ubese_bandolier.iff",
	craftingValues = {

		{"armor_integrity",18750, 31250,0},

	},
	skillMods = {

	},
	--no color pallets for customizing for ubese armor bandolier
	customizationStringNames = {},
	customizationValues = {},

	junkDealerTypeNeeded = JUNKGENERIC,
	junkMinValue = 45,
	junkMaxValue = 90
}

addLootItemTemplate("ubese_armor_bandolier", ubese_armor_bandolier)
