bone_armor_bicep_r = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Bone Armor Right Bicep",
	directObjectTemplate = "object/tangible/wearables/armor/bone/armor_bone_s01_bicep_r.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"energyeffectiveness",10,35,10},
		{"armor_effectiveness",4,19,10},
		{"armor_integrity",7500, 12500,0},
		{"armor_health_encumbrance",6,4,0},
		{"armor_action_encumbrance",8,4,0},
		{"armor_mind_encumbrance",4,2,0},
	},
	skillMods = {

	},
	customizationStringNames = {"/private/index_color_0", "/private/index_color_1"},
	customizationValues = {
			{0, 1},
			{0, 1, 2, 3, 4, 5, 6}
	},

	junkDealerTypeNeeded = JUNKARMOUR,
	junkMinValue = 25,
	junkMaxValue = 50
}

addLootItemTemplate("bone_armor_bicep_r", bone_armor_bicep_r)
