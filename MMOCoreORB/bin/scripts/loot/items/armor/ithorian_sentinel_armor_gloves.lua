ithorian_sentinel_armor_gloves = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/tangible/wearables/armor/ithorian_sentinel/ith_armor_s03_gloves.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"armor_effectiveness",8,39,10},
		{"armor_integrity",30000, 55000,0},
		{"armor_health_encumbrance",25,15,0},
		{"armor_action_encumbrance",22,13,0},
		{"armor_mind_encumbrance",25,15,0},
	},
	skillMods = {

	},
	customizationStringNames = {"/private/index_color_1"},
	customizationValues = {
			{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
	},

	junkDealerTypeNeeded = JUNKGENERIC,
	junkMinValue = 55,
	junkMaxValue = 110
}

addLootItemTemplate("ithorian_sentinel_armor_gloves", ithorian_sentinel_armor_gloves)
