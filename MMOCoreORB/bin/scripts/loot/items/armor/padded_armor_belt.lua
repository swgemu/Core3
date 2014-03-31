padded_armor_belt = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "a Padded Armor Belt",
	directObjectTemplate = "object/tangible/wearables/armor/padded/armor_padded_s01_belt.iff",
	craftingValues = {

		{"armor_integrity", 18750, 31000,0},
	},
	skillMods = {

	},
	customizationStringNames = {},
	customizationValues = {},

	junkDealerTypeNeeded = JUNKARMOUR,
	junkMinValue = 50,
	junkMaxValue = 100
}

addLootItemTemplate("padded_armor_belt", padded_armor_belt)
