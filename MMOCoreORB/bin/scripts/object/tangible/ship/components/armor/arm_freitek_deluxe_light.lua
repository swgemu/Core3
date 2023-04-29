object_tangible_ship_components_armor_arm_freitek_deluxe_light = object_tangible_ship_components_armor_shared_arm_freitek_deluxe_light:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_freitek_deluxe_light",

	attributes = {
		{"currentHitpoints", 181},
		{"maximumHitpoints", 181},
		{"maximumArmorHitpoints", 181},
		{"currentArmorHitpoints", 181},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1387.57},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_freitek_deluxe_light, "object/tangible/ship/components/armor/arm_freitek_deluxe_light.iff")
