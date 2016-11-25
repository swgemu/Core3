ubese_armor_gloves = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Ubese Armor Gloves",
	directObjectTemplate = "object/tangible/wearables/armor/ubese/armor_ubese_gloves.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"kineticeffectiveness",10,40,10},
		{"armor_effectiveness",4,29,10},
		{"armor_integrity",18750, 31250,0},
		{"armor_health_encumbrance",11,7,0},
		{"armor_action_encumbrance",28,17,0},
		{"armor_mind_encumbrance",19,11,0},
	},
	skillMods = {

	},
	--no color pallets for customizing for ubese armor gloves
	customizationStringNames = {},
	customizationValues = {},

	junkDealerTypeNeeded = JUNKGENERIC,
	junkMinValue = 45,
	junkMaxValue = 90
}

addLootItemTemplate("ubese_armor_gloves", ubese_armor_gloves)
