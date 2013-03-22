padded_armor_leggings = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Padded Armor Leggings",
	directObjectTemplate = "object/tangible/wearables/armor/padded/armor_padded_s01_leggings.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"blasteffectiveness",10,45,10},
		{"armor_effectiveness",8,29,10},
		{"armor_integrity",18750, 31000,0},
		{"armor_health_encumbrance",23,14,0},
		{"armor_action_encumbrance",175,105,0},
		{"armor_mind_encumbrance",52,31,0},
	},
	skillMods = {

	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("padded_armor_leggings", padded_armor_leggings)
