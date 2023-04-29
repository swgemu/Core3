object_tangible_ship_components_armor_arm_mandal_custom_heavy_composite = object_tangible_ship_components_armor_shared_arm_mandal_custom_heavy_composite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mandal_custom_heavy_composite",

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
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mandal_custom_heavy_composite, "object/tangible/ship/components/armor/arm_mandal_custom_heavy_composite.iff")
