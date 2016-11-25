ithorian_defender_armor_boots = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/tangible/wearables/armor/ithorian_defender/ith_armor_s01_boots.iff",
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
	customizationStringNames = {"/private/index_color_0", "/private/index_color_1"},
	customizationValues = {
			{0, 1},
			{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
	},

	junkDealerTypeNeeded = JUNKGENERIC,
	junkMinValue = 50,
	junkMaxValue = 100
}

addLootItemTemplate("ithorian_defender_armor_boots", ithorian_defender_armor_boots)
