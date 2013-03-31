bone_armor_gloves = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Bone Armor Gloves",
	directObjectTemplate = "object/tangible/wearables/armor/bone/armor_bone_s01_gloves.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"energyeffectiveness",10,35,10},
		{"armor_effectiveness",4,19,10},
		{"armor_integrity",7500, 12500,0},
		{"armor_health_encumbrance",6,4,0},
		{"armor_action_encumbrance",16,8,0},
		{"armor_mind_encumbrance",4,2,0},
	},
	skillMods = {

	},
	customizationStringNames = {"/private/index_color_0", "/private/index_color_1"},
	customizationValues = {
			{0, 1}, 
			{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95}},
}

addLootItemTemplate("bone_armor_gloves", bone_armor_gloves)
