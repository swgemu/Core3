object_tangible_ship_components_armor_arm_kessel_imperial_sds_imperial_impervious = object_tangible_ship_components_armor_shared_arm_kessel_imperial_sds_imperial_impervious:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_kessel_imperial_sds_imperial_impervious",

	attributes = {
		{"currentHitpoints", 1833.96},
		{"maximumHitpoints", 1833.96},
		{"maximumArmorHitpoints", 1833.96},
		{"currentArmorHitpoints", 1833.96},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 46530},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.3},
		{"energyMaintenance", 0},
		{"mass", 0.1},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_kessel_imperial_sds_imperial_impervious, "object/tangible/ship/components/armor/arm_kessel_imperial_sds_imperial_impervious.iff")
