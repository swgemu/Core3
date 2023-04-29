object_tangible_ship_components_armor_arm_freitek_standard = object_tangible_ship_components_armor_shared_arm_freitek_standard:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_freitek_standard",

	attributes = {
		{"currentHitpoints", 473.8},
		{"maximumHitpoints", 473.8},
		{"maximumArmorHitpoints", 473.8},
		{"currentArmorHitpoints", 473.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 3862.69},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.3},
		{"energyMaintenance", 0},
		{"mass", 0.318},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_freitek_standard, "object/tangible/ship/components/armor/arm_freitek_standard.iff")
