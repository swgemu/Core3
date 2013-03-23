padded_armor_helmet = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "a Padded Armor Helmet",
	directObjectTemplate = "object/tangible/wearables/armor/padded/armor_padded_s01_helmet.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"blasteffectiveness",10,45,10},
		{"armor_effectiveness",8,29,10},
		{"armor_integrity",18750, 31000,0},
		{"armor_health_encumbrance",22,13,0},
		{"armor_action_encumbrance",17,10,0},
		{"armor_mind_encumbrance",280,140,0},
	},
	skillMods = {

	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("padded_armor_helmet", padded_armor_helmet)
