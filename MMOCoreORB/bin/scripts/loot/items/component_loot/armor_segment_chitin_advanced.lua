armor_segment_chitin_advanced = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/tangible/component/armor/armor_segment_chitin_advanced.iff",
	craftingValues = {
		{"hit_points",1000,1000,0, true},
		{"armor_effectiveness",7,15,10},
		{"armor_integrity",1000,2000,0},
		{"armor_health_encumbrance",13,1,0},
		{"armor_action_encumbrance",13,1,0},
		{"armor_mind_encumbrance",16,1,0},
		{"armor_rating",1,1,0, true},
		{"armor_special_type",1,1,0, true},
		{"armor_special_effectiveness",15,30,0},
		{"armor_special_integrity",100,100,0, true},
		{"useCount",1,11,0},
	},
	customizationStringName = {},
	customizationValues = {}
}


addLootItemTemplate("armor_segment_chitin_advanced", armor_segment_chitin_advanced)
