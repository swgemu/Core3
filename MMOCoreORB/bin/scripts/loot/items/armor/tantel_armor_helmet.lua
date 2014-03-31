tantel_armor_helmet = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Tantel Armor Helmet",
	directObjectTemplate = "object/tangible/wearables/armor/tantel/armor_tantel_skreej_helmet.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"energyeffectiveness",10,30,10},
		{"armor_effectiveness",4,19,10},
		{"armor_integrity",11250, 18750,0},
		{"armor_health_encumbrance",9,6,0},
		{"armor_action_encumbrance",11,7,0},
		{"armor_mind_encumbrance",105,63,0},
	},
	skillMods = {

	},
	customizationStringNames = {"/private/index_color_1",},
	customizationValues = {
			{0, 1, 2, 3, 4, 5, 6}
	},

	junkDealerTypeNeeded = JUNKARMOUR,
	junkMinValue = 40,
	junkMaxValue = 80
}

addLootItemTemplate("tantel_armor_helmet", tantel_armor_helmet)
