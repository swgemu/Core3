armor_segment_bone_advanced = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/tangible/component/armor/armor_segment_bone_advanced.iff",
	craftingValues = {
		{"hit_points",1000,1000,0, true},
		{"armor_effectiveness",5,10,10},
		{"armor_integrity",500,1000,0},
		{"armor_health_encumbrance",6,1,0},
		{"armor_action_encumbrance",8,1,0},
		{"armor_mind_encumbrance",4,1,0},
		{"armor_rating",1,1,0, true},
		{"armor_special_type",2,2,0, true},
		{"armor_special_effectiveness",10,20,0},
		{"armor_special_integrity",100,100,0, true},
		{"useCount",1,11,0},
	},
	customizationStringName = {},
	customizationValues = {}
}


addLootItemTemplate("armor_segment_bone_advanced", armor_segment_bone_advanced)
