composit_armor_gloves = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Composit Armor Gloves",
	directObjectTemplate = "object/tangible/wearables/armor/composite/armor_composite_gloves.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"electricityeffectiveness",10,55,10},
		{"armor_effectiveness",8,39,10},
		{"armor_integrity",30000, 55000,0},
		{"armor_health_encumbrance",25,15,0},
		{"armor_action_encumbrance",22,13,0},
		{"armor_mind_encumbrance",25,15,0},
	},
	skillMods = {

	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("composit_armor_gloves", composit_armor_gloves)
