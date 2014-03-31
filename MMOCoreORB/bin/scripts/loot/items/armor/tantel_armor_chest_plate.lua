tantel_armor_chest_plate = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Tantel Armor Chest Plate",
	directObjectTemplate = "object/tangible/wearables/armor/tantel/armor_tantel_skreej_chest_plate.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"energyeffectiveness",10,30,10},
		{"armor_effectiveness",4,19,10},
		{"armor_integrity",11250, 18750,0},
		{"armor_health_encumbrance",95,56,0},
		{"armor_action_encumbrance",33,20,0},
		{"armor_mind_encumbrance",9,5,0},
	},
	skillMods = {

	},
	customizationStringNames = {"/private/index_color_1", "/private/index_color_2", "/private/index_color_3"},
	customizationValues = {
			{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
			{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
			{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}
	},

	junkDealerTypeNeeded = JUNKARMOUR,
	junkMinValue = 40,
	junkMaxValue = 80
}

addLootItemTemplate("tantel_armor_chest_plate", tantel_armor_chest_plate)
