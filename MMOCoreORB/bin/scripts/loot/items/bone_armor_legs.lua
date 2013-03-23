bone_armor_leggings = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Bone Armor Leggings",
	directObjectTemplate = "object/tangible/wearables/armor/bone/armor_bone_s01_leggings.iff",
	craftingValues = {
		{"armor_rating",1,1,0},
		{"energyeffectiveness",10,35,10},
		{"armor_effectiveness",4,19,10},
		{"armor_integrity",7500, 12500,0},
		{"armor_health_encumbrance",18,10,0},
		{"armor_action_encumbrance",60,36,0},
		{"armor_mind_encumbrance",4,2,0},
	},
	skillMods = {

	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("bone_armor_leggings", bone_armor_leggings)
