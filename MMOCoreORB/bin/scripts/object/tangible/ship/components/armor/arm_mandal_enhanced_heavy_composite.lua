object_tangible_ship_components_armor_arm_mandal_enhanced_heavy_composite = object_tangible_ship_components_armor_shared_arm_mandal_enhanced_heavy_composite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mandal_enhanced_heavy_composite",

	attributes = {
		{"currentHitpoints", 871.792},
		{"maximumHitpoints", 871.792},
		{"maximumArmorHitpoints", 871.792},
		{"currentArmorHitpoints", 871.792},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 9449.03},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mandal_enhanced_heavy_composite, "object/tangible/ship/components/armor/arm_mandal_enhanced_heavy_composite.iff")
