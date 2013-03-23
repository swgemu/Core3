padded_armor_gloves = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Padded Armor Gloves",
	directObjectTemplate = "object/tangible/wearables/armor/padded/armor_padded_s01_gloves.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"blasteffectiveness",10,45,10},
		{"armor_effectiveness",8,29,10},
		{"armor_integrity",18750, 31000,0},
		{"armor_health_encumbrance",23,14,0},
		{"armor_action_encumbrance",44,26,0},
		{"armor_mind_encumbrance",17,10,0},
	},
	skillMods = {

	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("padded_armor_gloves", padded_armor_gloves)
