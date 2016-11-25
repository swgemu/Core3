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
			{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119}
	},

	junkDealerTypeNeeded = JUNKGENERIC,
	junkMinValue = 40,
	junkMaxValue = 80
}

addLootItemTemplate("tantel_armor_helmet", tantel_armor_helmet)
