padded_armor_chest_plate = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "a Padded Armor Chest Plate",
	directObjectTemplate = "object/tangible/wearables/armor/padded/armor_padded_s01_chest_plate.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"blasteffectiveness",10,45,10},
		{"armor_effectiveness",8,29,10},
		{"armor_integrity",18750, 31000,0},
		{"armor_health_encumbrance",172,103,0},
		{"armor_action_encumbrance",66,39,0},
		{"armor_mind_encumbrance",23,14,0},
	},
	skillMods = {

	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("padded_armor_chest_plate", padded_armor_chest_plate)
