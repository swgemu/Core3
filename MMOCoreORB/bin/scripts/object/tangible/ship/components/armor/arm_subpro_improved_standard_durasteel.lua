object_tangible_ship_components_armor_arm_subpro_improved_standard_durasteel = object_tangible_ship_components_armor_shared_arm_subpro_improved_standard_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_subpro_improved_standard_durasteel",

	attributes = {
		{"currentHitpoints", 697.434},
		{"maximumHitpoints", 697.434},
		{"maximumArmorHitpoints", 697.434},
		{"currentArmorHitpoints", 697.434},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 5518.12},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.2},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_subpro_improved_standard_durasteel, "object/tangible/ship/components/armor/arm_subpro_improved_standard_durasteel.iff")
