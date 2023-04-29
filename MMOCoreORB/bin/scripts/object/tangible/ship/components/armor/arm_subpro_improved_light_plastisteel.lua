object_tangible_ship_components_armor_arm_subpro_improved_light_plastisteel = object_tangible_ship_components_armor_shared_arm_subpro_improved_light_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_subpro_improved_light_plastisteel",

	attributes = {
		{"currentHitpoints", 379.04},
		{"maximumHitpoints", 379.04},
		{"maximumArmorHitpoints", 379.04},
		{"currentArmorHitpoints", 379.04},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2252.25},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.318},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_subpro_improved_light_plastisteel, "object/tangible/ship/components/armor/arm_subpro_improved_light_plastisteel.iff")
