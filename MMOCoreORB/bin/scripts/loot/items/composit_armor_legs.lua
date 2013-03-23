composit_armor_leggings = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Composit Armor Leggings",
	directObjectTemplate = "object/tangible/wearables/armor/composite/armor_composite_leggings.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"electricityeffectiveness",10,55,10},
		{"armor_effectiveness",8,39,10},
		{"armor_integrity",30000, 65000,0},
		{"armor_health_encumbrance",70,40,0},
		{"armor_action_encumbrance",175,105,0},
		{"armor_mind_encumbrance",22,13,0},
	},
	skillMods = {

	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("composit_armor_leggings", composit_armor_leggings)
