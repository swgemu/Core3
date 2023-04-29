object_tangible_ship_components_armor_arm_subpro_limited_heavy_plastisteel = object_tangible_ship_components_armor_shared_arm_subpro_limited_heavy_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_subpro_limited_heavy_plastisteel",

	attributes = {
		{"currentHitpoints", 1026.62},
		{"maximumHitpoints", 1026.62},
		{"maximumArmorHitpoints", 1026.62},
		{"currentArmorHitpoints", 1026.62},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 13773.2},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_subpro_limited_heavy_plastisteel, "object/tangible/ship/components/armor/arm_subpro_limited_heavy_plastisteel.iff")
